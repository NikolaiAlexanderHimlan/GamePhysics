#ifndef ParticleLink_h__
#define ParticleLink_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "ParticleContactGenerator.h"
#include "MathDefines.h"

class Particle;
class Vector3f;

/**
* Links connect two particles together, generating a contact if
* they violate the constraints of their link. It is used as a
* base class for cables and rods, and could be used as a base
* class for springs with a limit to their extension.
*/
class ParticleLink
	: public ParticleContactGenerator
{
public:
	//Useful for dynamically choosing the type of link at runtime
	enum LinkType {
		INVALID_LINK = -1, 

		ROD, 
		CABLE, 

		NUM_LINK_TYPES
	};

	Particle* linkA = nullptr;
	Particle* linkB = nullptr;

protected:
	/**
	* Returns the current length of the link.
	*/
	real CurrentLength() const;
	real CurrentLengthSquared() const;

	Vector3f Normal() const;

public:
	/**
	* Generates the contacts to keep this link from being
	* violated. This class can only ever generate a single
	* contact, so the pointer can be a pointer to a single
	* element, the limit parameter is assumed to be at least 1
	* (0 isn’t valid), and the return value is 0 if the
	* cable wasn’t overextended, or 1 if a contact was needed.
	*
	* NB: This method is declared in the same way (as pure
	* virtual) in the parent class, but is replicated here for
	* documentation purposes.
	*/
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;

	//Attempts to resolve any potential contacts for only the specific link particle without affecting the other particle.
	//virtual 
		unsigned ResolveLinkA() const;// = 0;
	//virtual 
		unsigned ResolveLinkB() const;// = 0;
};

#endif // ParticleLink_h__
