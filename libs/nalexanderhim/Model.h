/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _MODEL_H
#define _MODEL_H

#include "Object3D.h"

class Model
	: public Object3D
{
public:
	Model() {};
	Model(const Transform& initialTransform)
		: Object3D(initialTransform)
	{
	}
	~Model();
};

#endif
