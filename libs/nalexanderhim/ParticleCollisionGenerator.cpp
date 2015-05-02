/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: bonus
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleCollisionGenerator.h"
#include "PhysicsGlobals.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "Boundings.h"
#include "ParticleContact.h"
#include <map>

unsigned ParticleCollisionGenerator::addContact(ParticleContact *contact, unsigned limit) const
{
	//[Particle being checked], [particle in collision] -> [checking next particle], [use collision checking with as key]
	std::map<Particle*, Particle*> mFoundCollisions = std::map<Particle*, Particle*>();//collisions that have already been found and contacts generated.  Don't create additional contacts for this pair again.

	//check for contacts between all particles.  Log the found collisions in the map so as to not generate duplicate collisions.
	const static real restitution = 0.0;

	Particle* checkParticle;
	Particle* checkCollide;
	auto foundItr = mFoundCollisions.begin();
	unsigned used = 0;	//countContacts
	for (uint i = 0; i < getGlobalParticleSystem()->numParticles(); i++)
	{
		checkParticle = getGlobalParticleSystem()->getParticle(i);
		if (!checkParticle->hasInfiniteMass())//first particle should not have infinite mass (it's a waist of time and can result in 2 objects of infinite mass colliding, which is bad).
		{
			for (uint j = 0; j < getGlobalParticleSystem()->numParticles(); j++)
			{
				if (i != j)
				{
					checkCollide = getGlobalParticleSystem()->getParticle(j);

					//check if the second particle has already generated contact with this one
					foundItr = mFoundCollisions.find(checkCollide);

					/*This is a complex and difficult to read+parse mess, just use continue!
					if ((foundItr != mFoundCollisions.end())?//other particle has had collisions
					(foundItr->second == checkParticle)://other particle has collision with this particle
					true)//other particle has not had any collisions with this particle
					//*/

					if (foundItr != mFoundCollisions.end())//check if other particle has had any collisions yet?
					{
						//if other particle has had collisions, check if they were with this particle
						if (foundItr->second == checkParticle)
							continue;//collisions were with this particle, skip to next iteration in loop
					}
					//if these 2 particles have not had any collisions yet (no condition on these brackets)
					{
						//save to mFoundCollisions whether a new contact ends up being generated or not
						mFoundCollisions.insert(std::pair<Particle*, Particle*>(checkParticle, checkCollide));
						//collision has not been detected yet between these particles, check for collision.
						if (checkParticle->getBounds().CheckOverlap(
							checkCollide->getBounds(),
							checkParticle->getPhysicsPosition(),
							checkCollide->getPhysicsPosition(), 
							&contact[used].penetration,
							&contact[used].contactNormal))
						{
							real thingy = 0.0;
							Vector3f thingN = 0.0f;
							checkParticle->getBounds().CheckOverlap(
								checkCollide->getBounds(),
								checkParticle->getPhysicsPosition(),
								checkCollide->getPhysicsPosition(),
								&thingy, &thingN);//HACK: result check

							//Particles overlap, generate contact
							contact[used].contactA = checkParticle;
							contact[used].contactB = checkCollide;
							contact[used].restitution = restitution;

							used++;//increment countContacts
						}
					}
				}
			}
		}
	}
	return used;
}
