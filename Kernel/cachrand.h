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


#ifndef INC_OBJECTCACHERANDOM
#define INC_OBJECTCACHERANDOM

#include "objcache.h"


/***********************************************************************************************

>	class ObjectCacheRandom : public ObjectCache

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/01/97
	Purpose:	provides a random cache replacement policy
	See also:	class ObjectCache
***********************************************************************************************/

class ObjectCacheRandom : public ObjectCache 
{
	// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(ObjectCacheRandom);

public:

	ObjectCacheRandom(); 
	ObjectCacheRandom(UINT32 ceiling);
	~ObjectCacheRandom();

protected:

	// override the ObjectCache function
	BOOL DeleteObject();

};


#endif
