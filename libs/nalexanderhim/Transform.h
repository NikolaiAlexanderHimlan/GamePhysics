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
//TODO: NOTE: Professor does not like including RotationMath here in the header
#include "RotationMath.h"

class Transform
{
public:
	Vector3f position;
	//TODO: replace rotation with a quaternion
	Vector3f rotation;//degrees
	//Rotation rotation;//degrees
	//CONSIDER: replace with Scale object which is essentially a Vector3fFactor to make division cheaper
	Vector3f scale;

public:
	Transform(const Vector3f& init_position = Vector3f::zero, const Vector3f& init_rotation = Vector3f::zero, const Vector3f& init_scale = Vector3f::one);
	~Transform();

	//Getters
	//Named Rotations
	inline float getPitch(bool degrees) const
	{
		if (degrees)
			return getPitchDeg();
		else
			return getPitchRad();
	};
	inline float getYaw(bool degrees) const
	{
		if (degrees)
			return getYawDeg();
		else
			return getYawRad();
	};
	inline float getRoll(bool degrees) const
	{
		if (degrees)
			return getRollDeg();
		else
			return getRollRad();
	};
	//Degrees
	inline float getPitchDeg() const { return rotation.x;	};
	inline float getYawDeg() const { return rotation.y;	};
	inline float getRollDeg() const { return rotation.z;	};
	//Radians
	inline float getPitchRad() const { return nah::DegreesToRadians(getPitchDeg());	};
	inline float getYawRad() const { return nah::DegreesToRadians(getYawDeg());	};
	inline float getRollRad() const { return nah::DegreesToRadians(getRollDeg());	};

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
	void setRotation(const M3DVector3f& newRotation);
	void setScale(float newScale);

	inline void setPitch(float degrees) { rotation.x = degrees;	};
	inline void setYaw(float degrees) { rotation.y = degrees;	};
	inline void setRoll(float degrees) { rotation.z = degrees;	};
	inline void setPitchRad(float radians);
	inline void setYawRad(float radians);
	inline void setRollRad(float radians);

	//Modifiers
	float addPitchDeg(float degrees);
	float addYawDeg(float degrees);
	float addRoll(float degrees);
	float addPitchRad(float radians);
	float addYawRad(float radians);
	float addRollRad(float radians);

	//Calculations
	inline const Vector3f calcLookAtRotation(const Vector3f lookHere) const { return Vector3f::calcLookAtAngle(position, lookHere);	}; //calculates the necessary rotation in order to look at a given location from this location
	void calcRenderMatrix(OUT_PARAM(M3DMatrix44f) outResult) const;

	//Actions
	void moveForward(float amount);
	void moveRight(float amount);
	void moveUp(float amount);

	void rotatePitch(float degrees);
	void rotateYaw(float degrees);
	void rotateRoll(float degrees);
	inline void rotateRollRight(float degrees) { return rotateRoll(degrees);	};
	inline void rotateTurnRight(float degrees) { return rotateYaw(degrees);	};
	inline void rotateTurnUp(float degrees) { return rotatePitch(degrees);	};

	inline void lookAt(const Transform& worldTransform) { rotation = calcLookAtRotation(worldTransform.position).asRad();	};//look at the transform once

	//Type Conversions
	std::string toString(bool pos = true, bool rot = true, bool scl = true) const;
	std::string toStringMultiLine(bool pos = true, bool rot = true, bool scl = true) const;
};

#endif
