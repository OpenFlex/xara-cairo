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

//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]

CC_IMPLEMENT_DYNCREATE(ListItem, CCObject)


ListItem::ListItem()
{
	Next = NULL;
	Previous = NULL;
}

ListItem *ListItem::GetItem(void)
{
	return(this);
}

void ListItem::ClearPointers()
{
	Next = NULL;
	Previous = NULL;
}
