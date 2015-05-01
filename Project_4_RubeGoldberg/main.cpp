#include <string>

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GL/glut.h>
#include <GLFrustum.h>
#include <GL/glui.h>

#include <GraphicsGlobals.h>
#include <PhysicsGlobals.h>
#include <CameraView.h>
#include <Object3D.h>
#include <Color.h>
#include <DebugTools.h>
#include <Timer.h>
#include <CountedArray.h>
#include <DataSystem.h>
#include <StringTools.h>
#include <ParticleObject.h>
#include <GroundArea.h>
#include <Boundings.h>//HACK: including Boundings for fixing scale on bounds
#include <RigidObject.h>
#include <RigidBodySystem.h>
#include <TransformObject.h>

#define RENDER_DATA mainView, shaderManager, mvpMatrix /*the necessary parameters for calling draw*/

using namespace nah;

//Engine Data
Timer engineTimer;
GLUI* gluiWindow;
int glutWindowID;
doubleFactor gcSimulationScale;

//datafile parsing values
const std::string DATA_DIR = "Data/";
const std::string DATAFILE_NAME = "LevelData.ini";

const std::string SEC_SIM = "simulation";
const std::string VAL_SCALEFACT = "scale factor";
const std::string VAL_GRAVITY = "gravity force";

const std::string SEC_GAME = "game";
const std::string VAL_NUM_OBJECTS = "num objects";

const std::string SEC_OBJ_PREFIX = "object";
const std::string VAL_OBJ_TYPE = "type";
const std::string VAL_OBJ_POS = "pos";//append axis

//GL rendering
GLShaderManager	shaderManager;
GLfloat			offset;
GLfloat			counter;
GLboolean		bDoSomething;
M3DMatrix44f	mvpMatrix;
GLint			width = 800, height = 600;

inline int getWindowWidth()
{ return width;	};
//{ return glutGet((GLenum)GLUT_WINDOW_WIDTH);	};
inline int getWindowHeight()
{ return height;	};
//{ return glutGet((GLenum)GLUT_WINDOW_HEIGHT);	};

//Debugging
bool gDebugGraphics = true;
bool gDebugPhysics = true;
Object3D* debugObj;
RigidBody* debugPhys;
int debugTargetIndex = 2;
bool gPauseSimulation = false;

//UI
GLUI_Control* camPosLocl;
GLUI_Control* camPosWrld;
GLUI_Control* targtIndx;
GLUI_Control* targtName;
GLUI_Control* targtPosGraph;
GLUI_Control* targtPosPhys;
GLUI_Control* targtVel;
GLUI_Control* targtRot;
GLUI_Control* collisionVal;

CameraView* mainView;
float viewDefaultDistance = 55.0f;//starting distance from any planet

//Implementation Data

//physics objects
std::vector<RigidBody*> gameObjects;
RigidObject* model1;
RigidObject* model2;

//forces
float gravityForce = 5.0f;

//contacts
uint maxContacts = 50;//TODO: update based on number of particles
GroundArea* ground;

void ChangeSize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, width, height);

	float aspectRatio = (float)(getWindowWidth() / getWindowHeight());
	float fovCalc = 35.0f; // 46.6f / aspectRatio;
	mainView->viewFrustum->SetPerspective(fovCalc, aspectRatio, 1.0f, 1000.0f);
}

//Implementation Functions

