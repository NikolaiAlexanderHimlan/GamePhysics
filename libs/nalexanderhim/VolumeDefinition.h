#ifndef VolumeDefinition_h__
#define VolumeDefinition_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ccmccooeyWrapper.h"
#include "SpaceDefines.h"

struct VolumeDefinition
{
	virtual Vector3f HighestPoint(VectParam volumePos = Vector3f::zero, Axis upAxis = UP) const=0;
	inline Vector3f LowestPoint(VectParam volumePos = Vector3f::zero, Axis upAxis = UP) const
	{ return HighestPoint(volumePos, upAxis) * -1.0f; };
};

struct SphereVolume
	: public VolumeDefinition
{
	float radius = 0.0f;
	inline Vector3f HighestPoint(const Vector3f& volumePos = Vector3f::zero, Axis upAxis = UP) const
	{
		Vector3f highPoint;

		switch (upAxis)
		{
		case X:
			highPoint = Vector3f(radius, 0.0f, 0.0f);
			break;
		case Y:
			highPoint = Vector3f(0.0f, radius, 0.0f);
			break;
		case Z:
			highPoint = Vector3f(0.0f, 0.0f, radius);
			break;
		default:
			throw std::logic_error("Invalid Axis - SphereVolume - LowestPoint!");
			break;
		}

		return volumePos + highPoint;
	};
};

#endif // VolumeDefinition_h__
