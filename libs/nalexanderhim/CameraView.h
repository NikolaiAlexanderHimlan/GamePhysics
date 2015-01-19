/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _CAMERAVIEW_H
#define _CAMERAVIEW_H

//GLTools
#include <math3d.h>

#include "Object3D.h"

class CameraView
	: public Object3D
{
public:
	Transform localTransform;

	CameraView(){};
	CameraView(const Transform& initialTransform) : Object3D(initialTransform){}
	~CameraView(){};
	
	void getView(M3DMatrix44f& outResult);
};

#endif
