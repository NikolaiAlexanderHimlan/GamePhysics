/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: pa 4
Certification of Authenticity:
I certify that this class is essentially a copy of the Vector2D class provided to our class by Dean Lawson.
*/
#include "IntCoord.h"
#include <cmath>
//#include <Vector2D.h>

using namespace nah;

IntCoord::IntCoord(int x /*= 0*/, int y /*= 0 */)
	:mX( x )
	,mY( y )
{
}
/*
IntCoord::IntCoord(Vector2D coord)
	:mX( (int)coord.getX() )
	,mY( (int)coord.getY() )
{
}
*/
IntCoord::IntCoord(REF(IntCoord) rhs)
	:mX( rhs.mX )
	,mY( rhs.mY )
{
}
IntCoord::~IntCoord()
{
}

const IntCoord nah::IntCoord::absGet() const { return IntCoord(abs(getX()),abs(getY()));	}

#include <sstream>//included to convert integers to std::string
#include <cmath>//used to buffer the values
std::string IntCoord::toString(int buffer /*= 1*/) const
{
	//return "{" + mX + ", " + mY + "}";//does not work

	std::string xBuffer = "";
	std::string yBuffer = "";
	while(buffer > 0)//buffer the numbers
	{
		buffer--;//go down

		if(mX < std::pow(10, buffer))
			xBuffer.append("0");
		if(mY < std::pow(10, buffer))
			yBuffer.append("0");
	}

	//source: http://stackoverflow.com/a/900035
	std::stringstream sstm;
	sstm << "{" << xBuffer << mX << ", " << yBuffer << mY << "}";
	return sstm.str();
}

//IntCoord::operator Vector2D () const { return Vector2D((float)getX(), (float)getY());	}