/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Particle.h"
#include "Object3D.h"

#include "PhysicsGlobals.h"

class PhysicsObject :
	public Particle, public Object3D
{
private:
	bool doRefreshPhysPosition = false;//should convert the object position and update the physics position

protected:
	//Actions
	inline void RefreshObjectPosition()//update the object position based on the physics position
	{
		setWorldPosition(mPosition * (float)SIMULATION_SCALE_FACTOR);
		doRefreshPhysPosition = false;//would be redundant at this point
	};
	inline void RefreshPhysicsPosition()//update the physics position based on the object position
	{
		mPosition = getWorldTransform().position * (float)SIMULATION_SCALE;
		doRefreshPhysPosition = false;//would be redundant at this point
	};

public:
	explicit
	PhysicsObject(float initialMass)
		: Particle(initialMass), Object3D()
	{
		doRefreshPhysPosition = true;//refresh at least once to sync them initially
	}
	virtual ~PhysicsObject(){};

	virtual void UpdatePhysics(Time elapsedSeconds)
	{
		//check if object position has been updated
		if (doRefreshPhysPosition)
		{
			doRefreshPhysPosition = false;//has synced
			RefreshPhysicsPosition();
		}

		__super::UpdatePhysics(elapsedSeconds);

		RefreshObjectPosition();
	}

	//Getters
	Transform& refLocalTransform()
	{
		doRefreshPhysPosition = true;//record that the physics position will need to be updated
		return __super::refLocalTransform();
	}
};
#endif
