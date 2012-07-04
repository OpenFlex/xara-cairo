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

#ifndef INC_PATHNMEX
#define INC_PATHNMEX

//#include "pathname.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class PathNameEx: public PathName

	Author:		Adrian_Stoicar (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/12/96
	Purpose:	Extended pathname class, having some extra features we needed in Webster:
						- allows access to the drivename
						- it can create a directory path on the storage medium if not present.
				
	SeeAlso:	PathName

********************************************************************************************/

class PathNameEx : public PathName
{
public:
	PathNameEx();
	BOOL CreateLocation(); 
	PathNameEx(const PathName& rPath) : PathName(rPath) {}	
	PathNameEx(const String_256& strPath) : PathName(strPath) {}
	inline const String_256& GetDrive() { return drivename;}
	inline BOOL Remove() { return RemoveRecursively(GetPath());}
protected:
	static BOOL RemoveRecursively(const String_256& rPath);
};

#endif
