/*
Author: Nikolai Alexander-Himlan
Class: EPG-410 <Section 01>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once

#include <random>

namespace nah
{
	//random int between 0 and RAND_MAX (non-inclusive)
	inline static int randomInt(void) { return rand();	};
	//random int between 0 and RAND_MAX, inclusiveness determined by boolean
	inline static int randomInt(bool inclusive)
		;//put implementation here
	//random int between min and max (non-inclusive)
	inline static int randomInt(int min, int max)
		;//put implementation here
	//random int between min and max, inclusiveness determined by boolean
	inline static int randomInt(int min, int max, bool inclusive)
		;//put implementation here

	//random float between 0 and 1 (non-inclusive)
	inline static float randomFloat(void)
	{ return (float)rand() / RAND_MAX;	};
	//random float between 0 and 1, inclusiveness determined by boolean
	inline static float randomFloat(bool inclusive)
	{ return (float)rand() / RAND_MAX-1;	}//need a fraction between 0.0 and 1.0, why bother giving the numerator a range of +1 when we can just subtract 1 from max, which means that the largest result for rand() will result in a float of 1.0
	//random float between min and max (non-inclusive)
	inline static float randomFloat(float min, float max)
	{ return min + randomFloat()*(max - min);	};
	//random float between min and max, inclusiveness determined by boolean
	inline static float randomFloat(float min, float max, bool inclusive)
	{ return min + randomFloat(inclusive) * (max - min);	};
}
