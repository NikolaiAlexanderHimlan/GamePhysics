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
	const static real restitution = 0.0;//ground has no restitution

	Particle* checkParticle;
	unsigned used = 0;	//count contacts generated
	for (uint i = 0; i < getGlobalParticleSystem()->numParticles(); i++)
	{
		bool makeContact = false;
		checkParticle = getGlobalParticleSystem()->getParticle(i);
		Vector3f pointBeneath = checkParticle->getPhysicsPosition();
		pointBeneath.y = physicsPosition.y;//x/z of the particle and the y position of the ground
		real interlap = 0;//store penetration

		if (physicsPosition.y >= checkParticle->getPhysicsPosition().y)//is below ground?
		{
			interlap = physicsPosition.y - checkParticle->getPhysicsPosition().y;
			makeContact = true;
		}
		else if (checkParticle->getBounds().Contains(checkParticle->getPhysicsPosition(), pointBeneath, &interlap))//check for actual collision?
			makeContact = true;

		if(makeContact)
		{
			//There is contact
			contact[used].contactA = checkParticle;
			contact[used].contactB = nullptr;
			contact[used].contactNormal = UP;
			contact[used].restitution = restitution;
			contact[used].penetration = interlap;

			used++;//increment countContacts
		}
		if (used >= limit) break;//no more available contacts
	}
	return used;
}
