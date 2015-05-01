/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 14, 2015
*	Filename:  Vector3f.cpp
*
*	Description:
*		This is a simple math class for 3d points in space. This class uses floats. This class contains many math functions that are commonly used for 3d vectors.
*		WARNING, contains some pointless functions I added for fun of it.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Vector3f.h"
#include <sstream>
#include <math.h>
#include <string.h>

//static vectors
const Vector3f Vector3f::zero = Vector3f(0.0f, 0.0f, 0.0f);
const Vector3f Vector3f::one = Vector3f(1.0f, 1.0f, 1.0f);
const Vector3f Vector3f::unitX = Vector3f(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::unitY = Vector3f(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::unitZ = Vector3f(0.0f, 0.0f, 1.0f);

//constructors
Vector3f::Vector3f()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Vector3f::Vector3f(float X, float Y)
{
	x = X;
	y = Y;
	z = 0.0f;
}
Vector3f::Vector3f(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}
Vector3f::Vector3f(const Vector3f &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}
Vector3f::Vector3f(const Vector3f *rhs)
{
	x = rhs->x;
	y = rhs->y;
	z = rhs->z;
}
Vector3f::Vector3f(const float xyz[])
{
	x = xyz[0];
	y = xyz[1];
	z = xyz[2];
}

//destructor
Vector3f::~Vector3f()
{
}

//setters
void Vector3f::Set(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

//assignment operator
Vector3f& Vector3f::operator=( const Vector3f& rhs )
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

//relative operators
/*disabled multiplication operator
Vector3f& Vector3f::operator *= ( const Vector3f& rhs )
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}
//*/
Vector3f& Vector3f::operator *= ( float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}
Vector3f& Vector3f::operator /= ( float scalar )
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

//math operators
/*disabled multiplication operator
const Vector3f Vector3f::operator*(const Vector3f &other) const
{
	return Vector3f(x * other.x, y * other.y, z * other.z);
}
//*/
const Vector3f Vector3f::operator*(float mult) const
{
	return Vector3f(x * mult, y * mult, z * mult);
}
const Vector3f Vector3f::operator/(float div) const
{
	return Vector3f(x / div, y / div, z / div);
}

//comparison operators
bool Vector3f::operator==(const Vector3f& rhs) const
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}
bool Vector3f::operator!=(const Vector3f& rhs) const
{
	return (x != rhs.x || y != rhs.y || z != rhs.z);
}

//streaming operators
std::ostream& operator<<(std::ostream& stream, const Vector3f& vector)
{
	stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}

//to string
std::string Vector3f::toString() const
{
	std::ostringstream ss;
	ss << (*this);
	return ss.str();
}
void Vector3f::toArray(float floatArray[3]) const
{
	floatArray[0] = x;
	floatArray[1] = y;
	floatArray[2] = z;
}


//math functions
void Vector3f::Normalize()
{
	float length = this->Length();
	x /= length;
	y /= length;
	z /= length;
}
void Vector3f::power(float power)
{
	x = powf(x, power);
	y = powf(y, power);
	z = powf(z, power);
}

//static math functions
float Vector3f::CrossProductF(const Vector3f &first, const Vector3f &second)
{
	return (first.y * second.z - first.z * second.y) + (first.z * second.x - first.x * second.z) + (first.x * second.y - first.y * second.x);
}
Vector3f Vector3f::CrossProduct(const Vector3f &first, const Vector3f &second)
{
	return Vector3f( (first.y * second.z - first.z - second.y), (first.z * second.x - first.x - second.z), (first.x * second.y - first.y - second.x) );
}
Vector3f Vector3f::Reciprical(const Vector3f &vector)
{
	return Vector3f( 1.0f / vector.x, 1.0f / vector.y, 1.0f / vector.z);
}

void Vector3f::vectorArrayToFloatArray(float floatArray[], const Vector3f *vectorArray, int vectorArraySize)
{
	int n = 0;
	for (int i = 0; i < vectorArraySize; i++)
	{
		floatArray[n] = vectorArray[i].x;
		floatArray[n + 1] = vectorArray[i].y;
		floatArray[n + 2] = vectorArray[i].z;
		n += 3;
	}
}

//Forward vector stuff
Vector3f Vector3f::EulerForward(float pitch, float yaw, float roll)
{
	Vector3f forward = Vector3f();
	forward.z = cosf(yaw)*cosf(pitch);
	forward.x = sinf(yaw)*cosf(pitch);
	forward.y = sinf(pitch);
	return forward;
}

