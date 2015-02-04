/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "CameraView.h"

#include <GLTools.h>
//#include <GL/glut.h>
#include <GLFrustum.h>

CameraView::CameraView(const Transform& initialTransform /*= Transform()*/)
{
	localTransform = initialTransform;
	viewFrustum = new GLFrustum();
}
CameraView::~CameraView()
{
	delete viewFrustum;
}

void CameraView::getViewMatrix(M3DMatrix44f& outResult) const
{
	localTransform.getRenderMatrix(outResult);
	M3DMatrix44f tempMatrix;
	m3dInvertMatrix44(tempMatrix, outResult);
	m3dCopyMatrix44(outResult, tempMatrix);
	return;//skip
}
