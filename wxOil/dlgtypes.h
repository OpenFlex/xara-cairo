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
 * */
// The following are platform independant types which are required by the 
// Dialog box system.

// They may end up in Camtypes.h
#ifndef INC_DLGTYPES
#define INC_DLGTYPES
     
class CCDC;
class CCPaintDC;
class DocRect;
class DocCoord;

class wxDialog;
typedef wxWindow *CWindowID;		// Window ID, This will never be specified directly in the kernel. 
									// Therefore its type could be changed to the specific system type
									// doing away with the need to map between platform dependant and 
									// independant window ids. 

typedef wxTreeItemId CTreeItemID;

// The rest of the dialog types must be platform independant
									
typedef UINT32 CDlgResID;            // Dialog resource ID
typedef UINT32 CGadgetID;            // GadgetID


// Device independent messages
enum CDlgMessage { 
					DIM_NONE = 0,
					DIM_LFT_BN_CLICKED,            // Left button pressed
					DIM_RGT_BN_CLICKED,            // Right button pressed
					DIM_SELECTION_CHANGED,         // List selection changed
					DIM_SELECTION_CHANGED_COMMIT,  // List selection changed commit
												   // (Double mouse click in windows)  
					DIM_SELECTION_CANCELED,        // Previous list selection cancelled
					DIM_OUT_OF_SPACE,              // List full
					
					DIM_LFT_BN_DOWN,			   // Left button pressed down
					DIM_LFT_BN_UP,			       // Left button released
					DIM_RGT_BN_DOWN,			   // Right button pressed down
					
					DIM_RGT_BN_UP,			       // Right button released
// Removed by Simon 25/11, as they make debugging a pain, they are unlikely to be needed

					
					DIM_MOUSE_MOVE,			   	   // Mouse move with button held down
					DIM_MOUSE_DRAG, 			   // Normal mouse move
					
					DIM_TEXT_CHANGED,	 		   // Text changed 

					DIM_COMMIT,					   // Commit message, sent when left button pressed on
												   // IDOK button or enter pressed
					DIM_SOFT_COMMIT,			   // Soft commit messsage sent when right button pressed
												   // on IDOK button
					DIM_CANCEL,					   // Escape pressed/left button click on CANCEL/
												   // Close dialog btn pressed

					DIM_CREATE,					   // A DIM_CREATE mesage is sent after the dialogOp's
												   // window has been created. It is required by 
												   // DialogBarOps so that they can initialise their
												   // controls.

					DIM_SLIDER_POS_CHANGING,		// Sent when a slider is being dragged
													// so that things controlled by the
													// slider can be updated interactively.
													// DlgMsgParam = current slider pos.
					DIM_SLIDER_POS_IDLE,			// REVISED CGS (9/8/2000)
													// Sent when a slider has been dragged
													// and the user has stopped moving the mouse,
													// but has still got the mouse button down.
													// this message can be used to redraw objects
													// that are too complex to be updated interactively
													// DlgMsgParam = current slider pos.
					DIM_SLIDER_POS_SET,				// Sent when a slider has just been
													// "dropped" so that things controlled
													// by the slider can be upated after it
													// has been dragged.
													// DlgMsgParam = current slider pos.

					DIM_SLIDER_POS_CANCELLED,		// Sent when a slide has just been
													// cancelled so that things controlled
													// by the slider can be updated


					DIM_GRID_BUTTON_DOWN,			// sent when the user clicks on a "telephone keypad"
													// custom control.  The numeric ID of the button
													// clicked (numbered 1 - 9) is in DlgMsgParam

					DIM_REDRAW,						// Message sent to dialog that create render regions
													// and draw into them. For a dialog to get one of these
													// messages it must have a control in it of class
													// cc_DialogDraw. Only this control will get the DIM_REDRAW
													// messages. DlgMsgParam holds a pointer to a CCDC that
													// can be used to create a render region.
					DIM_BAR_DEATH,					// similar to a cancel but this kills the op as well

					DIM_FOCUS_LOST,					// Sent when a gadget loses the input focus
													// NOTE: This may not be implemented for all gadget types
													// (search w/dlgmgr.cpp for DIM_FOCUS_LOST to check)

