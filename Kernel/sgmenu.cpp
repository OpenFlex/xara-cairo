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


// Context sensitive menu for SuperGalleries

/*
*/

#include "camtypes.h"

#include "sgmenu.h"
//#include "sgallery.h" - in camtypes.h [AUTOMATICALLY REMOVED]

DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_MEMDUMP(GalleryContextMenu, ContextMenu)
CC_IMPLEMENT_DYNCREATE(OpGalleryCommand, Operation);

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	GalleryContextMenu::GalleryContextMenu(SGMenuID TheMenuType, SuperGallery *ParentGallery)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95

	Inputs:		TheMenuType - Determines whether this will be a gallery-options dropdown menu
				or a gallery-item/group pop-up menu.

				ParentGallery - The gallery whose options are to be shown

	Purpose:	To construct ;-)

	Notes:		The default constructor will ERROR3 - always use this variant

********************************************************************************************/

GalleryContextMenu::GalleryContextMenu()
{
	ERROR3("GalleryContextMenu - DON'T call the default constructor!");
	MenuType = SGMENU_OPTIONS;
	ParentGallery = NULL;
}

GalleryContextMenu::GalleryContextMenu(SGMenuID TheMenuType, SuperGallery *ParentGal)
{
	MenuType = TheMenuType;
	ParentGallery = ParentGal;
}



/********************************************************************************************

>	virtual BOOL GalleryContextMenu::Build(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/9/95

	Returns:	TRUE if menu built OK
				FALSE (and sets error) otherwise

	Purpose:	To build the SuperGallery pop-up menu. (Called whn the list is adjust-clicked)
				The exact type (options or item-pop-up) of menu depends on the value passed\
				into the constructor.

********************************************************************************************/

BOOL GalleryContextMenu::Build(void)
{
	if (ParentGallery == NULL)
	{
		ERROR3("GalleryContextMenu incorrectly constructed");
		return(FALSE);
	}

	// It's all up to the gallery to fill us in appropriately
	return(ParentGallery->BuildCommandMenu(this, MenuType));
}






//-------------------------------------------------------------------------------------------
//- Polymorphic gallery menu-item Ops


/********************************************************************************************

>	static BOOL OpGalleryCommand::InitPolymorphicCommand(StringBase *OpToken, UINT32 MenuTextID)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/9/95

	Inputs:		OpToken - The OpToken for the new Op
				This must be of the form "Gallery name:Gallery command"
				Each portion must be no more than 31 characters long

				MenuTextID - A String Resource ID for the menu item text

	Returns:	TRUE if it succeeded, FALSE if not enough memory to register the OpDescriptor

	Purpose:	Given a Gallery command OpToken of the form "Gallery name:Command name"
				this creates a new OpDescriptor for the OpGalleryCommand Op. This in turn
				will provide an Upcall to the named Gallery containing the given command
				string, whenever the Op is invoked.

********************************************************************************************/

BOOL OpGalleryCommand::InitPolymorphicCommand(StringBase *OpToken, UINT32 MenuTextID)
{
	return(RegisterOpDescriptor(0,									// Tool ID 
								MenuTextID,		 					// String resource ID
								CC_RUNTIME_CLASS(OpGalleryCommand),	// Runtime class
								(TCHAR *) (*OpToken), 				// Token string
								OpGalleryCommand::GetCommandState,	// GetState function
								0,									// help ID
								0,									// bubble help
								0,									// resource ID
								0,									// control ID
								SYSTEMBAR_ILLEGAL,					// Bar ID
								FALSE,								// Recieve system messages
								FALSE,								// Smart duplicate operation
								TRUE,								// Clean operation
								0,									// No vertical counterpart
								0,									// String for one copy only error
								DONT_GREY_WHEN_SELECT_INSIDE		// Auto state flags
								));
}



