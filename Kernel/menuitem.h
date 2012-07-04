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
 *  */

#ifndef INC_MENUITEM
#define INC_MENUITEM

#include "cmdctrl.h" 

/********************************************************************************************
>   class OpMenuParam

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/20/2004

	Purpose:	Contain all the info transferred from the menu UI to Ops

	SeeAlso:	Operation::DoWithParam

********************************************************************************************/

class OpMenuParam : public OpParam
{
CC_DECLARE_DYNAMIC(OpMenuParam)

public:
	OpMenuParam() : OpParam()
	{
		strOpUnique = String( _T("") ); 
		strMenuText = String( _T("") ); 
		strMenuPath = String( _T("") );
	}

// Properties
public:
	String_256	strOpUnique;
	String_64	strMenuText;
	String_256	strMenuPath;

// Working vars
private:
};




/********************************************************************************************

>	Class MenuItem : public Control

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/6/93
	Purpose:	
		MenuItems are the things that appear in menus, but in camelot they are also the menus 
		themselves. The idea is that the menu system is a dynamically growing, living-thing 
		where all the elements are connected in a tree like structure. The elements of the 
		menu system or the nodes in the tree are MenuItems. MenuItems can therefore be 
		simple or composite i.e. a menu option or a sub menu. In windows there is a third 
		type of MenuItem: the separator, in our new improved menuing system separators will
		not be modelled as MenuItems. Instead a MenuItem may be specified as having a menu 
		separator following it.  
	Errors:		None yet.
	SeeAlso:	Control

********************************************************************************************/

class CCAPI MenuItem : public CmdControl
{ 

friend void UpdateWinMenu( CNativeMenu* pMenu, MenuItem* kernelMenu );

	CC_DECLARE_MEMDUMP(MenuItem);

public:
	virtual void PerformAction();

private:                        

	UINT32 ParentMenuId;
	List* SubMenuItems;
	String_256 Description;
	BOOL FollowedBySeparator;
	UINT32 m_nSelectedBitmapID;
	UINT32 m_nUnselectedBitmapID;
	OpMenuParam* pMenuParam;
	
public:
	
	MenuItem()
	  : ParentMenuId(0), SubMenuItems(0), FollowedBySeparator(FALSE),
	    m_nSelectedBitmapID(0), m_nUnselectedBitmapID(0), pMenuParam(0)
			{ /* empty */ }

	// new prototype, requires OpDescriptor only (almost)
	MenuItem(
			UINT32 parentMenuID,
			OpDescriptor* Owner,
			BOOL separator = FALSE
			);

	// new prototype for group MenuItem
	MenuItem(	const String_256& description, 
				UINT32 parentMenuID = 0,
				BOOL separator = FALSE
			);

    ~MenuItem();

	BOOL IsMenuItemGroup();
	BOOL IsFollowedBySeparator();
	BOOL IsCheckable();
	BOOL SetIsFollowedBySeparator(BOOL NewValue);

	BOOL UpdateControlState(BOOL AppendHotKeyName = TRUE);
	BOOL UpdateMenuState(BOOL AppendHotKeyNames = TRUE);

	UINT32 GetMenuId();
	UINT32 GetMenuItemParentId();
	UINT32 GetHelpId();
	String_256 GetMenuText();
	String_256* GetMenuDesc();
	String_32* GetOpToken();
	void SetMenuText(const String_256& strNewText) {Description=strNewText;}
	void SetMenuParam(OpMenuParam* pNewParam) {pMenuParam=pNewParam;}
	
	UINT32 GetMenuSelectedBitmapID();
	UINT32 GetMenuUnselectedBitmapID();

	MenuItem* GetFirstMenuItem();
	MenuItem* GetNextMenuItem(MenuItem* curItem);

	BOOL AddMenuItem(MenuItem *newItem);
	MenuItem* RemoveMenuItem(MenuItem* Item);

	static UINT32 AutomaticMenuID;
	static UINT32 GetNextAutomaticMenuID();
	static UINT32 GetAutomaticIDState();
	static BOOL SetAutomaticIDState(UINT32 newvalue);

	static const OpState DefaultMenuState;

private:
	void PopulateMenuParam();

};

#endif
