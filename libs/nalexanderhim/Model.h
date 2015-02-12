/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _MODEL_H
#define _MODEL_H

#ifdef GLTOOLS
#include <GLBatch.h>//TODO: try to move the include to the source file
#define BatchData GLBatch
//class GLBatch;
//typedef GLBatch BatchData;
#endif

class Model
{
protected:
	BatchData* mModelBatch;
public:
	Model() {};
	Model(BatchData* batch)
	{
		setBatch(batch);
	}
	~Model();

	void setBatch(BatchData* batch);
	//TODO: move functionality to static functions which return the batch
	//TODO: triangle function which takes 3 vectors
	void setBatchTriangle(float distUp, float distLeft, float distRight /*TODO: optional color parameters*/);//distance of each corner from the center
	void setBatchCube(float xDimension, float yDimension, float zDimension /*TODO: optional color parameters*/);
	//HACK: currently has 2 infinite points, problem resolved in DirectX version but not here
	void setBatchSphere(float radius , int numSegments = 8 /*TODO: optional color parameters*/);
};

#endif
