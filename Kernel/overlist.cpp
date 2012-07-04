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

// Imagemap class

#include "camtypes.h"
#include "overlist.h"
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]



CC_IMPLEMENT_DYNAMIC(OverrideList, List)

/********************************************************************************************

	OverrideList::OverrideList()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Purpose:	Default constructor
	
********************************************************************************************/

OverrideList::OverrideList() : List()
{
}

/********************************************************************************************

	virtual void OverrideList::AddHead( OverrideListItem* poliToAdd)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Inputs:		poliToAdd	The item to add
				
	Returns:	-

	Purpose:	Compares this list item with all the items in the list,
				to find out whether they override this list item or
				whether this list item overrides them.

				If this list item overrides any items already present
				in the list, the items in the list are deleted and this
				list item is added.

				If any item in the list overrides this list item,
				this list item is not added to the list.

				This function simply calls the InsertBefore function.

  SeeAlso:		OverrideList::InsertBefore()
	
********************************************************************************************/

void OverrideList::AddHead( OverrideListItem* poliToAdd)
{
	if (poliToAdd==NULL)
	{
		ERROR2RAW("OverrideList::AddHead - NULL parameter");
		return;
	}

	//Get the first item in the list
	OverrideListItem* pliFirst=(OverrideListItem*) GetHead();

	//Was there anything in the list?
	if (pliFirst!=NULL)				 
	{
		//Yes. So call our InsertBefore function
		InsertBefore(pliFirst, poliToAdd);
	}
	else
	{
		//No. So we need do no special checking - simply insert
		//the list item
		List::AddHead(poliToAdd);
	}
	
}

/********************************************************************************************

	virtual void OverrideList::AddTail( OverrideListItem* poliToAdd)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Inputs:		poliToAdd	The item to add
				
	Returns:	-

	Purpose:	Compares this list item with all the items in the list,
				to find out whether they override this list item or
				whether this list item overrides them.

				If this list item overrides any items already present
				in the list, the items in the list are deleted and this
				list item is added.

				If any item in the list overrides this list item,
				this list item is not added to the list.

				This function simply calls the InsertAfter function.

  SeeAlso:		OverrideList::InsertAfter()
	
********************************************************************************************/

void OverrideList::AddTail( OverrideListItem* poliToAdd)
{
	if (poliToAdd==NULL)
	{
		ERROR2RAW("OverrideList::AddTail - NULL parameter");
		return;
	}

	//Get the last item in the list
	OverrideListItem* pliLast=(OverrideListItem*) GetTail();

	//Was there anything in the list?
	if (pliLast!=NULL)				 
	{
		//Yes. So call our InsertAfter function
		InsertAfter(pliLast, poliToAdd);
	}
	else
	{
		//No. So we need do no special checking - simply insert
		//the list item
		List::AddTail(poliToAdd);
	}

	//And add our item after it
	InsertAfter(pliLast, poliToAdd);
	
}

/********************************************************************************************

	virtual ListItem* OverrideList::InsertBefore(OverrideListItem* here, OverrideListItem* item);

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Inputs:		poliToAdd	The item to add
				
	Returns:	-

	Purpose:	Compares this list item with all the items in the list,
				to find out whether they override this list item or
				whether this list item overrides them.

				It does this by calling the function 
				OverrideListItem::OverrideFromBelow on all items
				below the insertion position, and MergeListItem::OverrideFromAbove
				on all items above the insertion position.

				If this list item overrides any items already present
				in the list, the items in the list are deleted and this
				list item is added.

				If any item in the list overrides this list item,
				this list item is not added to the list.

				This function simply calls the InsertBefore function.

  SeeAlso:		OverrideList::InsertBefore()
	
********************************************************************************************/

ListItem* OverrideList::InsertBefore(OverrideListItem* pliInsertPoint, OverrideListItem* pliToInsert)
{
	ERROR2IF(pliToInsert==NULL, NULL, "OverrideList::InsertBefore - NULL parameter");
		
	//This variable will tell us whether to insert pliToInsert
	//into the list
	BOOL fInsert=TRUE;

	//First compare pliToInsert with everything below pliInsertPoint in the list
	fInsert=CompareWithItemsBelow(pliInsertPoint, pliToInsert);

	//Now get the list item above pliInsertPoint
	OverrideListItem* pliTest=(OverrideListItem*) GetPrev(pliInsertPoint);

	//If there is anything above pliInsertPoint
	if (fInsert && pliTest!=NULL)
	{
		//Then test everything above pliInsertPoint
		fInsert=CompareWithItemsAbove(pliInsertPoint, pliToInsert);
	}

	//So, should we insert pliToInsert?
	if (fInsert)
		//Yes. So do it.
		return List::InsertBefore(pliInsertPoint, pliToInsert);
	else
		//No. So return an error value.
		return NULL;
	
}

