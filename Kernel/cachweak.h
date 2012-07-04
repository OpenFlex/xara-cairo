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


#ifndef INC_OBJECTCACHEWEAKEST
#define INC_OBJECTCACHEWEAKEST

#include "objcache.h"


/***********************************************************************************************

>	class ObjectCacheWeakest : public ObjectCacheWeakest

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/01/97
	Purpose:	Provides a delete algorithm cache replacement policy according to the size
				of the object.
	See also:	class ObjectCache
***********************************************************************************************/

class ObjectCacheWeakest : public ObjectCache 
{
	// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(ObjectCacheWeakest);

public:

	ObjectCacheWeakest(); 
	ObjectCacheWeakest(UINT32 ceiling);
	~ObjectCacheWeakest();

protected:

	// override the Delete() base class function
	BOOL DeleteObject();

};


#endif
