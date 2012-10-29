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

// sgdrag.h - Drag Manager classes (information, targets) for supergallery scollbars
//			  and generic supergallery item dragging (for rearrangement only)

#ifndef INC_SGDRAG
#define INC_SGDRAG


#include "draginfo.h"


class SGDisplayRootScroll;
class SGDisplayItem;
class DocCoord;


/*********************************************************************************************

>	class 	SGScrollDragTarget : public KernelDragTarget

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/2/95

	Purpose:	An instantiation of this class is created by each entity which wishes to 
				provide a 'destination' to which the mouse can go to complete a drag.

				This particular target is used for handling drags of supergallery scroll
				bars, and for providing auto-repeat on scroll buttons.

	Notes:		Drag targets are destructed automatically when a drag finishes by the drag
				manager with which they were registered.

				To remove a drag target at any time, destruct it - it automatically deregisters
				and cleans up.
				
	SeeAlso:	DragManagerOp::StartDrag; DragInformation; DragTarget

	Documentation:	Docs\Specs\DragMan.doc

*********************************************************************************************/

class SGScrollDragTarget : public KernelDragTarget
{
friend class DragManagerOp;
	
CC_DECLARE_DYNAMIC(SGScrollDragTarget)


public:	// Public interface
	SGScrollDragTarget(DialogOp *TheDialog, CGadgetID TheGadget = NULL);
	
	virtual UINT32 GetCursorID();
	virtual BOOL GetStatusLineText(String_256 * TheText);

protected:
		// Process a drag-related event
	virtual BOOL ProcessEvent(DragEventType Event,
								DragInformation *pDragInfo,
								OilCoord *pMousePos, KeyPress* pKeyPress);

protected:
	MonotonicTime Timer;
};



typedef enum
{
	SGDRAG_NONE = 0,				// Used to notate when no drag is active/valid
	SGDRAG_SCROLLUP,				// Up	} - click scroll arrow
	SGDRAG_SCROLLDOWN,				// Down	}
	SGDRAG_PAGEUP,					// Up	} - click page-scroll areas
	SGDRAG_PAGEDOWN,				// Down	}
	SGDRAG_SAUSAGE					// Drag of scroll sausage
} SGDragType;



/********************************************************************************************

>	class SGScrollDragInfo : public DragInformation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/2/95
	Purpose:	Describes a supergallery scroll drag
				
********************************************************************************************/

class SGScrollDragInfo : public DragInformation
{ 
CC_DECLARE_DYNCREATE(SGScrollDragInfo)
 
public:
	SGScrollDragInfo();
 	SGScrollDragInfo(SGDisplayRootScroll *ParentRootNode, SGDragType TheDragType,
						SGMiscInfo *MiscInfo, INT32 DragAnchorOffset,
						BOOL IsAdjust = FALSE);
	
	void OnClick(INT32 Flags, POINT Point);
	
	virtual UINT32 GetCursorID(void);
 	virtual BOOL GetStatusLineText(String_256 * TheText);

	SGDisplayRootScroll *GetDragRootNode(void)	{ return(DragRootNode); }
	SGDragType GetDragType(void)				{ return(DragType); }
	SGMiscInfo *GetDragMiscInfo(void)			{ return(&DragMiscInfo); }
	INT32 GetDragAnchorOffset(void)				{ return(DragAnchor); }
	BOOL IsAdjustDrag(void)						{ return(DragAdjust); }

private:
	SGDisplayRootScroll *DragRootNode;		// The node which started the drag
	SGDragType	DragType;					// The type of drag (see SGDragType, above)
	SGMiscInfo	DragMiscInfo;				// Copy of MiscInfo for the event causing the drag
	INT32		DragAnchor;					// Offset from top of sausage rect to the point
											//   which was dragged.
	BOOL		DragAdjust;					// TRUE if this is an 'adjust' drag
};







typedef enum								// Where an item can be inserted...
{
	SGDRAGINSERT_NONE,						// No valid target
	SGDRAGINSERT_ADD,						// Add an item into a group
	SGDRAGINSERT_BEFORE,					// Insert before target
	SGDRAGINSERT_AFTER						// Insert after target
} SGDragInsertType;

