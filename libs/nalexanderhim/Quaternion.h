#ifndef Quaternion_h__
#define Quaternion_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "MathDefines.h"
#include "CodingDefines.h"

class Vector3f;

class Quaternion
{
public:
	//Holds the real component of the quaternion.
	real r;

	//Holds the first complex component of the quaternion.
	real i;

	//Holds the second complex component of the quaternion.
	real j;

	// Holds the third complex component of the quaternion.
	real k;

	/**
	* The explicit constructor creates a quaternion with the given components.
	*
	* @param r The real component of the rigid body's orientation quaternion.
	* @param i The first complex component of the rigid body's orientation quaternion.
	* @param j The second complex component of the rigid body's orientation quaternion.
	* @param k The third complex component of the rigid body's orientation quaternion.
	*
	* @note The given orientation does not need to be normalized, and can be zero.
	* This function will not alter the given values, or normalize the quaternion.
	* To normalize the quaternion (and make a zero quaternion a legal rotation), use the normalize function.
	*
	* @see normalize
	*/
	Quaternion(const real r = 0, const real i = 0, const real j = 0, const real k = 0)
		: r(r), i(i), j(j), k(k)
	{
	};
	~Quaternion(){};

	//Properties
	real Length() const;
	//More efficient, useful for comparisons
	inline real LengthSquared() const { return r*r + i*i + j*j + k*k;	};
	inline bool isOrientation() const { return LengthSquared() == 1;	};//Can use LengthSquared since we only care if the length is 1.

	//Actions
	//Normalizes the quaternion to unit length, making it a valid orientation quaternion.
	void Normalize();
	/**
	* Adds the given vector to this, scaled by the given amount.
	* This is used to update the orientation quaternion by a rotation and time.
	*
	* @param vector The vector to add.
	*
	* @param scale The amount of the vector to add.
	*/
	void addScaledVector(REF(Vector3f) vector, real scale);
	void RotateByVector(REF(Vector3f) vector);

	//Operators
		//Assignment
	Quaternion& operator *=(REF(Quaternion) rhs);
};

#endif // Quaternion_h__
