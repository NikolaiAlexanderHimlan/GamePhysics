/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Model.h"
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include <GLTools.h>
#include <GL/glut.h>

#include "ccmccooeyWrapper.h"
#include "Color.h"

Model::~Model()
{
	delete mModelBatch;
}

void Model::setBatch(GLBatch* batch)
{
	if (mModelBatch != NULL) delete mModelBatch;

	mModelBatch = batch;

	/*Copy Data - Disabled
	mModelBatch = new BatchData();
	
	GLfloat			vVerts[] = { -0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f };

	GLfloat			vColors[] = { 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f };

	mModelBatch->Begin(GL_TRIANGLES, 3);
	mModelBatch->CopyVertexData3f(vVerts);
	mModelBatch->CopyColorData4f(vColors);
	mModelBatch->End();
	*/
}

void Model::setBatchTriangle(float distUp, float distLeft, float distRight)
{
	GLBatch* modelBatch = new GLBatch();

	//*generate triangle model batch
	GLfloat			vVerts[] = {-distLeft, 0.0f, 0.0f, 
								distRight, 0.0f, 0.0f, 
								0.0f, distUp, 0.0f};

	GLfloat			vColors[] = {1.0f, 0.0f, 0.0f, 1.0f, 
								0.0f, 1.0f, 0.0f, 1.0f, 
								0.0f, 0.0f, 1.0f, 1.0f};
	//*/

	modelBatch->Begin(GL_TRIANGLES, 3);
	modelBatch->CopyVertexData3f(vVerts);
	modelBatch->CopyColorData4f(vColors);
	modelBatch->End();

	//model load batch
	setBatch(modelBatch);
}

void Model::setBatchCube(float xDimension, float yDimension, float zDimension)
{
	GLBatch* modelBatch = new GLBatch();

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
			float x = xDimension, y = yDimension, z = zDimension;
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

	modelBatch->Begin(GL_QUADS, numIndices);
	modelBatch->CopyVertexData3f(vVerts);
	modelBatch->CopyColorData4f(vColors);
	modelBatch->End();

	//model load batch
	setBatch(modelBatch);
}
