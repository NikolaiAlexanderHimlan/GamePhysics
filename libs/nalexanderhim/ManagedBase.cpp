/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ManagedBase.h"
#include "ManagerBase.h"
#include <cstdlib>

#pragma region managed system operators
void ManagedBase::addToManager()
{
	//TODO: need to prevent multiple calls
	bool isManaged = false;
	if (!isManaged)
		getManager()->addManage(this);
}
void ManagedBase::removeFromManager()
{
	getManager()->removeManage(this, getManagedID());
}

void* ManagedBase::operator new(std::size_t size)
{
	void* ptr = malloc(size);

	ManagedBase* addThis = (ManagedBase*)ptr;
	addThis->addToManager();

	return ptr;
}
void ManagedBase::operator delete(void *ptr)
{
	ManagedBase* deleteThis = (ManagedBase*)ptr;
	deleteThis->removeFromManager();

	free(ptr);
}
void* ManagedBase::operator new[](std::size_t size)
{
	void* ptr = malloc(size);

	//TODO: WARNING: I don't know if this adds other objects in the array to the manager
	ManagedBase* addThis = (ManagedBase*)ptr;
	addThis->addToManager();

	return ptr;
}
void ManagedBase::operator delete[](void *ptr)
{
	//TODO: WARNING: I don't know if this removes the other objects in the array from the manager
	ManagedBase* deleteThis = (ManagedBase*)ptr;
	deleteThis->removeFromManager();

	free(ptr);
}
#pragma endregion
