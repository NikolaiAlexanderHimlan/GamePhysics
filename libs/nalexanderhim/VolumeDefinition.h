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
#include "MathDefines.h"

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

	SphereVolume(float sphereRadius) : radius(sphereRadius) {};

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

struct CubeVolume
	: public VolumeDefinition
{
	float width, length, height;

	CubeVolume(float cubeWidth, float cubeLength, float cubeHeight)
		: width(cubeWidth), length(cubeLength), height(cubeHeight) {};

	inline Vector3f VolumeVector() const { return Vector3f(width, height, length);	}

	inline Vector3f HighestPoint(VectParam volumePos /* = Vector3f::zero */, Axis upAxis /* = UP */) const
	{
		Vector3f highPoint;

		switch (upAxis)
		{
		case X:
			highPoint.x = width;
			break;
		case Y:
			highPoint.y = height;
			break;
		case Z:
			highPoint.z = length;
			break;
		default:
			throw std::logic_error("Invalid Axis - CubeVolume - LowestPoint!");
			break;
		}

		return volumePos + highPoint;
	};
};
#endif // VolumeDefinition_h__
