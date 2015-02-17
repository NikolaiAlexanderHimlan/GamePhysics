#ifndef PhysicsDefines_h__
#define PhysicsDefines_h__

//Determine if position should use complex calculation (use acceleration), or not.
#define COMPLEX_POSITION

#define SIMULATION_SCALE 1.0
const double SIMULATION_SCALE_FACTOR = 1.0 / SIMULATION_SCALE;

const double GRAVITATIONAL_CONSTANT = 6.673e-11;// N·(m / kg)2
#define G_CONST GRAVITATIONAL_CONSTANT

#endif // PhysicsDefines_h__
