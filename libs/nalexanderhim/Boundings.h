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

#endif // Boundings_h__
