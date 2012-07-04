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

//
// Custom Windows scroll bar buttons.  This object is used by the (private)
// implementation of CScroller.
//
/*
 *  */


#ifndef SCRLBUTN__INC
#define SCRLBUTN__INC

#include <afxext.h>					// for class CBitmapButton


// These identifiers are used to distinguish the decrement button from the
// increment button when they are clicked.
#define IDB_DECBUTTON	1
#define IDB_INCBUTTON	2

#define IS_CHICAGO ((LOBYTE(LOWORD(GetVersion()))) > 3)
 

/////////////////////////////////////////////////////////////////////////////
// CScrollerButton, a specialisation of the MFC control class CBitmapButton,
// which displays on its face bitmaps loaded from the display driver's
// resources.

/***************************************************************************************
>	class CScrollerButton : public CBitmapButton

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	ages ago
	Purpose:	This OIL class extends standard Windows bitmapped buttons so that
				they respond to clicks with the right mouse-button, and send
				notification messages as long as they are held down.
				
****************************************************************************************/
class CScrollerButton : public CBitmapButton
{

/////////////////////////////////////////////////////////////////////////////
// Construction and destruction.

public:
	enum Orientation					// used to specify the direction of arrows etc.
	{
		UP, DOWN, LEFT, RIGHT
	};

private:
	// display driver's up/down/disabled button bitmaps
	static UINT32 BitmapNames[4][3];
	
	Orientation Orient;
	BOOL Reversed;
	BOOL TimerOn;
	UINT32 Message;
		
public:
	CScrollerButton(Orientation ort, UINT32 msg);
	
	virtual BOOL Create(LPCTSTR, DWORD style, const RECT& rect, CWnd* parent, UINT32 id);


/////////////////////////////////////////////////////////////////////////////
// Implementation.

private:
	virtual BOOL LoadOEMBitmaps(UINT32 upID, UINT32 downID, UINT32 disableID);
	void HandleButtonDown(BOOL reverse);
	void HandleButtonUp();	
	void DrawItem (LPDRAWITEMSTRUCT	lpDrawItemStruct);
	BOOL PlotMaskedBitmap(CDC* destDC, CBitmap* srcBitmap, INT32 SrcOffset,
					INT32 xPlotOffset,INT32 yPlotOffset, INT32 width, INT32 height);
/////////////////////////////////////////////////////////////////////////////
// Generated message map functions

protected:
	//{{AFX_MSG(CScrollerButton)
		afx_msg void OnLButtonDown(UINT32 nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT32 nFlags, CPoint point);
		afx_msg void OnRButtonDown(UINT32 nFlags, CPoint point);
		afx_msg void OnRButtonUp(UINT32 nFlags, CPoint point);
		afx_msg void OnTimer(UINT32 nIDEvent);
		afx_msg void OnCancelMode();
		afx_msg void OnLButtonDblClk(UINT32 nFlags, CPoint point);
		afx_msg void OnRButtonDblClk(UINT32 nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


// These private messages are sent by the scroller buttons to their parent window.
#define WM_INCBTNDOWN	(WM_USER + 0x104)
#define WM_DECBTNDOWN	(WM_USER + 0x105)


/////////////////////////////////////////////////////////////////////////////

#endif		// SCRLBUTN__INC
