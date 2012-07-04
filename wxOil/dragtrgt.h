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


// dragtrgt.h - Definitions for global dragging system DragTarget class

#ifndef INC_DRAGTRGT
#define INC_DRAGTRGT

#include "dlgtypes.h"		// Sorry! ;-)
#include "ops.h"			// For base class

class DialogOp;
class DragManagerOp;
class DragInformation;
class KeyPress;
class OilCoord;

enum ObjectDragTarget
{
	NO_TARGET,
	FILL_TARGET,
	LINE_TARGET,
	STARTCOL_TARGET,
	ENDCOL_TARGET,
	ENDCOL2_TARGET,
	ENDCOL3_TARGET,
	MANY_TARGET
};


/*********************************************************************************************

<	DragEventType

	Comment:		This enumerated type specifies all the drag event types that can be
					passed to a DragTarget during a global drag operation.
					The possible events are (prefix with 'DRAGEVENT_'):
					MonoOn
						INITIALISE		Given to all Targets once all targets have been
										registered with the drag manager
						DEINITIALISE	Given to all Targets immediately prior to the drag
										manager closing down

						ABORT			Sent when the drag is aborted
						COMPLETED		Sent when the drag is successfully completed
						MOUSEMOVED		Sent whenever the mouse pointer moves
						MOUSESTOPPED	Sent whenever the mouse pointer stops moving
						MOUSEIDLE		Sent whenever the mouse pointer stays stationary
						KEYPRESS		Sent whenever a key is pressed
					MonoOff

	Notes:			INITIALISE, ABORT, COMPLETED, MOUSEMOVED should never be claimed
					by any DragTarget, so that all DragTargets know about the event.

	Documentation:	Docs\Specs\DragMan.doc

	SeeAlso:		DragManagerOp; DragTarget;
					DragManagerOp::ProcessEvent; DragTarget::ProcessEvent

*********************************************************************************************/

typedef enum
{
	DRAGEVENT_INITIALISE,
	DRAGEVENT_ABORT,
	DRAGEVENT_COMPLETED,
	DRAGEVENT_MOUSEMOVED,
	DRAGEVENT_MOUSESTOPPED,
	DRAGEVENT_MOUSEIDLE,
	DRAGEVENT_KEYPRESS,
	DRAGEVENT_DEINITIALISE
}	DragEventType;




/*********************************************************************************************

>	class DragTarget : public ListItem

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/1/95
	Purpose:	An instantiation of this class is created by each entity which wishes to 
				provide a 'destination' to which the mouse can go to complete a drag.

	Notes:		IMPORTANT! The DragTarget class is the abstract base from which
				KernelDragTarget and OilDragTarget are derived. You should derive your
				class from one of these classes, NOT from DragTarget itself.

				This class would be properly abstract (pure virtual methods) execept that
				IMPLEMENT_DYNAMIC screws that all up for us.

	SeeAlso:	DragManagerOp::StartDrag; DragInformation

	Documentation:	Docs\Specs\DragMan.doc

*********************************************************************************************/

class CCAPI DragTarget : public ListItem
{
friend class DragManagerOp;					// Only DragManagerOp can call event handlers

	CC_DECLARE_DYNAMIC(DragTarget)


protected:		// Default constructor/destructor
	DragTarget();		// Nobody should use the default constructor!
	~DragTarget();		// Only DragTargets & DragManagers can delete us


public:			// Interface
		// Determine if DragTarget is kernel/winoil entity
	virtual BOOL IsAKernelObject(void);

protected:
		// Kernelly event processing (See KernelDragTarget)
	virtual BOOL ProcessEvent(DragEventType Event,
								DragInformation *pDragInfo,
								OilCoord *pMousePos, KeyPress* pKeyPress);

		// Winoily event processing (See OilDragTarget)
	virtual BOOL ProcessEvent(DragEventType Event,
								DragInformation *pDragInfo,
								wxPoint *pMousePos, KeyPress* pKeyPress);

	virtual void GetTargetAreaInfo(DialogOp **ReturnedDialog, CGadgetID *ReturnedGadget);

	virtual void GetTargetAreaInfo(wxWindow **ReturnedHWnd, wxRect *ReturnedTargetRect);

	virtual UINT32 GetCursorID();

	virtual BOOL GetStatusLineText(String_256 * TheText);


public:
	inline BOOL WantsAllEvents(void);


protected:
	BOOL IWantAllEvents;			// True if this target wants events even if the pointer
									// is outside the designated target area
};



