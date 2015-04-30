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
#include "TimeDefines.h"

class Matrix44r;

//Base class for physics objects such as particles and rigid bodies, providing shared function declarations
class PhysicsBase
{
public:
	struct PhysicsAccumulator //Accumulation of physics effects over the course of a frame.
	{
		Vector3f force; //Holds the accumulated force to be applied at the next integration step.
		Vector3f torque; //Holds the accumulated torque to be applied at the next integration step.
		Vector3f acceleration; // Holds the acceleration of the rigid body.  This value can be used to set acceleration due to gravity(its primary use), or any other constant acceleration.

		void NextFrame()//Clears the accumulation and stores the last frame acceleration.
		{
			//Save LastFrame accumulations
			mLastFrameAcceleration = acceleration;

			//Clear accumulations
			force = Vector3f::zero;
			torque = Vector3f::zero;
			acceleration = Vector3f::zero;
		};

	protected:
		Vector3f mLastFrameAcceleration; //Holds the linear acceleration of the rigid body, for the previous frame.
	};
	typedef PhysicsAccumulator PhysAccum;//Short name.

private:
protected:
	std::string mName = "PhysicsBase";

	floatFactor mMass;//values <= 0 indicate infinite mass, since the math will not work with a mass of 0 anyway (no physics calculations)

	/**
	* Holds the amount of damping applied to linear motion.
	* Damping is required to remove energy added through numerical instability in the integrator.
	*/
	real mDampingLinear = 0.999;

	//Holds the linear position of the particle in world space.
	Vector3f mPhysicsPosition;

	//Holds the linear velocity of the particle in world space.
	Vector3f mVelocityLinear = 0.0f;

	PhysAccum mAccumulator;

	//Setters
	inline virtual void setMass(real newMass) { mMass = (float)newMass;	};

	//Calculations
	//virtual Matrix44r calcTransformMatrix() const = 0;

public:
	//TODO: NOTE: need category name for "Update" type functions
	//Maintainers
	virtual void PhysicsUpdate(Time elapsedSeconds) = 0;
	void PhysicsFixedUpdate(Time elapsedSeconds);//Calls PhysicsUpdate using the simulation timestep enough times to match the actual elapsed time.

	//Getters
	inline REF(Vector3f) getPhysicsPosition() const { return mPhysicsPosition;	};
	inline REF(floatFactor) getMass() const
	{
		//TODO: Handle infinite mass
		if (this == nullptr)
			return floatFactor::ZERO;//if this is null, return infinite mass
		return mMass;
	};

	//Setters
	inline void setPhysicsPosition(REF(Vector3f) newSimulationPos) { mPhysicsPosition = newSimulationPos;	};

	//Properties
	inline bool hasInfiniteMass() const { return mMass <= 0.0f;	};
};
#endif // PhysicsBase_h__
