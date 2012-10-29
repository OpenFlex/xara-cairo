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

#include "camtypes.h"

#include "wrkrect.h"

DECLARE_SOURCE("$Revision: 1282 $");


                                  
/********************************************************************************************

>	OilRect::OilRect()

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/8/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default constructor for OilRect class.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

OilRect::OilRect() : Rect()
{
}



/********************************************************************************************

>	OilRect::OilRect(OilCoord lo, OilCoord hi)

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/8/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Constructor for OilRect class.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

OilRect::OilRect(OilCoord lo, OilCoord hi) : Rect(lo, hi)
{
}




/********************************************************************************************

>	WinRect OilRect::ToWin(View *pView) const

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/8/93
	Inputs:		pView - the view we are covnerting to.
	Returns:	A WinRect
	Purpose:	Converts an OilRect into a WinRect, using the current OilCoord pixel scales.

********************************************************************************************/

WinRect OilRect::ToWin(View *pView) const
{
	// Get pixel size for this view
	// NB. Previously this was done with 4 function calls!  - Tim
	FIXED16 PixelWidth, PixelHeight;
	pView->GetPixelSize(&PixelWidth, &PixelHeight);

	// Do the conversion and return the results.
	return WinRect(INT32(MPtoPixel(lo.x, PixelWidth)),
                  -INT32(MPtoPixel(hi.y, PixelHeight) ),
				   INT32(MPtoPixel(hi.x, PixelWidth)),
                  -INT32(MPtoPixel(lo.y, PixelHeight) ));
}




/********************************************************************************************

>	WorkRect OilRect::ToWork(const WorkCoord& ScrollOffset) const

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/8/93
	Inputs:		The current ScrollOffsets
	Outputs:	-
	Returns:	A WorkRect.
	Purpose:	Converts an OilRect into a WorkRect.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

WorkRect OilRect::ToWork(const WorkCoord& ScrollOffset) const
{
	return WorkRect(WorkCoord(ScrollOffset.x + lo.x, ScrollOffset.y + lo.y),
					WorkCoord(ScrollOffset.x + hi.x, ScrollOffset.y + hi.y));
}




DocRect OilRect::ToDoc(const Spread* pSpread, View *pView) const
{
	DocRect NewRect;

	OilCoord OilLo(lo.x, lo.y);
	OilCoord OilHi(hi.x, hi.y);
	
	// Convert the coords, leaving result in this new object
	NewRect.lo = OilLo.ToDoc( pSpread, pView);
	NewRect.hi = OilHi.ToDoc( pSpread, pView);

	return NewRect;
}
