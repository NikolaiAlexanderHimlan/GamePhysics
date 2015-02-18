/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Particle.h"
#include "PhysicsGlobals.h"
#include "ParticleSystem.h"

ManagerBase* Particle::getManager() const
{
	return getGlobalParticleSystem();
	//return gpParticleSystem;
}
