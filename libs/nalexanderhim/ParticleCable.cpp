/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "ParticleCable.h"
#include "ParticleContact.h"

#include <Vector3f.h>
unsigned ParticleCable::addContact(ParticleContact *contact, unsigned limit) const
{
	// Find the length of the cable.
	real length = CurrentLength();

	// Check if we’re overextended.
	if (length <= maxLength)
	{
		return 0;
	}

	// Otherwise, return the contact.
	contact->contactA = linkA;
	contact->contactB = linkB;

	// Calculate the normal.
	Vector3f normal = Normal();
	contact->contactNormal = normal;
	contact->penetration = length - maxLength;
	contact->restitution = restitution;
	return 1;
}

