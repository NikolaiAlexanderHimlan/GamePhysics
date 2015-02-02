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

Vector3f Transform::getForwardVector(char axis) const
{
	float forwardX = 0.0f, forwardY = 0.0f, forwardZ = 0.0f;

	//calculate each axis, unless an axis was specified, in which case only calculate that axis.
	//HACK: calculating only specific axes prevents correct normalization
	/*
	//if (axis != 'y' && axis != 'z')//calculate x-axis
		forwardX = cos(getYawRad()) * cos(getPitchRad());
	//if (axis != 'x' && axis != 'z')//calculate y-axis
		forwardY = sin(getPitchRad());//probably something extra?
	//if (axis != 'x' && axis != 'y')//calculate z-axis
		forwardZ = sin(getYawRad()) * cos(getPitchRad());
	//^above math is WRONG!!!*/

	forwardX = sin(getYawRad());
	forwardY = -sin(getPitchRad());
	forwardZ = cos(getYawRad());

	return -Vector3f(forwardX, forwardY, forwardZ).normalized();
}
Vector3f Transform::getUpVector(char axis) const
{
	float upX = 0.0f, upY = 0.0f, upZ = 0.0f;

	Vector3f forVect = getForwardVector();
	upX = forVect.x;
	upY = -forVect.z;
	upZ = forVect.y;

	return Vector3f(upX, upY, upZ).normalized();
}
Vector3f Transform::getRightVector(char axis) const
{
	float rightX=0.0f, rightY=0.0f, rightZ=0.0f;

	//calculate each axis, unless an axis was specified, in which case only calculate that axis.
	//HACK: calculating only specific axes prevents correct normalization
	/*
	//if (axis != 'y' && axis != 'z')//calculate x-axis
		rightX = (float)cos(getYawRad() - M_PI_2);
	//if (axis != 'x' && axis != 'z')//calculate y-axis
		rightY = 0.0f;//(float)sin(getPitchRad() - M_PI_2)
	//if (axis != 'x' && axis != 'y')//calculate z-axis
		rightZ = (float)sin(getYawRad() - M_PI_2);
	//^Am certain above math is wrong!!!*/

	/*
	rightX = sin(getYawRad() - M_PI_2);
	rightY = -sin(getPitchRad());
	rightZ = cos(getYawRad() - M_PI_2);
	//doesn't work quite right*/

	Vector3f forVect = getForwardVector();
	rightX = forVect.z;
	rightY = forVect.y;
	rightZ = -forVect.x;
	
	return -Vector3f(rightX, rightY, rightZ).normalized();
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

	//Vector3f::EulerForward(getPitchRad(), getYawRad(), getRollRad());

	position += Vector3f(amount * getForwardVector('x').x, amount * getForwardVector('y').y, amount * getForwardVector('z').z);
}
void Transform::moveRight(float amount)
{
	//position.x += amount;
	position += Vector3f(amount * getRightVector('x').x, amount * getRightVector('y').y, amount * getRightVector('z').z);
}
void Transform::moveUp(float amount)
{
	//position.y += amount;
	position += Vector3f(amount * getUpVector('x').x, amount * getUpVector('y').y, amount * getUpVector('z').z);
}

void Transform::rotatePitch(float degrees)
{
	//rotation.x -= amount;
	float newAngle = getPitchDeg() + degrees;
	//newAngle = nah::DegreesToRadians(newAngle);

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	setPitch(newAngle);
}
void Transform::rotateYaw(float degrees)
{
	//rotation.y += amount;
	float newAngle = getYawDeg() - degrees;
	//newAngle = nah::DegreesToRadians(newAngle);

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	setYaw(newAngle);
}
void Transform::rotateRoll(float degrees)
{
	//rotation.z += degrees;
	float newAngle = getRollDeg() + degrees;
	//newAngle = nah::DegreesToRadians(newAngle);

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	setRoll(newAngle);
}