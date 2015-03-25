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
#include "FloatFactor.h"
#include "Boundings.h"

//Physics Handler
class Particle
	: public ManagedBase
{
private:
	floatFactor mMass;//values <= 0 indicate infinite mass, since the math will not work with a mass of 0 anyway (no physics calculations)

	//Maintainers
	inline void RecalculateMomentum(float oldMass)
	{
		//Get old momentum
		Vector3f oldMomentum = mVelocity * oldMass;
		//Calculate new velocity
		mVelocity = oldMomentum * mMass.getFactor();
	}

protected:
	virtual ManagerBase* getManager() const;

	Bounding* mBounds = new Bounding();//defines the physics boundary of the particle

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

	//Maintainers
	inline void UpdatePosition(Time elapsedSeconds)
	{
		//Update Position
		mPosition += //previous position
#ifdef COMPLEX_POSITION
			//floating point powers are expensive, thus the #ifdef
			(mAcceleration*0.5f*powf((float)elapsedSeconds, 2)) + //movement due to acceleration
#endif
			(mVelocity*(float)elapsedSeconds);//movement due to velocity
	}
	inline void UpdateVelocity(Time elapsedSeconds)
	{
		if (InfiniteMass()) return;//velocity does not change for an object of infinite mass

		//NOTE: expensive pow calculation, details (Ian Millington, pg. 57)
		//Update Velocity

		//TODO: decide if velocity should be updated in Physics(elapsed time) or Force(duration)
		//TODO: CONSIDER: should the acceleration be applied when adding force, which would allow forces to be applied over a separate time
		//NOTE: damping would stay here (unless moved to a damping force generator) and clear forces and mAcceleration wouldn't be necessary (unless I wanted to save up the total force over a frame or use acceleration in the velocity calculation)
		//Acceleration
		mVelocity += (mAcceleration*(float)elapsedSeconds);

		//Damping
		//mVelocity *= (float)pow(mDamping, elapsedSeconds);
		//HACK: damping disabled in space

		//Clear Forces? (need to reapply force every frame)
		clearForce();
	}

	//Getters

	//Setters
	inline void setMass(float newMass)
	{
		floatFactor oldMass = mMass;
		mMass = newMass;

		RecalculateMomentum(oldMass);
	}

	inline void setBounds(Bounding* newBounds)
	{
		delete mBounds;
		mBounds = newBounds;
	}

	//Actions
	inline bool setForce(const Vector3f& forceVector)
	{
		if (InfiniteMass()) return false;//objects with infinite mass cannot have forces acting on them

		mAcceleration = forceVector * mMass.getFactor();

		return true;//applied force successfully
	}
	inline void clearForce() { setForce(Vector3f(0.0f));	};

public:
	Particle(float initialMass)
	{
		setMass(initialMass);
	}
	virtual ~Particle()
	{
		delete mBounds;
		mBounds = nullptr;
	};

	//Maintainers
	virtual inline void UpdatePhysics(Time elapsedSeconds)
	{
		UpdatePosition(elapsedSeconds);

		UpdateVelocity(elapsedSeconds);

		//Update Physics
	}

	//Getters
	//Simulation_ prefix is to differentiate from graphical position
	inline const Vector3f& getPhysicsPosition() const { return mPosition;	};
	inline const float& getMass() const { return mMass;	};//TODO: Handle infinite mass
	inline const Vector3f& getVelocity() const { return mVelocity;	};

	//Setters
	inline void setPhysicsPosition(const Vector3f& newSimulationPos) { mPosition = newSimulationPos;	};
	inline void setVelocity(const Vector3f& newVelocity) { mVelocity = newVelocity;	};
	
	//Properties
	inline bool InfiniteMass() const { return mMass <= 0.0f;	};
	inline float getSpeed() const { return mVelocity.length();	};
	Vector3f getMomentum() const;
	inline Vector3f getForce() const { return mAcceleration * getMass();	};

	//Manipulators
	void setMomentum(const Vector3f& newMomentum);

	//Actions
	inline bool AddForce(const Vector3f& forceVector)
	{
		if (InfiniteMass()) return false;//objects with infinite mass cannot have forces acting on them

		mAcceleration += forceVector * mMass.getFactor();

		return true;//applied force successfully
	}
	inline void clearPhysics() { clearForce(); setVelocity(0.0f);	};//HACK: publicly accessible
};
#endif
