/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _MANAGERBASE_H
#define _MANAGERBASE_H
#include "ManageTypes.h"

#include <vector>/* //Toggle #include vector or forward declaration
//vector object must be a pointer if forward declared
namespace std {
	template <typename T>
	class vector < T > ;
}//*/

#include "Defines.h"

//TODO: CONSIDER: make generic T class, where T is the managed class
class ManagerBase
{
	friend ManagedBase;
private:
	//TODO: replace with map so indexes/keys don't shift when a managed object is deleted
	std::vector<ManagedBase*> mManagedList;

	//used ONLY by ManagedBase when it is created or deleted
	int addManage(ManagedBase* addThis);
	void removeManage(ManageID removeID);
	void removeManage(ManagedBase* removeThis);
	void removeManage(ManagedBase* removeThis, ManageID verifyID);

protected:
	//Getters
	inline ManagedBase* getManaged(ManageID getID) const { return mManagedList[getID];	};


public:
	//Properties
	inline uint numManaged(void) const { return mManagedList.size();	};

	//Actions
	void deleteManage(ManageID removeIndex);
};
#endif
