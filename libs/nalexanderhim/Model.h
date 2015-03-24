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
#include "SpaceDefines.h"

class Model
{
private:
	float mMaxDistVert;
	float mMinDistVert;

protected:
	BatchData* mModelBatch;

public:
	Model() {};
	Model(BatchData* batch)
	{
		setBatch(batch);
	}
	virtual ~Model();
	
	//Getters
	float getMaxDistVert() const { return mMaxDistVert;	};
	float getMinDistVert() const { return mMinDistVert;	};

	//GL Batch
	void setBatch(BatchData* batch, float maxDistVert =0.0f, float minDistVert =0.0f);
	//TODO: move functionality to static functions which return the batch
	void setBatchPlane(float width, float length, Axis facing = Y, bool inv = false /*Face along the negative edge of the axis*/);
	//TODO: triangle function which takes 3 vectors
	void setBatchTriangle(float distUp, float distLeft, float distRight /*TODO: optional color parameters*/);//distance of each corner from the center
	void setBatchCube(float xDimension, float yDimension, float zDimension /*TODO: optional color parameters*/);
	//HACK: currently has 2 infinite points, problem resolved in DirectX version but not here
	void setBatchSphere(float radius , int numSegments = 8 /*TODO: optional color parameters*/);

	//Calculations
};

#endif
