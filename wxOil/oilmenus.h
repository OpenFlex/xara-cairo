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
 * */  

/********************************************************************************************

< Menus
< MenuItems
< OIL Menus

COMMENT:

\b OILMENUS Module \b0

The OilMenus module provides a set of functions used for initialising, updating and 
deinitialising the menu system. The new menu consists of two dynamic menu structures. The 
first is a platform independent structure which resides in the Kernel. This structure is 
created and and maintained by functions which reside in the OilMenus Module. The fundamental
component of this structure is the MenuItem class. The second menu structure is a Windows
specific one. It is composed of CMENU objects. The creation and deletion of these objects 
is again handled by functions which reside in the OilMenus module. Conversion between these
menu structures occurs during initialisation and update (i.e.  new menu items are added to 
an existing menu). The reasons for maintaining two menu structures are mainly to do with portability and 
flexibility. 

SeeAlso: 	MenuItem
SeeAlso: 	InitMenuSystem()
SeeAlso:	DeInitMenuSystem()
SeeAlso:	SetupDefaultMenu()
SeeAlso:	SetupSharedMenu()
SeeAlso:	ConvertToWinMenu()
SeeAlso:	PerformMenuCommand()
SeeAlso:	UpdateMenu()

********************************************************************************************/


#ifndef	INC_OILMENUS
#define INC_OILMENUS

#include "menuitem.h"


// A little wxMenuBase derived class to allow the killing of the accelerator table
class wxCamMenuBar : public wxMenuBar
{
public:
	void ClearAccelTable()
	{
#if defined(__WXMSW__)
		m_accelTable = wxAcceleratorTable();
#endif
	}
};

BOOL		InitMenuSystem();                                                
                                                
void		DeinitMenuSystem();

BOOL		DestroyCamMenu(MenuItem *CamMenu);

BOOL 		DestroyWinMenu(wxMenu* WinMenu);

BOOL		IsMenuCommand( wxCommandEvent& event );

BOOL		PerformMenuCommand( wxCommandEvent& event );

BOOL		UpdateMenu(wxMenu*);

MenuItem 	*SetupDefaultMenu();

MenuItem 	*SetupSharedMenu();
                                                
wxCamMenuBar* ConvertToWinMenu(MenuItem* CamMenu);

wxMenu		*CreatePopup(MenuItem* CamSubMenu);

MenuItem 	*GetMenuItem(UINT32 menuId, BOOL* pShowHotKeysFlag = NULL);

BOOL		FindMenu(MenuItem **TargetMenu, wxMenu* pMenu, BOOL* pShowHotKeysFlag = NULL);

BOOL		CreateContextMenu(MenuItem* pContextMenu);
BOOL		DestroyContextMenu();
MenuItem*	GetCurrentContextMenu();

MenuItem*	GetMainMDIMenu();
BOOL		UpdatePlugInsWinMenu(MenuItem* pPlugInsMenu);
BOOL 		DestroyWinMenuMFC(wxMenu* pWinMenu);

// shhh! Global Variables - Standard Camelot Menus

extern wxCamMenuBar*	WinDefMenu;						//Windows Menus
extern wxCamMenuBar*	WinMDIMenu;
extern wxMenu*			WinContextMenu;					// Pointer to current context-sensitive menu

// these define the range of valid menu IDs for automatic ID creation
const	UINT32 AUTO_MENU_ID_MIN = 1000;
const	UINT32 AUTO_MENU_ID_MAX = 2000;

#endif
