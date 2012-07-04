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

#ifndef INC_CAMVIEW_H
#define INC_CAMVIEW_H

//#include "docview.h"
//#include "ink.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "clikmods.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "rendwnd.h"
#include "wrkrect.h"
//#include "dragtrgt.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#include "wx/dnd.h"

// Forward definitions
class CRenderWnd;
class CWinScroller;
class CScrollerCorner;
class OILHorizontalRuler;
class OILVerticalRuler;
class OriginGadget;
class PrintView;
class DocView;
class ViewState;
class CCPrintInfo;
class PrintControl;
class Rect;

enum MouseOverRulerHit
{
	OVER_NO_RULERS,
	OVER_HORIZONTAL,
	OVER_VERTICAL,
	OVER_ORIGIN_GADGET
};


#define ReflectIntoView( Class, ViewClass, Handler, Type ) void Class::Handler( Type& event ) \
	{ ((ViewClass*)m_pView)->Handler( event ); }

/*******************************************************************************
>	class CCamView : public wxView

	Author:		Luke_Hart (Xara Group Ltd) <camelotdev@xara.com> H
	Created:	01/07/05
	Purpose:	This OIL class implements many window functions, such as
				scrolling and sizing the editing windows.  As such, it acts
				as an intermediary between the kernel and the host operating
				system.  It is derived from the wx class wxView, which
				provides comprehensive methods for managing the client area
				of a window.
				
				On creation, a CCamView asks its Document to provide a pointer
				to the DocView that is to be associated with this object.
				Once that link has been made, any changes in the state of the
				CCamView, eg. the user maximises it, are passed on in a
				device-independent form to the DocView.  This trick is done
				using a shared ViewState object.

*******************************************************************************/

class CCamView : public wxView
{

////////////////////////////////////////////////////////////////////////////////
// Creation and destruction.

public:
	CCamView();    						// default constructor
	virtual ~CCamView();

	virtual bool OnCreate( wxDocument* doc, /* TYPENOTE: Correct */ long flags );
	bool OnClose( bool deleteWindow = TRUE );

	wxMDIChildFrame *GetParentFrame() const
	{
		return m_pFrame;
	}

	static BOOL ReadViewPrefs();

////////////////////////////////////////////////////////////////////////////////
// Interface to the kernel's view onto a document and MFC's CDocument-derived
// object.

protected:
	void GrabKernelAttention() const;	// tells kernel this view is active
	void SetCurrentStates();
	virtual BOOL CreateNewDocView();
	virtual	BOOL IsARalphView(){ return FALSE;};

public:
	CCamDoc *GetDocument() const;		// returns a pointer to OIL/MFC document
	ViewState *GetViewState() const;	// returns a pointer to our ViewState
	ViewState *SetViewState( ViewState *pvs );

	void SetViewStateFromThis() const;  // set Status according to this view
	void SetThisFromViewState();		// set this view according to Status


public:
	BOOL IsTopmost() const;

////////////////////////////////////////////////////////////////////////////////
// Painting.

public:
	virtual CNativeDC *GetRenderDC() const;
	virtual void AllocateDC() const;
	virtual void DoneWithDC() const;
	void GetClientSize(/* TYPENOTE: Correct */ int * width, /*TYPENOTE: Correct */ int * height) const;
	
	virtual void OnDraw( wxDC *pDc );
PORTNOTE("printing", "Disabled CCamView::OnPreparePrinting")
#ifndef EXCLUDE_FROM_XARALX
	virtual BOOL OnPreparePrinting( CCPrintInfo *pInfo );
#endif

////////////////////////////////////////////////////////////////////////////////
// Menu functions, put in at Mario's behest.

public:
	virtual void OnFilePrint();
	virtual void OnFilePrintPreview();

public:
	CRenderWnd* GetRenderWindow() const { return(RenderWindow); }
	void InvalidateView(const OilRect* pRect = 0, BOOL updatenow = FALSE);

private:
    DECLARE_DYNAMIC_CLASS(CCamView)
    DECLARE_EVENT_TABLE()

public:
	void 	OnSize( wxSizeEvent &event );
	void 	OnLButtonDown( wxMouseEvent &event );
	void 	OnLButtonDblClk( wxMouseEvent &event );
	void 	OnLButtonUp( wxMouseEvent &event );
	void 	OnMButtonDown( wxMouseEvent &event );
	void 	OnMButtonDblClk( wxMouseEvent &event );
	void 	OnMButtonUp( wxMouseEvent &event );
	void 	OnRButtonDown( wxMouseEvent &event );
	void 	OnRButtonDblClk( wxMouseEvent &event );
	void 	OnRButtonUp( wxMouseEvent &event );
	void 	OnMouseMove( wxMouseEvent &event );
	void	OnMouseWheel( wxMouseEvent &event );
	void	OnScroll( wxScrollEvent &event);
	void	OnDragIdle( wxTimerEvent &event);		// OnTimer(DragIdleID)