					DIM_SET_ACTIVE,					// Sent when a tabbed dialogue pane becomes active

					DIM_FONTCHANGE,					// Sent when Font is Installed or DeInstalled

					DIM_LISTDROPPED,				// Sent when a list box is dropped ( e.g from a combo) 

					DIM_TITLEFOCUSWARN,				// Sent when a dialogue has been moved and when a
													// titlebar "mouseactivate" occurs. Used by the colour
													// editor to bodge away the input focus when moved.

					DIM_SET_FOCUS,				   	// An ed field has just received focus
					DIM_KILL_FOCUS,				   	// An ed field has just lost focus

					DIM_TIMER,					   	// The requested timer has gone off.

					DIM_SPINCONTROLUP,				// Special spin control message
					DIM_SPINCONTROLDOWN,				// Special spin control message

					DIM_DLG_MOVED,					// the dialog has been moved
					DIM_DLG_RESIZED,				// the dialog has been resized

					DIM_COMMIT_BRUSH,                // special message sent by the brush dialog

					DIM_MOUSEWHEEL_UP,				// mousewheel scroll upwards (away from user)
					DIM_MOUSEWHEEL_DOWN,			// mousewheel scroll downwards (towards user)
					DIM_MID_BN_DOWN,				// middle button down
					DIM_MID_BN_UP,					// middle button up
					DIM_MID_BN_CLICKED,				// middle button pressed

					DIM_CTRL_RESIZED,				// A control within the dialog has been resized

							// Profile (bias-gain) - related messages.
					DIM_PROFILE_CHANGED,			// A profile-changing message, sent by the profile dialog
													// to a toolbar.
					DIM_PROFILE_CHANGING,			// The same as DIM_PROFILE_CHANGED, but sent before profile finally
													// was changed. E.g. slider sends DIM_PROFILE_CHANGING while the user moves
													// the knob and DIM_PROFILE_CHANGED when he releases it (sets the filnal position).
					DIM_PROFILE_CHANGEIDLE			// Changing the 
				};	

enum CDlgMode { MODAL, MODELESS }; 	// Mode of dialog box     

// The EditGadgetType is used to specify those characters which should be accepted by a 
// subclassed edit control. 
enum EditGadgetType { UNIT_NUMERIC,     // only unit chars
					  INT_NUMERIC,      // only 0..9 chars
					  REAL_NUMERIC };   // only 0..9 and . chars
 
// This type is used to distinguish between DIM_SELECTION_CHANGE messages sent because the user has
// pressed ENTER in a combo, and COMMIT messages sent because the user has tabbed out of a combo.
// It is contained in the DlgMsgParam field of a DialogMsg (see MSG.H).
enum SelChangeMsgSubType
{
	NO_COMMIT,
	TAB_COMMIT,				// "I have finished editing this field, but I might come back in a minute"
	ENTER_COMMIT			// "I really have finished editing this field, go ahead and do your stuff!"
};



// These structures are used to pass extra info in the DIM_REDRAW and mouse move/click
// messages. Most of this info can only really be worked out in the oil layer, so the
// individual dialog op can not really do it
// Pointers to data structures are used to reduce dependencies. The pointers are only valid
// under some circumstances - all other times they will be NULL.
struct ReDrawInfoType
{
	// This data is always available
	INT32	 dx;			// The size of the window in Millipoints
	INT32	 dy;
	INT32 	 Dpi;			// The DPI of the screen

	// This data is only available during processing of cc_DialogDraw redraws
	DocRect* pClipRect;		// The rectangle that has actually been invalidated
	CCPaintDC*	 pDC;			// The DC to plot into

	// This data is only available when processing cc_DialogDraw mouse events
	DocCoord *pMousePos;	// The position of the mouse at this event
};

enum TabType
{
	TABTYPE_TABS,
	TABTYPE_LIST,
	TABTYPE_CHOICE,
	TABTYPE_TREE,
	TABTYPE_TOOLBAR
};

#endif          
                                         
