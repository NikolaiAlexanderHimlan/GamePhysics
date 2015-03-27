/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "ParticleContact.h"

#include "Particle.h"
#include <iostream>

void ParticleContact::Resolve(Time duration)
{
	if (contactA == nullptr) return;//empty contact, don't resolve

	//HACK: debug testing, does this even get called?
	std::cout << "Contact Details: " << std::endl
		<< "Particle1: " << contactA->getName().c_str() << std::endl
		<< "Particle2: " << contactB->getName().c_str() << std::endl
		<< "Penetration: " << penetration << std::endl
		<< "Restitution: " << restitution << std::endl
		<< "Contact Normal: " << contactNormal.toString().c_str() << std::endl
		;

	Clear();//reset data values
}