//assign model batches to models here
void setupModels()
{
	model1->setBatchCube(0.5f, 0.5f, 0.5f);
	model2->setBatchCube(0.5f, 0.5f, 0.5f);

	//model2->setBounds(new Bounding());/*Point Bounding*//*Scaled Cube Bounding
	//HACK: fix bounds size since bounds do not currently account for scale
	RigidBody::RigidBounds model2Bounding = model2->getBounds();
	model2Bounding.width *= 2;
	model2Bounding.length *= 2;
	model2Bounding.height *= 2;
	model2->setBounds(model2Bounding);
	//*/
}
void setupWorld()
{
	{//view setup
		mainView->clearParent();
		mainView->clearTarget();
		Vector3f viewPosition;
		Rotation3D rotateView = Rotation3D(false);
		viewPosition[0] = 0;//left/right
		viewPosition[1] = -3;//up/down
		viewPosition[2] = -15;//towards/away
		rotateView.x = 0;
		rotateView.y = 0;
		rotateView.z = 0;
		mainView->setWorldPosition(viewPosition);
		mainView->setWorldRotation(rotateView);
	}

	{//Model1 setup
		//model1 position
		Vector3f model1Position;
		model1Position[0] = -3.0f;//X, left/right
		model1Position[1] = -3.0f;//Y, up/down
		model1Position[2] = 5.0f;//Z, in/out
		model1->refLocalTransform().position = (model1Position);

		//model1 rotation
		Rotation3D rotateModel1;
		rotateModel1.x = 0;
		rotateModel1.y = 0;
		rotateModel1.z = 0;
		model1->refLocalTransform().rotation = (rotateModel1);
	}

	{//Model2 setup
		//model2 position
		Vector3f model2Position;
		model2Position[0] = 0;//X, left/right
		model2Position[1] = 0.0f;//Y, up/down
		model2Position[2] = 5.0f;//Z, in/out
		model2->refLocalTransform().position = (model2Position);

		//model2 rotation
		Rotation3D rotateModel2;
		rotateModel2.x = 0;
		rotateModel2.y = 0;
		rotateModel2.z = 0;
		model2->refLocalTransform().rotation = (rotateModel2);

		//model2 scale
		model2->refLocalTransform().scale = 2.0f;
	}

	//Ground plane setup
	ground->physicsPosition.y = -5.0f;
}
void LoadData()
{
	gpDataReader->readIniFile(DATA_DIR + DATAFILE_NAME);

	gcSimulationScale.setFactor(nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(SEC_SIM, VAL_SCALEFACT)));

	int numObjects = atoi(gpDataReader->getIniKeyValue(SEC_GAME, VAL_NUM_OBJECTS).c_str());
	//Particle* holdParticle;
	for (int i = 0; i < numObjects; i++)
	{
		//holdParticle->setPhysicsPosition(Vector3f());
		//gameObjects.push_back(holdParticle);
	}
}

void ResetPhysics()
{
	//TODO: RigidBody force system
	//getGlobalParticleSystem()->clearParticleForceRegistrations();//clear existing force registrations so there don't end up being duplicates
	//getGlobalParticleSystem()->clearParticleContactValues();//clear existing contacts as they are probably no longer valid

	//set initial velocities
	model1->clearPhysics();
	model2->clearPhysics();

	//set constant acceleration
	model1->setAccelerationConst(0.0, -gravityForce, 0.0);
	model2->setAccelerationConst(0.0, -gravityForce, 0.0);
}
void SetupPhysics()
{
	//add particles to manager
	model1->Manage();
	model2->Manage();

	//TODO: RigidBody contact system
	//initialize particle contact generation and register particle contacts
	//getGlobalRigidBodySystem()->InitContactGenerator(maxContacts);
	//getGlobalRigidBodySystem()->ManageParticleContactGenerator(ground);

	ResetPhysics();
}
void setupUI()
{
	//setup and initialize GLUI
	{
		gluiWindow = GLUI_Master.create_glui("GLUI", 0, 
			glutGet((GLenum)GLUT_WINDOW_X) + glutGet((GLenum)GLUT_WINDOW_WIDTH), 
			glutGet((GLenum)GLUT_WINDOW_Y) + -20);

		std::string bufferText = "__________________;";
		
		//Debug controls
		GLUI_Panel* holdPanel = new GLUI_Panel(gluiWindow, "Debug Ctrl");
		new GLUI_Checkbox(holdPanel, "Show Physics Debug", (int*)&gDebugPhysics);
		new GLUI_Checkbox(holdPanel, "Show Graphics Debug", (int*)&gDebugGraphics);

		//Debug output
		holdPanel = new GLUI_Panel(gluiWindow, "Debug Out");
		targtPosGraph = new GLUI_StaticText(holdPanel, "Target_");
		camPosLocl = new GLUI_StaticText(holdPanel, ("Camera_L: " + bufferText).c_str());
		camPosWrld = new GLUI_StaticText(holdPanel, ("Camera_W: " + bufferText).c_str());
		new GLUI_Separator(holdPanel);
		targtIndx = new GLUI_EditText(holdPanel, "Index: ", &debugTargetIndex, GLUI_EDITTEXT_INT);
		targtName = new GLUI_StaticText(holdPanel, "Target_");
		targtPosPhys = new GLUI_StaticText(holdPanel, "Target_");
		targtVel = new GLUI_StaticText(holdPanel, "Target_");

		//Collision testing
		holdPanel = new GLUI_Panel(gluiWindow, "Collision Testing");
		collisionVal = new GLUI_StaticText(holdPanel, ("Ground Collision: " + bufferText).c_str());

		gluiWindow->set_main_gfx_window(glutWindowID);
	}
}
void myInit()
{
	engineTimer.Reset();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	shaderManager.InitializeStockShaders();

	glEnable(GL_DEPTH_TEST);

	//Projection
	mainView->viewFrustum->SetPerspective(35.0f, (float)(width / height), 1.0f, 1000.0f);

	//LoadData();

	setupModels();

	setupWorld();

	SetupPhysics();

	setupUI();

	//mainView->clearParent();
	//mainView->clearTarget();
}
void ResetView()
{
	setupWorld();
}
void ResetSimulation()
{
	ResetView();
	ResetPhysics();
};

