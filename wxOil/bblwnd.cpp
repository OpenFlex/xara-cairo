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


// A class to implement the bubble help window.


#include "camtypes.h"

#include "bblwnd.h"

//#include "resource.h"
#include "fonts.h"
#include "camelot.h"	// IsWin32s

#include <multimon.h>

char *BubbleHelpWnd::BubbleClass = NULL;

#define TEXT_NOBUBBLEHELP "NO bubble help!"

// The new COLOR variables are only defined on VC4/MFC4, so only do this on this version or later 
// Use the same criteria that winuser.h uses to define them. We will only define them when it
// doesn't
#if (WINVER < 0x0400)
#define COLOR_INFOTEXT          23
#define COLOR_INFOBK            24
#endif

/********************************************************************************************

>	BubbleHelpWnd::BubbleHelpWnd()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/94
	Purpose:	Construct a bubble help window.  This gets a handle to the font that the
				window will use (this handle is released when the window is destroyed).
	SeeAlso:	BubbleHelpWnd::Init

********************************************************************************************/

BubbleHelpWnd::BubbleHelpWnd()
{
	BubbleText = NULL;

	// Get the font we want to use for this bubble help window.
	BubbleFont = FontFactory::GetCFont(STOCKFONT_BUBBLEHELP);
}

/********************************************************************************************

>	BubbleHelpWnd::~BubbleHelpWnd()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/94
	Purpose:	Deletes a bubble help window - frees up any buffers used to remember the
				bubble help text, and gives the font handle back to Windows.
	SeeAlso:	BubbleHelpWnd::Init

********************************************************************************************/

BubbleHelpWnd::~BubbleHelpWnd()
{
	free(BubbleText);

	// Call this here to prevent MFC giving us an annoying warning...
	DestroyWindow();
}

// Usual MFC message map affair:

BEGIN_MESSAGE_MAP(BubbleHelpWnd, CWnd)
	//{{AFX_MSG_MAP(BubbleHelpWnd)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_NCCALCSIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// BubbleHelpWnd message handlers


/********************************************************************************************

>	void BubbleHelpWnd::OnNcPaint()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Purpose:	We override this even though we have no client area just in case...
	SeeAlso:	BubbleHelpWnd::OnPaint

********************************************************************************************/

void BubbleHelpWnd::OnNcPaint()
{
	// Do not call CWnd::OnNcPaint() for painting messages
}

/********************************************************************************************

>	void BubbleHelpWnd::OnPaint()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Purpose:	Paint the bubble help window's client area.  i.e. draw the rounded
				rectangle and paint the bubble help text into it.

********************************************************************************************/

void BubbleHelpWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// In debug builds, if no bubble help exists we show the "No Bubble Help!!" message
	// in yellow on red. In retail builds we just don't do anything if there is no
	// bubble help.
#if _DEBUG
	BOOL NoBubbleHelp = (camStrcmp(BubbleText, TEXT_NOBUBBLEHELP) == 0);
#endif

	// Create the yellow brush to paint the client area (unless we have no bubble help
	// and it's a debug build)
	// Instead of yellow use the new Tool tip system colours that are new in Windows 95
	// and in NT 3.51
	CBrush Brush;

	COLORREF BubbleBorderColour		= GetSysColor(COLOR_WINDOWFRAME);
	COLORREF BubbleTextColour		= RGB(0,0,0);		// Black
	COLORREF BubbleBackgroundColour = RGB(255,255,100);	// Yellow 

#if _DEBUG
	// If no bubble help and on debug versions then use special colours
	if (NoBubbleHelp)
	{
		BubbleBorderColour		= RGB(255,0,0);	// Red
		BubbleTextColour		= RGB(255,0,0);	// Red
		BubbleBackgroundColour	= RGB(0,255,0);	// Blue
	}
	else
