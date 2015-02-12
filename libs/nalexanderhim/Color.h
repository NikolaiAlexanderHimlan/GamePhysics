/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _COLOR_H
#define _COLOR_H

//#include <Trackable.h>

#include "RandMath.h"

#if GRAPHICS_ALLEGRO
//typedef struct [Allegro ] Abstract
typedef struct ALLEGRO_COLOR	AbstractData;
typedef struct ALLEGRO_COLOR	AbstractColor;
typedef float ColorVal;
#elif GRAPHICS_DIRECTX9
//typedef struct [DirectX9 ] Abstract;
#elif GRAPHICS_SDL
#include <stdint.h>
//typedef struct [SDL ] Abstract;
typedef uint32_t			AbstractData;
typedef struct SDL_Color	AbstractColor;
typedef uint8_t	ColorVal;
#elif GRAPHICS_OPENGL
typedef float		GLfloat;
typedef GLfloat		ColorVal;
//typedef float		ColorVal;
typedef ColorVal	AbstractData;
typedef ColorVal	AbstractColor;
#endif

namespace nah
{
	//TODO: decide whether to abstract actual Color objects or keep as 3-value struct
	class Color //TODO: make struct
		//: public Trackable
	{
	public:
		static const ColorVal	MAX_COLOR;
		static const ColorVal	MIN_COLOR;
#define ALPHA_OPAQUE			MAX_COLOR
#define ALPHA_CLEAR				MIN_COLOR
		
		//CONSIDER: move to source file so RandMath is not included in header
		static inline Color RandomColor(bool randomAlpha = false) { return Color(randomFloat(MIN_COLOR, MAX_COLOR), randomFloat(MIN_COLOR, MAX_COLOR), randomFloat(MIN_COLOR, MAX_COLOR), randomAlpha?randomFloat(ALPHA_CLEAR,ALPHA_OPAQUE):ALPHA_OPAQUE); };

#pragma region Static Colors
		static const Color Empty;
		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color LightRed;
		static const Color DarkRed;
		static const Color LightGreen;
		static const Color DarkGreen;
		static const Color DarkBlue;
		static const Color LightBlue;
		static const Color Grey;
		static const Color Turqoise;
		static const Color Aqua;
		static const Color Aquamarine;
		static const Color Orange;
		static const Color Yellow;
		static const Color Pink;
		static const Color Purple;
#pragma endregion Pre-defined Color values

		Color(ColorVal red, ColorVal green, ColorVal blue, ColorVal alpha = ALPHA_OPAQUE)
		{
			mRed = red;
			mGreen = green;
			mBlue = blue;
			mAlpha = alpha;
		}
		Color(ColorVal all = ALPHA_OPAQUE)
		{
			mRed = all;
			mGreen = all;
			mBlue = all;
			mAlpha = all;
		}

		~Color(void){}

		inline ColorVal rgbRed()	const { return mRed; }
		inline ColorVal rgbGreen()	const { return mGreen; }
		inline ColorVal rgbBlue()	const { return mBlue; }
		inline ColorVal rgbAlpha()	const { return mAlpha; }

		//the type used for abstract color values
		AbstractColor getAbstractColor() const;
		//a possibly separate type for graphics relevant color data
		AbstractData getAbstractData() const;

	private:
		ColorVal mRed;
		ColorVal mGreen;
		ColorVal mBlue;
		ColorVal mAlpha;
	};
}
#endif
