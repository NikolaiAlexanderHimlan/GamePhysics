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
#include <ParticleSystem.h>
#include <Timer.h>
#include <CountedArray.h>
#include <DataSystem.h>
#include <StringTools.h>
#include <PhysicsObject.h>
#include <GroundArea.h>
#include <ParticleGravity.h>

using namespace nah;

//Engine Data

Timer engineTimer;
GLUI* gluiWindow;
int glutWindowID;

const std::string DATA_DIR = "Data/";

GLShaderManager	shaderManager;
GLfloat			offset;
GLfloat			counter;
GLboolean		bDoSomething;
M3DMatrix44f	mvpMatrix;
GLint			width = 800, height = 600;

inline int getWindowWidth()
{ return width;	};
//{ return glutGet((GLenum)GLUT_WINDOW_WIDTH); };
inline int getWindowHeight()
{ return height;	};
//{ return glutGet((GLenum)GLUT_WINDOW_HEIGHT); };

bool gDebugGraphics = true;
bool gDebugPhysics = true;
doubleFactor gcSimulationScale;
GLUI_Control* camPosLocl;
GLUI_Control* camPosWrld;
GLUI_Control* targtPos;
GLUI_Control* collisionVal;

CameraView* mainView;
float viewDefaultDistance = 55.0f;//starting distance from any planet

//Implementation Data

//physics objects
PhysicsObject* model1;
PhysicsObject* model2;

//forces
float gravityForce = 0.5f;
ParticleGravity* worldGrav = nullptr;

//contacts
GroundArea* ground;
uint maxContacts = 4;//TODO: update based on number of particles

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
}
void setupWorld()
{
	{//view setup
		mainView->clearParent();
		mainView->clearTarget();
		M3DVector3f viewPosition;
		M3DVector3f rotateView;
		viewPosition[0] = 0;//left/right
		viewPosition[1] = -3;//up/down
		viewPosition[2] = -15;//towards/away
		rotateView[0] = 0;
		rotateView[1] = 0;
		rotateView[2] = 0;
		mainView->setWorldPosition(viewPosition);
		mainView->setWorldRotation(rotateView);
	}

	{//Model1 setup
	//model1 position
	M3DVector3f model1Position;
	model1Position[0] = 0;//X, left/right
	model1Position[1] = 0;//Y, up/down
		model1Position[2] = 5.0f;//Z, in/out
	model1->refLocalTransform().setPosition(model1Position);

	//model1 rotation
	M3DVector3f rotateModel1;
	rotateModel1[0] = 0;
	rotateModel1[1] = 0;
	rotateModel1[2] = 0;
	model1->refLocalTransform().setRotation(rotateModel1);
	}

	{//Model2 setup
		//model2 position
		M3DVector3f model2Position;
		model2Position[0] = 0;//X, left/right
		model2Position[1] = -5.0f;//Y, up/down
		model2Position[2] = 6.0f;//Z, in/out
		model2->refLocalTransform().setPosition(model2Position);

		//model2 rotation
		M3DVector3f rotateModel2;
		rotateModel2[0] = 0;
		rotateModel2[1] = 0;
		rotateModel2[2] = 0;
		model2->refLocalTransform().setRotation(rotateModel2);

		//model2 scale
		model2->refLocalTransform().setScale(2.0f);
	}

	//Ground plane setup
	ground->refLocalTransform().position.y = -5.0f;
}
void setupPhysics()
{
	getGlobalParticleSystem()->clearParticleForceRegistrations();//clear existing force registrations so there don't end up being duplicates

	//set initial velocities
	model2->clearPhysics();

	//create and set force registrations
	if (worldGrav != nullptr) delete worldGrav;
	worldGrav = new ParticleGravity(Vector3f(0.0f, -gravityForce, 0.0f));
	//getGlobalParticleSystem()->RegisterParticleForce(worldGrav, model2);

	//initialize particle contact generation and register particle contacts
	getGlobalParticleSystem()->InitContactGenerator(maxContacts);
	getGlobalParticleSystem()->ManageParticleContactGenerator(ground);
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
		camPosLocl = new GLUI_StaticText(holdPanel, ("Camera_L: " + bufferText).c_str());
		camPosWrld = new GLUI_StaticText(holdPanel, ("Camera_W: " + bufferText).c_str());
		targtPos = new GLUI_TextBox(holdPanel, "Target_");

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

	setupModels();

	setupWorld();

	setupPhysics();

	setupUI();

	//mainView->clearParent();
	//mainView->clearTarget();
}
void ResetView()
{
	setupWorld();
}
void ResetPhysics()
{
	setupPhysics();
};
void ResetSimulation()
{
	ResetView();
	ResetPhysics();
};

