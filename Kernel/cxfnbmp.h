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

/********************************************************************************************

>	cxfbmp.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/06/96
	Purpose:	Saving code for node bitmaps

********************************************************************************************/

#ifndef INC_CXF_NODE_BITMAP
#define INC_CXF_NODE_BITMAP

/********************************************************************************************

>	class CXaraFileNodeBitmap

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/06/96
	Base Class:	-
	Purpose:	Abstract class holding exporting for node bitmaps.

********************************************************************************************/

class CXaraFileNodeBitmap
{
	// this is an abstract class, so we don't need the memory tracking macros.
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap);

protected:
	static BOOL WriteNodeBitmap(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap);
};

#endif  // INC_CXF_NODEBITMAP
