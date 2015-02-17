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

class PlanetaryGravity;

class Planet :
	public PhysicsObject
{
private:
	const int PLANET_SEGMENTS = 8;
	PlanetaryGravity* mpPlanetGravity = nullptr;

	void ClearPlanetGravity();

public:
	Planet(float initialMass, float diameter = 1.0f, float distFromSun = 0.0f, float initialSpeed = 1.0f)
		: PhysicsObject(initialMass)
	{
		setBatchCube(diameter, diameter, diameter);//Placeholder until sphere is working correctly
		Simulation_setPosition(Vector3f(distFromSun, 0.0f, 0.0f));
		setVelocity(Vector3f(0.0f,0.0f,initialSpeed));//create a velocity perpendicular to the starting position
	}
	~Planet()
	{
		ClearPlanetGravity();
	};

	//Actions
	PlanetaryGravity* GenerateGravity();//tells this planet to create a PlanetGravity object, set itself as the gravity source, and add the ForceGenerator to the manager
};
#endif // Planet_h__
