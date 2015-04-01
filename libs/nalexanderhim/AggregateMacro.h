/*by only adjusting the links with "this", the particles will not be set multiple times*/
//Calls the given function on all aggregate particles
#define CALL_ON_ALL_AGGREGATES(aggregateFunctionCall) for (uint i = 0; i < getNumLinks(); i++) { \
	if (getLink(i)->linkA == this) \
		getLink(i)->linkB->aggregateFunctionCall; \
	else if (getLink(i)->linkB == this) \
		getLink(i)->linkA->aggregateFunctionCall; \
}
