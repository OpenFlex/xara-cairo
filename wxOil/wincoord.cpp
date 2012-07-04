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



#include "camtypes.h"

//#include "wincoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "oilcoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "view.h" - in camtypes.h [AUTOMATICALLY REMOVED]

DECLARE_SOURCE("$Revision: 1395 $");



/********************************************************************************************
>	WinCoord::WinCoord(INT32 x, INT32 y)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/93
	Inputs:		Two integers (either signed 16 or 32 bits, depending on the Windows platform).
	Outputs:	-
	Returns:	-
	Purpose:	Constructor for a WinCoord.  Calls CPoint::CPoint(x, y)
	Errors:		None.
	See Also:	class CPoint

********************************************************************************************/

WinCoord::WinCoord(INT32 x, INT32 y) : wxPoint(x, y)
{
}



/********************************************************************************************
>	WinCoord::WinCoord(INT32 x, INT32 y)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/93
	Inputs:		Two integers (either signed 16 or 32 bits, depending on the Windows platform).
	Outputs:	-
	Returns:	-
	Purpose:	Constructor for a WinCoord.  Calls CPoint::CPoint(x, y)
	Errors:		None.
	See Also:	class CPoint

********************************************************************************************/

WinCoord::WinCoord(wxPoint pt) : wxPoint(pt)
{
}



/********************************************************************************************
>	OilCoord WinCoord::ToOil(View *pView, BOOL PixelCentre = FALSE) const

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/93
	Inputs:		-
	Outputs:	-
	Returns:	The position, as an OIL coordinate, of the bottom-left corner of the pixel
				located at (this) in the Windows coordinate system.
	Purpose:	Converts a WinCoord to a OilCoord.
	Errors:		None.
	See Also:	OilCoord::ToWin()

********************************************************************************************/

OilCoord WinCoord::ToOil(View *pView, BOOL PixelCentre) const
{
	// Note that we have to negate the y coord, because Windows starts with 0 at the top
	// and then positive coordinates in a downward direction, i.e. the opposite to
	// Camelot's coordinate systems.
	// NB. More importantly, we add 1 to the y coord, because the flipping of the y axis
	//     causes a misalignment in the pixel systems.  This is because Camelot coords
	//	   specify the bottom left of the pixel, whereas GDI coords specify the top-left.
	//	   (See coord.doc for more details)
//	return OilCoord(LongMulFixed16(x, OilCoord::PixelWidth()),
//				   -LongMulFixed16(y + 1, OilCoord::PixelHeight()));

	// New info: (Phil, 17/11/94)
	// The one pixel bodge is no longer required because the pixel model has been modified
	// so that pixel coordinates are in the centres of pixels, not on any edge.
	// This allows coordinate systems to be negated without any extra work.
//	return OilCoord(LongMulFixed16(x, OilCoord::PixelWidth()),
//				   -LongMulFixed16(y, OilCoord::PixelHeight()));
	
	FIXED16 PixelWidth, PixelHeight;
	pView->GetPixelSize(&PixelWidth, &PixelHeight);
	OilCoord temp = OilCoord(LongMulFixed16(x, PixelWidth),
				   			-LongMulFixed16(y, PixelHeight)
				   			);
	if (PixelCentre)
	{
		// Coordinate is a click coord which is different than normal rectangle coords
		// Rectangle coords need to specify the joints between pixels
		// Click coords need to specify pixel centres
		// So shift this coord to the centre of the pixel above and to the right of the
		// joint specified by the raw OilCoord.
		// The amount added is just less than half a pixel so that GDraw's anti-aliasing
		// will draw thin lines predictably.
		temp.x += (PixelWidth.MakeLong()*15)/32;
		temp.y -= (PixelHeight.MakeLong()*15)/32;
	}

	return temp;
}
