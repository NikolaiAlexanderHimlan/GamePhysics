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
protected:
	Transform mLocalTransform;//The local transform of the 3D object

public:
	Object3D(void){};
	Object3D(BatchData* batch)
		: Model(batch)
	{
		mLocalTransform = Transform();
	}
	virtual ~Object3D(){};

	//Getters
	inline Transform getLocalTransform() const { return mLocalTransform;	};
	virtual inline Transform& getLocalTransformRef() { return mLocalTransform;	};//returns a modifiable reference, done as a function so modifications can be tracked

	//Setters
	inline void setLocalTransform(const Transform& newTransform) { getLocalTransformRef() = newTransform; };//done using getLocalTransformRef for convenience to subclasses

	//TODO: make renderView a const pointer
	virtual bool Draw(CameraView* renderView, GLShaderManager& shaderManager, M3DMatrix44f& mvpMatrix) const;
};

#endif
