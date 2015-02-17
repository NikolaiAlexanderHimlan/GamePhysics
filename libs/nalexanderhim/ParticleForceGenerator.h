/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef ParticleForceGenerator_h__
#define ParticleForceGenerator_h__

#include "Defines.h"

class Particle;
class ParticleSystem;

//MUST BE ADDED TO A PARTICLE SYSTEM!
class ParticleForceGenerator
{
	friend ParticleSystem;
protected:
	ParticleForceGenerator(){};
	~ParticleForceGenerator(){};
	virtual void UpdateForce(Particle* applyForceTo, Time forceDuration) = 0;
};

#endif // ParticleForceGenerator_h__
