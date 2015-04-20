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
typedef Vector3f Rotation3D;/*2 variations of Rotation implementations [Comment this line to switch]
class Rotation3D
	: public Vector3f
{
public:
	bool isDegrees = true;

	Rotation3D(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f) : Vector3f(pitch, yaw, roll) {};
	explicit Rotation3D(const Vector3f& fromVec3) : Vector3f(fromVec3) {}

	//Properties
	Rotation3D asRad() const;
	Rotation3D asDeg() const;

	//Modifiers
	void setRad(const Rotation3D& radians);
	void setDeg(const Rotation3D& degrees);

	//Operators
	Rotation3D& operator =(const Rotation3D& rhs);
	//Rotation& operator =(const Vector3f& rhs);
};
//move to header
#include "RotationMath.h"
using namespace nah;
Rotation3D Rotation3D::asRad() const { return !isDegrees ? *this : Rotation3D(DegToRad(x), DegToRad(y), DegToRad(z));	};
Rotation3D Rotation3D::asDeg() const { return isDegrees ? *this : Rotation3D(RadToDeg(x), RadToDeg(y), RadToDeg(z));	};
*/
#endif // Rotation_h__
