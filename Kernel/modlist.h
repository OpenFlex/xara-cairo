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


#ifndef INC_MODLIST
#define INC_MODLIST


//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class Module;		// #include "module.h"
class OILModule; 	// #include "oilmods.h"


/********************************************************************************************

>	class ModuleListItem : public ListItem

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Purpose:	Used by the kernel to hold information on a particular module.
	            
	            The pOILModule field is a pointer to the OILModule object associated with
	            the Module object in this list item.  The OILModule is used to provide OIL
	            specific facilities to a module.
				
	SeeAlso:	ModuleList; Module; ModInfo; OILModule

********************************************************************************************/

class ModuleListItem : public ListItem
{
	CC_DECLARE_MEMDUMP(ModuleListItem);

public:
	// Constructor
	ModuleListItem(Module *, OILModule *);
	
	// Destructor
	~ModuleListItem();
	
	// Data fields
	BOOL				m_Initialised;  // TRUE if the module in this item has been initialised
	ModInfo				m_ModInfo;
	Module			   *m_pModule;
	OILModule		   *m_pOILModule;
};

/********************************************************************************************

>	class ModuleList : public List

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Purpose:	Used by the kernel to hold information on all the modules it currently
				knows about.  It has an overloaded Add function which will only add 
				modules if their ID has not already been used by another module.
	SeeAlso:	ModuleListItem

********************************************************************************************/

class ModuleList : public List
{
	CC_DECLARE_MEMDUMP(ModuleList);

public:
	// Destructor
	~ModuleList();
	
	ModuleListItem *Add(Module *, OILModule *);
};


#endif
