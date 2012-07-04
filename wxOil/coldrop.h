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


// coldrop.h - The Colour Drop-down list support class

#ifndef INC_COLDROP
#define INC_COLDROP

#include "dropdown.h"
#include "gbrush.h"
//#include "pump.h" - in camtypes.h [AUTOMATICALLY REMOVED]


class IndexedColour;
class DocColour;
class ColourDropMsgHandler;		// Defined below


/********************************************************************************************

>	class ColourDropDown : public DropDown

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	?/10/95
	Purpose:	Colour drop down class - provides a dropdown list of named colours with
				colour patch and name, for use in the colour editor etc.

********************************************************************************************/

class ColourDropDown : public DropDown
{
friend class DialogManager;

CC_DECLARE_DYNCREATE(ColourDropDown)

// --- Kernelly section

public:			// ColourDropDown management
	ColourDropDown(BOOL AutoUpdateOnColourListChange = TRUE);
	virtual ~ColourDropDown();

	virtual BOOL Init(CWindowID Window, CGadgetID Gadget);

	void ClearAllSpecialEntries(void);
				// Ensures that all special entries are wiped

	BOOL AddSpecialEntry(StringBase *Text, DocColour *Colour = NULL);
				// Adds a special entry to the top of the list. Call before FillInColourList

	BOOL UpdateSpecialEntry(StringBase *Text, DocColour *NewColour);
				// Changes the colour splodge shown in a special entry to a different colour

	BOOL FillInColourList(IndexedColour *Selected = NULL, INT32 SelectIndex = -1,
							IndexedColour *NotDescendantOf = NULL);
				// Fills in the combobox list of available colour styles, and selects either
				// the Selected colour or the special entry indicated by SelectIndex

	BOOL SetSelection(IndexedColour *Selected, INT32 SelectIndex = -1);
				// Sets the selected item in the list

	IndexedColour *DecodeSelection(INT32 SelectionIndex);
				// Decodes a selection in the list, returning the IndexedColour it references,
				// or NULL if SelectionIndex is a special entry index.

	static void UpdateForNewColourList(void);
				// Updates the list as appropriate for a new colour list, shading if there
				// is now no Selected Document to get a colour list from.
				// Called at appropriate times by the MessageHandler

	static void RedrawColourDropDowns(void);
				// Redraws all active dropdowns - usually to take into account changes
				// in colour separation/correction settings for the selected DocView.
				// Called from the message handler as appropriate.

protected:
	List SpecialEntries;							// A list of any attached special entries

	BOOL AutoUpdateOnChange;						// TRUE if we should automatically update
													// the list when the current list changes

protected:
	static ColourDropMsgHandler *MessageHandler;	// One msg handler for all coldropdowns
	static INT32 MsgHandlerCount;					// Count of how many people using the MsgHandler	


// --- Winoily section

protected:		// Methods that must be overridden by derived classes
	virtual BOOL HasIcon(void * ItemData);
				// Returns TRUE if the item has an icon. Default is no icon

	virtual BOOL DrawIcon(void * ItemData, wxDC& dc, wxRect& IconRect, BOOL Disabled, INT32 flags);
				// Handles redraw of the icon, if any. Default is nothing gets drawn

	virtual wxString GetText(void * ItemData, INT32 Item);
				// Gets the text

protected:
	GBrush GDrawBrush;								// A GBrush of our very own
};





/********************************************************************************************

>	class ColourDropMsgHandler : public MessageHandler

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/95
	Purpose:	Intercepts messages for the Colour Drop Downs to allow them to stay
				up to date when documents change etc.

********************************************************************************************/

class ColourDropMsgHandler : public MessageHandler
{
friend class ColourDropDown;
public:
	CC_DECLARE_DYNAMIC( ColourDropMsgHandler ) 
	ColourDropMsgHandler();					// Constructor

protected:
	MsgResult Message(Msg* Msg);			// Overridden message reciever
};


#endif

