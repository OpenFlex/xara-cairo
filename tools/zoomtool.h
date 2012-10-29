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

// The Zoom Tool

#ifndef INC_ZOOMTOOL
#define INC_ZOOMTOOL


class Cursor;
class Spread;
class ZoomInfoBarOp;
class OpZoom;



/********************************************************************************************
>	class ZoomTool : public Tool_v1

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/7/93
	Purpose:	This class is to allow the user to Zoom in and out of the document
				at will.  It provides an interface to the tool system for the zoom
				mouse-drag Operation.
	SeeAlso:	class OpZoom
********************************************************************************************/

class CCAPI ZoomTool : public Tool_v1
{
private:

	// Allow memory dumps.
	CC_DECLARE_MEMDUMP(ZoomTool);

public:

	// Creation & destruction
	ZoomTool();
	virtual ~ZoomTool();
	virtual BOOL Init();

	virtual void Describe(void* InfoPtr);
	virtual UINT32 GetID();
	
	// Event Handlers
	virtual void SelectChange(BOOL fIsSelected);
	virtual BOOL OnKeyPress(KeyPress* pKey);
	virtual void OnMouseMove(DocCoord dcMousePos, Spread* pSpread, ClickModifiers mods);
	virtual void OnClick(DocCoord, ClickType, ClickModifiers, Spread*);
	virtual BOOL GetStatusLineText(String_256* ptext, Spread* pSpread,
								   DocCoord DocPos, ClickModifiers ClickMods);
	void ValidateStatusText();

	// Used by helper classes.
	static BOOL IsSelectedTool();
	static void InvalidateStatusText();

private:

	BOOL				Inited;				// TRUE when initialisation has been attempted
	Cursor*				pcZoomCursor;		// pointer to this tool's cursor
	Cursor*				pcZoomOutCursor;	// pointer to this tool's zoom out cursor
	Cursor*				MyCurrentCursor;				// so I don't flip cursor too often

#ifdef RALPH

	Cursor*				pcHotLinkCursor;		// Graham 20/9/96: The "pointing hand" cursor
//	Cursor*				MyCurrentCursor;				// so I don't flip cursor too often
	void				ChangeCursor(Cursor* cursor);	// function to change cursor
//	BOOL				OnKeyPress(KeyPress* pKey);

#endif //Ralph

	INT32				CurrentCursorID;	// ID of the current cursor on the stack
	ZoomInfoBarOp*		pZoomInfoBarOp;		// points to our info bar
	String_256*			psStatusText;		// text "mask" for status-bar text	
	BOOL				bStatusTextValid;	// whether status-bar text needs updating

	static TCHAR	   *FamilyName;			// The Tools Family Name
	static TCHAR	   *ToolName;			// The Tool Name
	static TCHAR	   *Purpose;			// What the tool is for
	static TCHAR	   *Author;				// Who wrote it
	static BOOL			bIsActive;			// Whether the zoom tool is "selected"
};

#endif   // !INC_ZOOMTOOL