	void	OnSetCursor( wxSetCursorEvent& event );

	bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);

protected:
	LRESULT OnRenderView( WPARAM wp, LPARAM lp );
	void ScrollTo(const WorkCoord& offset);
	void ScrollBy(INT32 dx, INT32 dy);

public:
	static DocView* GetDocViewFromWindow(wxWindow* pWindow);
	static void SetUseVisibleDefaults(BOOL state){ UseVisibleDefaults = state;};

//	void GetWorkAreaExtent(WorkRect* pArea) const;
	void SetWorkAreaExtent(const WorkRect& area, BOOL redraw = TRUE);
	void GetScrollOffset(WorkCoord* pOffset) const;
	void SetScrollOffset(const WorkCoord& pos, BOOL redraw = TRUE);
	void ShowScrollers(BOOL Show); 
	void ShowRulers(BOOL Show);
	WorkRect GetMaxScrollRect() const;

	BOOL AreRulersVisible();
	BOOL AreScrollersVisible();
	MouseOverRulerHit IsMouseOverRuler();

	static BOOL GetUseVisibleDefaults()				 { return UseVisibleDefaults;};
	static BOOL GetDefaultRulersState()				 { return DefaultRulersState;};
	static BOOL GetDefaultScrollersState()			 { return DefaultScrollersState;};
	static void SetDefaultRulersState(BOOL State)	 { DefaultRulersState = State;};
	static void SetDefaultScrollersState(BOOL State) { DefaultScrollersState = State;};

////////////////////////////////////////////////////////////////////////////////////////////////
// Drag'n'drop data and functions.

protected:

	void HandleDragEvent(UINT32 Button, UINT32 nFlags, wxPoint point, ClickType t);
	void HandleDragEvent(UINT32 Button, ClickModifiers clickmods, wxPoint point, ClickType t);
	BOOL HandleMouseWheelEvent( wxMouseEvent &event );
	void HandleDragScrolling(wxPoint point);
	void CalcScrollDeltas(wxPoint point, WinRect wrSize, INT32* dx, INT32* dy);
	void HandleButtonUp(UINT32 Button, wxMouseEvent &event);
//	virtual void HandleOleDragOutOfView(wxPoint point);	// Used to allow derived classes to provide OLE drag and drop


public:
	void RecaptureMouseOnNextUpdate(void);

	static void GetClickMods( wxMouseEvent &event, ClickModifiers *p );
	BOOL StartDrag(Operation* pOp, DragType type, BOOL KeepAccuracy);
	BOOL EndDrag(Operation* pOp);
	BOOL ChangeDragType(DragType Type);
	void ClearClickState();

	// Allows a drag op to be invoked from the ScreenView object, as if it had been
	// invoked as a result of clicking into the document.
	// Useful esp. for drag ops that are not connected to a particular tool and/or started
	// from clicks outside the view, e.g. Creating guidelines by clicking on a ruler window
	BOOL InvokeDragOp(String_256* pOpToken,OpParam* pParam,UINT32 Flags,wxPoint point);
	BOOL InvokeDragOp(String_256* pOpToken,OpParam* pParam,ClickModifiers clickmods,wxPoint point);

	// Function to test if there is another mouse move message in the queue
	BOOL IsWaitingMouseMove();

	// This sets the output parameter to the current mouse position within this
	// ScreenView.  If the cursor isn't within the view it returns FALSE.
	BOOL GetCurrentMousePos(OilCoord* pMousePos) const;

	BOOL CreateDragTarget(DragInformation * DragInfo);


