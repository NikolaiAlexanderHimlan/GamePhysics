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
#include "RotationMath.h"

class Transform
{
public:
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

public:
	Transform(const Vector3f& init_position = Vector3f::zero, const Vector3f& init_rotation = Vector3f::zero, const Vector3f& init_scale = Vector3f::one);
	~Transform();

	//Rotation
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

	//more efficient, only calculates the requested axes of the vector
	Vector3f getForwardVector(char axis) const;
	Vector3f getUpVector(char axis) const;
	Vector3f getRightVector(char axis) const;
	//get all axes
	inline Vector3f getForwardVector() const { return getForwardVector('a');	};
	inline Vector3f getUpVector() const { return getUpVector('a');	};
	inline Vector3f getRightVector() const { return getRightVector('a');	};

	void getRenderMatrix(M3DMatrix44f& outResult) const;

	inline void setPitch(float degrees) { rotation.x = degrees;	};
	inline void setYaw(float degrees) { rotation.y = degrees;	};
	inline void setRoll(float degrees) { rotation.z = degrees;	};

	void rotatePitch(float degrees);
	void rotateYaw(float degrees);
	void rotateRoll(float degrees);
	inline void rotateRollRight(float degrees) { return rotateRoll(degrees);	};
	inline void rotateTurnRight(float degrees) { return rotateYaw(degrees);	};
	inline void rotateTurnUp(float degrees) { return rotatePitch(degrees);	};

	void lookAt(const Transform* worldTransform);
	void setTarget(const Transform* worldTransform);

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

};

#endif
