/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleWall.h"
#include "PhysicsGlobals.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "Boundings.h"
#include "ParticleContact.h"

unsigned ParticleWall::addContact(ParticleContact* contact, unsigned limit) const
{
	const static real restitution = 0.0;

	Particle* checkParticle;
	unsigned used = 0;	//countContacts
	for (uint i = 0; i < getGlobalParticleSystem()->numParticles(); i++)
	{
		checkParticle = getGlobalParticleSystem()->getParticle(i);
		if (mWallBounds.CheckOverlap(checkParticle->getBounds(), physicsPosition, checkParticle->getPhysicsPosition(), &contact[used].penetration))
		{
			//There is contact
			contact[used].contactA = checkParticle;
			contact[used].contactB = nullptr;
			contact[used].contactNormal = mWallBounds.normal;
			contact[used].restitution = restitution;

			used++;//increment countContacts
		}
	}
	return used;
}
