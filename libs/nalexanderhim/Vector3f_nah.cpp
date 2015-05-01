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

Vector3f Vector3f::Subtract_NonZero(Vector3f lhs, VectParam rhs, bool keepLeftOnZero /*= false*/, bool keepRightOnZero /*= false*/)
{
	if (lhs.x != 0 && rhs.x != 0)
		lhs.x -= rhs.x;
	else if (!keepLeftOnZero)
		lhs.x = 0;
	else if (keepRightOnZero)
		lhs.x = rhs.x;

	if (lhs.y != 0 && rhs.y != 0)
		lhs.y -= rhs.y;
	else if (!keepLeftOnZero)
		lhs.y = 0;
	else if (keepRightOnZero)
		lhs.y = rhs.y;

	if (lhs.z != 0 && rhs.z != 0)
		lhs.z -= rhs.z;
	else if (!keepLeftOnZero)
		lhs.z = 0;
	else if (keepRightOnZero)
		lhs.z = rhs.z;

	return lhs;
}

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
