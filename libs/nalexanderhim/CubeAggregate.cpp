/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "CubeAggregate.h"
#include "AggregateMacro.h"
#include <string>

const uint NUM_CUBE_PARTICLES = 8;//number of particles required for cube

void CubeAggregate::GenerateCubeAggregate()
{
	if (!maAggregateLinks.empty()) return;//Aggregate has already been created, creating it again would result in a memory leak

	//Generate all the particles for each corner of the aggregate cube
	//positions needs to be half the dimensions of the aggregate as they are from the center then flipped
	float aggrX = mAggregateVolume.width * 0.5f;
	float aggrZ = mAggregateVolume.length * 0.5f;
	float aggrY = mAggregateVolume.height * 0.5f;
	real aggrMass = getMass();
	Vector3f aggrPos = getPhysicsPosition();
	Particle** addList = new Particle*[NUM_CUBE_PARTICLES];
	std::string particlePrefix = "cubeBody_";

	uint indx = 0;
	addList[indx] = new Particle(aggrMass, particlePrefix + std::to_string(indx));
	addList[indx]->setPhysicsPosition(aggrPos + Vector3f(aggrX, aggrY, aggrZ));
	addList[indx]->Manage();
	indx++;
	addList[indx] = new Particle(aggrMass, particlePrefix + std::to_string(indx));
	addList[indx]->setPhysicsPosition(aggrPos + Vector3f(aggrX, aggrY, -aggrZ));
	addList[indx]->Manage();
	indx++;
	addList[indx] = new Particle(aggrMass, particlePrefix + std::to_string(indx));
	addList[indx]->setPhysicsPosition(aggrPos + Vector3f(-aggrX, aggrY, -aggrZ));
	addList[indx]->Manage();
	indx++;
	addList[indx] = new Particle(aggrMass, particlePrefix + std::to_string(indx));
	addList[indx]->setPhysicsPosition(aggrPos + Vector3f(-aggrX, aggrY, aggrZ));
	addList[indx]->Manage();
	indx++;
	addList[indx] = new Particle(aggrMass, particlePrefix + std::to_string(indx));
	addList[indx]->setPhysicsPosition(aggrPos + Vector3f(aggrX, -aggrY, aggrZ));
	addList[indx]->Manage();
	indx++;
	addList[indx] = new Particle(aggrMass, particlePrefix + std::to_string(indx));
	addList[indx]->setPhysicsPosition(aggrPos + Vector3f(aggrX, -aggrY, -aggrZ));
	addList[indx]->Manage();
	indx++;
	addList[indx] = new Particle(aggrMass, particlePrefix + std::to_string(indx));
	addList[indx]->setPhysicsPosition(aggrPos + Vector3f(-aggrX, -aggrY, -aggrZ));
	addList[indx]->Manage();
	indx++;
	addList[indx] = new Particle(aggrMass, particlePrefix + std::to_string(indx));
	addList[indx]->setPhysicsPosition(aggrPos + Vector3f(-aggrX, -aggrY, aggrZ));
	addList[indx]->Manage();
	indx++;

	//generated links are automatically managed
	GenerateInterlinkedAggregate({
		addList[0]
		, addList[1]
		, addList[2]
		, addList[3]
		, addList[4]
		, addList[5]
		, addList[6]
		, addList[7]
	});
}

void CubeAggregate::RefreshAggregatePositions()
{
	//positions needs to be half the dimensions of the aggregate as they are from the center and flipped
	float aggrX = mAggregateVolume.width * 0.5f;
	float aggrZ = mAggregateVolume.length * 0.5f;
	float aggrY = mAggregateVolume.height * 0.5f;
	Vector3f aggrPos = getPhysicsPosition();

	//TODO: save as member variable
	Vector3f poses[NUM_CUBE_PARTICLES] = {
		Vector3f(aggrX, aggrY, aggrZ),
		Vector3f(aggrX, aggrY, -aggrZ),
		Vector3f(-aggrX, aggrY, -aggrZ),
		Vector3f(-aggrX, aggrY, aggrZ),
		Vector3f(aggrX, -aggrY, aggrZ),
		Vector3f(aggrX, -aggrY, -aggrZ),
		Vector3f(-aggrX, -aggrY, -aggrZ),
		Vector3f(-aggrX, -aggrY, aggrZ)
	};

	uint uPCount = 0;//unique particle count
	CALL_ON_ALL_AGGREGATES(setPhysicsPosition(aggrPos + poses[uPCount++]))
}
