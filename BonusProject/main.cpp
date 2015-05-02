//System
#include <string>
#include <vector>

//OpenGL
#include <GLTools.h>
#include <GLShaderManager.h>
#include <GL/glut.h>
#include <GLFrustum.h>
#include <GL/glui.h>

//Tools Library
#include <GraphicsGlobals.h>
#include <PhysicsGlobals.h>
#include <CameraView.h>
#include <DebugTools.h>
#include <ParticleSystem.h>
#include <Timer.h>
#include <CountedArray.h>
#include <DataSystem.h>
#include <StringTools.h>
#include <ParticleObject.h>
#include <GroundArea.h>
#include <ParticleGravity.h>
#include <RandMath.h>
#include <ParticleCollisionGenerator.h>
#include <Boundings.h>
#include <ParticleObject.h>

#define RENDER_DATA mainView, shaderManager, mvpMatrix /*the necessary parameters for calling draw*/

using namespace nah;

//Engine Data
Timer engineTimer;
GLUI* gluiWindow;
int glutWindowID;
realFactor gcSimulationScale;

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
Particle* debugPhys;
int debugTargetIndex = 2;
bool gPauseSimulation = true;
bool gStepFrame = false;//when true, will pause the simulation and set itself to false

//UI
GLUI_Control* simPauseBtn;
GLUI_Control* camPosLocl;
GLUI_Control* camPosWrld;
GLUI_Control* targtIndx;
GLUI_Control* targtName;
GLUI_Control* targtPosGraph;
GLUI_Control* targtPosPhys;
GLUI_Control* targtVel;
GLUI_Control* collisionVal;

CameraView* mainView;
float viewDefaultDistance = 55.0f;//starting distance from any planet

//Implementation Data

//physics objects
vector<ParticleObject*> fallingObjects;
vector<ParticleObject*> boxObjects;
//TODO: load following data from file
float groundPos = -5.0f;
uint fallingCount = 10;
uint boxCount = 5;
ufloat fallingRadius = 0.5f;
Vector3f boxSizeMin = Vector3f(0.5f, 0.5f, 0.5f);
Vector3f boxSizeMax = Vector3f(1.0f, 2.0f, 1.0f);
Vector3f fallingPos = Vector3f(0, 5, 0);
Vector3f boxPos = Vector3f(0.0f, groundPos, 0.0f);
ufloat fallingSpacing = fallingRadius * 2.1f;
ufloat boxSpacingFactor = 2.1f;
real fallingMassMin = 5;
real fallingMassMax = 10;

//forces
float gravityForce = 5.0f;
ParticleGravity* worldGrav = nullptr;

//contacts
uint maxContacts = fallingCount * boxCount * 2;//TODO: update based on number of particles
GroundArea* ground;
ParticleCollisionGenerator* collider;

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
void TogglePauseSimulation(int id = -1)
{
	gPauseSimulation = !gPauseSimulation;
	simPauseBtn->set_int_val((int)gPauseSimulation);
}

//assign model batches to models here
void setupModels()
{
	for (uint i = 0; i < fallingObjects.size(); i++)
	{
		fallingObjects[i]->setBatchSphere(fallingRadius);
		//fallingObjects[i]->setBatchCube(fallingRadius, fallingRadius, fallingRadius);
	}
	for (uint j = 0; j < boxObjects.size(); j++)
	{
		float sizeX = nah::math::randomFloat(boxSizeMin.x, boxSizeMax.x);
		float sizeY = nah::math::randomFloat(boxSizeMin.y, boxSizeMax.y);
		float sizeZ = nah::math::randomFloat(boxSizeMin.z, boxSizeMax.z);
		boxObjects[j]->setBatchCube(sizeX, sizeY, sizeZ);
	}
}
void setupView()
	{//view setup
		mainView->clearParent();
		mainView->clearTarget();
		Vector3f viewPosition;
		Rotation3D rotateView = Rotation3D(false);
		viewPosition[0] = 0;//left/right
		viewPosition.y = 0;//up/down
		viewPosition.z = -viewDefaultDistance;//towards/away
		rotateView[0] = 0;
		rotateView[1] = 0;
		rotateView[2] = 0;
		mainView->setWorldPosition(viewPosition);
		mainView->setWorldRotation(rotateView);
	}
