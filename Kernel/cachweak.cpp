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
#include "cachweak.h"
#include "cache.h"
#include "objcache.h"




CC_IMPLEMENT_DYNCREATE(ObjectCacheWeakest, ObjectCache)

#define new CAM_DEBUG_NEW


/*********************************************************************************************

>	ObjectCacheWeakest::ObjectCacheWeakest()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	default constructor for ObjectCacheWeakest
	Note:		
	SeeAlso:	ObjectCache
**********************************************************************************************/
ObjectCacheWeakest::ObjectCacheWeakest()
{
	m_Ceiling = 0;
}

/*********************************************************************************************

>	ObjectCacheWeakest::ObjectCacheWeakest(UINT32 ceiling)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Inputs:		ceiling: size of the cache
	Purpose:	constructor for ObjectCacheWeakest
	Note:		
	SeeAlso:	
**********************************************************************************************/
ObjectCacheWeakest::ObjectCacheWeakest(UINT32 ceiling)
{
	m_Ceiling = ceiling;
}

/*********************************************************************************************

>	ObjectCacheWeakest::~ObjectCacheWeakest()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	destructor for ObjectCacheWeakest
	Note:		
	SeeAlso:	
**********************************************************************************************/
ObjectCacheWeakest::~ObjectCacheWeakest()
{
}


/*********************************************************************************************

>	BOOL ObjectCacheWeakest::Delete()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/01/97
	Returns:	TRUE if success
	Purpose:	Provides a delete alorithm according to the size of the object and an importance
				factor called "Immortal" (TRUE or FALSE). Bigger objects are deleted first,
				but an object which Immortal factor is set to TRUE will not be deleted.
	Note:		
	SeeAlso:	
**********************************************************************************************/

BOOL ObjectCacheWeakest::DeleteObject()
{
	if(m_NumObjects == 0)
		return FALSE;	// empty cache

	CachedObject* pWeakest = NULL;
	INT32 handle = 1;

	// Get the first non immortal object 
	while((pWeakest == NULL) && (handle<=m_HandleFactory))
	{
		pWeakest = LookUp(handle);
		if (pWeakest != NULL)
		{
			if (pWeakest->IsImmortal())		// it shouldn't be immortal
				pWeakest = NULL;
		}
		handle++;
	}

	if(pWeakest == NULL)
		return FALSE;						// all objects are immortal	

	// Get the size of the object
	UINT32 WeakestChance = pWeakest->GetSize();

	// save a copy of the handle
	WORD CurrentHandle = handle;

	// now look up for the biggest object that will be deleted from the cache.
	for(handle=1;handle<m_HandleFactory;handle++)
	{
		CachedObject* pWeakestTemp = LookUp(handle);
		if(pWeakestTemp != NULL)
		{
			if((pWeakestTemp->GetSize()>WeakestChance) && (!pWeakestTemp->IsImmortal()))
			{
				CurrentHandle = handle;
				pWeakest = pWeakestTemp;
				WeakestChance = pWeakest->GetSize();
			}
		}
	}

	// Delete the weakest Object
	m_NumObjects--;
	Remove(CurrentHandle);
	//Remove(pWeakest->GetHandle());			// Delete from the hash table
	m_CurrentSize -= pWeakest->GetSize();	// change the cache size
	delete pWeakest;

	return TRUE;
}
