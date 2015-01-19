/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _OBJECT3D_H
#define _OBJECT3D_H

#include "Transform.h"

class Object3D
{
public:
	Transform localTransform;//The local transform of the 3D object

	Object3D(const Transform& initialTransform = Transform())
	{ localTransform = initialTransform;	}
};
#endif
