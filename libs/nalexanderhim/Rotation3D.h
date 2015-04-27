#ifndef Rotation_h__
#define Rotation_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ccmccooeyWrapper.h"
#include "CodingDefines.h"
//typedef Vector3f Rotation3D;/*2 variations of Rotation implementations [Comment this line to switch]
class Rotation3D
	: public Vector3f
{
	bool radRotation = false;
public:
	Rotation3D(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f, bool isRad = false)
		: Vector3f(pitch, yaw, roll), radRotation(isRad) {};
	explicit Rotation3D(bool isRad)
		: Vector3f(0.0f, 0.0f, 0.0f), radRotation(isRad) {};
	Rotation3D(REF(Rotation3D) rot)
		: Vector3f((Vector3f)rot), radRotation(rot.isRadians()) {};
	explicit Rotation3D(REF(Vector3f) vec3, bool isRad = false)
		: Vector3f(vec3), radRotation(isRad) {};

	//Getters
	inline const bool& isRadians() const { return radRotation;	};
	inline const bool isDegrees() const { return !isRadians();	};
		//Gets the given value in the current rotation mode.
	inline const float& getPitch() const { return x;	};
	inline const float& getYaw() const { return y;		};
	inline const float& getRoll() const { return z;	};

	//Gets the given value of the given rotation mode.
	inline float getPitch(bool asDegrees) const	{ return asDegrees ? getPitchDeg() : getPitchRad();	};
	inline float getYaw(bool asDegrees) const	{ return asDegrees ? getYawDeg() : getYawRad();		};
	inline float getRoll(bool asDegrees) const	{ return asDegrees ? getRollDeg() : getRollRad();	};

	//Setters
	inline void setPitch(float angle) { x = angle;	};
	inline void setYaw(float angle) { y = angle;	};
	inline void setRoll(float angle) { z = angle;	};

	//Properties
	inline const Rotation3D asDegrees(void) const { return isRadians() ? *this : Rotation3D(*this).SwitchToRadians();		};
	inline const Rotation3D asRadians(void) const { return !isRadians() ? *this : Rotation3D(*this).SwitchToDegrees();	};

	//Modifiers
	void setRad(const Rotation3D& radians);
	void setDeg(const Rotation3D& degrees);

	//Calculations

	//Actions
	bool SwitchToDegrees(void);
	bool SwitchToRadians(void);
	//@param zeroMin Is the minimum value 0 or the negative half rotation?
	bool TruncateRotations(bool zeroMin = true);//limit rotations to the min and max
	bool WrapRotations(bool zeroMin = true);//wrap rotation values around

	//Operators
	Rotation3D& operator =(const Rotation3D& rhs);
	//Rotation& operator =(const Vector3f& rhs);
	//Static
};
//*/
#endif // Rotation_h__
