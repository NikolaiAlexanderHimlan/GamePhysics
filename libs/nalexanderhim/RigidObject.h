#ifndef RigidObject_h__
#define RigidObject_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "RigidBody.h"
#include "Object3D.h"
#include "PhysicsGlobals.h"

//TODO: replace parentage with aggregation, as at this point there is a lot of functionality that would be shared between the ParticleObject and RigidObject, and I can't think of another way to resolve the shared functionality.
class RigidObject :
	public RigidBody, public Object3D
{
private:
	bool doRefreshPhysPosition = false;//should convert the object position and update the physics position

protected:
	//Actions
	inline void RefreshObjectPosition()//update the object position based on the physics position
	{
		setWorldPosition(FROM_SIMULATION_SCALE(mPhysicsPosition));
		doRefreshPhysPosition = false;//would be redundant at this point
	};
	inline virtual void RefreshPhysicsPosition()//update the physics position based on the object position
	{
		mPhysicsPosition = TO_SIMULATION_SCALE(getWorldTransform().position);
		doRefreshPhysPosition = false;//would be redundant at this point
	};

public:
	explicit RigidObject(real initialMass, std::string name = "")
		: RigidBody(initialMass, name), Object3D()
	{
		doRefreshPhysPosition = true;//refresh at least once to sync them initially
	};
	virtual ~RigidObject(){};

	virtual void PhysicsUpdate(Time elapsedSeconds)
	{
		//check if object position has been updated
		if (doRefreshPhysPosition)
		{
			doRefreshPhysPosition = false;//has synced
			RefreshPhysicsPosition();
		};

		__super::PhysicsUpdate(elapsedSeconds);

		RefreshObjectPosition();
	};

	//Getters
	inline Transform& refLocalTransform()
	{
		doRefreshPhysPosition = true;//record that the physics position will need to be updated
		return __super::refLocalTransform();
	};

	//Calculations
	//TODO: WARNING: All the following need to convert their values from graphics to simulation
	//void setBatchPlane(float width, float length, Axis facing = Y, bool inv = false /*Face along the negative edge of the axis*/);
	//void setBatchTriangle(float distUp, float distLeft, float distRight /*TODO: optional color parameters*/);//distance of each corner from the center
	void setBatchCube(float xDimension, float yDimension, float zDimension /*TODO: optional color parameters*/);
	void setBatchSphere(float radius, int numSegments = 8 /*TODO: optional color parameters*/);
};
#endif // RigidObject_h__
