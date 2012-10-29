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

// sgname.h - the NameGallery classes.

/*
	$Log: /Camelot/kernel/sgname.h $
 * 
 * 2     16/07/99 18:06 Justinf
 * Now shows little circular blobs for adding sets to / subtracting sets
 * from the selection.
 * 
 * 1     24/06/99 16:23 Justinf
 * Name Gallery
*/

#ifndef SGNAME_H
#define SGNAME_H

#include "sgdrag.h"
#include "dragbmp.h"

#include "attrsets.h"


/***********************************************************************************************
>	class CCAPI NameGallery : public SuperGallery

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/1/95 (Based on the Colour SGallery code)
	Purpose:	The Name SuperGallery class
	Notes:		SuperGalleries are specced in a number of docs including
					specs\sgallery.doc ("super" gallery extensions)
					specs\propui.doc  (gallery basic ui)
				There is also howtouse\sgallery.doc which describes creating a supergallery
	SeeAlso:	SuperGallery; SGDisplayName
***********************************************************************************************/

class SGNameGroup;

class CCAPI NameGallery : public SuperGallery
{
public:
	NameGallery();
	virtual ~NameGallery();
	virtual MsgResult Message(Msg* pMessage);

protected:
	virtual BOOL PreCreate();

	virtual BOOL InitMenuCommands();
	virtual BOOL BuildCommandMenu(GalleryContextMenu* pMenu, SGMenuID id);
	virtual OpState GetCommandState(StringBase* pstrCommandID, String_256* pstrShadeReason);
	virtual void DoCommand(StringBase* pstrCommandID);

	virtual void SelectionHasChanged();
	virtual BOOL ApplyAction(SGActionType Action);
	
	virtual BOOL OnApply(SGNameGroup* pGroup, BOOL fIsAdjust);
	virtual BOOL OnCreate(SGNameGroup* pGroup);
	virtual BOOL OnRename(SGNameGroup* pGroup);
	virtual BOOL OnDelete(SGNameGroup* pGroup);
	virtual BOOL OnRedefine(SGNameGroup* pGroup);
	virtual BOOL OnUnname(SGNameGroup* pGroup);

	virtual SGNameGroup* CreateItems(Document* pParentDoc, SGNameGroup* pGroup);
	virtual BOOL GetNewName(SGNameGroup* pGroup, UINT32 nDialogTemplateID, String_256* pstrName);
	virtual void RefreshDocument(Document* pDoc);
	virtual BOOL OnIdleEvent();

private:
	// Extension to the action codes already defined by the SuperGallery class.
	enum { SGACTION_UNNAME = SGACTION_UNDO + 1 };

	BOOL m_fMenusCreated;
	BOOL m_fIdleProc;

	CC_DECLARE_DYNCREATE(NameGallery)
};



/***********************************************************************************************
>	class CCAPI SGNameGroup : public SGDisplayGroup

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/01/95
	Purpose:	A SuperGallery group of SGNameItems.  Records whether this group's display
				needs to be updated on the next idle event because of a change to its
				Document's named objects.
	SeeAlso:	NameGallery; SuperGallery; SGDisplayItem
***********************************************************************************************/

class CCAPI SGNameGroup : public SGDisplayGroup
{
public:
	SGNameGroup(NameGallery* pParentGal, Document* pParentDoc = 0)
	  :	SGDisplayGroup(pParentGal, pParentDoc),
		m_fRefresh(FALSE)
			{ Flags.CanSelect = TRUE; }

	// Call this to mark (or unmark) this group for refresh on the next idle event.
	void SetRefresh(BOOL fR = TRUE)
			{ m_fRefresh = fR; }
	
	// Query whether this group needs to be refreshed and also reset its status.
	BOOL NeedsRefresh()
			{ BOOL fR = m_fRefresh; m_fRefresh = FALSE; return fR; }

private:
	BOOL m_fRefresh;
};



/***********************************************************************************************
>	class CCAPI SGNameItem : public SGDisplayItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/01/95
	Purpose:	This DisplayTree node is used by the Name SuperGallery
				It is responsible for providing the ability to handle/redraw one NameItem
				displayed in said gallery.
	SeeAlso:	NameGallery; SuperGallery; SGDisplayItem
***********************************************************************************************/

