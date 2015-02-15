/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H
#include "Defines.h"
#include "ManagerBase.h"

class Particle;

class ParticleSystem
	: public ManagerBase//TODO: try to move this requirement to the management base classes
{
	friend Particle;
public:
	void Update(Time elapsedTime);

	//Getters
	inline Particle* getParticle(ManageID getID) const { return (Particle*)getManaged(getID);	};//TODO: safe cast

	//TODO: Gravity Force: Ian Millington, pg. 53

	//Properties
	inline uint numParticles(void) const { return numManaged();	};
};
extern ParticleSystem* gpParticleSystem;
#endif
