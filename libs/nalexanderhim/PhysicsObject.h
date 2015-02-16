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

class PhysicsObject :
	public Particle, public Object3D
{
private:
	bool doRefreshPhysPosition = false;//should convert the object position and update the physics position

	//Actions
	inline void RefreshObjectPosition()//update the object position based on the physics position
	{
		mLocalTransform.position = mPosition * (float)SIMULATION_SCALE_FACTOR;
	}
	inline void RefreshPhysicsPosition()//update the physics position based on the object position
	{
		mPosition = mLocalTransform.position * SIMULATION_SCALE;
	}
public:
	PhysicsObject(float initialMass)
		: Particle(initialMass), Object3D()
	{
		doRefreshPhysPosition = true;//refresh at least once
	}
	virtual ~PhysicsObject(){};

	void UpdatePhysics(Time elapsedSeconds)
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
	Transform& getLocalTransformRef()
	{
		doRefreshPhysPosition = true;//record that the physics position will need to be updated
		return mLocalTransform;
	}
};
#endif
