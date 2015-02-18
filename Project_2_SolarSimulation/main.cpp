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

#include "PlanetaryDataKey.h"
#include "Planet.h"
#include "PlanetaryGravity.h"

using namespace nah;

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

int getWindowWidth() { return width;	};
int getWindowHeight() { return height;	};
//{ return glutGet((GLenum)GLUT_WINDOW_WIDTH); };
//{ return glutGet((GLenum)GLUT_WINDOW_HEIGHT); };

bool gDebugGraphics = true;
bool gDebugPhysics = true;
doubleFactor gcSimulationScale;
GLUI_Control* camPosLocl;
GLUI_Control* camPosWrld;
GLUI_Control* targtPos;

CameraView* mainView;
float viewDefaultDistance = 15.0f;//starting distance from any planet

// Planet* model1;
// Planet* model2;

Planet* targetPlanet;//for view/debugging
//use PlanetDataKey::PlanetNames for indexes
CountedArray<Planet*> planetList = CountedArray<Planet*>(PlanetDataKey::NUM_PLANETS+1);

void ChangeSize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, width, height);

	float aspectRatio = (float)(getWindowWidth() / getWindowHeight());
	float fovCalc = 35.0f; // 46.6f / aspectRatio;
	mainView->viewFrustum->SetPerspective(fovCalc, aspectRatio, 1.0f, 1000.0f);
}

void setTargetPlanet(PlanetDataKey::PlanetName newTarget)
{
	targetPlanet = planetList[newTarget];
		/*
	mainView->setWorldPosition(
		Vector3f::Distancepoint(
		targetPlanet->getWorldTransform().position, 
		mainView->getWorldTransform().position, 
		viewDefaultDistance + targetPlanet->getRadius())
		);
		//*/
	mainView->setParent(targetPlanet);
	mainView->setTarget(targetPlanet);

	mainView->refLocalTransform().position = Vector3f(0.0f, 1.0f * viewDefaultDistance, 0.5f * viewDefaultDistance);
	mainView->refLocalTransform().rotation = Vector3f(-65.0f, 0.0f, 0.0f);//HACK: placeholder until setTarget works

}

