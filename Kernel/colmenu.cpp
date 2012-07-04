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


// Context sensitive menu for the Colour Editor

/*
*/

#include "camtypes.h"

#include "coldlog.h"
#include "colmenu.h"
//#include "galstr.h"
//#include "jason.h"

//#include "will2.h"

DECLARE_SOURCE("$Revision: 1149 $");


CC_IMPLEMENT_MEMDUMP(ColEditContextMenu, ContextMenu)
CC_IMPLEMENT_DYNCREATE(OpColEditCommand, Operation);


#define new CAM_DEBUG_NEW



String_32 ColCmd_Help(_T("ColEdit:Help"));
String_32 ColCmd_Name(_T("ColEdit:Name"));
String_32 ColCmd_HSV(_T("ColEdit:HSV"));
String_32 ColCmd_RGB(_T("ColEdit:RGB"));
String_32 ColCmd_CMYK(_T("ColEdit:CMYK"));
String_32 ColCmd_Grey(_T("ColEdit:Grey"));
String_32 ColCmd_EditParent(_T("ColEdit:EditParent"));
#ifdef WEBSTER
String_32 ColCmd_NewNColour(_T("ColEdit:NewNColour"));
#endif //WEBSTER



/********************************************************************************************

>	ColEditContextMenu::ColEditContextMenu()

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95

	Purpose:	To construct ;-)

********************************************************************************************/

ColEditContextMenu::ColEditContextMenu()
{
}



/********************************************************************************************

>	virtual BOOL ColEditContextMenu::Build(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95

	Returns:	TRUE if menu built OK
				FALSE (and sets error) otherwise

	Purpose:	To build the colour editor pop-up menu. (Called when the window is adjust-clicked)

********************************************************************************************/

BOOL ColEditContextMenu::Build(void)
{
	BOOL ok = TRUE;

// WEBSTER - Martin 11/07/97
// Edit of the drop down colour model menu list
#ifdef WEBSTER
	if (ok) ok = ok && BuildCommand(ColCmd_NewNColour);			// New named colour
#endif // WEBSTER
	if (ok) ok = ok && BuildCommand(ColCmd_Name);				// Rename
	if (ok) ok = ok && BuildCommand(ColCmd_EditParent, TRUE);	// Edit Parent - With a separator

	if (ok) ok = ok && BuildCommand(ColCmd_HSV);				// Change colour model
	if (ok) ok = ok && BuildCommand(ColCmd_RGB,TRUE);

#ifndef WEBSTER
	if (ok) ok = ok && BuildCommand(ColCmd_CMYK);
	if (ok) ok = ok && BuildCommand(ColCmd_Grey, TRUE);			// Plus a separator
#endif // WEBSTER

	if (ok) ok = ok && BuildCommand(ColCmd_Help);				// Help
	
	return(ok);
}






//-------------------------------------------------------------------------------------------
//- Polymorphic gallery menu-item Ops


/********************************************************************************************

>	static BOOL OpColEditCommand::InitPolymorphicCommand(StringBase *OpToken, UINT32 MenuTextID)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95

	Inputs:		OpToken - The OpToken for the new Op - use "ColEdit_Command"

				MenuTextID - A String Resource ID for the menu item text

	Returns:	TRUE if it succeeded, FALSE if not enough memory to register the OpDescriptor

	Purpose:	Given a command OpToken, this creates a new OpDescriptor for the OpColEditCommand Op.
				This in turn will provide an Upcall to the Editor containing the given command
				string, whenever the Op is invoked.

********************************************************************************************/

BOOL OpColEditCommand::InitPolymorphicCommand(StringBase *OpToken, UINT32 MenuTextID)
{
	return(RegisterOpDescriptor(0,									// Tool ID 
								MenuTextID,		 					// String resource ID
								CC_RUNTIME_CLASS(OpColEditCommand),	// Runtime class
								(TCHAR *) (*OpToken), 				// Token string
								OpColEditCommand::GetCommandState,	// GetState function
								0,									// help ID
								0,									// bubble help
								0,									// resource ID
								0,									// control ID
								SYSTEMBAR_ILLEGAL,					// Bar ID
								FALSE,								// Recieve system messages
								FALSE,								// Smart duplicate operation
								TRUE,								// Clean operation
								NULL,								// No vertical counterpart
								0,									// String for one copy only error
								DONT_GREY_WHEN_SELECT_INSIDE		// Auto state flags
								));
}



/********************************************************************************************

>	static BOOL OpColEditCommand::Init(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95

	Returns:	TRUE if the operation could be successfully initialised 
				FALSE if no more memory could be allocated 

	Purpose:	OpColEditCommand initialiser method.

	Notes:		Initialises all of the commands available to the colour editor

	SeeAlso:	SuperGallery::InitMenuCommand

********************************************************************************************/

BOOL OpColEditCommand::Init(void)
{
#ifdef WEBSTER
	InitPolymorphicCommand((StringBase *) &ColCmd_NewNColour, _R(IDS_NEWCOLOUR));
#endif // WEBSTER
	InitPolymorphicCommand((StringBase *) &ColCmd_Name, _R(IDS_SGMENU_RENAME));
	InitPolymorphicCommand((StringBase *) &ColCmd_EditParent, _R(IDS_COLMENU_EDITPARENT));

	InitPolymorphicCommand((StringBase *) &ColCmd_HSV, _R(IDS_COLMODEL_HSVT));
	InitPolymorphicCommand((StringBase *) &ColCmd_RGB, _R(IDS_COLMODEL_RGBT));
	InitPolymorphicCommand((StringBase *) &ColCmd_CMYK, _R(IDS_COLMODEL_CMYK));
	InitPolymorphicCommand((StringBase *) &ColCmd_Grey, _R(IDS_COLMODEL_GREY));

	InitPolymorphicCommand((StringBase *) &ColCmd_Help, _R(IDS_COLMENU_HELP));

	return (TRUE);
}               



/********************************************************************************************

>	static OpState OpColEditCommand::GetCommandState(String_256 *UIDescription,
														OpDescriptor *pOpDesc)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95

	Inputs:		UIDescription - ptr to a string to place a description of what went wrong (if it did!)
				OpDesc  - The OpDescriptor for which we need the state

	Outputs:	UIDescription is updated appropriately

	Returns:	The state of the OpColEditCommand operation for the given OpDescriptor
	Purpose:	For finding OpColEditCommand's state. 

********************************************************************************************/

OpState	OpColEditCommand::GetCommandState(String_256 *UIDescription, OpDescriptor *pOpDesc)
{
	if (ColourEditDlg::TheEditor != NULL)
		return(ColourEditDlg::TheEditor->GetCommandState(&pOpDesc->Token, UIDescription));

	// else return a "safe" shaded state
	OpState OpSt;
	OpSt.Greyed = TRUE;
	*UIDescription = String_256(_R(IDS_K_COLMENU_NOEDITOR));
	return (OpSt); 
}



/********************************************************************************************

>	void OpColEditCommand::Do(OpDescriptor* pOpDesc)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95
	Inputs:		pOpDesc = ptr to the op descriptor
	Outputs:	-
	Returns:	-
	Purpose:	The nudge op's Do() function.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void OpColEditCommand::Do(OpDescriptor* pOpDesc)
{  
	if (ColourEditDlg::TheEditor != NULL)
		ColourEditDlg::TheEditor->DoCommand(&pOpDesc->Token);

	End();
}

