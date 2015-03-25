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

#endif // VolumeDefinition_h__