class CCAPI SGNameItem : public SGDisplayItem
{
public:
	SGNameItem(const String_256& strName);
	
	virtual void GetNameText(String_256* pResult);
	virtual BOOL GetBubbleHelp(DocCoord* pMousePos, String_256* pResult);
	virtual BOOL GetStatusLineHelp(DocCoord* pMousePos, String_256* pResult);
	virtual	BOOL HandleEvent(SGEventType EventType, void* pEventInfo,
							 SGMiscInfo* pMiscInfo);
	Document* GetDocument()
		{ return ((SGDisplayGroup*) GetParent())->GetParentDocument(); }

protected:
	virtual void CalculateMyRect(SGFormatInfo* pFormatInfo, SGMiscInfo* pMiscInfo);
	virtual void HandleRedraw(SGRedrawInfo* pRedrawInfo, SGMiscInfo* pMiscInfo);
	
private:
	String_256 m_strSetName;
	AttributeSets::Intersect m_eIntersect;
	
	CC_DECLARE_DYNAMIC(SGNameItem);
};



/********************************************************************************************
>	class CCAPI GalleryNameDragInfo : public BitmapDragInformation

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	A Wix ObjectName attribute drag, which was started from the Name gallery
	SeeAlso:	BitmapDragInformation			
********************************************************************************************/

class TemplateAttribute;
class DragTarget;
class ViewDragTarget;

class CCAPI GalleryNameDragInfo : public BitmapDragInformation
{ 
public:
	// Creation & destruction.
	GalleryNameDragInfo();
 	GalleryNameDragInfo(SGNameItem* pSourceItem, SGMouseInfo* pMouseInfo,
						SGMiscInfo* pMiscInfo, TemplateAttribute* pAttrib,
						BOOL fIsAdjust = FALSE);
	virtual ~GalleryNameDragInfo();

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
	
	SGNameItem* GetDraggedNameAttr()	{ return m_pSourceItem; }

private:
	SGNameItem*	   m_pSourceItem;
	SGMouseInfo	   m_MouseInfo;
	SGMiscInfo	   m_MiscInfo;
	NodeAttribute* m_pAttrib;

	CC_DECLARE_DYNCREATE(GalleryNameDragInfo)
};



/*********************************************************************************************
>	class CCAPI SGNameDragTarget : public SGListDragTarget

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
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
	SGNameDragTarget();
	SGNameDragTarget(NameGallery* pGallery, CGadgetID idGadget = 0);

protected:
	virtual BOOL ProcessEvent(DragEventType nEvent, DragInformation* pDragInfo,
							  OilCoord* pMousePos, KeyPress* pKeyPress);
private:
	CC_DECLARE_DYNAMIC(SGNameDragTarget)
};



/********************************************************************************************
>	class CCAPI OpDisplayNameGallery: public Operation

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/2/95 (Based on the Colour SGallery code)
	Purpose:	Displays the Name gallery.  This op can be attached to a menu, button
				or keypress.
	SeeAlso:	NameGallery
********************************************************************************************/

#define OPTOKEN_DISPLAY_NAME_GALLERY    TEXT("DisplayNameGallery")

class CCAPI OpDisplayNameGallery: public Operation
{         
public:
	static BOOL	Init();				
	static OpState GetState(String_256*, OpDescriptor*);		
    void Do(OpDescriptor*);

private:
	static DialogBarOp* FindGallery();

private:
	CC_DECLARE_DYNCREATE(OpDisplayNameGallery);
};  



/********************************************************************************************
>	class CCAPI NameObjectsDlg: public DialogOp

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/6/94
	Purpose:	Runs a dialog which asks the user to enter a name for the selected objects.
********************************************************************************************/

#define OPTOKEN_NAME_OBJECTS_DLG	TEXT("NameObjectsDlg")

class CCAPI NameObjectsDlg : public DialogOp
{         
public:
	NameObjectsDlg();
	static BOOL Init();
	
	static OpState GetState(String_256*, OpDescriptor*);
	void DoWithParam(OpDescriptor*, OpParam*);
	MsgResult Message(Msg* Message);

private:
	// Where to output the results of the dialog.
	String_256* m_pstrOutputName;
	BOOL* m_pfOkCancel;	

	CC_DECLARE_DYNCREATE(NameObjectsDlg)  
}; 

#endif	/* SGNAME_H */
