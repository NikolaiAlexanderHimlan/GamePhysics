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

#include "ccmccooeyWrapper.h"

class Transform
{
public:
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

public:
	Transform(const Vector3f& init_position = Vector3f::zero, const Vector3f& init_rotation = Vector3f::zero, const Vector3f& init_scale = Vector3f::one);
	~Transform();

	void getRenderMatrix(M3DMatrix44f& outResult) const;

	std::string toString(bool pos = true, bool rot = true, bool scl = true) const
	{
		std::string textline = "";
		if (pos)
			textline += position.toString() + " | ";
		if (rot)
			textline += rotation.toString() + " | ";
		if (scl)
			textline += scale.toString();
		return textline;
	}
	std::string toStringMultiLine(bool pos = true, bool rot = true, bool scl = true) const
	{
		std::string textline = "";
		if (pos)
			textline += position.toString() + "\n";
		if (rot)
			textline += rotation.toString() + "\n";
		if (scl)
			textline += scale.toString() + "\n";
		return textline;
	}

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
