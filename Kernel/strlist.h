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

#ifndef STRINGLISTITEM
#define STRINGLISTITEM


/********************************************************************************************

>	class StringListItem : public ListItem

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	A String_256 in a list item

********************************************************************************************/

class StringListItem : public ListItem
{
	CC_DECLARE_DYNAMIC(StringListItem)

	//Constructors
public:
	StringListItem();
	StringListItem(const String_256& strToCopy);

	//Access functions
public:
	String_256& GetString()
	{
		return m_String;
	}

	void SetString(const String_256& strToSet)
	{
		m_String=strToSet;
	}
	
	//Member variable
public:
	String_256 m_String;
};

#endif // STRINGLISTITEM

