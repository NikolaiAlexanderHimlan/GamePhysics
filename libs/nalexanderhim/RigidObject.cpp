/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "RigidObject.h"
#include "Boundings.h"

//HACK: exact duplicate code with ParticleObject

void RigidObject::setBatchCube(float xDimension, float yDimension, float zDimension /*TODO: optional color parameters*/)
{
	setBounds(RigidBounds::BoundsBox(xDimension, zDimension, yDimension));
	Object3D::setBatchCube(xDimension, yDimension, zDimension);
}

void RigidObject::setBatchSphere(float radius, int numSegments /*= 8 /*TODO: optional color parameters*/)
{
	setBounds(RigidBounds::BoundsSphere(radius));
	Object3D::setBatchSphere(radius, numSegments);
}
