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

// Imagemap

#ifndef OVERRIDELISTITEM
#define OVERRIDELISTITEM

//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class OverrideListItem : public ListItem

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	An item in an OverrideList. See class OverrideList for an
				explanation.

********************************************************************************************/

class OverrideListItem : public ListItem
{
	CC_DECLARE_DYNAMIC(OverrideListItem)

	//Override functions
public:
	virtual BOOL OverrideFromAbove(OverrideListItem* pliOther)
	{
		return FALSE;
	}

	virtual BOOL OverrideFromBelow(OverrideListItem* pliOther)
	{
		return FALSE;
	}

	//IsA functions
public:
	virtual BOOL IsAClickableArea()
	{
		return FALSE;
	}
};



#endif // OVERRIDELISTITEM

