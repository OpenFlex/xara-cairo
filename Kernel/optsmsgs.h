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


// docmsgs.h - The DocChangingMsg class
// See document.cpp for what little implementation exists (CC_IMPLEMENT_DYNAMIC)

/*
$Log
*/

// Definition of Options changing messages

#ifndef INC_OPTSMSGS
#define INC_OPTSMSGS

//#include "msg.h"


/*********************************************************************************************
>	class OptionsChangingMessage : public Msg

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/1/1995
	Purpose:	This message is sent when a user has changed the options on a document or
				a global application based option. At present the messages include:-

				NEWUNITS messages are broadcast when the user has specified new display, page
				or font units are to be used.

				An OptionsChangingMsg contains a pointer to the appropriate Document
				object (pScopeDoc), and a state indicating the option that is being changed.
				Both members are public.
	
	SeeAlso:	OptionsTabs; UnitsTab; AppPrefsDlg; DocPrefsDlg;

*********************************************************************************************/

	

class OptionsChangingMsg : public Msg
{
	CC_DECLARE_DYNAMIC(OptionsChangingMsg)
public:

	// Options changing messages are sent on these events.
	enum OptionsState
	{
		NEWUNITS,					// Sent when a new set of default units has been specified
									// This will include page, display and font default units.
		NEWCOLOURBARMODE,			// Sent when a new colour bar display mode has been set

		ASKBEFORESETTINGATTR,		// Sent when the ask before setting attribute mode has been
									// changed.

		IMPORTWITHLAYERS,			// Sent when the import with layers mode has been changed
		
		AUTOMATICTRANSPARENCY,		// Sent when the automatic transparency mode has been changed

		NEWDEFAULTGRID,				// Sent when there has been a change in the default grid

		NEWPAGESIZE,				// Sent when there has been a change in the page size (undo/redo)
									// This is sent by the redo/undo actions and forces an update of
									// the page tab.
		PAGESIZEHASCHANGED,			// Sent when there has been a change in the page size (do)
									// This is sent by the page tab itself when the do happens and
									// does not force an update of the page tab.

		SEPARATIONSENABLED			// Sent when colour seps are enabled/disabled, so that the
									// related imagesetting tabs can update themselves
	};

	Document *pScopeDoc;			// Points to the document in which the change occurred
	OptionsState  State;			// The message specifics, as enumerated above

	OptionsChangingMsg(Document* pScopeDocument, OptionsState NewState)
	  : pScopeDoc(pScopeDocument), State(NewState)
	  	{ /* empty */ }

	OptionsChangingMsg(OptionsState NewState)
	  : pScopeDoc(NULL), State(NewState)
	  	{ /* empty */ }
};

#endif // INC_OPTSMSGS

