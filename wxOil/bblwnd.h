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

/********************************************************************************************

>	class BubbleHelpWnd : public CWnd

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/94
	Purpose:	Provide a special window class for bubble help windows.  This window has
				a number of special properties.  It knows how big to make itself, and
				where to position itself - you just create one, tell it what text to display
				and then tell it to show itself. It's fabby, believe you me.
				It registers a special window class with the CS_SAVEBITS flag so that the
				window update is really snappy when it goes away (this flag tells Windows
				to cache the windows under the bubble help window in a bitmap, and then
				blit that back onto the screen when the bubble goes away - the same as
				menus do automatically).
	SeeAlso:	ControlHelper

********************************************************************************************/

class BubbleHelpWnd : public wxWindow
{
// Construction
public:
	BubbleHelpWnd();

// Attributes
public:

// Operations
public:
	static BOOL Init();
	static BOOL DeInit();
	BOOL Create();
	BOOL SetText(UINT32 ResID, UINT32 ModuleID = 0);
	BOOL SetText(TCHAR *);
	void Show();
	void Hide();
	void MoveTo(INT32 x, INT32 y);

// Implementation
public:
	virtual ~BubbleHelpWnd();

	// Generated message map functions
protected:
PORTNOTE("other", "Removed MFC MESSAGE_MAPs" )
#if !defined(EXCLUDE_FROM_XARALX)
	//{{AFX_MSG(BubbleHelpWnd)
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
#endif

protected:
	TCHAR*		BubbleText;
	wxFont*		BubbleFont;
	POINT  	 	 BubbleSize;

	// Name of the special window class for our bubble help windows
	static char *BubbleClass;
};

/////////////////////////////////////////////////////////////////////////////
