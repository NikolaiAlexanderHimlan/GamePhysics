#ifndef CubeAggregate_h__
#define CubeAggregate_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "MassAggregate.h"
#include "VolumeDefinition.h"

class CubeAggregate
	: public MassAggregate
{
	//TODO: CONSIDER: should I explicitly store the particles or access them through the links as I do now?
	CubeVolume mAggregateVolume;

protected:
	void RefreshAggregatePositions();//moves all particles to match the graphical representation, used during initialization and graphics movement
	virtual inline void RefreshPhysicsPosition()
	{
		__super::RefreshPhysicsPosition();
		RefreshAggregatePositions();
	};

public:
	CubeAggregate(REF(CubeVolume) cubeDefinition, real mass, std::string name = "")
		: MassAggregate(mass, name)
		, mAggregateVolume(cubeDefinition)
	{
		setBatchCube(mAggregateVolume.width, mAggregateVolume.length, mAggregateVolume.height);
		setBounds(new Bounding());/*assign Point Bounding for the primary aggregate particle, bounding is simulated by the aggregation of particles.*/
		//GenerateCubeAggregate();
	};

	virtual inline REF(CubeVolume) getAggregateVolume() const { return mAggregateVolume;	};

	void GenerateCubeAggregate();
};
#endif // CubeAggregate_h__
