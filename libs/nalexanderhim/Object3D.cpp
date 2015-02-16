/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Object3D.h"

#include <GLTools.h>
#include <GL/glut.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>

#include "CameraView.h"

bool Object3D::Draw(CameraView* renderToView, GLShaderManager& shaderManager, M3DMatrix44f& mvpMatrix) const
{
	M3DMatrix44f modelTransform, viewMatrix, modelView;

	renderToView->getViewMatrix(viewMatrix);
	mLocalTransform.getRenderMatrix(modelTransform);

	//ModelView
	m3dMatrixMultiply44(modelView, viewMatrix, modelTransform);
	//ModelViewProjection
	m3dMatrixMultiply44(mvpMatrix, renderToView->viewFrustum->GetProjectionMatrix(), modelView);

	shaderManager.UseStockShader(GLT_SHADER_SHADED, mvpMatrix);
	//	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE, mvpMatrix, vColor, texture);

	mModelBatch->Draw();

	return true;
}
