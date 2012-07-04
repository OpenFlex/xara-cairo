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


#ifndef INC_TOOLLIST
#define INC_TOOLLIST


//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]

//#include "tool.h" - in camtypes.h [AUTOMATICALLY REMOVED]
class OILTool;  		// #include "oiltool.h"

/********************************************************************************************

>	class ToolListItem : public ListItem

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Purpose:	Used by the kernel to hold information on a particular tool.  Contains
				a link to the OilTool object associated with the Tool.
	SeeAlso:	ToolList

********************************************************************************************/

class ToolListItem : public ListItem
{
	CC_DECLARE_MEMDUMP(ToolListItem);
	
public:
	// Constructor
	ToolListItem(Tool *NewTool, UINT32 ParentID);
	
	// Destructor (destroys associated Tool and OilTool)
	~ToolListItem();
	
	// Data fields
	BOOL 	 m_fInitialised; // Has this tool been initialised ok?
	ToolInfo m_ToolInfo;
	Tool    *m_pTool;
//	OILTool *m_pOILTool;
};

/********************************************************************************************

>	class ToolList : public List

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Purpose:	Used by the kernel to hold information on all the tools it currently
				knows about.  It has an overloaded Add function which will only add 
				tools if their ID has not already been used by another tool.
	SeeAlso:	ToolListItem

********************************************************************************************/

class ToolList : public List
{
	CC_DECLARE_MEMDUMP(ToolList);
public:
	// Destructor
	~ToolList();
	
	ToolListItem *Add(Tool *, UINT32 ParentID);
};


#endif
