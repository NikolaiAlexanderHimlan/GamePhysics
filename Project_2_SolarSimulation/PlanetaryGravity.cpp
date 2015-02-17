/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "PlanetaryGravity.h"
#include "Planet.h"
#include <PhysicsDefines.h>
#include <Particle.h>

Vector3f PlanetaryGravity::GravityPosition() const
{
	return mpGravitySource->Simulation_getPosition();
}

void PlanetaryGravity::CalculateGravity(const Particle* gravityOn)
{
	float gravDistanceSqrd = Vector3f::DistanceSquared(mpGravitySource->Simulation_getPosition(), gravityOn->Simulation_getPosition());
	float gravMagnitude = (float)(G_CONST*(mpGravitySource->getMass() * gravityOn->getMass() / gravDistanceSqrd));
	mGravity = Vector3f::Distancepoint(gravityOn->Simulation_getPosition(), mpGravitySource->Simulation_getPosition(), gravMagnitude);
}
