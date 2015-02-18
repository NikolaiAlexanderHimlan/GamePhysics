#include "doubleFactor.h"

extern bool gDebugPhysics;

extern doubleFactor gcSimulationScale;
#define SIMULATION_SCALE gcSimulationScale.getValue()
#define SIMULATION_SCALE_FACTOR gcSimulationScale.getFactor()

class ParticleSystem;
extern ParticleSystem* getGlobalParticleSystem();
extern ParticleSystem* gpParticleSystem;
