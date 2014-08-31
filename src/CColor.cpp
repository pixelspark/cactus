/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003-2004 Tommy van der Vorst

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
--------------------------------------------------------------------------------------------------------------------------------------------------- */


// ---------------------------------------------------------------------------------------------------------------------------------------------------
// This file contains all method implementations for the class CColor. 
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#include "../include/cactus.h"
using namespace cactus;

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Default constructor. Inits all color values with 0.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
CColor::CColor() {
	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 0;
}

CColor::CColor(int c) {
	_red = INT_GETRED(c);
	_green = INT_GETGREEN(c);
	_blue = INT_GETBLUE(c);
	_alpha = INT_GETALPHA(c);
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Constructs the color object with the specified colors.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
CColor::CColor(unsigned char red,unsigned char green, unsigned char blue) {
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = 127;
}

CColor::CColor(unsigned char red,unsigned char green,unsigned char blue, unsigned char alpha) {
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Getters and setters for CColor. All setters check their arguments with an assertion, so the program might stop when an invalid
// argument is given. However, logic errors are avoided using assertions.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char CColor::GetBlue() {
	return _blue;
}

unsigned char CColor::GetRed() {
	return _red;
}

unsigned char CColor::GetGreen() {
	return _green;
}

unsigned char CColor::GetAlpha() {
	return _alpha;
}

void CColor::SetAlpha(unsigned char alpha) {
	_alpha = alpha;
}

void CColor::SetBlue(unsigned char blue) {
	_blue = blue;
}

void CColor::SetGreen(unsigned char green) {
	_green = green;
}

void CColor::MixWith(CColor& col) {
	_red = (char)((col._red+_red)/2);
	_green = (char)((col._green+_green)/2);
	_blue = (char)((col._blue+_blue)/2);
	_alpha = (char)((col._alpha+_alpha)/2);
}

void CColor::SetRed(unsigned char red) {
	_red = red;
}

void CColor::Invert() {
	_red = (unsigned char)255-_red;
	_green = (unsigned char)255-_green;
	_blue = (unsigned char)255-_blue;
}