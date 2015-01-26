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
};

#endif