//assign model batches to models here
void setupModels()
{
}
void setupWorld()
{
	{//view setup
		mainView->clearParent();
		mainView->clearTarget();
		M3DVector3f viewPosition;
		M3DVector3f rotateView;
		viewPosition[0] = 0;//left/right
		viewPosition[1] = 1;//up/down
		viewPosition[2] = 0.5;//towards/away
		rotateView[0] = -65;
		rotateView[1] = 0;
		rotateView[2] = 0;
		mainView->setWorldPosition(viewPosition);
		mainView->setWorldRotation(rotateView);
	}

	for each (Planet* var in planetList)
	{
		var->clearParent();
		var->clearTarget();
		var->resetOrbit();
	}
}
void setupPhysics()
{
	getGlobalParticleSystem()->clearParticleForceRegistrations();//clear existing force registrations so there don't end up being duplicates

	//set initial velocities

	//create and set force registrations
	PlanetaryGravity* tempGravity;
	for (size_t grav = 0; grav < planetList.count(); grav++)
	{
		tempGravity = planetList[grav]->GenerateGravity();
		for (size_t p = 0; p < planetList.count(); p++)
		{
			//if (grav != p) getGlobalParticleSystem()->RegisterParticleForce(tempGravity, planetList[p]);
			//if (grav == 0) getGlobalParticleSystem()->RegisterParticleForce(tempGravity, planetList[p]);//assign sun gravity
		}
	}
}
void setupUI()
{
	//setup and initialize GLUI
	{
		gluiWindow = GLUI_Master.create_glui("GLUI", 0, 
			glutGet((GLenum)GLUT_WINDOW_X) + glutGet((GLenum)GLUT_WINDOW_WIDTH), 
			glutGet((GLenum)GLUT_WINDOW_Y) + -20);

		//Debug controls
		GLUI_Panel* holdPanel = new GLUI_Panel(gluiWindow, "Debug Ctrl");
		new GLUI_Checkbox(holdPanel, "Show Physics Debug", (int*)&gDebugPhysics);
		new GLUI_Checkbox(holdPanel, "Show Graphics Debug", (int*)&gDebugGraphics);

		//Debug output
		holdPanel = new GLUI_Panel(gluiWindow, "Debug Out");
		camPosLocl = new GLUI_StaticText(holdPanel, "Camera_L");
		camPosWrld = new GLUI_StaticText(holdPanel, "Camera_W");
		targtPos = new GLUI_TextBox(holdPanel, "Target_");
		
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

	setTargetPlanet(PlanetDataKey::NUM_PLANETS);
	mainView->clearParent();
	mainView->clearTarget();
}
void ResetView()
{
	setupWorld();
	setupPhysics();
}

void RenderScene(void)
{
	//Swap Colors
	GLfloat vColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//TODO: Depth Buffer
	//Draw all models
	//Draw planets
	for each (Planet* var in planetList)
	{
		var->Draw(mainView, shaderManager, mvpMatrix);
	}

	if (gDebugPhysics || gDebugGraphics)
	{
		if (gDebugGraphics)
		{
			//Debug output
			camPosLocl->set_text(("Camera_L: \n" + mainView->getLocalTransform().toStringMultiLine(true, true, false)).c_str());
			camPosWrld->set_text(("Camera_W: \n" + mainView->getWorldTransform().toStringMultiLine(true, true, false)).c_str());
			//targtPos->set_text(("Target: \n" + targetPlanet->getWorldTransform().toStringMultiLine()).c_str());
		}
		if (gDebugPhysics)
		{
			targtPos->set_text((targetPlanet->getName() +
				" \n| Vel:\n " + targetPlanet->getVelocity().toString() +
				" \n| SimPos:\n " + targetPlanet->Simulation_getPosition().toString() +
				" \n| GrphPos:\n " + targetPlanet->getWorldTransform().position.toString()
				).c_str());
		}
		static bool isRefreshed = false;
		if (!isRefreshed)
		{
			gluiWindow->refresh();
			isRefreshed = true;
		}
	}

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
		targetPlanet->refLocalTransform().position.x += model2Speed;//model position X up
	}
	if ((key == 'J') || (key == 'j'))
	{
		targetPlanet->refLocalTransform().position.x -= model2Speed;//model position X down
	}
	if((key == 'I')||(key == 'i'))
	{
		targetPlanet->refLocalTransform().position.y += model2Speed;//model position Y up
	}
	if((key == 'K')||(key == 'k'))
	{
		targetPlanet->refLocalTransform().position.y -= model2Speed;//model position Y down
	}
	if((key == 'O')||(key == 'o'))
	{
		targetPlanet->refLocalTransform().position.z += model2Speed;//model position Z up
	}
	if((key == 'U')||(key == 'u'))
	{
		targetPlanet->refLocalTransform().position.z -= model2Speed;//model position Z down
	}

	//Set view/debug target
	for (int i = 0; i < PlanetDataKey::NUM_PLANETS; i++)
	{
		//HACK: allow unlocking camera
		mainView->clearTarget();
		mainView->clearParent();

		//check if one of the number keys was pressed, set that planet as the target
		if (key == std::to_string(i)[0])
		{
			setTargetPlanet((PlanetDataKey::PlanetName)i);
			break;
		}
	}
}
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_HOME)//reset camera
		ResetView();
	if (key == GLUT_KEY_END)//pause
	{
		//HACK: cancel physics
		for each (Planet* p in planetList)
		{
			p->clearPhysics();
		}

		//also putting a planet at 0,0,0 in the hopes that I can see it
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

	//load planet data
	gpDataReader->readIniFile(DATA_DIR + PlanetDataKey::DATAFILE_NAME);

	gcSimulationScale.setFactor(nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(PlanetDataKey::SEC_SIM, PlanetDataKey::VAL_SCALEFACT)));

	for (int i = 0; i < PlanetDataKey::NUM_PLANETS; i++)
	{
		PlanetDataKey::PlanetName iP = (PlanetDataKey::PlanetName)i;
		planetList[i] = new Planet(
			(float)nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(PlanetDataKey::getPlanetNameString(iP), PlanetDataKey::VAL_MASS))
			, (float)nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(PlanetDataKey::getPlanetNameString(iP), PlanetDataKey::VAL_SIZE))
			, (float)nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(PlanetDataKey::getPlanetNameString(iP), PlanetDataKey::VAL_DIST))
			, (float)nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(PlanetDataKey::getPlanetNameString(iP), PlanetDataKey::VAL_VEL))
			, PlanetDataKey::getPlanetNameString(iP)
			);
		planetList[i]->manage();
	}

	//extra debugging planet
	planetList[PlanetDataKey::NUM_PLANETS] = new Planet(
		(float)nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(PlanetDataKey::getPlanetNameString(PlanetDataKey::EARTH), PlanetDataKey::VAL_MASS))
		, (float)nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(PlanetDataKey::getPlanetNameString(PlanetDataKey::EARTH), PlanetDataKey::VAL_SIZE))
		, 1.0f//(float)nah::StringTools::parseSciNotation(gpDataReader->getIniKeyValue(PlanetDataKey::getPlanetNameString(PlanetDataKey::EARTH), PlanetDataKey::VAL_DIST))
		, 1.0f//no velocity
		, "Le Bugger"
		);
	planetList[PlanetDataKey::NUM_PLANETS]->manage();

	gpDataReader->clearIniData();

}
void Update()
{
	Time elapsedSeconds = engineTimer.ElapsedSeconds();
	//physics
	gpParticleSystem->UpdatePhysics(elapsedSeconds);
	gpParticleSystem->UpdateForces(elapsedSeconds);

	//graphics
	glutSetWindow(glutWindowID);
	glutPostRedisplay();

	engineTimer.Reset();
}
void cleanup()
{
	delete mainView;
	mainView = nullptr;

	for each (Planet* var in planetList)
	{
		var->unmanage();
		delete var;
		var = nullptr;
	}

	ParticleSystem::ClearGlobal();
	DataSystem::clearGlobal();
}

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
