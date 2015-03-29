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
#include "MathDefines.h"
#include "TimeDefines.h"

class Particle;
class ParticleContactResolver;

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
	friend ParticleContactResolver;
public:
	Particle* contactA;
	Particle* contactB;//NOTE: contactB is allowed to be null, in which case it is assumed to have infinite mass

	real penetration;
	real restitution;
	Vector3f contactNormal;

protected:
	/**
	* Resolves this contact for both velocity and interpenetration.
	*/
	void Resolve(Time duration);
	/**
	* Calculates the separating velocity at this contact.
	*/
	real CalculateSeparatingVelocity() const;

	void Clear()
	{
		contactA = nullptr;
		contactB = nullptr;
		penetration = 0;
		restitution = 0;
		contactNormal = Vector3f::zero;
	}

private:
	/**
	* Handles the impulse calculations for this collision.
	*/
	void ResolveVelocity(real duration);
};

#endif // ParticleContact_h__
