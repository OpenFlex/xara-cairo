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

// Header for the blank tool implementation

#ifndef INC_BLANKTOOL
#define INC_BLANKTOOL

//#include "tool.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "bars.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class Cursor;
class Spread;
class BlankInfoBarOp;


/********************************************************************************************

>	class BlankTool : public Tool_v1

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/94
	Purpose:	A template tool class

********************************************************************************************/

class CCAPI BlankTool : public Tool_v1
{
// Give tool name in memory dumps
CC_DECLARE_MEMDUMP(BlankTool);

public:
	BlankTool();
	~BlankTool();

	// Standard calls your tool must provide
	BOOL Init();
	void Describe(void* InfoPtr);
	UINT32 GetID() { return TOOLID_BLANK; };	// <****** CHANGE THIS TO YOUR TOOL'S ID!!! (defined in kernel\tool.h)
	
	// Some very common event handlers
	void SelectChange(BOOL isSelected);
	void OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	void OnMouseMove(DocCoord PointerPos,Spread* pSpread, ClickModifiers ClickMods);
	void RenderToolBlobs(Spread* pSpread,DocRect* pDocRect);
	BOOL GetStatusLineText(String_256* ptext, Spread* pSpread, DocCoord DocPos, ClickModifiers ClickMods);

	// Some useful static functions
	static BlankInfoBarOp* 	GetBlankInfoBarOp()  { return s_pBlankInfoBarOp; }
	static BOOL 			IsCurrentTool() 	 { return s_bCurrentTool; }

private:
	void DisplayStatusBarHelp(DocCoord DocPos, Spread* pSpread, ClickModifiers ClickMods);
	void GetCurrentStatusText(String_256* ptext, Spread* pSpread, DocCoord DocPos, ClickModifiers ClickMods);

	BOOL CreateCursors();							// Create  your tool's cursors in this func
	void DestroyCursors();							// Destroy your tool's cursors in this func

	static BOOL 			s_bCurrentTool;			// Can be useful to keep a "is my tool currenmt?" flag
	static BlankInfoBarOp*	s_pBlankInfoBarOp;		// Ptr to your tool's infobar

	Cursor*					m_pcNormalBlankCursor;	// Your standard cursor to use when your tool becomes active
	Cursor*					m_pcCurrentCursor;		// The cursor your tool is currently displaying
	INT32 					m_CurrentCursorID;		// ID of the current cursor you're displaying

	// Standard tool static vars
	static 	LPTSTR FamilyName;						// The Tools Family Name
	static 	LPTSTR ToolName;						// The Tool Name
	static 	LPTSTR Purpose;							// What the tool is for
	static 	LPTSTR Author;							// Who wrote it
};


//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------


/********************************************************************************************

>	class BlankInfoBarOp : public InformationBarOp

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/94
	Purpose:	Class for handling the tool's information bar.

********************************************************************************************/

class BlankInfoBarOp : public InformationBarOp
{
	CC_DECLARE_DYNCREATE( BlankInfoBarOp )  
public:
	BlankInfoBarOp(BlankTool* pTool=NULL)
	{
		m_pBlankTool = pTool;
		DlgResID = _R(IDD_BLANKTOOLBAR);
	}

	MsgResult 	Message(Msg* Msg);	// All messages to the info bar come through here

private:
	BlankTool*	m_pBlankTool;
};
	

#endif 		// INC_BLANKTOOL
