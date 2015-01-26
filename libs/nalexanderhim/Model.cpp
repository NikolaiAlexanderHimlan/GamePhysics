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