void setupWorld()
{
	int rowCount = (int)(sqrt(fallingCount * 0.25f));
	int colCount = (int)((fallingCount*0.5f) / (rowCount+1));//estimation
	//TODO: offset spheres at various heights and horizontal positions so they can collide
	int curRow = 0;
	int curCol = 0;
	int heightCount = 0;
	float startX = colCount * fallingSpacing * -0.5f;
	float startZ = rowCount * fallingSpacing * -0.5f;
	for (uint i = 0; i < fallingObjects.size(); i++)
	{
		Vector3f model1Position;
		model1Position[0] = fallingPos.x + startX + (curCol * fallingSpacing)
				+ (heightCount * fallingRadius * 0.5f);//X, left/right
		model1Position[1] = fallingPos.y + fallingRadius + (heightCount * 2.1f * fallingRadius);//position at half height
		model1Position[2] = fallingPos.z + startZ + (curRow * fallingSpacing)
				+ (heightCount * fallingRadius * 0.5f);//Z, in/out
		fallingObjects[i]->refLocalTransform().position = (model1Position);

		curRow++;//next row
		if (curRow >= rowCount)
		{
			curRow = 0;
			curCol++;//next column
		}
		if(curCol >= colCount)
		{
			curCol = 0;
			heightCount++;
		}
	}

	rowCount = (int)sqrt(boxCount);
	colCount = boxCount / rowCount;//estimation
	curRow = 0;
	curCol = 0;
	float xSpacing, zSpacing;
	//Double-Spaced boxes
	for (uint j = 0; j < boxObjects.size(); j++)
	{
		//spacing calculation
		xSpacing = boxSpacingFactor * boxObjects[j]->getBounds().getDimensions().x;
		zSpacing = boxSpacingFactor * boxObjects[j]->getBounds().getDimensions().z;
		startX = colCount * xSpacing * -0.5f;
		startZ = rowCount * zSpacing * -0.5f;

		Vector3f model2Position;
		model2Position[0] = boxPos.x + startX + (curCol * xSpacing)
			+ (0.5f * boxObjects[j]->getBounds().getDimensions().x);//X, left/right
		model2Position[1] = boxPos.y + (0.5f * boxObjects[j]->getBounds().getDimensions().y);//position at half height
		model2Position[2] = boxPos.z + startZ + (curRow * zSpacing)
			+ (0.5f * boxObjects[j]->getBounds().getDimensions().z);//Z, in/out
		boxObjects[j]->refLocalTransform().position = (model2Position);

		curRow++;//next row
		if (curRow >= rowCount)
		{
			curRow -= rowCount;
			curCol++;//next column
		}
	}

	//Ground plane setup
	ground->physicsPosition.y = groundPos;
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
	getGlobalParticleSystem()->clearParticleForceRegistrations();//clear existing force registrations so there don't end up being duplicates
	getGlobalParticleSystem()->clearParticleContactValues();//clear existing contacts as they are probably no longer valid

	//initialize physics
	SAFE_ASSIGN(worldGrav) = new ParticleGravity(Vector3f(0.0f, -gravityForce, 0.0f));

	for (uint i = 0; i < fallingObjects.size(); i++)
	{
		fallingObjects[i]->clearPhysics();
		getGlobalParticleSystem()->RegisterParticleForce(worldGrav, fallingObjects[i]);
	}
	for (uint j = 0; j < boxObjects.size(); j++)
	{
		boxObjects[j]->clearPhysics();
	}
}
void SetupPhysics()
{
	//initialize particle contact generation and register particle contacts
	getGlobalParticleSystem()->InitContactGenerator(maxContacts);
	getGlobalParticleSystem()->ManageParticleContactGenerator(ground);
	getGlobalParticleSystem()->ManageParticleContactGenerator(collider);

	ResetPhysics();
}

