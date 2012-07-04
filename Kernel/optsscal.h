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

//
// Header for the handling code for the Scale tab of the options dialog box 

//WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER

#ifndef INC_OPTSSCALE
#define INC_OPTSSCALE

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "appprefs.h"

/********************************************************************************************

>	class ScaleTab: public OptionsTabs

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/1/95
	Purpose:	Allows the user to set any options which are normally associated
				with a documents scaling.

	SeeAlso:	OptionsTabs; AppPrefsDlg; DocPrefsDlg;

********************************************************************************************/

class ScaleTab: public OptionsTabs
{         
	CC_DECLARE_DYNCREATE( ScaleTab )  
public:

	ScaleTab();
	~ScaleTab();

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
	DimScale*	pDimScale;

	BOOL ShowScaleDetails();

private:
	BOOL GreyStatus;			// Remember the state that we are currently in

	// Variables to store the old control states.
	String_256 OldDrawingStr;	// remember entry state of drawing scale string
	String_256 OldRealStr;		// remember entry state of real scale string
	BOOL OldActiveState;		// remember entry state of scaling active button

}; 

#endif // INC_OPTSSCALE

#endif //webster
