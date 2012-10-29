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


#ifndef INC_CTRLLIST
#define	INC_CTRLLIST


class DialogOp;

/*******************************************************************************************

>	class ControlList : public CCObject

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	19/12/2005
	Purpose:	A class to maintain a list of the wxControls that might be on bars
	Notes:		In the OIL
	See Also:	

This class maintains a list of wxControls, and what OpDescriptor (if any) they
are associated with. It is by no means a sin for a wxControl not to have an
OpDescriptor. However, if it does, ControlList will cause it to grey and
ungrey, and be ticked and unticked.

Right now we are doing this on idle events (why oh why?) for compatibilty.

********************************************************************************************/

class ControlPtrToListEntry;

class ControlList : public CCObject
{
public:
	CC_DECLARE_DYNCREATE( ControlList )

	class ListEntry
	{
		public:
			OpState m_OpState;
			OpDescriptor * m_pOpDesc;
			DialogOp * m_pDialogOp;
			BOOL m_SpecifiedOpDesc;
			ListEntry(OpDescriptor * opdesc = NULL) {m_pOpDesc = opdesc; m_SpecifiedOpDesc = FALSE; m_pDialogOp = NULL;}
	};

	ControlList();
	virtual ~ControlList();

	static ControlList * Get() {return m_pControlList;}
	static BOOL Init();
	static void DeInit();

	BOOL NewControl(wxControl * pControl);
	BOOL DeleteControl(wxControl * pControl);
	BOOL AssociateControl(wxControl * pControl, DialogOp * pDialogOp = NULL);

	BOOL ReflectAllStates(BOOL IgnoreChangedFlag = FALSE);

	void Changed() {m_ChangedFlag = TRUE;}

	void Invoke(wxControl * pControl, OpParam* pOpParam = NULL, BOOL fWithUndo = TRUE);
	OpDescriptor * Find(wxControl * pControl);
	BOOL BuildGadgetList(List* pOutputList, OpDescriptor * pOpDesc);

	static void Idle() {if (m_pControlList) m_pControlList->ReflectAllStates();}

	BOOL SendMessageToAllControls(DialogOp * pDialogOp, DialogMsg * DlgMsg, CWindowID pWindow = NULL);

	void RegisterWindowAndChildren(wxWindow * pwxWindow, DialogOp * pDialogOp );
	void RemoveWindowAndChildren(wxWindow * pwxWindow);

private:
	static ControlList * m_pControlList;

	ControlPtrToListEntry * m_pHash;
	BOOL m_ChangedFlag;

	BOOL ReflectState(wxControl * pControl, ControlList::ListEntry * pListEntry, BOOL ForceUpdate=FALSE);
};

typedef wxControl * wxControl_ptr;
WX_DECLARE_HASH_MAP( wxControl_ptr, ControlList::ListEntry, wxPointerHash, wxPointerEqual, ControlPtrToListEntry );

#endif

