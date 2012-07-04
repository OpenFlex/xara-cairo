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
	A ViewState object contains platform-independent data describing a view onto a
	document.

	vstate.h
*/

#ifndef VSTATE_H
#define VSTATE_H

//#include "coord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "rect.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "wrkcoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "wrkrect.h"

class View;

class ViewState
{	
public:

	// Construction & destruction
	ViewState();
	virtual ~ViewState();

#ifdef _DEBUG
	void Dump() const;
#endif

public:

	// Data members (public for easy access)

	View* 	    pView;					// The kernel view object this describes

	Rect		ScreenRect;             // screen dimensions of the platform
	Rect		ParentRect;				// position of parent (MDI frame) window	
	Rect		ViewRect;				// position of this CCamView
	
	Coord 		IconPoint;				// position when iconised

	WorkRect  	WorkAreaExtent;			// the scrollable area

// Removed by Phil, 22/11/94, to try to rationalise the storage of pixel sizes in the system.
//	MILLIPOINT	PixelWidth;          	// pixel width in millipoints
//	MILLIPOINT	PixelHeight;         	// pixel height in millipoints
//	FIXED16 	PixelXScale;			// no. of pixels per millipoint horizontally
//	FIXED16 	PixelYScale;			// and vertically.
	FIXED16		ViewScale;				// this view's current scaling factor for zooms
	
	BOOL 		IsNewView;				// is this a fresh view?
	BOOL 		IsMinimised;			// is view currently iconised?
	BOOL 		IsMaximised;			// is view currently maximised?
	BOOL		AlwaysOnTop;			// TRUE if window has "always on top" attribute
	BOOL		RulersVisible;			// TRUE if Rulers are visible
	BOOL 		ScrollersVisible;		// TRUE if Scrollers are visible
	INT32			zPos;					// relative z-order of the view

	// These are temporary storage used by LoadAppWindowState to store the values of the
	// corresponding DocView flags until they can be written to a created DocView.
	// See MakeViewStateFromKey and CCamView::OnInitialUpdate.
	BOOL _GridShow : 1;
	BOOL _GridSnap : 1;
	BOOL _ObjectsSnap : 1;
	BOOL _MagObjectsSnap : 1;
	BOOL _PrintBorderShow : 1;
	BOOL _LogicalView : 1;
	BOOL _GuidesSnap : 1;
	BOOL _GuidesShow : 1;


	// Functions to access the protected scroll offset and ensure it's pixel aligned...
	WorkCoord	SetScrollPos(WorkCoord sp, BOOL fPixelise = TRUE);
	WorkCoord	GetScrollPos(BOOL Pixelise = TRUE);

protected:
	WorkCoord 	ScrollPosition;			// offset of scroll bars
	
};


#endif	// VSTATE_H
