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

// The FreeHand Tool
// Created by Phil on 27/09/2004



#ifndef INC_LIVEEFFECTSTOOL
#define INC_LIVEEFFECTSTOOL


#include "wrkrect.h"
#include "dragtool.h"


class Cursor;
class LiveEffectsInfoBarOp;
class Progress;
class Trans2DMatrix;
class BlendRef;
class EffectsStack;


/********************************************************************************************
>	class LiveEffectsTool : public Tool_v1

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/09/2004
	Purpose:	This class implements the Live Effects tool that allows the use to apply
				live bitmap effects to objects.

********************************************************************************************/

class CCAPI LiveEffectsTool : public DragTool
{
// Give my name in memory dumps
CC_DECLARE_MEMDUMP(LiveEffectsTool);

public:
							LiveEffectsTool();
							~LiveEffectsTool();

	BOOL					Init();
	void					Describe(void* InfoPtr);
	UINT32					GetID();
	
	// Event Handlers
	virtual void			SelectChange(BOOL);
	virtual void			OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	virtual void			OnMouseMove(DocCoord, Spread*, ClickModifiers);
	virtual BOOL			GetStatusLineText(String_256* ptext, Spread*, DocCoord, ClickModifiers);
	virtual BOOL			OnIdle();
	// Rendering the blobs functions
//	virtual void			RenderToolBlobs(Spread*, DocRect*);

	LiveEffectsInfoBarOp*	GetInfoBar() const { return m_pInfoBarOp;}
	void					ScreenChanged(BOOL WipeRegion);
	EffectsStack*			GetEffectsStack() const;
	String_256				GetCurrentEffectID() const {return m_strCurrentEffectID;}
	void					SetCurrentEffectID(String_256 strNewEffectID) {m_strCurrentEffectID = strNewEffectID;}
	INT32						GetCurrentStackPos() {return m_iCurrentStackPos;}
	void					SetCurrentStackPos(INT32 iNewPos) {m_iCurrentStackPos = iNewPos;}
	BOOL					UpdatePPStack(BOOL bUCE = TRUE);

protected:
	// Helper functions
	// Functions to load, remove and change the active cursor
	BOOL					LoadCursors();
	void					RemoveCursors();
	void					ChangeCursor(Cursor* pCursor);

protected:
	static char*			FamilyName;	// The Tools Family Name
	static char*			ToolName;		// The Tool Name
	static char*			Purpose;		// What the tool is for
	static char*			Author;		// Who wrote it

	// The status line text
	String_256				StatusMsg;

	// The coord of the initial click
	DocCoord				StartPos;
	Spread*					StartSpread;

	// The tools cursor
	Cursor*					pNormalCursor;				// The normal cursor
	Cursor*					pActiveCursor;				// Whichever cursor is being displayed (see ChangeCursor).
	INT32					CurrentCursorID;				// ID of the current cursor on the stack

	// The info bar
	LiveEffectsInfoBarOp*	m_pInfoBarOp;

	// Lists of pointers to nodes that we use to run the UI and Ops
	EffectsStack*			m_pPPStack;

	// The name of the current effect we are reflecting/applying
	String_256				m_strCurrentEffectID;
	INT32						m_iCurrentStackPos;

};


#endif  //INC_LIVEEFFECTSTOOL



