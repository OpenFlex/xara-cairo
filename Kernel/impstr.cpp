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
#include "impstr.h"

#include "cxftags.h"

CC_IMPLEMENT_DYNCREATE(ImportedString,	ListItem);
CC_IMPLEMENT_DYNAMIC(ImportedStringList,List);

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	ImportedString::ImportedString(TextChar* pChar,CXaraFileRecord* pRecord)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Inputs:		pChar   = ptr to a char node in the tree
				pRecord = ptr to string record that's been imported
	Returns:	-
	Purpose:	The constructor.

				pChar should point to a TextChar that's been inserted into the tree that contains
				the first character in the string.

				pRecord should point to the string record imported from the file.

				This constructor keeps a copy of the pChar address.
				It makes a copy of pRecord, so it's safe to delete pRecord after this call

	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ImportedString::ImportedString(TextChar* pChar,CXaraFileRecord* pRecord)
{
	ERROR3IF(pChar   == NULL,"pChar is NULL");
	ERROR3IF(pRecord == NULL,"pRecord is NULL");

	pFirstChar = pChar;
	pCopyOfStringRecord = NULL;

	if (pRecord != NULL)
	{
		pCopyOfStringRecord = pRecord->GetCopy();

		ERROR3IF(pRecord->GetTag() != TAG_TEXT_STRING,"The record is not a string record");
	}	
}

/********************************************************************************************

>	ImportedString::~ImportedString()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Inputs:		-
	Returns:	-
	Purpose:	The destructor
				It frees up the copy of the record it created at construction time.

	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ImportedString::~ImportedString()
{
	if (pCopyOfStringRecord != NULL)
		delete pCopyOfStringRecord;
}

/********************************************************************************************

>	CXaraFileRecord* ImportedString::GetRecord()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Inputs:		-
	Returns:	ptr to the string record
	Purpose:	Returns a ptr to the copy of the string record passed into the constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

CXaraFileRecord* ImportedString::GetRecord()
{
	return pCopyOfStringRecord;
}

/********************************************************************************************

>	TextChar* ImportedString::GetFirstChar()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Inputs:		-
	Returns:	ptr to the text char
	Purpose:	Returns a ptr to the text char passed into the constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

TextChar* ImportedString::GetFirstChar()
{
	return pFirstChar;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

/********************************************************************************************

>	void ImportedStringList::AddTail(ImportedString* pItem)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Inputs:		pItem = ptr to the ImportedString object
	Returns:	-
	Purpose:	Adds the string item to the list
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void ImportedStringList::AddTail(ImportedString* pItem)
{
	List::AddTail(pItem);
}

/********************************************************************************************

>	ImportedString* ImportedStringList::GetHead()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Inputs:		-
	Returns:	ptr to the head of the list
	Purpose:	Returns a ptr to the head of the list
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ImportedString* ImportedStringList::GetHead()
{
	return (ImportedString*)List::GetHead();
}

/********************************************************************************************

>	ImportedString* ImportedStringList::GetNext(ImportedString* pItem)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Inputs:		pItem = ptr to a ImportedString object in the list
	Returns:	ptr to the next itme in the list
	Purpose:	Returns a ptr to the next itme in the list
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ImportedString* ImportedStringList::GetNext(ImportedString* pItem)
{
	return (ImportedString*)List::GetNext(pItem);
}
