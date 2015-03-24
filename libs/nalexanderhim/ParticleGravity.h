#ifndef ParticleGravity_h__
#define ParticleGravity_h__

/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ccmccooeyWrapper.h"
#include "ParticleForceGenerator.h"

class ParticleGravity
	: public ParticleForceGenerator
{
protected:
	Vector3f mGravity;

	virtual void UpdateForce(Particle* applyForceTo, Time forceDuration);

public:
	ParticleGravity(const Vector3f& gravityForce) : mGravity(gravityForce){};
};
#endif // ParticleGravity_h__
