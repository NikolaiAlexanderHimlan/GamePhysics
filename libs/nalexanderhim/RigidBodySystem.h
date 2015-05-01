#ifndef RigidBodySystem_h__
#define RigidBodySystem_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ManagerBase.h"
#include "CodingDefines.h"
#include "TimeDefines.h"
#include "ccmccooeyWrapper.h"

class RigidBody;
class RigidBodySystem;

extern RigidBodySystem* gpRigidBodySystem;

class RigidBodySystem :
	public ManagerBase
{
	friend RigidBody;
protected:
	RigidBodySystem(){};
	~RigidBodySystem()
	{
	};

public:
	static bool InstantiateGlobal()
	{
		if (gpRigidBodySystem != nullptr) return false;

		gpRigidBodySystem = new RigidBodySystem();

		return true;
	};
	static void ClearGlobal()
	{
		SAFE_DELETE(gpRigidBodySystem);
	};

	//GameLoop
	void PhysicsUpdate(Time elapsedSeconds);//Update Particles

	//Getters
	inline RigidBody* getRigidBody(ManageID getID) const
	{ return (RigidBody*)(getManaged(getID));	};

	//Properties
	inline uint numRigidBodies(void) const { return numManaged();	};

	//Calculations
	Vector3f getTotalVelocity() const;
	Vector3f getTotalForce() const;
};
#endif // RigidBodySystem_h__
