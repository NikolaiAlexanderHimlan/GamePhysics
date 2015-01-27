/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Color.h"

#include <gl/glew.h>

using namespace nah;

const GLfloat nah::Color::MAX_COLOR = 1.0f;
const GLfloat nah::Color::MIN_COLOR = 0.0f;

//TODO: Figure out how to move to generic area
const Color nah::Color::White = Color::MIN_COLOR;
const Color nah::Color::Black = Color::MAX_COLOR;
const Color nah::Color::Red = Color(MAX_COLOR, MIN_COLOR, MIN_COLOR);
const Color nah::Color::Green = Color(MIN_COLOR, MAX_COLOR, MIN_COLOR);
const Color nah::Color::Blue = Color(MIN_COLOR, MIN_COLOR, MAX_COLOR);

//http://www.avatar.se/molscript/doc/colour_names.html
const Color nah::Color::Aquamarine = Color(0.498039f, 1.0f, 0.831373f);
const Color nah::Color::DarkBlue = Color(0.0f, 0.0f, 0.545098f);
const Color nah::Color::DarkGreen = Color(0.0f, 0.392157f, 0.0f);
const Color nah::Color::DarkRed = Color(0.545098f, 0.0f, 0.0f);
const Color nah::Color::Orange = Color(1.0f, 0.647059f, 0.0f);

