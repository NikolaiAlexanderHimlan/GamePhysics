#ifndef Rotation_h__
#define Rotation_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ccmccooeyWrapper.h"
/*
class Rotation
	: public Vector3f
{
public:
	bool isDegrees = true;

	Rotation(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f) : Vector3f(pitch, yaw, roll) {};
	explicit Rotation(const Vector3f& fromVec3) : Vector3f(fromVec3) {}

	//Properties
	Rotation asRad() const;
	Rotation asDeg() const;

	//Modifiers
	void setRad(const Rotation& radians);
	void setDeg(const Rotation& degrees);

	//Operators
	Rotation& operator =(const Rotation& rhs);
	//Rotation& operator =(const Vector3f& rhs);
};
//move to header
#include "RotationMath.h"
using namespace nah;
Rotation Rotation::asRad() const { return !isDegrees ? *this : Rotation(DegToRad(x), DegToRad(y), DegToRad(z));	};
Rotation Rotation::asDeg() const { return isDegrees ? *this : Rotation(RadToDeg(x), RadToDeg(y), RadToDeg(z));	};
*/
#endif // Rotation_h__
