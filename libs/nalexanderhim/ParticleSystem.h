/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H
#include "TimeDefines.h"
#include "MathDefines.h"
#include "ManagerBase.h"
#include "ccmccooeyWrapper.h"
#include "CountedArray.h"

class Particle;
class ParticleSystem;
class ParticleForceGenerator;
class ParticleContactGenerator;
class ParticleContactResolver;
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
	std::vector<ParticleContactGenerator*> mParticleContactGeneratorList;

	//Particle Contact system values
	bool mContactsEnabled = false;
	ParticleContactResolver* mpResolver = nullptr;//NOTE: no reason to be a pointer other than forward declaration

protected:
	ParticleSystem(){};
	~ParticleSystem()
	{
		clearParticleForceList();
		clearParticleForceRegistrations();
		clearParticleContactGeneratorList();
		DisableContactGenerator();
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

	//Getters
	inline Particle* getParticle(ManageID getID) const { return (Particle*)getManaged(getID);	};//TODO: safe cast

	//Properties
	inline uint numParticles(void) const { return numManaged();	};

	//Calculations
	Vector3f getTotalVelocity() const;
	Vector3f getTotalForce() const;

	//Actions
	//Initialization
	/**
	* Enables Particle contact handling.  
	* Simulator can handle up to the given number of contacts per frame.
	* You can also optionally give a number of contact-resolution iterations to use.
	* If you don't give a number of iterations, then twice the number of contacts will be used.
	*/
	void InitContactGenerator(unsigned maxContacts, unsigned iterations = 0);
	void DisableContactGenerator();

	//Update Systems
	void UpdatePhysics(Time elapsedSeconds);//Update Particles
	void UpdateForces(Time elapsedSeconds);//Update ParticleForces + apply force registrations
	void UpdateContacts(Time elapsedSeconds);//check for and generate particle contacts

#pragma region Particle Force Generators
	//Getters
	ManageID getParticleForceID(ParticleForceGenerator* findThis);

	//Properties
	inline uint numForceGenerators(void) const { return mParticleForceList.size();	};

	//Actions
	//HACKS: ParticleForceGenerator not managed type
	void ManageParticleForceGenerator(ParticleForceGenerator* manageForce)
	{ mParticleForceList.push_back(manageForce);	};

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


#pragma region Particle Contact Generators
	//Getters
	ManageID getParticleContactGeneratorID(ParticleContactGenerator* findThis);
	ParticleContactGenerator* getParticleContactGenerator(ManageID contactID) const { return mParticleContactGeneratorList[contactID];	};

	//Properties
	inline uint numContactGenerators() const { return mParticleContactGeneratorList.size();	};

	//Actions
		//Affect Contact system
	void clearParticleContactValues();

		//Add to Manager
	inline void ManageParticleContactGenerator(ParticleContactGenerator* manageContactGenerator)
	{ mParticleContactGeneratorList.push_back(manageContactGenerator);	};

		//Delete object
	void deleteParticleContactGenerator(ManageID removeID);
	inline void deleteParticleContactGenerator(ParticleContactGenerator* removeThis)
	{ deleteParticleContactGenerator(getParticleContactGeneratorID(removeThis));	};

		//Remove from manage
	inline void clearParticleContactGeneratorList()
	{
		for (uint i = 0; i < numContactGenerators(); i++)
		{
			deleteParticleContactGenerator(i);
		}
	};
#pragma endregion Particle Contact Generators
};
#endif
