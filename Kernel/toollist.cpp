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

#include "toollist.h"
//#include "oiltool.h"


CC_IMPLEMENT_MEMDUMP(ToolListItem, ListItem);
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	ToolListItem(Tool *NewTool, UINT32 ParentID)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Inputs:		NewTool - Pointer to the tool to fill in the list item with.
				ParentID - Module ID of the module that provides this tool.
	Purpose:	Create a new ToolListItem with the tool pointer and info fields
				filled in.  The info fields are filled in by interrogating the tool.
				A new OILTool object is created for this tool, and linked in to the
				list item.
				The tool is linked to the ToolListItem via the Parent member variable, as
				this means it is easy to get hold of the tool's info (ToolInfo object)
				given a pointer to a tool (otherwise you have to do GetID() and call
				Tool::Find() to get the Tool info, which is a bit daft).

********************************************************************************************/

ToolListItem::ToolListItem(Tool *NewTool, UINT32 ParentID)
{
	m_fInitialised = FALSE;
	NewTool->Describe( &m_ToolInfo );
	m_ToolInfo.ParentModuleID = ParentID;
	m_pTool = NewTool;
	NewTool->Parent = this;
}

/********************************************************************************************

>	ToolListItem::~ToolListItem()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/7/93
	Purpose:	Destructor.  Deletes the associated Tool and OILTool objects.
	Errors:		Asserts if the Tool object is not valid (i.e. NULL)

********************************************************************************************/

ToolListItem::~ToolListItem()
{
	// m_pTool may be NULL if the tool didn't initialise properly, because the Add() function 
	// will 'de-install' the tool from this list item to stop it being deleted
	// prematurely.
	delete m_pTool;

	// m_pOILTool may be NULL if the 'new' failed so don't assert (and our 
	// SimpleCCObject::delete can handle 'delete NULL;').
//	delete m_pOILTool;
}


CC_IMPLEMENT_MEMDUMP(ToolList, List);

/********************************************************************************************

>	ToolList::~ToolList()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/7/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroys a ToolList object.  Deletes the Tool and OILTool objects contained
				in the list items, and deletes the list items themselves.
	Errors:		-
	SeeAlso:	~ToolListItem

********************************************************************************************/

ToolList::~ToolList()
{
	// Call destructors on all objects in the list
	
	ToolListItem *Item = (ToolListItem *) RemoveHead();
	
	while (Item != NULL)
	{
		// Delete the list item
		delete Item;
		
		// Try the next item
		Item = (ToolListItem *) RemoveHead();
	}
}


/********************************************************************************************

>	ToolListItem *ToolList::Add(Tool *NewTool, UINT32 ParentID)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Inputs:		NewTool - pointer to the tool to add into the list.
				ParentID - Module ID of the module that provides this tool.
	Outputs:	-
	Returns:	Pointer to the new item in the list if the tool was successfully added,
				NULL otherwise.
	Purpose:	Safe addition of tools to the kernel's list of known tools.  A tool
				will only be added if its ID has not already been used.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ToolListItem *ToolList::Add(Tool *NewTool, UINT32 ParentID)
{
	// Construct a tentative list item
	ToolListItem *NewItem = new ToolListItem(NewTool, ParentID);
    if (NewItem == NULL)
    	goto AbnormalExit;
	
	// Create a new OIL tool for this node
//	NewItem->m_pOILTool = new OILTool(ParentID);
//	if (NewItem->m_pOILTool == NULL)
//  	goto AbnormalExit;
	
	// Interrogate tool about itself.
/*	if (NewItem->ToolInfo.ID == TOOLID_INVALID)
    	goto AbnormalExit;
	
	
	// Search list to make sure this ID is not already in use.
	// (If I use one line initialisation the compiler complains that the gotos avoid it.)
	ToolListItem *Item;
	Item = (ToolListItem *) GetHead();
	
	while (Item != NULL)
	{
		if (Item->ToolInfo.ID == NewItem->ToolInfo.ID)
			// Found ID already in use - discard new list item and abort.
			goto AbnormalExit;
		
		// Try the next node in the list.
		Item = (ToolListItem *) GetNext(Item);
	}
*/	
	// The ID is not already in use so add the tool to the list.
	AddTail(NewItem);
	return NewItem;
	
	// Abnormal exit - clean up and return a NULL pointer to indicate it didn't work.
AbnormalExit:
	// Set Tool pointer to NULL to avoid it being deleted by the ToolListItem's destructor, because
	// the caller is not expecting this tool to be deleted from under its feet.
	NewItem->m_pTool = NULL;

	// Delete the ToolListItem
	delete NewItem;

	return NULL;
}


