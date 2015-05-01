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

	//Setters
	inline void setMass(real newMass)
	{
		floatFactor oldMass = getMass();
		__super::setMass(newMass);
		RecalculateMomentum(oldMass);
	};

public:
	explicit Particle(real initialMass, std::string name = "")
		: PhysicsBase(initialMass, name)
	{
	};
	virtual ~Particle()
	{
		delete mpBounds;
		mpBounds = nullptr;
	};

	//Getters
	inline REF(Bounding) getBounds() const { return *SAFE_GET(mpBounds, new Bounding());	};

	//Setters
	inline void setBounds(Bounding* newBounds) { SAFE_ASSIGN(mpBounds) = newBounds;	};

	//Properties
	inline Vector3f getForceTotal() const
	{ return mForceAccum + (mAccelerationConstant * getMass());	};

	//Actions
	// Applies the given change of force.
	inline bool addForce(REF(Vector3f) forceVector){
		if (hasInfiniteMass()) return false;//objects with infinite mass cannot have forces acting on them
		mForceAccum += forceVector;
		return true;//applied force successfully
	};
	inline bool addImpulse(REF(Vector3f) impulseVector)
	{
		//TODO: verify that infinite mass objects cannot receive impulse
		if (hasInfiniteMass()) return false;//objects with infinite mass cannot have impulses acting on them

		mVelocityLinear += impulseVector * getMass().getFactor();

		return true;//applied impulse successfully
	};
};
#endif
