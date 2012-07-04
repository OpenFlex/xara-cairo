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
// Class that represents pop-up menus in the kernel.
//

#ifndef INC_CONTEXTMENU
#define INC_CONTEXTMENU

//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "clikmods.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class MenuItem;
class Spread;
class OpMenuParam;

/********************************************************************************************

>	class ContextMenu : public CCObject

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/03/95
	Purpose:	Encapsulate the concept of pop-up, context-sensitive menus at the kernel
				level.

				To create and use a new context-sensitive menu:
				*	Derive a new subclass from ContextMenu, e.g. ViewContextMenu.
				*	Create the operations that you want to use from the menu or use existing
					operations.
				*	Implement a new Build function in your subclass to build your menu using
					the helper functions provided (see func headers for more details).
				*	That's all there is to it - the menu system handles everything else!

				Note: There are guidelines about how to construct a pop-up menu and when to
				open it.
				*	The menu should be formed something like this:
						Clicked object's primary commands
						Clicked object's transfer commands (e.g. cut, copy, etc...)
						"Properties..." command
				*	The menu should be opened in response to a BUTTON UP event!!!

********************************************************************************************/

class ContextMenu : public CC_CLASS_MEMDUMP
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(ContextMenu);

public:
						ContextMenu();
	virtual 			~ContextMenu();

// Major functions...
	BOOL				Show();
	BOOL				ShowOverView(Spread* pSpread, DocCoord ClickPos, ClickModifiers ClickMods);
	BOOL				Hide();
	static BOOL			HideCurrent();

// Functions that MUST be over-ridden in derived classes...
// Either:
	virtual	BOOL		Build();
// Or:
	virtual	BOOL		BuildOverView(Spread* pSpread, DocCoord ClickPos, ClickModifiers ClickMods);


//protected:
// Helper functions...
	BOOL 				BuildTransferCommands(BOOL NodeCommands);
	BOOL				BuildEffectCommands();
	BOOL 				BuildCommand(TCHAR* pOpToken,
									 BOOL Separator = FALSE,
									 MenuItem* pRootMenu = NULL,
									 const String& strNewText = String( _T("") ),
									 OpMenuParam* pParam = NULL);
	MenuItem*			GetLastItem();

protected:
	MenuItem*			pRootItem;
	MenuItem*			pLastItem;
	UINT32				AutoIDStash;

	static ContextMenu* pCurrentMenu;

};

#endif  // INC_CONTEXTMENU


