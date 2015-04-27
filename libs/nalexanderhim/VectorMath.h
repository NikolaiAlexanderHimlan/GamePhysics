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
typedef nah::CountedArray<float> VectorNf;//Vector of an arbitrary length.

static VectorNf Cross(REF(VectorNf) lhs, REF(VectorNf) rhs);
static float Dot(REF(VectorNf) lhs, REF(VectorNf) rhs);

#endif // VectorMath_h__
