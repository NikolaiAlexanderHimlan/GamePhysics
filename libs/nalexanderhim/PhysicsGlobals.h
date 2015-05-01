#ifndef PhysicsGlobals_h__
#define PhysicsGlobals_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "doubleFactor.h"
#include "CodingDefines.h"

extern bool gDebugPhysics;

extern doubleFactor gcSimulationScale;
#define SIMULATION_SCALE gcSimulationScale.getValue()
#define SIMULATION_SCALE_FACTOR gcSimulationScale.getFactor()
#define TO_SIMULATION_SCALE(fromBase) (fromBase * (float)SIMULATION_SCALE)
#define FROM_SIMULATION_SCALE(fromSimulation) (fromSimulation * (float)SIMULATION_SCALE_FACTOR)

class ParticleSystem;
extern ParticleSystem* getGlobalParticleSystem();
extern ParticleSystem* gpParticleSystem;

class RigidBodySystem;
extern RigidBodySystem* getGlobalRigidBodySystem();
extern RigidBodySystem* gpRigidBodySystem;

#endif // PhysicsGlobals_h__
