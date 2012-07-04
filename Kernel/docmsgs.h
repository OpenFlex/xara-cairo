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



#ifndef INC_DOCMSGS
#define INC_DOCMSGS

#include "msg.h"

class Document;

/*********************************************************************************************
>	class DocChangingMessage : public Msg

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/4/1994
	Purpose:	This message is sent when something about a document changes. This includes:
				MonoOn
					BORN (pChangingDoc)			- When a doc has been created
					ABOUTTODIE (pChangingDoc)	- When a doc is starting to be destructed
					KILLED (pChangingDoc)		- When a doc has been destructed

					TITLECHANGED (pChangingDoc)	- When the document title text has changed

					SELCHANGED (pOldDoc,pNewDoc)- When SelectedDoc has changed
				MonoOff

	Documentation:	docs\howtouse\messages.doc

*********************************************************************************************/

	

class DocChangingMsg : public Msg
{
	CC_DECLARE_DYNAMIC(DocChangingMsg)
public:

	// Document messages are sent on these events.
	enum DocState
	{
		BORN,						// sent when a document has just been constructed
		SELCHANGED,					// New style (22/7/94) selection changing message
									// as described in the docstate.doc document,
									// pOldDoc being the one that is being unselected
									// and pNewDoc being the one selected.
									// NOTE!!!! pOldDoc and/or pNewDoc can be NULL!!!!!

		ABOUTTODIE,					// sent just before a document is destroyed
		KILLED,						// sent after a document has been destroyed

		TITLECHANGED,				// sent if the doc's title text has been changed
		BORNANDSTABLE				// sent as the last part of a document creation process
									// at present it is sent as the last part of a new
									// document or open document process. This means that
									// the document is loaded, selected, everything is set up
									// and ready, so now is the time to update details on the
									// document such as those displayed in the options dialog
	};

	Document* pChangingDoc;			// points to document being created/destroyed
									//   (BORN/ABOUTTODIE/KILLED/TITLECHANGED/BORNANDSTABLE only)

	Document* pOldDoc;				// points to document which was selected (or NULL)
	Document* pNewDoc;				// points to document which is now selected (or NULL)
									//   (SELCHANGED only)
	DocState  State;				// The message specifics, as enumerated above
									//   (All messages)


	DocChangingMsg(Document* pdoc, DocState state)
	  : pChangingDoc(pdoc), pOldDoc(NULL), pNewDoc(NULL), State(state) { /* empty */ }

	DocChangingMsg(Document* pThisOldDoc, Document* pThisNewDoc, DocState state)
	  : pChangingDoc(NULL), pOldDoc(pThisOldDoc), pNewDoc(pThisNewDoc), State(state) { /* empty */ }
};


#endif

