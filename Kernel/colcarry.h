/*
 * xara-cairo, a vector drawing program
 *
 * Based on Xara XL, Copyright (C) 1993-2006 Xara Group Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */


// colcarry.h : Colour Context Array definition
// This needs to be a separate header file to resolve include-deadlock between
// document.h and colcontx.h, as well as removing the dependency of document
// upon colcontx.


#ifndef INC_COLCARRY
#define INC_COLCARRY


class CCAPI ColourContext;

typedef struct
{
	ColourContext *Context[16];
} ColourContextArray;


#endif

