#include <GLTools.h>
#include <GLShaderManager.h>
#include <GL/glut.h>
#include <GLFrustum.h>

GLBatch			triangleBatch;
GLShaderManager	shaderManager;
GLfloat			offset;
GLfloat			counter;
GLboolean		bDoSomething;
M3DMatrix44f	mvpMatrix;
GLFrustum		viewFrustum;
GLint			width, height;
//GLfloat			rotateAroundModelZaxis;
//GLfloat			rotateAroundViewZaxis;

M3DVector3f viewPosition;
M3DVector3f model1Position;
M3DVector3f model2Position;
M3DVector3f rotateView;
M3DVector3f rotateModel1;
M3DVector3f rotateModel2;

void ChangeSize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0,0,width, height);


	viewFrustum.SetPerspective(35.0f, (float)(width/height), 1.0f, 1000.0f);

}

void setupWorld()
{
	GLfloat			vVerts[] = {-0.5f, 0.0f, 0.0f, 
								0.5f, 0.0f, 0.0f, 
								0.0f, 0.5f, 0.0f};

	GLfloat			vColors[] = {1.0f, 0.0f, 0.0f, 1.0f, 
								0.0f, 1.0f, 0.0f, 1.0f, 
								0.0f, 0.0f, 1.0f, 1.0f};

	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.CopyColorData4f(vColors);
	triangleBatch.End();
}

void myInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	shaderManager.InitializeStockShaders();

	//Projection
	viewFrustum.SetPerspective(35.0f, (float)(width/height), 1.0f, 1000.0f);

	//rotateAroundModelZaxis = 0;
	//rotateAroundViewZaxis = 0;
	setupWorld();

	//position
	viewPosition[0] = 0;//left/right
	viewPosition[1] = -2;//up/down
	viewPosition[2] = -10;//towards/away
	model1Position[0] = 0;//X, left/right
	model1Position[1] = 1;//Y, up/down
	model1Position[2] = 0;//Z, in/out
	model2Position[0] = 0;//X, left/right
	model2Position[1] = 1;//Y, up/down
	model2Position[2] = 0.5f;//Z, in/out

	//rotation
	rotateView[0] = 0;
	rotateView[1] = 0;
	rotateView[2] = 0;
	rotateModel1[0] = 0;
	rotateModel1[1] = 0;
	rotateModel1[2] = 0;
	rotateModel2[0] = 0;
	rotateModel2[1] = 0;
	rotateModel2[2] = 0;
}

void ResetView()
{
	myInit();
}

