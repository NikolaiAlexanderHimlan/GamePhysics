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
class GLFrustum;

#include "Transform.h"

class CameraView
{
public:
	Transform localTransform;
	GLFrustum* viewFrustum;

	CameraView(const Transform& initialTransform = Transform());
	~CameraView();
	
	void getViewMatrix(M3DMatrix44f& outResult) const;
	GLFrustum* getViewFrustum() const { return viewFrustum;	}
};

#endif