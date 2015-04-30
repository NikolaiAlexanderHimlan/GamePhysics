/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on Ian Millington's cyclone physics engine.
*/
#include "Quaternion.h"
#include "Vector3f.h"
#include <cmath>

real Quaternion::Length() const { return real_sqrt(LengthSquared());	}

void Quaternion::Normalize()
{
	real len = Length();

	// Check for zero length quaternion, and use the no-rotation quaternion in that case.
	if (len < real_epsilon) {
		r = 1;
		return;
	};

	//calculate the factor of the length
	real d = ((real)1.0) / real_sqrt(len);
	r *= d;
	i *= d;
	j *= d;
	k *= d;
}

void Quaternion::addScaledVector(REF(Vector3f) vector, real scale)
{
	Quaternion q(0,
		vector.x * scale,
		vector.y * scale,
		vector.z * scale);
	q *= *this;
	r += q.r * ((real)0.5);
	i += q.i * ((real)0.5);
	j += q.j * ((real)0.5);
	k += q.k * ((real)0.5);
}

void Quaternion::RotateByVector(REF(Vector3f) vector)
{
	Quaternion q(0, vector.x, vector.y, vector.z);
	(*this) *= q;
}

Quaternion& Quaternion::operator*=(REF(Quaternion) rhs)
{
	Quaternion q = *this;

	r = q.r * rhs.r - q.i * rhs.i -
		q.j * rhs.j - q.k * rhs.k;

	i = q.r * rhs.i + q.i * rhs.r +
		q.j * rhs.k - q.k * rhs.j;

	j = q.r * rhs.j + q.j * rhs.r +
		q.k * rhs.i - q.i * rhs.k;

	k = q.r * rhs.k + q.k * rhs.r +
		q.i * rhs.j - q.j * rhs.i;

	return *this;
}
