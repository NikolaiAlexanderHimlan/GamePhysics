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
#include "ccmccooeyWrapper.h"

class Particle;
class ParticleSystem;
class ParticleForceGenerator;
typedef std::pair<ParticleForceGenerator*, Particle*> ParticleForceRegistration;

extern ParticleSystem* gpParticleSystem;

class ParticleSystem
	: public ManagerBase//TODO: try to move this requirement to the management base classes
{
	friend Particle;
private:
	//TODO: replace with linked lists, don't need random access
	//TODO: CONSIDER: have a vector<pair<ParticleForceGenerator*, vector<Particle*>>>, (or use ParticleForceGenerator* as a key in a multimap), this combines the ParticleForceList and ParticleForceRegistry
	std::vector<ParticleForceGenerator*> mParticleForceList;
	std::vector<ParticleForceRegistration> mParticleForceRegistry;

protected:
	ParticleSystem(){};
	~ParticleSystem()
	{
		clearParticleForceList();
		clearParticleForceRegistrations();
	};
public:
	static bool InstantiateGlobal()
	{
		if (gpParticleSystem != nullptr) return false;

		gpParticleSystem = new ParticleSystem();

		return true;
	}
	static void ClearGlobal()
	{
		delete gpParticleSystem;
		gpParticleSystem = nullptr;
	}
	//Update Particles
	void UpdatePhysics(Time elapsedSeconds);
	//Update ParticleForces + apply force registrations
	void UpdateForces(Time elapsedSeconds);

	//Getters
	inline Particle* getParticle(ManageID getID) const { return (Particle*)getManaged(getID);	};//TODO: safe cast

	//Properties
	inline uint numParticles(void) const { return numManaged();	};

	//Calculations
	Vector3f getTotalVelocity() const;
	Vector3f getTotalForce() const;


#pragma region Particle Force Generators
	//Getters
	ManageID getParticleForceID(ParticleForceGenerator* findThis);

	//Properties
	inline uint numForceGenerators(void) const { return mParticleForceList.size();	};

	//Actions
	//HACKS: ParticleForceGenerator not managed type
	void ManageParticleForceGenerator(ParticleForceGenerator* manageForce)
	{ mParticleForceList.push_back(manageForce); };
	
	//refer to getParticleForceID for potential implementation
	bool CheckManaged_ParticleForce(ParticleForceGenerator* checkThis, ManageID verifyID = INVALID_ID) const;

	void deleteParticleForce(ManageID removeID);
	inline void deleteParticleForce(ParticleForceGenerator* removeThis)
	{ deleteParticleForce(getParticleForceID(removeThis));	};
	
	inline void clearParticleForceList()
	{
		for (uint i = 0; i < numForceGenerators(); i++)
		{
			deleteParticleForce(i);
		}
	}
#pragma endregion Particle Force Generators


#pragma region Particle Force Registrations
	//Properties
	inline uint numForceRegistrations(void) const { return mParticleForceRegistry.size();	};

	//Actions
	//WARNING: Trusting that the user does not create a duplicate registrations, DUPLICATE REGISTRATIONS WILL STACK!
	//TODO: take ManageIDs and create registration out of the IDs, this forces the particle and force generator to already be managed and might make comparison fast enough that a check could be done to see if the registration already exists
	void RegisterParticleForce(ParticleForceGenerator* forceSource, Particle* forceTarget)
	{ mParticleForceRegistry.push_back(ParticleForceRegistration(forceSource, forceTarget));	};
	void RegisterParticleForce(ParticleForceGenerator* forceSource, nah::CountedArray<Particle*> forceTargets);

	inline void clearParticleForceRegistrations()
	{
		//all Particles and ParticleForceGenerators are saved elsewhere, just clear the list
		mParticleForceRegistry.clear();
	}
#pragma endregion Particle Force Registrations


};
#endif
