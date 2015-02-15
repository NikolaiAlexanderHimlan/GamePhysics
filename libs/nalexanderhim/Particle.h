/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "Defines.h"
#include "PhysicsDefines.h"
#include "ccmccooeyWrapper.h"
#include "ManagedBase.h"

//Physics Handler
class Particle
	: public ManagedBase
{
private:
	void addToManager();
	void removeFromManager();

	float mMass;//Since 0 mass doesn't work, have values <=0 indicate infinite mass (no physics calculations)
	float mcMassFactor;//DO NOT MODIFY UNLESS mMass CHANGES!

	//Maintainers
	inline void resetMassFactor()
	{
		if (InfiniteMass())
			mcMassFactor = 1.0f / mMass;
		else mcMassFactor = 0.0f;
	}
	inline void resetMomentum(float oldMass)
	{
		//Get old momentum
		Vector3f oldMomentum = mVelocity * oldMass;
		//Calculate new velocity
		mVelocity = oldMomentum * mcMassFactor;
	}

protected:
	/**
	* Holds the linear position of the particle in
	* world space.
	*/
	//TODO: CONSIDER: rename Physics_Position or Simulation_Position
	Vector3f mPosition;
	/**
	* Holds the linear velocity of the particle in
	* world space.
	*/
	Vector3f mVelocity = 0.0f;
	/**
	* Holds the acceleration of the particle. This value
	* can be used to set acceleration due to gravity (its primary
	* use), or any other constant acceleration.
	*/
	Vector3f mAcceleration = 0.0f;

	/**
	* Holds the amount of damping applied to linear
	* motion. Damping is required to remove energy added
	* through numerical instability in the integrator.
	*/
	udouble mDamping = 0.999;

	void UpdatePosition(Time elapsedTime)
	{
		//Update Position
		mPosition += //previous position
#ifdef COMPLEX_POSITION
			//floating point powers are expensive, thus the #ifdef
			(mAcceleration*0.5f*powf((float)elapsedTime, 2)) + //movement due to acceleration
#endif
			(mVelocity*(float)elapsedTime);//movement due to velocity
	}
	void UpdateVelocity(Time elapsedTime)
	{
		//NOTE: expensive pow calculation, details (Ian Millington, pg. 57)
		//Update Velocity
		mVelocity = (mVelocity * (float)pow(mDamping, elapsedTime)) + (mAcceleration*(float)elapsedTime);
	}

	//Getters
	inline float getMassFactor() const { return mcMassFactor;	};

	//Setters
	inline void setMass(float newMass)
	{
		float oldMass = mMass;
		//float oldMassFactor = mcMassFactor;
		mMass = newMass;

		resetMassFactor();

		resetMomentum(oldMass);
		//resetMomentum(oldMassFactor);
	}
	void setMomentum(const Vector3f& newMomentum);

public:
	Particle(void);
	virtual ~Particle();

	inline void Update(Time elapsedTime)
	{
		UpdatePosition(elapsedTime);

		UpdateVelocity(elapsedTime);

		//Update Physics
	}

	//Getters
	inline float getMass() const { return mMass;	};//TODO: Handle infinite mass
	Vector3f Simulation_getPosition() const;

	//Setters
	void Simulation_setPosition(const Vector3f& newSimulationPos);
	
	//Properties
	inline bool InfiniteMass() const { return mMass <= 0.0f;	};

	//Actions
	void ApplyForce(const Vector3f& forceVector);
};
#endif
