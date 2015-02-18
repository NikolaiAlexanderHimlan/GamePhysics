/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once

//CONSIDER: rename file cmathExtension/cmathExtender

///System Tools
//TODO: decide if it is alright for math.h to be included in every class that uses my MathTools
#include <cmath>
#include <math.h>

using namespace std;

namespace nah
{
#define exp10(exponent) pow(10.0, exponent);
	//namespace math {

	static inline float absInv(float invertThis) { return -abs(invertThis);	};
	
	//************************************
	// Method:    checkWholeNumber
	// FullName:  checkWholeNumber
	// Access:    public static 
	// Returns:   bool
	// Qualifier:
	// Parameter: float checkThis
	// Parameter: double precision
	//************************************
	/// <summary> Takes a float and determines if it is a whole number (no decimal value) </summary>
	/// <remarks> Solution found here: <a href="http://stackoverflow.com/a/15314018"/></remarks>
	/// <param name="checkThis"></param>
	/// <param name="precision">how precisely to check</param>
	/// <returns> if the number is a whole number </returns>
	static inline bool checkWholeNumber(float checkThis, double precision = 0.000001)
	{
		//return checkThis == floor(checkThis);
		return fabs(checkThis - std::floor(checkThis)) < precision;
	}

	static inline bool equalsInRange(float rhs, float lhs, float range)
	{ return abs(rhs-lhs) <= range;	}

	static inline int round(float roundThis)
	{ 
		if(roundThis >0) return (int)std::floor(roundThis+0.5f);
		else if(roundThis <0) return (int)std::ceil(roundThis-0.5f);
		return 0;//roundThis is 0
	}

	static inline float wrapFloat(float wrapThis, float maxWrap = 1.0f, float minWrap = 0.0f)
	{

		const float WRAP_RANGE = maxWrap - minWrap;//difference between the min and max ranges
		const float ACCEPTABLE_RANGE = 0.0f;//maximum acceptable value for the range before the function does nothing
		//const int MAX_WRAP_ATTEMPTS = 10000;//TODO: wrap limit

		bool brokeWrap = false;//something went wrong, do simple wrap

		//check if range is acceptable
		if (WRAP_RANGE <= ACCEPTABLE_RANGE) return WRAP_RANGE;
		
		//check min value
		while (wrapThis < minWrap)
			wrapThis += WRAP_RANGE;
		
		//check max value
		while (wrapThis > maxWrap)
			wrapThis -= WRAP_RANGE;

		if (brokeWrap)
		{
			if (wrapThis < minWrap) wrapThis = minWrap;
			else if (wrapThis > maxWrap) wrapThis = maxWrap;
		}

		return wrapThis;
	}
	//}
}
