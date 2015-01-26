/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _DEBUGTOOLS_H
#define _DEBUGTOOLS_H

#include "ccmccooeyWrapper.h"
#include "Color.h"
//#include "IntCoord.h"

class Debug_OpenGL
{
public:
	static void outputText(const Vector3f& location, const nah::Color& color, void* font, const char* text);
};

#endif
