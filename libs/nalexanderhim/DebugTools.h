/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _DEBUGTOOLS_H
#define _DEBUGTOOLS_H

//#include "IntCoord.h"
#include "CodingDefines.h"

void LOG_WARNING(const char* warningMessage);
void LOG_ERROR(const char* errorMessage);

class Vector3f;
namespace nah {
	class Color;
}
class Debug_OpenGL
{
public:
	//NOTE: not really a debug tool specifically, move elsewhere
	static void outputText(REF(Vector3f) location, const nah::Color& color, void* font, const char* text);
};

#endif
