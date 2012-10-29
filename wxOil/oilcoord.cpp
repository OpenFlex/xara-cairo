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

#include "paper.h"
#include "chapter.h"





/*********************************************************************************************
>	OilCoord::OilCoord(MILLIPOINT xx, MILLIPOINT yy)

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27th August 1993
	Inputs:		Two INT32s (measured in millipoints).
	Outputs:	-
	Returns:	-
	Purpose:	Constructs an OIL coordinate.
	Errors:		-
	Scope:		Public

**********************************************************************************************/ 

OilCoord::OilCoord(MILLIPOINT xx, MILLIPOINT yy) : Coord(xx, yy)
{
}









/********************************************************************************************

>	WinCoord OilCoord::ToWin(View *pView) const;

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/93
	Inputs:		The view we are converting to.
	Purpose:	Converts an OilCoord to a WinCoord.

********************************************************************************************/

WinCoord OilCoord::ToWin(View *pView) const
{
	// Note that we have to negate the y coord, because Windows starts with 0 at the top
	// and then positive coordinates in a downward direction, i.e. the opposite to
	// Camelot's coordinate systems.

	// NB. More importantly, we add 1 to the y coord, because the flipping of the y axis
	//     causes a misalignment in the pixel systems.  This is because Camelot coords
	//	   specify the bottom left of the pixel, whereas GDI coords specify the top-left.
	//	   (See coord.doc for more details)

//	return WinCoord(INT32(MPtoPixel(x, xPixelScale)), -INT32(MPtoPixel(y, yPixelScale) + 1));

	// New info: (Phil, 17/11/94)
	// The one pixel bodge is no longer required because the pixel model has been modified
	// so that pixel coordinates are in the centres of pixels, not on any edge.
	// This allows coordinate systems to be negated without any extra work.

	// Get pixel size for this view
	FIXED16 PixelWidth, PixelHeight;
	pView->GetPixelSize(&PixelWidth, &PixelHeight);

	// Do the conversion and return the results.
	return WinCoord(INT32(MPtoPixel(x, PixelWidth)), -INT32(MPtoPixel(y, PixelHeight) ));
}


/********************************************************************************************

>	WinCoord OilCoord::ToWin( const INT32 dpi ) const;

	Author: 	Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/93
	Inputs:		Transform Matrix.
				dpi	the value of the destination dpi rather than assuming screen dpi 
	Outputs:	None
	Returns:	None.
	Purpose:	Same as above in that it converts an OilCoord to a WinCoord but instead of
				assuming screen dpi, as in using x/yPixelScale, it uses the specified dpi
				to work out the transformation.
	Errors:		None.

********************************************************************************************/

//WinCoord OilCoord::ToWin( const INT32 dpi ) const
//{
	// See above ToWin routine for conversion comments
	// Work out our x and y pixel scaling factors for the specified destination dpi
//	FIXED16 PixScale = 72000.0/dpi;

//	return WinCoord(INT32(MPtoPixel(x, PixScale)), -INT32(MPtoPixel(y, PixScale) ));
//}

/********************************************************************************************

>	WinCoord OilCoord::ToWin( const double dpi ) const;

	Author: 	Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/93
	Inputs:		Transform Matrix.
				dpi	the value of the destination dpi rather than assuming screen dpi 
	Outputs:	None
	Returns:	None.
	Purpose:	Same as above in that it converts an OilCoord to a WinCoord but instead of
				assuming screen dpi, as in using x/yPixelScale, it uses the specified dpi
				to work out the transformation.
				Different to above in that it takes a double dpi instead of a INT32 dpi. Now
				superceeds the above. Changed 12/12/95.
	Errors:		None.

********************************************************************************************/

WinCoord OilCoord::ToWin( const double dpi ) const
{
	// See above ToWin routine for conversion comments
	// Work out our x and y pixel scaling factors for the specified destination dpi
	FIXED16 PixScale = 72000.0/dpi;

	return WinCoord(INT32(MPtoPixel(x, PixScale)), -INT32(MPtoPixel(y, PixScale) ));
}




/********************************************************************************************

>	WorkCoord OilCoord::ToWork(const WorkCoord& ScrollOffset) const

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/93
	Inputs:		Scroll offset.
	Outputs:	None
	Returns:	None.
	Purpose:	Converts an OilCoord to a WorkCoord.
	Errors:		None.

********************************************************************************************/

WorkCoord OilCoord::ToWork(const WorkCoord& ScrollOffset) const
{
	// Add the scroll offsets to get workarea values...
	return WorkCoord(ScrollOffset.x + x, ScrollOffset.y + y);
}




/********************************************************************************************

>	void OilCoord::ToWork(const WorkCoord& scrollOffset, WorkCoord* result ) const

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/93
	Inputs:		Scroll offset.
	Outputs:	None
	Returns:	None.
	Purpose:	Converts an OilCoord to a WorkCoord.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

void OilCoord::ToWork(const WorkCoord& scrollOffset, WorkCoord* result ) const
{
// Implementation...
	// Then add the scroll offsets to get workarea values...
	result->x = scrollOffset.x + x; 
	result->y = scrollOffset.y + y;
}




/********************************************************************************************

>	DocCoord OilCoord::ToDoc(const Spread* pSpread, View *pView) const

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/93
	Inputs:		pSpread - The spread that we know that the oil coord is in
				View - the view to use when converting.
	Returns:	This coordinate as measured in DocCoords
	Purpose:	Convert an OilCoord to a DocCoord

********************************************************************************************/

DocCoord OilCoord::ToDoc(const Spread* pSpread, View* pView) const
{
	DocCoord	Return;
	WorkCoord	Point((XLONG)(this->x), (XLONG)(this->y));

	// First, convert the OilCoord into a LogicalCoord...
	FIXED16 ViewScale = pView->GetViewScale();
	WorkCoord ScrollOffset = pView->GetScrollOffsets();

	Point.x = MakeXLong( double(Point.x + ScrollOffset.x) / ViewScale.MakeDouble());
	Point.y = MakeXLong( double(Point.y + ScrollOffset.y) / ViewScale.MakeDouble());

	// Find the parent chapter
	Chapter* pChapter = (Chapter*) pSpread->FindParent();
	ENSURE( pChapter != NULL, "Spread had no parent" );
	ENSURE( pChapter->IsKindOf(CC_RUNTIME_CLASS(Chapter)), "Chapter is not a chapter" );

	// Find the depth of the chapter
	XLONG ChapDepth = pChapter->GetChapterDepth();

	// Find the chapters position
	DocCoord ChapterPos;
	ChapterPos.x = pChapter->GetPasteboardRect(TRUE, pView).lo.x; 
	ChapterPos.y = pChapter->GetPasteboardRect(TRUE, pView).hi.y;

	// Build the return value up
	Return.x = Point.x + ChapterPos.x;
	Return.y = Point.y + MakeXLong(ChapterPos.y) + ChapDepth;

	return (Return);
	
}