void UpdateUI()
{
	//Set debug targets
	debugObj = model2;
	if (debugTargetIndex < 0)
		debugTargetIndex = getGlobalRigidBodySystem()->numRigidBodies() - 1;//wrap back to the last index
	else if (debugTargetIndex >= (int)getGlobalRigidBodySystem()->numRigidBodies())
		debugTargetIndex = 0;//wrap forward to the first index
	debugPhys = getGlobalRigidBodySystem()->getRigidBody(debugTargetIndex);

	//Handle Debug
	if (gDebugPhysics || gDebugGraphics)
	{
		//TODO: limit character lengths so the numbers don't jump left/right as they change
		if (gDebugGraphics)
		{
			//Debug output
			camPosLocl->set_text(("Camera_L: \n" + mainView->getLocalTransform().toStringMultiLine(true, true, false)).c_str());
			camPosWrld->set_text(("Camera_W: \n" + mainView->getWorldTransform().toStringMultiLine(true, true, false)).c_str());
			if (debugObj != nullptr)
				targtPosGraph->set_text(("GrphObjPos: \n" + debugObj->getWorldTransform().toStringMultiLine()).c_str());
		}
		if (gDebugPhysics)
		{
			if (debugPhys != nullptr)
			{
				targtIndx->set_int_val(debugTargetIndex);
				targtName->set_text(("Phys Name:\n  " + debugPhys->getName()).c_str());
				//targtPosGraph->set_text(("GrphPhysPos:\n  " + debugPhys->getWorldTransform().position.toString()).c_str());
				targtPosPhys->set_text(("SimPos:\n  " + debugPhys->getPhysicsPosition().toString()).c_str());
				targtVel->set_text(("Velocity:\n  " + debugPhys->getVelocityLinear().toString()).c_str());
			}

			std::string val = "beep";
			collisionVal->set_text(("Ground Collision: " + val).c_str());//TODO: output collision information
		}
		static bool isRefreshed = false;
		if (!isRefreshed)
		{
			gluiWindow->refresh();
			isRefreshed = true;
		}
	}
}

