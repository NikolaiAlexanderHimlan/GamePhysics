/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "DebugTools.h"

#include <string>

#include <GLTools.h>
#include <GL/glut.h>

void Debug_OpenGL::outputText(const Vector3f& location, const nah::Color& color, void* font, const char* text)
{
	const char* charText = text;// text.c_str();
	int len = (int)strlen(charText);

	glPushMatrix();
	glColor3f(color.rgbRed(), color.rgbGreen(), color.rgbBlue());
	glRasterPos2f(location.x, location.y);
	//glTranslatef(location.x, location.y, location.z);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(&font, charText[i]);
	}
	glPopMatrix();
}
