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

// Merge list item

#ifndef OVERRIDELIST
#define OVERRIDELIST

#include "overitem.h"	//OverrideListItem

/***********************************************************************************************

>	class OverrideList

  Author:	Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
  Created:	21/4/97
  Purpose:	An override list contains items that can override each other.

			For example, imagine we are building a list of clickable areas in
			an imagemap. Our list of clickable areas already contains
			a rectangle with bottom left corner (0,0) and top right corner (200, 200),
			that links to the URL "http://www.xara.com".

			Now we add another clickable rectangle to the imagemap. This rectangle
			has bottom left corner (50,50) and top right corner (100,100) and also
			links to "http://www.xara.com".

			But our first rectangle is contained within our second rectangle! There
			is no need for the second rectangle at all.
			
			It is clear that the first rectangle overrides the second, so the 
			second rectangle should not be added to the list.

			Now imagine the small rectangle is already in the list and the large
			rectangle is added.

			Again, the large rectangle overrides the small one. So the large 
			rectangle should be added to the list and the smaller rectangle
			should be deleted.

			So, this class works as follows.

			When an OverrideListItem is added to this list, this function compares
			the item with every other item in the list. 
			
			It does this by calling either the function
			OverrideListItem::OverrideFromAbove (if the item in the list is before
			the item being added) or OverrideListItem::OverrideFromBelow(if the
			item in the list is below the item being added).

			Then:

			a. If an item in the list overrides the item being added, then the
				new item is not added to the list.

			b. If the item being added overrides an item in the list, then the
				new item is added and the item in the list is deleted.

***********************************************************************************************/

class OverrideList : public List
{   
	CC_DECLARE_DYNAMIC( OverrideList )

	//Constructor
public:
	OverrideList();

	//Overridden functions
public:
	virtual void AddHead( OverrideListItem* );	
	virtual void AddTail( OverrideListItem* );

	virtual LISTPOS InsertBefore(LISTPOS here, OverrideListItem* item);
	virtual ListItem *InsertBefore(OverrideListItem* here, OverrideListItem* item);

	virtual LISTPOS InsertAfter(LISTPOS here, OverrideListItem* item);
	virtual ListItem *InsertAfter(OverrideListItem* here, OverrideListItem* item);

	//Toolkit functions
protected:
	virtual BOOL CompareWithItemsAbove(OverrideListItem* pliStartPos, OverrideListItem* pliToInsert);
	virtual BOOL CompareWithItemsBelow(OverrideListItem* pliStartPos, OverrideListItem* pliToInsert);



};



#endif // OVERRIDELIST

