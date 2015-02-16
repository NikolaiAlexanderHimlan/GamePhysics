#ifndef Planet_h__
#define Planet_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include <PhysicsObject.h>

class Planet :
	public PhysicsObject
{
public:
	Planet(float initialMass)
		: PhysicsObject(initialMass)
	{
	}
	~Planet()
	{
	};
};
#endif // Planet_h__
