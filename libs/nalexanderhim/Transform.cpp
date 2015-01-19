/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Transform.h"
#include "M3DTools.h"

Transform::Transform(const Vector3f& init_position, const Vector3f& init_rotation, const Vector3f& init_scale)
{
	position = init_position;
	rotation = init_rotation;
	scale = init_scale;
}
Transform::~Transform()
{
}

void Transform::getRenderMatrix(M3DMatrix44f& outResult)
{
	M3DMatrix44f translate;
	M3DMatrix44f rotateResult, rotateX, rotateY, rotateZ;
	M3DMatrix44f scaleResult;

	m3dLoadIdentity44(outResult);
	m3dTranslationMatrix44(translate, position.x, position.y, position.z);
	m3dRotationMatrix44(rotateZ, (float)m3dDegToRad(rotation.z), 0.0f, 0.0f, 1.0f);
	m3dRotationMatrix44(rotateY, (float)m3dDegToRad(rotation.y), 0.0f, 1.0f, 0.0f);
	m3dRotationMatrix44(rotateX, (float)m3dDegToRad(rotation.x), 1.0f, 0.0f, 0.0f);
	m3dMatrixMultiply44(rotateResult, rotateX, rotateY);
	m3dMatrixMultiply44(rotateResult, rotateResult, rotateZ);
	m3dScaleMatrix44(scaleResult, scale.x, scale.y, scale.z);
	
	//TRANSLATE -> ROTATE -> SCALE
	//m3dMatrixMultiply44(outResult, scaleResult, rotateResult);
	//m3dMatrixMultiply44(outResult, translate, outResult);
	m3dMatrixMultiply44(outResult, rotateResult, translate);
	m3dMatrixMultiply44(outResult, scaleResult, outResult);
}

void Transform::setPosition(const M3DVector3f& newPosition)
{
	assignVector3f(position, newPosition);
}
void Transform::setRotation(const M3DVector3f& newRotation)
{
	assignVector3f(rotation, newRotation);
}
void Transform::setScale(float newScale)
{
	scale.x = newScale;
	scale.y = newScale;
	scale.z = newScale;
}

void Transform::moveForward(float amount)
{
	position.z += amount;
}
void Transform::moveRight(float amount)
{
	position.x -= amount;
}
void Transform::moveUp(float amount)
{
	position.y -= amount;
}
void Transform::rotateRollRight(float amount)
{
	rotation.z += amount;
}
void Transform::rotateTurnRight(float amount)
{
	rotation.y += amount;
}
void Transform::rotateTurnUp(float amount)
{
	rotation.x -= amount;
}
