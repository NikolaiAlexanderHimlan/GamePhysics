/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _TRANSFORM_OBJECT_H
#define _TRANSFORM_OBJECT_H

#include "Transform.h"
#include "CodingDefines.h"

//Object containing a transform and handling complex transformations
class TransformObject
{
	//TODO: make class pure virtual
	//TODO: pull transform (position) change check down from ParticleObject
private:
	const TransformObject* mpTargetTransform = nullptr;//look at
	const TransformObject* mpParentTransform = nullptr;//move with

	Transform mLocalTransform;//The local transform

	//TODO: need to setup calling this function in setters (and refs)
	//TODO: add check for any calculations (ex: in setters) to see if the calculation should be overridden by an existing locks.
	bool HandleLocks(void)//handles any existing locks (Target, etc..), returns if anything was modified.
	{
		//TODO: if target and parent are the same, lookAt can be simplified
		if (hasTarget())
			lookAt(mpTargetTransform->getWorldTransform().position);
		if (hasParent())
		{}//parent is only relevant to world transform
	};

public:
	//Getters
	inline REF(Transform) getLocalTransform() const { return mLocalTransform;	};
	inline virtual Transform& refLocalTransform() { return mLocalTransform;	};//returns a modifiable reference, done as a function so modifications can be tracked

	//Setters
	inline void setLocalTransform(REF(Transform) newTransform) { refLocalTransform() = newTransform;	};//done using getLocalTransformRef for convenience to subclasses

	//Properties
	inline bool hasLock() const
	{
		return false//will not affect result
			|| hasTarget()
			|| hasParent()
			;
	};
	inline bool hasTarget() const { return mpTargetTransform != nullptr;	};
	inline bool hasParent() const { return mpParentTransform != nullptr;	};
	const Transform getWorldTransform() const//calculates the world transform based on the local transform and parent world transform
	{
		if (!hasParent())
			return getLocalTransform();

		//HACK: Currently only calculates the (incorrect) world position and scale.  correct world position will require scale calculation
		//TODO: store current world, and previous local and world transforms.  Don't recalculate WorldTransform unless LocalTransform has changed.

		//initialize with world transform values
		Transform parentWorldTransform = mpParentTransform->getWorldTransform();
		Vector3f worldPosition = getLocalTransform().position;
		Vector3f worldRotation = getLocalTransform().rotation;
		Vector3f worldScale = getLocalTransform().scale;

		//TODO: parent rotation needs to affect position
		worldPosition = parentWorldTransform.position + Vector3f::Multiply(getLocalTransform().position, parentWorldTransform.scale);//scale affects the position//HACK: should be influenced by rotation also
		worldRotation = parentWorldTransform.rotation + (getLocalTransform().rotation);//rotation is affected by nothing else
		Vector3f::Multiply(worldScale, parentWorldTransform.scale);//combine the scales

		return Transform(worldPosition, Rotation3D(worldRotation, getLocalTransform().rotation.isRadians()), worldScale);
	};

	//Modifiers
	void setWorldTransform(REF(Transform) newWorldTransform)
	{
		setWorldPosition(newWorldTransform.position);
		setWorldRotation(newWorldTransform.rotation);
		setWorldScale(newWorldTransform.scale);
	};
	void setWorldPosition(REF(Vector3f) newWorldPosition)
	{
		if (mpParentTransform == nullptr)
		{
			refLocalTransform().position = newWorldPosition;
			return;
		};
		//Calculate new local position value
		//TODO: parent rotation needs to affect position
		refLocalTransform().position = (getLocalTransform().position / mpParentTransform->getWorldTransform().scale) - mpParentTransform->getWorldTransform().position;//HACK: simplified calculation
	};
	void setWorldRotation(REF(RotationVal) newWorldRotation)
	{
		if (mpParentTransform == nullptr)
		{
			refLocalTransform().rotation = newWorldRotation;
			return;
		};
		//Calculate new local rotation value
		refLocalTransform().rotation = (getLocalTransform().rotation) - mpParentTransform->getWorldTransform().rotation;//rotation is affected by nothing else
	};
	void setWorldScale(REF(Vector3f) newWorldScale)
	{
		if (mpParentTransform == nullptr)
		{
			refLocalTransform().scale = newWorldScale;
			return;
		};
		//Calculate new local scale value
		refLocalTransform().scale /= mpParentTransform->getWorldTransform().scale;
	};

	//Actions
	//Lock to Transform, it should be noted that calling these should not actually affect the WorldPosition, though any subsequent movement by the parent should affect the world position
	inline void lookAt(REF(Vector3f) lookHere)
	{ setWorldRotation(Rotation3D::calcLookAtRotation(getWorldTransform().position, lookHere));	};
	inline void setTarget(const TransformObject* targetThis)//look at this transform and keep looking at it until the lock is released
	{
		mpTargetTransform = targetThis;
		//TODO: if target is the same as parent, lookAt can be simplified
		if (hasParent())
			lookAt(targetThis->getWorldTransform().position);
	};
	inline void clearTarget(void) { setTarget(nullptr);	};
	inline void setParent(const TransformObject* attachTo)//attach to this transform, local transform is now relative to this
	{
		//world values should be the same before and after the parent has been set
		Transform oldWorld = getWorldTransform();//save the current world transform
		mpParentTransform = attachTo;
		setWorldTransform(oldWorld);//local now stores the value relative to the parent
	};
	inline void clearParent(void) { setParent(nullptr);	};
};
#endif
