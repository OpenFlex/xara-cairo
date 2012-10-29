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


#ifndef INC_RENDBITS
#define INC_RENDBITS

#include "osrndrgn.h"


enum BitmapContents
{
	BITMAPCONTENTS_CENTRE,							// centre pixel set
	BITMAPCONTENTS_ANY,								// any pixel set
	BITMAPCONTENTS_NONE,							// no pixels set
	BITMAPCONTENTS_ERROR = 0x80						// couldn't say
};


/********************************************************************************************

>	class OSRenderBitmap : public OSRenderRegion

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/11/93
	Purpose:	Special version of a RenderRegion that can render into a bitmap. For now
				it is monochrome only. It can also be asked if it is 'blank' - this can 
				be used for proper click detection. If USE_GDRAW_BITMAP is defined then
				this class is much reduced, its functionality being subsumed by GRenderClick.

********************************************************************************************/


class OSRenderBitmap : public OSRenderRegion
{
public:
	OSRenderBitmap();								// never used but required by compiler

	// static fns everyone can call
//	static RenderRegion *Create( DocRect, Matrix, FIXED16, UINT32, BOOL colour = FALSE);
	static RenderRegion* Create( DocRect, Matrix, FIXED16, RenderType rType = RENDERTYPE_MONOBITMAP);
	static BitmapContents GetContents( RenderRegion* , BOOL);
	static void DebugMe(RenderRegion*, INT32);	  	// helper fn for debugging

};

#endif
