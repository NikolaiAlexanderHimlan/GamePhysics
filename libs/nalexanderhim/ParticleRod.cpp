/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "ParticleRod.h"
#include "ParticleContact.h"
#include <Vector3f.h>

unsigned ParticleRod::addContact(ParticleContact *contact, unsigned limit) const
{
	// Find the length of the rod.
	real currentLen = CurrentLength();

	// Check if we’re overextended.
	if (currentLen == length)
	{
		return 0;
	}

	// Otherwise, return the contact.
	contact->contactA = FirstLink();
	contact->contactB = SecondLink();

	// Calculate the normal.
	Vector3f normal = Normal();

	// The contact normal depends on whether we’re extending or compressing.
	if (currentLen > length) {
		contact->contactNormal = normal;
		contact->penetration = currentLen - length;
	}
	else {
		contact->contactNormal = normal * -1;
		contact->penetration = length - currentLen;
	}

	// Always use zero restitution (no bounciness).
	contact->restitution = 0;

	return 1;
}
