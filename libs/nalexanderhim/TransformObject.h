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

//Object containing a transform and handling complex transformations
class TransformObject
{
	//TODO: make class pure virtual
	//TODO: pull transform (position) change check down from PhysicsObject
private:
	const TransformObject* mpTargetTransform = nullptr;//look at
	const TransformObject* mpParentTransform = nullptr;//move with

	Transform mLocalTransform;//The local transform

public:
	//Getters
	inline const Transform& getLocalTransform() const { return mLocalTransform;	};
	virtual inline Transform& refLocalTransform() { return mLocalTransform;	};//returns a modifiable reference, done as a function so modifications can be tracked

	//Setters
	inline void setLocalTransform(const Transform& newTransform) { refLocalTransform() = newTransform; };//done using getLocalTransformRef for convenience to subclasses

	//Properties
	const Transform getWorldTransform() const//calculates the world transform based on the local transform and parent world transform
	{
		if (mpParentTransform == nullptr) return getLocalTransform();

		//HACK: Currently only calculates the (incorrect) world position and scale.  correct world position will require scale calculation
		//TODO: store current world, and previous local and world transforms.  Don't recalculate WorldTransform unless LocalTransform has changed.

		//initialize with world transform values
		Transform parentWorldTransform = mpParentTransform->getWorldTransform();
		Vector3f worldPosition = getLocalTransform().position;
		Vector3f worldRotation = getLocalTransform().rotation;
		Vector3f worldScale = getLocalTransform().scale;

		//HACK: need to calculate actual world transform
		worldPosition = parentWorldTransform.position + (getLocalTransform().position * parentWorldTransform.scale);//scale affects the position//HACK: should be influenced by rotation
		worldRotation = parentWorldTransform.rotation + (getLocalTransform().rotation * parentWorldTransform.scale);//scale affects rotation
		worldScale *= parentWorldTransform.scale;//combine the scales

		return Transform(worldPosition, worldRotation, worldScale);
	};

	//Modifiers
	void setWorldTransform(const Transform& newWorldTransform)
	{
		setWorldPosition(newWorldTransform.position);
		setWorldRotation(newWorldTransform.rotation);
		setWorldScale(newWorldTransform.scale);
	}
	void setWorldPosition(const Vector3f& newWorldPosition)
	{
		if (mpParentTransform == nullptr)
		{
			refLocalTransform().position = newWorldPosition;
			return;
		}
		//Calculate new local position value
		refLocalTransform().position = (getLocalTransform().position / mpParentTransform->getWorldTransform().scale) - mpParentTransform->getWorldTransform().position;//HACK: simplified
	}
	void setWorldRotation(const Vector3f& newWorldRotation)
	{
		if (mpParentTransform == nullptr)
		{
			refLocalTransform().rotation = newWorldRotation;
			return;
		}
		//Calculate new local rotation value
		refLocalTransform().rotation = (getLocalTransform().rotation / mpParentTransform->getWorldTransform().scale) - mpParentTransform->getWorldTransform().rotation;//HACK: simplified 
	}
	void setWorldScale(const Vector3f& newWorldScale)
	{
		if (mpParentTransform == nullptr)
		{
			refLocalTransform().scale = newWorldScale;
			return;
		}
		//Calculate new local scale value
		refLocalTransform().scale /= mpParentTransform->getWorldTransform().scale;
	}

	//Actions
	//Lock to Transform, it should be noted that calling these should not actually affect the WorldPosition, though any subsequent movement by the parent should affect the world position
	inline void lookAt(const TransformObject* lookHere)
	{
		if (lookHere == nullptr) return;
		setWorldRotation(getWorldTransform().getLookAtRotation(lookHere->getWorldTransform().position));
	}
	inline void setTarget(const TransformObject* targetThis)//look at this transform and keep looking at it until the lock is released
	{
		mpTargetTransform = targetThis;
		lookAt(targetThis);
	};
	inline void clearTarget(void) { setTarget(nullptr);	};
	inline void setParent(const TransformObject* attachTo)//attach to this transform, local transform is now relative to this
	{
		Transform oldWorld = getWorldTransform();
		mpParentTransform = attachTo;
		setWorldTransform(oldWorld);//local now stores the value relative to the parent
	};
	inline void clearParent(void)
	{
		Transform oldWorld = getWorldTransform();//save the current world transform
		setParent(nullptr);
		setWorldTransform(oldWorld);//restore the world transform into the local transform
	};
};
#endif
