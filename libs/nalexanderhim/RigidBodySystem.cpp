/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "RigidBodySystem.h"
#include "RigidBody.h"

RigidBodySystem* gpRigidBodySystem = nullptr;

extern RigidBodySystem* getGlobalRigidBodySystem()
{
	return gpRigidBodySystem;
}

void RigidBodySystem::PhysicsUpdate(Time elapsedSeconds)
{
	for (uint i = 0; i < numRigidBodies(); i++)
	{
		getRigidBody(i)->PhysicsUpdate(elapsedSeconds);
	}
}
