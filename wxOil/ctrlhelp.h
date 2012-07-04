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


// Code to modify the behaviour of controls on Camelot bars so that they respond
// to help messages and can be dragged about etc.

#ifndef INC_CTRLHELP
#define INC_CTRLHELP

//#include "monotime.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class OpDescriptor;
class ControlTable;
class BarTable;
class BubbleHelpWnd;   

#define COMMIT 2

/********************************************************************************************

>	class ControlHelpInfo

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/05/94
	Purpose:	Used to specify details of a control that is to be added to the list of
				sub-classed controls. The fields are:
				MonoOn
				pOpDesc - pointer to the OpDescriptor for this control.
						  If this field is non-NULL, then all the ID fields are ignored.
						  Id this field is NULL, then the ID fields are used to define the
						  bubble help text and status bar text to be displayed for this
						  control.
				BubbleID - ID of the string resource to be used for bubble help.
				StatusID - ID of the string resource to be used for status bar text.
				ModuleID - defines where to find the above resources.
				Parent - internal use; any value you put in here will be ignored.
				MonoOff
	SeeAlso:	ControlHelper::NotifyControlCreated

********************************************************************************************/

class ControlHelpInfo
{
public:
	OpDescriptor* pOpDesc;
	UINT32 BubbleID;
	UINT32 StatusID;
	UINT32 ModuleID;
	wxWindow* Parent;
};

/********************************************************************************************

< BubbleHelpCallback

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Comment:	This is a function that is called by the bubble help system when providing
				'ad-hoc' bubble help on a window, i.e. not on 'real' controls, but on
				GUI elements which may be just rendered, e.g. the colour bar uses this
				facility.
				You pass a function of this type into ControlHelper::DoBubbleHelpOn(), and
				this function is called back when the bubble help needs to be displayed.
				You should return a pointer to the bubble help text to display.

				MonoOn
				typedef TCHAR *(*BubbleHelpCallback)(wxWindow*, UINT32, void*);
				MonoOff

				The parameters provide context information for the callback as there is
				usually a delay between calling DoBubbleHelpOn(), and the callback being
				called (because there is a short time delay before bubble help appears).

	Inputs:		wxWindow* - the handle of the window that bubble help is being provided on.
				UINT32 - the 'psuedo-ID' you passed in to DoBubbleHelpOn() which indicates
					   which GUI element in the window that bubble help is being provided
					   for.  This number is determined by you - it means nothing to the
					   bubble help system, apart from when it does an equality check to
					   see if the user has moved onto another GUI element in your window.
				void* - an arbitrary piece of data associated with you system which may
						provide more assistance in working out the context of the call.
						This data is the data you pass in to DoBubbleHelpOn.

	SeeAlso:	ControlHelper::DoBubbleHelpOn

********************************************************************************************/


/********************************************************************************************

>	class ControlHelper : public SimpleCCObject

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/07/94
	Purpose:	Provide a system for subclassing controls on Camelot bars which offers
				various facilities such as bubble help/status bar text and commit handling.
				To use this system you use the Notifyxxx() functions to keep the class up
				to date with which bars/controls exist.  This module will subclass these
				controls and do some preprocessing of Windows messages in order to do
				bubble help/commit handling etc.
				You can 'fake' bubble help on a window that doesn't really have controls
				in it, by using the 'ad-hoc' bubble help function, DoBubbleHelpOn().
	SeeAlso:	ControlHelpInfo;
				ControlHelper::NotifyBarCreated; ControlHelper::NotifyBarDeleted;
				ControlHelper::NotifyBarChanged;
				ControlHelper::NotifyControlCreated; ControlHelper::NotifyControlDeleted
				ControlHelper::DoBubbleHelpOn

********************************************************************************************/

class ControlHelper : public SimpleCCObject
{
public:
	// Interface for use by the routines that manage bars + child controls.
	static BOOL Init();
	static void DeInit();

	static BOOL NotifyBarCreated(wxWindow*);
	static BOOL NotifyBarDeleted(wxWindow*);
	static BOOL NotifyBarChanged(wxWindow* Old, wxWindow* New);
	static BOOL NotifyControlCreated(wxWindow*, ControlHelpInfo*);
	static BOOL NotifyControlCreated(wxWindow*, OpDescriptor*);
	static BOOL NotifyControlDeleted(wxWindow*);

	// Allow the control Bubble help to be changed on the fly
	static BOOL NotifyControlChanged(wxWindow*, ControlHelpInfo*);

	typedef TCHAR *(*BubbleHelpCallback)(wxWindow*, UINT32, void*);

	static void DoBubbleHelpOn(wxWindow*, UINT32, BubbleHelpCallback, void*);

	static void ServiceBubbleHelp();
	static void BubbleHelpDisable();

	static void InformModalDialogOpened();
	static void InformModalDialogClosed();
	static BOOL GetStatusLineText(String_256* ptext, wxWindow* window);

