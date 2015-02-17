#ifndef PlanetaryGravity_h__
#define PlanetaryGravity_h__

/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include <ParticleGravity.h>

class Planet;

class PlanetaryGravity
	: public ParticleGravity
{
	friend Planet;
private:
	const Planet* mpGravitySource;

	PlanetaryGravity(const Planet* gravitySource)
		: ParticleGravity(Vector3f()), mpGravitySource(gravitySource)
	{
		//CalculateGravity(TODO);
	}

	virtual void UpdateForce(Particle* applyForceTo, Time forceDuration)
	{
		CalculateGravity(applyForceTo);
		__super::UpdateForce(applyForceTo, forceDuration);
	}

	//Properties
	Vector3f GravityPosition() const;

	//Actions
	void CalculateGravity(const Particle* gravityOn);//sets mGravity based on the gravity source
};
#endif // PlanetaryGravity_h__
