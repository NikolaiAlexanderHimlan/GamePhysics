#include <GLTools.h>
#include <GLShaderManager.h>
#include <GL/glut.h>
#include <GLFrustum.h>

#include <GraphicsGlobals.h>
#include <CameraView.h>
#include <Object3D.h>
#include <Color.h>
#include <DebugTools.h>
#include <ParticleSystem.h>
#include <Timer.h>

#include "Planet.h"

Timer engineTimer;

GLShaderManager	shaderManager;
GLfloat			offset;
GLfloat			counter;
GLboolean		bDoSomething;
M3DMatrix44f	mvpMatrix;
GLint			width, height;

int getWindowWidth() { return width;	};
int getWindowHeight() { return height;	};

CameraView* mainView;

Planet* model1;
Planet* model2;

void ChangeSize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0,0,width, height);

	mainView->viewFrustum->SetPerspective(35.0f, (float)(width/height), 1.0f, 1000.0f);
}

void setupModels()
{
	//model1->setBatchSphere(1.0f, 7);
	model1->setBatchCube(0.5f, 0.5f, 0.5f);
	model2->setBatchCube(0.5f, 0.5f, 0.5f);
}
void setupWorld()
{
	{//view setup
		M3DVector3f viewPosition;
		M3DVector3f rotateView;
		viewPosition[0] = 0;//left/right
		viewPosition[1] = 0;//up/down
		viewPosition[2] = 0;//towards/away
		rotateView[0] = 0;
		rotateView[1] = 0;
		rotateView[2] = 0;
		mainView->localTransform.setPosition(viewPosition);
		mainView->localTransform.setRotation(rotateView);
	}

	{//Model1 setup
		//model1 position
		M3DVector3f model1Position;
		model1Position[0] = 0;//X, left/right
		model1Position[1] = 0;//Y, up/down
		model1Position[2] = -5.0f;//Z, in/out
		model1->getLocalTransformRef().setPosition(model1Position);

		//model1 rotation
		M3DVector3f rotateModel1;
		rotateModel1[0] = 0;
		rotateModel1[1] = 0;
		rotateModel1[2] = 0;
		model1->getLocalTransformRef().setRotation(rotateModel1);
	}

	{//Model2 setup
		//model2 position
		M3DVector3f model2Position;
		model2Position[0] = 0;//X, left/right
		model2Position[1] = 0.5f;//Y, up/down
		model2Position[2] = -6.0f;//Z, in/out
		model2->getLocalTransformRef().setPosition(model2Position);

		//model2 rotation
		M3DVector3f rotateModel2;
		rotateModel2[0] = 0;
		rotateModel2[1] = 0;
		rotateModel2[2] = 0;
		model2->getLocalTransformRef().setRotation(rotateModel2);

		//model2 scale
		model2->getLocalTransformRef().setScale(2.0f);

		//model2 physics
		model2->setVelocity(Vector3f(1.0f, 0.0f, 0.0f));
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
}
void ResetView()
{
	setupWorld();
}

//HACK: using console output for debugging, inefficient and needs to be replaced
//#include <stdlib.h>
//#include <iostream>
#include <string>
void RenderScene(void)
{
	//Swap Colors
	GLfloat vColor[]=  { 1.0f, 1.0f, 1.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//TODO: Depth Buffer
	//Draw all models
	model1->Draw(mainView, shaderManager, mvpMatrix);
	model2->Draw(mainView, shaderManager, mvpMatrix);

	//Debug output
	std::string text = "Camera: \n" + mainView->localTransform.toStringMultiLine(true, true, false);
	Debug_OpenGL::outputText(Vector3f(1, 1), nah::Color(0.5f, 0.5f, 0.5f), 
		//GLUT_STROKE_ROMAN
		GLUT_BITMAP_8_BY_13
		, text.c_str());
	/*HACK: font doesn't load, placeholder
	std::system("cls");
	std::cout << "Camera: \n" + mainView->localTransform.toStringMultiLine(true, true, false) << std::endl;
	std::cout << "Model1: \n" + model1->localTransform.toStringMultiLine() << std::endl;
	std::cout << "Model2: \n" + model2->localTransform.toStringMultiLine() << std::endl;
	//*/

	glutSwapBuffers();
}

void Keys(unsigned char key, int x, int y)
{
	if(key == 27)//Esc
		exit(0);

	//Move view
	float viewSpeed = 1;
	if((key == 'W')||(key == 'w'))//view move forward
	{
		mainView->localTransform.moveForward(viewSpeed);
	}
	if((key == 'A')||(key == 'a'))//view move left
	{
		mainView->localTransform.moveRight(-viewSpeed);
	}
	if((key == 'S')||(key == 's'))//view move backward
	{
		mainView->localTransform.moveForward(-viewSpeed);
	}
	if((key == 'D')||(key == 'd'))//view move right
	{
		mainView->localTransform.moveRight(viewSpeed);
	}
	if((key == 'R')||(key == 'r'))//view rise
	{
		//mainView->localTransform.moveUp(viewSpeed);//local rise
		//want to move up/down in world
		mainView->localTransform.position.y += viewSpeed;
	}
	if((key == 'F')||(key == 'f'))//view fall
	{
		//mainView->localTransform.moveUp(-viewSpeed);//local fall
		//want to move up/down in world
		mainView->localTransform.position.y -= viewSpeed;
	}

	//Rotate view
	float viewSpinSpeed = 10.0f;
	if ((key == 'Q')||(key == 'q'))
	{
		//roll left
		mainView->localTransform.rotateRollRight(-viewSpinSpeed);
	}

	if ((key == 'E')||(key == 'e'))
	{
		//roll right
		mainView->localTransform.rotateRollRight(viewSpinSpeed);
	}

	//Move model2
	float model2Speed = 1;
	if((key == 'L')||(key == 'l'))
	{
		//model position X up
		model2->getLocalTransformRef().position.x += model2Speed;
	}
	if((key == 'J')||(key == 'j'))//model position X down
	{
		model2->getLocalTransformRef().position.x -= model2Speed;
	}
	if((key == 'I')||(key == 'i'))//model position Y up
	{
		model2->getLocalTransformRef().position.y += model2Speed;
	}
	if((key == 'K')||(key == 'k'))//model position Y down
	{
		model2->getLocalTransformRef().position.y -= model2Speed;
	}
	if((key == 'O')||(key == 'o'))//model position Z up
	{
		model2->getLocalTransformRef().position.z += model2Speed;
	}
	if((key == 'U')||(key == 'u'))
	{
		//model position Z down
		model2->getLocalTransformRef().position.z -= model2Speed;
	}

	//Rotate models
	float modelSpinSpeed = 10.0f;
	if ((key == 'V')||(key == 'v'))
	{
		model1->getLocalTransformRef().rotateTurnRight(-modelSpinSpeed);
	}
	if ((key == 'C')||(key=='c'))
	{
		model1->getLocalTransformRef().rotateTurnRight(modelSpinSpeed);
	}
	if ((key == 'Z') || (key == 'z'))
	{
		model2->getLocalTransformRef().rotateTurnRight(-modelSpinSpeed);
	}
	if ((key == 'X') || (key == 'x'))
	{
		model2->getLocalTransformRef().rotateTurnRight(modelSpinSpeed);
	}
}

void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_HOME)//reset camera
		ResetView();

	//Rotate view
	float viewTurnSpeed = 5.0f;
	if (key == GLUT_KEY_LEFT)
	{
		mainView->localTransform.rotateTurnRight(-viewTurnSpeed);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		mainView->localTransform.rotateTurnRight(viewTurnSpeed);
	}
	if(key==GLUT_KEY_UP)
	{
		mainView->localTransform.rotateTurnUp(viewTurnSpeed);
	}
	if(key==GLUT_KEY_DOWN)
	{
		mainView->localTransform.rotateTurnUp(-viewTurnSpeed);
	}
}

void create()
{
	ParticleSystem::InstantiateGlobal();
	
	mainView = new CameraView();
	model1 = new Planet(1.0f);
	model1->manage();
	model2 = new Planet(1.0f);
	model2->manage();
}
void Update()
{
	//physics
	gpParticleSystem->Update(engineTimer.ElapsedSeconds());

	//graphics
	glutPostRedisplay();

	engineTimer.reset();
}
void cleanup()
{
	delete mainView;
	mainView = NULL;

	delete model1;
	model1 = NULL;
	delete model2;
	model2 = NULL;

	ParticleSystem::ClearGlobal();
}

int main(int argc, char* argv[])
{
	atexit(cleanup);
	create();

	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA| GLUT_DEPTH | GLUT_STENCIL | GLUT_ALPHA);

	width = 800;
	height = 600;
	glutInitWindowSize(getWindowWidth(), getWindowHeight());

	glutCreateWindow("Boxor");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(Keys);
	glutIdleFunc(Update);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	myInit();

	glutMainLoop();
	cleanup();
	return 0;
}
