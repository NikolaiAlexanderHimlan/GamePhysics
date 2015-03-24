#ifndef SpaceDefines_h__
#define SpaceDefines_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
enum Axis { 
	INVALID_AXIS = -1, 

	X, Y, Z, 
	FORWARD = Z, 
	RIGHT = X, 
	UP = Y, 
};
#define AXIS_ERROR(errCause) (throw std::logic_error(("Invalid Axis - " + (std::string)(errCause)).c_str()))

#endif // SpaceDefines_h__
