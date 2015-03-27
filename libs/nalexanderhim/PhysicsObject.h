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

//HACK: WARNING: mpBounds does not account for scale!
//TODO: CONSIDER: professor proposed that PhysicsObject should contain instead of subclass Particle/Object3D.  This would allow for more controlled update/sync of position between the 2.
class PhysicsObject :
	public Particle, public Object3D
{
private:
	bool doRefreshPhysPosition = false;//should convert the object position and update the physics position

protected:
	//Actions
	inline void RefreshObjectPosition()//update the object position based on the physics position
	{
		setWorldPosition(FROM_SIMULATION_SCALE(mPosition));
		doRefreshPhysPosition = false;//would be redundant at this point
	};
	inline void RefreshPhysicsPosition()//update the physics position based on the object position
	{
		mPosition = TO_SIMULATION_SCALE(getWorldTransform().position);
		doRefreshPhysPosition = false;//would be redundant at this point
	};

public:
	explicit PhysicsObject(float initialMass, std::string name = "")
		: Particle(initialMass, name), Object3D()
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

	//Calculations
	//TODO: WARNING: All the following need to convert their values from graphics to simulation
	inline void setBatchPlane(float width, float length, Axis facing = Y, bool inv = false /*Face along the negative edge of the axis*/)
	{
		setBounds(new PlaneBounding(width, length, Vector3f::AxisNormal(facing) *(inv ? -1.0f : 1.0f)));
		Object3D::setBatchPlane(width, length, facing, inv);
	};
	inline void setBatchTriangle(float distUp, float distLeft, float distRight /*TODO: optional color parameters*/)//distance of each corner from the center
	{
		setBounds(new PlaneBounding(distLeft + distRight, distUp, FORWARD));
		Object3D::setBatchTriangle(distUp, distLeft, distRight);
	};
	inline void setBatchCube(float xDimension, float yDimension, float zDimension /*TODO: optional color parameters*/)
	{
		setBounds(new CubeBounding(CubeVolume(xDimension, zDimension, yDimension)));
		Object3D::setBatchCube(xDimension, yDimension, zDimension);
	};
	inline void setBatchSphere(float radius, int numSegments = 8 /*TODO: optional color parameters*/)
	{
		setBounds(new SphereBounding(radius));
		Object3D::setBatchSphere(radius, numSegments);
	};
};
#endif
