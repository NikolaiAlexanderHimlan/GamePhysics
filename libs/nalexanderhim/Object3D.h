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
#include "Model.h"

class BatchData;
class GLShaderManager;
class GLFrustum;

class CameraView;

class Object3D
	: public Model
{
public:
	Transform localTransform;//The local transform of the 3D object

	Object3D(void){};
	Object3D(BatchData* batch)
		: Model(batch)
	{
		localTransform = Transform();
	}
	~Object3D(){};

	//TODO: make renderView a const pointer
	bool Draw(CameraView* renderView, GLShaderManager& shaderManager, M3DMatrix44f& mvpMatrix, GLFrustum& viewFrustum) const;
};

#endif
