#ifndef intFactor_h__
#define intFactor_h__
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

#define FACTOR_CLASS floatFactor /**/
#define VALUE_TYPE int /**/
#define VALUE_ZERO 0 /*The default constructor value*/
#define FACTOR_TYPE float /**/
#define FACTOR_ZERO (0.0f /*Default value*/)
#define FACTOR_ONE 1.0f /*What to divide by value to get the factor*/

#include "FactorBase.h"
#endif // intFactor_h__
