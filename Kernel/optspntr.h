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

// Header for the handling code for the Edit tab of the options dialog box 

// WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER

#ifndef INC_OPTSPOINTERS
#define INC_OPTSPOINTERS

#include "appprefs.h"

/********************************************************************************************

>	class PointersTab: public OptionsTabs

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/12/94
	Purpose:	Allows the user to set any options which are normally associated
				with Pointers. This includes such things as:-
					 Magnetic snap radii
					 Actions for the different mouse buttons
	SeeAlso:	OptionsTabs; AppPrefsDlg; DocPrefsDlg;

********************************************************************************************/

class PointersTab: public OptionsTabs
{         
	CC_DECLARE_DYNCREATE( PointersTab )  
public:

	PointersTab();
	~PointersTab();

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

	// Function called when new default units come into operation.
	virtual BOOL NewUnitsInSection();

	virtual CDlgResID GetPageID();		// Return section/page id system

	virtual BOOL IsDocumentOption();	// Return True if document option  

	virtual BOOL IsProgramOption();		// Return True if program option

protected:
	// Lots of controlling and handling functions specific to this section
	BOOL InitClickLists();				// Initialise the click modifier lists
	BOOL InitMagneticRadii();			// Initialise the magnetic radii bits

private:
	BOOL GreyStatus;			// Remember the state that we are currently in

}; 

#endif // INC_OPTSPOINTERS

#endif //webster
