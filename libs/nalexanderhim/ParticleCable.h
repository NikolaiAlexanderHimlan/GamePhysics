#ifndef ParticleCable_h__
#define ParticleCable_h__
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
* Cables link a pair of particles, generating a contact if they
* stray too far apart.
*/
class ParticleCable : public ParticleLink
{
public:
	/**
	* Holds the maximum length of the cable.
	*/
	real maxLength;

	/**
	* Holds the restitution (bounciness) of the cable.
	*/
	real restitution;

public:
	/**
	* Fills the given contact structure with the contact needed
	* to keep the cable from overextending.
	*/
	virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
};

#endif // ParticleCable_h__
