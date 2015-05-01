/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _M3DTOOLS_H
#define _M3DTOOLS_H

//GLTools
#include "M3DTypes.h"
#include <math3d.h>

#include <Vector3f.h>

void assignM3DVector3(M3DVector3f& destination, REF(M3DVector3f) assignedValue)
{
	destination[0] = assignedValue[0];
	destination[1] = assignedValue[1];
	destination[2] = assignedValue[2];
}
void assignVector3f(Vector3f& destination, REF(M3DVector3f) assignedValue)
{
	destination.x = assignedValue[0];
	destination.y = assignedValue[1];
	destination.z = assignedValue[2];
}

void assignM3DMatrix44(M3DMatrix44f& destination, REF(M3DMatrix44f) assignedValue)
{
	for (int i = 0; i < 16; i++)
	{
		destination[i] = assignedValue[i];
	};
}

#endif
