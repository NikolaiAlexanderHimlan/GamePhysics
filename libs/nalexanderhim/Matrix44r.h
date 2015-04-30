#ifndef Matrix44r_h__
#define Matrix44r_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#pragma once
#include "MatrixR.h"
class Matrix44r :
	public MatrixR
{
public:

	Matrix44r()
		: MatrixR(4,4)
	{
	};
	~Matrix44r()
	{
	};
};

#endif // Matrix44r_h__
