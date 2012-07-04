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


#ifndef INC_OBJECTCACHE
#define INC_OBJECTCACHE

#include "cache.h"
//#include "afxcoll.h"	// CMapWordToPtr


/***********************************************************************************************

>	class ObjectCache : public ObjectCache

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	Base class for the cache. The cache replacement policy algorithms are implemented
				in the derived classes such as ObjectCacheRand...etc.

***********************************************************************************************/

class ObjectCache : public CCObject 
{
	// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(ObjectCache);

public:
	ObjectCache(); 
	ObjectCache(UINT32 ceiling);
	~ObjectCache();

	virtual CACHE_HANDLE Add(CachedObject *pObj);
	virtual CachedObject* LookUp(CACHE_HANDLE hObj);
	virtual BOOL Remove(CACHE_HANDLE hObj);
	virtual BOOL SetMaxCacheSize(UINT32 NewCeiling);

protected:
	UINT32 m_Ceiling;				// maximum size of the cache
	UINT32 m_CurrentSize;			// cached used
	WORD m_NumObjects;				// num of objects in the cache
	std::map<WORD, PVOID>	m_ObjectMap;	// hash table
	WORD m_HandleFactory;			// create a handle for the object to cache

	// Virtual functions. Overrided in the derived classes.
	virtual BOOL MakeRoomFor(CachedObject* pObj);
	virtual BOOL DeleteObject();
	
};


#endif
