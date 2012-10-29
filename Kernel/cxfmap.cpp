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
#include "cxfmap.h"

CC_IMPLEMENT_DYNAMIC(CXaraFileMapTagToHandler,CCObject);

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	CXaraFileMapTagToHandler::CXaraFileMapTagToHandler()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/8/96
	Purpose:	The default constructor
	SeeAlso:	-

********************************************************************************************/

CXaraFileMapTagToHandler::CXaraFileMapTagToHandler()
{
	pMap = NULL;
}

/********************************************************************************************

>	CXaraFileMapTagToHandler::~CXaraFileMapTagToHandler()

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/8/96
	Purpose:	The destructor
	SeeAlso:	-

********************************************************************************************/

CXaraFileMapTagToHandler::~CXaraFileMapTagToHandler()
{
	if (pMap != NULL)
		delete pMap;
}


/********************************************************************************************

>	void CXaraFileMapTagToHandler::Add(UINT32 Tag,CXaraFileRecordHandler* pHandler)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/8/96
	Imputs:		Tag = the tag that the given handler handles
				pHandler = ptr to a record handler
	Returns:	-
	Purpose:	Adds a map entry, associating the tag with the handler
	SeeAlso:	-

********************************************************************************************/

void CXaraFileMapTagToHandler::Add(UINT32 Tag,CXaraFileRecordHandler* pHandler)
{
	if (pHandler == NULL)
		return;

	if (pMap == NULL)
		pMap = new CMapLongToPtr;

	if (pMap != NULL)
		(*pMap)[INT32(Tag)] = (void *)pHandler;
}

/********************************************************************************************

>	CXaraFileRecordHandler* CXaraFileMapTagToHandler::LookUp(UINT32 Tag)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/8/96
	Imputs:		Tag = the tag
	Returns:	ptr to the handler for the given tag, or NULL if one can't be found
	Purpose:	Returns the handler associated with the given tag
	SeeAlso:	-

********************************************************************************************/

CXaraFileRecordHandler* CXaraFileMapTagToHandler::LookUp(UINT32 Tag)
{
	CXaraFileRecordHandler* pHandler = NULL;

	if (pMap != NULL)
	{
		CMapLongToPtr::iterator	iter = pMap->find( INT32(Tag) );
		if( iter == pMap->end() )
			return NULL;

		pHandler = (CXaraFileRecordHandler *)iter->second;
	}

	return pHandler;
}
