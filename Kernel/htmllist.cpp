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



#include "camtypes.h" 
#include "htmllist.h"



DECLARE_SOURCE("$Revision: 751 $");

CC_IMPLEMENT_DYNAMIC(HTMLFileList, List)
CC_IMPLEMENT_DYNAMIC(HTMLFileListItem, ListItem)

#define new CAM_DEBUG_NEW


///////////////////////////////////////////////////////////////////////
////////		class HTMLFileList and HTMLFileListItem			///////
///////////////////////////////////////////////////////////////////////


/********************************************************************************************

>	HTMLFileListItem::HTMLFileListItem(String_256 Filename, HTMLTAG_TYPE TagId, BOOL Center)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/04/97
	Inputs:		Filename - name of the file
				TagId - which tag ? (img, body...)
				Center - used for formatting
	Returns:	
	Purpose:	HTMLFileListItem constructor. Create a new HTMLFileListItem.
	Errors:		

********************************************************************************************/

HTMLFileListItem::HTMLFileListItem(String_256 Filename, HTMLTAG_TYPE TagId, BOOL Center)
{
	m_Filename = Filename;
	m_TagId = TagId;
	m_IsCenter = Center;
}


/********************************************************************************************

>	String_256 HTMLFileListItem::GetFileName()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/04/97
	Inputs:		
	Returns:	
	Purpose:	return the filename
	Errors:		

********************************************************************************************/

String_256 HTMLFileListItem::GetFileName()
{
	return m_Filename;
}


/********************************************************************************************

>	HTMLTAG_TYPE HTMLFileListItem::GetTagId()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/04/97
	Inputs:		
	Returns:	
	Purpose:	return the tag ID
	Errors:		

********************************************************************************************/

HTMLTAG_TYPE HTMLFileListItem::GetTagId()
{
	return m_TagId;
}


/********************************************************************************************

>	BOOL HTMLFileListItem::IsCenter()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/04/97
	Inputs:		
	Returns:	
	Purpose:	return the tag ID
	Errors:		

********************************************************************************************/

BOOL HTMLFileListItem::IsCenter()
{
	return m_IsCenter;
}



void HTMLFileListItem::MyPrint()
{
	if (IsUserName("Olivier"))
	{
		TRACE( _T("HTMLFileListItem::FileName = %s\n"), (TCHAR*)m_Filename);
		//TRACE( _T("HTMLFileListItem::TagId = %d\n"), m_TagId);
	}
}


/********************************************************************************************

>	BOOL HTMLFileList::Add(HTMLFileListItem* pItem)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/04/97
	Inputs:		pItem - Item to add in the list
	Returns:	
	Purpose:	add an element in the list
	See also:	AddTail()
	Errors:		

********************************************************************************************/

BOOL HTMLFileList::Add(HTMLFileListItem* pItem)
{
	//Graham 8/8/97: Is our item already in the list?
	if (IsAlreadyInList(pItem))
	{
		//Yes. So return FALSE
		return FALSE;
	}
	else
	{
		//No. So add it.
		AddTail(pItem);

		//And return TRUE
		return TRUE;
	}
}


/********************************************************************************************

>	BOOL HTMLFileList::IsAlreadyInList(HTMLFileListItem* pItem)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/04/97
	Inputs:		pItem - Item to check
	Returns:	TRUE if pItem is already in the list, FALSE otherwise.
	Purpose:	check whether pItem is already in the list or not
	See also:	
	Errors:		

********************************************************************************************/

BOOL HTMLFileList::IsAlreadyInList(HTMLFileListItem* pItem)
{
	// how many item in the list ?
	DWORD NbItem = GetCount();

	// is it already in the list
	if (NbItem != 0)
	{
		// first item of the list
		HTMLFileListItem* ListBitmaps = (HTMLFileListItem*)GetHead();
		if ((ListBitmaps->GetFileName()).IsIdentical(pItem->GetFileName()))
			return TRUE;

		// scan the list
		while(ListBitmaps = (HTMLFileListItem*)GetNext(ListBitmaps))
		{
			if ((ListBitmaps->GetFileName()).IsIdentical(pItem->GetFileName()))
				return TRUE;
		}
	}
	
	return FALSE;
}





