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

// Header for the handling code for the Tuneup tab of the options dialog box 

//WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER

#ifndef INC_OPTSTUNE
#define INC_OPTSTUNE

//#include "unittype.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "units.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "appprefs.h"

/********************************************************************************************

>	class TuneTab: public OptionsTabs

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>/Neville Humphrys
	Created:	19/1/95
	Purpose:	Allows the user to set various tuning parameters, such as:-
	            - Gdraw memory for rendering
				- Undo buffer size for the current document
	SeeAlso:	OptionsTabs; AppPrefsDlg;

********************************************************************************************/

class TuneTab: public OptionsTabs
{         
	CC_DECLARE_DYNCREATE( TuneTab )  
public:

	TuneTab();
	~TuneTab();

	virtual BOOL Init();                        

	// Function to handle the messages for this tab/pane window
	virtual BOOL HandleMsg(DialogMsg* Msg);

	// Function to set up the values on this tab when being opened
	virtual BOOL InitSection();

	// Function to commit the values on this tab on ok
	virtual BOOL CommitSection();

	// Functions to handle document changing messages
	virtual BOOL GreySection();			// Called when the user has closed all documents
	virtual BOOL UngreySection();		// Called when the user has opened a document
	BOOL ChangeControlStatus(const BOOL Status); // used to grey/ungrey all controls
	virtual BOOL UpdateSection(String_256 *DocumentName);	// Called when the user has switched to a new document

	virtual CDlgResID GetPageID();		// Return section/page id system

	virtual BOOL IsDocumentOption();	// Return True if document option  

	virtual BOOL IsProgramOption();		// Return True if program option

protected:
	// Lots of controlling and handling functions specific to this section
	BOOL InitRenderingSection();
	BOOL InitUndoSection();

	BOOL CommitRenderingSection();
	BOOL CommitUndoSection();

private:
	UINT32 CurrentTempMemValue;

	BOOL GreyStatus;			// Remember the state that we are currently in

	// Variables to store the old control states.
	UINT32 OldMaxUndoSize;
}; 

#endif // INC_OPTSTUNE

#endif //webster
