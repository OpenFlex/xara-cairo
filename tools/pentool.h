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

// The Pen Tool
// Created by Mike on 19/9/94

#ifndef INC_PENTOOL
#define INC_PENTOOL

#include "wrkrect.h"
//#include "viewrc.h"
#include "penedit.h"

class NodePath;
class Cursor;
class PenToolInfoBarOp;

#define OPTOKEN_PENTOOL _T("PenTool")


enum penstate
{
	IS_Undefined,
	IS_MoveTo,
	IS_DragTo,
};

enum penopstate
{
	OS_Undefined,
	OS_EditInternal,
	OS_CreatePath,
	OS_AddElement,
	OS_ClosePath
};

typedef enum penclick
{
 	PenNewPath, 
 	PenOnPoint,
 	PenAddSegment,
	PenEditInternalMove,
	PenClosePath,
	PenReshapeLine
};



/********************************************************************************************

>	class PenTool : public Tool_v1

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/9/94
	Purpose:	This class handles the Pen Tool that is used to draw lines and curves via
				clicking and draging on the workarea.

********************************************************************************************/

class CCAPI PenTool : public Tool_v1
{
// Give my name in memory dumps
CC_DECLARE_MEMDUMP(PenTool);

public:
	PenTool();
	~PenTool();
	
	BOOL Init();
	void Describe(void* InfoPtr);
	UINT32 GetID() { return TOOLID_PEN; };
	
	// Event Handlers
	void SelectChange(BOOL);
	virtual void OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	virtual void RenderToolBlobs(Spread*, DocRect*);
	virtual BOOL GetStatusLineText(String_256*, Spread*, DocCoord, ClickModifiers);
	virtual void OnMouseMove(DocCoord, Spread*, ClickModifiers);
	virtual BOOL OnKeyPress(KeyPress* pKeyPress);
	void GenerateStatusLineText(NodePath* pNodePath, penclick WhatToDo, String_256* pStatusMsg);
	
	void SetInternalState();
	void ClearInternalState();

	BOOL OverPathEnd(DocCoord, Spread*, NodePath**);
	penclick DetermineClickEffect(DocCoord, Spread*, NodePath**);
	void RemoveSelection(DocCoord PointerPos, Spread *pSpread, NodePath* pNodePath=NULL);
	void ClearPath();
	void ClearOp();
	void CreateNewPath();
	void AddElementToPath();
	void CloseWithPath();

	penopstate GetPenOpState() const;

private:
	void ClickOnEndPoint(ClickType Click, ClickModifiers ClickMods, Spread *pSpread, NodePath* pNodePath );
	BOOL CreatePenCursors();
	void DeletePenCursors();

private:
	static 	TCHAR* FamilyName;		// The Tools Family Name
	static 	TCHAR* ToolName;		// The Tool Name
	static 	TCHAR* Purpose;			// What the tool is for
	static 	TCHAR* Author;			// Who wrote it

	penstate 	CurrPenState;		// current internal tool state
	penopstate	CurrPenOpState;		// current internal tool op state

	Path		EditPath;			// temporary path for eor editing
	ControlPts  EditHandles;		// handle coordinates for eoring

	NodePath*	pNodePath;
	INT32		NodeIndex;

	// The tools cursors
	Cursor* 	pcPenCursor;
	Cursor* 	pcPenAdjustCursor;
	Cursor*		pcPenReshapeCursor;
	Cursor*		pcMoveBezCursor;
	Cursor* 	MyCurrentCursor;

	INT32 		CurrentCursorID;				// ID of the current cursor on the stack
	void		ChangeCursor(Cursor* cursor);	// function to change cursor

	// The info bar
	PenToolInfoBarOp* pPenInfoBarOp;


};



/********************************************************************************************

>	class PenToolInfoBarOp : public InformationBarOp

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/9/94
	Purpose:	Class for handling the pen tool's information bar.

********************************************************************************************/

class PenToolInfoBarOp : public InformationBarOp
{
 	CC_DECLARE_DYNCREATE(PenToolInfoBarOp)
public:
	PenToolInfoBarOp() {DlgResID = _R(IDD_PENTOOLBAR);};	// Dummy default constructor for DYNCREATE
	MsgResult Message(Msg*);			// All messages to the info bar come through here
	// void	InitControls();				// Initialises the controls in the info bar
	// void	EnableControls();			// Enables/disables the controls in the info bar
	// virtual void UpdateState();		// Overrides the empty function in InformationBarOp

	PenTool* pPenTool;					// Pointer to instance of pen tool

};


/********************************************************************************************

>	class PenToolInfoBarOpCreate : public BarCreate

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/9/94
	Purpose:	Class for creating PenToolInfoBarOps.
				Derived classes of BarCreate are used by DialogBarOp::ReadBarsFromFile()

********************************************************************************************/

class PenToolInfoBarOpCreate : public BarCreate
{
public:
	DialogBarOp*	Create() { return (new PenToolInfoBarOp); }
};



#endif  //INC_PENTOOL
