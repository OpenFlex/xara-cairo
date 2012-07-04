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

#ifndef INC_OBJECTCACHEFIFO
#define INC_OBJECTCACHEFIFO

#include "objcache.h"


/***********************************************************************************************

>	class ObjectCacheFIFO : public ObjectCache

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/01/97
	Purpose:	provides a FIFO cache replacement policy
	See also:	class ObjectCache
***********************************************************************************************/

class ObjectCacheFIFO : public ObjectCache
{
	// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(ObjectCacheFIFO);

public:

	ObjectCacheFIFO(); 
	ObjectCacheFIFO(UINT32 ceiling);
	~ObjectCacheFIFO();

protected:
	WORD m_first;		// keep track of the first object handle 

	// override the ObjectCache function
	virtual BOOL DeleteObject();

};


#endif
