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
// Class that represents pop-up menus in the kernel
//
/*
*/

#include "camtypes.h"
#include "contmenu.h"
#include "menuitem.h"
#include "oilmenus.h"
#include "menupref.h"
#include "cutop.h"
//#include "spread.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "effects_stack.h"
#include "opliveeffects.h"

// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe
DECLARE_SOURCE("$Revision: 1282 $");

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
CC_IMPLEMENT_MEMDUMP(ContextMenu, CC_CLASS_MEMDUMP)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW



ContextMenu* ContextMenu::pCurrentMenu = NULL;

/********************************************************************************************

>	ContextMenu::ContextMenu()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE
				FALSE
	Purpose:	
	Errors:		-

********************************************************************************************/

ContextMenu::ContextMenu()
{
	pRootItem = NULL;
	pLastItem = NULL;
	AutoIDStash = 0;
}




/********************************************************************************************

>	ContextMenu::~ContextMenu()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE
				FALSE
	Purpose:	
	Errors:		-

********************************************************************************************/

ContextMenu::~ContextMenu()
{
}




/********************************************************************************************

>	BOOL ContextMenu::Show()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE
				FALSE
	Purpose:	
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::Show()
{
	// If there's a menu still around for some reason, get rid of it.
	if (pCurrentMenu)
	{
		pCurrentMenu->Hide();
	}

	// Preserve current ID generator state
	AutoIDStash = MenuItem::GetAutomaticIDState();

	// Make a new root item
	pRootItem = new MenuItem("CONTEXT");
	if (pRootItem)
	{
		// OK, make this menu current and try to build it's contents
		pCurrentMenu=this;
		if (Build())
		{
			// Kernel menu built OK so create the OILy part of it...
			CreateContextMenu(pRootItem);
			return TRUE;
		}
	}

	// Failed to completely build Kernel menu structure so delete anything
	// that might have been built...
	Hide();
	return FALSE;
}




/********************************************************************************************

>	BOOL ContextMenu::ShowOverView(Spread* pSpread, DocCoord ClickPos, ClickModifiers ClickMods)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE
				FALSE
	Purpose:	This function does the same job as ShowMenu but unfortunately needs some
				parameters to pass on to the menu builders. Not very neat, I know...
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::ShowOverView(Spread* pSpread, DocCoord ClickPos, ClickModifiers ClickMods)
{
	// If there's a menu still around for some reason, get rid of it.
	if (pCurrentMenu)
	{
		pCurrentMenu->Hide();
	}

	// Preserve current ID generator state
	AutoIDStash = MenuItem::GetAutomaticIDState();

	// Make a new root item
	pRootItem = new MenuItem("CONTEXT");
	if (pRootItem)
	{
		// OK, make this menu current and try to build it's contents
		pCurrentMenu=this;
		if (BuildOverView(pSpread, ClickPos, ClickMods))
		{
			// Kernel menu built OK so create the OILy part of it...
			CreateContextMenu(pRootItem);
			return TRUE;
		}
	}

	// Failed to completely build Kernel menu structure so delete anything
	// that might have been built...
	Hide();
	return FALSE;
}




/********************************************************************************************

>	BOOL ContextMenu::Hide()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE
				FALSE
	Purpose:	Close and delete any context menu that may be open.
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::Hide()
{
	DestroyContextMenu();

	// Restore ID generator state
	MenuItem::SetAutomaticIDState(AutoIDStash);
	AutoIDStash = 0;

	if (pCurrentMenu==this)
		pCurrentMenu = NULL;

	delete this;
	return TRUE;
}




/********************************************************************************************

>	static BOOL ContextMenu::HideCurrent()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/10/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE
				FALSE
	Purpose:	Close and delete the current context menu if it's open.
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::HideCurrent()
{
	if (pCurrentMenu)
		pCurrentMenu->Hide();
	return TRUE;
}




/********************************************************************************************

>	BOOL ContextMenu::Build()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		pRootMenu	Pointer to root menu item to add new items to.
	Outputs:	-
	Returns:	TRUE if menu built OK
				FALSE (and sets error) otherwise
	Purpose:	Base class implementation of menu builder.
				This function builds a menu statically by creating the appropriate objects.
				It does NOT call teh menu script interpreter because I am unhappy about the
				reliability of repeatedly calling that code.

				An overloaded version of this function could be written which takes in a
				reference to a "file" to be opened and interpreted.

				Note also that by building the menu programmatically it can change depending
				on the context within which it is opened...

				The standard layout for pop-up menus is:
					Clicked object's primary commands
					Transfer commands
					Other commands supported by the clicked object
					The "What's this?" command
					The Properties... command
				These are only guidelines and you can omit any sections you don't need.

				To implement an overriden version of this function you simply need to make it
				add new menu items to the root menu. There are helper functions to make this
				easier:
					BuildTransferCommands will add Cut,Copy,Paste,etc.
					BuildCommand will take any OPTOKEN you give it and build an item linked
						to that OPTOKEN.
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::Build()
{
	ERROR2(FALSE,"ContextMenu::Build called in base class - should be overridden!");
}




/********************************************************************************************

>	BOOL ContextMenu::BuildOverView(Spread* pSpread, DocCoord ClickPos, ClickModifiers ClickMods)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		pRootMenu	Pointer to root menu item to add new items to.
	Outputs:	-
	Returns:	TRUE if menu built OK
				FALSE (and sets error) otherwise
	Purpose:	Base class function which, when overridden in derived classes, will build
				a pop-up menu according to a given position in a view.
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::BuildOverView(Spread* pSpread, DocCoord ClickPos, ClickModifiers ClickMods)
{
	ERROR2(FALSE,"ContextMenu::BuildOverView called in base class - should be overridden!");
}




/********************************************************************************************

>	BOOL ContextMenu::BuildTransferCommands(BOOL NodeCommands)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		-
	Outputs:	-
	Returns:	Pointer to first MenuItem in the kernel menu definition
	Purpose:	Append the standard "transfer command" menu items to the input root menu
				This function adds:
					Cut
					Copy
					Paste
					(Paste link	When we implement OLE...)
				And if NodeCommands is TRUE:
					-----
					Delete
					Duplicate
					Clone
					-----
					
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::BuildTransferCommands(BOOL NodeCommands)
{
	// Build the standard transfer command menu items...
	BuildCommand(OPTOKEN_CUT);
	BuildCommand(OPTOKEN_COPY);
	BuildCommand(OPTOKEN_PASTE, TRUE);
//	BuildCommand(OPTOKEN_PASTELINK);

	// If caller wants transfer commands for Nodes in the document build them...
	if (NodeCommands)
	{
		BuildCommand(OPTOKEN_DELETE);
		BuildCommand(OPTOKEN_DUPLICATE);
		BuildCommand(OPTOKEN_CLONE, TRUE);
	}

	return TRUE;
}




/********************************************************************************************

>	BOOL ContextMenu::BuildEffectCommands()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Inputs:		-
	Outputs:	-
	Returns:	Pointer to first MenuItem in the kernel menu definition
	Purpose:	Append the "effect" menu items to the input root menu
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::BuildEffectCommands()
{
	EffectsStack* pStack = GetApplication()->FindSelection()->GetEffectsStack();	// Cached copy
	if (pStack->IsEmpty() || !pStack->bConsistent)
		return TRUE;

	BuildCommand( TOOL_OPTOKEN_LIVEEFFECT );		// Go to Effects tool

	pStack->BuildEffectMenu(this);						// <List of effects>

	BuildCommand(OPTOKEN_DELETEALL_LIVEEFFECT, TRUE);	// Remove all Effects

	return TRUE;
}




/********************************************************************************************

>	BOOL ContextMenu::BuildCommand(TCHAR* pOpToken, BOOL Separator = FALSE, MenuItem* pRootMenu = NULL, const String& strNewText = "", OpMenuParam* pParam = NULL)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/03/95
	Inputs:		pOpToken	Pointer to optoken for this item
				Separator	Flag that separator is required after this item
				pRootMenu	Pointer to root menu to add this to or NULL for main root
	Outputs:	-
	Returns:	Pointer to first MenuItem in the kernel menu definition
	Purpose:	Append a new menu item to this menu.
				Passing pRootMenu as NULL (leaving it defaulted) causes the new item to be
				added to the first level of the pop-up menu.
				Passing pRootMenu non-NULL allows you to build a submenu.
	Errors:		-

********************************************************************************************/

BOOL ContextMenu::BuildCommand(TCHAR* pOpToken, BOOL Separator, MenuItem* pRootMenu, const String& strNewText, OpMenuParam* pParam)
{
	MenuItem* pNewItem;

	// If caller hasn't specified a root menu use the root of the whole thing...
	if (pRootMenu == NULL)
		pRootMenu = pRootItem;

	// Create a new kernel menu item...
	pNewItem = CreateMenuItem(pOpToken, pRootMenu->GetMenuId(), Separator);

	// If that worked, add it to the root menu. Else flag failure.
	if (pNewItem)
	{
		pLastItem = pNewItem;

		if (!strNewText.IsEmpty())
			pNewItem->SetMenuText(strNewText);

		if (pParam)
			pNewItem->SetMenuParam(pParam);

		pRootMenu->AddMenuItem(pNewItem);

		return TRUE;
	}
	else
		return FALSE;
}




/********************************************************************************************

>	MenuItem* ContextMenu::GetLastItem()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/03/95
	Inputs:		-
	Outputs:	-
	Returns:	Pointer to last MenuItem defined
	Purpose:	Get pointer to item last previously created
	Errors:		-

********************************************************************************************/

MenuItem* ContextMenu::GetLastItem()
{
	return	pLastItem;
}