/********************************************************************************************

>	static SuperGallery *OpGalleryCommand::GetGalleryAndCommand(OpDescriptor *pOpDesc,
																String_32 *Command)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95
	Inputs:		pOpDesc - The Op Descriptor for the Op

	Outputs:	Command - returned as "" or as the command string from the OpToken

	Returns:	NULL if the gallery wasn't found, or a pointer to the SuperGallery which
				should process the command

	Purpose:	Given a Gallery command OpDescriptor of the form "Gallery name:Command name"
				this returns a pointer to the gallery to use and the string "Command name"
				which is the command that gallery should apply.

********************************************************************************************/

SuperGallery *OpGalleryCommand::GetGalleryAndCommand(OpDescriptor *pOpDesc, String_32 *Command)
{
	String_256 Temp = pOpDesc->Token;
	TCHAR *Str = (TCHAR *)Temp;

	*Command = TEXT("");

	while (*Str != '\0' && *Str != ':')
		Str++;

	if (*Str == '\0')
		return(NULL);

	// Copy the right end of the string into Command for return
	*Command = (TCHAR *) (Str+1);

	// Find the gallery referenced by the left end of the string
	*Str = '\0';		// NULL Terminate the left end of the string

	String_32 Bob;
	Temp.Left(&Bob, 31);
	SuperGallery* pSuperGallery = SuperGallery::FindSuperGallery(Bob , GalleryBarNameLimitSize);

	if (pSuperGallery != NULL && pSuperGallery->IsKindOf(CC_RUNTIME_CLASS(SuperGallery)))
		return((SuperGallery *) pSuperGallery);

	// Not found, or isn't a gallery?! (eep!)
	return(NULL);
}



/********************************************************************************************

>	static BOOL OpGalleryCommand::Init(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95

	Returns:	TRUE if the operation could be successfully initialised 
				FALSE if no more memory could be allocated 

	Purpose:	OpGalleryCommand initialiser method.

	Notes:		This Init does nothing - The Op does not have its own OpDescriptor.
				Instead, each gallery will add an OpDescriptor for each command they
				wish to add to their menu, all of which will reference this Op.

	SeeAlso:	SuperGallery::InitMenuCommand

********************************************************************************************/

//BOOL OpGalleryCommand::Init(void)
//{
//	return (TRUE);
//}               



/********************************************************************************************

>	static OpState OpGalleryCommand::GetCommandState(String_256 *UIDescription,
														OpDescriptor *pOpDesc)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95

	Inputs:		UIDescriptoin - ptr to a string to place a description of what went wrong (if it did!)
				OpDesc  - The OpDescriptor for which we need the state

	Outputs:	UIDescription is updated appropriately

	Returns:	The state of the OpGalleryCommand operation for the given OpDescriptor
	Purpose:	For finding OpGalleryCommand's state. 

********************************************************************************************/

OpState	OpGalleryCommand::GetCommandState(String_256 *UIDescription, OpDescriptor *pOpDesc)
{
	String_32 Command;
	SuperGallery *ParentGallery = GetGalleryAndCommand(pOpDesc, &Command);

	if (ParentGallery != NULL)
		return(ParentGallery->GetCommandState(&Command, UIDescription));

	ERROR3("Attempt to get state for non-existent Gallery command");

	// Return a "safe" shaded state
	OpState OpSt;
	OpSt.Greyed = TRUE;
	*UIDescription = "";
	return (OpSt);   
}



/********************************************************************************************

>	void OpGalleryCommand::Do(OpDescriptor* pOpDesc)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95
	Inputs:		pOpDesc = ptr to the op descriptor
	Outputs:	-
	Returns:	-
	Purpose:	The nudge op's Do() function.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void OpGalleryCommand::Do(OpDescriptor* pOpDesc)
{  
	String_32 Command;
	SuperGallery *ParentGallery = GetGalleryAndCommand(pOpDesc, &Command);

	if (ParentGallery != NULL)
		ParentGallery->DoCommand(&Command);

	End();
}