public:
	DocView* GetDocViewPtr() const
	{
		return pDocView;
	}
//	virtual BOOL IsSelected(const CObject* pDocItem) const;

protected:
	// Helper functions for printing.
	BOOL PrintPaper(wxDC *pPrintDC, CCPrintInfo *pPrintInfo, PrintControl *pPrintControl);
	WinRect GetPrintClipRect(wxDC *pPrintDC, CCPrintInfo *pPrintInfo);
	void EnumeratePagePatches(CCPrintInfo *pPrintInfo);


	void UpdateViewPosition() const;	// called on moves & resizes

protected:
	virtual void OnInitialUpdate();		// called once between creation & painting
    virtual void OnUpdate(wxView* sender, wxObject* hint=(wxObject*)NULL);
	virtual void OnActivateView(bool bActivate, wxView* pActiveView,
								wxView* pDeactiveView);

////////////////////////////////////////////////////////////////////////////////////////////////
// Triple and quad click support

public:
	BOOL IsSingleClickReallyTriple() const	{return ThisSingleIsTriple;}
	BOOL IsSingleClickReallyQuad() const	{return ThisDoubleIsQuad;}

// Member variables
protected:
	wxMDIChildFrame* m_pFrame;
	CRenderWnd* RenderWindow;
	CWinScroller* HScrollBar;				// proportional scroll bars
	CWinScroller* VScrollBar;
	CScrollerCorner* Corner;                // the "size box"
	OILHorizontalRuler* HRuler;
	OILVerticalRuler* VRuler;
	OriginGadget* OGadget;

	DocView	   *pDocView;				// link to the kernel's view
	PrintView  *pPrintView;				// only linked during printing.
	ViewState  *Status;					// shared with the above

	BOOL fSetupDone;					// if TRUE then all inits done
	BOOL fInitialUpdate;				// Set after calling OnInitialUpdate
	BOOL fJustCreated;					// this view has never been activated before, it's new

	WinRect CurrentSize;				// the size of this view
	WorkRect WorkArea;
	WorkCoord OldOffset;				// previous scroller position

	// Vars used by InvokeDragOp()
	String_256 	DragOpToken;
	OpParam* 	pDragOpParam;
	BOOL 		DragOpInvoke;

	MonotonicTime TimeOfLastClick;
	wxPoint LastDoubleClickPos;
	BOOL ThisSingleIsTriple;
	BOOL ThisDoubleIsQuad;

	wxTimer m_DragIdleTimer;
	MonotonicTime m_OLELastOutTime;		// Used to time the delay before "OLE scrolling"

	BOOL DragKeepAccuracy;				// Used to control drag responsiveness

	BOOL AutoScrollExcludeRulers;		// Flag used to extend the autoscroll region to 
										// include rulers - allows guidelines to be deleted

	ClickType		LastClickType;		// click type of last START_DRAG
	UINT32			LastClickButton;	// buttons down on last START_DRAG
	wxPoint			LastClickPoint;		// mouse position of last START_DRAG
	wxPoint			CurrentMousePos;	// the mouse was here last time we looked
	ClickModifiers	LastClickMods;		// ClickMods on last mouse event (NOT
										// modified by button-up events!)

	UINT32 FirstClickButton;			// Which button started the drag (if dragging).

	Operation* pCurrentDragOp;			// current mouse-drag operation
	DragType CurrentDragType;			// what to do when dragging off-screen
	WinRect MouseClipRect;				// cursor was clipped against this

	BOOL OLERecaptureMouse;				// Used when OLE drags return to the view window - we resume our
										// drag, and we have to recapture the mouse to recover properly.

	// Mouse move elimination code
	INT32 m_LastMouseState;
	wxPoint m_LastMousePosition;
	INT32 m_LastMouseUsedTimestamp;
	BOOL m_CouldSkipNextMouse;

public:
	void DontSkipNextMouse() {m_CouldSkipNextMouse=FALSE;}

