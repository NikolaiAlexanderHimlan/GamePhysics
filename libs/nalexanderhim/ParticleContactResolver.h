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

#include "MathDefines.h"
#include "TimeDefines.h"

class ParticleContact;

class ParticleContactResolver
{
protected:
	ParticleContact* maContacts;
	unsigned mCurrentContact = 0;//the last contact which has a value in the array
	unsigned mMaxContacts;//the maximum number of contacts that can be stored
	unsigned mMaxIterations;//the maximum number of iterations that can be used to resolve contact per frame

public:
	ParticleContactResolver(unsigned maxContacts, unsigned maxIterations);
	virtual ~ParticleContactResolver();

	//Setters
	void addContacts(unsigned addNumContacts) { mCurrentContact += addNumContacts;	};

	//Properties
	unsigned getLimit() const { return mMaxContacts - mCurrentContact;	};//returns the remaining number of contacts available
	//First unused ParticleContact, returns nullptr if the number of max contacts has already been exceeded
	ParticleContact* NextAvailableContact();

	//Actions
	void ResolveContacts(Time duration);
};



#endif // ParticleContactResolver_h__
