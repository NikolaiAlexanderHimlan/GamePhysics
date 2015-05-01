//DO NOT INCLUDE THIS FILE ANYWHERE!
#ifndef FACTOR_CLASS
#error I told you not to include this!
#else
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "CodingDefines.h"

//This file is included by files which have the missing defines to create a set of class types which have identical functionality for different data types.
// #define FACTOR_CLASS
// #define VALUE_TYPE
// #define VALUE_ZERO
// #define FACTOR_TYPE
// #define FACTOR_ONE

//TODO: CONSIDER: maybe this should be a Template T class instead, but that doesn't forcefully limit it to numbers
//TODO: CONSIDER: is this factor or inverse?
//TODO: the following TODO does not currently work, as RefreshFactor cannot be called in getFactor due to const, implementation left but disabled.  //TODO: use boolean to track if mValue has been changed and calculate mFactor only in getFactor and only if mValue has changed

class FACTOR_CLASS
{
private:
	bool mChanged = false;
	VALUE_TYPE mValue;
	FACTOR_TYPE mFactor;

	inline void RefreshFactor()
	{
		if (mChanged)
		{
			if (mValue == VALUE_ZERO)
				mFactor = FACTOR_ZERO;
			else
				mFactor = FACTOR_ONE / mValue;

			mChanged = false;
		};
	};
public:
	static const FACTOR_CLASS ZERO;

	FACTOR_CLASS(VALUE_TYPE val = VALUE_ZERO) { setValue(val);	};
	FACTOR_CLASS(REF(FACTOR_CLASS) rhs) { setValue(rhs.getValue());	};

	//Getters
	inline REF(VALUE_TYPE) getValue() const { return mValue;	};
	inline FACTOR_TYPE getFactor() const {
		//RefreshFactor();
		return mFactor;
	};

	//Setters
	inline void setValue(VALUE_TYPE newValue)
	{
		mValue = newValue;
		mChanged = true;
		RefreshFactor();//NOTE: unable to call in getFactor as intended due to const
	};
	inline void setFactor(FACTOR_TYPE newFactor)
	{
		mFactor = newFactor;
		mValue = VALUE_ZERO;
		if(newFactor != FACTOR_ZERO)
		mValue = FACTOR_ONE / mFactor;
	};

	//Accessors
// 	inline VALUE_TYPE& Value() { mChanged = true; return &mValue;	};
// 	inline FACTOR_TYPE& Factor() { return &mFactor	};

	//Operators
	inline REF(FACTOR_CLASS) operator =(REF(VALUE_TYPE) rhs) { setValue(rhs); return *this;	};
	inline REF(FACTOR_CLASS) operator =(REF(FACTOR_CLASS) rhs) { setValue(rhs.getValue()); return *this;	};

	//Conversion Operators
	operator REF(VALUE_TYPE)() const { return getValue();	};
};

__declspec(selectany) const FACTOR_CLASS FACTOR_CLASS::ZERO = VALUE_ZERO;

#endif