/********************************************************************************************

	virtual ListItem* OverrideList::InsertBefore(OverrideListItem* here, OverrideListItem* item);

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Inputs:		poliToAdd	The item to add
				
	Returns:	-

	Purpose:	Compares this list item with all the items in the list,
				to find out whether they override this list item or
				whether this list item overrides them.

				This function simply calls the other InsertBefore override.
								
  SeeAlso:		OverrideList::InsertBefore()
	
********************************************************************************************/

LISTPOS OverrideList::InsertBefore(LISTPOS here, OverrideListItem* item)
{

	ERROR2IF(item==NULL, NULL, "OverrideList::InsertBefore - NULL parameter");
		

	//First find the list item at the position we have been given
	OverrideListItem* pliInsertionPoint=(OverrideListItem*) FindItem(here);

	//If we have not found it, return -1
	if (pliInsertionPoint==NULL)
		return -1;

	//Otherwise, call our other function to do the insertion
	OverrideListItem* pliResult=(OverrideListItem*) InsertBefore(pliInsertionPoint, item);

	//If we have been returned NULL, then return an error value
	if (pliResult==NULL)
		return -1;

	//Otherwise, find our newly returned list item in the list
	//and return it
	return FindPosition(pliResult);
	
}

/********************************************************************************************

	virtual ListItem* OverrideList::InsertAfter(OverrideListItem* here, OverrideListItem* item);

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Inputs:		poliToAdd	The item to add
				
	Returns:	-

	Purpose:	Compares this list item with all the items in the list,
				to find out whether they override this list item or
				whether this list item overrides them.

				It does this by calling the function 
				MergeListItem::OverrideFromBelow on all items
				below the insertion position, and MergeListItem::OverrideFromAbove
				on all items above the insertion position.

				If this list item overrides any items already present
				in the list, the items in the list are deleted and this
				list item is added.

				If any item in the list overrides this list item,
				this list item is not added to the list.

				This function simply calls the InsertBefore function.

  SeeAlso:		OverrideList::InsertBefore()
	
********************************************************************************************/

ListItem* OverrideList::InsertAfter(OverrideListItem* pliInsertPoint, OverrideListItem* pliToInsert)
{
	ERROR2IF(pliToInsert==NULL, NULL, "OverrideList::InsertAfter - NULL parameter");

	//This variable will tell us whether to insert pliToInsert
	//into the list
	BOOL fInsert=TRUE;

	//First compare pliToInsert with everything above pliInsertPoint in the list
	fInsert=CompareWithItemsAbove(pliInsertPoint, pliToInsert);

	//Now get the list item after pliInsertPoint
	OverrideListItem* pliTest=(OverrideListItem*) GetNext(pliInsertPoint);

	//If there is anything before pliInsertPoint
	if (fInsert && pliTest!=NULL)
	{
		//Then test everything before pliInsertPoint
		fInsert=CompareWithItemsBelow(pliInsertPoint, pliToInsert);
	}

	//So, should we insert pliToInsert?
	if (fInsert)
		//Yes. So do it.
		return List::InsertAfter(pliInsertPoint, pliToInsert);
	else
		//No. So return an error value.
		return NULL;


	
}

/********************************************************************************************

	virtual ListItem* OverrideList::InsertAfter(OverrideListItem* here, OverrideListItem* item);

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Inputs:		poliToAdd	The item to add
				
	Returns:	-

	Purpose:	Compares this list item with all the items in the list,
				to find out whether they override this list item or
				whether this list item overrides them.

				This function simply calls the other InsertAfter override.
								
  SeeAlso:		OverrideList::InsertAfter()
	
********************************************************************************************/

