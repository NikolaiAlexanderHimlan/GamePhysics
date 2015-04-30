#ifndef IntertiaTensor_h__
#define IntertiaTensor_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "Matrix33r.h"
class IntertiaTensor
	: public Matrix33r
{
public:
	IntertiaTensor();
	~IntertiaTensor();

	//Setters
	//Sets the value of the matrix from inertia tensor values.
	void setInertiaTensorCoeffs(real ix, real iy, real iz, real ixy = 0, real ixz = 0, real iyz = 0);
	/**
	* Sets the value of the matrix as an inertia tensor of a rectangular block 
	* aligned with the body's coordinate system with the given axis half-sizes and mass.
	*/
	void setBlockInertiaTensor(REF(Vector3f) halfSizes, real mass);
};

#endif // IntertiaTensor_h__
