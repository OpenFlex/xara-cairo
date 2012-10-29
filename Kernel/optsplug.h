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

// Header for the handling code for the plug-ins tab of the options dialog box 

#ifndef INC_OPTSPLUGINS
#define INC_OPTSPLUGINS

#include "appprefs.h"

//class PlugInManager;

/********************************************************************************************

>	class PlugInsTab: public OptionsTabs

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/12/96
	Purpose:	Allows the user to define options assocaited with plug-ins. At present this
				covers:-
					- setting up the pathnames to use
					- a switch to say whether to parse the plug-ins at start up or not.
	SeeAlso:	OptionsTabs; AppPrefsDlg; DocPrefsDlg;

********************************************************************************************/

class PlugInsTab: public OptionsTabs
{         
	CC_DECLARE_DYNCREATE( PlugInsTab )  
public:

	PlugInsTab();
	~PlugInsTab();

	virtual BOOL Init();                        

	// Function to handle the messages for this tab/pane window
	virtual BOOL HandleMsg(DialogMsg* Msg);

	// Function to set up the values on this tab when being opened
	virtual BOOL InitSection();

	// Function to commit the values on this tab on ok
	virtual BOOL CommitSection();

	// Functions to handle document changing messages
	virtual CDlgResID GetPageID();		// Return section/page id system

	virtual BOOL IsDocumentOption();	// Return True if document option  

	virtual BOOL IsProgramOption();		// Return True if program option

protected:
	// Lots of controlling and handling functions specific to this section
	BOOL CommitDialogValues();

	BOOL InitControls();
	BOOL EnableControls();

//	BOOL CreateNewPath();
//	BOOL DeletePath();
//	void BuyPluginsAction();
//	BOOL ShowPathDetails();

private:
//	PlugInManager * m_pManager;	// Plug in manager

	BOOL m_ChangedList;
}; 

#endif // INC_OPTSPLUGINS
