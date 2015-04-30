#ifndef RigidBody_h__
#define RigidBody_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "PhysicsBase.h"

//TODO: CONSIDER: move to .cpp
#include "IntertiaTensor.h"
#include "Quaternion.h"
#include "Matrix44r.h"

class RigidBody :
	public PhysicsBase
{
	//TODO: EulerTransform class, separate transform object using Quaternion, so as to not mess up the existing Transform object.
protected:
	std::string mName = "RigidBody";

	/**
	* A body can be put to sleep to avoid it being updated by the
	* integration functions or affected by collisions with the world.
	*/
	bool isAwake;

	/**
	* Some bodies may never be allowed to fall asleep.
	* User controlled bodies, for example, should always be awake.
	*/
	bool canSleep;

	/**
	* Holds the inverse of the body's inertia tensor.
	* The inertia tensor provided must not be degenerate
	* (that would mean the body had zero inertia for spinning along one axis).
	* As long as the tensor is finite, it will be invertible.
	* The inverse tensor is used for similar reasons to the use of inverse mass.
	* The inertia tensor, unlike the other variables that define a rigid body, is given in body space.
	*
	* @see inverseMass
	*/
	IntertiaTensor mInverseInertiaTensor;

	/**
	* Holds the amount of damping applied to angular motion.
	* Damping is required to remove energy added through numerical instability in the integrator.
	*/
	real mDampingAngular = 0.999;

	// Holds the angular orientation of the rigid body in world space.
	Quaternion mOrientation;

	// Holds the angular velocity, or rotation, or the rigid body in world space.
	Vector3f mRotationVel;

	//TODO: WARNING: Unknown! Should these be variables or calculated properties?
	//Holds the amount of motion of the body. This is a recently weighted mean that can be used to put a body to sleep.
	//real motion;
	
	//Calculations
	virtual Matrix44r calcTransformMatrix() const;

public:
	RigidBody();
	virtual ~RigidBody();

	//Getters
	/**
	* Copies the current inertia tensor of the rigid body into the given matrix.
	*
	* @param inertiaTensor A pointer to a matrix to hold the current inertia tensor of the rigid body.
	* The inertia tensor is expressed in the rigid body's local space.
	*/
	void getInertiaTensor(OUT_PARAM(Matrix33r) inertiaTensor) const;

	/**
	* Gets a copy of the current inertia tensor of the rigid body.
	*
	* @return A new matrix containing the current inertia tensor.
	* The inertia tensor is expressed in the rigid body's local space.
	*/
	Matrix33r getInertiaTensor() const;
	/**
	* Copies the current inverse inertia tensor of the rigid body into the given matrix.
	*
	* @param inverseInertiaTensor A pointer to a matrix to hold
	* the current inverse inertia tensor of the rigid body.
	* The inertia tensor is expressed in the rigid body's local space.
	*/
	void getInverseInertiaTensor(OUT_PARAM(Matrix33r)inverseInertiaTensor) const;

	/**
	* Gets a copy of the current inverse inertia tensor of the rigid body.
	*
	* @return A new matrix containing the current inverse inertia tensor.
	* The inertia tensor is expressed in the rigid body's local space.
	*/
	Matrix33r getInverseInertiaTensor() const;

	//Setters
	/**
	* Sets the inertia tensor for the rigid body.
	*
	* @param inertiaTensor The inertia tensor for the rigid body.
	* This must be a full rank matrix and must be invertible.
	*
	* @warning This invalidates internal data for the rigid body.
	* Either an integration function, or the calculateInternals
	* function should be called before trying to get any settings from the rigid body.
	*/
	void setInertiaTensor(REF(Matrix33r) inertiaTensor);
	/**
	* Sets the inverse intertia tensor for the rigid body.
	*
	* @param inverseInertiaTensor The inverse inertia tensor for the rigid body.
	* This must be a full rank matrix and must be invertible.
	*
	* @warning This invalidates internal data for the rigid body.
	* Either an integration function, or the calculateInternals
	* function should be called before trying to get any settings from the rigid body.
	*/
	void setInverseInertiaTensor(REF(Matrix33r) inverseInertiaTensor);

	//Calculations
	//Gets the inertia tensor of the rigid body expressed in world space.
	void getInertiaTensorWorld(OUT_PARAM(Matrix33r) inertiaTensor) const;
	Matrix33r getInertiaTensorWorld() const;

	/**
	* The inverse inertia tensor of the body in world space.
	* @see inverseInertiaTensor
	*/
	void calcInertiaTensorWorld(OUT_PARAM(Matrix33r) inertiaTensor) const;
	Matrix33r calcInverseInertiaTensorWorld() const;
};

#endif // RigidBody_h__
