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
#include "ManagedBase.h"

//TODO: CONSIDER: move to .cpp
#include "IntertiaTensor.h"
#include "Quaternion.h"
#include "Matrix44r.h"
#include "Boundings.h"

class RigidBody :
	public PhysicsBase
	, public ManagedBase
{
public:
	//HACK: rather than messing with my fairly complicated Boundings class, making a simplified version which is specific to RigidBody.
	struct RigidBounds {
		Vector3f direction;
		float width, length, height;
		Bounding::BoundType collider;

		void setAll(float newVal) {
			width = newVal;
			length = newVal;
			height = newVal;
		};

		static RigidBounds BoundsPlane(REF(Vector3f) normal, float width, float length);
		static RigidBounds BoundsSphere(float diameter) {
			RigidBounds newBounds;
			newBounds.collider = Bounding::SPHERE;
			newBounds.setAll(diameter);
			return newBounds;
		};
		static RigidBounds BoundsBox(float width, float length, float height) {
			RigidBounds newBounds;
			newBounds.collider = Bounding::CUBE;
			newBounds.width = width;
			newBounds.length = length;
			newBounds.height = height;
			return newBounds;
		};
	};
	//TODO: EulerTransform class, separate transform object using Quaternion, so as to not mess up the existing Transform object.
protected:
	virtual ManagerBase* getManager() const;

	std::string mName = "RigidBody";

	RigidBounds mBounds;

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
	Vector3f mRotationVelocity;

	//Holds the accumulated torque to be applied at the next integration step.
	Vector3f mTorqueAccum;

	//TODO: WARNING: Unknown! Should these be variables or calculated properties?
	//Holds the amount of motion of the body. This is a recently weighted mean that can be used to put a body to sleep.
	//real motion;
	
	//Calculations
	virtual Matrix44r calcTransformMatrix() const
	{ return getRigidTransform();	};

	//Actions
	void clearAccumulators()
	{
		__super::clearAccumulators();
		mTorqueAccum = Vector3f::zero;
	};

public:
	explicit RigidBody(real initialMass, std::string name = "")
		: PhysicsBase(initialMass, name)
	{
	};
	virtual ~RigidBody()
	{
	};

	//GameLoop
	inline virtual void PhysicsUpdate(Time elapsedSeconds)
	{
		//TODO: override UpdatePosition and UpdateVelocity to take torque and rotational velocity into account.
		UpdatePosition(elapsedSeconds);

		UpdateVelocity(elapsedSeconds);

		//Update Physics
		__super::PhysicsUpdate(elapsedSeconds);
	};

	//Getters
	REF(RigidBounds) getBounds(void) { return mBounds;	};
	/**
	* Fills the given quaternion with the current value of the rigid body's orientation.
	* @param orientation A pointer to a quaternion to receive the orientation data.
	*/
	void getOrientation(OUT_PARAM(Quaternion) orientation) const;
	/**
	* Gets the orientation of the rigid body.
	* @return The orientation of the rigid body.
	*/
	REF(Quaternion) getOrientation() const { return mOrientation;	};

	/**
	* Copies the current inertia tensor of the rigid body into the given matrix.
	* @param inertiaTensor A pointer to a matrix to hold the current inertia tensor of the rigid body.
	* The inertia tensor is expressed in the rigid body's local space.
	*/
	void getInertiaTensor(OUT_PARAM(Matrix33r) inertiaTensor) const;
	/**
	* Gets a copy of the current inertia tensor of the rigid body.
	* @return A new matrix containing the current inertia tensor.
	* The inertia tensor is expressed in the rigid body's local space.
	*/
	Matrix33r getInertiaTensor() const;
	/**
	* Copies the current inverse inertia tensor of the rigid body into the given matrix.
	* @param inverseInertiaTensor A pointer to a matrix to hold the current inverse inertia tensor of the rigid body.
	* The inertia tensor is expressed in the rigid body's local space.
	*/
	void getInverseInertiaTensor(OUT_PARAM(Matrix33r) inverseInertiaTensor) const;
	/**
	* Gets a copy of the current inverse inertia tensor of the rigid body.
	* @return A new matrix containing the current inverse inertia tensor.
	* The inertia tensor is expressed in the rigid body's local space.
	*/
	Matrix33r getInverseInertiaTensor() const;
	/**
	* Fills the given vector with the rotation of the rigid body.
	* @param rotation A pointer to a vector into which to write the rotation.
	* The rotation is given in world local space.
	*/
	void getRotationVelocity(OUT_PARAM(Vector3f) rotation) const;
	/**
	* Gets the rotation of the rigid body.
	* @return The rotation of the rigid body.
	* The rotation is given in world local space.
	*/
	Vector3f getRotationVelocity() const;
	/**
	* Gets the current angular damping value.
	* @return The current angular damping value.
	*/
	real getAngularDamping() const;

	//Setters
	void setBounds(REF(RigidBounds) newBounds) { mBounds = newBounds;	};
	void setOrientation(REF(Quaternion) orientation);
	/**
	* Sets the inertia tensor for the rigid body.
	* @param inertiaTensor The inertia tensor for the rigid body.
	* This must be a full rank matrix and must be invertible.
	* @warning This invalidates internal data for the rigid body.
	* Either an integration function, or the calculateInternals function should be called before trying to get any settings from the rigid body.
	*/
	void setInertiaTensor(REF(Matrix33r) inertiaTensor);
	/**
	* Sets the inverse inertia tensor for the rigid body.
	* @param inverseInertiaTensor The inverse inertia tensor for the rigid body.
	* This must be a full rank matrix and must be invertible.
	* @warning This invalidates internal data for the rigid body.
	* Either an integration function, or the calculateInternals function should be called before trying to get any settings from the rigid body.
	*/
	void setInverseInertiaTensor(REF(Matrix33r) inverseInertiaTensor);
	/**
	* Sets the rotation of the rigid body.
	* @param rotation The new rotation of the rigid body.
	* The rotation is given in world space.
	*/
	void setRotationVelocity(REF(Vector3f) rotation);
	/**
	* Sets the rotation of the rigid body by component.
	* The rotation is given in world space.
	* @param x The x coordinate of the new rotation of the rigid body.
	* @param y The y coordinate of the new rotation of the rigid body.
	* @param z The z coordinate of the new rotation of the rigid body.
	*/
	void setRotationVelocity(const real x, const real y, const real z);
	/**
	* Sets the angular damping for the rigid body.
	* @param angularDamping The speed that rotation is shed from the rigid body.
	* @see setLinearDamping
	*/
	void setAngularDamping(const real angularDamping);
	/**
	* Sets the orientation of the rigid body.
	* @param orientation The new orientation of the rigid body.
	* @note The given orientation does not need to be normalized, and can be zero.
	* This function automatically constructs a valid rotation quaternion with (0,0,0,0) mapping to (1,0,0,0).
	*/

	//Properties
	/**
	* Fills the given matrix with a transformation representing the rigid body's position and orientation.
	* @note Transforming a vector by this matrix turns it from the body's local space to world space.
	* @param transform A pointer to the matrix to fill.
	*/
	void getRigidTransform(OUT_PARAM(Matrix44r) transform) const;
	/**
	* Gets a transformation representing the rigid body's position and orientation.
	* @note Transforming a vector by this matrix turns it from the body's local space to world space.
	* @return The transform matrix for the rigid body.
	*/
	Matrix44r getRigidTransform() const
	{
		Matrix44r tranform;
		getRigidTransform(&tranform);
		return tranform;
	};
	/**
	* Fills the given matrix data structure with a transformation representing the rigid body's position and orientation.
	* @note Transforming a vector by this matrix turns it from the body's local space to world space.
	* @param matrix A pointer to the matrix to fill.
	*/
	void getRigidTransform(real matrix[16]) const;
	/**
	* Fills the given matrix data structure with a transformation representing the rigid body's position and orientation.
	* The matrix is transposed from that returned by getTransform. This call returns a matrix suitable for applying as an OpenGL transform.
	* @note Transforming a vector by this matrix turns it from the body's local space to world space.
	* @param matrix A pointer to the matrix to fill.
	*/
	void getGLTransform(float matrix[16]) const;

	//Calculations
	/**
	* Copies the current inertia tensor of the rigid body into the given matrix.
	* @param inertiaTensor A pointer to a matrix to hold the current inertia tensor of the rigid body.
	* The inertia tensor is expressed in world space.
	*/
	void calcInertiaTensorWorld(OUT_PARAM(Matrix33r) inertiaTensor) const;
	/**
	* Gets a copy of the current inertia tensor of the rigid body.
	* @return A new matrix containing the current inertia tensor.
	* The inertia tensor is expressed in world space.
	*/
	Matrix33r calcInertiaTensorWorld() const;
	/**
	* The inverse inertia tensor of the body in world space.
	* @see inverseInertiaTensor
	*/
	void calcInverseInertiaTensorWorld(OUT_PARAM(Matrix33r) inertiaTensor) const;
	/**
	* Gets a copy of the current inverse inertia tensor of the rigid body.
	* @return A new matrix containing the current inverse inertia tensor.
	* The inertia tensor is expressed in world space.
	*/
	Matrix33r calcInverseInertiaTensorWorld() const;

	/**
	* Converts the given point from world space into the body's local space.
	* @param point The point to covert, given in world space.
	* @return The converted point, in local space.
	*/
	Vector3f calcPointInLocalSpace(REF(Vector3f) point) const;
	/**
	* Converts the given point from world space into the body's local space.
	* @param point The point to covert, given in local space.
	* @return The converted point, in world space.
	*/
	Vector3f calcPointInWorldSpace(REF(Vector3f) point) const;
	/**
	* Converts the given direction from world space into the body's local space.
	* @note When a direction is converted between frames of reference, there is no translation required.
	* @param direction The direction to covert, given in world space.
	* @return The converted direction, in local space.
	*/
	Vector3f calcDirectionInLocalSpace(REF(Vector3f) direction) const;
	/**
	* Converts the given direction from world space into the body's local space.
	* @note When a direction is converted between frames of reference, there is no translation required.
	* @param direction The direction to covert, given in local space.
	* @return The converted direction, in world space.
	*/
	Vector3f calcDirectionInWorldSpace(REF(Vector3f) direction) const;

	//Actions
	// Applies the given change in rotation.
	virtual bool addForce(REF(Vector3f) forceVector)
	{
		//TODO: implement
		return false;
	};
	virtual bool addImpulse(REF(Vector3f) impulseVector)
	{
		//TODO: implement
		return false;
	};
	bool addRotationVelocity(REF(Vector3f) deltaRotation);
	/**
	* Adds the given torque to the rigid body.
	* The force is expressed in world-coordinates.
	* @param torque The torque to apply.
	*/
	void addTorque(REF(Vector3f) torque);
	/**
	* Adds the given force to the given point on the rigid body.
	* Both the force and the application point are given in world space.
	* Because the force is not applied at the centre of mass, it may be split into both a force and torque.
	* @param force The force to apply.
	* @param point The location at which to apply the force, in world-coordinates.
	*/
	bool addForceAtPoint(REF(Vector3f) force, REF(Vector3f) point);
	/**
	* Adds the given force to the given point on the rigid body.
	* The direction of the force is given in world coordinates, but the application point is given in body space.
	* This is useful for spring forces, or other forces fixed to the body.
	* @param force The force to apply.
	* @param point The location at which to apply the force, in body-coordinates.
	*/
	void addForceAtBodyPoint(REF(Vector3f) force, REF(Vector3f) point);

	inline void clearPhysics(bool clearConstAccel = true)
	{
		__super::clearPhysics(clearConstAccel);
		mTorqueAccum = 0.0f;
	};
};

#endif // RigidBody_h__
