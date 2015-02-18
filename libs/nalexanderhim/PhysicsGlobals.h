extern bool gDebugPhysics;

#define SIMULATION_SCALE 1.0
const double SIMULATION_SCALE_FACTOR = 1.0 / SIMULATION_SCALE;

class ParticleSystem;
extern ParticleSystem* getGlobalParticleSystem();
extern ParticleSystem* gpParticleSystem;
