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
#include "objcache.h"
#include "cache.h"
#include <time.h>
#include <stdlib.h>




CC_IMPLEMENT_DYNCREATE(ObjectCache, CCObject)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


#define MYTRACE if(IsUserName("Olivier")) TRACE

/*********************************************************************************************

>	ObjectCache::ObjectCache()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	default constructor for ObjectCache
	Note:		
	SeeAlso:	
**********************************************************************************************/
ObjectCache::ObjectCache()
{
	// Compute the available amount of memory
	/*TunedMemory* pTuneMem = GetTunedMemManager();
	if (pTuneMem != NULL)
		Ceiling = pTuneMem->GetAvailableTunedMem();*/

	m_NumObjects	= 0;
	m_HandleFactory = 1;
	m_CurrentSize	= 0;
}

/*********************************************************************************************

>	ObjectCache::ObjectCache(UINT32 ceiling)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	constructor for ObjectCache, set the cache size.
	Inputs:		ceiling: the amount of memory available for the cache
	Note:		
	SeeAlso:	
**********************************************************************************************/
ObjectCache::ObjectCache(UINT32 ceiling)
{
	m_Ceiling		= ceiling;
	m_NumObjects	= 0;
	m_HandleFactory = 1;	// we don't start from 0 
	m_CurrentSize	= 0;
}

/*********************************************************************************************

>	ObjectCache::~ObjectCache()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	destructor for ObjectCache
	Note:		
	SeeAlso:	
**********************************************************************************************/
ObjectCache::~ObjectCache()
{}


/*********************************************************************************************

>	void ObjectCache::SetMaxCacheSize(UINT32 NewCeiling)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Inputs:		NewCeiling: The size of the new ceiling
	Purpose:	dynamically change the size (in bytes) of the Cache.
	Note:		
	SeeAlso:	
**********************************************************************************************/

BOOL ObjectCache::SetMaxCacheSize(UINT32 NewCeiling)
{
//	MYTRACE( _T("ObjectCache::SetMaxCacheSize()\n"));
	while (m_CurrentSize > NewCeiling)
	{
		if(!DeleteObject())
			break;
	}
	m_Ceiling = NewCeiling;
	return TRUE;
}


/*********************************************************************************************

>	CACHE_HANDLE ObjectCache::Add(CachedObject *pObj)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/01/97
	Inputs:		pObj: the Object to cache
	Purpose:	Add an object in the Hash table of the cache
	Note:		
	SeeAlso:	
**********************************************************************************************/

CACHE_HANDLE ObjectCache::Add(CachedObject *pObj)
{
	ERROR3IF(pObj==NULL, "Error: the object to cache can't be NULL");

	if (pObj == NULL)
		return 0;

//	MYTRACE( _T("ObjectCache::Add()\n"));

	// if we can make room for the object then assign the object a unique handle and cache it
	if (MakeRoomFor(pObj))
	{
		CACHE_HANDLE hObj = m_HandleFactory++;

		pObj->StoreHandle(hObj);		// store the CachedObject Handle
		m_NumObjects++;					// Increase the number of objects
		m_CurrentSize += pObj->GetSize();	// Increase the space used
		m_ObjectMap[hObj] = pObj;	// set the object in the hash table
		return hObj;
	}

	return 0;
}


/*********************************************************************************************

>	BOOL ObjectCache::MakeRoomFor(CachedObject* pObj)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/01/97
	Inputs:		pObj: The object to add in the cache
	Returns:	TRUE if succesful, FALSE otherwise
	Purpose:	make room for another object by deleting old objects if the cache is full
	Note:		
	SeeAlso:	
**********************************************************************************************/

BOOL ObjectCache::MakeRoomFor(CachedObject* pObj)
{
	ERROR3IF(pObj==NULL, "Error: the object to cache can't be NULL");

	if (pObj == NULL)
		return FALSE;

	// is there room in the cache or do we have to free some memory ?
	if (pObj->GetSize() + m_CurrentSize <= m_Ceiling)
		return TRUE;	// enough room

	// is the cache big enough ? 
	if (pObj->GetSize() > m_Ceiling)
		return FALSE;	// the object is bigger than the cache size

	// Scan the cache deleting objects until there is room
	BOOL EnoughRoom = (pObj->GetSize() + m_CurrentSize <= m_Ceiling);
	do
	{
		BOOL ObjectDeleted = DeleteObject();

		EnoughRoom = (pObj->GetSize() + m_CurrentSize <= m_Ceiling);

		if(!ObjectDeleted && !EnoughRoom)
			return FALSE;		// no room and no deleted objects 
	}
	while (!EnoughRoom);

	return TRUE;
}


/*********************************************************************************************

>	CachedObject *ObjectCache::LookUp(CACHE_HANDLE hObj)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/01/97
	Purpose:	LookUp in the hash table
	Returns:	return a pointer to the object found, NULL otherwise
	Note:		
	SeeAlso:	
**********************************************************************************************/

CachedObject *ObjectCache::LookUp(CACHE_HANDLE hObj)
{
//	void* pObjMap = NULL;

	std::map<WORD, PVOID>::iterator iter = m_ObjectMap.find( hObj );
	if( m_ObjectMap.end() != iter  )
		return (CachedObject *)iter->second;

	return NULL;
}


/*********************************************************************************************

>	BOOL ObjectCache::Remove(CACHE_HANDLE hObj)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/01/97
	Inputs:		hObj: the object handle
	Returns:	TRUE if success, FALSE otherwise
	Purpose:	Remove a key from the hash table
	Note:		
	SeeAlso:	
**********************************************************************************************/

BOOL ObjectCache::Remove(CACHE_HANDLE hObj)
{
	if( m_ObjectMap.erase( hObj ) )
		return TRUE;

	return FALSE;
}


/*********************************************************************************************

>	BOOL ObjectCache::DeleteObject()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/01/97
	Purpose:	virtual function. This is the base class delete function. All algorithms
				are implemented in the derived classes such as ObjectCacheRandom...etc.
	Note:		
	SeeAlso:	
**********************************************************************************************/

BOOL ObjectCache::DeleteObject()
{
	return TRUE;
}


