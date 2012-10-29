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

// Implementation of the Coord class

/*
*/

#include "camtypes.h"

/********************************************************************************************

> double Coord::Distance(const Coord& Coord) const

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/3/94
	Inputs:		A coord
	Outputs:	None
	Returns:	the distance between this coord and the given coord
	Purpose:	Accurate distance function.
	Errors:		None.

********************************************************************************************/

double Coord::Distance(const Coord& Coord) const
{
	double dx 		= (double) (this->x-Coord.x);
	double dy 		= (double) (this->y-Coord.y);
	double sumsqrs 	= (dx*dx)+(dy*dy);
	
	return (sqrt(sumsqrs));
}

