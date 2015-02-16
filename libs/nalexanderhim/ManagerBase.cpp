/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ManagerBase.h"
#include "ManagedBase.h"

#include <vector>

#pragma region Management Handlers
int ManagerBase::addManage(ManagedBase* addThis)
{
	mManagedList.push_back(addThis);
	ManageID addID = mManagedList.size() - 1;//index
	addThis->mManagedID = addID;
	//addThis->mIsManaged = true;
	return addID;
}
void ManagerBase::removeManage(ManageID removeID)
{
	//WARNING: MESSES UP INDEXES!!
	__debugbreak();//don't use this

	//remove pointer from vector
	auto it = mManagedList.begin();
	std::advance(it, removeID);
	mManagedList.erase(it);

	//TODO: update other IDs
}
void ManagerBase::removeManage(ManagedBase* removeThis)
{
	//TODO: verify ID
	mManagedList.erase(std::find(mManagedList.begin(), mManagedList.end(), removeThis));

	//TODO: update other IDs
}
void ManagerBase::removeManage(ManagedBase* removeThis, ManageID verifyID)
{
	//TODO: verify ID
	removeManage(removeThis);
}
#pragma endregion

void ManagerBase::deleteManage(ManageID removeID)
{
	//HACK: this will result in indexes changing, fix later
	delete mManagedList[removeID];
}

void ManagerBase::clearManagedList()
{
	for (uint i = 0; i < numManaged(); i++)
	{
		deleteManage(i);
	}
}
