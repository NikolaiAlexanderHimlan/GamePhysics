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

Particle::Particle(void)
{
	setMass(mMass);
}

void Particle::ApplyForce(const Vector3f& forceVector)
{
	mAcceleration += forceVector * mcMassFactor;
}


