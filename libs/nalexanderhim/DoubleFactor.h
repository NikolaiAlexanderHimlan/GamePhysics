#ifndef doubleFactor_h__
#define doubleFactor_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#undef FACTOR_CLASS
#undef VALUE_TYPE
#undef VALUE_ZERO
#undef FACTOR_TYPE
#undef FACTOR_ZERO
#undef FACTOR_ONE

#define FACTOR_CLASS doubleFactor /**/
#define VALUE_TYPE double /**/
#define VALUE_ZERO 0.0 /*The default constructor value*/
#define FACTOR_TYPE VALUE_TYPE /**/
#define FACTOR_ZERO (0.0 /*Default value*/)
#define FACTOR_ONE 1.0 /*What to divide by value to get the factor*/

#include "FactorBase.h"
#endif // doubleFactor_h__
