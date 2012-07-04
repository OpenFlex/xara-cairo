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

// ProgBar.h - Definition of the CProgressBar window class. By Jason, 14/02/94


#ifndef INC_PROGBAR
#define INC_PROGBAR

#include <afxext.h>


/********************************************************************************

>	class CProgressBar : public CControlBar

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/02/93 (-ish)
	Purpose:	Progres bar display window for "busy" operations

 ********************************************************************************/


// Hierarchy:  CWnd -> CControlBar -> CProgressBar


class CProgressBar : public CControlBar
{
	DECLARE_DYNAMIC(CProgressBar)

public:
	CProgressBar();
	virtual ~CProgressBar();

	BOOL Create(CFrameWnd* pParentWnd, String_64 *JobDescrip = NULL,
				DWORD dwStyle = CBRS_BOTTOM,
				UINT32 nID = _R(AFX_IDW_STATUS_BAR));

	void CProgressBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

	INT32 GetPercent(void) const;
	BOOL SetPercent(INT32 Percent, BOOL RedrawBackground = FALSE, String_64 *JobDescrip = NULL);

protected:
	INT32 CurrentPercent;			// The currently displayed percentage value
	String_64 *JobDescription;	// NULL, or pointer to description of current job
	HFONT m_hFont;				// Cached display font handle
	INT32 m_FontDescent;			// Cached size of display-font descent
	BOOL FontIsSystemFont;		// TRUE if the m_hFont is a system Stock Object

#if _MFC_VER >= 0x300
	INT32 BarHeight;
#endif

	virtual void DoPaint(CDC* pDC);

	//{{AFX_MSG(CProgressBar)
	afx_msg void 	OnSize(UINT32, INT32, INT32);
	afx_msg LRESULT OnSizeParent(WPARAM, LPARAM lParam);
	afx_msg LRESULT	OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnGetFont(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 

