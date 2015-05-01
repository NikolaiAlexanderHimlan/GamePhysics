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

		REF(Vector3f) LastFrameAcceleration(void) const { return mLastFrameAcceleration;	};
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

	/**
	* A body can be put to sleep to avoid it being updated by the
	* integration functions or affected by collisions with the world.
	*/
	bool mIsAwake;
	/**
	* Some bodies may never be allowed to fall asleep.
	* User controlled bodies, for example, should always be awake.
	*/
	bool mCanSleep;

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

	//GameLoop

	//Setters
	inline virtual void setMass(real newMass) { mMass = (float)newMass;	};

	//Calculations
	//virtual Matrix44r calcTransformMatrix() const = 0;

	//Actions
	virtual void clearPhysics() = 0;//Clear stored physics values in preparation for the next frame.
	// Clears the accumulated physics for the frame. This will be called automatically after each integration step.
	void clearAccumulators();

public:
	//TODO: NOTE: need category name for "Update" type functions
	//GameLoop
	virtual void PhysicsUpdate(Time elapsedSeconds) = 0;
	void PhysicsFixedUpdate(Time elapsedSeconds);//Calls PhysicsUpdate using the simulation timestep enough times to match the actual elapsed time.

	//Getters
	inline REF(std::string) getName() const {
		static const std::string NULL_PARTICLE_NAME = "null physics";
		if (this == nullptr)
			return NULL_PARTICLE_NAME;
		return mName;
	};
	// @returns true if the body is awake and responding to integration.
	bool getAwake() const { return mIsAwake;	};
	// @returns true if the body is allowed to go to sleep at any time.
	bool getCanSleep() const { return mCanSleep;	};
	inline REF(Vector3f) getPhysicsPosition() const { return mPhysicsPosition;	};
	inline Vector3f& refPhysicsPosition() { return mPhysicsPosition;	};
	inline REF(floatFactor) getMass() const {
		if (this == nullptr)//can safely call on a null object, for contact resolution.
			return floatFactor::ZERO;//if this is null, return infinite mass
		return mMass;
	};
	/**
	* Gets the current linear damping value.
	* @return The current linear damping value.
	*/
	real getDampingLinear() const;
	/**
	* Fills the given vector with the velocity of the rigid body.
	* @param velocity A pointer to a vector into which to write the velocity.
	* The velocity is given in world local space.
	*/
	void getVelocityLinear(OUT_PARAM(Vector3f) velocity) const;
	/**
	* Gets the velocity of the rigid body.
	* @return The velocity of the rigid body.
	* The velocity is given in world local space.
	*/
	inline REF(Vector3f) getVelocityLinear() const {
		if (this == nullptr)//can safely call on a null object, for contact resolution.
			return Vector3f::zero;//if this is null return 0 vector
		return mVelocityLinear;
	};

	/**
	* Fills the given vector with the acceleration of the rigid body.
	* @param acceleration A pointer to a vector into which to write the acceleration.
	* The acceleration is given in world local space.
	*/
	void getAcceleration(OUT_PARAM(Vector3f) acceleration) const;
	/**
	* Gets the acceleration of the rigid body.
	* @return The acceleration of the rigid body.
	* The acceleration is given in world local space.
	*/
	Vector3f getAcceleration() const;
	/**
	* Fills the given vector with the current accumulated value for linear acceleration.
	* The acceleration accumulators are set during the integration step.
	* They can be read to determine the rigid body's acceleration over the last integration step.
	* The linear acceleration is given in world space.
	* @param linearAcceleration A pointer to a vector to receive the linear acceleration data.
	*/
	void getLastFrameAcceleration(OUT_PARAM(Vector3f) linearAcceleration) const;
	/**
	* Gets the current accumulated value for linear acceleration.
	* The acceleration accumulators are set during the integration step.
	* They can be read to determine the rigid body's acceleration over the last integration step.
	* The linear acceleration is given in world space.
	* @return The rigid body's linear acceleration.
	*/
	Vector3f getLastFrameAcceleration() const;

	//Setters
	/**
	* Sets the awake state of the body. If the body is set to be not awake, then its velocities are also canceled,
	* since a moving body that is not awake can cause problems in the simulation.
	* @param awake The new awake state of the body.
	*/
	void setAwake(const bool awake = true);
	/**
	* Sets whether the body is ever allowed to go to sleep. Bodies under the player's control,
	* or for which the set of transient forces applied each frame are not predictable, should be kept awake.
	* @param canSleep Whether the body can now be put to sleep.
	*/
	void setCanSleep(const bool canSleep = true);
	inline void setPhysicsPosition(REF(Vector3f) newSimulationPos) { mPhysicsPosition = newSimulationPos;	};
	/**
	* Sets the linear damping for the rigid body.
	* @param linearDamping The speed that velocity is shed from the rigid body.
	*/
	void setDampingLinear(const real linearDamping);
	/**
	* Sets the velocity of the rigid body.
	* @param newVelocity The new velocity of the rigid body. The velocity is given in world space.
	*/
	inline void setVelocityLinear(REF(Vector3f) newVelocity) { mVelocityLinear = newVelocity; };
	/**
	* Sets the velocity of the rigid body by component. The velocity is given in world space.
	* @param x The x coordinate of the new velocity of the rigid body.
	* @param y The y coordinate of the new velocity of the rigid body.
	* @param z The z coordinate of the new velocity of the rigid body.
	*/
	void setVelocityLinear(const real x, const real y, const real z);
	/**
	* Sets the constant acceleration of the rigid body.
	* @param acceleration The new acceleration of the rigid body.
	*/
	void setAcceleration(REF(Vector3f) acceleration);
	/**
	* Sets the constant acceleration of the rigid body by component.
	* @param x The x coordinate of the new acceleration of the rigid body.
	* @param y The y coordinate of the new acceleration of the rigid body.
	* @param z The z coordinate of the new acceleration of the rigid body.
	*/
	void setAcceleration(const real x, const real y, const real z);

	//Properties
	inline bool hasInfiniteMass() const { return mMass <= 0.0f;	};
	inline float getSpeed() const { return mVelocityLinear.Length();	};
	Vector3f getMomentumLinear() const;

	//Modifiers
	void setMomentumLinear(REF(Vector3f) newMomentum);

	//Calculations
	/**
	* Converts the given point from world space into the body's local space.
	* @param point The point to covert, given in world space.
	* @return The converted point, in local space.
	*/
	virtual Vector3f calcPointInLocalSpace(REF(Vector3f) point) const = 0;
	/**
	* Converts the given point from world space into the body's local space.
	* @param point The point to covert, given in local space.
	* @return The converted point, in world space.
	*/
	virtual Vector3f calcPointInWorldSpace(REF(Vector3f) point) const = 0;
	/**
	* Converts the given direction from world space into the body's local space.
	* @note When a direction is converted between frames of reference, there is no translation required.
	* @param direction The direction to covert, given in world space.
	* @return The converted direction, in local space.
	*/
	virtual Vector3f calcDirectionInLocalSpace(REF(Vector3f) direction) const = 0;
	/**
	* Converts the given direction from world space into the body's local space.
	* @note When a direction is converted between frames of reference, there is no translation required.
	* @param direction The direction to covert, given in local space.
	* @return The converted direction, in world space.
	*/
	virtual Vector3f calcDirectionInWorldSpace(REF(Vector3f) direction) const = 0;

	//Actions
	// Applies the given change in velocity.
	bool addVelocityLinear(REF(Vector3f) deltaVelocity);
	/**
	* Adds the given force to center of mass of the rigid body.
	* The force is expressed in world-coordinates.
	* @param force The force to apply.
	*/
	virtual bool addForce(REF(Vector3f) forceVector) = 0;
	// Creates an instantaneous change in velocity over a single frame.
	virtual bool addImpulse(REF(Vector3f) impulseVector) = 0;

	//Refresh
};
#endif // PhysicsBase_h__
