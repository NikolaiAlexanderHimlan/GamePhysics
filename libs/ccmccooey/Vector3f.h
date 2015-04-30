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

//TODO: upon claim: 
// * add class to nah namespace

#define Vector2f(x,y) Vector3f(x,y,0.0f)
//#define Vector2f(allValues) Vector3f(allValues)
#define VectParam const Vector3f&

//pre-engine declarations
enum Axis;
typedef float ufloat;

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
	Vector3f(const Vector3f* rhs);
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
		//Math
	inline const Vector3f operator + (VectParam rhs) const { return Add(*this, rhs);	};//[NAH]
	inline const Vector3f operator - (VectParam rhs) const { return Subtract(*this, rhs);	};//[NAH]
	inline const Vector3f operator / (VectParam rhs) const { return Divide(*this, rhs);	};//[NAH]
	inline const Vector3f operator - () const { return Inverse();	};//[NAH]
	
		//Assignment
	Vector3f& operator = ( const Vector3f& rhs );
	//Should do this manually// Vector3f& operator = ( const float& rhs ) { x = rhs;	y = rhs;	z = rhs;	return *this;	};//[NAH]
	Vector3f& operator *= ( float mult );
	inline Vector3f& operator += (VectParam rhs) { return *this = *this + rhs;	};//[NAH]
	inline Vector3f& operator -= (VectParam rhs) { return *this = *this - rhs;	};//[NAH]
	//Vector3f& operator *= ( VectParam rhs );//Require explicit call to either Multiply or DotProduct
	inline Vector3f& operator /= (VectParam rhs) { return *this = *this / rhs;	};//[NAH]
	Vector3f& operator /= (float div);

	//const Vector3f Vector3f::operator*(VectParam other) const;//Require explicit call to either Multiply or DotProduct
	const Vector3f Vector3f::operator*(float mult) const;
	const Vector3f Vector3f::operator/(float div) const;

		//Comparison
	bool Vector3f::operator==(VectParam other) const;
	bool Vector3f::operator!=(VectParam other) const;

		//Conversion
	friend std::ostream& Vector3f::operator<<(std::ostream& stream, const Vector3f& vector);
	std::string toString() const;
	void toArray(float outArray[3]) const;

	//math functions
	inline Vector3f Inverse() const { return Vector3f(-x, -y, -z);	};//[NAH]
	//more expensive, actual length of the vector
	inline ufloat Length() const
	{ return sqrt(LengthSquared());	};//[NAH]
	//Cheaper than length, useful for comparing the lengths of vectors
	inline ufloat LengthSquared() const
	{ return pow(x, 2.0f) + pow(y, 2.0f) + pow(z, 2.0f);	};//[NAH]

	//returns a vector of length 1 in the direction of this vector
	inline Vector3f getNormalized() const//[NAH]
	{
		Vector3f toNormalize = *this;
		toNormalize.Normalize();
		return toNormalize;
	};

	//Modifiers
	inline void setLength(float length)//Normalize then multiply by the new length
	{ Normalize(); *this *= length;	};//[NAH] //make the vector length a specific value
	void Normalize(); //make the vector length 1

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
	{ return Vector3f(std::abs(makeAbsolute.x), std::abs(makeAbsolute.y), std::abs(makeAbsolute.z));	};//[NAH]

	//TODO: make inline upon claim
	static Vector3f ClampMax(VectParam clampThis, VectParam clampMax);//[NAH]
	static Vector3f ClampMaxKeepSign(VectParam clampThis, VectParam clampMax);//[NAH]

	inline static Vector3f Add(Vector3f lhs, VectParam rhs, bool lhsRotationType = true) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		return lhs;
	};//[NAH]
	inline static Vector3f Subtract(VectParam lhs, VectParam rhs) { return Add(lhs, -rhs);	};
	/// <summary> Subtracts the right hand value from the vector if the value is not 0. </summary>
	/// <param name="keepLeftOnZero">
	/// If true, will use the values of the left hand vector if either value is 0. 
	/// <para> Overrides the [keepRightOnZero] parameter. </para>
	/// </param>
	/// <param name="keepRightOnZero"> If true, will use the values of the right hand vector if either value is 0. </param>
	static Vector3f Subtract_NonZero(Vector3f lhs, VectParam rhs, bool keepLeftOnZero = false, bool keepRightOnZero = false);//[NAH]
	static inline Vector3f Multiply(Vector3f lhs, VectParam rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
		return lhs;
	};//[NAH]
	inline static Vector3f Divide(Vector3f lhs, VectParam rhs) {
		lhs.x = lhs.x / rhs.x;
		lhs.y = lhs.y / rhs.y;
		lhs.z = lhs.z / rhs.z;
		return lhs;
	};//[NAH]
	static float DotProduct(VectParam first, VectParam second);
	static float CrossProductF(VectParam first, VectParam second);
	static Vector3f CrossProduct(VectParam first, VectParam second);

	static inline ufloat Distance(VectParam first, VectParam second)
	{ return sqrt(DistanceSquared(first, second));	};//[NAH]
	static inline ufloat DistanceSquared(VectParam first, VectParam second)
	{ return Difference(first, second).LengthSquared();	};//[NAH]

	static inline Vector3f Difference(VectParam first, VectParam second)
	{ return second - first;	};//[NAH] //gets a vector representing the space between 2 other vectors
	static inline Vector3f DirectionTo(VectParam from, VectParam to)
	{ return Difference(from, to).getNormalized();	};//[NAH] //gets a unit vector representing the direction from first to second
	static inline Vector3f DirectionFrom(VectParam from, VectParam to)
	{ return from + DirectionTo(from, to);	};//[NAH] //gets a unit vector pointing from first to second

	/// <summary>Gets the point a given distance between 2 vectors. </summary>
	/// <param name="first"></param>
	/// <param name="second"></param>
	/// <param name="distance"> actual distance value, will move this amount from first to second. </param>
	/// <returns>Location of the point.</returns>
	static inline Vector3f Distancepoint(VectParam first, VectParam second, float distance)
	{ return first + (DirectionTo(first, second) * distance);	};//[NAH]
	/// <param name="value"> value between 0 and 1 representing a range. </param>
	static inline Vector3f Betweenpoint(VectParam first, VectParam second, float value) { return first + (Difference(first, second) * value); };//[NAH] //value between 0 and 1
	static inline Vector3f Midpoint(VectParam first, VectParam second) { return Betweenpoint(first, second, 0.5f); };
	static inline Vector3f Quaterpoint(VectParam first, VectParam second) { return Betweenpoint(first, second, 0.25f); };
	static inline Vector3f ThreeQuaterpoint(VectParam first, VectParam second) { return Betweenpoint(first, second, 0.75f); };

	static Vector3f Reciprical(VectParam vector);
	static Vector3f EulerForward(float pitch, float yaw, float roll);
	static void vectorArrayToFloatArray(float floatArray[], const Vector3f* vectorArray, int vectorArraySize); //fill a float array from an array of vector3s

	static inline bool isBetween(VectParam lhs, VectParam rhs, VectParam checkBetween)
	{ return (rhs - lhs).GreaterEqual_All(checkBetween - lhs);	};//[NAH]

	Vector3f asRad() const;//[NAH]
	static const Vector3f& AxisNormal(Axis toNorm);//[NAH]
	//TODO: try to find a better name for the NormalWeight functions
	/// <summary> Takes a vector and a normal and returns the vector weighted against the normal.
	/// <para> EX. weighting (6, 5, 8) against (0,1,0)[UP] would return (0, 5, 0). </para>
	/// </summary>
	/// <param name="vector">The vector that is weighted against the normal.</param>
	/// <param name="normal">The normal to weight against.</param>
	/// <returns>The weighted version of the vector.</returns>
	static inline Vector3f NormalWeight(VectParam vector, VectParam normal)
	{ return Multiply(vector, normal);	};//[NAH]
	/// <summary> Takes a vector and a normal and returns the vector inversely weighted against the normal.
	/// <para> EX. weighting (6, 5, 8) against (0,1,0)[UP] would return (0, 5, 0). </para>
	/// <para> On the other hand, inversely weighting the previous vector with the normal would return (6, 0, 8). </para>
	/// </summary>
	/// <param name="vector">The vector that is weighted against the normal.</param>
	/// <param name="normal">The normal to inversely weight against.</param>
	/// <returns>The weighted version of the vector.</returns>
	static inline Vector3f InvertNormalWeight(VectParam vector, VectParam normal)
	{ return normal - NormalWeight(vector, normal);	};//[NAH]
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

