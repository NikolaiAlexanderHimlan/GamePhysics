/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Rotation3D.h"
#include "RotationMath.h"

float Rotation3D::getPitchDeg() const	{ return isRadians() ? nah::RadiansToDegrees(getPitch()) : getPitch();	}
float Rotation3D::getYawDeg() const		{ return isRadians() ? nah::RadiansToDegrees(getYaw()) : getYaw();	}
float Rotation3D::getRollDeg() const	{ return isRadians() ? nah::RadiansToDegrees(getRoll()) : getRoll();	}
float Rotation3D::getPitchRad() const	{ return isDegrees() ? nah::DegreesToRadians(getPitch()) : getPitch();	}
float Rotation3D::getYawRad() const		{ return isDegrees() ? nah::DegreesToRadians(getYaw()) : getYaw();	}
float Rotation3D::getRollRad() const	{ return isDegrees() ? nah::DegreesToRadians(getRoll()) : getRoll();	}

void Rotation3D::setPitchDeg(float degrees)	{ setPitch(isDegrees() ? degrees : nah::DegreesToRadians(degrees));	}
void Rotation3D::setYawDeg(float degrees)	{ setYaw(isDegrees() ? degrees : nah::DegreesToRadians(degrees));	}
void Rotation3D::setRollDeg(float degrees)	{ setRoll(isDegrees() ? degrees : nah::DegreesToRadians(degrees));	}

bool Rotation3D::SwitchToDegrees(void)
{
	if (isRadians())
	{
		setPitch(getPitchDeg());
		setYaw(getYawDeg());
		setRoll(getRollDeg());
		radRotation = false;
	}
	return isRadians();
}
bool Rotation3D::SwitchToRadians(void)
{
	if (isDegrees())
	{
		setPitch(getPitchRad());
		setYaw(getYawRad());
		setRoll(getRollRad());
		radRotation = true;
	}
	return isRadians();
}

#pragma region Rotation Limiters
#define CALCULATE_ROTATION_LIMITS float minVal = 0.0f, maxVal, halfVal;\
{\
	if (isRadians())\
		maxVal = 2.0f;\
	else\
		maxVal = 360.0f;\
	halfVal = maxVal * 0.5f;\
	if (!zeroMin){\
		minVal -= halfVal;\
		maxVal -= halfVal;\
	}\
}\

bool Rotation3D::TruncateRotations(bool zeroMin /*= true*/)
{
	CALCULATE_ROTATION_LIMITS;

	bool changedRotation = false;
	if (getPitch() > maxVal)		{ refPitch() = maxVal; changedRotation = true;	}
	else if (getPitch() < minVal)	{ refPitch() = minVal; changedRotation = true;	}
	if (getYaw() > maxVal)			{ refYaw() = maxVal; changedRotation = true;	}
	else if (getYaw() < minVal)		{ refYaw() = minVal; changedRotation = true;	}
	if (getRoll() > maxVal)			{ refRoll() = maxVal; changedRotation = true;	}
	else if (getRoll() < minVal)	{ refRoll() = minVal; changedRotation = true;	}

	return changedRotation;
}
bool Rotation3D::WrapRotations(bool zeroMin /*= true*/)
{
	CALCULATE_ROTATION_LIMITS;

	bool changedRotation = false;
	if (getPitch() > maxVal)		{ refPitch() = minVal; changedRotation = true;	}
	else if (getPitch() < minVal)	{ refPitch() = maxVal; changedRotation = true;	}
	if (getYaw() > maxVal)			{ refYaw() = minVal; changedRotation = true;	}
	else if (getYaw() < minVal)		{ refYaw() = maxVal; changedRotation = true;	}
	if (getRoll() > maxVal)			{ refRoll() = minVal; changedRotation = true;	}
	else if (getRoll() < minVal)	{ refRoll() = maxVal; changedRotation = true;	}

	return changedRotation;
}
#pragma endregion Rotation Limiters

Rotation3D Rotation3D::Add(Rotation3D lhs, Rotation3D rhs, bool lhsRotationType /*= true*/)
{
	bool addRadians;
	if (lhsRotationType)
		addRadians = lhs.isRadians();
	else
		addRadians = rhs.isRadians();

	if(addRadians)
	{
		lhs.SwitchToRadians();
		rhs.SwitchToRadians();
	}
	else
	{
		lhs.SwitchToDegrees();
		rhs.SwitchToDegrees();
	}

	return Rotation3D(Vector3f::Add(lhs, rhs), addRadians);
}

//implementation found here: http://stackoverflow.com/a/8208951
const Rotation3D Rotation3D::calcLookAtRotation(REF(Vector3f) eye, REF(Vector3f) lookAt, bool inRadians)
{
	Rotation3D lookRotation = Rotation3D(true);//start with radians

	/*TODO: implement ACTUAL look at
	#if _MSC_VER
	#pragma warning ("Warning : LookAt is NOT implemented!")
	#endif
	LOG_WARNING("LookAt is NOT implemented!");
	//*/

	Vector3f diff = Difference(lookAt, eye);
	float xzdistance = sqrt(diff.x * diff.x + diff.z * diff.z);
	lookRotation.x = (-atan2(diff.y, xzdistance)); // rotation around x
	lookRotation.y = (atan2(diff.x, diff.z)); // rotation around y
	lookRotation.z = (0); // rotation around z

	//switch to degrees if set to
	if (!inRadians)
		lookRotation.SwitchToDegrees();

	return lookRotation;
}
