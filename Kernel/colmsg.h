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

// Definition of Colour messages

#ifndef INC_COLMSG
#define INC_COLMSG

class Document; 
class ColourList;
class IndexedColour;



/*********************************************************************************************

>	class ColourChangingMessage : public Msg

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/5/94
	Purpose:	This message is sent whenever certain events of importance happen in the
				colour system. Most of these events relate to IndexedColour lists, or
				individual IndexedColours.
				See Develop:Camelot\Docs\howtouse\message.doc for details.

	SeeAlso:	ColourManager

*********************************************************************************************/

class ColourChangingMsg : public Msg
{
	CC_DECLARE_DYNAMIC(ColourChangingMsg)

public:
	// list messages are sent on these events.
	enum ColourState
	{
		LISTPAGED,		  				// Sent when a different list is paged in
		LISTUPDATED,	  				// Sent when the existing list is edited
		COLOURUPDATED,					// Sent when a colour has changed (visibly - see below)
		COLOURUPDATEDINVISIBLE,			// Sent when a colour has changed (invisibly - see below)
		LISTDESELECTED,		   			// Sent when there is now no selected list
		LISTDELETED,					// Sent when a list has been deleted

		NEWLISTBORN,					// Sent when a new list is created, so that
										// others can add sort modes to it.

		SELVIEWCONTEXTCHANGE			// Sent when the colour context attached to the
										// selected view changes (so the col editor, gallery,
										// line can redraw using new colour correction info)
	};
	
	Document *ScopeDoc;					// Points to the document in which the change occurred
	ColourList *NewColourList;  		// NULL, or points to the new/affected ColourList
	IndexedColour *ChangedColour;		// NULL, or pointer to the colour which has changed
	ColourState State;					// The state, as defined above

										// Constructor
	ColourChangingMsg(Document *pScopeDocument, ColourList *pChangedList,
						IndexedColour *pChangedColour, ColourState NewState)
		: ScopeDoc(pScopeDocument), NewColourList(pChangedList), ChangedColour(pChangedColour), State(NewState)
			{ /* empty */ }
};



// **** SPECIAL NOTE ****
// COLOURUPDATED and COLOURUPDATEDINVISIBLE are used in the following fashion:
// If the definition of the colour chnages such that the actual dispalyed colour will change,
// thus necessitating a redraw of the document, a COLOURUPDATED should be sent.
// If part of the definition changes which will not need a redraw of coloured regions (e.g
// the name, type, etc), then a COLOURUPDATEDINVISIBLE is sent. The latter is only used
// by those entities which need to update on all colour changes (they sit on both messages)
// while things like document redraws only occur if the visible colour has chnaged.
// See ColourManager::ColourHasChanged and ColourHasChangedInvisible

#endif
