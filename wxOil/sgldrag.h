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

// sgldrag.h - Line gallery item dragging

#ifndef INC_SGLDRAG
#define INC_SGLDRAG

#include "dragbmp.h"
#include "sgdrag.h"
#include "sgline.h"

class Bitmap;
class KernelBitmap;

/********************************************************************************************

>	class GalleryLineDragInfo : public BitmapDragInformation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	A Line attribute drag, which was started from the line gallery
	SeeAlso:	BitmapDragInformation
				
********************************************************************************************/

class GalleryLineDragInfo : public BitmapDragInformation
{ 
	CC_DECLARE_DYNCREATE(GalleryLineDragInfo)
 
public:
	GalleryLineDragInfo();
 	GalleryLineDragInfo(	LineAttrItem *pSourceItem,
							SGMouseInfo *pMouseInfo, SGMiscInfo *pMiscInfo,
 							BOOL IsAdjust = FALSE);

	~GalleryLineDragInfo();

	virtual void OnClick(INT32 Flags, POINT Point);

	virtual UINT32 GetCursorID(DragTarget* pDragTarget);
	virtual BOOL GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget);

	virtual BOOL CanDropOnPage() { return TRUE; }
	virtual BOOL OnPageDrop(ViewDragTarget*);

	virtual INT32 GetDragTransparency();
	virtual KernelBitmap* GetSolidDragMask();

	LineAttrItem*	GetDraggedLineAttr()	{ return(SourceItem); }

protected:
	BOOL DropStartOrEndArrow(Path*, DocCoord, BOOL*);
	NodeAttribute* MakeStartOrEndArrow(NodeAttribute*, BOOL);

protected:
	LineAttrItem*	SourceItem;
	SGMouseInfo				MouseInfo;
	SGMiscInfo				MiscInfo;

	NodeAttribute* pAttr;
};

/*********************************************************************************************

>	class 	SGLineDragTarget : public SGListDragTarget

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95

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

class SGLineDragTarget : public SGListDragTarget
{
friend class DragManagerOp;
	
CC_DECLARE_DYNAMIC(SGLineDragTarget)

public:	// Public interface
	SGLineDragTarget(DialogOp *TheDialog, CGadgetID TheGadget = NULL);

protected:
		// Process a drag-related event
	virtual BOOL ProcessEvent(DragEventType Event,
								DragInformation *pDragInfo,
								OilCoord *pMousePos, KeyPress* pKeyPress);
};

#endif
