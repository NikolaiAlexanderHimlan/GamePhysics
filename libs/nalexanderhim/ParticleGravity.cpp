/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleGravity.h"
#include "Particle.h"

void ParticleGravity::UpdateForce(Particle* applyForceTo, Time forceDuration) const { applyForceTo->addForce(mGravity * (float)applyForceTo->getMass()); }
