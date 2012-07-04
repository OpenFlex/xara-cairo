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

// SGDFonts.h - the FontsSGallery dragging classes

#ifndef INC_SGDFONTS
#define INC_SGDFONTS

#ifndef EXCLUDE_GALS

//#include "sgallery.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "dragbmp.h"
#include "sgdrag.h"

class String_256;
class KernelBitmap;
class SGDisplayGroup;
class SGDisplayPreviewFonts;
class SGLibFontItem;

/********************************************************************************************

>	class GalleryFontsDragInfo : public BitmapDragInformation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/4/95
	Purpose:	A fill drag, which was started from the fill gallery
	SeeAlso:	BitmapDragInformation
				
********************************************************************************************/

class GalleryFontsDragInfo : public BitmapDragInformation
{ 
	CC_DECLARE_DYNCREATE(GalleryFontsDragInfo)
 
public:
	GalleryFontsDragInfo();
	~GalleryFontsDragInfo();
 	GalleryFontsDragInfo(	SGDisplayPreviewFonts *pSourceItem,
							SGMouseInfo *pMouseInfo, SGMiscInfo *pMiscInfo,
 							BOOL IsAdjust = FALSE, INT32 XSize = 0, INT32 YSize = 0);

	virtual void OnClick(INT32 Flags, POINT Point);

	virtual UINT32 GetCursorID(DragTarget* pDragTarget);
	virtual BOOL GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget);

	virtual BOOL CanDropOnPage() { return TRUE; }
	virtual BOOL OnPageDrop(ViewDragTarget*);

	SGDisplayPreviewFonts*	GetDraggedFont()		{ return(SourceItem); }

	INT32 GetDragTransparency();

	KernelBitmap* GetSolidDragMask();

protected:
	SGDisplayPreviewFonts*	SourceItem;
	SGMouseInfo				MouseInfo;
	SGMiscInfo				MiscInfo;
};

/********************************************************************************************

>	class GalleryLibFontsDragInfo : public BitmapDragInformation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/4/95
	Purpose:	A fill drag, which was started from the fill gallery
	SeeAlso:	BitmapDragInformation
				
********************************************************************************************/

class GalleryLibFontsDragInfo : public BitmapDragInformation
{ 
	CC_DECLARE_DYNCREATE(GalleryLibFontsDragInfo)
 
public:
	GalleryLibFontsDragInfo();
	~GalleryLibFontsDragInfo();
 	GalleryLibFontsDragInfo(SGLibFontItem *pSourceItem,
							SGMouseInfo *pMouseInfo, SGMiscInfo *pMiscInfo,
 							BOOL IsAdjust = FALSE, INT32 XSize = 0, INT32 YSize = 0);

	virtual void OnClick(INT32 Flags, POINT Point);

	virtual UINT32 GetCursorID(DragTarget* pDragTarget);
	virtual BOOL GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget);

	virtual BOOL CanDropOnPage() { return TRUE; }
	virtual BOOL OnPageDrop(ViewDragTarget*);

	SGLibFontItem*	GetDraggedFont()		{ return(SourceItem); }

	INT32 GetDragTransparency();

	KernelBitmap* GetSolidDragMask();
	
protected:
	SGLibFontItem*		SourceItem;
	SGMouseInfo				MouseInfo;
	SGMiscInfo				MiscInfo;
};

/*********************************************************************************************

>	class 	SGFontsDragTarget : public SGListDragTarget

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/4/95

	Purpose:	An instantiation of this class is created by each entity which wishes to 
				provide a 'destination' to which the mouse can go to complete a drag.

				This particular target is used for handling drags of BitmapSGalllery items
				within their displayed list. It automatically handles drags with draginfo
				derived from BitmapDragInformation.

	Notes:		Drag targets are destructed automatically when a drag finishes by the drag
				manager with which they were registered.

				To remove a drag target at any time, destruct it - it automatically deregisters
				and cleans up.
				
	SeeAlso:	DragManagerOp::StartDrag; DragInformation; DragTarget;
				SGBitmapDragTarget::ProcessEvent

	Documentation:	Docs\Specs\DragMan.doc; Docs\HowToUse\SGallery.doc

*********************************************************************************************/

class SGFontsDragTarget : public SGListDragTarget
{
friend class DragManagerOp;
	
CC_DECLARE_DYNAMIC(SGFontsDragTarget)

public:	// Public interface
	SGFontsDragTarget(DialogOp *TheDialog, CGadgetID TheGadget = NULL);

protected:
		// Process a drag-related event
	virtual BOOL ProcessEvent(DragEventType Event,
								DragInformation *pDragInfo,
								OilCoord *pMousePos, KeyPress* pKeyPress);
};

#endif
#endif
