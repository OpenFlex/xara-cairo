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

>	class Coord

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/5/1993          
	Purpose:	Structure holding a 32-bit cartesian coordinate.
	Errors:		None.

*********************************************************************************************/

#ifndef INC_COORD
#define INC_COORD

#include <math.h>

class CAMAPI Coord
{
public:
	INT32 x;
	INT32 y;
	
	inline void translate(INT32 thatX, INT32 thatY);

	friend Coord operator-(const Coord&);

	inline BOOL operator==(const Coord&) const;
	inline BOOL operator!=(const Coord&) const;

	double Distance(const Coord&) const;

	Coord(INT32 x1, INT32 y1) { x=x1; y=y1; }
	Coord() {} 
};   

/********************************************************************************************

>	inline void Coord::translate(const INT32 thatX, const INT32 thatY)

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/5/93
	Inputs:		translation coordinates.
	Outputs:	None
	Returns:	None.
	Purpose:	tranlates a Coord by thatX and thatY.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

inline void Coord::translate(INT32 thatX, INT32 thatY) 
{
	this->x += thatX;
	this->y += thatY;
}

//-----------------------------------------------------------------------------------------

inline Coord operator-(const Coord& input)
{
Coord result;

	result.x = -input.x;
	result.y = -input.y;
	return result;
}

//-----------------------------------------------------------------------------------------

inline BOOL Coord::operator==(const Coord& input) const
{
	return ((input.x == x) && (input.y == y));
}

//-----------------------------------------------------------------------------------------

inline BOOL Coord::operator!=(const Coord& input) const
{
	return ((input.x != x) || (input.y != y));
}


#endif // INC_COORD


