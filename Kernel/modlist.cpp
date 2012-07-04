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

#include "camtypes.h"

#include "module.h"
#include "modlist.h"
#include "oilmods.h"	// for pOILModule.

CC_IMPLEMENT_MEMDUMP(ModuleListItem, ListItem)
CC_IMPLEMENT_MEMDUMP(ModuleList, List)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	ModuleListItem(Module *pNewModule, OILModule *pNewOILModule)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Inputs:		NewModule - The module to fill in the list item with.
				pNewOILModule - pointer to the OILModule object to associate with this
				module.
	Outputs:	-
	Returns:	-
	Purpose:	Create a new ModuleListItem with the module pointer and info fields
				filled in.  The info fields are filled in by interrogating the module.
	Errors:		-

********************************************************************************************/

ModuleListItem::ModuleListItem(Module *pNewModule, OILModule *pNewOILModule)
{
	m_Initialised = FALSE;
	pNewModule->Describe( &m_ModInfo );
	m_pModule = pNewModule;
	m_pOILModule = pNewOILModule;
}

/********************************************************************************************

>	ModuleListItem::~ModuleListItem()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/7/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroys a ModuleListItem.  Deletes the module contained within it.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ModuleListItem::~ModuleListItem()
{
	delete m_pModule;
	m_pModule = NULL;
	
	if( NULL != m_pOILModule )
	{
//		PORTNOTETRACE("other","ModuleListItem::~ModuleListItem - m_pOILModule NOT deleted");
//#ifndef EXCLUDE_FROM_XARALX
		delete m_pOILModule;
//#endif
		m_pOILModule = NULL;
	}
}

/********************************************************************************************

>	ModuleList::~ModuleList

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/7/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroys a module list, destroying all modules in the list too.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ModuleList::~ModuleList()
{
	// Call destructors on all objects in the list
	
	ModuleListItem *Item = (ModuleListItem *) RemoveHead();
	
	while (Item != NULL)
	{
		// Delete the list item
		delete Item;
		
		// Try the next item
		Item = (ModuleListItem *) RemoveHead();
	}

}

/********************************************************************************************

>	ModuleListItem *ModuleList::Add(Module *pNewModule, OILModule *pNewOILModule)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Inputs:		pNewModule - pointer to the module to add into the list.
				pNewOILModule - pointer to the OILModule object to associate with this
				module.
	Outputs:	-
	Returns:	Pointer to the new item in the list if the module was successfully added,
				NULL otherwise.
	Purpose:	Safe addition of modules to the kernel's list of known modules.  A module
				will only be added if its ID has not already been used.
	Errors:		-
	SeeAlso:	ModuleListItem

********************************************************************************************/

ModuleListItem *ModuleList::Add(Module *pNewModule, OILModule *pNewOILModule)
{
	// Construct a tentative list item.
	ModuleListItem *NewItem = new ModuleListItem(pNewModule, pNewOILModule);
	if (NewItem == NULL)
		return NULL;
		
	// Fill in the OILModule pointer with the pointer provided by the caller.
	NewItem->m_pOILModule = pNewOILModule;
	
	// Interrogate module about itself.
	if( NewItem->m_ModInfo.ID == MODULEID_INVALID )
	{
		// Invalid ID - discard new list item and abort.
		NewItem->m_pModule = NULL;							// dont delete the module
		delete NewItem;
		return NULL;
	}
	
	
	// Search list to make sure this ID is not already in use.
	ModuleListItem *Item = (ModuleListItem *) GetHead();
	
	while (Item != NULL)
	{
		if( Item->m_ModInfo.ID == NewItem->m_ModInfo.ID )
		{
			// Found ID already in use - discard new list item and abort.
			NewItem->m_pModule = NULL;						// dont delete the module
			delete NewItem;
			return NULL;
		}
		
		// Try the next node in the list.
		Item = (ModuleListItem *) GetNext(Item);
	}
	
	// The ID is not already in use so add the module to the list.
	AddTail(NewItem);
	return NewItem;
}


