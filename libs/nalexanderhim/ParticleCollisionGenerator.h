#ifndef PhysicalParticleDetection_h__
#define PhysicalParticleDetection_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: bonus
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "ParticleContactGenerator.h"

//Detects contact with all other particles, stores a list of particle pairs so as to not resolve the same particle multiple times
class ParticleCollisionGenerator :
	public ParticleContactGenerator
{
public:
	ParticleCollisionGenerator(){};
	virtual ~ParticleCollisionGenerator(){};

	virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
};

#endif // PhysicalParticleDetection_h__
