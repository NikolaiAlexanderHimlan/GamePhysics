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
