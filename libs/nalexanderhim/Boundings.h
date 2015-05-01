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
#include "DebugDefines.h"
#include "CodingDefines.h"
#include "MathDefines.h"
#include "GeneralMath.h"
#include "SpaceDefines.h"

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

	//Checks with another set of bounds for an overlap
	//(What it actually does is figure out this bounds's closest point then checks if the other bounds contains that point)
	//@param  Overlap amount
	virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr) const
	{
		return otherBounds.Contains(otherLocation, boundsLocation, overlapAmount);
	};

	//checks if a given point is within bounds
	//@return Depth from the edge of bounds
	virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount) const
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

	virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr) const
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
	};

	virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount) const
	{
		bool doesContain = false;
		real overlap;

		overlap = Vector3f::DistanceSquared(boundsLocation, checkLocation);

		//checkLocation on opposite side from normal
		//TODO: handle impassable
		if (impassable)
		{
			if(overlap > 0)
			LOGIC_ERR("impassible not implemented - PlanesBounding - Contains");
		}
		else overlap = nah::absInv((float)overlap);//if plane is not "impassable" then there cannot be a positive overlap
		OUT_SET(overlapAmount, nah::sqrtKeepSign((float)overlap))
		return doesContain;
	};
};

#include "VolumeDefinition.h"
struct SphereBounding
	: public Bounding, public SphereVolume
{
	static const BoundType BOUND_TYPE = SPHERE;

	SphereBounding(REF(SphereVolume) boundingVolume) : SphereVolume(boundingVolume) {};

	virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr) const
	{
		//1st, calculate a vector to otherLocation with radius as the length.
		Vector3f vectTo = Vector3f::Distancepoint(boundsLocation, otherLocation, radius);

		//2nd, check if this vector passes the otherLocation, in which case there is definitely a collision
		if(Vector3f::isBetween(boundsLocation, vectTo, otherLocation))
			return true;

		//3rd, check if the other bounds contains the location indicated by the calculated vector
		//return otherBounds.Contains(otherLocation, vectTo);//cannot call directly due to inheritance funnyness, calling Bounding CheckOverlap
		return otherBounds.Contains(otherLocation, vectTo, overlapAmount);
	};

	virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount) const
	{
		//check if distance to checkLocation is less than radius, return this as the result
		real overlap = std::powf(radius, 2.0f) - Vector3f::DistanceSquared(boundsLocation, checkLocation);
		OUT_SET(overlapAmount, overlap)
		return overlap > 0;
	};
};

struct CubeBounding
	: public Bounding, public CubeVolume
{
	static const BoundType BOUND_TYPE = CUBE;

	CubeBounding(REF(CubeVolume) boundingVolume) : CubeVolume(boundingVolume) {};

	virtual bool CheckOverlap(REF(Bounding) otherBounds, REF(Vector3f) boundsLocation, REF(Vector3f) otherLocation, OUT_PARAM(real) overlapAmount = nullptr) const
	{
		Vector3f closePoint = VolumeVector();
		closePoint = Vector3f::Multiply(closePoint, 
			Vector3f::DirectionTo(boundsLocation, otherLocation));
		return otherBounds.Contains(otherLocation, closePoint, overlapAmount);
	};

	virtual bool Contains(REF(Vector3f) boundsLocation, REF(Vector3f) checkLocation, OUT_PARAM(real) overlapAmount) const
	{
		Vector3f relativePoint = checkLocation - boundsLocation;
		//Vector3f relativePoint = boundsLocation - checkLocation;
		OUT_SET(overlapAmount, Vector3f::Subtract_NonZero(VolumeVector(), Vector3f::abs(relativePoint)).Length())
		return VolumeVector().GreaterEqual_All(Vector3f::abs(relativePoint));
	};
};
#endif // Boundings_h__