	static BOOL IsUserInterfaceCaptured();

private:
	static void	BubbleHelpKill();

	static BOOL AddControl(wxWindow*, ControlHelpInfo *);
	static ControlTable  *Controls;
	static BarTable      *Bars;
	static BubbleHelpWnd *BubbleWnd;

	static LRESULT CALLBACK MyWndProc(wxWindow*, UINT32, WPARAM, LPARAM);
	static MonotonicTime PendingTimer;
	static POINT LastPos;
	static wxWindow* LastControl;
	static BOOL ControlHasFocus;

	static wxWindow* AdHocWindow;
	static UINT32 AdHocControl;
	static BOOL AdHocControlIsDifferent;
	static void *AdHocReference;
	static BubbleHelpCallback AdHocCallback;

	typedef enum
	{

		STATE_DEAD,				// No bubble help is displayed - cursor is not over a
								// a bar or a control.

		STATE_ACTIVE,			// Bubble help is displayed - cursor is over a control.

		STATE_INITIAL_PENDING,	// Waiting to show bubble help for the first time - the 
								// cursor is over a control.

		STATE_UPDATE_PENDING,	// Waiting to display help for a different control - i.e.
								// the user has moved from one control to another,
								// possible via a bar (STATE_DISABLED).

		STATE_INITIAL_DISABLED,	// Pointer is over bar, but no help has yet been displayed 
								// during this session.

		STATE_DISABLED			// Pointer over bar, and bubble help has been displayed
								// during this session.

	} BubbleState;

	static BubbleState BubbleHelpState;

	// Number of modal dialogs open (that are NOT managed by the kernel dialog manager)
	static INT32 ModalDialogs;

	// State control functions
PORTNOTE( "dialog", "Remove function that needs WNDPROC" )
#if 0
	static void BubbleHelpStateMachine(POINT Pos, wxWindow* ThisControl, WNDPROC WndProc);
#endif
	static void SetState(BubbleState NewState, wxWindow* Window = NULL);
	static void DeadHandler();
	static void ActiveHandler(wxWindow* Window);
	static void InitialPendingHandler();
	static void InitialDisabledHandler();
	static void UpdatePendingHandler();
	static void DisabledHandler();
};



/********************************************************************************************

>	class ControlEntry

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/04/94
	Purpose:	Contains the information for a particular control.
				The data members are:
				MonoOn
				wxWindow* Window - the handle of the control.
				OpDescriptor *pOpDesc - pointer to the OpDescriptor associated with this
										control.
				WNDPROC WndProc - pointer to the normal WndProc for the subclassed control.
				MonoOff
	SeeAlso:	ControlTable; ControlHelper

********************************************************************************************/

class ControlEntry
{
public:
	wxWindow* Window;			// Handle of the control being sublassed (may be a subwindow of
							// a control).
	wxWindow* Parent;			// Not necessarily the immediate parent - just the handle of the
							// parent control, or none if this *is* the parent control.
	OpDescriptor *pOpDesc;	// The OpDescriptor for this control, or NULL if there isn't one.
	UINT32 BubbleID;			// String resource ID for bubble help.
	UINT32 StatusID;			// String resource ID for status bar text.
	UINT32 ModuleID;			// Module ID to be used when loading bubble help/status 
							// bar string resources.
PORTNOTE( "dialog", "Remove WNDPROC usage" )
#if 0
	WNDPROC WndProc;		// Normal WndProc for this control.
#endif

	BOOL AddCommitHandling; // This flag is set to TRUE if the control is an edit or a combo 
							// it is used in the subclass procedure to determine if we
							// should respond to Enter and Tab keys being pressed
							// - Added by Simon (08/06/94)
	BOOL ControlStatusLineText(String_256* text);
};


/********************************************************************************************

>	class ControlTable : public SimpleCCObject

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/04/94
	Purpose:	Stores/manipulates an array of ControlEntry objects, in order to keep
				track of all the controls we have currently subclassed.
	SeeAlso:	ControlEntry; ControlHelper

********************************************************************************************/

class ControlTable : public SimpleCCObject
{
public:
	ControlTable();
	~ControlTable();
	BOOL Init();

PORTNOTE( "dialog", "Remove function that needs WNDPROC" )
#if 0
	BOOL AddControl(wxWindow*, ControlHelpInfo*, WNDPROC);
	WNDPROC DeleteControl(wxWindow* Window, wxWindow* *RealWindow);
#endif
	ControlEntry *FindControl(wxWindow* Window);
	BOOL ChangeControl(wxWindow*, ControlHelpInfo*);

private:
	INT32 FindControlIndex(wxWindow* Window, BOOL IgnoreChildren = TRUE);

	enum
	{
		NotFound = -1,
		EmptySlot = 0,
		Granularity = 30,
		InitialSize = 100
	};

	ControlEntry *Table;
	INT32 TableSize;

	// State information - used when scanning the table for controls.
	wxWindow* LastWindow;
	INT32  LastIndex;
};

#endif