void ResetView(int id = -1)
{
	setupView();
}
void ResetSimulation(int id = -1)
{
	setupWorld();
	ResetPhysics();
}
void StepSimulation(int id = -1)
{
	gStepFrame = true;
	gPauseSimulation = false;
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

		holdPanel = new GLUI_Panel(gluiWindow, "Simulation Ctrl");
		simPauseBtn = new GLUI_Checkbox(holdPanel, "Pause Simulation", (int*)&gPauseSimulation);
		new GLUI_Button(holdPanel, "Reset View", -1, ResetView);
		new GLUI_Button(holdPanel, "Reset Simulation", -1, ResetSimulation);
		new GLUI_Button(holdPanel, "Simulation Step", -1, StepSimulation);

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

	setupView();
	setupWorld();

	SetupPhysics();

	setupUI();

	//mainView->clearParent();
	//mainView->clearTarget();
}

void UpdateUI()
{
	//sync values
	//simPauseBtn->set_int_val((int)gPauseSimulation);

	//Set debug targets
	debugObj = ground;
	if (debugTargetIndex < 0)
		debugTargetIndex = getGlobalParticleSystem()->numParticles() - 1;//wrap back to the last index
	else if (debugTargetIndex >= (int)getGlobalParticleSystem()->numParticles())
		debugTargetIndex = 0;//wrap forward to the first index
	debugPhys = getGlobalParticleSystem()->getParticle(debugTargetIndex);

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
	GLfloat vColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//TODO: Depth Buffer
	//Draw all models
	for (uint i = 0; i < fallingObjects.size(); i++)
		fallingObjects[i]->Draw(RENDER_DATA);
	for (uint j = 0; j < boxObjects.size(); j++)
		boxObjects[j]->Draw(RENDER_DATA);
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
	{
		ResetView();
		ResetSimulation();
	}
	if (key == GLUT_KEY_END)//pause
		TogglePauseSimulation();


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
	ParticleSystem::InstantiateGlobal();

	mainView = new CameraView();

	gcSimulationScale.setFactor(1.0f);

	//Create Objects
	ParticleObject* holdObject;
	for (uint i = 0; i < fallingCount; i++)
	{
		holdObject = new ParticleObject(nah::math::randomDouble(fallingMassMin, fallingMassMax), "Falling_" + std::to_string(i));
		holdObject->Manage();

		fallingObjects.push_back(holdObject);
	}
	for (uint j = 0; j < boxCount; j++)
	{
		//Boxes have infinite mass
		holdObject = new ParticleObject(0, "Box_" + std::to_string(j));
		holdObject->Manage();

		boxObjects.push_back(holdObject);
	}
	ground = new GroundArea(10.0f, 10.0f, -5.0f);
	collider = new ParticleCollisionGenerator();
}
void Update()
{
	Time elapsedSeconds = engineTimer.ElapsedSeconds();

	//physics
	if (!gPauseSimulation)
	{
	gpParticleSystem->PhysicsUpdate(elapsedSeconds);
	gpParticleSystem->UpdateForces(elapsedSeconds);
	gpParticleSystem->UpdateContacts(elapsedSeconds);
	}
	if (gStepFrame)
	{
		gPauseSimulation = true;
		gStepFrame = false;
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
	int delIndx;
	while(fallingObjects.size() > 0)
	{
		delIndx = fallingObjects.size() - 1;
		fallingObjects[delIndx]->Unmanage();
		SAFE_DELETE(fallingObjects[delIndx]);
		fallingObjects.pop_back();
	}
	while (boxObjects.size() > 0)
	{
		delIndx = boxObjects.size() - 1;
		boxObjects[delIndx]->Unmanage();
		SAFE_DELETE(boxObjects[delIndx]);
		boxObjects.pop_back();
	}

	/*prevent end of program crash due to glut extra update
	delete ground;
	ground = nullptr;

	SAFE_DELETE(collider);
	*/

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
