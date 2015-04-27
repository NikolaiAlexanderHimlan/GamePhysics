/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
//#include <Trackable.h>
#include <initializer_list>//TODO: move to source file and forward declare

namespace nah {

template <typename T>

//An array that also contains a count/length value
struct CountedArray
	// : public Trackable
{
private:
	T* maArray;
	size_t mCount;

	inline void AssignList(std::initializer_list<T> arrayList)
	{
		mCount = arrayList.size();
		//*maArray[mCount] = arrayList;
		maArray = new T[mCount];
		int i = 0;
		for (auto iter = arrayList.begin(); iter != arrayList.end(); iter++)
		{
			maArray[i++] = *iter;
		}
	};

public:

	explicit CountedArray(size_t storeCount = 0)
	{
		mCount = storeCount;
		maArray = new T[mCount];
		//this = new[storeCount];
	}
	CountedArray(const T& storeValue)
	{
		mCount = 1;
		maArray = new T[mCount];
		//this = new[storeCount];
		maArray[0] = storeValue;
	}
	CountedArray(size_t storeCount, T* storeArray)
	{
		mCount = storeCount;
		maArray = storeArray;
	}
	CountedArray(std::initializer_list<T> arrayList)
	{
		AssignList(arrayList);
	}
	//CountedArray( const CountedArray& otherArray){ *this = otherArray;	}// WARNING: THIS BREAKS THE CODE OR CAUSES MEMORY LEAKS! (based on if maArray is deleted or not)
	CountedArray(const CountedArray& otherArray)
	{
		//copy contents of other array
		mCount = otherArray.mCount;
		maArray = new T[mCount];
		for (unsigned int i = 0; i < mCount; i++)
			maArray[i] = otherArray.maArray[i];
	}
	~CountedArray(void){ delete[] maArray;	}

	//Getters
	inline T& getIndex(size_t index) { return [index];	};

	//Operators
	inline CountedArray& operator =(std::initializer_list<T> arrayList)
	{
		delete[] maArray;
		AssignList(arrayList);
	}
	inline CountedArray& operator =(const CountedArray& otherArray)
	{
		//unsure if this is necessary?
		//if(maArray != nullptr)//WARNING: NOTE: this may result in a memory leak if the first item is set to NULL while the remaining objects are not
		delete[] maArray;

		//copy contents of other array
		mCount = otherArray.mCount;
		maArray = new T[mCount];
		for (unsigned int i = 0; i < mCount; i++)
			maArray[i] = otherArray.maArray[i];
		return *this;
	}

	//Array Operators
	inline void* operator new[] (size_t storeCount)
	{
		//unsure if this is necessary?
		delete[] maArray;

		//create new array
		mCount = storeCount;
		maArray = new T[mCount];
		return this;
	}
	inline T& operator[] (size_t index){ return maArray[index];	}

	//Properties
	//number of spaces in the array
	inline size_t count(void){ return mCount;	}
	inline size_t length(void){ return mCount;	}
	inline size_t size(void){ return mCount;	}

	//Iterators
	typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin() { return &maArray[0];	}
	const_iterator begin() const { return &maArray[0];	}
	iterator end() { return &maArray[size()];	}
	const_iterator end() const { return &maArray[size()];	}
};
}

