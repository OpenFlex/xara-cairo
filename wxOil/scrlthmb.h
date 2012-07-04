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

/*
	The proportional scroller thumb window.


*/


#ifndef	SCRLTHMB__INC
#define SCRLTHMB__INC



/***************************************************************************************
>	class CScrollerThumb : public CWnd

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	ages ago
	Purpose:	This OIL class represents a scroll bar "thumb", which sends drag
				messages to its parent CScroller object.
				
****************************************************************************************/

class CScrollerThumb : public CWnd
{

/////////////////////////////////////////////////////////////////////////////
// Data, construction and destruction.

private:
	BOOL Dragging;
	BOOL DragIsAdjust;

public:
	CScrollerThumb();
	virtual ~CScrollerThumb();
	
	virtual BOOL Create(LPCTSTR, LPCTSTR, DWORD style, const RECT& rect,
						CWnd* parent, UINT32 id, CCreateContext* ctxt = 0);
	

/////////////////////////////////////////////////////////////////////////////
// Implementation

private:
	void PostMsgToScroller(UINT32 msg, CPoint pt) const;

	void OnWin95Paint();

/////////////////////////////////////////////////////////////////////////////
// Message map for CScrollerThumb.

	// Generated message map functions
protected:
	//{{AFX_MSG(CScrollerThumb)
		afx_msg void OnPaint();
		afx_msg void OnLButtonDown(UINT32 nFlags, CPoint point);
		afx_msg void OnRButtonDown(UINT32 nFlags, CPoint point);
		afx_msg void OnMouseMove(UINT32 nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT32 nFlags, CPoint point);
		afx_msg void OnRButtonUp(UINT32 nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


// These private messages are passed between the scroller and its thumb, when
// the user tries to drag the latter. The ADJ variants mean the drag is occurring
// in 'adjust' (right button) mode.
// Note that some other inter-scroller user message numbers are defined in scrlbutn.h
// hence these values start at 10a to avoid clashes.
#define WM_GRABTHUMB		(WM_USER + 0x10a)
#define WM_GRABTHUMBADJ		(WM_USER + 0x10b)
#define WM_DRAGTHUMB		(WM_USER + 0x10c)
#define WM_DRAGTHUMBADJ		(WM_USER + 0x10d)
#define WM_RELEASETHUMB		(WM_USER + 0x10e)
#define WM_RELEASETHUMBADJ	(WM_USER + 0x10f)


// This is the numeric child window identifier.
#define IDB_THUMB		3


#endif	// SCRLTHMB__INC
