/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "MassAggregate.h"
#include "AggregateMacro.h"
#include "ParticleLink.h"
#include "ParticleRod.h"
#include "ParticleSystem.h"

void MassAggregate::RegisterLink(ParticleLink* addLink)
{
	maAggregateLinks.push_back(addLink);
	getGlobalParticleSystem()->ManageParticleContactGenerator(addLink);
}

bool MassAggregate::MergeIntoAggregate(ParticleLink* newLink)
{
	bool validLink = false;

	//Check if either of the links are the MassAggregate
	if (newLink->linkA == this || newLink->linkB == this)
	{
		validLink = true;//link is valid, save link
	}
	else if (newLink->linkA == nullptr)//is linkA empty?
	{
		newLink->linkA = this;//save MassAggregate into linkA, link is now valid
		validLink = true;
	}
	else if (newLink->linkB == nullptr)//is linkB empty?
	{
		newLink->linkB = this;//save MassAggregate into linkB, link is now valid
		validLink = true;
	}
	//else //neither link particle is empty, link is not valid, do not save

	if (validLink)
		maAggregateLinks.push_back(newLink);
	return validLink;
}

void MassAggregate::GenerateInterlinkedAggregate(nah::CountedArray<Particle*> aParticles, ParticleLink::LinkType linkType /*= ParticleLink::ROD*/)
{
	//HACK: only implementing ROD links for now.
	ParticleRod* holdRod;
	for (uint lA = 0; lA < aParticles.length(); lA++)
	{
		//Link this index to the aggregate
		holdRod = new ParticleRod();
		holdRod->linkA = this;
		holdRod->linkB = aParticles[lA];
		holdRod->length = Vector3f::Distance(this->getPhysicsPosition(), aParticles[lA]->getPhysicsPosition());
		RegisterLink(holdRod);

		//Link this index to the following particles
		for (uint lB = lA+1; lB < aParticles.length(); lB++)
		{
			//link the primary index to this inner index
			holdRod = new ParticleRod();
			holdRod->linkA = aParticles[lA];
			holdRod->linkB = aParticles[lB];
			holdRod->length = Vector3f::Distance(aParticles[lA]->getPhysicsPosition(), aParticles[lB]->getPhysicsPosition());
			RegisterLink(holdRod);
		}
	}
}

bool MassAggregate::Draw(CameraView* renderView, GLShaderManager& shaderManager, M3DMatrix44f& mvpMatrix) const
{
	if (mRenderAggregate)
	{
		bool combineBool = true;
		PhysicsObject* testParticle = nullptr;
		for (uint i = 0; i < getNumLinks(); i++)
		{
			if (getLink(i)->linkA == this)
				testParticle = dynamic_cast<PhysicsObject*>(getLink(i)->linkB);
			else if (getLink(i)->linkB == this)
				testParticle = dynamic_cast<PhysicsObject*>(getLink(i)->linkA);

			if (testParticle != nullptr)
				combineBool &= testParticle->Draw(renderView, shaderManager, mvpMatrix);
			else combineBool = false;
		}
		return combineBool;
	}
	else if (mLineAggregate)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		bool drawResult = __super::Draw(renderView, shaderManager, mvpMatrix);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		return drawResult;
	}
	else return __super::Draw(renderView, shaderManager, mvpMatrix);
}
