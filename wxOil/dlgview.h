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

#ifndef INC_DLGVIEW
#define INC_DLGVIEW

//#include "view.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class DialogView : public View

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/20/95
	Purpose:	Simple view class for dialogs to use when rendering via a Camelot
				RenderRegion.
	SeeAlso:	View

********************************************************************************************/

class DialogView : public View
{
	CC_DECLARE_DYNAMIC(DialogView);

	virtual ~DialogView();
	BOOL Init();

/////////////////////////////////////////////////////////////////////////////////////////////////
//	Interface to the OIL layer CCamView and the kernel Document.

public:
	virtual BOOL ViewStateChanged();			// informs us that ViewState has changed


/////////////////////////////////////////////////////////////////////////////////////////////////
//	"Current" and "Selected" Views
public:
	virtual void SetViewPixelSize();			// Set pixel size according to this view.

/////////////////////////////////////////////////////////////////////////////////////////////////
//	Rendering

public:
	virtual void ContinueRenderView(RenderRegion*, Spread*, BOOL = TRUE, BOOL = TRUE,
									 BOOL bForceImmediate = FALSE);
	virtual wxDC *GetRenderDC();

public:
	virtual BOOL GetForeBackMode();
	virtual void SetForeBackMode(BOOL);

/////////////////////////////////////////////////////////////////////////////////////////////////
//	Scrolling, scaling and extents

public:
	virtual DocRect GetDocViewRect(Spread*);
	virtual void SetExtent(DocCoord, DocCoord);	// Reset the extent of the document
	virtual WorkRect GetViewRect();				// The physical rect of the view
};

#endif  // INC_DLGVIEW


