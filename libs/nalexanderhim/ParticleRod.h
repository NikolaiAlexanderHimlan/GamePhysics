#ifndef ParticleRod_h__
#define ParticleRod_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "ParticleLink.h"

/**
* Rods link a pair of particles, generating a contact if they
* stray too far apart or too close.
*/
class ParticleRod
	: public ParticleLink
{
public:
	/**
	* Holds the length of the rod.
	*/
	real length;

public:
	/**
	* Fills the given contact structure with the contact needed
	* to keep the rod from extending or compressing.
	*/
	virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
};

#endif // ParticleRod_h__
