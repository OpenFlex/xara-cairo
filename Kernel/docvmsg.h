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


// Definition of DocView messages

/*
 * */

// Definition of Colour messages

#ifndef INC_DOCVMSG
#define INC_DOCVMSG

class DocView;

/*********************************************************************************************

>	class DocViewMsg : public Msg

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/5/1994
	Purpose:	This message is sent when a DocView is about to be destroyed or has just
				been created/loaded.  It contains a pointer to the appropriate view
				object (pDocView), and a state indicating if the view is being
				destroyed or is being created etc. (State).  Both members are public.
				See the file DOCVIEW.H for more information.

*********************************************************************************************/



class DocViewMsg : public Msg
{
	CC_DECLARE_DYNAMIC(DocViewMsg)
public:

	// Document messages are sent on these events.
	enum DocViewState
	{
		BORN,			// sent when a view is first constructed
		NEWANDSTABLE,	// sent out when a new docview is stable
		SCALECHANGED,	// DocView scale factor changed
		SELCHANGED,		// New style (22/7/94) selection changing message
						// as described in the docstate.doc document
						// Combines the SELECTED and UNSELECTED messages into one
						// message, with pOldDocView being the one that is being unselected
						// and pNewDocView being the one selected.
						// NOTE!!!! pOldDocView and/or pNewDocView can be NULL!!!!!
		KILLED,			// sent when a view is destroyed
		SELABOUTTOCHANGE	// This message is broadcast around just before the selected document
							// is changed (ie, it will be closly followed by a SELCHANGED message.
							// When this message is sent, nothing has actually been changed yet.
	};

	DocView* 		pDocView;			// points to view the message is about

	DocView* 		pOldDocView;
	DocView* 		pNewDocView;

	DocViewState  	State;				// TRUE if message refers to a newly created doc

	DocViewMsg(DocView* pview, DocViewState state)
	  : pDocView(pview), pOldDocView(0), pNewDocView(0), State(state) { /* empty */ };

	DocViewMsg(DocView* pThisOldDocView, DocView* pThisNewDocView, DocViewState state)
	  : pDocView(0), pOldDocView(pThisOldDocView), pNewDocView(pThisNewDocView), State(state)  { /* empty */ }
};

#endif