void UpdateUI()
{
	//Debugging
	Object3D* debugObj;
	PhysicsObject* debugPhys;
	//Set debug targets
	debugObj = model2;
	debugPhys = model2;
	//Handle Debug
	if (gDebugPhysics || gDebugGraphics)
	{
		if (gDebugGraphics)
		{
			//Debug output
			camPosLocl->set_text(("Camera_L: \n" + mainView->getLocalTransform().toStringMultiLine(true, true, false)).c_str());
			camPosWrld->set_text(("Camera_W: \n" + mainView->getWorldTransform().toStringMultiLine(true, true, false)).c_str());
			if (debugObj != nullptr)
				targtPos->set_text(("Target: \n" + debugObj->getWorldTransform().toStringMultiLine()).c_str());
		}
		if (gDebugPhysics)
		{
			if (debugPhys != nullptr)
			{
				targtPos->set_text((
					" Particle: " + debugPhys->getName() + 
					" \n| Vel:\n " + debugPhys->getVelocity().toString() +
					" \n| SimPos:\n " + debugPhys->getPhysicsPosition().toString() +
					" \n| GrphPos:\n " + debugPhys->getWorldTransform().position.toString()
					).c_str());
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
	GLfloat vColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//TODO: Depth Buffer
	//Draw all models
	model1->Draw(mainView, shaderManager, mvpMatrix);
	model2->Draw(mainView, shaderManager, mvpMatrix);
	ground->Draw(mainView, shaderManager, mvpMatrix);

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
		mainView->refLocalTransform().rotateRollRight(-viewSpinSpeed);
	}

	if ((key == 'E') || (key == 'e'))
	{
		//roll right
		mainView->refLocalTransform().rotateRollRight(viewSpinSpeed);
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
	if((key == 'I')||(key == 'i'))
	{
		model2->refLocalTransform().position.y += model2Speed;//model position Y up
	}
	if((key == 'K')||(key == 'k'))
	{
		model2->refLocalTransform().position.y -= model2Speed;//model position Y down
	}
	if((key == 'O')||(key == 'o'))
	{
		model2->refLocalTransform().position.z += model2Speed;//model position Z up
	}
	if((key == 'U')||(key == 'u'))
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
	{
		//TODO: pause physics simulation
	}

	//Rotate view
	float viewTurnSpeed = 5.0f;
	if (key == GLUT_KEY_LEFT)
	{
		mainView->refLocalTransform().rotateTurnRight(-viewTurnSpeed);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		mainView->refLocalTransform().rotateTurnRight(viewTurnSpeed);
	}
	if (key == GLUT_KEY_UP)
	{
		mainView->refLocalTransform().rotateTurnUp(viewTurnSpeed);
	}
	if (key == GLUT_KEY_DOWN)
	{
		mainView->refLocalTransform().rotateTurnUp(-viewTurnSpeed);
	}
}

void create()
{
	DataSystem::instantiateGlobal();
	ParticleSystem::InstantiateGlobal();

	mainView = new CameraView();

	gcSimulationScale.setFactor(1.0f);

	//Create Objects
	model1 = new PhysicsObject(5.0f);
	model2 = new PhysicsObject(10.0f, "Falling Model");
	model2->Manage();
	ground = new GroundArea(10.0f, 10.0f, -5.0f);
}
void Update()
{
	Time elapsedSeconds = engineTimer.ElapsedSeconds();
	//physics
	gpParticleSystem->UpdatePhysics(elapsedSeconds);
	gpParticleSystem->UpdateForces(elapsedSeconds);
	gpParticleSystem->UpdateContacts(elapsedSeconds);

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
	delete model1;
	model1 = nullptr;

	model2->Unmanage();
	delete model2;
	model2 = nullptr;

	delete ground;
	ground = nullptr;

	delete worldGrav;
	worldGrav = nullptr;

	ParticleSystem::ClearGlobal();
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
