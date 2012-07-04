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

/********************************************************************************************

>	class OilCoord : public Coord

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/1993          
	Base Class: Coord
	Purpose:	Structure holding a 32-bit cartesian coordinate.
				Its main use is to hold the coordinates supplied to and from the operating 
				system.
	Errors:		None.

********************************************************************************************/

#ifndef INC_OILCOORD
#define INC_OILCOORD

#include "coord.h"
#include "doccoord.h"
#include "matrix.h"
#include "xmatrix.h"
#include "wincoord.h"


// Forward references.
class CCAPI WinCoord;
class CCAPI WorkCoord;
class Chapter;
class View;

class CCAPI OilCoord : public Coord
{
	friend class OilRect;

public:
	OilCoord() : Coord() {}
	OilCoord(MILLIPOINT xx, MILLIPOINT yy);

	WinCoord ToWin(View *pView) const;
	//WinCoord ToWin( const INT32 dpi) const;
	WinCoord ToWin( const double dpi) const;

	WorkCoord ToWork(const WorkCoord& ScrollOffset) const;
	void ToWork(const WorkCoord& scrollOffset, WorkCoord* result) const;

	DocCoord ToDoc(const Spread* pSpread, View *pView) const;
};

#endif	// INC_OILCOORD
