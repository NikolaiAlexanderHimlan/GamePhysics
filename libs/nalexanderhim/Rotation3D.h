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
	inline const float& getRoll() const { return z;		};
		//Gets a reference to the given rotation value.
	inline float& refPitch() { return x;	};
	inline float& refYaw() { return y;		};
	inline float& refRoll() { return z;		};

	//Gets the given value of the given rotation mode.
	inline float getPitch(bool asDegrees) const	{ return asDegrees ? getPitchDeg() : getPitchRad();	};
	inline float getYaw(bool asDegrees) const	{ return asDegrees ? getYawDeg() : getYawRad();		};
	inline float getRoll(bool asDegrees) const	{ return asDegrees ? getRollDeg() : getRollRad();	};

	//Setters
	inline void setPitch(float angle) { refPitch() = angle;	};
	inline void setYaw(float angle) { refYaw() = angle;		};
	inline void setRoll(float angle) { refRoll() = angle;	};

	//Properties
		//Degrees
	float getPitchDeg() const;
	float getYawDeg() const;
	float getRollDeg() const;
		//Radians
	float getPitchRad() const;
	float getYawRad() const;
	float getRollRad() const;

	inline const Rotation3D asDegrees(void) const { return isRadians() ? *this : Rotation3D(*this).SwitchToRadians();		};
	inline const Rotation3D asRadians(void) const { return !isRadians() ? *this : Rotation3D(*this).SwitchToDegrees();	};

	//Modifiers
		//Degrees
	void setPitchDeg(float degrees);
	void setYawDeg(float degrees);
	void setRollDeg(float degrees);
		//Radians
	void setPitchRad(float radians);
	void setYawRad(float radians);
	void setRollRad(float radians);

	void setRad(const Rotation3D& radians);
	void setDeg(const Rotation3D& degrees);

	//Calculations
	inline Rotation3D Inverse() const { return Rotation3D(-getPitch(), -getYaw(), -getRoll(), isRadians());	};

	//Actions
		//specific rotation modifiers which make it clear what direction rotation will occur in
	inline void rotateYawTurnRightDeg(float degrees) { return setYawDeg(getYawDeg() + degrees);	};
	inline void rotatePitchTiltUpDeg(float degrees) { return setPitchDeg(getPitchDeg() + degrees);	};
	inline void rotateRollRightDeg(float degrees) { return setRollDeg(getRollDeg() + degrees);	};

	bool SwitchToDegrees(void);
	bool SwitchToRadians(void);
	//@param zeroMin Is the minimum value 0 or the negative half rotation?
	bool TruncateRotations(bool zeroMin = true);//limit rotations to the min and max
	bool WrapRotations(bool zeroMin = true);//wrap rotation values around

	//Operators
		//Math
	inline const Rotation3D operator + (REF(Rotation3D) rhs) const	{ return Add(*this, rhs, true );		};
	inline const Rotation3D operator - (REF(Rotation3D) rhs) const	{ return Subtract(*this, rhs, true);	};
	const Rotation3D operator * (REF(Rotation3D) rhs) const			{ return Multiply(*this, rhs, true);	};
	const Rotation3D operator * (REF(Vector3f) rhs) const			{ return Multiply(*this, rhs);			};
	const Rotation3D operator * (float mult) const;
	const Rotation3D operator / (REF(Rotation3D) rhs) const;
	const Rotation3D operator / (REF(Vector3f) rhs) const;
	const Rotation3D operator / (float div) const;
	inline const Rotation3D operator - () const { return Inverse();	};
	
		//Assignment
	//Rotation3D& operator = (REF(Rotation3D) rhs);
	Rotation3D& operator += (REF(Rotation3D) rhs);
	Rotation3D& operator -= (REF(Rotation3D) rhs);
	Rotation3D& operator *= (REF(Rotation3D) rhs);
	Rotation3D& operator *= (REF(Vector3f) rhs);
	Rotation3D& operator *= (float mult);
	Rotation3D& operator /= (REF(Rotation3D) rhs);
	Rotation3D& operator /= (REF(Vector3f) rhs);
	Rotation3D& operator /= (float div);

	 	//Comparison
	bool operator==(REF(Rotation3D) rhs) const;
	bool operator!=(REF(Rotation3D) rhs) const;

	//Static
	// @param lhsRotationType Use rotation type (Radians/Degrees) of the left value.
	static Rotation3D Add(Rotation3D lhs, Rotation3D rhs, bool lhsRotationType = true);
	inline static Rotation3D Subtract(REF(Rotation3D) lhs, REF(Rotation3D) rhs, bool lhsRotationType = true) { return Add(lhs, -rhs);	};
	static Rotation3D Multiply(REF(Rotation3D) lhs, REF(Rotation3D) rhs, bool lhsRotationType = true);
	static Rotation3D Multiply(REF(Rotation3D) lhs, REF(Vector3f) rhs);

	static const Rotation3D calcLookAtRotation(REF(Vector3f) eye, REF(Vector3f) lookAt, bool inRadians = true); //calculates the necessary angle in order to look at one location from another location.
};
//*/
#endif // Rotation_h__
