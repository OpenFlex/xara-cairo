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
// This file declares the CRendWnd class, into which all document rendering
// is done.
//
/*
 *  */

#ifndef RENDWND__INC
#define RENDWND__INC

// A private message
#define WM_RENDERVIEW	(WM_USER + 200)

#define OPTOKEN_TOGGLEDOUBLEBUFFER		TEXT("ToggleDoubleBuffer")

class CCClientDC;
class CCamView;

/////////////////////////////////////////////////////////////////////////////
// CRenderWnd window

/***************************************************************************************
>	class CRenderWnd : public wxWindow

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	ages ago
	Purpose:	This OIL class is rendered into.  It passes all input to its parent
				CCamView window.
				
****************************************************************************************/
class CRenderWnd : public wxWindow
{
	DECLARE_DYNAMIC_CLASS(CRenderWnd)

public:
	CRenderWnd(CCamView* pView = NULL);
	virtual ~CRenderWnd();

/////////////////////////////////////////////////////////////////////////////
// Construction and destruction.

public:
	virtual BOOL Create(const wxRect& rect, wxWindow* parent, UINT32 id);
	void SetView(CCamView* pView) { m_pView = pView; }
	CCamView* GetView(void) { return(m_pView); }

	static void SetDoubleBuffer (BOOL DoubleBuffer);
	static BOOL GetDoubleBuffer () {return m_DoubleBuffer;}

	virtual wxClientDC * GetClientDC();
	virtual void AllocateDC(BOOL KeepIt=TRUE);
	virtual void DoneWithDC();

/////////////////////////////////////////////////////////////////////////////
// Generated message map functions

protected:
	void OnPaint( wxPaintEvent &evnt );
	void OnLButtonDown( wxMouseEvent &evnt );
	void OnLButtonDblClk( wxMouseEvent &evnt );
	void OnLButtonUp( wxMouseEvent &evnt );
	void OnMouseMove( wxMouseEvent &evnt );
	void OnRButtonDown( wxMouseEvent &evnt );
	void OnRButtonDblClk( wxMouseEvent &evnt );
	void OnRButtonUp( wxMouseEvent &evnt );
	void OnMButtonDown( wxMouseEvent &evnt );
	void OnMButtonDblClk( wxMouseEvent &evnt );
	void OnMButtonUp( wxMouseEvent &evnt );
	void OnMouseWheel( wxMouseEvent &evnt );

    void OnSize ( wxSizeEvent &event );
    void OnErase ( wxEraseEvent &event );

	void OnSetCursor( wxSetCursorEvent &event );

#if defined(__WXGTK__)
	void OnEnter( wxMouseEvent &event );
	void OnLeave( wxMouseEvent &event );
#endif

	void OnKey ( wxKeyEvent & event);
	void OnChar( wxKeyEvent& event );
	void OnIdle( wxIdleEvent& event );

protected:
	CCamView* m_pView;

	static BOOL m_DoubleBuffer;
	static void ReflectDoubleBufferingInChildren(wxWindow * pWindow);

	INT32 m_DCUsers;

	DECLARE_EVENT_TABLE()

	CCClientDC * m_pCCClientDC;
};


#if WIN32

const INT32 MAX_RECT_LIST=4;

typedef struct
{
	RGNDATAHEADER rdh;
	RECT rectlist[MAX_RECT_LIST];
} CCRGNDATA;

#endif

UINT32 GetRectangleList( wxDC* pCDC, LPRECT *lplpRect );

/////////////////////////////////////////////////////////////////////////////

/********************************************************************************************

>	class OpToggleDoubleBuffer : public Operation

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14 Mar 2006
	Purpose:	This class represents the OpToggleDoubleBuffer operation.
				Creating an instance of this class and calling its "Do" function will toggle
				the state of the flag controlling whether double buffering is used for
				rendering on GTK

********************************************************************************************/

class OpToggleDoubleBuffer: public Operation
{
	CC_DECLARE_DYNCREATE( OpToggleDoubleBuffer )
	
public:
	OpToggleDoubleBuffer();											// Constructor
	~OpToggleDoubleBuffer();										// Destructor

	static BOOL		Init();									// Register an OpDescriptor
	void			Do(OpDescriptor*);						// "Do" function
	static OpState	GetState(String_256*, OpDescriptor*);	// Read the state of an operation
};


#endif	// RENDWND__INC
