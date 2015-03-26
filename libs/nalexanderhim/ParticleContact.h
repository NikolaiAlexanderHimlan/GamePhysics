#ifndef ParticleContact_h__
#define ParticleContact_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include <Vector3f.h>
#include "MathTypes.h"

class Particle;

/**
* A contact represents two objects in contact (in this case
* ParticleContact representing two particles). Resolving a
* contact removes their interpenetration, and applies sufficient
* impulse to keep them apart. Colliding bodies may also rebound.
*
* The contact has no callable functions, it just holds the
* contact details. To resolve a set of contacts, use the particle
* contact resolver class.
*/
class ParticleContact
{
public:
	Particle* contacted[2];

	real penetration;
	real restitution;
	Vector3f contactNormal;

protected:
	/**
	* Resolves this contact for both velocity and interpenetration.
	*/
	void Resolve(real duration);
	/**
	* Calculates the separating velocity at this contact.
	*/
	real CalculateSeparatingVelocity() const;

private:
	/**
	* Handles the impulse calculations for this collision.
	*/
	void ResolveVelocity(real duration);
};

#endif // ParticleContact_h__
