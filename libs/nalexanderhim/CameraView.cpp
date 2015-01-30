/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "CameraView.h"

#include <GLTools.h>
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

	M3DMatrix44f translate;
	M3DMatrix44f rotateResult, rotateX, rotateY, rotateZ;
	M3DMatrix44f scaleResult;

	m3dLoadIdentity44(outResult);
	
	//Translation
	m3dTranslationMatrix44(translate, localTransform.position.x, localTransform.position.y, localTransform.position.z);

	//Rotation
	m3dRotationMatrix44(rotateZ, (float)m3dDegToRad(localTransform.rotation.z), 0.0f, 0.0f, 1.0f);
	m3dRotationMatrix44(rotateY, (float)m3dDegToRad(localTransform.rotation.y), 0.0f, 1.0f, 0.0f);
	m3dRotationMatrix44(rotateX, (float)m3dDegToRad(localTransform.rotation.x), 1.0f, 0.0f, 0.0f);
	m3dMatrixMultiply44(rotateResult, rotateX, rotateY);
	m3dMatrixMultiply44(rotateResult, rotateResult, rotateZ);
	
	//Scale
	m3dScaleMatrix44(scaleResult, localTransform.scale.x, localTransform.scale.y, localTransform.scale.z);

	//TRANSLATE -> ROTATE -> SCALE
	//m3dMatrixMultiply44(outResult, scaleResult, rotateResult);
	//m3dMatrixMultiply44(outResult, translate, outResult);
	m3dMatrixMultiply44(outResult, rotateResult, translate);
	m3dMatrixMultiply44(outResult, scaleResult, outResult);
}
