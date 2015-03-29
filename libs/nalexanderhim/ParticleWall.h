#ifndef ParticleWall_h__
#define ParticleWall_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleContactGenerator.h"
#include "DebugDefines.h"
#include "Boundings.h"
#include "CodingDefines.h"
#include "PhysicsGlobals.h"

//An "Immovable" object which generates a ParticleContact whenever a particle collides with it
class ParticleWall
	: public ParticleContactGenerator
{
private:
	PlaneBounding mWallBounds;

public:
	Vector3f physicsPosition;

	ParticleWall(float width, float length, Axis normalAxis, bool impassable = false)
		: ParticleWall(width, length, Vector3f::AxisNormal(normalAxis)){};
	ParticleWall(float width, float length, const Vector3f& normalVector, bool impassable = false)
	{
		mWallBounds.normal = normalVector;
		mWallBounds.width = width;
		mWallBounds.length = length;
		mWallBounds.impassable = impassable;
	};

	//Getters
	inline const float& getWidth() const { return mWallBounds.width;	};
	inline const float& getLength() const { return mWallBounds.length;	};
	inline VectParam getNormal() const { return mWallBounds.normal;	};
	inline const bool& getImpassible() const { return mWallBounds.impassable;	};

	//Properties
	inline Vector3f getGraphicsPosition() const { return FROM_SIMULATION_SCALE(physicsPosition);	};

	//Modifiers
	inline void setGraphicsPosition(REF(Vector3f) newPosition) { physicsPosition = TO_SIMULATION_SCALE(newPosition);	};

	//Actions
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const;
};
#endif // ParticleWall_h__
