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

#ifndef _INC_XARPREFS_H
#define _INC_XARPREFS_H

#include "bmpprefs.h"
#include "webparam.h"
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class NativePrefsDlg : public DialogOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	1/5/96
	Purpose:	The export web file preference dialog box
	
				Allows the user to set options like:-
					Save selection, drawing or spread
					Whether bitmap compression that is taking place

********************************************************************************************/

#define OPTOKEN_NATIVEPREFSDLG _T("NativePrefsDlg")

class NativePrefsDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE( NativePrefsDlg )

public:
	NativePrefsDlg ();								// Default constructor.
	~NativePrefsDlg();

	void DoWithParam ( OpDescriptor*,				// "DoWithParam" function
					   OpParam* Param );

	void Do ( OpDescriptor* );

	static BOOL Init ();							// Setup function.
	BOOL Create ();									// Create this dialogue.

	static OpState GetState ( String_256*,			// Get the state of the op.
							  OpDescriptor* );

	virtual MsgResult Message ( Msg* Message );		// Message handler


protected:
	NativePrefsDlg ( CDlgResID IDD );				// The other constructor.

	SelectionType GetExportSelection ( UINT32 ControlID );// Returns the export selection.

	virtual BOOL CommitDialogValues();

	virtual BOOL InitDialog ();						// Standard set up function

	WebPrefsDlgParam *mpParams;						// The export parameters.
};
#endif // _INC_XARPREFS_H
