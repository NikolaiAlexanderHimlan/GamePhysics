/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 14, 2015
*	Filename:  Vector3f.h
*
*	Description:
*		This is a simple math class for 3d points in space. This class uses floats. This class contains many math functions that are commonly used for 3d vectors.
*		WARNING, contains some pointless functions I added for fun of it.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _VECTOR3F_H
#define _VECTOR3F_H

#include <ostream>

//TODO: upon claim, add class to nah namespace

#define Vector2f(x,y) Vector3f(x,y,0.0f)
//#define Vector2f(allValues) Vector3f(allValues)
#define VectParam const Vector3f&

class Rotation;
enum Axis;

class Vector3f
{
#define DV DEFAULT_VAL
public:
	float x;
	float y;
	float z;

public:
	Vector3f();
	Vector3f(float allValues)
		: Vector3f(allValues, allValues, allValues)
	{};//[NAH]
	Vector3f(float x, float y);
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f &rhs);
	Vector3f(const Vector3f *rhs);
	Vector3f(const float xyz[3]);
	Vector3f(Axis direction)
		: Vector3f(AxisNormal(direction))
	{};//[NAH]
	~Vector3f();

	//setters
	void Set(float x, float y, float z); //set all the values of the vector in a single line of a code

	//getters
	float getAngleY( const Vector3f& toVector );

	//operators overloads
	Vector3f& operator = ( const Vector3f& rhs );
	//Should do this manually// Vector3f& operator = ( const float& rhs ) { x = rhs;	y = rhs;	z = rhs;	return *this;	};//[NAH]
	Vector3f& operator += ( const Vector3f& rhs );
	Vector3f& operator -= ( const Vector3f& rhs );
	Vector3f& operator *= ( const Vector3f& rhs );
	Vector3f& operator /= ( const Vector3f& rhs );
	Vector3f& operator *= ( float mult );
	Vector3f& operator /= ( float div );
	
	const Vector3f Vector3f::operator+(const Vector3f &other) const;
	const Vector3f Vector3f::operator-(const Vector3f &other) const;
	//const Vector3f Vector3f::operator*(VectParam other) const;//Require explicit call to either Multiply or DotProduct
	const Vector3f Vector3f::operator/(const Vector3f &other) const;
	const Vector3f Vector3f::operator*(float mult) const;
	const Vector3f Vector3f::operator/(float div) const;
	const Vector3f operator-() const;

	bool Vector3f::operator==(const Vector3f &other) const;
	bool Vector3f::operator!=(const Vector3f &other) const;

	friend std::ostream& Vector3f::operator<<(std::ostream& stream, const Vector3f& vector);
	std::string toString() const;
	void toArray(float floatArray[3]);

	//math functions
	//more expensive, actual length of the vector
	inline float Length() const
	{ return sqrt(LengthSquared());	};//[NAH]
	//Cheaper than length, useful for comparing the lengths of vectors
	inline float LengthSquared() const
	{ return pow(x, 2.0f) + pow(y, 2.0f) + pow(z, 2.0f);	};//[NAH]

	void normalize(); //make the vector length 1
	//returns a vector of length 1 in the direction of this vector
	inline Vector3f Normalized() const//[NAH]
	{
		Vector3f toNormalize = *this;
		toNormalize.normalize();
		return toNormalize;
	};

	//Modifiers
	inline void setLength(float length)//Normalize then multiply by the new length
	{ normalize(); *this *= length;	};//[NAH] //make the vector length a specific value

	//Math functions
	void power(float power);

	//Comparison functions
	inline bool Equals_Any(VectParam rhs) const
	{ return x == rhs.x || y == rhs.y || z == rhs.z;	};//[NAH]
	inline bool Equals_All(VectParam rhs) const
	{ return x == rhs.x && y == rhs.y && z == rhs.z;	};//[NAH]
	inline bool Equals_NonZero(const Vector3f& rhs) const//compares the values of the vectors, ignoring values of 0
	{
		bool isEqual = true;

		if (x != 0 && rhs.x != 0)
			isEqual &= (x == rhs.x);
		if (y != 0 && rhs.y != 0)
			isEqual &= (y == rhs.y);
		if (z != 0 && rhs.z != 0)
			isEqual &= (z == rhs.z);

		return isEqual;
	}
	inline bool Greater_Any(VectParam rhs) const
	{ return x > rhs.x || y > rhs.y || z > rhs.z;	};//[NAH]
	inline bool Greater_All(VectParam rhs) const
	{ return x > rhs.x && y > rhs.y && z > rhs.z;	};//[NAH]
	inline bool Greater_NonZero(VectParam rhs) const;//[NAH]
	bool GreaterEqual_Any(const Vector3f& rhs) const
	{ return Greater_Any(rhs) || Equals_Any(rhs);	};//[NAH]
	bool GreaterEqual_All(const Vector3f& rhs) const
	{ return x >= rhs.x && y >= rhs.y && z >= rhs.z;	};//[NAH] //NOTE: needs an implementation instead of function wrapper because some of the values might be less and some of them might be equal
	inline bool GreaterEqual_NonZero(VectParam rhs) const;//[NAH]

	//static math functions
	//@return a positive version of the vector
	static inline Vector3f abs(VectParam makeAbsolute)
	{ return Vector3f(std::abs(makeAbsolute.x), std::abs(makeAbsolute.y), std::abs(makeAbsolute.z)); };//[NAH]

	//TODO: make inline upon claim
	static Vector3f ClampMax(VectParam clampThis, VectParam clampMax);//[NAH]
	static Vector3f ClampMaxKeepSign(VectParam clampThis, VectParam clampMax);//[NAH]

	/// <summary> Subtracts the right hand value from the vector if the value is not 0. </summary>
	/// <param name="keepLeftOnZero">
	/// If true, will use the values of the left hand vector if either value is 0. 
	/// <para> Overrides the [keepRightOnZero] parameter. </para>
	/// </param>
	/// <param name="keepRightOnZero"> If true, will use the values of the right hand vector if either value is 0. </param>
	static inline Vector3f Subtract_NonZero(Vector3f lhs, VectParam rhs, bool keepLeftOnZero = false, bool keepRightOnZero = false)
	{
		if (lhs.x != 0 && rhs.x != 0)
			lhs.x -= rhs.x;
		else if (!keepLeftOnZero)
			lhs.x = 0;
		else if (keepRightOnZero)
			lhs.x = rhs.x;

		if (lhs.y != 0 && rhs.y != 0)
			lhs.y -= rhs.y;
		else if (!keepLeftOnZero)
			lhs.y = 0;
		else if (keepRightOnZero)
			lhs.y = rhs.y;

		if (lhs.z != 0 && rhs.z != 0)
			lhs.z -= rhs.z;
		else if (!keepLeftOnZero)
			lhs.z = 0;
		else if (keepRightOnZero)
			lhs.z = rhs.z;

		return lhs;
	};//[NAH]
	static Vector3f Multiply(Vector3f lhs, VectParam rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
		return lhs;
	};//[NAH]
	static float DotProduct(const Vector3f &first, const Vector3f &second);
	static float CrossProductF(const Vector3f &first, const Vector3f &second);
	static Vector3f CrossProduct(const Vector3f &first, const Vector3f &second);

	static inline float Distance(VectParam first, VectParam second)
	{ return sqrt(DistanceSquared(first, second));	};//[NAH]
	static inline float DistanceSquared(VectParam first, VectParam second)
	{ return Difference(first, second).LengthSquared();	};//[NAH]

	static inline Vector3f Difference(const Vector3f &first, const Vector3f &second) { return second - first;	};//[NAH] //gets a vector representing the space between 2 other vectors
	static inline Vector3f DirectionFrom(const Vector3f &from, const Vector3f &to) { return from + DirectionTo(from, to);	};//[NAH] //gets a unit vector pointing from first to second
	static inline Vector3f DirectionTo(const Vector3f &from, const Vector3f &to)
	{ return Difference(from, to).Normalized(); };//[NAH] //gets a unit vector representing the direction from first to second
	/// <summary>Gets the point a given distance between 2 vectors. </summary>
	/// <param name="first"></param>
	/// <param name="second"></param>
	/// <param name="distance"> actual distance value, will move this amount from first to second. </param>
	/// <returns>Location of the point.</returns>
	static inline Vector3f Distancepoint(const Vector3f &first, const Vector3f &second, float distance) { return first + DirectionTo(first, second) * distance; };//[NAH]
	/// <param name="value"> value between 0 and 1 representing a range. </param>
	static inline Vector3f Betweenpoint(const Vector3f &first, const Vector3f &second, float value) { return first + (Difference(first, second) * value); };//[NAH] //value between 0 and 1
	static inline Vector3f Midpoint(const Vector3f &first, const Vector3f &second) { return Betweenpoint(first, second, 0.5f); };
	static inline Vector3f Quaterpoint(const Vector3f &first, const Vector3f &second) { return Betweenpoint(first, second, 0.25f); };
	static inline Vector3f ThreeQuaterpoint(const Vector3f &first, const Vector3f &second) { return Betweenpoint(first, second, 0.75f); };
	
	static Vector3f Reciprical(const Vector3f &vector);
	static Vector3f EulerForward(float pitch, float yaw, float roll);
	static Vector3f getLookAtAngle(const Vector3f& eye, const Vector3f& lookAt);//[NAH] //calculates the necessary angle in order to look at a given location from this location
	static void vectorArrayToFloatArray(float floatArray[], const Vector3f *vectorArray, int vectorArraySize); //fill a float array from an array of vector3s

	static inline bool isBetween(VectParam lhs, VectParam rhs, VectParam checkBetween)
	{ return (rhs - lhs).GreaterEqual_All(checkBetween - lhs);	};//[NAH]

	Vector3f asRad() const;
	static const Vector3f& AxisNormal(Axis toNorm);//[NAH]
	//TODO: try to find a better name for the NormalWeight functions
	/// <summary> Takes a vector and a normal and returns the vector weighted against the normal.
	/// <para> EX. weighting (6, 5, 8) against (0,1,0)[UP] would return (0, 5, 0). </para>
	/// </summary>
	/// <param name="vector">The vector that is weighted against the normal.</param>
	/// <param name="normal">The normal to weight against.</param>
	/// <returns>The weighted version of the vector.</returns>
	static Vector3f NormalWeight(VectParam vector, VectParam normal)
	{ return Multiply(vector, normal); };//[NAH]
	/// <summary> Takes a vector and a normal and returns the vector inversely weighted against the normal.
	/// <para> EX. weighting (6, 5, 8) against (0,1,0)[UP] would return (0, 5, 0). </para>
	/// <para> On the other hand, inversely weighting the previous vector with the normal would return (6, 0, 8). </para>
	/// </summary>
	/// <param name="vector">The vector that is weighted against the normal.</param>
	/// <param name="normal">The normal to inversely weight against.</param>
	/// <returns>The weighted version of the vector.</returns>
	static Vector3f InvertNormalWeight(VectParam vector, VectParam normal)
	{ return normal - NormalWeight(vector, normal);  };//[NAH]
	static inline Vector3f clearAxes_Key(Vector3f vector, Axis axisKey);//[NAH]
	//clears axes of a vector if the corresponding axis in axisKey is 0
	static inline Vector3f clearAxes_Key(Vector3f vector, VectParam axisKey)
	{
		//TODO: handle float precision
		if (axisKey.x == 0)
			vector.x = 0;
		if (axisKey.y == 0)
			vector.y = 0;
		if (axisKey.z == 0)
			vector.z = 0;

		return vector;
	};//[NAH]

public:
	static const float DEFAULT_VAL;
	//constant vectors
	const static Vector3f defaultVect;
	const static Vector3f zero;
	const static Vector3f one;
	const static Vector3f unitX;
	const static Vector3f unitY;
	const static Vector3f unitZ;
};

#endif

