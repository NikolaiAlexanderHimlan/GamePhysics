/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleObject.h"
#include "Boundings.h"

void ParticleObject::setBatchPlane(float width, float length, Axis facing /*= Y*/, bool inv /*= false /*Face along the negative edge of the axis*/)
{
	setBounds(new PlaneBounding(width, length, Vector3f::AxisNormal(facing) *(inv ? -1.0f : 1.0f)));
	Object3D::setBatchPlane(width, length, facing, inv);
}

void ParticleObject::setBatchTriangle(float distUp, float distLeft, float distRight /*TODO: optional color parameters*/) //distance of each corner from the center
{
	setBounds(new PlaneBounding(distLeft + distRight, distUp, FORWARD));
	Object3D::setBatchTriangle(distUp, distLeft, distRight);
}

void ParticleObject::setBatchCube(float xDimension, float yDimension, float zDimension /*TODO: optional color parameters*/)
{
	setBounds(new CubeBounding(CubeVolume(xDimension, zDimension, yDimension)));
	Object3D::setBatchCube(xDimension, yDimension, zDimension);
}

void ParticleObject::setBatchSphere(float radius, int numSegments /*= 8 /*TODO: optional color parameters*/)
{
	setBounds(new SphereBounding(radius));
	Object3D::setBatchSphere(radius, numSegments);
}
