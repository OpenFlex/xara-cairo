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

// A simple Dialog That does some Gavin Rendering into itself

/*
Code for the colour selector tool added 22/07/99 ap
*/

#include "camtypes.h"

#include "prvwmenu.h"
#include "bmpexprw.h"
//#include "exprwres.h"


// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
CC_IMPLEMENT_DYNCREATE(OpPreviewPopupCommand, Operation)

BitmapExportPreviewDialog *OpPreviewPopupCommand::m_pDialog = NULL;

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW



/********************************************************************************************
>	virtual	BOOL PreviewContextMenu :: Build()

	Author:		Stefan_Stoykov (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/5/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Builds the context menu
********************************************************************************************/

BOOL PreviewContextMenu :: Build()
{
	BOOL ok = TRUE;

	if (ok) ok = ok && BuildCommand(OPTOKEN_PREVIEW_ZOOM_TOOL);
	if (ok) ok = ok && BuildCommand(OPTOKEN_PREVIEW_PUSH_TOOL);
	if (ok) ok = ok && BuildCommand(OPTOKEN_PREVIEW_COLOUR_SELECTOR_TOOL);
	if (ok) ok = ok && BuildCommand(OPTOKEN_PREVIEW_ZOOM_TO_FIT);
	if (ok) ok = ok && BuildCommand(OPTOKEN_PREVIEW_ZOOM_TO_100);
	if (ok) ok = ok && BuildCommand(OPTOKEN_PREVIEW_1TO1, TRUE);
	if (ok) ok = ok && BuildCommand(OPTOKEN_PREVIEW_HELP);

	return (ok);
}




	
/********************************************************************************************
>	static BOOL OpPreviewPopupCommand::InitPolymorphicCommand(TCHAR *OpToken, UINT32 MenuTextID)

	Author:		Stefan_Stoykov (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/5/97
	Inputs:		OpToken - the token of a menu operation
				MenuTextID - the resource string of the menu command
	Outputs:	-
	Returns:	-
	Purpose:	Registeres a menu operation
********************************************************************************************/

BOOL OpPreviewPopupCommand::InitPolymorphicCommand(TCHAR *OpToken, UINT32 MenuTextID)
{
	return(RegisterOpDescriptor(0,									// Tool ID 
								MenuTextID,		 					// String resource ID
								CC_RUNTIME_CLASS(OpPreviewPopupCommand),// Runtime class
								OpToken, 							// Token string
								OpPreviewPopupCommand::GetCommandState,	// GetState function
								0,									// help ID
								0,									// bubble help
								0,									// resource ID
								0,									// control ID
								SYSTEMBAR_ILLEGAL,					// Bar ID
								FALSE,								// Receive system messages
								FALSE,								// Smart duplicate operation
								TRUE,								// Clean operation
								NULL,								// No vertical counterpart
								0,									// String for one copy only error
								DONT_GREY_WHEN_SELECT_INSIDE		// Auto state flags
								));
}



/********************************************************************************************
>	static BOOL OpPreviewPopupCommand::Init(void)

	Author:		Stefan_Stoykov (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/5/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Registeres all the menu operations by calling InitPolymorphicCommand
********************************************************************************************/

BOOL OpPreviewPopupCommand::Init(void)
{
	InitPolymorphicCommand(OPTOKEN_PREVIEW_ZOOM_TOOL,			 _R(IDS_MENU_ZOOM));
	InitPolymorphicCommand(OPTOKEN_PREVIEW_PUSH_TOOL,			 _R(IDS_MENU_PUSH));
	InitPolymorphicCommand(OPTOKEN_PREVIEW_COLOUR_SELECTOR_TOOL, _R(IDS_MENU_SELECTOR));
	InitPolymorphicCommand(OPTOKEN_PREVIEW_ZOOM_TO_FIT,			 _R(IDS_MENU_FIT));
	InitPolymorphicCommand(OPTOKEN_PREVIEW_ZOOM_TO_100,			 _R(IDS_MENU_100));
	InitPolymorphicCommand(OPTOKEN_PREVIEW_1TO1,				 _R(IDS_MENU_1TO1));
	InitPolymorphicCommand(OPTOKEN_PREVIEW_HELP, _R(IDS_PREVIEW_MENU_HELP));

	return (TRUE);
}               



/********************************************************************************************

>	static OpState	OpPreviewPopupCommand::GetCommandState(String_256 *UIDescription, 
															OpDescriptor *pOpDesc)

	Author:		Stefan_Stoykov (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/5/97

	Inputs:		UIDescription - ptr to a string to place a description of what went wrong 
								(if it did!)
				OpDesc  - The OpDescriptor for which we need the state

	Outputs:	UIDescription is updated appropriately

	Returns:	The state of the OpPreviewPopupCommand operation for the given OpDescriptor
	Purpose:	For finding OpPreviewPopupCommand's state. Used only to tick the proper tool, 
				depending on the current mode

********************************************************************************************/

OpState	OpPreviewPopupCommand::GetCommandState(String_256 *UIDescription, OpDescriptor *pOpDesc)
{
	OpState OpSt;
	OpSt.Greyed = FALSE; //always active
	// tick either the push or the zoom tool depending on the current mode
	if (((pOpDesc->Token == String_256(OPTOKEN_PREVIEW_PUSH_TOOL)) && 
				(m_pDialog->GetCurrentTool() == PREVIEW_PUSH_TOOL)) ||
		((pOpDesc->Token == String_256(OPTOKEN_PREVIEW_ZOOM_TOOL)) && 
				(m_pDialog->GetCurrentTool() == PREVIEW_ZOOM_TOOL)) ||
		((pOpDesc->Token == String_256(OPTOKEN_PREVIEW_COLOUR_SELECTOR_TOOL)) &&
				(m_pDialog->GetCurrentTool() == PREVIEW_COLOUR_SELECTOR_TOOL)))
		OpSt.Ticked = TRUE;

	return (OpSt); 
}


/********************************************************************************************
>	virtual void OpPreviewPopupCommand::Do(OpDescriptor* pOpDesc)

	Author:		Stefan_Stoykov (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/5/97
	Inputs:		pOpDesc - the descriptor of the operation
	Outputs:	-
	Returns:	-
	Purpose:	Passes the token of the selected menu command to the dialog so it can be 
				handled there
********************************************************************************************/

void OpPreviewPopupCommand::Do(OpDescriptor* pOpDesc)
{  
	// get the token
	String_256 s(pOpDesc->Token);

	// ask the dialog to handle it
	m_pDialog->DoCommand(&s);

	End();
}

