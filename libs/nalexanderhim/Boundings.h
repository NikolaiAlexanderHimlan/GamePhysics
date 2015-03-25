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

/* Bounding Function Default data
static const BoundType BOUND_TYPE = ;

//Specific Bounds Data

virtual inline bool CheckOverlap(const Bounding& otherBounds, const Vector3f& boundsLocation, const Vector3f& otherLocation) const

virtual inline bool Contains(const Vector3f& boundsLocation, const Vector3f& checkLocation) const
*/

struct Bounding
{
	enum BoundType {
		INVALID_BOUND_TYPE = -1,

		BASIC,
		PLANE,
		SPHERE,
		CUBE,

		NUM_BOUND_TYPES
	};
	static const BoundType BOUND_TYPE = BASIC;

	//Checks with another set of bounds for an overlap
	virtual inline bool CheckOverlap(const Bounding& otherBounds, const Vector3f& boundsLocation, const Vector3f& otherLocation) const
	{
		return otherBounds.Contains(otherLocation, boundsLocation);
	};

	//checks if a given point is within bounds
	virtual inline bool Contains(const Vector3f& boundsLocation, const Vector3f& checkLocation) const
	{
		return boundsLocation == checkLocation;
	};
};

//HACK: walls are currently essentially infinite
//HACK: impassable is currently not implemented
struct PlaneBounding
	: public Bounding
{
	static const BoundType BOUND_TYPE = PLANE;

	float width, length;
	Vector3f normal;
	bool impassable = false;//is it possible for an object to be on the opposite side of the wall from the normal?

	virtual inline bool CheckOverlap(const Bounding& otherBounds, const Vector3f& boundsLocation, const Vector3f& otherLocation) const
	{
		//Generate a vector with the correct location along the normal and otherLocation filling in the remaining data
		//NOTE: the closer to 1 the axis value in normal is, the less relevant otherLocation is
		//TODO: limit the range of wallPoint based on the width and length
		Vector3f wallPoint = 
			Vector3f::Multiply(boundsLocation, normal)//location of bounds is is directly relevant based on the normal
			+ Vector3f::Multiply(otherLocation, normal.InvertedNormal());//other location is inversely relevant based on the normal

		//checkLocation on opposite side from normal
		//TODO: handle impassable
		if (impassable)
		{
			LOGIC_ERR("impassible not implemented - PlanesBounding - Contains");
		}

		return otherBounds.Contains(otherLocation, wallPoint);
	};

	virtual inline bool Contains(const Vector3f& boundsLocation, const Vector3f& checkLocation) const
	{
		bool doesContain = false;

		//checkLocation on opposite side from normal
		//TODO: handle impassable
		if (impassable)
		{
			LOGIC_ERR("impassible not implemented - PlanesBounding - Contains");
		}
		return doesContain;
	};
};

#include "VolumeDefinition.h"
struct SphereBounding
	: public Bounding, public SphereVolume
{
	static const BoundType BOUND_TYPE = SPHERE;

	virtual inline bool CheckOverlap(const Bounding& otherBounds, const Vector3f& boundsLocation, const Vector3f& otherLocation) const
	{
		//1st, calculate a vector to otherLocation with radius as the length.
		Vector3f vectTo = Vector3f::Distancepoint(boundsLocation, otherLocation, radius);
		
		//2nd, check if this vector passes the otherLocation, in which case there is definitely a collision
		if(Vector3f::Between(boundsLocation, vectTo, otherLocation))
			return true;

		//3rd, check if the other bounds contains the location indicated by the calculated vector
		//return otherBounds.Contains(otherLocation, vectTo);//cannot call directly due to inheritance funnyness, calling Bounding CheckOverlap
		return otherBounds.Contains(otherLocation, vectTo);
	}

	virtual inline bool Contains(const Vector3f& boundsLocation, const Vector3f& checkLocation) const
	{
		//check if distance to checkLocation is less than radius, return this as the result
		return std::powf(radius, 2.0f) > Vector3f::DistanceSquared(boundsLocation, checkLocation);
	}
};

#endif // Boundings_h__