/*********************************************************************************************

>	class 	SGListDragTarget : public KernelDragTarget

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/3/95

	Purpose:	An instantiation of this class is created by each entity which wishes to 
				provide a 'destination' to which the mouse can go to complete a drag.

				This particular target is used for handling drags of supergallery items
				within their displayed list. It automatically handles drags with draginfo
				derived from SGListDragInfo. If you wish to handle drags of other
				more specialised types, then you should derive a class from this one, and
				simply override the ProcessEvent method in order to correctly divine
				information such as parent gallery and dragged gallery item from the
				current DragInfo object. (c.f. sgcolour.cpp -the SGColourDragTarget)

	Notes:		Drag targets are destructed automatically when a drag finishes by the drag
				manager with which they were registered.

				To remove a drag target at any time, destruct it - it automatically deregisters
				and cleans up.
				
	SeeAlso:	DragManagerOp::StartDrag; DragInformation; DragTarget;
				SGColourDragTarget::ProcessEvent

	Documentation:	Docs\Specs\DragMan.doc; Docs\HowToUse\SGallery.doc

*********************************************************************************************/

class SGListDragInfo;

class SGListDragTarget : public KernelDragTarget
{
friend class DragManagerOp;
	
CC_DECLARE_DYNAMIC(SGListDragTarget)


public:	// Public interface
	SGListDragTarget(DialogOp *TheDialog, CGadgetID TheGadget = NULL);
	
	virtual UINT32 GetCursorID();
	virtual BOOL GetStatusLineText(String_256 * TheText);

protected:
		// Process a drag-related event
	virtual BOOL ProcessEvent(DragEventType Event,
								DragInformation *pDragInfo,
								OilCoord *pMousePos, KeyPress* pKeyPress);

		// Subroutine to determine whether we will try to insert above or below an item
	SGDragInsertType GetDragInsertType(SuperGallery *ParentGallery,
								SGDisplayNode *DraggedNode,
								OilCoord *pMousePos,
								SGDisplayNode *DestNode);

		// Subroutine for handling a successful drag completion
	void HandleDragCompleted(SuperGallery *ParentGallery,
								SGDisplayNode *DraggedNode,
								OilCoord *pMousePos,
								BOOL DragThisItemOnly = FALSE);

		// Determines a cursor shape appropriate to the current mouse position
	virtual BOOL DetermineCursorShape(SuperGallery *ParentGallery,
								SGDisplayNode *DraggedNode,
								OilCoord *pMousePos);

		// Determines (by comparing format rects) if the given node takes up an
		// entire 'line' of the dislay list.
	BOOL OwnsEntireLine(SGDisplayNode *TheNode);

protected:
	UINT32 CurrentCursorID;
};






/********************************************************************************************

>	class SGListDragInfo : public DragInformation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/3/95
	Purpose:	Describes a generic supergallery item drag

	Documentation:	Docs\Specs\DragMan.doc; Docs\HowToUse\SGallery.doc

	SeeAlso:	SGListDragTarget; SuperGallery; SGDisplayNode::HandleEvent
				
********************************************************************************************/

class SGListDragInfo : public DragInformation
{ 
CC_DECLARE_DYNCREATE(SGListDragInfo)
 
public:
	SGListDragInfo();
 	SGListDragInfo(SuperGallery *ParentGal, SGDisplayNode *DraggedNode,
					SGMouseInfo *TheMouseInfo, BOOL IsAdjust = FALSE);
	
	void OnClick(INT32 Flags, POINT Point);
	
	virtual UINT32 GetCursorID(void);
 	virtual BOOL GetStatusLineText(String_256 * TheText);

	SuperGallery  *GetParentGallery(void)	{ return(ParentGallery); }
	SGDisplayNode *GetDraggedNode(void)		{ return(DragNode); }
	SGMouseInfo	  *GetMouseInfo(void)		{ return(&MouseInfo); }

private:
	SuperGallery  *ParentGallery;			// The gallery from which this drag originated
	SGDisplayNode *DragNode;				// The node which is being dragged											//   which was dragged.
	SGMouseInfo	  MouseInfo;				// A COPY of the original MouseInfo for the click
};


#endif




