/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "GroundArea.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "ParticleContact.h"
#include "PhysicsGlobals.h"

unsigned GroundArea::addContact(ParticleContact* contact, unsigned limit) const
{
	const static real restitution = 0.0;

	Particle* checkParticle;
	unsigned used = 0;	//countContacts
	for (uint i = 0; i < getGlobalParticleSystem()->numParticles(); i++)
	{
		checkParticle = getGlobalParticleSystem()->getParticle(i);
		Vector3f pointBeneath = checkParticle->getPhysicsPosition();
		pointBeneath.y = physicsPosition.y;//x/z of the particle and the y position of the ground
		if (checkParticle->getBounds().Contains(checkParticle->getPhysicsPosition(), pointBeneath, &contact[used].penetration))
		{
			//There is contact
			contact[used].contactA = checkParticle;
			contact[used].contactB = nullptr;
			contact[used].contactNormal = UP;
			contact[used].restitution = restitution;

			used++;//increment countContacts
		}
	}
	return used;
}
