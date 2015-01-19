/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "CameraView.h"

void CameraView::getView(M3DMatrix44f& outResult)
{
	return localTransform.getRenderMatrix(outResult);

	M3DMatrix44f translate;
	M3DMatrix44f rotateResult, rotateX, rotateY, rotateZ;
	M3DMatrix44f scaleResult;

	m3dLoadIdentity44(outResult);
	m3dTranslationMatrix44(translate, localTransform.position.x, localTransform.position.y, localTransform.position.z);
	m3dRotationMatrix44(rotateZ, (float)m3dDegToRad(localTransform.rotation.z), 0.0f, 0.0f, 1.0f);
	m3dRotationMatrix44(rotateY, (float)m3dDegToRad(localTransform.rotation.y), 0.0f, 1.0f, 0.0f);
	m3dRotationMatrix44(rotateX, (float)m3dDegToRad(localTransform.rotation.x), 1.0f, 0.0f, 0.0f);
	m3dMatrixMultiply44(rotateResult, rotateX, rotateY);
	m3dMatrixMultiply44(rotateResult, rotateResult, rotateZ);
	m3dScaleMatrix44(scaleResult, localTransform.scale.x, localTransform.scale.y, localTransform.scale.z);

	//TRANSLATE -> ROTATE -> SCALE
	//m3dMatrixMultiply44(outResult, scaleResult, rotateResult);
	//m3dMatrixMultiply44(outResult, translate, outResult);
	m3dMatrixMultiply44(outResult, rotateResult, translate);
	m3dMatrixMultiply44(outResult, scaleResult, outResult);
}
