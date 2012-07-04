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



#ifndef INC_HTMLLIST
#define INC_HTMLLIST

//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]


#define HTMLTAG_TYPE	INT32


///////////////////////////////////////////////////////////////////////
////////		class HTMLFileList and HTMLFileListItem			///////
///////////////////////////////////////////////////////////////////////	

/********************************************************************************************
>	class HTMLFileListItem : public ListItem

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/04/97
	Purpose:	Item to add in the list
	SeeAlso:	ListItem
********************************************************************************************/

class HTMLFileListItem : public ListItem
{
	CC_DECLARE_DYNAMIC(HTMLFileListItem)

public:
	HTMLFileListItem(String_256 Filename, HTMLTAG_TYPE TagId, BOOL Center);
	String_256 GetFileName();
	HTMLTAG_TYPE GetTagId();
	BOOL IsCenter();
	void MyPrint();

private:
	BOOL m_IsCenter;	// this is used for formatting
	String_256 m_Filename;
	String_256 m_Path;
	HTMLTAG_TYPE m_TagId;

};


/********************************************************************************************
>	class HTMLFileList : public List

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/04/97
	Purpose:	List of Item
	SeeAlso:	List
********************************************************************************************/

// list of all bitmaps
class HTMLFileList : public List
{
	CC_DECLARE_DYNAMIC(HTMLFileList)

public:
	BOOL Add(HTMLFileListItem* pItem);
	BOOL IsAlreadyInList(HTMLFileListItem* pItem);
	

};

#endif	//INC_HTMLLIST
