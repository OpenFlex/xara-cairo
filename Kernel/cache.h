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


#ifndef INC_CACHEDOBJECT
#define INC_CACHEDOBJECT

// handle for the Cache
#define CACHE_HANDLE WORD


/***********************************************************************************************

>	class CachedObject : public CCObject

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Purpose:	All objects that we want to add to the ObjectCache must be derived from
				a CachedObject base class.

***********************************************************************************************/

class CachedObject : public CCObject
{
	// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(CachedObject);

public:
	CachedObject();
	CachedObject(INT32 size);
	CachedObject(BOOL immortal, UINT32 size);
	virtual ~CachedObject(); 

	BOOL StoreHandle(CACHE_HANDLE Handle);
	virtual UINT32 GetSize() { return m_Size; }
	virtual UINT32 GetChanceOfSurvival() { return (GetSize()); }

	BOOL IsImmortal(){ return m_Immortal; }

protected:
	virtual BOOL SetSize(UINT32 size);

private:
	UINT32 m_Size;				// Size of the object
	BOOL m_Immortal;			// TRUE or FALSE
	CACHE_HANDLE m_hObj;		// Handle of the object

};



/***********************************************************************************************

>	class DummyCachedObject : public CachedObject

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/01/97
	Purpose:	A dummy class to test the cacheobject

***********************************************************************************************/

#if _DEBUG	// only in debug build

class DummyCachedObject : public CachedObject
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(DummyCachedObject);

public:
	DummyCachedObject();
	DummyCachedObject(INT32 size);
	DummyCachedObject(BOOL immortal, UINT32 size);
	~DummyCachedObject();

private:
	// all data members there
	INT32 m_DataMembers;

};

#endif


#endif
