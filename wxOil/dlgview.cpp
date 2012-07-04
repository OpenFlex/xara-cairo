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


// Simple view class for dialogs to use when rendering using RenderRegions.

/*
*/

#include "camtypes.h"
#include "dlgview.h"
#include "vstate.h"
//#include "errors.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "osrndrgn.h"

DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_DYNAMIC(DialogView, View)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/********************************************************************************************

>	BOOL DialogView::Init()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Returns:	TRUE if initialised ok;
				FALSE if not
	Purpose:	Initialise the DialogView for rendering.
	SeeAlso:	DialogView

********************************************************************************************/

BOOL DialogView::Init()
{
	// Get pixel size from screen DC.
	INT32					pixwidth, pixheight;
	wxScreenDC dc;
	wxSize ppi = OSRenderRegion::GetFixedDCPPI(dc);
	pixwidth=ppi.GetWidth();
	pixheight=ppi.GetHeight();
	
	// Set up our pixel size
	PixelWidth = FIXED16(72000.0 / pixwidth);
	PixelHeight = FIXED16(72000.0 / pixheight);
	ScaledPixelWidth = PixelWidth;
	ScaledPixelHeight = PixelHeight;

	// Get ourselves a ViewState object
	pVState = new ViewState;
	if (pVState == NULL) 
		return FALSE;

	// Connect this view state to this view
	pVState->pView = this;

	// No document for dialogs
	pDoc = NULL;

	// All ok
	return TRUE;
}

/********************************************************************************************

>	DialogView::~DialogView()

	Author:		Jim_Lynn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/11/95
	Purpose:	Destructor - the class leaks viewstates like a privatised water company - the
				destructor has to delete them.

********************************************************************************************/

DialogView::~DialogView()
{
	if (pVState != NULL)
	{
		delete pVState;
		pVState = NULL;
	}
}

/********************************************************************************************

>	BOOL DialogView::ViewStateChanged()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Returns:	TRUE (always).
	Purpose:	None - DialogView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	DialogView

********************************************************************************************/

BOOL DialogView::ViewStateChanged()
{
	return TRUE;
}

/********************************************************************************************

>	void DialogView::SetViewPixelSize()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Purpose:	Sets up the pixel size for this view object.
	SeeAlso:	DialogView

********************************************************************************************/

void DialogView::SetViewPixelSize()
{
	// Set the scaled pixel size
	ScaledPixelWidth = PixelWidth / Scale;
	ScaledPixelHeight = PixelHeight / Scale;
}

/********************************************************************************************

>	void DialogView::ContinueRenderView(RenderRegion*, Spread*, BOOL = TRUE, BOOL = TRUE,
									 BOOL bForceImmediate = FALSE)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Inputs:		N/A
	Purpose:	None - DialogView is a skeleton class that is only used to access screen
				characteristics.
	Errors:		Always => ERROR3
	SeeAlso:	DialogView

********************************************************************************************/

void DialogView::ContinueRenderView(RenderRegion*, Spread*, BOOL, BOOL,
									 BOOL bForceImmediate)
{
	ERROR3("DialogView::ContinueRenderView() should not be called!");
}

/********************************************************************************************

>	CDC *DialogView::GetRenderDC()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Returns:	NULL (always)
	Purpose:	None - DialogView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	DialogView

********************************************************************************************/

wxDC *DialogView::GetRenderDC()
{
	return NULL;
}

/********************************************************************************************

>	BOOL DialogView::GetForeBackMode()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Returns:	FALSE - dialogs don't do background rendering.
	Purpose:	None - DialogView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	DialogView

********************************************************************************************/

BOOL DialogView::GetForeBackMode()
{
	// DialogViews don't background render.
	return FALSE;
}

/********************************************************************************************

>	void DialogView::SetForeBackMode(BOOL)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Inputs:		N/A
	Purpose:	None - DialogView is a skeleton class that is only used to access screen
				characteristics.
	Errors:		ERROR3 always - dialogs cannot background render!
	SeeAlso:	DialogView

********************************************************************************************/

void DialogView::SetForeBackMode(BOOL)
{
	ERROR3("DialogView::SetForeBackMode() should not be called!");
}

/********************************************************************************************

>	DocRect DialogView::GetDocViewRect(Spread*)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Inputs:		N/A
	Returns:	An empty rectangle (always).
	Purpose:	None - DialogView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	DialogView

********************************************************************************************/

DocRect DialogView::GetDocViewRect(Spread*)
{
	DocRect Empty;
	return Empty;
}

/********************************************************************************************

>	void DialogView::SetExtent(DocCoord, DocCoord)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Inputs:		N/A
	Purpose:	None - DialogView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	DialogView

********************************************************************************************/

void DialogView::SetExtent(DocCoord, DocCoord)
{
}

/********************************************************************************************

>	WorkRect DialogView::GetViewRect()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Returns:	An empty rectangle (always).
	Purpose:	None - DialogView is a skeleton class that is only used to access screen
				characteristics.
	SeeAlso:	DialogView

********************************************************************************************/

WorkRect DialogView::GetViewRect()
{
	WorkRect Empty;
	return Empty;
}
