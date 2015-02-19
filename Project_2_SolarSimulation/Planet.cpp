/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Planet.h"
#include "PlanetaryGravity.h"
#include <ParticleSystem.h>

const int Planet::PLANET_SEGMENTS = 8;
const double Planet::PLANETARY_TIMESCALE =
	60 //seconds per minute
	* 60 //minutes per hour
	* 24 //hours per day
	//* 30 //days per month
	;

PlanetaryGravity* Planet::GenerateGravity()
{
	if (mpPlanetGravity != nullptr) return mpPlanetGravity;

	mpPlanetGravity = new PlanetaryGravity(this);

	getGlobalParticleSystem()->manageParticleForceGenerator(mpPlanetGravity);

	return mpPlanetGravity;
}
void Planet::ClearPlanetGravity()
{
	if (mpPlanetGravity != nullptr)
	{
		getGlobalParticleSystem()->deleteParticleForce(mpPlanetGravity);
		mpPlanetGravity = nullptr;
	}
}
