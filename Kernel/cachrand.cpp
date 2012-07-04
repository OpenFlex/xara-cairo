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
#include "cachrand.h"
#include "objcache.h"
#include "cache.h"
#include <time.h>
#include <stdlib.h>


DECLARE_SOURCE( "$Revision: 751 $" );


CC_IMPLEMENT_DYNCREATE(ObjectCacheRandom, ObjectCache)

#define new CAM_DEBUG_NEW


/*********************************************************************************************

>	ObjectCacheRandom::ObjectCacheRandom()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	default constructor for ObjectCache
	Note:		
	SeeAlso:	
**********************************************************************************************/
ObjectCacheRandom::ObjectCacheRandom()
{
	m_Ceiling = 0;
}

/*********************************************************************************************

>	ObjectCacheRandom::ObjectCacheRandom(UINT32 ceiling)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Inputs:		ceiling: max size of the cache.
	Purpose:	constructor for ObjectCacheRandom. Set the size of the cache.
	Note:		
	SeeAlso:	
**********************************************************************************************/
ObjectCacheRandom::ObjectCacheRandom(UINT32 ceiling)
{
	m_Ceiling = ceiling;
}

/*********************************************************************************************

>	ObjectCacheRandom::~ObjectCacheRandom()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	destructor for ObjectCache
	Note:		
	SeeAlso:	
**********************************************************************************************/
ObjectCacheRandom::~ObjectCacheRandom()
{
}


/*********************************************************************************************

>	BOOL ObjectCacheRandom::Delete()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/01/97
	Returns:	TRUE is success, FALSE otherwise.
	Purpose:	delete an object in the cache according a radom algorithm.
	Note:		
	SeeAlso:	
**********************************************************************************************/

BOOL ObjectCacheRandom::DeleteObject()
{
	if (m_NumObjects == 0)
		return FALSE;

	srand((unsigned)time(NULL));
	BOOL ok = FALSE;
	WORD Factory = 0;
	CachedObject* pObj = NULL;

	do
	{
		WORD hObj = rand() % m_HandleFactory + 1;		// generate a handle 
		Factory++;									// count the number of generated numbers

		pObj = LookUp(hObj);						// look up in the hash table
		ok = (pObj != NULL);

		if(ok)
		{
			Remove(hObj);							// remove from the hash table
			m_NumObjects--;							// decrease the number of objects
			m_CurrentSize -= pObj->GetSize();			// decrease the used space of cache
		}
	}
	while (!ok && Factory<=m_HandleFactory);

	//if(ok && Factory<=HandleFactory)
	if(ok)
	{
		delete pObj;
		pObj = NULL;
		return TRUE;
	}

	return FALSE;
}
