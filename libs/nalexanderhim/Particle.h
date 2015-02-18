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
#include "PhysicsGlobals.h"
#include "ccmccooeyWrapper.h"
#include "ManagedBase.h"

//Physics Handler
class Particle
	: public ManagedBase
{
private:
	float mMass;//Since 0 mass doesn't work, have values <=0 indicate infinite mass (no physics calculations)
	float mcMassFactor;//DO NOT MODIFY UNLESS mMass CHANGES!

	//Maintainers
	inline void RecalculateMassFactor()
	{
		if (!InfiniteMass())
			mcMassFactor = 1.0f / mMass;
		else mcMassFactor = 0.0f;
	}
	inline void RecalculateMomentum(float oldMass)
	{
		//Get old momentum
		Vector3f oldMomentum = mVelocity * oldMass;
		//Calculate new velocity
		mVelocity = oldMomentum * mcMassFactor;
	}

protected:
	virtual ManagerBase* getManager() const;
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

	void UpdatePosition(Time elapsedSeconds)
	{
		//Update Position
		mPosition += //previous position
#ifdef COMPLEX_POSITION
			//floating point powers are expensive, thus the #ifdef
			(mAcceleration*0.5f*powf((float)elapsedSeconds, 2)) + //movement due to acceleration
#endif
			(mVelocity*(float)elapsedSeconds);//movement due to velocity
	}
	void UpdateVelocity(Time elapsedSeconds)
	{
		if (InfiniteMass()) return;//velocity does not change for an object of infinite mass

		//NOTE: expensive pow calculation, details (Ian Millington, pg. 57)
		//Update Velocity

		//Acceleration
		mVelocity += (mAcceleration*(float)elapsedSeconds);

		//Damping
		mVelocity *= (float)pow(mDamping, elapsedSeconds);

		//Clear Forces? (need to reapply force every frame)
		ClearForce();
	}

	//Getters
	inline float getMassFactor() const { return mcMassFactor;	};

	//Setters
	inline void setMass(float newMass)
	{
		float oldMass = mMass;
		//float oldMassFactor = mcMassFactor;
		mMass = newMass;

		RecalculateMassFactor();

		RecalculateMomentum(oldMass);
		//recalculateMomentum(oldMassFactor);
	}

	//Actions
	inline void ClearForce() { SetForce(Vector3f(0.0f));	};
	inline bool setForce(const Vector3f& forceVector)
	{
		if (InfiniteMass()) return false;//objects with infinite mass cannot have forces acting on them

		mAcceleration = forceVector * mcMassFactor;

		return true;//applied force successfully
	}

public:
	Particle(float initialMass)
	{
		setMass(initialMass);
	}
	virtual ~Particle(){};

	//Maintainers
	virtual inline void UpdatePhysics(Time elapsedSeconds)
	{
		UpdatePosition(elapsedSeconds);

		//TODO: decide if velocity should be updated in Physics(elapsed time) or Force(duration)
		UpdateVelocity(elapsedSeconds);

		//Update Physics
	}

	//Getters
	Vector3f Simulation_getPosition() const { return mPosition;	};
	inline float getMass() const { return mMass;	};//TODO: Handle infinite mass
	Vector3f getVelocity() const { return mVelocity;	};
	Vector3f getMomentum() const;

	//Setters
	void setVelocity(const Vector3f& newVelocity) { mVelocity = newVelocity;	};
	inline void Simulation_setPosition(const Vector3f& newSimulationPos) { mPosition = newSimulationPos;	};
	void setMomentum(const Vector3f& newMomentum);
	
	//Properties
	inline bool InfiniteMass() const { return mMass <= 0.0f;	};
	inline float Speed() const { return mVelocity.length();	};

	//Actions
	inline bool AddForce(const Vector3f& forceVector)
	{
		if (InfiniteMass()) return false;//objects with infinite mass cannot have forces acting on them

		mAcceleration += forceVector * mcMassFactor;

		return true;//applied force successfully
	}
};
#endif
