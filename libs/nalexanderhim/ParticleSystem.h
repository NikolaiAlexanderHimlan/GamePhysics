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
class ParticleSystem;
class ParticleForceGenerator;
typedef std::pair<ParticleForceGenerator*, Particle*> ParticleForceRegistration;

extern ParticleSystem* gpParticleSystem;

class ParticleSystem
	: public ManagerBase//TODO: try to move this requirement to the management base classes
{
	friend Particle;
private:
	//TODO: CONSIDER: have a vector<pair<ParticleForceGenerator*, vector<Particle*>>>, (or use ParticleForceGenerator* as a key in a multimap), this combines the ParticleForceList and ParticleForceRegistry
	std::vector<ParticleForceGenerator*> mParticleForceList;
	std::vector<ParticleForceRegistration> mParticleForceRegistry;

protected:
	ParticleSystem(){};
	~ParticleSystem()
	{
		clearParticleForceList();
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
	void UpdatePhysics(Time elapsedSeconds);
	void UpdateForces(Time elapsedSeconds);

	//Getters
	inline Particle* getParticle(ManageID getID) const { return (Particle*)getManaged(getID);	};//TODO: safe cast
	ManageID getParticleForceID(ParticleForceGenerator* findThis);

	//Properties
	inline uint numParticles(void) const { return numManaged();	};
	inline uint numForceGenerators(void) const { return mParticleForceList.size();	};
	inline uint numForceRegistrations(void) const { return mParticleForceRegistry.size();	};
	//refer to getParticleForceID for potential implementation
	bool checkManagedParticleForce(ParticleForceGenerator* checkThis, ManageID verifyID = INVALID_ID) const;

	//Actions
	//WARNING: Trusting that the user does not create a duplicate registrations, DUPLICATE REGISTRATIONS WILL STACK!
	//TODO: take ManageIDs and create registration out of the IDs, this forces the particle and force generator to already be managed and might make comparison fast enough that a check could be done to see if the registration already exists
	void RegisterParticleForce(ParticleForceGenerator* forceSource, Particle* forceTarget)
	{ mParticleForceRegistry.push_back(ParticleForceRegistration(forceSource, forceTarget));	};
	//TODO: Register with variable number of Particle args
	void deleteParticleForce(ManageID removeID);
	inline void deleteParticleForce(ParticleForceGenerator* removeThis) { deleteParticleForce(getParticleForceID(removeThis));	};
	inline void clearParticleForceList()
	{
		for (uint i = 0; i < numForceGenerators(); i++)
		{
			deleteParticleForce(i);
		}
	}
	void clearParticleForceRegistrations()
	{
		//all Particles and ParticleForceGenerators are saved elsewhere, just clear the list
		mParticleForceRegistry.clear();
	}

	//HACKS: ParticleForceGenerator not managed type
	//HACK: should be private once ForceGenerators are automatically managed
	void manageParticleForceGenerator(ParticleForceGenerator* manageForce) { mParticleForceList.push_back(manageForce); };
};
#endif
