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


/*
*/

#ifndef INC_WINCOORD
#define INC_WINCOORD

#include "oilcoord.h"

class OilCoord;
class Matrix;
class View;

/********************************************************************************************

>	class CCAPI WinCoord : public wxPoint

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/1993          
	Base Class: The wx point coordinate structure, wxPoint.
	Purpose:	Structure holding a 16-bit/32-bit (Win16/Win32) cartesian coordinate.  Its
				main use is to hold the coordinates supplied to and from the operating 
				system.  The origin for this coordinate system is the top-left of the screen
				or window.

********************************************************************************************/

class CCAPI WinCoord : public wxPoint
{
public:
	WinCoord() : wxPoint() {}
	WinCoord(INT32 x, INT32 y);
	WinCoord(wxPoint pt);

	OilCoord ToOil(View *pView, BOOL PixelCentre = FALSE) const;
};

#endif	// INC_WINCOORD
