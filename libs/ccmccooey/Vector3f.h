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
	Vector3f(float allValues);
	Vector3f(float x, float y);
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f &rhs);
	Vector3f(const Vector3f *rhs);
	Vector3f(const float xyz[3]);
	Vector3f(Axis direction) : Vector3f(AxisNormal(direction)) {};
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
	const Vector3f Vector3f::operator*(const Vector3f &other) const;
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
	float length() const;
	//Cheaper than length, useful for comparing the lengths of vectors
	float lengthSquared() const;
	void normalize(); //make the vector length 1
	//returns a vector of length 1 in the direction of this vector
	inline Vector3f Normalized() const//[NAH]
	{
		Vector3f toNormalize = *this;
		toNormalize.normalize();
		return toNormalize;
	};
	void setLength(float length); //make the vector length a specific value
	void power(float power);

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
	bool GreaterEqual_Any(const Vector3f& rhs) const
	{
		return
			x >= rhs.x || 
			y >= rhs.y || 
			z >= rhs.z;
	};//[NAH]
	bool GreaterEqual_All(const Vector3f& rhs) const
	{
		return 
			x >= rhs.x && 
			y >= rhs.y && 
			z >= rhs.z;
	};//[NAH]

	//static math functions
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

	static float Distance(const Vector3f &first, const Vector3f &second);
	static float DistanceSquared(const Vector3f &first, const Vector3f &second);
	
	static bool Between(const Vector3f& lhs, Vector3f rhs, const Vector3f& checkBetween)
	{
		return (rhs - lhs).GreaterEqual_All(checkBetween - lhs);
	};//[NAH]

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
	/// <param name="value"> value between 0 and 1 </param>
	static inline Vector3f Betweenpoint(const Vector3f &first, const Vector3f &second, float value) { return first + (Difference(first, second) * value); };//[NAH] //value between 0 and 1
	static inline Vector3f Midpoint(const Vector3f &first, const Vector3f &second) { return Betweenpoint(first, second, 0.5f); };
	static inline Vector3f Quaterpoint(const Vector3f &first, const Vector3f &second) { return Betweenpoint(first, second, 0.25f); };
	static inline Vector3f ThreeQuaterpoint(const Vector3f &first, const Vector3f &second) { return Betweenpoint(first, second, 0.75f); };
	
	static Vector3f Reciprical(const Vector3f &vector);
	static Vector3f EulerForward(float pitch, float yaw, float roll);
	static Vector3f getLookAtAngle(const Vector3f& eye, const Vector3f& lookAt);//[NAH] //calculates the necessary angle in order to look at a given location from this location
	static void vectorArrayToFloatArray(float floatArray[], const Vector3f *vectorArray, int vectorArraySize); //fill a float array from an array of vector3s

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

//Static Values
__declspec(selectany) const float Vector3f::DEFAULT_VAL = 0.0f;//[NAH]
__declspec(selectany) const Vector3f Vector3f::defaultVect = Vector3f(DV, DV, DV);//[NAH]

#endif

