/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef ParticleForceGenerator_h__
#define ParticleForceGenerator_h__

#include "TimeDefines.h"

class Particle;
class ParticleSystem;

//MUST BE ADDED TO A PARTICLE SYSTEM!
//NOTE: ^ why is this?
class ParticleForceGenerator
{
	friend ParticleSystem;
protected:
	virtual void UpdateForce(Particle* applyForceTo, Time forceDuration) const = 0;

public:
	ParticleForceGenerator(){};
	virtual ~ParticleForceGenerator(){};
};

#endif // ParticleForceGenerator_h__
