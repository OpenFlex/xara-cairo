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


// dragmgr.h - Definitions for global dragging system manager

#ifndef INC_DRAGMGR
#define INC_DRAGMGR


#include "draginfo.h"
#include "dragmsg.h"

class Cursor;
enum ObjectDragTarget;

/********************************************************************************************

>	class CaptureHandler : public CWnd

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/01/95
	Purpose:	An event handler to centralise the mouse handling during a drag
	SeeAlso:	

********************************************************************************************/

class CaptureHandler : public wxEvtHandler
{
	DECLARE_DYNAMIC_CLASS(CaptureHandler)

	friend class DragManagerOp;	
	friend class DragInformation;

public:
	CaptureHandler(wxWindow* pWindow = NULL);
	~CaptureHandler();

	void OnMouseMove(wxMouseEvent& event);
	void OnLButtonUp(wxMouseEvent& event);
	void OnRButtonUp(wxMouseEvent& event);

public:
	BOOL StartCapture();

	BOOL SetUpSolidDrag(wxPoint StartPos);
	BOOL CleanUpSolidDrag();

	BOOL CleanUpSolidDragInScreenArea(const wxRect& Area);
		// Called to remove any on-scren solid drag stuff if it overlaps the given area
		// This minimises flicker when unrelated areas of the screen are redrawn while we're dragging

	BOOL DrawSolidDrag(wxPoint point);
	BOOL DrawTransparentDrag(wxPoint point, INT32 Transparency);

protected:
	wxWindow* m_pWindow;
	BOOL m_bHasCapture;
	wxScreenDC* m_pDisplayDC;

	wxBitmap* m_pBackBitmap;
	wxRect m_DragRect;	

	// Some things for semi-transparent drags
	wxBitmap* m_pMaskBitmap;

	DECLARE_EVENT_TABLE()
};                                                                                                                                                         



/*********************************************************************************************

>	class DragManagerOp : public Operation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/1/95
	Purpose:	An instantiation of this class (created by a call to its static StartDrag
				method) is used to describe a current global drag. When the drag completes,
				this object will self destruct. While alive, this object controls the drag,
				passing relevant events on to registered drag targets, etc.
				See the documentation for a fuller description of the global drag system.

	SeeAlso:	DragManagerOp::StartDrag; DragTarget; DragInformation

	Documentation:	Docs\Specs\DragMan.doc

*********************************************************************************************/

class CCAPI DragManagerOp : public Operation
{
friend class DragTarget;
friend class KernelDragTarget;
friend class OilDragTarget;
friend class CaptureHandler;
friend class DragInformation;

	CC_DECLARE_DYNCREATE(DragManagerOp)


protected:		// Protected constructors/Destructor
	DragManagerOp();					// use StartDrag to create a new DragManagerOp
	DragManagerOp(DragInformation *Descriptor);

	~DragManagerOp();					// use AbortDrag to destruct a DragManagerOp


public:			// External drag management methods
	static void StartDrag(DragInformation *Descriptor, CWindowID DragWindow);
		// To start a drag going

	static void EndDrag(INT32 Flags);
		// To end a drag - called from the capture window on mouse ups

	static void AbortDrag(void);
		// To abort the current drag (if any)

	static DragManagerOp *GetCurrentManager(void);
		// Returns NULL, or a pointer to the current drag manager
	static BOOL GetStatusText(String_256 * StatusText);

	static CaptureHandler * GetDragCaptureHandler();

	static DragInformation * GetCurrentDragInfo();

	static wxPoint GetDragMousePos();

	static BOOL IsDragActive(){return DragActive;}

	static void SetDragActive(BOOL State){DragActive = State;}

	static void RedrawStarting(void);
	static void RedrawStarting(CWindowID TheWindow, CGadgetID TheGadget, DocRect *TheArea = NULL);
	static void RedrawFinished(void);
		// Call to tell the drag manager that a redraw is occurring, during a drag.
		// This allows the drag manager to ensure all drag blobs are removed from screen during the redraw

public:			// Operation class overrides
	virtual BOOL OnIdleEvent(void);
		// Handles idle events

protected:		// Methods for use only by friend classes
	void RegisterTarget(DragTarget *NewTarget, BOOL HighPriority = FALSE);
		// Registers a target with the current drag manager

	void DeregisterTarget(DragTarget *OldTarget);
		// De-registers a registered target. Is quiet if the target is already deregistered

	static void SetCursor();
		// Sets the cursor shape. If nobody tries to set the shape during an event processing
		// pass, then it will be set back to the default. Repeated calls with the same shape
		// have no effect (except to stop the pointer reverting)
	
	static void SetStatusLineText();
		// writes status line text

private:		// Internal methods
	BOOL ProcessEvent(DragEventType Event);
		// Passes a Drag Event to all (or until event claimed) registered DragTargets

	void CleanUpAfterDrag(void);
		// Deletes all of our memory claims
  
private:		// private data
	static DragManagerOp *CurrentManager;	// ptr to the currently active Drag Manager
											 
	static DragInformation *CurrentDragInfo;// Points to descriptor of current drag

	static DragTarget * CurrentDragTarget;  // Points to the current drag target

	static UINT32 StatusLineStringID;			// ID of Current StatusLine Text string

	UINT32 CurrentID;
	Cursor* CurrentCursor;

	List 		Targets;					// List of DragTargets for this current drag

	KeyPress	*CurrentKeypress;			// NULL, or last keypress info

	wxPoint		InitialMousePos;			// Contains first winoily screen mouse position
	wxPoint		CurrentMousePos;			// Contains last winoily screen mouse position	
	wxPoint		LastMousePos;				// Last position the mouse was at

	DragEventType LastEvent;				// Type of the last Drag Event processed	

	static CaptureHandler * TheCaptureHandler;	// The event handler we use to centralised mouse handling

	static BOOL DragPending;				// Drag pending flag ie. this may be a click !		
	
	static BOOL DragEnded;

	static MonotonicTime DragStartTimer;

	static UINT32 DragMinDist;				// drag start distance

	static UINT32 DragDelay;					// millisecond delay before drag starts

	static wxRect DragStartRect;
	
	static wxRect StillClickRect;			// initial area for drag start - if pointer
											// leaves this area we start a drag.

	static BOOL DragActive;

	static BOOL RedrawInProgress;			// An external redraw is occurring
};


#endif

