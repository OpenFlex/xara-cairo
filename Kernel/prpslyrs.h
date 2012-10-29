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

// WEBSTER - markn 15/1/97
// Don't need this tab in Webster
//#ifdef WEBSTER
//#define INC_PROPERTIESLAYERS
//#endif

#ifndef INC_PROPERTIESLAYERS
#define INC_PROPERTIESLAYERS

#include "property.h"
#include "layerprp.h"

/********************************************************************************************

>	class LayerPropertiesTab: public LayerPropertyTabs

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/09/95
	Purpose:	Allows the user to set various layer properties, such as:-

	SeeAlso:	LayerProperties; LayerProperties;

********************************************************************************************/

class LayerPropertiesTab : public LayerPropertyTabs
{         
	CC_DECLARE_DYNCREATE( LayerPropertiesTab )  
public:

	LayerPropertiesTab();
	~LayerPropertiesTab();

	virtual BOOL Init();                        

	// Function to handle the messages for this tab/pane window
	virtual BOOL HandleMsg(DialogMsg* Msg);

	// Function to set up the values on this tab when being opened
	virtual BOOL InitSection();

	// Function to commit the values on this tab on ok
	virtual BOOL CommitSection();

	// Called when layer-related UI needs updating
	virtual BOOL UpdateLayerSection();

	// Functions to handle document changing messages
	virtual BOOL GreySection();			// Called when the user has closed all documents
	virtual BOOL UngreySection();		// Called when the user has opened a document
	BOOL ChangeControlStatus(const BOOL Status); // used to grey/ungrey all controls
	virtual BOOL UpdateSection();		// Called when the user has switched to a new document

	virtual CDlgResID GetPageID();		// Return section/page id system

	// Some functions to determine whether this particular property tab is required.
	virtual BOOL IsPropertyRequired();			// Return True if required

protected:

private:
	BOOL ShowDetails();
	BOOL UpdateApplyState();
	BOOL HavePropertiesChanged(Layer* pLayer);

	BOOL GreyStatus;					// Remember the state that we are currently in
}; 

#endif // INC_PROPERTIESLAYERS
