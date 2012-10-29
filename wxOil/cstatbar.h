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

// CCStatusBar

#ifndef INC_CCSTATUSBAR
#define INC_CCSTATUSBAR

//#include "ed.h"
//#include "eddlg.h"

// Special include to get VC4/MFC4 to compile as the CStatusBar class has changed in MFC4
#include "mfcstat.h"

//#define _STATUSLINE_MEMORYPANE
//#define _STATUSLINE_RENDERPANE

struct StatusBarPaneData { 
	UINT32      PaneID;
	FlagState InitState;
	BOOL	  OwnerDrawn;	// UIC
	UINT32      BubbleHelpID;
	UINT32      StatusHelpID;
	UINT32      BitmapID;
	UINT32      OffBitmapID;
};
// UIC for Win '95
// --------------------------------------------------------------------------------------------------------
// Status bar without current separation mode field
// data required to specify the status bar panes ...
static StatusBarPaneData StatusLineData[] = 
{
	{ _R(ID_SEPARATOR),        Enable,  TRUE, _R(IDS_SL_HELPTEXT_BH), _R(IDS_SL_HELPTEXT_SH), NULL,  NULL }, 

	{ _R(IDS_SL_SDRAG),		   Disable, TRUE, _R(IDS_SL_SDRAG_BH), _R(IDS_SL_SDRAG_SH), _R(IDB_SL_SDRAG0),  _R(IDB_SL_SDRAG1) },

	{ _R(IDS_SL_SNAPPED),      Disable, TRUE, _R(IDS_SL_SNAPPED_BH),  _R(IDS_SL_SNAPPED_SH), _R(IDB_SL_SNAP),  _R(IDB_SL_SNAPN) },	

#ifdef _STATUSLINE_RENDERPANE
	{ _R(IDS_SL_RENDERING),    Enable, TRUE, _R(IDS_SL_RENDERING_BH), _R(IDS_SL_RENDERING_SH), _R(IDB_SL_RENDN), _R(IDB_SL_RENDN) },
#endif

	{ _R(IDS_SL_MOUSEPOS),     Disable,	TRUE, _R(IDS_SL_MOUSEPOS_BH),     _R(IDS_SL_MOUSEPOS_SH), NULL, NULL },			

#ifdef _STATUSLINE_MEMORYPANE
	{ _R(IDS_SL_MEMORY),       Enable,  FALSE, _R(IDS_SL_MEMORY_BH), _R(IDS_SL_MEMORY_SH), NULL, NULL }	
#endif
};

// --------------------------------------------------------------------------------------------------------
// Status bar with current separation mode field
// data required to specify the status bar panes ...
static StatusBarPaneData StatusLineData2[] = 
{
	{ _R(ID_SEPARATOR),        Enable,  TRUE, _R(IDS_SL_HELPTEXT_BH), _R(IDS_SL_HELPTEXT_SH), NULL,  NULL }, 

	{ _R(IDS_SL_PRINTMODE),    Disable,	TRUE, _R(IDS_SL_PRINTMODE_BH), _R(IDS_SL_PRINTMODE_SH), _R(IDB_SL_PRINTMODE), NULL },

	{ _R(IDS_SL_SDRAG),		   Disable, TRUE, _R(IDS_SL_SDRAG_BH), _R(IDS_SL_SDRAG_SH), _R(IDB_SL_SDRAG0),  _R(IDB_SL_SDRAG1) },

	{ _R(IDS_SL_SNAPPED),      Disable, TRUE, _R(IDS_SL_SNAPPED_BH),  _R(IDS_SL_SNAPPED_SH), _R(IDB_SL_SNAP),  _R(IDB_SL_SNAPN) },	

#ifdef _STATUSLINE_RENDERPANE
	{ _R(IDS_SL_RENDERING),    Enable, TRUE, _R(IDS_SL_RENDERING_BH), _R(IDS_SL_RENDERING_SH), _R(IDB_SL_RENDN), _R(IDB_SL_RENDN) },
#endif

	{ _R(IDS_SL_MOUSEPOS),     Disable,	TRUE, _R(IDS_SL_MOUSEPOS_BH),     _R(IDS_SL_MOUSEPOS_SH), NULL, NULL },			

#ifdef _STATUSLINE_MEMORYPANE
	{ _R(IDS_SL_MEMORY),       Enable,  FALSE, _R(IDS_SL_MEMORY_BH), _R(IDS_SL_MEMORY_SH), NULL, NULL }	
#endif
};



/*****************************************************************************
>	class	CCStatusBar : public CStatusBar

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/12/94
	Purpose:	To override various part of the CStatusBar
*****************************************************************************/

class CCStatusBar : public CStatusBar
{
	DECLARE_DYNAMIC(CCStatusBar);

// over-ridden base class functions
public:
	CCStatusBar();
	~CCStatusBar();
//	void DoPaint(CDC* pdc);
	void DrawStatusText(CDC* pDC, const CRect& rect, LPCTSTR lpszText, UINT32 nStyle);
	BOOL SetIndicators(StatusBarPaneData* pSLPD, INT32 Panes);
	BOOL Create(CFrameWnd* pParentWnd,
				DWORD dwStyle=WS_CHILD|WS_VISIBLE|CBRS_BOTTOM,
				UINT32 nID=_R(AFX_IDW_STATUS_BAR));

	// UIC 
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

	virtual void DrawItem(LPDRAWITEMSTRUCT);
		
	BOOL UpdateStatusLineFont();
	
	//{{AFX_MSG(CCStatusBar)
	afx_msg void OnLButtonDblClk(UINT32 nFlags, CPoint point);
	afx_msg void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT32 nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

// new functions
public:
	BOOL UpdatePaneText(INT32 PaneID, StringBase* pText, BOOL ImmediateUpdate=FALSE);
	BOOL UpdatePaneBitmap(INT32 PaneID, UINT32 BitmapID, BOOL ImmediateUpdate);
	BOOL GetPaneRect(CRect* pRect, INT32 PaneID);
	BOOL SetPaneWidth(INT32 width, INT32 PaneID);
	INT32  GetTextWidth(StringBase* pText, BOOL fBold = FALSE);
	INT32  GetPaneIndexFromPoint(CPoint point);
	BOOL GetStatusLineText(String_256* pText, CPoint MousePos, HWND hWnd);
	BOOL PaintBitmap(CDC* pDC, const CRect& rect, UINT32 BitmapID, UINT32 nStyle);
	FlagState PaneState(INT32 PaneID, FlagState NewState=NoChange);  
	static TCHAR* BubbleHelpCallBack(HWND hWnd, UINT32 PaneID, void* UserData);
	BOOL UnSetIndicators();
	BOOL PaneExists(INT32 PaneID);

protected:
	UINT32     NumPanes;
	CPoint   OldMousePos;
	StatusBarPaneData* pPaneData;
	CFont m_OldFont;

};

#endif  // INC_CCSTATUSBAR