#endif
	{
		// Use the proper Windows 95 bubble help text and background colour if
		// we are not on Win32s, as this doesn't support it, and as a double check
		// see if the bubble help foreground and background colours are different. This
		// should stop NT3.5 being wrong as these colours are unlikely to be defined. On
		// NT3.51 they are defined.
		if (
			//( IsWindows95() || IsWindowsNT() ) &&
			CCamApp::IsPartialNewWindowsUI() &&
			( GetSysColor(COLOR_INFOTEXT) != GetSysColor(COLOR_INFOBK) )
		   )
		{
			BubbleTextColour		= GetSysColor(COLOR_INFOTEXT);
			BubbleBackgroundColour	= GetSysColor(COLOR_INFOBK);	
		}
	}

	// Create the brush for the background colour
	Brush.CreateSolidBrush(BubbleBackgroundColour);

	// Get the size of the window	
	RECT rect;
	GetClientRect(&rect);

	// Create the pen and select into the DC.
	CPen Pen;
	Pen.CreatePen(PS_SOLID, 0, BubbleBorderColour);
	CPen *OldPen = dc.SelectObject(&Pen);

	// Fill in the background colour
	InflateRect(&rect, -1, -1);
	dc.FillRect(&rect, &Brush);
	InflateRect(&rect, 1, 1);

	// Paint the rounded border
	POINT Points[9];

	Points[0].x = rect.left + 2;	Points[0].y = rect.top;
	Points[1].x = rect.right - 3; 	Points[1].y = rect.top;
	Points[2].x = rect.right - 1; 	Points[2].y = rect.top + 2;
	Points[3].x = rect.right - 1; 	Points[3].y = rect.bottom - 3;
	Points[4].x = rect.right - 3; 	Points[4].y = rect.bottom - 1;
	Points[5].x = rect.left + 2; 	Points[5].y = rect.bottom - 1;
	Points[6].x = rect.left; 		Points[6].y = rect.bottom - 3;
	Points[7].x = rect.left; 		Points[7].y = rect.top + 2;
	Points[8].x = rect.left + 2; 	Points[8].y = rect.top;

	dc.Polyline(Points, 9);

	// Use a nice small font
	CFont *OldFont = dc.SelectObject(BubbleFont);
	
	CString BubbleString(BubbleText);

	dc.SetBkMode(TRANSPARENT);
	
	// If it has no bubble help then do the text in red (only in debug builds)
	// else do it in the proper text colour
	#if _DEBUG
	if (NoBubbleHelp)
		dc.SetTextColor(RGB(255,0,0)); // Red
	else
	#endif
		dc.SetTextColor(BubbleTextColour);

	dc.TextOut(3, 1, BubbleString);

	// Clean up
	dc.SelectObject(OldFont);
	dc.SelectObject(OldPen);

	// Do not call CWnd::OnPaint() for painting messages
}

/********************************************************************************************

>	void BubbleHelpWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Inputs:		See CWnd::OnNcCalcSize
	Outputs:	See CWnd::OnNcCalcSize
	Purpose:	Inform Windows that we have no non-client area - we actually do nothing
				in this function, but if we don't override it, MFC/Windows will give us
				a non-client area, which we don't want.

********************************************************************************************/

void BubbleHelpWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	// Do nothing - we have no non-client area!
}


/********************************************************************************************

>	BOOL BubbleHelpWnd::Init()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Returns:	TRUE if the bubble help system intialised ok;
				FALSE if not.
	Purpose:	Initialise the bubble help system.  This should be done once and only once
				before using a BubbleHelpWnd object.
				This function registers the special window class we use for the bubble help.
	Errors:		Out of memory.
	SeeAlso:	BubbleHelpWnd::Create
	Scope:		Static

********************************************************************************************/

BOOL BubbleHelpWnd::Init()
{
	// Register our special window class.
	// Text returned by AfxRegisterWndClass is only a static buffer, so we take a copy of
	// it for our own use.
	BubbleClass = camStrdup(AfxRegisterWndClass(CS_SAVEBITS));
	ENSURE(BubbleClass != NULL, "Bubble help window class could not be registered!");
	ERRORIF(BubbleClass == NULL, _R(IDS_OUT_OF_MEMORY), FALSE);

	// All ok
	return TRUE;
}



/********************************************************************************************

>	BOOL BubbleHelpWnd::DeInit()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28 September 2000
	Purpose:	Deinitialises the bubble help system.
				Actually this consists of freeing the BubbleClass static string,
				as otherwise it leaks memory.

********************************************************************************************/
BOOL BubbleHelpWnd::DeInit()
{
	free(BubbleClass);
	return TRUE;
}



/********************************************************************************************

>	BOOL BubbleHelpWnd::Create()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Returns:	TRUE if the window was created ok;
				FALSE if not.
	Purpose:	Create a window and associate it with this BubbleHelpWnd object.
				This will fail if BubbleHelpWnd::Init has not been called.
	Errors:		Bubble help system not initialised; Unable to create the window.
	SeeAlso:	BubbleHelpWnd::Init

********************************************************************************************/

BOOL BubbleHelpWnd::Create()
{
	ENSURE(BubbleClass != NULL, "Bubble help window class has not been registered!");

	if (BubbleClass == NULL)
		// System has not initialised so don't create a window.
		return FALSE;

	// Create the window (but ensure it is not visible)
	// WS_CHILD is needed to prevent MFC asserting because we're using the default
	// window class (I don't know why they enforce this...)
	return CreateEx(0, BubbleClass, NULL,
					(WS_POPUP & (~WS_VISIBLE)) // | WS_CHILD | WS_CLIPCHILDREN
					,
					CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
					AfxGetMainWnd()->GetSafeHwnd(), 
					NULL);
}

