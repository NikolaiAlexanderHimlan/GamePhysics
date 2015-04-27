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
	if (x > maxVal)			{ x = maxVal; changedRotation = true;	}
	else if (x < minVal)	{ x = minVal; changedRotation = true;	}
	if (y > maxVal)			{ y = maxVal; changedRotation = true;	}
	else if (x < minVal)	{ y = minVal; changedRotation = true;	}
	if (z > maxVal)			{ z = maxVal; changedRotation = true;	}
	else if (z < minVal)	{ z = minVal; changedRotation = true;	}

	return changedRotation;
}
bool Rotation3D::WrapRotations(bool zeroMin /*= true*/)
{
	CALCULATE_ROTATION_LIMITS;

	bool changedRotation = false;
	if (x > maxVal)			{ x = minVal; changedRotation = true;	}
	else if (x < minVal)	{ x = maxVal; changedRotation = true;	}
	if (y > maxVal)			{ y = minVal; changedRotation = true;	}
	else if (x < minVal)	{ y = maxVal; changedRotation = true;	}
	if (z > maxVal)			{ z = minVal; changedRotation = true;	}
	else if (z < minVal)	{ z = maxVal; changedRotation = true;	}

	return changedRotation;
}
#pragma endregion Rotation Limiters

