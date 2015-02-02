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

class Vector3f
{
public:
	float x;
	float y;
	float z;

public:
	Vector3f();
	Vector3f(float x);
	Vector3f(float x, float y);
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f &rhs);
	Vector3f(const Vector3f *rhs);
	Vector3f(const float xyz[3]);
	~Vector3f();

	//setters
	void Set(float x, float y, float z); //set all the values of the vector in a single line of a code

	//getters
	float getAngleY( const Vector3f& toVector );

	//operators overloads
	Vector3f& operator = ( const Vector3f& rhs );
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
	float length() const;
	float lengthSquared() const;
	void normalize(); //make the vector length 1
	//returns a vector of length 1 in the direction of this vector
	inline Vector3f normalized() const
	{
		Vector3f toNormalize = *this;
		toNormalize.normalize();
		return toNormalize;
	}
	void setLength(float length); //make the vector length a specific value
	void power(float power);

	//static math functions
	static float DotProduct(const Vector3f &first, const Vector3f &second);
	static float CrossProductF(const Vector3f &first, const Vector3f &second);
	static Vector3f CrossProduct(const Vector3f &first, const Vector3f &second);
	static float Distance(const Vector3f &first, const Vector3f &second);
	static float DistanceSquared(const Vector3f &first, const Vector3f &second);
	static Vector3f Midpoint(const Vector3f &first, const Vector3f &second);
	static Vector3f Quaterpoint(const Vector3f &first, const Vector3f &second);
	static Vector3f ThreeQuaterpoint(const Vector3f &first, const Vector3f &second);
	static Vector3f Betweenpoint(const Vector3f &first, const Vector3f &second, float value); //value between 0 and 1
	static Vector3f Reciprical(const Vector3f &vector);
	static Vector3f EulerForward(float pitch, float yaw, float roll);
	static void vectorArrayToFloatArray(float floatArray[], const Vector3f *vectorArray, int vectorArraySize); //fill a float array from an array of vector3s

public:
	//constant vectors
	const static Vector3f zero;
	const static Vector3f one;
	const static Vector3f unitX;
	const static Vector3f unitY;
	const static Vector3f unitZ;
};

#endif

