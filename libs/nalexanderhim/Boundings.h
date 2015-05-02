#ifndef Boundings_h__
#define Boundings_h__

/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ccmccooeyWrapper.h"
#include "CodingDefines.h"
#include "SpaceDefines.h"
#include "DebugDefines.h"
#include "MathDefines.h"

/* Bounding Function Default data
static const BoundType BOUND_TYPE = ;

//Specific Bounds Data

virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr) const;

virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount) const;
*/

//TODO: CONSIDER: rather than creating a new struct for each bounds type, instead Bounding functions take a Volume as parameters
struct Bounding
{
	//TODO: CONSIDER: combine with Primitives type
	enum BoundType {
		INVALID_BOUND_TYPE = -1,

		BASIC,
		PLANE,
		SPHERE,
		CUBE,
		BOX = CUBE, 

		NUM_BOUND_TYPES
	};
	static const BoundType BOUND_TYPE = BASIC;
	BoundType getType() const { return BOUND_TYPE;	};
	virtual Vector3f getDimensions() const { return Vector3f::zero;	};

	//Checks with another set of bounds for an overlap
	//(What it actually does is figure out this bound's closest point then checks if the other bounds contains that point)
	//@param  Overlap amount
	virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr, OUT_PARAM(Vector3f) overlapNormal = nullptr) const
	{
		return otherBounds.Contains(otherLocation, boundsLocation, overlapAmount);
	};

	//checks if a given point is within bounds
	//@return Depth from the edge of bounds
	virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount, OUT_PARAM(Vector3f) overlapNormal = nullptr) const
	{
		OUT_SET(overlapAmount, 0);
		return boundsLocation == checkLocation;
	};
};

//HACK: walls are currently essentially infinite
//HACK: impassable is currently not implemented
struct PlaneBounding
	: public Bounding
{
	static const BoundType BOUND_TYPE = PLANE;

	PlaneBounding(Vector3f planeNormal = UP, bool planeImpassable = false)
		: normal(planeNormal), impassable(planeImpassable), infinite(true) {};
	PlaneBounding(float planeWidth, float planeLength, Vector3f planeNormal = UP, bool planeImpassable = false)
		: width(planeWidth), length(planeLength), normal(planeNormal), impassable(planeImpassable), infinite(false) {};

	float width, length;
	Vector3f normal;
	bool impassable = false;//is it possible for an object to be on the opposite side of the wall from the normal?
	bool infinite = false;//should the width/length not matter?

	virtual Vector3f getDimensions() const { return Vector3f(width, 0.0f, length);	};

	virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr, OUT_PARAM(Vector3f) overlapNormal = nullptr) const;

	virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount, OUT_PARAM(Vector3f) overlapNormal = nullptr) const;
};

#include "VolumeDefinition.h"
struct SphereBounding
	: public Bounding, public SphereVolume
{
	static const BoundType BOUND_TYPE = SPHERE;

	SphereBounding(REF(SphereVolume) boundingVolume) : SphereVolume(boundingVolume) {};

	virtual Vector3f getDimensions() const { return Vector3f(radius, radius, radius);	};

	virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr, OUT_PARAM(Vector3f) overlapNormal = nullptr) const;

	virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount, OUT_PARAM(Vector3f) overlapNormal = nullptr) const;
};

struct CubeBounding
	: public Bounding, public CubeVolume
{
	static const BoundType BOUND_TYPE = CUBE;

	CubeBounding(REF(CubeVolume) boundingVolume) : CubeVolume(boundingVolume) {};

	virtual Vector3f getDimensions() const { return VolumeVector() * 2.0f;	};

	virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr, OUT_PARAM(Vector3f) overlapNormal = nullptr) const;

	virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount, OUT_PARAM(Vector3f) overlapNormal = nullptr) const;
};
typedef CubeBounding BoxBounding;
#endif // Boundings_h__
