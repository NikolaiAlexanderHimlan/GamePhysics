/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleLink.h"
#include "Particle.h"
#include <Vector3f.h>

#include <cmath>
real ParticleLink::CurrentLength() const
{
	return std::sqrt(CurrentLengthSquared());
}
real ParticleLink::CurrentLengthSquared() const
{
	return Vector3f::DistanceSquared(
		maLinked[0]->getPhysicsPosition(), 
		maLinked[1]->getPhysicsPosition());
}

Vector3f ParticleLink::Normal() const
{
	return Vector3f::DirectionFrom(maLinked[0]->getPhysicsPosition(), maLinked[1]->getPhysicsPosition());
}

