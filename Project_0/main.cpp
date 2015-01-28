#include <GLTools.h>
#include <GLShaderManager.h>
#include <GL/glut.h>
#include <GLFrustum.h>

#include <CameraView.h>
#include <Object3D.h>
#include <Color.h>
#include <DebugTools.h>

GLShaderManager	shaderManager;
GLfloat			offset;
GLfloat			counter;
GLboolean		bDoSomething;
M3DMatrix44f	mvpMatrix;
GLint			width, height;
//GLfloat			rotateAroundModelZaxis;
//GLfloat			rotateAroundViewZaxis;

CameraView* mainView;

Object3D* model1;
Object3D* model2;

void ChangeSize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0,0,width, height);

	mainView->viewFrustum->SetPerspective(35.0f, (float)(width/height), 1.0f, 1000.0f);
}

void setupWorld()
{
	GLBatch* modelBatch1 = new GLBatch();
	GLBatch* modelBatch2 = new GLBatch();

	/*generate triangle model batch
	GLfloat			vVerts[] = {-0.5f, 0.0f, 0.0f, 
								0.5f, 0.0f, 0.0f, 
								0.0f, 0.5f, 0.0f};

	GLfloat			vColors[] = {1.0f, 0.0f, 0.0f, 1.0f, 
								0.0f, 1.0f, 0.0f, 1.0f, 
								0.0f, 0.0f, 1.0f, 1.0f};
	//*/
	//*generate cube model batch
	GLfloat vVerts[24 * 3];//number of indices times 3 points in a vertex
	GLfloat vColors[24 * 4];//number of indices times number of values per color
	int numIndices = 24;
	{
		int vectIndx[24] = { 1, 2, 3, 4,
			5, 8, 7, 6,
			1, 5, 6, 2,
			2, 6, 7, 3,
			3, 7, 8, 4,
			5, 1, 4, 8 };

		Vector3f vectVerts[8];
		{
			float x = 0.5f, y = 0.5f, z = 0.5f;
			vectVerts[0] = Vector3f(x, -y, -z);
			vectVerts[1] = Vector3f(x, -y, z);
			vectVerts[2] = Vector3f(-x, -y, z);
			vectVerts[3] = Vector3f(-x, -y, -z);
			vectVerts[4] = Vector3f(x, y, -z);
			vectVerts[5] = Vector3f(x, y, z);
			vectVerts[6] = Vector3f(-x, y, z);
			vectVerts[7] = Vector3f(-x, y, -z);
		}
		int counterCounter = 0;
		for (int i = 0; i < numIndices; i++)
		{
			vVerts[counterCounter++] = vectVerts[vectIndx[i] - 1].x;
			vVerts[counterCounter++] = vectVerts[vectIndx[i] - 1].y;
			vVerts[counterCounter++] = vectVerts[vectIndx[i] - 1].z;
		}

		nah::Color colorVerts[8];
		{
			colorVerts[0] = nah::Color::Red;
			colorVerts[1] = nah::Color::Aquamarine;
			colorVerts[2] = nah::Color::Blue;
			colorVerts[3] = nah::Color::DarkBlue;
			colorVerts[4] = nah::Color::DarkGreen;
			colorVerts[5] = nah::Color::DarkRed;
			colorVerts[6] = nah::Color::Green;
			colorVerts[7] = nah::Color::Orange;
		}
		counterCounter = 0;
		for (int i = 0; i < numIndices; i++)
		{
			vColors[counterCounter++] = colorVerts[vectIndx[i] - 1].rgbRed();
			vColors[counterCounter++] = colorVerts[vectIndx[i] - 1].rgbGreen();
			vColors[counterCounter++] = colorVerts[vectIndx[i] - 1].rgbBlue();
			vColors[counterCounter++] = colorVerts[vectIndx[i] - 1].rgbAlpha();
		}
	}
	//*/

	//modelBatch1->Begin(GL_TRIANGLES, 3);
	modelBatch1->Begin(GL_QUADS, numIndices);
	modelBatch1->CopyVertexData3f(vVerts);
	modelBatch1->CopyColorData4f(vColors);
	modelBatch1->End();

	//model1 load batch
	model1->setBatch(modelBatch1);

	//modelBatch2->Begin(GL_TRIANGLES, 3);
	modelBatch2->Begin(GL_QUADS, numIndices);
	modelBatch2->CopyVertexData3f(vVerts);
	modelBatch2->CopyColorData4f(vColors);
	modelBatch2->End();

	//model2 load batch
	model2->setBatch(modelBatch2);
}

void myInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	shaderManager.InitializeStockShaders();

	glEnable(GL_DEPTH_TEST);

	//Projection
	mainView->viewFrustum->SetPerspective(35.0f, (float)(width / height), 1.0f, 1000.0f);

	//rotateAroundModelZaxis = 0;
	//rotateAroundViewZaxis = 0;
	setupWorld();

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
		//model1->localTransform.setPosition(viewPosition);
		model1->localTransform.setPosition(model1Position);

		//model1 rotation
	M3DVector3f rotateModel1;
	rotateModel1[0] = 0;
	rotateModel1[1] = 0;
	rotateModel1[2] = 0;
		//model1->localTransform.setRotation(rotateView);
		model1->localTransform.setRotation(rotateModel1);
	}

	{//Model2 setup
		//model2 position
		M3DVector3f model2Position;
		model2Position[0] = 0;//X, left/right
		model2Position[1] = 0.5f;//Y, up/down
		model2Position[2] = -6.0f;//Z, in/out
		//model2->localTransform.setPosition(viewPosition);
		model2->localTransform.setPosition(model2Position);

		//model2 rotation
		M3DVector3f rotateModel2;
	rotateModel2[0] = 0;
	rotateModel2[1] = 0;
	rotateModel2[2] = 0;
		//model2->localTransform.setRotation(rotateView);
		model2->localTransform.setRotation(rotateModel2);

		//model2 scale
	model2->localTransform.setScale(2.0f);
	}
}

void ResetView()
{
	//HACK: hack method
	myInit();
}

void RenderScene(void)
{
	//Swap Colors
	GLfloat vColor[]=  { 1.0f, 1.0f, 1.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//TODO: Depth Buffer
	//Draw all models
	model1->Draw(mainView, shaderManager, mvpMatrix);
	model2->Draw(mainView, shaderManager, mvpMatrix);

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
		mainView->localTransform.moveUp(viewSpeed);
	}
	if((key == 'F')||(key == 'f'))//view fall
	{
		mainView->localTransform.moveUp(-viewSpeed);
	}

	//Rotate view
	float viewSpinSpeed = 10.0f;
	if ((key == 'Q')||(key == 'q'))//rotate left
	{
		mainView->localTransform.rotateTurnRight(-viewSpinSpeed);
	}

	if ((key == 'E')||(key == 'e'))//rotate right
	{
		mainView->localTransform.rotateTurnRight(viewSpinSpeed);
	}

	//Move model2
	float model2Speed = 1;
	if((key == 'L')||(key == 'l'))
	{
		//model position X up
		model2->localTransform.position.x += model2Speed;
	}
	if((key == 'J')||(key == 'j'))//model position X down
	{
		model2->localTransform.position.x -= model2Speed;
	}
	if((key == 'I')||(key == 'i'))//model position Y up
	{
		model2->localTransform.position.y += model2Speed;
	}
	if((key == 'K')||(key == 'k'))//model position Y down
	{
		model2->localTransform.position.y -= model2Speed;
	}
	if((key == 'O')||(key == 'o'))//model position Z up
	{
		model2->localTransform.position.z += model2Speed;
	}
	if((key == 'U')||(key == 'u'))
	{
		//model position Z down
		model2->localTransform.position.z -= model2Speed;
	}

	//Rotate models
	float modelSpinSpeed = 10.0f;
	if ((key == 'V')||(key == 'v'))
	{
		model1->localTransform.rotateTurnRight(-modelSpinSpeed);
	}
	if ((key == 'C')||(key=='c'))
	{
		model1->localTransform.rotateTurnRight(modelSpinSpeed);
	}
	if ((key == 'Z')||(key == 'z'))//||(key == 122))
	{
		model2->localTransform.rotateTurnRight(-modelSpinSpeed);
	}
	if ((key == 'X')||(key=='x'))//||(key == 120))
	{
		model2->localTransform.rotateTurnRight(modelSpinSpeed);
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
	mainView = new CameraView();
	model1 = new Object3D();
	model2 = new Object3D();
}
	//HACK:
#include <stdlib.h>
#include <iostream>
#include <string>
void Update()
{
	//physics
	//
	glutPostRedisplay();

	//Debug_OpenGL::outputText(Vector3f(1, 1), nah::Color(0.5f, 0.5f, 0.5f), GLUT_BITMAP_8_BY_13, text);
	//HACK: font doesn't load, placeholder
	std::system("cls");
	std::cout << "Camera: \n" + mainView->localTransform.toStringMultiLine(true, true, false) << std::endl;
	std::cout << "Model1: \n" + model1->localTransform.toStringMultiLine() << std::endl;
	std::cout << "Model2: \n" + model2->localTransform.toStringMultiLine() << std::endl;
}
void cleanup()
{
	delete mainView;
	delete model1;
	delete model2;
}

int main(int argc, char* argv[])
{
	create();

	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA| GLUT_DEPTH | GLUT_STENCIL | GLUT_ALPHA);

	width = 800;
	height = 600;
	glutInitWindowSize(800,600);

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
