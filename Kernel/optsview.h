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

// Header for the handling code for the View tab of the options dialog box 

//WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER

#ifndef INC_OPTSVIEW
#define INC_OPTSVIEW

//#include "unittype.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "units.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "appprefs.h"

/********************************************************************************************

>	class ViewTab: public OptionsTabs

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/12/94
	Purpose:	Allows the user to set any options which are normally associated
				with the applications View. This includes such things as:-
					Colour bar display mode
					Showing percentage hourglasses and/or progress bars

	SeeAlso:	OptionsTabs; AppPrefsDlg; DocPrefsDlg;

********************************************************************************************/

class ViewTab: public OptionsTabs
{         
	CC_DECLARE_DYNCREATE( ViewTab )  
public:

	ViewTab();
	~ViewTab();

	virtual BOOL Init();                        

	// Function to handle the messages for this tab/pane window
	virtual BOOL HandleMsg(DialogMsg* Msg);

	// Function to set up the values on this tab when being opened
	virtual BOOL InitSection();

	// Function to commit the values on this tab on ok
	virtual BOOL CommitSection();
	BOOL CommitBitmapSmoothingFlag( BOOL bNewSetting );


	// Functions to handle document changing messages
	virtual BOOL GreySection();			// Called when the user has closed all documents
	virtual BOOL UngreySection();		// Called when the user has opened a document
	BOOL ChangeControlStatus(const BOOL Status); // used to grey/ungrey all controls
	virtual BOOL UpdateSection(String_256 *DocumentName);	// Called when the user has switched to a new document

//	removed 27/8/96 - transparency control DEAD 
//	Special function for the view tab to get it to update the transparency switch
//	BOOL UpdateTransparencyState(const BOOL NewState);

	virtual CDlgResID GetPageID();		// Return section/page id system

	virtual BOOL IsDocumentOption();	// Return True if document option  

	virtual BOOL IsProgramOption();		// Return True if program option

protected:
	// Lots of controlling and handling functions specific to this section
	BOOL GetDisplayStyleForView();		// read attributes associated with current view

	// Function to decode the selected item in automatic colour model list
	BOOL DecodeModelListItem(BOOL *AutoColourModel, ColourModel *DisplayModel);
	// Set up the automatic colour model list, passingin the required display model
	// and returning the index into the display list 
	BOOL InitAutoColourModelList(ColourModel DisplayModel, INT32 *SelectedIndex);

	// Function to get the 'Screen dither' radio button settings
	INT32 GetSelectedDither(void);

	// Function to set the 'Screen dither' radio buttons
	BOOL SetSelectedDither(INT32 DitherStyle);

private:
	BOOL GreyStatus;			// Remember the state that we are currently in

	// Variables to store the old control states.
	BOOL OldShowTransparency;	
 	BOOL OldBackgroundRedraw; 
	BOOL OldPropScroll;
	BOOL OldViewDither;
}; 

#endif // INC_OPTSVIEW

#endif //webster
