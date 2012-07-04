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



// Header file for the GalleryBar class

#ifndef INC_GALBAR
#define INC_GALBAR

//#include "dockbar.h"  - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "bars.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "basebar.h"

#ifndef WIN32
#include "dlgmgr.h"		// for DLGTEMPLATE etc
#endif

/********************************************************************************************

>	class GalleryBar : public BaseBar

	Author:		Alex Bligh
	Created:	22/6/94
	Purpose:	A subclass of BaseBar that is the oil representation of a Gallery
	SeeAlso:	GalleryBar

********************************************************************************************/

class GalleryBar : public BaseBar
{
public:
	DECLARE_DYNCREATE( GalleryBar )

	GalleryBar();
	CSize GetGallerySize(){ return GallerySize;}
	// Generated message map functions
	//{{AFX_MSG(GalleryBar)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
//	afx_msg BOOL OnNcActivate(BOOL bActive);
//	afx_msg INT32 OnMouseActivate( CWnd* pDesktopWnd, UINT32 nHitTest, UINT32 message );
//	afx_msg void OnActivate( UINT32 nState, CWnd* pWndOther, BOOL bMinimized );
//	afx_msg void OnActivateApp( BOOL  bActive, HTASK  hTask );   
//	afx_msg void OnPaint();
	afx_msg UINT32 OnNcHitTest(CPoint point);
	afx_msg void OnMouseMove(UINT32 nFlags, CPoint point);
//	afx_msg void OnNcRButtonDown(UINT32 nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT32 nHitTest, CPoint point);
//	afx_msg void OnLButtonDown(UINT32 nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT32 nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk( UINT32 nFlags, CPoint point );
//	afx_msg void OnParentNotify( UINT32 message, LPARAM lParam );  
//	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT32 nFlags, short zDelta, CPoint pt);
//	afx_msg void OnSize(UINT32 nType, INT32 cx, INT32 cy);
	//}}AFX_MSG

	afx_msg LRESULT GetBarSize(WPARAM DockType , LPARAM ControlSize);
	afx_msg LRESULT SetGallerySize(WPARAM cx, LPARAM cy);
	afx_msg LRESULT DoResize(WPARAM , LPARAM);
	afx_msg LRESULT SetControlFocus(WPARAM , LPARAM State);
	DECLARE_MESSAGE_MAP()

protected:
	void PaintWin95BarNonClient(BOOL IsActive);
	
	// Format this bar according to its dock type
	virtual BOOL FormatBar(BOOL MoveWindows,ForceControlSize Force);
	
	// Format a Horizontal bar from the kernel BarItem list
	virtual BOOL FormatHorizontalBar(BOOL MoveWindows,ForceControlSize Force);

   	// Format a Vertical bar from the kernel BarItem list
	virtual BOOL FormatVerticalBar(BOOL MoveWindows,ForceControlSize Force);
	
	// Size the actual window
	virtual CRect SetBarSize(DockBarType BarType,BOOL DoRedraw = TRUE);

	// Adjust the size of a bar post format
	virtual void AdjustFormattedBarSize(CSize* BarSize);

	// Position and Format controls
	virtual BOOL PositionControls(BOOL DoRedraw = TRUE);

	// Create any extra controls
	virtual INT32 CreateExtraControls();

	// Position any extra controls
	virtual void PositionExtraControls(CSize BarSize, INT32 xpos, INT32 ypos);

	virtual BOOL SetStatusLineText();
	virtual BOOL GetStatusText(String_256 * StatusText);

	virtual CRect GetFormatRect(DockBarType BarType);

private:
	CSize	GallerySize;
	HWND	ListBoxHWND;
	CFont * ListFont;
};

#endif
