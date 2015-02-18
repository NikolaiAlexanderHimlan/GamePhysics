//DO NOT INCLUDE THIS ANYWHERE!
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

//This file is included by files which have the missing defines to create a set of class types which are nearly identical.
// #define FACTOR_CLASS
// #define VALUE_TYPE
// #define VALUE_ZERO
// #define FACTOR_TYPE
// #define FACTOR_ONE

//TODO: CONSIDER: maybe this should be a Template T class instead, but that doesn't forcefully limit it to numbers

class FACTOR_CLASS
{
private:
	VALUE_TYPE mValue;
	FACTOR_TYPE mFactor;
public:
	FACTOR_CLASS(VALUE_TYPE val = VALUE_ZERO) { setValue(val); };
	FACTOR_CLASS(const FACTOR_CLASS& rhs) { setValue(rhs.getValue()); };

	//Getters
	inline VALUE_TYPE getValue() const { return mValue; };
	inline FACTOR_TYPE getFactor() const { return mFactor; };

	//Setters
	inline void setValue(VALUE_TYPE newValue)
	{
		mValue = newValue;
		mFactor = FACTOR_ONE / mValue;
	}
	inline void setFactor(FACTOR_TYPE newFactor)
	{
		mFactor = newFactor;
		mValue = FACTOR_ONE / mFactor;
	}

	//Accessors
// 	inline VALUE_TYPE& Value() { return &mValue;	};
// 	inline FACTOR_TYPE& Factor() { return &mFactor	};

	//Operators
	inline FACTOR_CLASS& operator =(const VALUE_TYPE& rhs) { setValue(rhs); return *this; };
	inline FACTOR_CLASS& operator =(const FACTOR_CLASS& rhs) { setValue(rhs.getValue()); return *this; };

	//Conversion Operators
	operator VALUE_TYPE() const { return getValue(); };
};
#endif
