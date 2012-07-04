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

// Header file for status line class

#ifndef INC_STATUSLINE
#define INC_STATUSLINE

//#include "pump.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "flags.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "camframe.h"
//#include "monotime.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "stdbars.h"
//#include "ed.h"
#include "ktimer.h"

class Spread;
class StringBase;
class Cursor;

#define STATUSLINE_SELDESC_DEFAULT		1	// over dialogs, outside app window
#define STATUSLINE_SELDESC_BARDRAG		0
#define STATUSLINE_SELDESC_OTHERDOC		0
#define STATUSLINE_SELDESC_DRAGOPS		1
#define STATUSLINE_SELDESC_SELDOC		1
#define STATUSLINE_SELDESC_COLBAR		1
#define STATUSLINE_SELDESC_STATBAR		1
#define STATUSLINE_SELDESC_BUTTONS		1
#define STATUSLINE_SELDESC_MENUS		1
#define STATUSLINE_SELDESC_PREVIEWDLG	1

enum RenderState { Rendering,Paused,NotRendering,Animate };


/****************************************************************************************
>	class StatusLine : public MessageHandler

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/11/94
	Purpose:	Encapsulate the status line
********************************************************************************************/

class StatusLine : public StandardBar
{
public:
	StatusLine();
	~StatusLine();

	MsgResult Message(Msg* Msg);
	BOOL UpdateText(String_256* ptext, BOOL PrefixSelDesc=TRUE);
	BOOL UpdateTextForColourPicker(String_256* ptext, BOOL PrefixSelDesc=TRUE);
	BOOL UpdateMousePosAndSnap(DocCoord* pDocCoord, Spread* pSpread, DocView* pDocView, BOOL Snapped);
	BOOL UpdateSolidDragIndicator(BOOL bSolidAllowed, BOOL bSolid);
	BOOL SetRenderIndicator(RenderState Action);
	void FlagMousePosNeedsUpdating() { MousePosNeedsUpdatingFlag=TRUE; };
	BOOL MousePosNeedsUpdating() { return MousePosNeedsUpdatingFlag; };
	
	void FlagMousePosPaneNeedsUpdating() {MousePosPaneNeedsResizing=TRUE;};

	// This can be used to override the default behaviour of showing the selection state
	// as a prefix to the status-line.
	static void SetPrefix(const StringBase& str);
	static void SetDefaultPrefix();
	static INT32  GetPrefixWidth();

	// colour picker custom control interface functions ....

	BOOL RestrictStatusLineFunctionsToColourPicker (CWindowID colourPicker);
	BOOL RestoreStatusLineFunctions (CWindowID colourPicker);
	BOOL IsRestrictedAccessToColourPicker () { return restrictStatusLineFunctionsToColourPicker; }

	BOOL LockOutControlHelp () { DoControlHelp = FALSE; return (TRUE); }
	BOOL UnlockControlHelp () { DoControlHelp = TRUE; return (TRUE); }
	BOOL AllowControlHelp () { return (DoControlHelp); }

	void SetNeedsUpdate(BOOL Immediate=FALSE);

protected:
	BOOL OnIdleEvent();

	BOOL SetMousePosPaneWidth(Spread* pSpread);
	BOOL RefreshHelpText();
	BOOL GetMousePosText(String_256* pText, DocCoord MousePos, Spread* pSread, INT32 dp=-1);
	BOOL TruncateTextToWidth(String_256* pText, INT32 width);

	Cursor* pSnappedCursor;
	INT32 SnappedCursorID;

protected:

	MonotonicTime TextTimer;
	MonotonicTime RenderTimer;
	BOOL MousePosPaneNeedsResizing;
	BOOL MousePosNeedsUpdatingFlag;
//	BOOL TransparencyNeedsUpdating;
	INT32  RenderAnimationState;
	INT32  MousePosDP;
	INT32 OldMemory;

private:

	// The prefix to display in the status-line - if empty, show the selection state.
	static String_256 m_strPrefix;

	static BOOL restrictStatusLineFunctionsToColourPicker;
	static BOOL DoControlHelp;								// whether controls are allowed
															// to display help text (or not)
	static StatusLine * s_pStatusLine;

public:
	static StatusLine * Get() {return s_pStatusLine;}

// Progress related functions
public:
	BOOL ShowProgress (BOOL Show=TRUE, StringBase *JobDescrip = NULL);

	INT32 GetPercent() const {return CurrentPercent;}
	BOOL SetPercent(INT32 Percent, BOOL RedrawBackground = FALSE, StringBase *JobDescrip = NULL);

	BOOL IsProgressShown() const {return ProgressShown;}

protected:
	INT32 CurrentPercent;			// The currently displayed percentage value
	String_256 *JobDescription;	// NULL, or pointer to description of current job
	BOOL ProgressShown;
	String_256 StatusText;
	BOOL SetStatusText(const String_256 &text);
	String_256 m_MousePosText;

	void OnTimer()
	{
		GetApplication()->NeedMoreIdles();
	}

	class StatusTimer : public KernelTimer
	{
	public:
		StatusTimer(StatusLine * pOwner) : m_pOwner(pOwner) {}
		virtual void Notify() {m_pOwner->OnTimer();}
		StatusLine * m_pOwner;
	};

	StatusTimer m_Timer;

	CC_DECLARE_DYNCREATE(StatusLine);
};

#endif  // INC_STATUSLINE
