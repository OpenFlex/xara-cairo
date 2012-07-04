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
// This declares the CScroller, CHorzScroller &
// CVertScroller classes, which implement RISCOS
// style proportional scroll bars under Windows. It
// also declares the CScrollerCorner window, which
// is the "size box" gadget between two scroll bars.
//
/*
 *  */


#ifndef SCROLLER__INC
#define SCROLLER__INC

#include "camelot.h"
//#include "ccmaths.h" - in camtypes.h [AUTOMATICALLY REMOVED]


/////////////////////////////////////////////////////////////////////////////
// This user-defined messsage indicates to the window owning the scroller
// that the scroll offset has changed.

#define WM_SCROLLEREVENT	(WM_USER + 0x110)

/////////////////////////////////////////////////////////////////////////////
// CScrollerCorner window

/***************************************************************************************
>	class CScrollerCorner : public CWnd

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	ages ago
	Purpose:	This OIL class is the little square in the bottom-right of a window
				featuring horizontal and vertical scroll bars.  It is currently
				completely useless (except visually, of course).
				
****************************************************************************************/

class CScrollerCorner : public wxWindow
{

/////////////////////////////////////////////////////////////////////////////
// Construction

public:
	CScrollerCorner();
	virtual BOOL Create(LPCTSTR, LPCTSTR, DWORD style, const wxRect& rect,
						wxWindow* pParent, UINT32 id);

private:
	wxBitmap SizeBitmap;


private:
	DECLARE_EVENT_TABLE()

public:
	void OnPaint(wxPaintEvent& event );
	void OnLButtonDown(wxMouseEvent &event );
	
	void OnSetCursor( wxSetCursorEvent& event );
};

/////////////////////////////////////////////////////////////////////////////

class CWinScroller : public wxScrollBar
{
protected:
	static INT32 ScrollerSize	;			// UIC 
/*
	XLONG MinVal;						// "smallest" scroll value
	XLONG MaxVal;						// "largest" scroll value
	XLONG Range;						// the difference between the above
	XLONG Delta;						// the sign of (MaxVal - MinVal)
	XLONG ThumbVal;						// current scroll value
	
	XLONG Granularity;					// smallest possible scroll delta
	XLONG LineSize;						// current size of a "line"
	XLONG PageSize;						// current size of a "page"
	
	BOOL Proportional;
	BOOL Enabled;
*/
	BOOL Horizontal;

public:
	CWinScroller(BOOL Horizontal);
	virtual ~CWinScroller();
	BOOL Create(wxWindow* pParent, UINT32 nID, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize);

public:
	virtual BOOL IsHorizontal() { return Horizontal; };
/*
	void GetScrollPos(XLONG* pxl) const;
	static INT32 GetScrollerSize() {return ScrollerSize;};
	void SetGranularity(const XLONG& unit);

	void SetScrollPos(const XLONG& n, BOOL redraw = TRUE);
	void SetScrollRange(const XLONG& lo, const XLONG& hi, BOOL redraw = TRUE);
	
	void SetLineSize(const XLONG& sz);
	void SetPageSize(const XLONG& sz);
	
	void LineUp();
	void LineDown();
	void PageUp();
	void PageDown();
	
	void ShowScroller(BOOL show = TRUE);
	static BOOL HasScrollerSizeChanged();	// UIC

	void SetProportional(BOOL bProp);
	virtual void CalcPosFromParentClient(LPRECT lpRect);
	void HandleScrollMessage(UINT32 nSBCode, UINT32 nPos);

private:
	void SnapToGrain(XLONG* pxl) const;
	void ClipThumbPos(const XLONG& n);
	void MoveThumb(BOOL redraw);
*/
};


#endif		// SCROLLER__INC
