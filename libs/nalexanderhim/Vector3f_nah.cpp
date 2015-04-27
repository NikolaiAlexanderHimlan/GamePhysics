/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Vector3f.h"
#include "SpaceDefines.h"
#include "Rotation3D.h"
#include "RotationMath.h"
#include "GeneralMath.h"

//Static Values
const float Vector3f::DEFAULT_VAL = 0.0f;//[NAH]
const Vector3f Vector3f::defaultVect = Vector3f(DV, DV, DV);//[NAH]

Vector3f Vector3f::ClampMax(VectParam clampThis, VectParam clampMax)
{
	return Vector3f(
		nah::Clamp(clampThis.x, clampMax.x),
		nah::Clamp(clampThis.y, clampMax.y),
		nah::Clamp(clampThis.z, clampMax.z));
}
Vector3f Vector3f::ClampMaxKeepSign(VectParam clampThis, VectParam clampMax)
{
	return Vector3f(
		nah::ClampKeepSign(clampThis.x, std::abs(clampMax.x)),
		nah::ClampKeepSign(clampThis.y, std::abs(clampMax.y)),
		nah::ClampKeepSign(clampThis.z, std::abs(clampMax.z)));
}

Vector3f Vector3f::asRad() const { return Vector3f(nah::DegToRad(x), nah::DegToRad(y), nah::DegToRad(z));	};

//implementation found here: http://stackoverflow.com/a/8208951
const Rotation3D Vector3f::calcLookAtAngle(VectParam eye, VectParam lookAt)
{
	Rotation3D lookRotation;

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

VectParam Vector3f::AxisNormal(Axis toNorm)
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