/********************************************************************************************

>	BOOL BubbleHelpWnd::SetText(UINT32 ResID, UINT32 ModuleID = 0)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Inputs:		ResID - a resource ID to use
				ModuleID - the module ID (used to locate the string resource).
	Returns:	TRUE if the text was found and set ok;
				FALSE if not.
	Purpose:	Set the text string to be used in the bubble help window.
	Errors:		Unable to find resource; Out of memory

********************************************************************************************/

BOOL BubbleHelpWnd::SetText(UINT32 ResID, UINT32 ModuleID)
{
	if (ResID == 0)
	{
		#if _DEBUG
		return SetText("");
		#else
		// Duff string resource ID - ignore it.
		return FALSE;
		#endif
	}

	// Make a string out of it
	String_64 BubbleString;
	BubbleString.Load(ResID, ModuleID);
	return SetText((TCHAR *)BubbleString);
}

/********************************************************************************************

>	BOOL BubbleHelpWnd::SetText(TCHAR *Text)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/05/94
	Inputs:		ResID - a resource ID to use
				ModuleID - the module ID (used to locate the string resource).
	Returns:	TRUE if the text was found and set ok;
				FALSE if not.
	Purpose:	Set the text string to be used in the bubble help window.
				(This is used by the overloaded version of SetText, but can be used by
				other clients, e.g. ControlHelper uses it to do ad-hoc help).
	Errors:		Out of memory

********************************************************************************************/

BOOL BubbleHelpWnd::SetText(TCHAR *Text)
{
	if (BubbleText != NULL)
		// Delete previous text
		free(BubbleText);

	#if _DEBUG

	if ((Text == NULL) || (Text[0] == 0))
		BubbleText = camStrdup(TEXT_NOBUBBLEHELP);
	else
		BubbleText = camStrdup(Text);

	#else

	if ((Text == NULL) || (Text[0] == 0))
		// No text!
		return FALSE;

	BubbleText = camStrdup(Text);

	#endif

	if (BubbleText == NULL)
		// Out of memory
		return FALSE;

	// Work out how big the window should be.

    // Get a context
    CDC *dc = GetWindowDC();
    
	// Get a nice small font
	CFont *OldFont = dc->SelectObject(BubbleFont);

	// Find out how big this text is.
	CSize TextSize = dc->GetTextExtent(BubbleText, camStrclen(BubbleText));

	// Clean up and release the DC
	dc->SelectObject(OldFont);
	ReleaseDC(dc);

	// Set the window size according to the text size
	BubbleSize.x = TextSize.cx + 5;
	BubbleSize.y = TextSize.cy + 3;
	SetWindowPos(NULL, 0, 0, BubbleSize.x, BubbleSize.y,
				 SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);

	// All worked ok
	return TRUE;
}

/********************************************************************************************

>	void BubbleHelpWnd::Show()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/05/94
	Purpose:	Shows the bubble help window - it is sized and positioned automatically.
	SeeAlso:	BubbleHelpWnd::Hide

********************************************************************************************/

void BubbleHelpWnd::Show()
{
	// Work out where to put window based on cursor position
	POINT CursorPos;
	::GetCursorPos(&CursorPos);

	// Centre the window under the cursor.
	POINT Pos;
	Pos.x = CursorPos.x - (BubbleSize.x / 2) + 10;
	Pos.y = CursorPos.y + 16;

	RECT PossibleBubbleWin;
	PossibleBubbleWin.left		= Pos.x;
	PossibleBubbleWin.right		= Pos.x + BubbleSize.x;
	PossibleBubbleWin.top		= Pos.y;
	PossibleBubbleWin.bottom	= Pos.y + BubbleSize.y;

	MONITORINFO mi;
	mi.cbSize = sizeof(MONITORINFO);
	if (GetMonitorInfo(MonitorFromRect(&PossibleBubbleWin, MONITOR_DEFAULTTONEAREST), &mi) == 0)
	{
		SetWindowPos(NULL, Pos.x, Pos.y, 0, 0, 
			 SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
		TRACE( _T("Could not find a monitor to display bubble help on\n"));
		return;
	}

	// Make sure the window stays on a screen
	RECT Rect = mi.rcMonitor;
	if (Pos.x < Rect.left)
		Pos.x = Rect.left;
	if (Pos.x + BubbleSize.x > Rect.right)
		Pos.x = Rect.right - BubbleSize.x;
	if (Pos.y < Rect.top)
		Pos.y = Rect.top;

	if (Pos.y + BubbleSize.y > Rect.bottom)
	{
		// If we move up we'll probably cover the cursor, so make sure it's above the cursor
		Pos.y = CursorPos.y - 20;
	}
	
	SetWindowPos(NULL, Pos.x, Pos.y, 0, 0, 
				 SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

/********************************************************************************************

>	void BubbleHelpWnd::Hide()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/05/94
	Purpose:	Hides the bubble help window but does not destroy it.
	SeeAlso:	BubbleHelpWnd::Show

********************************************************************************************/

void BubbleHelpWnd::Hide()
{
	ShowWindow(SW_HIDE);
}


