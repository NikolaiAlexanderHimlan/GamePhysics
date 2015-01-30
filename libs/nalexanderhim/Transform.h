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

	//Degrees
	inline float getPitch() const { return rotation.x;	};
	inline float getYaw() const { return rotation.y;	};
	inline float getRoll() const { return rotation.z;	};

	Vector3f getForwardVector() const;
	Vector3f getUpVector() const;
	Vector3f getRightVector(char axis) const;//more efficient, only calculates the requested axes of the vector
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
