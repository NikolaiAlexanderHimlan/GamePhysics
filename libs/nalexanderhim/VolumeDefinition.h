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
#include "CodingDefines.h"
#include "MathDefines.h"

struct VolumeDefinition
{
	virtual Vector3f NearestPoint(REF(Vector3f) toPos, REF(Vector3f) volumePos = Vector3f::zero, OUT_PARAM(real) distanceToPos = nullptr) const = 0;
	virtual Vector3f HighestPoint(VectParam volumePos = Vector3f::zero, Axis upAxis = UP) const=0;
	inline Vector3f LowestPoint(VectParam volumePos = Vector3f::zero, Axis upAxis = UP) const
	{ return HighestPoint(volumePos, upAxis) * -1.0f;	};
};

struct SphereVolume
	: public VolumeDefinition
{
	float radius = 0.0f;

	SphereVolume(float sphereRadius) : radius(sphereRadius) {};

	virtual Vector3f NearestPoint(REF(Vector3f) toPos, REF(Vector3f) volumePos /* = Vector3f::zero */, OUT_PARAM(real) distanceToPos /* = nullptr */) const
	{
		Vector3f nearVect = Vector3f::Distancepoint(volumePos, toPos, radius);
		OUT_SET(distanceToPos, (nearVect - volumePos).Length())
		return nearVect;
	};

	inline Vector3f HighestPoint(REF(Vector3f) volumePos = Vector3f::zero, Axis upAxis = UP) const
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
		};

		return volumePos + highPoint;
	};
};

struct CubeVolume
	: public VolumeDefinition
{
	float width, length, height;

	CubeVolume(float cubeWidth, float cubeLength, float cubeHeight)
		: width(cubeWidth), length(cubeLength), height(cubeHeight) {};

	inline Vector3f VolumeVector() const { return Vector3f(width, height, length);	};

	inline Vector3f NearestPoint(REF(Vector3f) toPos, REF(Vector3f) volumePos /* = Vector3f::zero */, OUT_PARAM(real) distanceToPos /* = nullptr */) const
	{
		return Vector3f::ClampMaxKeepSign(
			Vector3f::Difference(volumePos, toPos), VolumeVector());
	};

	inline Vector3f HighestPoint(VectParam volumePos /* = Vector3f::zero */, Axis upAxis /* = UP */) const
	{
		Vector3f highPoint;

		switch (upAxis)
		{
		case X:
			highPoint.x = width * 0.5f;
			break;
		case Y:
			highPoint.y = height * 0.5f;//from center
			break;
		case Z:
			highPoint.z = length * 0.5f;
			break;
		default:
			throw std::logic_error("Invalid Axis - CubeVolume - LowestPoint!");
			break;
		};

		return volumePos + highPoint;
	};
};

struct TetrahedronVolume
	: public VolumeDefinition
{
	float width, length, height;

	inline Vector3f NearestPoint(REF(Vector3f) toPos, REF(Vector3f) volumePos /* = Vector3f::zero */, OUT_PARAM(real) distanceToPos /* = nullptr */) const
	{
		LOGIC_ERR("Tetrahedron does not yet have NearestPoint implemented!");
	};

	inline Vector3f HighestPoint(VectParam volumePos /* = Vector3f::zero */, Axis upAxis /* = UP */) const
	{
		Vector3f highPoint;

		highPoint.y = height * 0.5f;//from center

		return volumePos + highPoint;
	};
};

struct PrismVolume
	: public VolumeDefinition
{
	float width, length, height;

	inline Vector3f NearestPoint(REF(Vector3f) toPos, REF(Vector3f) volumePos /* = Vector3f::zero */, OUT_PARAM(real) distanceToPos /* = nullptr */) const
	{
		LOGIC_ERR("Prism does not yet have NearestPoint implemented!");
	};

	inline Vector3f HighestPoint(VectParam volumePos /* = Vector3f::zero */, Axis upAxis /* = UP */) const
	{
		Vector3f highPoint;

		highPoint.y = height * 0.5f;//from center

		return volumePos + highPoint;
	};
};
#endif // VolumeDefinition_h__
