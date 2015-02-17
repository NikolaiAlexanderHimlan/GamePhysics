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

void* ManagedAuto::operator new(std::size_t size)
{
	void* ptr = malloc(size);

	handleAdd(ptr);

	return ptr;
}
void ManagedAuto::operator delete(void *ptr)
{
	handleRemove(ptr);

	free(ptr);
}
void* ManagedAuto::operator new[](std::size_t size)
{
	void* ptr = malloc(size);

	//TODO: WARNING: I don't know if this adds other objects in the array to the manager
	handleAdd(ptr);

	return ptr;
}
void ManagedAuto::operator delete[](void *ptr)
{
	//TODO: WARNING: I don't know if this removes the other objects in the array from the manager
	handleRemove(ptr);

	free(ptr);
}

void ManagedAuto::handleAdd(void* ptr)
{
	//WARNING: can't call addToManager here as the virtual function table has not been allocated and will not be allocated until after the return.  Instead a local variable is created which calls addToManager on this object in its destructor, which will be called when it leaves this function scope.
	ManagedBase* addThis = (ManagedBase*)ptr;
	//addThis->addToManager();
}
void ManagedAuto::handleRemove(void* ptr)
{
	ManagedBase* deleteThis = (ManagedBase*)ptr;
	deleteThis->removeFromManager();
}

#pragma endregion
