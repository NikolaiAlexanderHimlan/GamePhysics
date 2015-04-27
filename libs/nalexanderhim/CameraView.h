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
class GLFrustum;

#include "TransformObject.h"

class CameraView
	: public TransformObject
{
public:
	GLFrustum* viewFrustum;

	CameraView(const Transform& initialTransform = Transform());
	~CameraView();
	
	//Getters
	inline GLFrustum* getViewFrustum() const { return viewFrustum;	}

	//Calculations
	void calcViewMatrix(OUT_PARAM(M3DMatrix44f) outResult) const;
};

#endif
