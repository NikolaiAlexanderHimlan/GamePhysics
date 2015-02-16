/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
//#include <Trackable.h>
template <typename T>
//An array that also contains a count/length value
struct CountedArray
	// : public Trackable
{
private:
	T* mArray;
	size_t mCount;
public:

	CountedArray(size_t storeCount = 0)
	{
		mCount = storeCount;
		mArray = new T[mCount];
		//this = new[storeCount];
	}
	CountedArray(const T& storeValue)
	{
		mCount = 1;
		mArray = new T[mCount];
		//this = new[storeCount];
		mArray[0] = storeValue;
	}
	CountedArray(size_t storeCount, T* storeArray)
	{
		mCount = storeCount;
		mArray = storeArray;
	}
	//CountedArray( const CountedArray& otherArray){ *this = otherArray;	}// WARNING: THIS BREAKS THE CODE OR CAUSES MEMORY LEAKS! (based on if mArray is deleted or not)
	CountedArray(const CountedArray& otherArray)
	{
		//copy contents of other array
		mCount = otherArray.mCount;
		mArray = new T[mCount];
		for (unsigned int i = 0; i < mCount; i++)
			mArray[i] = otherArray.mArray[i];
	}
	~CountedArray(void){ delete[] mArray;	}

	inline CountedArray& operator =(const CountedArray& otherArray)
	{
		//unsure if this is necessary?
		//if(mArray != nullptr)//WARNING: NOTE: this may result in a memory leak if the first item is set to NULL while the remaining objects are not
		delete[] mArray;

		//copy contents of other array
		mCount = otherArray.mCount;
		mArray = new T[mCount];
		for (unsigned int i = 0; i < mCount; i++)
			mArray[i] = otherArray.mArray[i];
		return *this;
	}
	inline void* operator new[] (size_t storeCount)
	{
		//unsure if this is necessary?
		delete[] mArray;

		//create new array
		mCount = storeCount;
		mArray = new T[mCount];
		return this;
	}

	inline T& operator[] (size_t index){ return mArray[index];	}
	//number of spaces in the array
	inline size_t count(void){ return mCount;	}
	inline size_t length(void){ return mCount;	}
	inline size_t size(void){ return mCount;	}
};

