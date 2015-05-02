/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: bonus
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Boundings.h"
#include "MathDefines.h"
#include "GeneralMath.h"

#pragma region Plane Bounds
bool PlaneBounding::CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount /*= nullptr*/, OUT_PARAM(Vector3f) overlapNormal /*= nullptr*/) const
{
	//Generate a vector with the correct location along the normal and otherLocation filling in the remaining data
	//NOTE: the closer to 1 the axis value in normal is, the less relevant otherLocation is
	//TODO: limit the range of wallPoint based on the width and length
	Vector3f wallPoint =
		Vector3f::NormalWeight(boundsLocation, normal)//location of bounds is directly relevant based on the normal
		+ Vector3f::InvertNormalWeight(otherLocation, normal);//other location is inversely relevant based on the normal

	//checkLocation on opposite side from normal
	//TODO: handle impassable
	if (impassable)
	{
		LOGIC_ERR("impassible not implemented - PlanesBounding - Contains");
	}
	return otherBounds.Contains(otherLocation, wallPoint, overlapAmount);
}

bool PlaneBounding::Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount, OUT_PARAM(Vector3f) overlapNormal /*= nullptr*/) const
{
	bool doesContain = false;
	real overlap;

	overlap = Vector3f::DistanceSquared(boundsLocation, checkLocation);

	//checkLocation on opposite side from normal
	//TODO: handle impassable
	if (impassable)
	{
		if (overlap > 0)
			LOGIC_ERR("impassible not implemented - PlanesBounding - Contains");
	}
	else overlap = nah::absInv((float)overlap);//if plane is not "impassable" then there cannot be a positive overlap
	OUT_SET(overlapAmount, nah::sqrtKeepSign((float)overlap))
		return doesContain;
}
#pragma endregion Plane Bounds

#pragma region Sphere Bounds
bool SphereBounding::CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount /*= nullptr*/, OUT_PARAM(Vector3f) overlapNormal /*= nullptr*/) const
{
	//1st, calculate a vector to otherLocation with radius as the length.
	Vector3f vectTo = Vector3f::Distancepoint(boundsLocation, otherLocation, radius);

	//2nd, check if this vector passes the otherLocation, in which case there is definitely a collision
	//if(Vector3f::isBetween(boundsLocation, vectTo, otherLocation)) return true;

	//3rd, check if the other bounds contains the location indicated by the calculated vector
	//return otherBounds.Contains(otherLocation, vectTo);//cannot call directly due to inheritance funnyness, calling Bounding CheckOverlap
	return otherBounds.Contains(otherLocation, vectTo, overlapAmount, overlapNormal);
}

bool SphereBounding::Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount, OUT_PARAM(Vector3f) overlapNormal) const
{
	//check if distance to checkLocation is less than radius, return this as the result
	real overlap = std::powf(radius, 2.0f) - Vector3f::DistanceSquared(boundsLocation, checkLocation);
	OUT_SET(overlapAmount, overlap);
	OUT_SET(overlapNormal, (checkLocation - boundsLocation).getNormalized());
	return overlap > 0;
}
#pragma endregion Sphere Bounds

#pragma region Box Bounds
bool CubeBounding::CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount /*= nullptr*/, OUT_PARAM(Vector3f) overlapNormal /*= nullptr*/) const
{
	Vector3f closePoint = VolumeVector();
	closePoint = Vector3f::Multiply(closePoint,
		Vector3f::DirectionTo(boundsLocation, otherLocation));
	return otherBounds.Contains(otherLocation, closePoint, overlapAmount, overlapNormal);
}

bool CubeBounding::Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount, OUT_PARAM(Vector3f) overlapNormal) const
{
	Vector3f relativePoint = checkLocation - boundsLocation;
	//Vector3f relativePoint = boundsLocation - checkLocation;
	float volumeLength = VolumeVector().Length();
	float relativeLength = relativePoint.Length();
	Vector3f posVolume = boundsLocation + VolumeVector();
	OUT_SET(overlapAmount, Vector3f::Subtract_NonZero(posVolume, (checkLocation)).Length());
	OUT_SET(overlapNormal, Vector3f::MaxToAxis(checkLocation - boundsLocation, true, true))
	return posVolume.GreaterEqual_All((checkLocation));
}
#pragma endregion Box Bounds
