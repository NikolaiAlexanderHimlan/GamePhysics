#ifndef ParticleSpring_h__
#define ParticleSpring_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "ParticleForceGenerator.h"
#include "MathDefines.h"

class ParticleSpring
	: public ParticleForceGenerator
{
	/** The particle at the other end of the spring. */
	Particle* mpSpringEnd;

	/** Holds the spring constant. */
	real mSpringConstant;

	/** Holds the rest length of the spring. */
	real mRestingLength;

public:
	/** Creates a new spring with the given parameters. */
	ParticleSpring(Particle* other, real springConstant, real restLength);

	/** Applies the spring force to the given particle. */
	virtual void updateForce(Particle *particle, real duration);
};

#endif // ParticleSpring_h__
