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
	$Header: /wxCamelot/Kernel/ngcore.h 18    17/11/05 15:31 Luke $
	Attribute gallery core object
*/

#ifndef NGCORE_H
#define NGCORE_H

//#include "sgallery.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "ktimer.h"

#include <list>

class SGNameGroup;
class SGNameItem;
class SGUsedNames;
class Node;
class NamedStretchProp;
class NodeBarProperty;

// no more than 25 objects can change size through a stretch at one time
#define MAX_SIM_EXTENDS		35

// there can be no more than 20 bars in a single document
#define MAX_BARS			100


/***********************************************************************************************
>	class CCAPI NameGallery : public SuperGallery

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/5/99
	Purpose:	Core object of the Camelot naming system.
	SeeAlso:	SuperGallery
***********************************************************************************************/

class CCAPI NameGallery : public SuperGallery
{
public:
	// Creation & destruction.
	NameGallery();
	virtual ~NameGallery();
	static NameGallery* Instance();

	// Display groups and items.
	SGNameGroup* GetFirstGroup();
	SGUsedNames* GetUsedNames();

	// Item properties.
	INT32 GetPropertyIndex() const;
	INT32 SetPropertyIndex(INT32 nNewIndex);

	// UI state helper.  Returns how many items of each type are highlighted by the user.
	void GetHighlightCount(INT32* pnTotalItems, INT32* pnJustNames);

	// Call this to force an immediate update of the gallery's display, and thereby the
	// status of the document's sets.
	void ForceUpdate();
	BOOL FastUpdateNamedSetSizes(BOOL PropagateChanges = TRUE);
	BOOL FastApplyStretchScan(ObjChangeParam & ObjChange);

	String_256	m_BarToIgnoreTargetsOf;
	String_256	TheIgnoreBar() { return m_BarToIgnoreTargetsOf; }
	INT32 m_TouchedBar; // every item in this bar MAY has moved so sort it out


	// Called when the document has been changed.  Updates the targets of stretches whose
	// sources have changed bounds etc.
	BOOL PreTriggerEdit(UndoableOperation* pOp, ObjChangeParam* pParam, Range* pRange);
	BOOL PreTriggerEdit(UndoableOperation* pOp, ObjChangeParam* pParam, Node* pNode);
	BOOL PostTriggerEdit(UndoableOperation* pOp, ObjChangeParam* pParam);

	BOOL OnTimerEvent();

protected:
	// Event & redraw handlers.
	virtual BOOL PreCreate();
	virtual MsgResult Message(Msg* pMessage);
	virtual void DisplayDirty();
	virtual BOOL OnIdleEvent();
	
	// SuperGallery UI handlers.
	virtual void SetVisibility(BOOL fOpen);
	virtual BOOL InitMenuCommands();
	virtual BOOL BuildCommandMenu(GalleryContextMenu* pMenu, SGMenuID id);
	virtual void DoCommand(StringBase* pstrCommandID);
	virtual OpState GetCommandState(StringBase* pstrCommandID, String_256* pstrShadeReason);
	virtual BOOL ApplyAction(SGActionType nAction);
	virtual void SelectionHasChanged();

	BOOL CreateDisplayTree(); // initialises the display tree

	// bar handling functions
	void ResetRelationshipRects(SGNameItem* pTarget, NamedStretchProp* pProp,
								DocRect* pCleanTargetRect = 0, DocRect* pKnownTriggerRect = 0);
	void ShuffleBar(INT32 BarNumber, INT32 Spacing, INT32 BarDirection,
					SGUsedNames* pNames, Spread * pSpread, ObjChangeParam & ObjChange);

	BOOL ExpandVirtualTriggers(INT32 ExpandType, INT32 BarNo, DocRect &r1);

private:
	// Data.
	SGUsedNames*		m_pUsedNames;			// cached ptr to 'Used Names' display group
	INT32					m_nPropertyIndex;		// type of item property being displayed
	UINT32				m_nRefresh;				// non-zero if gallery display needs redrawing
	UINT32				m_nHiddenUpdates;		// non-zero if doc changed while gallery hidden
	BOOL				m_fMenusCreated;		// TRUE if menus have been created
	BOOL				m_fChildChanges;		// TRUE if must send child-change messages
	UndoableOperation*	m_LastOpUsed;			// the ptr to the op given in PreTrigger and reused in PostTrigger

	static NameGallery* m_pInstance;			// the global instance of the gallery

	BOOL				m_bResetARelationship;  // gets set when calling ResetRelationships

	// bar size data is required to make the buttons the same size
	// since they are required to be the size of the largest, we need to know the largest
	// element of every bar.
	struct BarSizeType
	{
		DWORD MaxWidth;
		DWORD MaxHeight;
		BYTE  TriggeredBar;
		BYTE  HasABackBar;
	} m_BarSize[MAX_BARS];

	// Matt - 06/02/2001
	// Accessor and Mutator Functions for m_BarSize[] BarSizeType...
	BOOL  SetBSTData(INT32 Index, DWORD MaxWidth, DWORD MaxHeight, BYTE TriggeredBar, BYTE HasABackBar);
	DWORD GetBSTMaxWidth(INT32 Index)		{ if (Index < MAX_BARS) { return m_BarSize[Index].MaxWidth;     } else { ERROR3("Out of range m_BarSize[] index!"); return 0; }};
	DWORD GetBSTMaxHeight(INT32 Index)	{ if (Index < MAX_BARS) { return m_BarSize[Index].MaxHeight;    } else { ERROR3("Out of range m_BarSize[] index!"); return 0; }};
	BYTE  GetBSTTriggeredBar(INT32 Index) { if (Index < MAX_BARS) { return m_BarSize[Index].TriggeredBar; } else { ERROR3("Out of range m_BarSize[] index!"); return 0; }};
	BYTE  GetBSTHasABackBar(INT32 Index)  { if (Index < MAX_BARS) { return m_BarSize[Index].HasABackBar;  } else { ERROR3("Out of range m_BarSize[] index!"); return 0; }};

private:
	class NameGalleryTimer : public KernelTimer
	{
	public:
		NameGalleryTimer(NameGallery * pOwner) : m_pOwner(pOwner) {}
		virtual void Notify() {m_pOwner->OnTimerEvent();}
		NameGallery * m_pOwner;
	};
	NameGalleryTimer m_Timer;

	CC_DECLARE_DYNCREATE(NameGallery)
};

#endif	/* !NGCORE_H */