void RenderScene(void)
{
	//Swap Colors
	GLfloat vColor[]=  { 1.0f, 1.0f, 1.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	M3DMatrix44f mModel1, mModel2, mView, mModelView;
	M3DMatrix44f mScale, mRotateX, mRotateY, mRotateZ, mRotateResult, mTranslate;

	//Model
	m3dLoadIdentity44(mModel1);
	m3dRotationMatrix44(mRotateZ, (float)m3dDegToRad(rotateModel1[2]), 0.0f, 0.0f, 1.0f);
	m3dTranslationMatrix44(mTranslate, model1Position[0], model1Position[1], model1Position[2]);
	m3dScaleMatrix44(mScale, 1.0, 1.0, 1.0);
	m3dMatrixMultiply44(mModel1, mScale, mRotateZ);//TRANSLATE -> ROTATE -> SCALE
	m3dMatrixMultiply44(mModel1, mTranslate, mModel1);


	m3dLoadIdentity44(mModel2);
	m3dRotationMatrix44(mRotateZ, (float)m3dDegToRad(rotateModel2[2]), 0.0f, 1.0f, 1.0f);
	m3dTranslationMatrix44(mTranslate, model2Position[0], model2Position[1], model2Position[2]);
	m3dScaleMatrix44(mScale, 2.0, 2.0, 2.0);
	m3dMatrixMultiply44(mModel2, mScale, mRotateZ);
	m3dMatrixMultiply44(mModel2, mTranslate, mModel2);


	//View
	m3dLoadIdentity44(mView);
	m3dRotationMatrix44(mRotateZ, (float)m3dDegToRad(rotateView[2]), 0.0f, 0.0f, 1.0f);
	m3dRotationMatrix44(mRotateY, (float)m3dDegToRad(rotateView[1]), 0.0f, 1.0f, 0.0f);
	m3dRotationMatrix44(mRotateX, (float)m3dDegToRad(rotateView[0]), 1.0f, 0.0f, 0.0f);
	m3dTranslationMatrix44(mTranslate, viewPosition[0], viewPosition[1], viewPosition[2]);
	m3dMatrixMultiply44(mRotateResult, mRotateX, mRotateY);
	m3dMatrixMultiply44(mRotateResult, mRotateResult, mRotateZ);
	m3dMatrixMultiply44(mView, mRotateResult, mTranslate);

	//TODO: create batch object (model), contains translation and rotation as well as batch information
	//TODO: create function to draw models in order based on z-axis position (depth)
	//ModelView
	m3dMatrixMultiply44(mModelView, mView, mModel1);

	//ModelViewProjection
	m3dMatrixMultiply44(mvpMatrix, viewFrustum.GetProjectionMatrix(), mModelView);

	shaderManager.UseStockShader(GLT_SHADER_SHADED, mvpMatrix);
	triangleBatch.Draw();


	//ModelView
	m3dMatrixMultiply44(mModelView, mView, mModel2);
	//ModelViewProjection
	m3dMatrixMultiply44(mvpMatrix, viewFrustum.GetProjectionMatrix(), mModelView);

	shaderManager.UseStockShader(GLT_SHADER_SHADED, mvpMatrix);
//	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE, mvpMatrix, vColor, texture);

	triangleBatch.Draw();

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
		viewPosition[2] += viewSpeed;
	}
	if((key == 'A')||(key == 'a'))//view move left
	{
		viewPosition[0] += viewSpeed;
	}
	if((key == 'S')||(key == 's'))//view move backward
	{
		viewPosition[2] -= viewSpeed;
	}
	if((key == 'D')||(key == 'd'))//view move right
	{
		viewPosition[0] -= viewSpeed;
	}
	if((key == 'R')||(key == 'r'))//view rise
	{
		viewPosition[1] -= viewSpeed;
	}
	if((key == 'F')||(key == 'f'))//view fall
	{
		viewPosition[1] += viewSpeed;
	}

	//Rotate view
	float viewSpinSpeed = 10.0f;
	if ((key == 'Q')||(key == 'q'))//rotate left
	{
		rotateView[2]-=viewSpinSpeed;
	}

	if ((key == 'E')||(key == 'e'))//rotate right
	{
		rotateView[2]+=viewSpinSpeed;
	}

	//Move model2
	float model2Speed = 1;
	if((key == 'U')||(key == 'u'))//model position X up
	{
		model2Position[0] += model2Speed;
	}
	if((key == 'J')||(key == 'j'))//model position X down
	{
		model2Position[0] -= model2Speed;
	}
	if((key == 'I')||(key == 'i'))//model position Y up
	{
		model2Position[1] += model2Speed;
	}
	if((key == 'K')||(key == 'k'))//model position Y down
	{
		model2Position[1] -= model2Speed;
	}
	if((key == 'O')||(key == 'o'))//model position Z up
	{
		model2Position[2] += model2Speed;
	}
	if((key == 'L')||(key == 'l'))//model position Z down
	{
		model2Position[2] -= model2Speed;
	}

	//Rotate models
	float modelSpinSpeed = 10.0f;
	if ((key == 'V')||(key == 'v'))
	{
		rotateModel1[2] -= modelSpinSpeed;
	}
	if ((key == 'C')||(key=='c'))
	{
		rotateModel1[2] += modelSpinSpeed;
	}
	if ((key == 'Z')||(key == 'z'))//||(key == 122))
	{
		rotateModel2[2] -= modelSpinSpeed;
	}
	if ((key == 'X')||(key=='x'))//||(key == 120))
	{
		rotateModel2[2] += modelSpinSpeed;
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
		rotateView[1]-=viewTurnSpeed;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		rotateView[1]+=viewTurnSpeed;
	}
	if(key==GLUT_KEY_UP)
	{
		rotateView[0]-=viewTurnSpeed;
	}
	if(key==GLUT_KEY_DOWN)
	{
		rotateView[0]+=viewTurnSpeed;
	}
}

void Update()
{
	//physics
	//
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA| GLUT_DEPTH | GLUT_STENCIL);

	width = 800;
	height = 600;
	glutInitWindowSize(800,600);

	glutCreateWindow("Triangle");
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
	return 0;
}
