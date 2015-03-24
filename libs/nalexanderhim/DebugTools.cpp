/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "DebugTools.h"

#include <string>
#include <iostream>

void LOG_WARNING(const char* warningMessage)
{
	//TODO: platform independent
	//TODO: prepend with warning information
	//TODO: get line number where this function is called
	std::cerr << warningMessage << std::endl;
}
void LOG_ERROR(const char* errorMessage)
{
	//TODO: platform independent
	//TODO: prepend with warning information
	//TODO: get line number where this function is called
	std::cerr << errorMessage << std::endl;
	__debugbreak();
}

#include <GLTools.h>
#include <GL/glut.h>

#include "GraphicsGlobals.h"
#include "ccmccooeyWrapper.h"
#include "Color.h"

void Debug_OpenGL::outputText(const Vector3f& location, const nah::Color& color, void* font, const char* text)
{
	const char* charText = text;// text.c_str();
	int len = (int)strlen(charText);

	/*added 1
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, getWindowWidth, 0, getWindowHeight, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	
	//plus 3
	glDisable(GL_TEXTURE_2D);
	//*/
	/*added 2

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, getWindowWidth(), 0.0, getWindowHeight());

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//*/
	//added 4
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glColor3f(color.rgbRed(), color.rgbGreen(), color.rgbBlue());


	/*added 4
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, getWindowWidth(), 0, getWindowHeight());
	glScalef(1, -1, 1);
	glTranslatef(0, -getWindowHeight(), 0);
	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
	glLoadIdentity();
	//*/


	//*2D Text
	//(x,y) is from the bottom left of the window
	glRasterPos2f(location.x, location.y);
	//*/
	/*/3D Text
	//glTranslatef(location.x, location.y, location.z);
	//*/

	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, charText[i]);
		//glutStrokeCharacter(font, charText[i]);
	}

	/*added 1
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//*/
	/*added 2
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	//plus 3
	glEnable(GL_TEXTURE_2D);
	//*/
	/*added 4
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//*/
}
