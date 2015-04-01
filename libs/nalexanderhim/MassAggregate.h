#ifndef MassAggregate_h__
#define MassAggregate_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "PhysicsObject.h"
#include <vector>
#include "CodingDefines.h"
#include "CountedArray.h"
#include "ParticleLink.h"//Included for LinkType

class Particle;
class ParticleLink;

class MassAggregate
	: public PhysicsObject
{
protected:
	//NOTE: aggregate particles will inherently affect this one through the links
	std::vector<ParticleLink*> maAggregateLinks;//links connecting the aggregate together

	uint getNumLinks() const { return maAggregateLinks.size();	};
	
	ParticleLink* getLink(uint linkIndex) const
	{ return linkIndex < getNumLinks()?maAggregateLinks[linkIndex]:nullptr;	};
	
	void RegisterLink(ParticleLink* addLink);

public:
	explicit MassAggregate(real mass, std::string name = "")
		: PhysicsObject(mass, name)
	{
	};

	/// <summary>
	/// Adds the given link to the MassAggregate, if it is valid.
	/// </summary>
	/// <param name="newLink"> One of the links in newLink must either be THIS or a nullptr.  If one of them is a nullptr, THIS will be assigned as that link. </param>
	/// <returns> If the link was added to the aggregate. </returns>
	bool MergeIntoAggregate(ParticleLink* newLink);
	
	/// <summary>
	/// Attempts to add an array of links to the MassAggregate.
	/// </summary>
	/// <param name="invalidLinkIndexes"> Output for an array of indexes which indicate the links which were not valid.  This is useful for deleting or fixing the invalid links to prevent memory leaks. </param>
	/// <returns> Number of invalid links. </returns>
	uint MergeMultipleLinks(ParticleLink* aLinkArray, uint numLinks, OUT_PARAM(uint) invalidLinkIndexes = nullptr);

	/// Takes an array of Particles and creates links between all of them and this, using their current distances as the max length of the link.
	void GenerateInterlinkedAggregate(nah::CountedArray<Particle*> aParticles, ParticleLink::LinkType linkType = ParticleLink::ROD);
};
#endif // MassAggregate_h__
