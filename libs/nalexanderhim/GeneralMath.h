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

///Lawson Tools
#include <Trackable.h>

using namespace std;

namespace nah
{
	//namespace math {
	/*Apparently I can make the functions global by declaring them outside of any class
	///<summary>Custom tools for doing math.</summary>
	//static 
	class MathTools 
	: public Trackable
	{
	public:

	};
	*/

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
	//}
}
