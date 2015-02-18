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
#include <string>

class PlanetaryGravity;

class Planet :
	public PhysicsObject
{
private:
	const int PLANET_SEGMENTS = 8;
	std::string mPlanetName;
	PlanetaryGravity* mpPlanetGravity = nullptr;

	//initial values
	float mInitialDist;
	float mInitialSpeed;

	void ClearPlanetGravity();

public:
	Planet(float initialMass, float diameter = 1.0f, float distFromSun = 0.0f, float initialSpeed = 1.0f, const std::string& planetName = "")
		: PhysicsObject(initialMass)
		, mPlanetName(planetName)
		, mInitialDist(distFromSun), mInitialSpeed(initialSpeed)
	{
		//TODO: CONSIDER: have the radius of the batch be 1.0, then use scale to adjust the size
		setBatchCube(diameter, diameter, diameter);//Placeholder until sphere is working correctly
		resetOrbit();
	}
	Planet(const Planet& otherPlanet)
		: PhysicsObject(otherPlanet.getMass())
		, mPlanetName(otherPlanet.getName())
		, mInitialDist(otherPlanet.mInitialDist), mInitialSpeed(otherPlanet.mInitialSpeed)
	{
		*this = otherPlanet;
		resetOrbit();
	}
	~Planet()
	{
		ClearPlanetGravity();
	};

	//Getters
	inline const std::string& getName() const { return mPlanetName;	};

	//Properties
	float getDiameter() const;
	float getRadius() const;
	float getDisanceFromSun() const;

	//Modifiers
	void setDiameter(float newDiameter);
	void setRadius(float newRadius);
	void setDistanceFromSun(float newDist);//sets the planet's position so it is the same direction from the sun at the new distance

	//Actions
	PlanetaryGravity* GenerateGravity();//tells this planet to create a PlanetGravity object, set itself as the gravity source, and add the ForceGenerator to the manager
	inline void resetOrbit()//resets the position of the planet
	{
		//throw std::logic_error("The method or operation is not implemented.");
		Simulation_setPosition(Vector3f(mInitialDist, 0.0f, 0.0f));
		setVelocity(Vector3f(0.0f, 0.0f, mInitialSpeed));//create a velocity perpendicular to the starting position
		setForce(0.0f);
	}

	//Operators
	Planet& operator =(const Planet& rhs)
	{
		setMass(rhs.getMass());
		if (rhs.mpPlanetGravity != nullptr)
			GenerateGravity();
		mPlanetName = rhs.mPlanetName;
		//setDiameter(rhs.getDiameter());
	}
};
#endif // Planet_h__
