/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Transform.h"
#include "DebugTools.h"

#define _USE_MATH_DEFINES // for C++
#include <math.h>

#include <math3d.h>

#include "M3DTools.h"
#include "GeneralMath.h"
#include "RotationMath.h"

const float ROTATION_LIMIT = 180.0f;//89.0 * M_PI / 180.0;

const Vector3f Transform::getForwardVector() const
{
	float forwardX = 0.0f, forwardY = 0.0f, forwardZ = 0.0f;

	/*Precision testing
	float sinP = sin(getPitchRad());
	float sinY = sin(getYawRad());
	float sinR = sin(getRollRad());
	float cosP = nah::CosF_Precise(getPitchRad());
	float cosY = cos(getYawRad());
	float cosR = cos(getRollRad());
	float tanP = tan(getPitchRad());
	float tanY = tan(getYawRad());
	float tanR = tan(getRollRad());
	//*/

	//* My sourced method
		//HACK: This method does not account for Roll, which will break the Right and Up vectors.
	forwardX = nah::SinF_Precise(rotation.getYawRad());
	forwardY = nah::SinF_Precise(rotation.getPitchRad());
	forwardZ = nah::CosF_Precise(rotation.getPitchRad()) * nah::CosF_Precise(rotation.getYawRad());
	//*/

	return Vector3f(forwardX, forwardY, forwardZ).getNormalized();
}
const Vector3f Transform::getUpVector() const
{
	float upX = 0.0f, upY = 0.0f, upZ = 0.0f;

	//*Old method
	//WARNING: WILL NOT WORK WITH ROLL!
	Vector3f forVect = getForwardVector();
	upX = 0.0f;//no x-axis without roll// forVect.x;
	upY = -forVect.z;
	upZ = forVect.y;
	//*/
	/*Attempted improvement
	Vector3f crossVect = Vector3f::CrossProductF(getForwardVector(), getRightVector());
	upX = crossVect.x;
	upY = crossVect.y;
	upZ = crossVect.z;
	//*/

	return Vector3f(upX, upY, upZ).getNormalized();
}
const Vector3f Transform::getRightVector() const
{
	float rightX=0.0f, rightY=0.0f, rightZ=0.0f;

	//*Old method
	//WARNING: WILL NOT WORK WITH ROLL!
	Vector3f forVect = getForwardVector();
	rightX = -forVect.z;
	rightY = 0.0f;//no y-axis without roll// forVect.y;
	rightZ = forVect.x;
	//*/
	/*Attempted improvement
	Vector3f crossVect = Vector3f::CrossProductF(getForwardVector(), &Vector3f(0.0f, 1.0f, 0.0f));//HACK: using the standard Up vector for cross means Roll will not work
	rightX = crossVect.x;
	rightY = crossVect.y;
	rightZ = crossVect.z;
	//*/

	return -Vector3f(rightX, rightY, rightZ).getNormalized();
}

void Transform::calcRenderMatrix(OUT_PARAM(M3DMatrix44f) outResult) const
{
	//TODO: only recalculate matrices if they are changed

	M3DMatrix44f translate;
	M3DMatrix44f rotateResult, rotateX, rotateY;// , rotateZ;
	M3DMatrix44f scaleResult;

	m3dLoadIdentity44(*outResult);
	
	//Translation
	m3dTranslationMatrix44(translate, position.x, position.y, -position.z);

	//Rotation
	//m3dRotationMatrix44(rotateZ, (float)m3dDegToRad(rotation.z), 0.0f, 0.0f, 1.0f);
	m3dRotationMatrix44(rotateY, (float)m3dDegToRad(rotation.y), 0.0f, -1.0f, 0.0f);
	m3dRotationMatrix44(rotateX, (float)m3dDegToRad(rotation.x), 1.0f, 0.0f, 0.0f);
	m3dMatrixMultiply44(rotateResult, rotateY, rotateX);
	//m3dMatrixMultiply44(rotateResult, rotateResult, rotateZ);//this line causes Roll
	
	//Scale
	m3dScaleMatrix44(scaleResult, scale.x, scale.y, scale.z);
	
	//TRANSLATE -> ROTATE -> SCALE
	m3dMatrixMultiply44(*outResult, rotateResult, scaleResult);
	m3dMatrixMultiply44(*outResult, translate, *outResult);
}

void Transform::setPosition(REF(M3DVector3f) newPosition)
{
	assignVector3f(position, newPosition);
}
void Transform::setRotation(REF(M3DVector3f) newRotation, bool setDegrees /*= true*/)
{
	Vector3f tempRot;
	assignVector3f(tempRot, newRotation);
	rotation = Rotation3D(rotation, !setDegrees);
}

std::string Transform::toString(bool pos /*= true*/, bool rot /*= true*/, bool scl /*= true*/) const
{
	std::string textline = "";
	if (pos)
		textline += position.toString() + " | ";
	if (rot)
		textline += rotation.toString() + " | ";
	if (scl)
		textline += scale.toString();
	return textline;
}
std::string Transform::toStringMultiLine(bool pos /*= true*/, bool rot /*= true*/, bool scl /*= true*/) const
{
	std::string textline = "";
	if (pos)
		textline += position.toString() + "\n";
	if (rot)
		textline += rotation.toString() + "\n";
	if (scl)
		textline += scale.toString() + "\n";
	return textline;
}