void RenderScene(void)
{
	//Swap Colors
	GLfloat vColor[] = { 1.0f, 1.0f, 1.0f, 1.0f	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//TODO: Depth Buffer
	//Draw all models
	model1->Draw(RENDER_DATA);
	model2->Draw(RENDER_DATA);
	ground->Draw(RENDER_DATA);

	UpdateUI();

	glutSwapBuffers();
}

void Keys(unsigned char key, int x, int y)
{
	if (key == 27)//Esc
		exit(0);

	//Move view
	float viewSpeed = 1;
	if ((key == 'W') || (key == 'w'))//view move forward
	{
		mainView->refLocalTransform().moveForward(viewSpeed);
	}
	if ((key == 'A') || (key == 'a'))//view move left
	{
		mainView->refLocalTransform().moveRight(-viewSpeed);
	}
	if ((key == 'S') || (key == 's'))//view move backward
	{
		mainView->refLocalTransform().moveForward(-viewSpeed);
	}
	if ((key == 'D') || (key == 'd'))//view move right
	{
		mainView->refLocalTransform().moveRight(viewSpeed);
	}
	if ((key == 'R') || (key == 'r'))//view rise
	{
		//mainView->localTransform.moveUp(viewSpeed);//local rise
		//want to move up/down in world
		mainView->refLocalTransform().position.y += viewSpeed;
	}
	if ((key == 'F') || (key == 'f'))//view fall
	{
		//mainView->localTransform.moveUp(-viewSpeed);//local fall
		//want to move up/down in world
		mainView->refLocalTransform().position.y -= viewSpeed;
	}

	//Rotate view
	float viewSpinSpeed = 10.0f;
	if ((key == 'Q') || (key == 'q'))
	{
		//roll left
		mainView->refLocalTransform().rotation.rotateRollRightDeg(-viewSpinSpeed);
	}

	if ((key == 'E') || (key == 'e'))
	{
		//roll right
		mainView->refLocalTransform().rotation.rotateRollRightDeg(viewSpinSpeed);
	}

	//Move target planet
	float model2Speed = 1;
	if ((key == 'L') || (key == 'l'))
	{
		model2->refLocalTransform().position.x += model2Speed;//model position X up
	}
	if ((key == 'J') || (key == 'j'))
	{
		model2->refLocalTransform().position.x -= model2Speed;//model position X down
	}
	if ((key == 'U') || (key == 'u'))
	{
		model2->refLocalTransform().position.y += model2Speed;//model position Y up
	}
	if ((key == 'O') || (key == 'o'))
	{
		model2->refLocalTransform().position.y -= model2Speed;//model position Y down
	}
	if ((key == 'I') || (key == 'i'))
	{
		model2->refLocalTransform().position.z += model2Speed;//model position Z up
	}
	if ((key == 'K') || (key == 'k'))
	{
		model2->refLocalTransform().position.z -= model2Speed;//model position Z down
	}

	//View controls
	if ((key == 'G') || (key == 'g'))
	{
		//unlock the camera from the target
		mainView->clearTarget();
		mainView->clearParent();
	}
}
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_HOME)//reset camera
		ResetSimulation();
	if (key == GLUT_KEY_END)//pause
		gPauseSimulation = !gPauseSimulation;

	//iterate through all the particles for debugging
	if (key == GLUT_KEY_PAGE_UP)//previous particle
		debugTargetIndex--;
	if (key == GLUT_KEY_PAGE_DOWN)//next particle
		debugTargetIndex++;

	//Rotate view
	float viewTurnSpeed = 5.0f;
	if (key == GLUT_KEY_LEFT)
	{
		mainView->refLocalTransform().rotation.rotateYawTurnRightDeg(-viewTurnSpeed);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		mainView->refLocalTransform().rotation.rotateYawTurnRightDeg(viewTurnSpeed);
	}
	if (key == GLUT_KEY_UP)
	{
		mainView->refLocalTransform().rotation.rotatePitchTiltUpDeg(viewTurnSpeed);
	}
	if (key == GLUT_KEY_DOWN)
	{
		mainView->refLocalTransform().rotation.rotatePitchTiltUpDeg(-viewTurnSpeed);
	}
}

void create()
{
	DataSystem::instantiateGlobal();
	RigidBodySystem::InstantiateGlobal();

	mainView = new CameraView();

	gcSimulationScale.setFactor(1.0f);

	//Create Objects
	model1 = new RigidObject(5.0f, "Bonus Model");
	model2 = new RigidObject(10.0f, "Falling Model");
	ground = new GroundArea(10.0f, 10.0f, -5.0f);
}
void Update()
{
	Time elapsedSeconds = engineTimer.ElapsedSeconds();

	//physics
	if (!gPauseSimulation)
	{
		gpRigidBodySystem->PhysicsUpdate(elapsedSeconds);
	}

	//graphics
	glutSetWindow(glutWindowID);
	glutPostRedisplay();

	engineTimer.Reset();
}
void cleanup()
{
	delete mainView;
	mainView = nullptr;

	//Clean up Objects
	model1->Unmanage();
	delete model1;
	model1 = nullptr;

	model2->Unmanage();
	delete model2;
	model2 = nullptr;

	/*prevent end of program crash due to glut extra update
	delete modelLink1;
	modelLink1 = nullptr;

	delete modelLink2;
	modelLink2 = nullptr;

	delete ground;
	ground = nullptr;
	*/

	RigidBodySystem::ClearGlobal();
	DataSystem::clearGlobal();
}

// Entry
int main(int argc, char* argv[])
{
	atexit(cleanup);

	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_ALPHA);

	glutInitWindowSize(getWindowWidth(), getWindowHeight());

	glutWindowID = glutCreateWindow("Boxor");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(Keys);
	//glutIdleFunc(Update);
	GLUI_Master.set_glutIdleFunc(Update);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	create();
	myInit();

	glutMainLoop();
	cleanup();
	//Cleanup GLUI
	{
		gluiWindow->close();
		delete gluiWindow;
	}
	return 0;
}
