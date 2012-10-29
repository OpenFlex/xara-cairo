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


/*
*/

// Code to handle printing in a kernely sort of way
// (For the moment, this is just to do menu code interaction)

#include "camtypes.h"
//	WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER
#include "printing.h"
//#include "mario.h"
#include "menucmds.h"
#include "helpids.h"
#include "bubbleid.h"
#include "prncamvw.h"
#include "prdlgctl.h"
//#include "barsdlgs.h"
//#include "nev.h"		// _R(IDS_FILE_PRINT_ONE)

CC_IMPLEMENT_DYNCREATE(OpPrint, Operation)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	OpPrint::OpPrint()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/11/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Constructs a new OpPrint object: setting default operation flags, and 
				adding it to the Live list. 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
     
OpPrint::OpPrint(): Operation()
{                 
}



/********************************************************************************************

>	OpState OpPrint::GetState(String_256*, OpDescriptor*)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/93
	Inputs:		-
	Outputs:	-
	Returns:	Not ticked and not greyed
	Purpose:	Menu state for Print item
	Errors:		-

********************************************************************************************/

OpState OpPrint::GetState(String_256*, OpDescriptor* WhichOp)
{
	BOOL ForceGreyed = FALSE;
	if ((WhichOp->Token) == (String(OPTOKEN_PRINT_SETUP)))
		ForceGreyed=!CCPrintInfo::HasPrintSetup();
	// not ticked, greyed only if already printing (or the print dialog is open).
	return OpState( FALSE, PrintMonitor::IsPrintingActive() || ForceGreyed);
}


/********************************************************************************************

>	void OpPrint::Do(OpDescriptor* WhichOp)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/93
	Inputs:		A pointer to OpDescriptor - allows selection of appropriate print routine.
	Outputs:	-
	Returns:	-
	Purpose:	Actually do appropriate print function. Print Functions available include
				Print, Print setup and Print preview.
	Errors:		-

********************************************************************************************/

void OpPrint::Do(OpDescriptor* WhichOp)
{
	if ((WhichOp->Token) == (String(OPTOKEN_PRINT)))
		PrintAction();
	else if  ((WhichOp->Token) == (String(OPTOKEN_PRINT_SETUP)))
		PrintSetupAction();
	else if  ((WhichOp->Token) == (String(OPTOKEN_PRINT_PREVIEW)))
		PrintPreviewAction();
	
	End();
}


/********************************************************************************************

>	BOOL OpPrint::Init()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/93
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if successully created all necessary opdescriptors.
	Purpose:	Initialises all the print operation OpDescriptors..
	Errors:		-

********************************************************************************************/

BOOL OpPrint::Init()
{
	BOOL InitOK = TRUE;

	InitOK = RegisterOpDescriptor(
									0, 							// Tool ID
									_R(IDS_FILE_PRINT),				// String resource ID
									CC_RUNTIME_CLASS(OpPrint), 	// Runtime class
									OPTOKEN_PRINT,				// Token string
									OpPrint::GetState,			// GetState function
									HID_FILE_PRINT,				// help ID
									_R(IDBBL_PRINTOP),				// bubble help
									_R(IDD_BARCONTROLSTORE),		// resource ID
									_R(IDC_BTN_FILEPRINT),			// control ID
									SYSTEMBAR_FILE,				// Bar ID
									TRUE,						// Recieve system messages
									FALSE,						// Smart duplicate operation
									TRUE,						// Clean operation
									0,							// No vertical counterpart
									_R(IDS_FILE_PRINT_ONE),			// String for one copy only error
									(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC) // Auto state flags
 								);
	ERRORIF(!InitOK, _R(IDE_NOMORE_MEMORY), FALSE);
 

	InitOK = RegisterOpDescriptor(
									0, 							// Tool ID
									_R(IDS_FILE_PRINT_SETUP),		// String resource ID
									CC_RUNTIME_CLASS(OpPrint), 	// Runtime class
									OPTOKEN_PRINT_SETUP,		// Token string
									OpPrint::GetState,			// GetState function
									HID_FILE_PRINT_SETUP,		// help ID
									_R(IDBBL_PSETUPOP),				// bubble help
									_R(IDD_BARCONTROLSTORE),		// resource ID
									_R(IDC_PRINTSETUP),				// control ID
									SYSTEMBAR_FILE,				// Bar ID
									TRUE,						// Recieve system messages
									FALSE,						// Smart duplicate operation
									TRUE,						// Clean operation
									0,							// No vertical counterpart
									0,							// String for one copy only error
									(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC) // Auto state flags
 								);
	ERRORIF(!InitOK, _R(IDE_NOMORE_MEMORY), FALSE);

	OpDescriptor* PPreviewOp = new OpDescriptor(
												0, 
												_R(IDS_FILE_PRINT_PREVIEW),
												CC_RUNTIME_CLASS(OpPrint), 
												OPTOKEN_PRINT_PREVIEW,
												OpPrint::GetState,
												HID_FILE_PRINT_PREVIEW,
												_R(IDBBL_PPREVIEWOP),
												0	/* bitmap ID */);

	ERRORIF(!PPreviewOp, _R(IDE_NOMORE_MEMORY), FALSE);

	return TRUE;
}

#endif //webster
