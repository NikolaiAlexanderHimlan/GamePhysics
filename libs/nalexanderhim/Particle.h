/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "ManagedBase.h"
#include "PhysicsBase.h"
#include "TimeDefines.h"
#include "PhysicsDefines.h"
#include "ccmccooeyWrapper.h"
#include "FloatFactor.h"
#include "Boundings.h"
#include "CodingDefines.h"

//Physics Handler
class Particle
	: public ManagedBase
	, public PhysicsBase
{
private:
	//Refresh
	inline void RecalculateMomentum(real oldMass)
	{
		//Get old momentum
		Vector3f oldMomentum = mVelocityLinear * (float)oldMass;
		//Calculate new velocity
		mVelocityLinear = oldMomentum * getMass().getFactor();
	};

protected:
	virtual ManagerBase* getManager() const;

	std::string mName = "Particle";

	//NOTE: reason it is a pointer is to allow subclasses to be used.
	Bounding* mpBounds = new Bounding();//defines the physics boundary of the particle

	//GameLoop
	inline void UpdatePosition(Time elapsedSeconds)
	{
		//Update Position
		mPhysicsPosition += //previous position
#ifdef COMPLEX_POSITION
			//floating point powers are expensive, thus the #ifdef
			(mAcceleration*0.5f*powf((float)elapsedSeconds, 2)) + //movement due to acceleration
#endif
			(mVelocityLinear*(float)elapsedSeconds);//movement due to velocity
	};
	inline void UpdateVelocity(Time elapsedSeconds)
	{
		if (hasInfiniteMass()) return;//velocity does not change for an object of infinite mass

		//NOTE: expensive pow calculation, details (Ian Millington, pg. 57)
		//Update Velocity

		//TODO: decide if velocity should be updated in Physics(elapsed time) or Force(duration)
		//TODO: CONSIDER: should the acceleration be applied when adding force, which would allow forces to be applied over a separate time
		//NOTE: damping would stay here (unless moved to a damping force generator) and clear forces and mAcceleration wouldn't be necessary (unless I wanted to save up the total force over a frame or use acceleration in the velocity calculation)
		//Acceleration
		//TODO: NOTE: acceleration recalculated
		mVelocityLinear += (mAccumulator.acceleration*(float)elapsedSeconds);

		//Damping
		mVelocityLinear *= (float)pow(mDampingLinear, elapsedSeconds);
		//HACK: damping disabled in space

		//Clear Forces? (need to reapply force every frame)
		clearForce();
	};

	//Getters

	//Setters
	inline void setMass(real newMass)
	{
		floatFactor oldMass = getMass();
		__super::setMass(newMass);
		RecalculateMomentum(oldMass);
	};

	//Actions
	inline bool setForce(REF(Vector3f) forceVector)
	{
		if (hasInfiniteMass()) return false;//objects with infinite mass cannot have forces acting on them

		//TODO: NOTE: acceleration recalculated
		mAccumulator.acceleration = forceVector * getMass().getFactor();

		return true;//applied force successfully
	};
	inline void clearForce() { setForce(Vector3f(0.0f));	};

public:
	explicit Particle(real initialMass, std::string name = "")
	{
		setMass(initialMass);

		if (name != "")
			mName = name;
	};
	virtual ~Particle()
	{
		delete mpBounds;
		mpBounds = nullptr;
	};

	//GameLoop
	virtual inline void PhysicsUpdate(Time elapsedSeconds)
	{
		UpdatePosition(elapsedSeconds);

		UpdateVelocity(elapsedSeconds);

		mAccumulator.NextFrame();

		//Update Physics
	};

	//Getters
	inline REF(Bounding) getBounds() const { return *SAFE_GET(mpBounds, new Bounding());	};

	//Setters
	inline void setBounds(Bounding* newBounds) { SAFE_ASSIGN(mpBounds) = newBounds;	};

	//Properties
	inline Vector3f getForce() const { return mAccumulator.force + (mAccumulator.acceleration * getMass());	};

	//Actions
	// Applies the given change of force.
	inline bool addForce(REF(Vector3f) forceVector)
	{
		if (hasInfiniteMass()) return false;//objects with infinite mass cannot have forces acting on them

		//TODO: NOTE: acceleration recalculated
		mAccumulator.acceleration += forceVector * getMass().getFactor();

		return true;//applied force successfully
	};
	inline bool addImpulse(REF(Vector3f) impulseVector)
	{
		//TODO: verify that infinite mass objects cannot receive impulse
		if (hasInfiniteMass()) return false;//objects with infinite mass cannot have impulses acting on them

		mVelocityLinear += impulseVector * getMass().getFactor();

		return true;//applied impulse successfully
	};
	inline void clearPhysics() { clearForce(); setVelocityLinear(0.0f);	};//HACK: publicly accessible
};
#endif
