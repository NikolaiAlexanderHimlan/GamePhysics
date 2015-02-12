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
#include "ModelData.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <GLTools.h>
#include <GL/glut.h>

#include "ccmccooeyWrapper.h"
#include "Color.h"
#include "RotationMath.h"

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
		//index list of how the vectors connect together (every 3 indexes is a triangle)
		int vectIndx[24] = { 
			1, 2, 3, 4,
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

void Model::setBatchSphere(float radius, int numSegments /*= 8 /*TODO: optional color parameters*/)
{
	GLBatch* modelBatch = new GLBatch();

	int numVerts;
	int numIndexes;

	/*generate sphere model batch, custom method
	int vertsPerSegment = (numSegments * 2);//number of vertices on each segment of the sphere
	numVerts = numSegments * vertsPerSegment;//total number of unique vertices
	numIndexes = vertsPerSegment * numSegments;//number of vertex values in the final result
	GLfloat* vVerts = new GLfloat[numIndexes * 3];//number of indices times 3 points in a vertex
	GLfloat* vColors = new GLfloat[numIndexes * 4];//number of indices times number of values per color
	{
		//index buffer, min value should be 1, max value should be numVerts
		int* vectIndx = new int[numIndexes];
		for (int i = 0; i < numIndexes; i++)
		{
			vectIndx[i] = i+1;//HACK: connect each vertex to the next one
		}
		//vectIndx[numIndexes - 1] = 1;//wrap around
		//vectIndx[3] = 1;

		Vector3f* vectVerts = new Vector3f[numVerts];//array of all unique vertexes
		int horzIndex;//indicates where to start the vertical ring
		float radsPerSegmentHorz = nah::DegToRad(360.0f / numSegments);
		float radsPerSegmentVert = nah::DegToRad(360.0f / vertsPerSegment);
		float radiusPerSegment = radius / numSegments;
		float radiusHorz, radiusVert;//radius at each segment, are inversely proportional
		float thetaHorz, thetaVert;//the angle at each segment
		float x, y, z;
		//TODO: subtract 2 from numSegments and use a single point for the farthest vertexes
		for (int i = 0; i < numSegments; i++)//horizontal ring (from bottom)
		{
			horzIndex = i * numSegments;
			thetaHorz = i * radsPerSegmentHorz;
			radiusHorz = (radius*0.5f) - (i*radiusPerSegment) - radiusPerSegment*0.5f;//radius/2 to -radius/2
			radiusVert = radius - abs(radiusHorz);
			for (int j = 0; j < vertsPerSegment; j++)//vertical ring (from left)
			{
				thetaVert = j * radsPerSegmentVert;

				x = radiusHorz;
				//x = cos(thetaHorz) * radiusHorz;
				//x = sin(thetaHorz) * radiusHorz;
				y = sin(thetaVert) * radiusVert;
				//y = cos(thetaHorz) * radiusHorz;
				z = cos(thetaVert) * radiusVert;

				vectVerts[j + horzIndex] = Vector3f(x,y,z);
			}
		}

		nah::Color* colorVerts = new nah::Color[numVerts];//array of colors for each vertex
		/*
		for (int k = 0; k < numVerts / 8; k++)
		{
			colorVerts[0 + k] = nah::Color::Red;
			colorVerts[1 + k] = nah::Color::Aquamarine;
			colorVerts[2 + k] = nah::Color::Blue;
			colorVerts[3 + k] = nah::Color::DarkBlue;
			colorVerts[4 + k] = nah::Color::DarkGreen;
			colorVerts[5 + k] = nah::Color::DarkRed;
			colorVerts[6 + k] = nah::Color::Green;
			colorVerts[7 + k] = nah::Color::Orange;
		}
		* /
		for (int k = 0; k < numVerts; k++)
		{
			colorVerts[k] = nah::Color::RandomColor();
		}
	}
	//*/

	//*Solution 1: http://stackoverflow.com/a/13846592
	float const R = (float)(1. / (float)(numSegments - 1));
	float const S = (float)(1. / (float)(numSegments - 1));

	numVerts = (numSegments) * (numSegments);
	numIndexes = numVerts * 6;//each vertex generated 6 indices in the example
	GLfloat* vVerts = new GLfloat[numIndexes * 3];//number of indices times 3 points in a vertex
	GLfloat* vColors = new GLfloat[numIndexes * 4];//number of indices times number of values per color
	int* vectIndx = new int[numIndexes];//index buffer (used for vertexes and colors)

	Vector3f* vectVerts = new Vector3f[numVerts];//array of all unique vertexes
	int vertCounter = 0;
	int indexCounter = 0;
	float x, y, z;
	for (int r = 0; r < numSegments; r++)
	{
		for (int s = 0; s < numSegments; s++)
		{
			x = cosf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);
			y = sinf((float)-M_PI_2 + (float)M_PI * r * R);
			z = sinf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);

			vectVerts[vertCounter++] = Vector3f(x, y, z) * radius;

			//if (r != numSegments-1 && s != numSegments-1)//skip last ring/segment
			{//Generate Index Buffer
				int curRow = r * numSegments;
				int nextRow = (r + 1) * numSegments;

				vectIndx[indexCounter++] = curRow + s;
				vectIndx[indexCounter++] = nextRow + s;
				vectIndx[indexCounter++] = nextRow + (s + 1);

				vectIndx[indexCounter++] = curRow + s;
				vectIndx[indexCounter++] = nextRow + (s + 1);
				vectIndx[indexCounter++] = curRow + (s + 1);
			}
		}
	}
	nah::Color* colorVerts = new nah::Color[numVerts];//array of colors for each vertex
	for (int k = 0; k < numVerts; k++)
	{
		colorVerts[k] = nah::Color::RandomColor();
	}
	//*/

	int counterCounter = 0;
	for (int i = 0; i < numIndexes; i++)
	{
		vVerts[counterCounter++] = vectVerts[vectIndx[i] - 1].x;
		vVerts[counterCounter++] = vectVerts[vectIndx[i] - 1].y;
		vVerts[counterCounter++] = vectVerts[vectIndx[i] - 1].z;
	}
	counterCounter = 0;
	for (int i = 0; i < numIndexes; i++)
	{
		vColors[counterCounter++] = colorVerts[vectIndx[i] - 1].rgbRed();
		vColors[counterCounter++] = colorVerts[vectIndx[i] - 1].rgbGreen();
		vColors[counterCounter++] = colorVerts[vectIndx[i] - 1].rgbBlue();
		vColors[counterCounter++] = colorVerts[vectIndx[i] - 1].rgbAlpha();
	}
	delete[] vectIndx;
	delete[] vectVerts;
	delete[] colorVerts;

	modelBatch->Begin(GL_TRIANGLES, numIndexes);
	modelBatch->CopyVertexData3f(vVerts);
	modelBatch->CopyColorData4f(vColors);
	modelBatch->End();

	delete[] vVerts;
	delete[] vColors;

	//model load batch
	setBatch(modelBatch);
}
