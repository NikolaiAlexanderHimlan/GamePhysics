#ifndef PhysicsBase_h__
#define PhysicsBase_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ccmccooeyWrapper.h"
#include "FloatFactor.h"
#include "MathDefines.h"
#include "CodingDefines.h"

//Base class for physics objects such as particles and rigid bodies, providing shared function declarations
class PhysicsBase
{
private:
	floatFactor mMass;//values <= 0 indicate infinite mass, since the math will not work with a mass of 0 anyway (no physics calculations)

protected:
	/**
	* Holds the linear position of the particle in
	* world space.
	*/
	Vector3f mPhysicsPosition;

	//Setters
	inline virtual void setMass(real newMass)
	{
		mMass = (float)newMass;
	}


public:
	//Getters
	inline const Vector3f& getPhysicsPosition() const { return mPhysicsPosition;	};
	inline REF(floatFactor) getMass() const
	{
		//TODO: Handle infinite mass
		if (this == nullptr)
			return floatFactor::ZERO;//if this is null, return infinite mass
		return mMass;
	};

	//Setters
	inline void setPhysicsPosition(const Vector3f& newSimulationPos) { mPhysicsPosition = newSimulationPos;	};

	//Properties
	inline bool hasInfiniteMass() const { return mMass <= 0.0f;	};
};
#endif // PhysicsBase_h__
