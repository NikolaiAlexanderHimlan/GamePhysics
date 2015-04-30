#ifndef Matrix33r_h__
#define Matrix33r_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "MatrixR.h"
class Matrix33r :
	public MatrixR
{
public:

	Matrix33r()
		: MatrixR(3,3)
	{
	};
	~Matrix33r()
	{
	};
};

#endif // Matrix33r_h__
