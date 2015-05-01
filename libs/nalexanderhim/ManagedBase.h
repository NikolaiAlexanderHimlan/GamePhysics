/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _MANAGEDBASE_H
#define _MANAGEDBASE_H
#include <cstddef>
#include "ManageTypes.h"

//Base class for any managed classes, need to manually add to manager
//TODO: CONSIDER: Make generic T class, where T is the manager type
class ManagedBase
{
	friend ManagerBase;
	friend ManagedAuto;
private:
	ManageID mManagedID;

	//TODO: CONSIDER: these functions are pure virtual but they call a protected function which takes a ManagerBase as a parameter.  This would bypass the need for the manager implementation to friend the managed class
	//CONSIDER: replace these with single public function which takes a boolean to add/remove this object, but also takes a private "manage key" value which is private to this class, the manage function won't do anything without the correct "key"
	void addToManager();//adds this to the manager
	void removeFromManager();//removes this object from the manager

protected:
	ManageID getManagedID() const { return mManagedID;	};
	virtual ManagerBase* getManager() const = 0;

public:
	static const bool AUTO_MANAGED = false;

	virtual ~ManagedBase() {};//make sure subclass destructor is called

	//HACK: temporarily make this public until I can fix the management
	inline void Manage() { addToManager();	};//adds this to the manager
	inline void Unmanage() { removeFromManager();	};//removes this from the manager
};

//Base class for automatic management
class ManagedAuto
	: public ManagedBase
{
	//friend ManagerBase;
private:
	inline static void handleAdd(void* ptr);//does shenanigans to add to manager
	inline static void handleRemove(void* ptr);//handles removing

	//HACK: change permissions
	inline void Manage() { addToManager();	};//adds this to the manager
	inline void Unmanage() { removeFromManager();	};//removes this from the manager

public:
	static const bool AUTO_MANAGED = true;

	ManagedAuto()
	{
	};
	virtual ~ManagedAuto() {};//make sure subclass destructor is called

	void* operator new(std::size_t size);
	void operator delete(void *ptr);
	void* operator new[](std::size_t size);
	void operator delete[](void *ptr);
	inline void operator delete(void *ptr, ManageID verifyID)
	{
		/*verification disabled
		//verify key then delete
		Particle* deleteThis = (Particle*)ptr;
		if (deleteThis->mcParticleKey != verifyID)//make sure it matches the Unit key
		{
			//KEY MISMATCH!
			__debugbreak();
			//throw std::logic_error("KEY MISMATCH!");
		};
		*/
		delete ptr;//call normal delete function
	};
	inline void operator delete[](void *ptr, ManageID verifyID)
	{
		/*verification disabled
		//verify key then delete
		Particle* deleteThis = (Particle*)ptr;
		if (deleteThis->mcParticleKey != verifyID)//make sure it matches the Unit key
		{
			//KEY MISMATCH!
			__debugbreak();
			//throw std::logic_error("KEY MISMATCH!");
		};
		*/
		delete[] ptr;//call normal delete function
	};
};
#endif
