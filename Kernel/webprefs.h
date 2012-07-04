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
// Header file for WebPrefs.cpp
//
// 

#ifndef _INC_WEBPREFS_H
#define _INC_WEBPREFS_H

#include "bmpprefs.h"

// Forward declaration of the parameter class, and the base class.
class WebPrefsDlgParam;
class NativePrefsDlg;

/********************************************************************************************

>	class WebPrefsDlg : public NativePrefsDlg

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	1/5/96
	Purpose:	The export web file preference dialog box
	
				Allows the user to set options like:-
					Save selection, drawing or spread
					Whether bitmap compression that is taking place

********************************************************************************************/

#define OPTOKEN_WEBPREFSDLG _T("WebPrefsDlg")

PORTNOTE("dialog","Removed WebPrefsDlg - derived from NativePrefsDlg")
#ifndef EXCLUDE_FROM_XARALX
class WebPrefsDlg : public NativePrefsDlg
{
	CC_DECLARE_DYNCREATE( WebPrefsDlg )

public:
	WebPrefsDlg ();									// Default constructor.

	static BOOL Init();								// Setup function
	BOOL Create();									// Create this dialog
													// Return the state of this operation
	virtual MsgResult Message(Msg* Message);		// Message handler

	BOOL InvokeDialog(SelectionType *Selection, BOOL *Compression);
	BOOL InvokeDialog(WebPrefsDlgParam *pPrefs);

protected:
	virtual BOOL CommitDialogValues ( void );
	virtual BOOL InitDialog ( void );				// Standard set up function

private:
	BOOL CheckIfCompatibleBitmaps(Document* pDoc);	// function to check if bitmaps in doc are JPEGable
	
};
#endif

#endif // INC_WEBPREFS
