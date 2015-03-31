/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "ParticleContactResolver.h"
#include "ParticleContact.h"

ParticleContactResolver::ParticleContactResolver(unsigned maxContacts, unsigned maxIterations) : mMaxContacts(maxContacts), mMaxIterations(maxIterations)
{
	maContacts = new ParticleContact[mMaxContacts];
	if (mMaxIterations == 0)
		mMaxIterations = mMaxContacts * 2;
}
ParticleContactResolver::~ParticleContactResolver()
{
	delete[] maContacts;
}

ParticleContact* ParticleContactResolver::NextAvailableContact()
{
	if (mCurrentContact >= mMaxContacts)
		return nullptr;
	return &maContacts[mCurrentContact];
}

void ParticleContactResolver::ResolveContacts(Time duration)
{
	unsigned iterationsUsed = 0;//the number of iterations that have been used this frame
	while (iterationsUsed < mMaxIterations)
	{
		// Find the contact with the largest closing velocity;
		unsigned maxIndex = mMaxContacts;
		real maxVel;//the best closing velocity that has been found so far
		maxVel = REAL_MAX;//assign the first separating velocity to be the maximum possible value, guaranteeing that the first valid contact replaces it
		for (unsigned i = 0; i < mCurrentContact; i++)//NOTE: no point in going past mCurrentContact, as any contacts past that were not created this frame
		{
			real sepVel = maContacts[i].CalculateSeparatingVelocity();
			if (sepVel < maxVel && //greater separating velocity than the current max
				(sepVel < 0 || maContacts[i].penetration > 0))//there is a contact
			{
				maxVel = sepVel;
				maxIndex = i;
			}
		}

		// Do we have anything worth resolving?
		if (maxIndex == mMaxContacts) break;//none of the contacts had valid collisions, don't resolve anything

		maContacts[maxIndex].Resolve(duration);//resolve the contact with the largest closing velocity

		// Update the interpenetration for all particles in case current Resolution has resolved other contacts
		Vector3f moveA = maContacts[maxIndex].particleMovementA;
		Vector3f moveB = maContacts[maxIndex].particleMovementB;
		for (unsigned i = 0; i < mCurrentContact; i++)
		{
			if (maContacts[i].contactA == maContacts[maxIndex].contactA)
			{
				maContacts[i].penetration -= Vector3f::DotProduct(moveA, maContacts[i].contactNormal);
			}
			else if (maContacts[i].contactA == maContacts[maxIndex].contactB)
			{
				maContacts[i].penetration -= Vector3f::DotProduct(moveB, maContacts[i].contactNormal);
			}
			if (maContacts[i].contactB != nullptr)//don't compare if B is null
			{
				if (maContacts[i].contactB == maContacts[maxIndex].contactA)
				{
					maContacts[i].penetration += Vector3f::DotProduct(moveA, maContacts[i].contactNormal);
				}
				else if (maContacts[i].contactB == maContacts[maxIndex].contactB)
				{
					maContacts[i].penetration += Vector3f::DotProduct(moveB, maContacts[i].contactNormal);
				}
			}
		}
		maContacts[maxIndex].Clear();//empty out the used contact
		iterationsUsed++;
	}
	//reset current contact, contacts will be regenerated next frame
	mCurrentContact = 0;
}

