/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <math3d.h>

//#include <Vector3f.h>
#include "..\ccmccooey\Vector3f.h"

class Transform
{
public:
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

public:
	Transform(const Vector3f& init_position = Vector3f::zero, const Vector3f& init_rotation = Vector3f::zero, const Vector3f& init_scale = Vector3f::one);
	~Transform();

	void getRenderMatrix(M3DMatrix44f& outResult);

	void setPosition(const M3DVector3f& newPosition);
	void setRotation(const M3DVector3f& newRotation);
	void setScale(float newScale);

	void moveForward(float amount);
	void moveRight(float amount);
	void moveUp(float amount);

	void rotateRollRight(float amount);
	void rotateTurnRight(float amount);
	void rotateTurnUp(float amount);
};

#endif
