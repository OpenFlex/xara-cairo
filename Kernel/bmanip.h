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


#ifndef _BITMAPMANIP_H
#define _BITMAPMANIP_H

////////////////////////////////////////////
// NB functions assume a totally transparent destination bitmap

////////////////////////////////////////////

/******************************************************************************************

>	class CBitmapManip : public CObject

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17-3-98

	Purpose:	Performs bitmap manipulations

	SeeAlso:	WebStyle program

******************************************************************************************/


class CBitmapManip : public CObject
{
public:
// applies a 3x3 filter to the bitmap
	BOOL ApplyGaussianFilter(BYTE * bits, INT32 wid, INT32 hei, INT32 matrix[3][3], 
		BOOL IgnoreBlankPixels = FALSE);
} ;

#endif


