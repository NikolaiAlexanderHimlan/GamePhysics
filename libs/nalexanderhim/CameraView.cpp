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
#include <math3d.h>

CameraView::CameraView(REF(Transform) initialTransform /*= Transform()*/)
{
	setLocalTransform(initialTransform);
	viewFrustum = new GLFrustum();
}
CameraView::~CameraView()
{
	delete viewFrustum;
}

void CameraView::calcViewMatrix(OUT_PARAM(M3DMatrix44f) outViewMat) const
{
	getWorldTransform().calcRenderMatrix(outViewMat);
	M3DMatrix44f tempMatrix;
	m3dInvertMatrix44(tempMatrix, *outViewMat);
	m3dCopyMatrix44(*outViewMat, tempMatrix);
}
