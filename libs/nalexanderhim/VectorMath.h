#ifndef VectorMath_h__
#define VectorMath_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "CountedArray.h"
#include "ccmccooeyWrapper.h"
#include "DebugDefines.h"
#include "MathDefines.h"

typedef nah::CountedArray<float> VectorNf;//Vector of an arbitrary length.

static VectorNf toVectorNf(REF(Vector3f) vect)
{
	float vectArray[3];
	vect.toArray(vectArray);
	return VectorNf(3, vectArray);
};
static VectorNf Cross(REF(VectorNf) lhs, REF(VectorNf) rhs);
static float Dot(REF(VectorNf) lhs, REF(VectorNf) rhs)
{
	if (lhs.count() != rhs.count())
		LOGIC_ERR("Vector N sizes do not match!");

	float dotTotal = 0.0f;
	for (uint i = 0; i < lhs.count(); i++)
		dotTotal += lhs[i] * rhs[i];

	return dotTotal;
};

#endif // VectorMath_h__