// Static functions
protected:
    static void wxPoint2Coord(const wxPoint& point, Coord* pcoord);
	static void Coord2wxPoint(const Coord& coord, wxPoint* ppoint);
    static void wxRect2Rect(const wxRect& rect, Rect* pkrect);
	static void Rect2wxRect(const Rect& krect, wxRect* prect);

public:
	static DocView *GetDocViewFromWindowID( CWindowID WindowID );

// Static variables
protected:
	static const INT32 WID_RENDERWINDOW = 1;
	static const INT32 WID_HSCROLLBAR = 2;
	static const INT32 WID_VSCROLLBAR = 3;
	static const INT32 WID_SIZECORNER = 4;
	static const INT32 WID_HRULER = 5;
	static const INT32 WID_VRULER = 6;
	static const INT32 WID_RULERORIGIN = 7;
	static const INT32 DragIdleID = 100;

	static INT32 PopCount;					// how many CCamViews around
	static ViewState* pReadyMadeViewState;	// points to the ViewState to use on next create

	static BOOL DefaultScrollersState;
	static BOOL DefaultRulersState;
	static BOOL UseVisibleDefaults; 

	static INT32 DragLatency;			// mouse must move >= this for a drag, except:
	static INT32 DragDelay;				// delay before we start a drag anyway, even if
										// mouse has not moved.
	static MonotonicTime DragTimer;		// Used to time the drag delay above.

	static INT32 ScrollBarSize;			// Width of the wider of the scroll bars

public:
	static INT32 s_MouseMoveEliminationPeriod;
};


/*********************************************************************************************

>	class PageDropInfo : public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/3/95
	Purpose:	Gives info about where an drag has, or is going to be, dropped on a page.

	SeeAlso:	DragInformation

*********************************************************************************************/

class PageDropInfo : public CCObject
{
	CC_DECLARE_DYNCREATE(PageDropInfo)

public:
	Document* 	pDoc;
	DocView* 	pDocView;
	Spread* 	pSpread;
	DocCoord 	DropPos;

	ObjectDragTarget 	TargetHit; 
	NodeRenderableInk* 	pObjectHit;
};


/*********************************************************************************************
>	class 	ViewDragTarget : public OilDragTarget

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>.
	Created:	2/1/95

	Purpose:	An instantiation of this class is created by each entity which wishes to 
				provide a 'destination' to which the mouse can go to complete a drag.
				WinoilDragTargets are used as a base class from which to derive drag targets
				for WINOIL entities (an optional HWND)

	Notes:		Drag targets are destructed automatically when a drag finishes by the drag
				manager with which they were registered.

				To remove a drag target at any time, destruct it - it automatically deregisters
				and cleans up.
				
	SeeAlso:	DragManagerOp::StartDrag; DragInformation; DragTarget

	Documentation:	Docs\Specs\DragMan.doc
*********************************************************************************************/

class ViewDragTarget : public OilDragTarget
{
friend class DragManagerOp;
friend class ColourDragInformation;
	
CC_DECLARE_DYNAMIC(ViewDragTarget)


public:	// Public interface
	
	ViewDragTarget( wxWindow *TheWindow, wxRect *ClientArea = NULL, DragInformation* pDragInfo = NULL);
	
	virtual UINT32 GetCursorID();
	virtual BOOL GetStatusLineText(String_256 * TheText);

	virtual BOOL GetDropInfo(PageDropInfo*);

protected:
	
	// Process a drag-related event
	BOOL ProcessEvent(DragEventType Event,
						DragInformation *pDragInfo,
						wxPoint *pMousePos, KeyPress* pKeyPress);

	DragInformation* pCurrentDragInfo;

	BOOL OverOutline;
	INT32 LineRad;

	DocView* 	pThisDoc;
	Spread* 	pSpread;
	DocCoord 	DropPos;

	ObjectDragTarget 	OverTarget;
	NodeRenderableInk* 	OverNode;
};



class CViewFileDropTarget : public wxFileDropTarget
{
public:
	CViewFileDropTarget(CCamView* pView);
	virtual ~CViewFileDropTarget();

	virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);

protected:
	CCamView* m_pView;
};


#endif	// INC_CAMVIEW_H
