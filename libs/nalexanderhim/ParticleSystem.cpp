/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleSystem.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "PhysicsGlobals.h"

//#include <cstddef>

ParticleSystem* gpParticleSystem = nullptr;

extern ParticleSystem* getGlobalParticleSystem()
{
	return gpParticleSystem;
}

void ParticleSystem::UpdatePhysics(Time elapsedSeconds)
{
	for (uint i = 0; i < numParticles(); i++)
	{
		getParticle(i)->UpdatePhysics(elapsedSeconds);
	}
}
void ParticleSystem::UpdateForces(Time elapsedSeconds)
{
	Particle* holdParticle;
	ParticleForceGenerator* holdForceGenerator;
	for (uint i = 0; i < mParticleForceRegistry.size(); i++)
	{
		holdForceGenerator = mParticleForceRegistry[i].first;
		holdParticle = mParticleForceRegistry[i].second;

		if (holdForceGenerator == nullptr
			|| holdParticle == nullptr)
		{
			//TODO: delete this force registration

			//i--;//repeat this index
		}
		else {//both values are valid
		holdForceGenerator->UpdateForce(holdParticle, elapsedSeconds);
		}
	}
}

ManageID ParticleSystem::getParticleForceID(ParticleForceGenerator* findThis)
{
	auto iterFound = std::find(mParticleForceList.begin(), mParticleForceList.end(), findThis);
	if (iterFound == mParticleForceList.end()) return INVALID_ID;
	return iterFound - mParticleForceList.begin();
}

void ParticleSystem::deleteParticleForce(ManageID removeID)
{
	if (mParticleForceList[removeID] != nullptr)
		delete mParticleForceList[removeID];

	mParticleForceList.erase(mParticleForceList.begin() + removeID);
}

ManageID ParticleSystem::getParticleContactGeneratorID(ParticleContactGenerator* findThis)
{
	auto iterFound = std::find(mParticleContactGeneratorList.begin(), mParticleContactGeneratorList.end(), findThis);
	if (iterFound == mParticleContactGeneratorList.end()) return INVALID_ID;
	return iterFound - mParticleContactGeneratorList.begin();
}

void ParticleSystem::deleteParticleContactGenerator(ManageID removeID)
{
	if (mParticleContactGeneratorList[removeID] != nullptr)
		delete mParticleContactGeneratorList[removeID];

	mParticleContactGeneratorList.erase(mParticleContactGeneratorList.begin() + removeID);
}
