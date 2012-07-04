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


// Implements bits of the stuff defined in cxflists.h

#include "camtypes.h"
//#include "camfiltr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "cxflists.h"
//#include "group.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "cxftags.h"

/***********************************************************************************************

>	CXaraFileTextStoryGroupRefListItem::~CXaraFileTextStoryGroupRefListItem();

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/8/96
	Inputs:		-
	Returns:	-
	Purpose:	Destroys every last fragmented morsal of this pathetic excuse for an object.

				If it has a group, its children are deleted via CascadeDelete(), then the group
				itself is deleted

***********************************************************************************************/

// WEBSTER - markn 31/1/97
// Replaced with general system
/*
CXaraFileTextStoryGroupRefListItem::~CXaraFileTextStoryGroupRefListItem()
{
	if (pNodeGroup != NULL)
	{
		pNodeGroup->CascadeDelete();
		delete pNodeGroup;
		pNodeGroup = NULL;
	}
}
*/

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

/***********************************************************************************************

>	CXaraFileNodeGroupRefListItem::~CXaraFileNodeGroupRefListItem();

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/1/97
	Inputs:		-
	Returns:	-
	Purpose:	Destroys every last fragmented morsal of this pathetic excuse for an object.

				If it has a group, its children are deleted via CascadeDelete(), then the group
				itself is deleted

  				WEBSTER - markn 29/1/97
				Part of the general form of the system used to convert text to outlines in v1.5

***********************************************************************************************/

CXaraFileNodeGroupRefListItem::~CXaraFileNodeGroupRefListItem()
{
	if (pNodeGroup != NULL)
	{
		pNodeGroup->CascadeDelete();
		delete pNodeGroup;
		pNodeGroup = NULL;
	}
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

/***********************************************************************************************

>	InsertLevelStackItem::InsertLevelStackItem(BaseCamelotFilter* pThisFilter)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/9/96
	Inputs:		pThisFilter = ptr to the filter this item is used by
	Returns:	-
	Purpose:	The default constructor

***********************************************************************************************/

InsertLevelStackItem::InsertLevelStackItem(BaseCamelotFilter* pThisFilter)
{ 
	NumNodesInserted	= 0; 
	pLastInsertedNode	= NULL; 
	pLastHandler		= NULL; 
	LastHandledTag		= TAG_UNDEFINED;
	pFilter				= pThisFilter;
	LastNodeInformedChildrenComplete = FALSE;

	ERROR3IF(pFilter == NULL,"pFilter is NULL");
}

/***********************************************************************************************

>	BOOL InsertLevelStackItem::SetLastInsertedNode(Node* pNode)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/9/96
	Inputs:		pNode = ptr to node just inserted into the tree
	Returns:	TRUE if ok, FALSE if a failure has ocurred
	Purpose:	Sets the last inserted node of this tree

***********************************************************************************************/

BOOL InsertLevelStackItem::SetLastInsertedNode(Node* pNode)
{
	ERROR3IF(pNode == NULL,"pNode is NULL");

	if (pNode != NULL)
	{
		if (pNode->FindPrevious() == pLastInsertedNode)
		{
			if (!InformLastInsertedNodeChildrenComplete())
				return FALSE;
		}

		pLastInsertedNode = pNode;
		LastNodeInformedChildrenComplete = FALSE;

		IncNumNodesInserted();			// Inc the number of nodes on this level
	}

	return TRUE;
}

/***********************************************************************************************

>	BOOL InsertLevelStackItem::InformLastInsertedNodeChildrenComplete()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/9/96
	Inputs:		-
	Returns:	TRUE if ok, FALSE if a failure has ocurred
	Purpose:	Tells the last inserted node that its children are complete

***********************************************************************************************/

BOOL InsertLevelStackItem::InformLastInsertedNodeChildrenComplete()
{
	ERROR3IF(pFilter == NULL,"pFilter is NULL");

	if (!LastNodeInformedChildrenComplete && pLastInsertedNode != NULL && pFilter != NULL)
	{
		if (!pFilter->ReadPostChildren(pLastInsertedNode))
			return FALSE;

		LastNodeInformedChildrenComplete = TRUE;
	}

	return TRUE;
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

/***********************************************************************************************

>	InsertLevelStack::InsertLevelStack();

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/9/96
	Inputs:		-
	Returns:	-
	Purpose:	The default constructor

***********************************************************************************************/

InsertLevelStack::InsertLevelStack()
{
	InsertLevel = 0;
}

/***********************************************************************************************

>	InsertLevelStack::~InsertLevelStack();

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/9/96
	Inputs:		-
	Returns:	-
	Purpose:	The default destructor - deletes all the list's items

***********************************************************************************************/

InsertLevelStack::~InsertLevelStack()
{
	DeleteAll();
}

/***********************************************************************************************

>	void InsertLevelStack::Add(InsertLevelStackItem* pItem)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/9/96
	Inputs:		pItem
	Returns:	-
	Purpose:	Adds the item to the top of the stack

***********************************************************************************************/

void InsertLevelStack::Add(InsertLevelStackItem* pItem)
{
	InsertLevel++;
	AddTail(pItem);
}

/***********************************************************************************************

>	InsertLevelStackItem* InsertLevelStack::Get()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/9/96
	Inputs:		-
	Returns:	ptr to a InsertLevelStackItem 
	Purpose:	Returns a ptr to the item on the top of the stack, without removing it

***********************************************************************************************/

InsertLevelStackItem* InsertLevelStack::Get()
{
	return (InsertLevelStackItem*)List::GetTail();
}

/***********************************************************************************************

>	InsertLevelStackItem* InsertLevelStack::Pop()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/9/96
	Inputs:		-
	Returns:	ptr to a InsertLevelStackItem 
	Purpose:	Removes the item from the top of the stack, and returns a ptr to it

***********************************************************************************************/

InsertLevelStackItem* InsertLevelStack::Pop()
{
	if (InsertLevel == 0)
	{
		ERROR3("InsertLevel == 0");
		return NULL;
	}

	InsertLevel--;

	return (InsertLevelStackItem*)List::RemoveTail();
}

