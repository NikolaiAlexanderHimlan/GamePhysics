/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Vector3f.h"
#include "SpaceDefines.h"
#include "Rotation.h"

#include "RotationMath.h"
using namespace nah;
Vector3f Vector3f::asRad() const { return Vector3f(DegToRad(x), DegToRad(y), DegToRad(z)); };

//implementation found here: http://stackoverflow.com/a/8208951
Vector3f Vector3f::getLookAtAngle(const Vector3f& eye, const Vector3f& lookAt)
{
	Vector3f lookRotation;

	/*TODO: implement ACTUAL look at
	#if _MSC_VER
	#pragma warning ("Warning : LookAt is NOT implemented!")
	#endif
	LOG_WARNING("LookAt is NOT implemented!");
	//*/

	Vector3f diff = Difference(lookAt, eye);
	float xzdistance = sqrt(diff.x * diff.x + diff.z * diff.z);
	lookRotation.x = (-atan2(diff.y, xzdistance)); // rotation around x
	lookRotation.y = (atan2(diff.x, diff.z)); // rotation around y
	lookRotation.z = (0); // rotation around z

	return lookRotation;
}

const Vector3f& Vector3f::AxisNormal(Axis toNorm)
{
	switch (toNorm)
	{
	case X:
		return Vector3f::unitX;
		break;
	case Y:
		return Vector3f::unitY;
		break;
	case Z:
		return Vector3f::unitZ;
		break;
	default:
		AXIS_ERROR("AxisNormal");
		break;
	}
}
