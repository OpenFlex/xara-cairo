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

// FontPGen.h - the Font Previewer Thumbnail Generation class

#ifndef INC_FONTPGEN
#define INC_FONTPGEN

#ifndef EXCLUDE_GALS

//#include "camtypes.h"
#include "bfxbase.h"
#include "fontbase.h"

 /***********************************************************************************************

>	class StringToBitmap : public BitmapEffectBase

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/02/95
	Purpose:	Generation of anti-aliased font-string bitmaps for the font installer / de-installer

	SeeAlso:	BfxALU.cpp, Textfuns.cpp

***********************************************************************************************/

class StringToBitmap : public BitmapEffectBase
{
	CC_DECLARE_DYNAMIC(StringToBitmap)

public:
	// Constructor
	StringToBitmap(void);
	
	// Destructor
	~StringToBitmap(void);

	// Create a bitmap and add in a string text in the desired font
	BOOL MakeBitmap(String_256 *text, UINT32 Xsize, UINT32 Ysize, UINT32 BPP, UINT32 DPI,
		PLOGFONT pLogFont,	INT32 IL, KernelBitmap **BM, FontClass Type, PathName *Filename = NULL);

	// Contone the given KernelBitmap
	static BOOL ContoneFontBitmap(KernelBitmap *pBitmap);

protected:

	// Save a kernel bitmap to a file
	BOOL SaveBitmap(KernelBitmap *Bitmap, PathName *Path);

	// Actually whack a string in the bitmap (using either ATM or TTF fonts)
	BOOL StringToBitmap::AddString(String_256 *text, UINT32 Xsize, UINT32 Ysize, UINT32 DPI, PLOGFONT pLogFont,
								 INT32 IL, KernelBitmap **BM, UINT32 ForeColour, FontClass Type);

	// Actually whack a string in the bitmap (using a TTF font)
	BOOL StringToBitmap::TTFAddString(String_256 *text, UINT32 Xsize, UINT32 Ysize, UINT32 DPI, PLOGFONT pLogFont,
								 INT32 IL, KernelBitmap **BM, UINT32 ForeColour);

	// Create a blank bitmap of the desired size, shape and colour
	BOOL StringToBitmap::BlankBitmap(UINT32 Xsize, UINT32 Ysize, UINT32 BPP, UINT32 BackCol, KernelBitmap **BM);
											 
	// Profiling function
	INT32 StringToBitmap::Scale(INT32 Value, INT32 DPI, INT32 Height);
};

#endif
#endif

