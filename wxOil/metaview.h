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

// Simple view class for Metafiles to use when rendering using RenderRegions.

#ifndef INC_METAVIEW
#define INC_METAVIEW


/********************************************************************************************

>	class MetafileView : public View

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Purpose:	Simple view class for metafiles to use when rendering via a Camelot
				RenderRegion.
	SeeAlso:	View

********************************************************************************************/

class MetafileView : public View
{
	CC_DECLARE_DYNAMIC(MetafileView);

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
	virtual CDC *GetRenderDC();

public:
	virtual BOOL GetForeBackMode();
	virtual void SetForeBackMode(BOOL);

/////////////////////////////////////////////////////////////////////////////////////////////////
//	Scrolling, scaling and extents

public:
	virtual DocRect GetDocViewRect(Spread*);
	virtual void SetExtent(DocCoord, DocCoord);	// Reset the extent of the document
	virtual WorkRect GetViewRect();				// The physical rect of the view

// Functions specific to the Metafile View class
public:
	INT32 GetMetafileFlatness();
	INT32 GetMetafileDPI();
	INT32 GetMetafileMapMode();
	void GetScaleFactor(FIXED16* pXScale, FIXED16* pYScale);
};

#endif  // INC_METAVIEW


