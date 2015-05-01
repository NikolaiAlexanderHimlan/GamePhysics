#pragma once
#include "RigidBodyForceGenerator.h"
class RigidBodyGravity :
	public RigidBodyForceGenerator
{
public:
	RigidBodyGravity();
	virtual ~RigidBodyGravity();
};

