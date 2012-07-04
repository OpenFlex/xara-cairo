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
 *  */

/*********************************************************************************************

>	class WorkCoord

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/5/1993          
	Purpose:	Structure holding a 64-bit cartesian coordinate.
				Its main use is to hold the coordinates of scrolled objects in CCamView.
	Errors:		None.



*********************************************************************************************/

#ifndef INC_WRKCOORD
#define INC_WRKCOORD

#include "ccmaths.h"						// for XLONG
#include "coord.h"							// for Coord

class OSCoord;
class OilCoord;

class CCAPI WorkCoord
{
public:
	XLONG x;
	XLONG y;

	WorkCoord() { };
	WorkCoord( INT32 x, INT32 y);
	WorkCoord( XLONG x, XLONG y);

	OilCoord ToOil(const WorkCoord& scrollOffset);
	void ToOil(const WorkCoord& scrollOffset, OilCoord *result);

	WorkCoord& operator=(const Coord&);
	friend WorkCoord operator-(const WorkCoord&);

	WorkCoord Pixelise(double pixwidthx, double pixwidthy) {return WorkCoord(
		(INT64)((floor(0.5 + (double)x / pixwidthx)) * pixwidthx),
		(INT64)((floor(0.5 + (double)x / pixwidthy)) * pixwidthy)
		);}
};

/********************************************************************************************

>	WorkCoord::WorkCoord( XLONG x, XLONG y )

>	WorkCoord::WorkCoord( INT32 x, INT32 y )

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		x and y positions, as ints or XLONGs
	Outputs:	None
	Purpose:	Constructor that can initialise elements
	Errors:		None

********************************************************************************************/

inline WorkCoord::WorkCoord( XLONG initialX, XLONG initialY )
{
	x = initialX;
	y = initialY;
}

inline WorkCoord::WorkCoord( INT32 initialX, INT32 initialY )
{
	x = (XLONG) initialX;
	y = (XLONG) initialY;
}


/********************************************************************************************

>	WorkCoord& WorkCoord::operator=(const Coord& input)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		A Coord
	Outputs:	A WorkCoord
	Purpose:	Safe casting between types using operator overloading.
	Errors:		None

********************************************************************************************/


inline WorkCoord& WorkCoord::operator=(const Coord& input)
{
	this->x = input.x;
	this->y = input.y;

	return *this;
}

/********************************************************************************************

>	WorkCoord& operator-(const WorkCoord& input)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/6/93
	Inputs:		A WprkCoord
	Outputs:	A WorkCoord
	Purpose:	Negates a WorkCoord.
	Errors:		None

********************************************************************************************/

inline WorkCoord operator-(const WorkCoord& input)
{
	WorkCoord result;

	result.x = -input.x;
	result.y = -input.y;
	return result;
}


#endif
