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

// RRCaps are the render region caps. This lets us know what a render region can and can't
// render.

/*
*/

#include "camtypes.h"

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_MEMDUMP(RRCaps, CC_CLASS_MEMDUMP)

// Better Memory Dumps
#define new CAM_DEBUG_NEW


/********************************************************************************************

>	RRCaps::RRCaps()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	Constructor. Sets all the params to FALSE

********************************************************************************************/

RRCaps::RRCaps()
{
	// by default we can render nothing
	CanDoNothing();
}



/********************************************************************************************

>	RRCaps::RRCaps(const RRCaps& Other)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Inputs:		Other - the one to copy
	Returns:	this one
	Purpose:	copies the data from one RRCaps object to another

********************************************************************************************/

RRCaps::RRCaps(const RRCaps& Other)
{
	// Copy all the params from the other one
	Transparency = Other.Transparency;
	GradFills = Other.GradFills;
	PerspectiveGradFills = Other.PerspectiveGradFills;
	BitmapFills = Other.BitmapFills;
	PerspectiveBitmapFills = Other.PerspectiveBitmapFills;
	LineAttrs = Other.LineAttrs;
	ArrowHeads = Other.ArrowHeads;
	DashPatterns = Other.DashPatterns;
	SimpleBitmaps = Other.SimpleBitmaps;
	ArbitraryBitmaps = Other.ArbitraryBitmaps;
	ClippedSimpleBitmaps = Other.ClippedSimpleBitmaps;
	ClippedArbitraryBitmaps = Other.ClippedArbitraryBitmaps;
	Grad3and4Fills = Other.Grad3and4Fills;
	ClippedOutput = Other.ClippedOutput;
}



/********************************************************************************************

>	RRCaps& RRCaps::operator=(RRCaps &Other)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Inputs:		Other - the one to copy
	Returns:	this one
	Purpose:	copies the data from one RRCaps object to another

********************************************************************************************/

RRCaps& RRCaps::operator=(const RRCaps &Other)
{
	// Copy all the params from the other one
	Transparency = Other.Transparency;
	GradFills = Other.GradFills;
	PerspectiveGradFills = Other.PerspectiveGradFills;
	BitmapFills = Other.BitmapFills;
	PerspectiveBitmapFills = Other.PerspectiveBitmapFills;
	LineAttrs = Other.LineAttrs;
	ArrowHeads = Other.ArrowHeads;
	DashPatterns = Other.DashPatterns;
	SimpleBitmaps = Other.SimpleBitmaps;
	ArbitraryBitmaps = Other.ArbitraryBitmaps;
	ClippedSimpleBitmaps = Other.ClippedSimpleBitmaps;
	ClippedArbitraryBitmaps = Other.ClippedArbitraryBitmaps;
	Grad3and4Fills = Other.Grad3and4Fills;
	ClippedOutput = Other.ClippedOutput;

	// return it
	return *this;
}

/********************************************************************************************

>	RRCaps::~RRCaps()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	default desctuctor

********************************************************************************************/

RRCaps::~RRCaps()
{
	// does nothing
}



/********************************************************************************************

>	void RRCaps::CanDoAll()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	Sets all the flags in the RRCaps object to TRUE

********************************************************************************************/

void RRCaps::CanDoAll()
{
	// we can do everything
	Transparency = TRUE;
	GradFills = TRUE;
	PerspectiveGradFills = TRUE;
	BitmapFills = TRUE;
	PerspectiveBitmapFills = TRUE;
	LineAttrs = TRUE;
	ArrowHeads = TRUE;
	DashPatterns = TRUE;
	SimpleBitmaps = TRUE;
	ArbitraryBitmaps = TRUE;
	ClippedSimpleBitmaps = TRUE;
	ClippedArbitraryBitmaps = TRUE;
	Grad3and4Fills = TRUE;
	ClippedOutput = TRUE;
}


/********************************************************************************************

>	void RRCaps::CanDoNothing()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	Sets all the flags in the RRCaps object to FALSE

********************************************************************************************/

void RRCaps::CanDoNothing()
{
	// we can do nothing :-(
	Transparency = FALSE;
	GradFills = FALSE;
	PerspectiveGradFills = FALSE;
	BitmapFills = FALSE;
	PerspectiveBitmapFills = FALSE;
	LineAttrs = FALSE;
	ArrowHeads = FALSE;
	DashPatterns = FALSE;
	SimpleBitmaps = FALSE;
	ArbitraryBitmaps = FALSE;
	ClippedSimpleBitmaps = FALSE;
	ClippedArbitraryBitmaps = FALSE;
	Grad3and4Fills = FALSE;
	ClippedOutput = FALSE;
}



/********************************************************************************************

>	BOOL RRCaps::DoesRegionDoAll()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/4/95
	Returns:	TRUE if the region that owns this RRCaps can do everything
	Purpose:	This function helps to identify render regions that need no special
				treatment early on. If this function returns TRUE it means that there is
				nothing the region that this caps object belongs to can't do.

********************************************************************************************/

BOOL RRCaps::DoesRegionDoAll()
{
	// See if everything is set to TRUE
	if ((Transparency==TRUE) && 
		(GradFills==TRUE) && 
		(PerspectiveGradFills==TRUE) && 
		(BitmapFills==TRUE) && 
		(PerspectiveBitmapFills==TRUE) && 
		(SimpleBitmaps==TRUE) &&
		(ArbitraryBitmaps==TRUE) &&
		(ClippedSimpleBitmaps==TRUE) &&
		(ClippedArbitraryBitmaps==TRUE) &&
		(LineAttrs==TRUE) &&
		(ArrowHeads==TRUE) &&
		(DashPatterns==TRUE) &&
		(Grad3and4Fills==TRUE) &&
		(ClippedOutput==TRUE))
		return TRUE;

	// something was not set to TRUE
	return FALSE;
}


/********************************************************************************************

>	BOOL RRCaps::DoesRegionDoNothing()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/4/95
	Returns:	TRUE if the region that owns this RRCaps can do nothing.
	Purpose:	This function helps to identify render regions that need special
				treatment early on. If this function returns TRUE it means that there is
				nothing the region can do.

********************************************************************************************/

BOOL RRCaps::DoesRegionDoNothing()
{
	// See if everything is set to TRUE
	if ((Transparency==FALSE) && 
		(GradFills==FALSE) && 
		(PerspectiveGradFills==FALSE) && 
		(BitmapFills==FALSE) && 
		(PerspectiveBitmapFills==FALSE) && 
		(SimpleBitmaps==FALSE) &&
		(ArbitraryBitmaps==FALSE) &&
		(ClippedSimpleBitmaps==FALSE) &&
		(ClippedArbitraryBitmaps==FALSE) &&
		(LineAttrs==FALSE) &&
		(ArrowHeads==FALSE) &&
		(DashPatterns==FALSE) &&
		(Grad3and4Fills==FALSE) &&
		(ClippedOutput==FALSE))
		return TRUE;

	// something was not set to TRUE
	return FALSE;
}