/*********************************************************************************************

>	inline BOOL DragTarget::WantsAllEvents(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/3/95

		

	Purpose:	To determine if a given dragtarget wants events to be passed to it if the
				mouse pointer is outside the target area - This is only necessary for
				targets which supply a target window area. It is also not necessary for
				some events (e.g. INITIALISE, DEINITIALISE) which are always delivered,
				regardless of the pointer position.

	Notes:		Targets which wish to recieve these events (e.g. scroll drags in galleries
				like to continue scrolling even if the pointer moves out of the window - 
				the drag is used to "capture" the mouse) should set their member variable
				"IWantAllEvents" in their constructors.

				If an event is claimed by another target, it will NOT be passed on to
				other targets, even if this method returns TRUE.

*********************************************************************************************/

BOOL DragTarget::WantsAllEvents(void)
{
	return(IWantAllEvents);
}






/*********************************************************************************************

>	class KernelDragTarget public DragTarget

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/1/95

	Purpose:	An instantiation of this class is created by each entity which wishes to 
				provide a 'destination' to which the mouse can go to complete a drag.
				KernelDragTargets are used as a base class from which to derive drag targets
				for KERNEL entities (usually a DialogOp and optional Gadget ID)

	Notes:		Drag targets are destructed automatically when a drag finishes by the drag
				manager with which they were registered.

				To remove a drag target at any time, destruct it - it automatically deregisters
				and cleans up.
				
	SeeAlso:	DragManagerOp::StartDrag; DragInformation; DragTarget

	Documentation:	Docs\Specs\DragMan.doc

*********************************************************************************************/

class CCAPI KernelDragTarget : public DragTarget
{
friend class DragManagerOp;					// Only DragManagerOp can call event handlers

	CC_DECLARE_DYNAMIC(KernelDragTarget)


public:			// Construction/destruction
	KernelDragTarget(DialogOp *TheDialog, CGadgetID TheGadget = NULL);


public:			// Public interface
		// Returns TRUE (this is a kernel object) - DO NOT OVERRIDE (derive from WinoilDT instead)
	virtual BOOL IsAKernelObject(void);


protected:
		// Process a drag-related event
	virtual BOOL ProcessEvent(DragEventType Event,
								DragInformation *pDragInfo,
								OilCoord *pMousePos, KeyPress* pKeyPress);

		// Get the target area (dialogue) information for this target
	virtual void GetTargetAreaInfo(DialogOp **ReturnedDialog, CGadgetID *ReturnedGadget);


protected:		// Internal data
	DialogOp	*TargetDialog;
	CGadgetID	TargetGadget;
};




/*********************************************************************************************

>	class CCAPI OilDragTarget : public DragTarget

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/1/95

	Purpose:	An instantiation of this class is created by each entity which wishes to 
				provide a 'destination' to which the mouse can go to complete a drag.
				OilDragTargets are used as a base class from which to derive drag targets
				for WINOIL entities (an optional HWND)

	Notes:		Drag targets are destructed automatically when a drag finishes by the drag
				manager with which they were registered.

				To remove a drag target at any time, destruct it - it automatically deregisters
				and cleans up.
				
	SeeAlso:	DragManagerOp::StartDrag; DragInformation; DragTarget

	Documentation:	Docs\Specs\DragMan.doc

*********************************************************************************************/

class CCAPI OilDragTarget : public DragTarget
{
friend class DragManagerOp;					// Only DragManagerOp can call event handlers

	CC_DECLARE_DYNAMIC(OilDragTarget)


public:			// Construction/destruction
	OilDragTarget(wxWindow *TheWindow, wxRect *ClientArea = NULL);
		

public:			// Public interface
		// Returns TRUE (this is a kernel object) - DO NOT OVERRIDE (derive from WinoilDT instead)
	virtual BOOL IsAKernelObject(void);


protected:
		// Process a drag-related event
	virtual BOOL ProcessEvent(DragEventType Event,
								DragInformation *pDragInfo,
								wxPoint *pMousePos, KeyPress* pKeyPress);

		// Get the target area (window) information for this target
	virtual void GetTargetAreaInfo(wxWindow **ReturnedHWnd, wxRect *ReturnedTargetRect);


protected:		// Internal data
	wxWindow*	TargetHWnd;
	wxRect		TargetClientArea;
};


#endif

