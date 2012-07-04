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

// StringListItem class

#include "camtypes.h"
#include "strlist.h"

CC_IMPLEMENT_DYNAMIC(StringListItem, ListItem)

/********************************************************************************************

	StringListItem::StringListItem()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Inputs:		-
	Outputs:	-
	Purpose:	Default contructor
	
********************************************************************************************/

StringListItem::StringListItem()
{
	//Set our member variable to an empty string
	m_String.Empty();
}

/********************************************************************************************

	StringListItem::StringListItem(const String_256& strToCopy)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Inputs:		strToCopy	String to put into our member variable
	Outputs:	-
	Purpose:	Specific contructor
	
********************************************************************************************/

StringListItem::StringListItem(const String_256& strToCopy)
{
	m_String=strToCopy;
}

