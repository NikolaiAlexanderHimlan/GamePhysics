/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "RigidBody.h"
#include "PhysicsGlobals.h"
#include "RigidBodySystem.h"

ManagerBase* RigidBody::getManager() const
{
	return getGlobalRigidBodySystem();
}

void RigidBody::getRigidTransform(OUT_PARAM(Matrix44r) transformMatrix) const
{
	(*transformMatrix)[0] = 1 - 2 * getOrientation().j*getOrientation().j -
		2 * getOrientation().k*getOrientation().k;
	(*transformMatrix)[1] = 2 * getOrientation().i*getOrientation().j -
		2 * getOrientation().r*getOrientation().k;
	(*transformMatrix)[2] = 2 * getOrientation().i*getOrientation().k +
		2 * getOrientation().r*getOrientation().j;
	(*transformMatrix)[3] = getPhysicsPosition().x;
	
	(*transformMatrix)[4] = 2 * getOrientation().i*getOrientation().j +
		2 * getOrientation().r*getOrientation().k;
	(*transformMatrix)[5] = 1 - 2 * getOrientation().i*getOrientation().i -
		2 * getOrientation().k*getOrientation().k;
	(*transformMatrix)[6] = 2 * getOrientation().j*getOrientation().k -
		2 * getOrientation().r*getOrientation().i;
	(*transformMatrix)[7] = getPhysicsPosition().y;
	
	(*transformMatrix)[8] = 2 * getOrientation().i*getOrientation().k -
		2 * getOrientation().r*getOrientation().j;
	(*transformMatrix)[9] = 2 * getOrientation().j*getOrientation().k +
		2 * getOrientation().r*getOrientation().i;
	(*transformMatrix)[10] = 1 - 2 * getOrientation().i*getOrientation().i -
		2 * getOrientation().j*getOrientation().j;
	(*transformMatrix)[11] = getPhysicsPosition().z;
}
