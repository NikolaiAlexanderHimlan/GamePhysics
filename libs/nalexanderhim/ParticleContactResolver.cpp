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
	return &maContacts[mCurrentContact++];
}

void ParticleContactResolver::ResolveContacts(Time duration)
{
	for (unsigned i = 0; i < mCurrentContact; i++)
	{
		maContacts[i].Resolve(duration);
	}
	mCurrentContact = 0;
}