LISTPOS OverrideList::InsertAfter(LISTPOS here, OverrideListItem* item)
{
	ERROR2IF(item==NULL, 0, "OverrideList::InsertAfter - NULL parameter");

	//First find the list item at the position we have been given
	OverrideListItem* pliInsertionPoint=(OverrideListItem*) FindItem(here);

	//If we have not found it, return -1
	if (pliInsertionPoint==NULL)
		return -1;

	//Otherwise, call our other function to do the insertion
	OverrideListItem* pliResult=(OverrideListItem*) InsertAfter(pliInsertionPoint, item);

	//If we have been returned NULL, then return an error value
	if (pliResult==NULL)
		return -1;

	//Otherwise, find our newly returned list item in the list
	//and return it
	return FindPosition(pliResult);
	
}

/*****************************************************

  Toolkit functions

  ****************************************************/

/********************************************************************************************

	virtual BOOL OverrideList::CompareWithItemsAbove(OverrideListItem* pliStartPos, OverrideListItem* pliToInsert);

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Inputs:		pliStartPos		The position to start searching from
				pliToAdd		The list items to add
				
	Returns:	FALSE	if pliToAdd was overridden by another
						item in the list

				TRUE	if pliToAdd was not overridden

				Note that, if pliToAdd overrides another item in the list,
				this does not affect the result returned.

	Purpose:	Compares this list item with all the items 
				above pliStartPos, inclusive.
				
  SeeAlso:		OverrideList::InsertBefore(), OverrideList::After()
	
********************************************************************************************/

BOOL OverrideList::CompareWithItemsAbove(OverrideListItem* pliStartPos, OverrideListItem* pliToInsert)
{
	//This pointer will show the item we are looking at
	OverrideListItem* pliLook=pliStartPos;

	//While we are still looking at a valid item
	while (pliLook!=NULL)
	{
		//This will be the next item we look at
		//It's important to do this now - because we may delete pliLook in a moment
		OverrideListItem* pliNext=(OverrideListItem*) GetPrev(pliLook);

		//Does the item we are looking at override the item
		//we are about to insert?
		if (pliLook->OverrideFromAbove(pliToInsert))
		{
			//Yes. So return to say that we're not going to insert the
			//item
			return FALSE;
		}

		//Does the item we are about to insert override the item
		//we are looking at?
		if (pliToInsert->OverrideFromBelow(pliLook))
		{
			//Yes. So delete the item we are looking at.
			RemoveItem(pliLook);
			delete pliLook;
		}

		//And move on to the next item
		pliLook=pliNext;
	}

	//ANd return to say that pliToInsert has not been overridden
	return TRUE;
}

/********************************************************************************************

	virtual BOOL OverrideList::CompareWithItemsBelow(OverrideListItem* pliStartPos, OverrideListItem* pliToInsert)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/97
	Inputs:		pliStartPos		The position to start searching from
				pliToAdd		The list items to add
				
	Returns:	FALSE	if pliToAdd was overridden by another
						item in the list

				TRUE	if pliToAdd was not overridden

				Note that, if pliToAdd overrides another item in the list,
				this does not affect the result returned.

	Purpose:	Compares this list item with all the items 
				below pliStartPos, inclusive.
				
  SeeAlso:		OverrideList::InsertBefore(), OverrideList::After()
	
********************************************************************************************/

BOOL OverrideList::CompareWithItemsBelow(OverrideListItem* pliStartPos, OverrideListItem* pliToInsert)
{
	//This pointer will show the item we are looking at
	OverrideListItem* pliLook=pliStartPos;

	//While we are still looking at a valid item
	while (pliLook!=NULL)
	{
		//This will be the next item we look at
		//It's important to do this now - because we may delete pliLook in a moment
		OverrideListItem* pliNext=(OverrideListItem*) GetNext(pliLook);

		//Does the item we are looking at override the item
		//we are about to insert?
		if (pliLook->OverrideFromBelow(pliToInsert))
		{
			//Yes. So return to say that we're not going to insert the
			//item
			return FALSE;
		}

		//Does the item we are about to insert override the item
		//we are looking at?
		if (pliToInsert->OverrideFromAbove(pliLook))
		{
			//Yes. So delete the item we are looking at.
			RemoveItem(pliLook);
			delete pliLook;
		}
				
		//And move on to the next item
		pliLook=pliNext;
	}

	//And return to say that pliToInsert has not been overridden
	return TRUE;
}



	 	
