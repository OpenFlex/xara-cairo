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

// Class definition for the push tool

/*
*/


#ifndef INC_PUSHTOOL
#define INC_PUSHTOOL


#include "wrkrect.h"
//#include "bars.h"


// Forward references:-
class OpState;			// #include "opdesc.h"
class Cursor;			// #include "csrstack.h"
class ZoomInfoBarOp;	// #include "zoomops.h"


#define OPTOKEN_PUSH _T("PushTool")


/********************************************************************************************

>	class PushTool : public Tool_v1

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/93
	Purpose:	This class handles the Push Tool that is used to slide the document
				about in a more convienient way than using the scroll bars. Most of the
				hard work is done in the OpPush (The push operation).

********************************************************************************************/

class CCAPI PushTool : public Tool_v1
{
// Give my name in memory dumps
CC_DECLARE_MEMDUMP(PushTool);

public:
	PushTool();
	virtual ~PushTool();
	
	virtual BOOL Init();
	virtual void Describe(void* InfoPtr);
	virtual UINT32 GetID() { return TOOLID_PUSH; };
	
	// Event Handlers
	virtual void SelectChange(BOOL);
	virtual void OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	BOOL GetStatusLineText(String_256* ptext, Spread*, DocCoord, ClickModifiers);
	void OnMouseMove(DocCoord, Spread*, ClickModifiers);
	
private:
	Cursor*			pcPushCursor;		// points to our cursor object

	
#ifdef RALPH

	Cursor*				pcHotLinkCursor;		// Graham 20/9/96: The "pointing hand" cursor
	Cursor*				MyCurrentCursor;				// so I don't flip cursor too often
	void				ChangeCursor(Cursor* cursor);	// function to change cursor
//	BOOL				OnKeyPress(KeyPress* pKey);


#endif //Ralph

	INT32 			CurrentCursorID;	// ID of the current cursor on the net
	ZoomInfoBarOp* 	pPushInfoBarOp;		// points to our info-bar operation

	// The descrition of the tool
	static TCHAR* FamilyName;
	static TCHAR* ToolName;
	static TCHAR* Purpose;
	static TCHAR* Author;
};





/********************************************************************************************

>	class OpPush : public Operation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/7/93
	Purpose:	This is the Push operation that slides the document about

********************************************************************************************/

class OpPush : public Operation
{

CC_DECLARE_DYNCREATE(OpPush);

public:
	// Construction/Destruction
	OpPush();

	// The all important Do functions
	void DoDrag( DocCoord Anchor);
	virtual BOOL SnappingDrag() { return FALSE; }
	
	// Virtual functions needed for the dragging operations to work
	virtual void DragPointerMove( DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragFinished(	DocCoord Pos, ClickModifiers Mods, Spread*, BOOL Success, BOOL bSolidDrag);
	
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
	BOOL GetStatusLineText(String_256* ptext, Spread*, DocCoord, ClickModifiers);

private:
	// The Doc point that we clicked on to start the drag
	WorkCoord AnchorPoint;
};

#endif  //INC_PUSHTOOL
