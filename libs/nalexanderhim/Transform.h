/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "M3DTypes.h"

#include "ccmccooeyWrapper.h"
#include "Rotation3D.h"
#include "CodingDefines.h"

class Transform
{
public:
	Vector3f position;
	//TODO: replace rotation with a quaternion
	//CONSIDER: replace with Scale object which is essentially a Vector3fFactor to make division cheaper
	Rotation3D rotation;
	Vector3f scale;

public:
	Transform(REF(Vector3f) init_position = Vector3f::zero, REF(Rotation3D) init_rotation = Rotation3D(Vector3f::zero, true), REF(Vector3f) init_scale = Vector3f::one)
		: position(init_position), rotation(init_rotation), scale(init_scale) {};
	~Transform() {};

	//Getters

	//Properties
	//more efficient, only calculates the requested axes of the vector
	Vector3f getForwardVector(char axis) const;
	Vector3f getUpVector(char axis) const;
	Vector3f getRightVector(char axis) const;
	//get all axes
	inline Vector3f getForwardVector() const { return getForwardVector('a');	};
	inline Vector3f getUpVector() const { return getUpVector('a');	};
	inline Vector3f getRightVector() const { return getRightVector('a');	};

	//Setters
	void setPosition(const M3DVector3f& newPosition);
	void setRotation(REF(M3DVector3f) newRotation, bool setDegrees = true);
	void setScale(float newScale);


	//Modifiers

	//Calculations
	inline const Vector3f calcLookAtRotation(const Vector3f lookHere) const { return Vector3f::calcLookAtAngle(position, lookHere);	}; //calculates the necessary rotation in order to look at a given location from this location
	void calcRenderMatrix(OUT_PARAM(M3DMatrix44f) outResult) const;

	//Actions
	inline void rotateRollRight(float degrees) { return rotateRoll(degrees);	};
	inline void rotateTurnRight(float degrees) { return rotateYaw(degrees);	};
	inline void rotateTurnUp(float degrees) { return rotatePitch(degrees);	};
	inline void moveForward(float amount)	{ position += getForwardVector() * amount;	};
	inline void moveRight(float amount)		{ position += getRightVector() * amount;	};
	inline void moveUp(float amount)			{ position += getUpVector() * amount;	};

	inline void lookAt(const Transform& worldTransform) { rotation = calcLookAtRotation(worldTransform.position).asRad();	};//look at the transform once

	//Type Conversions
	std::string toString(bool pos = true, bool rot = true, bool scl = true) const;
	std::string toStringMultiLine(bool pos = true, bool rot = true, bool scl = true) const;
};

#endif // Transform_h__
