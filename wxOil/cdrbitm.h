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

// Bitmaps for the CorelDRAW filter

/*
*/


#ifndef INC_CDRBITM
#define INC_CDRBITM

#include "rifffile.h"
//#include "bitmap.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CDRFilter;

/********************************************************************************************

>	class CDRBitmap

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>		
	Created:	10/03/95	
	Purpose:	Does conversion of Corel format bitmaps

********************************************************************************************/

class CDRBitmap
{
public:
	static KernelBitmap *ConvertPattern(RIFFFile *RIFF, DWORD *Reference, CDRFilter *C);
	static KernelBitmap *ConvertBitmap5(RIFFFile *RIFF, DWORD *Reference, CDRFilter *C);
	static KernelBitmap *ConvertBitmap4(RIFFFile *RIFF, DWORD *Reference, CDRFilter *C);
	static KernelBitmap *GenerateBitmap(Node *Objects, DocRect *BBox, Document *pDocument);
};



#endif 		// INC_CDRBITM

