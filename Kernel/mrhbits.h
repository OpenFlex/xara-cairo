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

//

class BitmapFillAttribute;

#ifndef INC_CBMPBITS
#define INC_CBMPBITS

/**************************************************************************************

>	class CBMPBits : public CC_CLASS_MEMDUMP

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com> H
	Created:	2/8/99
	Purpose:	Converts & removes Solid on Black 32bit problems!

**************************************************************************************/

class CBMPBits : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(CBMPBits);

public:
	static OILBitmap* RenderOILBMPToTransparentWhiteRect(OILBitmap* pConvBMP = NULL, BOOL Transparent = TRUE, INT32 OutputBPP = 32);
	static OILBitmap* RenderKernelBMPToTransparentWhiteRect(KernelBitmap* pConvBMP = NULL, BOOL Transparent = TRUE, INT32 OutputBPP = 32);
	static OILBitmap* RenderBMPFillAttrToTransparentWhiteRect(BitmapFillAttribute* pRef = NULL, BOOL Transparent = TRUE, INT32 OutputBPP = 32);
	static OILBitmap* RenderSelectionToBMP(SelRange* pSel = NULL, INT32 OutputBPP = 32, BOOL Transparent = TRUE, DocRect *pClip = NULL, double DPI = 96.0);
};


#endif	// INC_CBMPBITS

