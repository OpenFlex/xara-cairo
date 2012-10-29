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


// Operations to save in the version 2 Native/Web format.
// Loading ops are not required as the general open operation will open any format file.

/*
*/

#include "camtypes.h"

#include "webop.h"
#include "nativeop.h"
//#include "filtrres.h"

//#include "barsdlgs.h"

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_DYNCREATE(OpSaveAsWeb, Operation)
CC_IMPLEMENT_DYNCREATE(OpSaveAsNativeV2, Operation)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	virtual UINT32 OpSaveAsWeb::GetSearchFilterId()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/96
	Inputs:		-
	Returns:	The id of the filter to search for.
	Purpose:	To allow different ops to just specify different filters and reuse
				the same operation code to save out the file in different file
				formats.

********************************************************************************************/

UINT32 OpSaveAsWeb::GetSearchFilterId()
{
	return FILTERID_WEB;
}

/********************************************************************************************

>	virtual BOOL OpSaveAsWeb::FixFileType()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/8/96
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if fixing is required, FALSE otherwise
	Purpose:	To determine whether this operation requires the file type or extension on
				the specified file path to be correct and match the	filter we are about to use.
				This baseclass version says no as the old native save operation did not do
				it.

********************************************************************************************/

BOOL OpSaveAsWeb::FixFileType()
{
	// Say we do not want it in this baseclass version
	return TRUE;
}

/********************************************************************************************

>	BOOL OpSaveAsWeb::Init()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/96
	Returns:	TRUE if it worked, FALSE if not
	Purpose:	Registers the OpDescriptor for the Save Operation.

********************************************************************************************/

BOOL OpSaveAsWeb::Init()
{
	BOOL InitOK = TRUE;

	// Register the save as web op desciptor
	InitOK = RegisterOpDescriptor(
									0, 							// Tool ID
									_R(IDS_SAVEASWEB),				// String resource ID
									CC_RUNTIME_CLASS(OpSaveAsWeb), 	// Runtime class
									OPTOKEN_SAVEASWEB,			// Token string
									GetState,					// GetState function
									0,							// help ID
									_R(IDBBL_SAVEASWEB),			// bubble help
									0, //_R(IDD_BARCONTROLSTORE),		// resource ID
									0, //_R(IDC_FILESAVETEMPLATE),		// control ID
									SYSTEMBAR_ILLEGAL,			// Bar ID
									TRUE,						// Recieve system messages
									FALSE,						// Smart duplicate operation
									TRUE,						// Clean operation
									0,							// No vertical counterpart
									0,							// String for one copy only error
									(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC) // Auto state flags
 								);
	if (!InitOK) return FALSE; 

	// All worked
	return TRUE;
}

/********************************************************************************************

>	OpState OpSaveAsWeb::GetState(String_256*, OpDescriptor*)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/96
	Purpose:	The OpState function

********************************************************************************************/

OpState OpSaveAsWeb::GetState(String_256*, OpDescriptor*)
{
	OpState Blobby;
	return Blobby;
}



/********************************************************************************************
/ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/
********************************************************************************************/


/********************************************************************************************

>	virtual UINT32 OpSaveAsNativeV2::GetSearchFilterId()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/96
	Inputs:		-
	Returns:	The id of the filter to search for.
	Purpose:	To allow different ops to just specify different filters and reuse
				the same operation code to save out the file in different file
				formats.

********************************************************************************************/

UINT32 OpSaveAsNativeV2::GetSearchFilterId()
{
	return FILTERID_NATIVE;
}

/********************************************************************************************

>	virtual BOOL OpSaveAsNativeV2::FixFileType()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/8/96
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if fixing is required, FALSE otherwise
	Purpose:	To determine whether this operation requires the file type or extension on
				the specified file path to be correct and match the	filter we are about to use.
				This baseclass version says no as the old native save operation did not do
				it.

********************************************************************************************/

BOOL OpSaveAsNativeV2::FixFileType()
{
	// Say we do not want it in this baseclass version
	return TRUE;
}

/********************************************************************************************

>	BOOL OpSaveAsNativeV2::Init()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/96
	Returns:	TRUE if it worked, FALSE if not
	Purpose:	Registers the OpDescriptor for the Save Operation.

********************************************************************************************/

BOOL OpSaveAsNativeV2::Init()
{
	BOOL InitOK = TRUE;

	// Register the save as web op desciptor
	InitOK = RegisterOpDescriptor(
									0, 							// Tool ID
									_R(IDS_SAVEASNATIVEV2),			// String resource ID
									CC_RUNTIME_CLASS(OpSaveAsNativeV2), 	// Runtime class
									OPTOKEN_SAVEASNATIVEV2,		// Token string
									GetState,					// GetState function
									0,							// help ID
									_R(IDBBL_SAVEASNATIVEV2),		// bubble help
									0, //_R(IDD_BARCONTROLSTORE),		// resource ID
									0, //_R(IDC_FILESAVETEMPLATE),		// control ID
									SYSTEMBAR_ILLEGAL,			// Bar ID
									TRUE,						// Recieve system messages
									FALSE,						// Smart duplicate operation
									TRUE,						// Clean operation
									0,							// No vertical counterpart
									0,							// String for one copy only error
									(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC) // Auto state flags
 								);
	if (!InitOK) return FALSE; 

	// All worked
	return TRUE;
}

/********************************************************************************************

>	OpState OpSaveAsNativeV2::GetState(String_256*, OpDescriptor*)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/96
	Purpose:	The OpState function

********************************************************************************************/

OpState OpSaveAsNativeV2::GetState(String_256*, OpDescriptor*)
{
	OpState Blobby;
	return Blobby;
}


