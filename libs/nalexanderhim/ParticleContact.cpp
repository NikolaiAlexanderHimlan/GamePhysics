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
#include "DebugKeys.h"

#include <iostream>

void ParticleContact::Resolve(Time duration)
{
	if (contactA == nullptr) return;//empty contact, don't resolve

#ifdef DEBUG_CONTACTS
	//HACK: debug testing, does this even get called?
	std::cout << "Contact Details: " << std::endl
		<< "Particle1: " << contactA->getName().c_str() << std::endl
		<< "Particle2: " << contactB->getName().c_str() << std::endl
		<< "Penetration: " << penetration << std::endl
		<< "Restitution: " << restitution << std::endl
		<< "Contact Normal: " << contactNormal.toString().c_str() << std::endl
		<< std::endl;
#endif

	ResolveVelocity(duration);
	ResolveInterpenetration(duration);

	//Call manually //Clear();//reset data values
}

real ParticleContact::CalculateSeparatingVelocity() const
{
	if (contactA == nullptr) return 0;//contactA should never be null if the contact is valid
	Vector3f relativeVelocity = contactA->getVelocityLinear();
	if (contactB != nullptr) relativeVelocity -= contactB->getVelocityLinear();
	return Vector3f::Dot(relativeVelocity, contactNormal);
}

void ParticleContact::ResolveVelocity(Time duration)
{
	// Find the velocity in the direction of the contact.
	real separatingVelocity = CalculateSeparatingVelocity();

	// Check if it needs to be resolved.
	if (separatingVelocity > 0)
	{
		// The contact is either separating, or stationary;
		// no impulse is required.
		return;
	}

	// Calculate the new separating velocity.
	real newSepVelocity = -separatingVelocity * restitution;

	real deltaVelocity = newSepVelocity - separatingVelocity;

	// We apply the change in velocity to each object in proportion to
	// their inverse mass (i.e., those with lower inverse mass [higher
	// actual mass] get less change in velocity).
	real totalInverseMass = contactA->getMass().getFactor();
	if (contactB != nullptr) totalInverseMass += contactB->getMass().getFactor();

	// If all particles have infinite mass, then impulses have no effect.
	if (totalInverseMass <= 0) return;

	// Calculate the impulse to apply.
	real impulse = deltaVelocity / totalInverseMass;

	// Find the amount of impulse per unit of inverse mass.
	Vector3f impulsePerIMass = contactNormal * (float)impulse;

	// Apply impulses: they are applied in the direction of the contact,
	// and are proportional to the inverse mass.
	contactA->setVelocityLinear( contactA->getVelocityLinear() +
		impulsePerIMass * (float)contactA->getMass().getFactor());
	if (contactB != nullptr)
	{
		if (!contactB->hasInfiniteMass())
		{
		// Particle 1 goes in the opposite direction
		contactB->setVelocityLinear( contactB->getVelocityLinear() +
			impulsePerIMass * (float)-contactB->getMass().getFactor());
		}
	}
}

void ParticleContact::ResolveInterpenetration(Time duration)
{
	// If we don’t have any penetration, skip this step.
	if (penetration <= 0) return;

	// The movement of each object is based on their inverse mass, so total that.
	real totalInverseMass = contactA->getMass().getFactor();
	if (contactB != nullptr) totalInverseMass += contactB->getMass().getFactor();

	// If all particles have infinite mass, then we do nothing.
	// Check if particle is null, has infinite mass if null
	if (((contactA == nullptr)?true:
			contactA->hasInfiniteMass()) &&
		((contactB == nullptr)?true:
			contactB->hasInfiniteMass()))
		return;

	// Find the amount of penetration resolution per unit of inverse mass.
	Vector3f movePerIMass = contactNormal * (float)(penetration / totalInverseMass);

	// Calculate the movement amounts.
	particleMovementA = movePerIMass * (float)contactA->getMass().getFactor();
	if (contactB != nullptr) {
		particleMovementB =
			movePerIMass * (float)-contactB->getMass().getFactor();
	}
	else {
		particleMovementB = Vector3f::zero;
	}

	// Apply the penetration resolution.
	contactA->setPhysicsPosition(
		contactA->getPhysicsPosition() + particleMovementA );

	if (contactB != nullptr) {
		contactB->setPhysicsPosition(
			contactB->getPhysicsPosition() + particleMovementB );
	}
}
