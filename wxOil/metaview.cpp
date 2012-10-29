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


// Simple view class for metafiles to use when rendering using RenderRegions.

/*
*/

#include "camtypes.h"
#include "metaview.h"
#include "vstate.h"


CC_IMPLEMENT_DYNAMIC(MetafileView, View)

#define new CAM_DEBUG_NEW


/********************************************************************************************

>	BOOL MetafileView::Init()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Returns:	TRUE if initialised ok;
				FALSE if not
	Purpose:	Initialise the MetafileView for rendering.
	SeeAlso:	MetafileView

********************************************************************************************/

BOOL MetafileView::Init()
{
	// Metafiles are always exported in the same format.
	// This is HIENGLISH which has 1000 pixels per inch.
	// As a result, we know that there are 72 millipoints per pixel.
	PixelWidth  = FIXED16(72);
	PixelHeight = FIXED16(72);
	
	// The scaled version are the same
	ScaledPixelWidth  = PixelWidth;
	ScaledPixelHeight = PixelHeight;

	// Get ourselves a ViewState object
	pVState = new ViewState;
	if (pVState == NULL) 
		return FALSE;

	// Connect this view state to this view
	pVState->pView = this;

	// No document for metafiles
	pDoc = NULL;

	// All ok
	return TRUE;
}

/********************************************************************************************

>	BOOL MetafileView::ViewStateChanged()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Returns:	TRUE (always).
	Purpose:	None - MetafileView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	MetafileView

********************************************************************************************/

BOOL MetafileView::ViewStateChanged()
{
	return TRUE;
}

/********************************************************************************************

>	void MetafileView::SetViewPixelSize()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Purpose:	Sets up the pixel size for this view object.
	SeeAlso:	MetafileView

********************************************************************************************/

void MetafileView::SetViewPixelSize()
{
	// Set the scaled pixel size
	ScaledPixelWidth = PixelWidth;
	ScaledPixelHeight = PixelHeight;
}

/********************************************************************************************

>	void MetafileView::ContinueRenderView(RenderRegion*, Spread*, BOOL = TRUE, BOOL = TRUE,
									 BOOL bForceImmediate = FALSE)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Inputs:		N/A
	Purpose:	None - MetafileView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	MetafileView
	Errors:		Always => ERROR3

********************************************************************************************/

void MetafileView::ContinueRenderView(RenderRegion*, Spread*, BOOL, BOOL,
									 BOOL bForceImmediate)
{
	ERROR3("MetafileView::ContinueRenderView() should not be called!");
}

/********************************************************************************************

>	CDC *MetafileView::GetRenderDC()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Returns:	NULL (always)
	Purpose:	None - MetafileView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	MetafileView

********************************************************************************************/

CDC *MetafileView::GetRenderDC()
{
	return NULL;
}

/********************************************************************************************

>	BOOL MetafileView::GetForeBackMode()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Returns:	FALSE - Metafiles don't do background rendering.
	Purpose:	None - MetafileView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	MetafileView

********************************************************************************************/

BOOL MetafileView::GetForeBackMode()
{
	// MetafileViews don't background render.
	return FALSE;
}

/********************************************************************************************

>	void MetafileView::SetForeBackMode(BOOL)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Inputs:		N/A
	Purpose:	None - MetafileView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	MetafileView
	Errors:		ERROR3 always - dialogs cannot background render!

********************************************************************************************/

void MetafileView::SetForeBackMode(BOOL)
{
	ERROR3("MetafileView::SetForeBackMode() should not be called!");
}

/********************************************************************************************

>	DocRect MetafileView::GetDocViewRect(Spread*)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Inputs:		N/A
	Returns:	An empty rectangle (always).
	Purpose:	None - MetafileView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	MetafileView

********************************************************************************************/

DocRect MetafileView::GetDocViewRect(Spread*)
{
	DocRect Empty;
	return Empty;
}

/********************************************************************************************

>	void MetafileView::SetExtent(DocCoord, DocCoord)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Inputs:		N/A
	Purpose:	None - MetafileView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	MetafileView

********************************************************************************************/

void MetafileView::SetExtent(DocCoord, DocCoord)
{
}

/********************************************************************************************

>	WorkRect MetafileView::GetViewRect()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Returns:	An empty rectangle (always).
	Purpose:	None - MetafileView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	MetafileView

********************************************************************************************/

WorkRect MetafileView::GetViewRect()
{
	WorkRect Empty;
	return Empty;
}




/********************************************************************************************

>	INT32 MetafileView::GetMetafileFlatness()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Returns:	The flatness to use for metafiles
	Purpose:	Allows the format that metafiles are saved in to change, without changing
				everything else in the world.

********************************************************************************************/

INT32 MetafileView::GetMetafileFlatness()
{
	// Say how much we are prepared to flatten paths
	return 1024;
}




/********************************************************************************************

>	INT32 MetafileView::GetMetafileDPI()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Returns:	the number of pixels per inch for the metafile we are creating
	Purpose:	Allows the format that metafiles are saved in to change, without changing
				everything else in the world.

********************************************************************************************/

INT32 MetafileView::GetMetafileDPI()
{
	// We are currently using HIENGLISH mapping mode, which is at 1000 dpi
	return 1000;
}




/********************************************************************************************

>	INT32 MetafileView::GetMetafileMapMode()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Returns:	The mapping mode to use for metafiles. This is currently MM_HIENGLISH
	Purpose:	Allows the format that metafiles are saved in to change, without changing
				everything else in the world.

********************************************************************************************/

INT32 MetafileView::GetMetafileMapMode()
{
	// return the mapping mode we want to use
	return MM_ANISOTROPIC;
}



/********************************************************************************************

>	void MetafileView::GetScaleFactor(FIXED16* pXScale, FIXED16* pYScale)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Outputs:	pXScale, pYScale - the x and y scale factor to render the drawing to,
				to get the best range of values from the coord system.
	Purpose:	Allows the format that metafiles are saved in to change, without changing
				everything else in the world.

********************************************************************************************/

void MetafileView::GetScaleFactor(FIXED16* pXScale, FIXED16* pYScale)
{
	// boost the scale to get the most out of the coord range.
	// We get this figure as we need to get 1000 dpi, but a scale of 1 will give 96 dpi
	// ie 1000/96 = 10.42
	*pXScale = FIXED16(1);
	*pYScale = FIXED16(1);
}


