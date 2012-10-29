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
	$Header: /Camelot/kernel/ngdrag.h 3     15/10/99 13:15 Justinf $
	Attribute gallery mouse dragging operations
*/

#ifndef NGDRAG_H
#define NGDRAG_H

#include "sgdrag.h"
#include "dragbmp.h"

class SGNameItem;
class DragTarget;
class ViewDragTarget;


/********************************************************************************************
>	class CCAPI SGNameDrag : public BitmapDragInformation

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/7/99
	Purpose:	A Wix ObjectName attribute drag, which was started from the Name gallery
	SeeAlso:	BitmapDragInformation			
********************************************************************************************/

class CCAPI SGNameDrag : public BitmapDragInformation
{ 
public:
	// Creation & destruction.
	SGNameDrag();
 	SGNameDrag(SGNameItem* pSourceItem, SGMouseInfo* pMouseInfo,
						SGMiscInfo* pMiscInfo);
	virtual ~SGNameDrag();

	// Click handling and user feedback.
	virtual void OnClick(INT32 nFlags, POINT ptClick);
	virtual UINT32 GetCursorID(DragTarget* pDragTarget);
	virtual BOOL GetStatusLineText(String_256* pText, DragTarget* pDragTarget);

	// Called when the drag ends over a view onto a document.
	virtual BOOL CanDropOnPage();
	virtual BOOL OnPageDrop(ViewDragTarget*);

	// Handlers for bitmap rendering during a drag.
	virtual INT32 GetDragTransparency();
	virtual KernelBitmap* GetSolidDragMask();
	virtual BOOL OnDrawSolidDrag(wxPoint ptOrigin, wxDC* pDC);
	
	// Returns a pointer to the Name Gallery display item being dragged.
	SGNameItem* GetDraggedNameAttr();

protected:
	// This returns a rendered image of m_pSourceItem into a bitmap of the given depth.
	virtual KernelBitmap* MakeImage(UINT32 nDepth = 0);

	SGNameItem*	m_pSourceItem;		// item drag originated with
	SGMouseInfo	m_MouseInfo;		// current state of the mouse
	SGMiscInfo	m_MiscInfo;			// current state of other stuff

private:
	CC_DECLARE_DYNCREATE(SGNameDrag);
};



/*********************************************************************************************
>	class CCAPI SGNameDragTarget : public SGListDragTarget

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/7/99
	Purpose:	An instantiation of this class is created by each entity which wishes to 
				provide a 'destination' to which the mouse can go to complete a drag.
				This particular target is used for handling drags of NameGalllery items
				within their displayed list. It automatically handles drags with draginfo
				derived from BitmapDragInformation.
	Notes:		Drag targets are destroyed automatically when a drag finishes by the drag
				manager with which they were registered.
				To remove a drag target at any time, destroy it - it automatically deregisters
				and cleans up.			
	SeeAlso:	SGListDragTarget; DragManagerOp::StartDrag; DragInformation; DragTarget;
				SGBitmapDragTarget::ProcessEvent
*********************************************************************************************/

class CCAPI SGNameDragTarget : public SGListDragTarget
{
public:
	SGNameDragTarget(CGadgetID idGadget = 0);
protected:
	virtual BOOL ProcessEvent(DragEventType nEvent, DragInformation* pDragInfo,
							  OilCoord* pMousePos, KeyPress* pKeyPress);
private:
	CC_DECLARE_DYNAMIC(SGNameDragTarget);
};

#endif	/* !NGDRAG_H */
