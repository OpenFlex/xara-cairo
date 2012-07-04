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


#ifndef INC_OPTSINET
#define INC_OPTSINET

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "appprefs.h"
//#include "webster.h"




/********************************************************************************************

>	class InternetTab : public OptionsTabs

	Author:		Adrian_Stoicar (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/06/97
	Purpose:	Allows the user to set Internet-related options
	SeeAlso:	OptionsTabs; AppPrefsDlg;

********************************************************************************************/

class InternetTab: public OptionsTabs
{         
	CC_DECLARE_DYNCREATE(InternetTab)  
public:

	// Function to handle the messages for this tab/pane window
	virtual BOOL HandleMsg(DialogMsg* Msg);

	// Function to set up the values on this tab when being opened
	virtual BOOL InitSection();

	// Function to commit the values on this tab on ok
	virtual BOOL CommitSection();

	virtual CDlgResID GetPageID() {return _R(IDD_OPTSTAB_INTERNET);} // Return section/page id system

	virtual BOOL IsDocumentOption() {return FALSE;} // Return True if document option  

	virtual BOOL IsProgramOption()	 {return TRUE;}	// Return True if program option

}; 



#endif
