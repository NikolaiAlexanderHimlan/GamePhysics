/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#ifndef ParticleContactResolver_h__
#define ParticleContactResolver_h__

#include "MathTypes.h"
#include "Defines.h"

class ParticleContact;

class ParticleContactResolver
{
protected:
	ParticleContact* maContacts;
	unsigned mCurrentContact = 0;
	unsigned mMaxContacts;
	unsigned mMaxIterations;
	unsigned mIterationsUsed;

public:
	ParticleContactResolver(unsigned maxContacts, unsigned maxIterations);
	virtual ~ParticleContactResolver();

	//Setters
	void addContacts(unsigned numNewContacts) { mCurrentContact += numNewContacts;	};

	//Properties
	unsigned getLimit() const { return mMaxContacts - mCurrentContact;	};//returns the remaining number of contacts available
	//First unused ParticleContact, returns nullptr if the number of max contacts has already been exceeded
	ParticleContact* NextAvailableContact();

	//Actions
	void ResolveContacts(Time duration);
};



#endif // ParticleContactResolver_h__
