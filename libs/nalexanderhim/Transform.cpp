/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Transform.h"

#define _USE_MATH_DEFINES // for C++
#include <math.h>

#include "M3DTools.h"
#include "GeneralMath.h"
#include "RotationMath.h"

const float ROTATION_LIMIT = 180.0f;//89.0 * M_PI / 180.0;

Transform::Transform(const Vector3f& init_position, const Vector3f& init_rotation, const Vector3f& init_scale)
{
	position = init_position;
	rotation = init_rotation;
	scale = init_scale;
}
Transform::~Transform()
{
}

Vector3f Transform::getRightVector(char axis) const
{
	float rightX=0.0f, rightY=0.0f, rightZ=0.0f;

	//calculate each axis, unless an axis was specified, in which case only calculate that axis.
	if (axis != 'y' && axis != 'z')//calculate x-axis
		rightX = (float)cos(getYaw() - M_PI_2);
	if (axis != 'x' && axis != 'z')//calculate y-axis
		rightY = 0.0f;/*(float)sin(getPitch() - M_PI_2)*/
	if (axis != 'x' && axis != 'y')//calculate z-axis
		rightZ = (float)sin(getYaw() - M_PI_2);
	
	return Vector3f(rightX, rightY, rightZ);
}

void Transform::getRenderMatrix(M3DMatrix44f& outResult) const
{
	M3DMatrix44f translate;
	M3DMatrix44f rotateResult, rotateX, rotateY, rotateZ;
	M3DMatrix44f scaleResult;

	m3dLoadIdentity44(outResult);
	
	//Translation
	m3dTranslationMatrix44(translate, position.x, position.y, position.z);

	//Rotation
	m3dRotationMatrix44(rotateZ, (float)m3dDegToRad(rotation.z), 0.0f, 0.0f, 1.0f);
	m3dRotationMatrix44(rotateY, (float)m3dDegToRad(rotation.y), 0.0f, 1.0f, 0.0f);
	m3dRotationMatrix44(rotateX, (float)m3dDegToRad(rotation.x), 1.0f, 0.0f, 0.0f);
	m3dMatrixMultiply44(rotateResult, rotateX, rotateY);
	m3dMatrixMultiply44(rotateResult, rotateResult, rotateZ);
	
	//Scale
	m3dScaleMatrix44(scaleResult, scale.x, scale.y, scale.z);
	
	//TRANSLATE -> ROTATE -> SCALE
	//m3dMatrixMultiply44(outResult, scaleResult, rotateResult);
	//m3dMatrixMultiply44(outResult, translate, outResult);
	m3dMatrixMultiply44(outResult, rotateResult, scaleResult);
	m3dMatrixMultiply44(outResult, translate, outResult);
	//m3dMatrixMultiply44(outResult, rotateResult, translate);
	//m3dMatrixMultiply44(outResult, scaleResult, outResult);
	//m3dMatrixMultiply44(outResult, translate, scaleResult);
	//m3dMatrixMultiply44(outResult, rotateResult, outResult);
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
	//position.z -= amount;
	float movX = cos(getYaw()) * cos(getPitch());
	float movY = sin(getPitch());
	float movZ = sin(getYaw()) * cos(getPitch());

	position += Vector3f(amount * movX, amount * movY, amount * movZ);
}
void Transform::moveRight(float amount)
{
	//position.x += amount;
	position += Vector3f(amount * getRightVector().x, amount * getRightVector().y, amount * getRightVector().z);
}
void Transform::moveUp(float amount)
{
	position.y += amount;
}

void Transform::rotatePitch(float degrees)
{
	//rotation.x -= amount;
	float newAngle = getPitch() + degrees;
	//newAngle = nah::DegreesToRadians(newAngle);

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	setPitch(newAngle);
}
void Transform::rotateYaw(float degrees)
{
	//rotation.y += amount;
	float newAngle = getYaw() - degrees;
	//newAngle = nah::DegreesToRadians(newAngle);

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	setYaw(newAngle);
}
void Transform::rotateRoll(float degrees)
{
	//rotation.z += degrees;
	float newAngle = getRoll() + degrees;
	//newAngle = nah::DegreesToRadians(newAngle);

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	setRoll(newAngle);
}
