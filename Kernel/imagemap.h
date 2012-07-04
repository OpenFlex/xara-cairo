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

// Imagemap

#ifndef IMAGEMAPLIST
#define IMAGEMAPLIST

#include "overlist.h"
//#include "docrect.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "flatfact.h"

class CCLexFile;
class Path;

/********************************************************************************************

>	class Imagemap : public OverrideList

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	This is a list of clickable areas.

				The clickable areas can be any of the following objects:

				ImagemapClickableCircle
				ImagemapClickableRectangle
				ImagemapClickablePolygon

				All these classes are derived from the ImagemapClickableArea
				class, which is in turn derived from ListItem.

				This imagemap class also has the ability to write itself out
				to a file, via the Write function.

********************************************************************************************/


class Imagemap : public OverrideList
{
	CC_DECLARE_DYNAMIC(Imagemap)
	
	//Constructor
public:
	Imagemap();
	
	//Destructor
public:
	~Imagemap();

	//Operations (functions which are called from other objects)

	//Adding to the imagemap
public:
	void AddRectangle(DocRect rectToAdd, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);
	void AddCircle(Path* pthToAdd, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);
	void AddPolygon(Path* pthToAdd, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);

	//Writing out the imagemap
public:
	INT32 Write(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);
};



#endif // IMAGEMAPRENDERREGION

