/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleSystem.h"

#include <cstddef>

#include "Particle.h"

ParticleSystem* gpParticleSystem = NULL;

extern ParticleSystem* getGlobalParticleSystem()
{
	return gpParticleSystem;
}

void ParticleSystem::Update(Time elapsedTime)
{
	for (uint i = 0; i < numParticles(); i++)
	{
		getParticle(i)->Update(elapsedTime);
	}
}

