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


#if !defined(AFX_AI_BMP_H__BEB8C6A1_047C_11D4_836C_006008484641__INCLUDED_)
#define AFX_AI_BMP_H__BEB8C6A1_047C_11D4_836C_006008484641__INCLUDED_

//	forward definitions
class AI5EPSFilter;
class KernelBitmap;

#include "impbmp.h"


/********************************************************************************************

>	class AIBitmapProcessor  

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00
	Purpose:	Helps with the import of Adobe Illustrator 8.0 files.
				(at the time of writing only the version 7.0 documentation was available
				so some omissions are inevitable).
				It creates a list of bitmaps from the input stream.

********************************************************************************************/
class AIBitmapProcessor  
{
public:
	AIBitmapProcessor();
	virtual ~AIBitmapProcessor();

	BOOL BeginRaster();
	BOOL DecodeXI( AI5EPSFilter& filter );
	BOOL EndRaster();

protected:
	BOOL ReadImageData( AI5EPSFilter& filter, const INT32 ImageType, ADDR pDataStart, INT32 nLength, INT32 nLineLength, INT32 nMaxLineOffset );
	INT32 DecodeHexStringAsCMYK( AI5EPSFilter& filter, ADDR& pCurrentLine, INT32& nLineOffset, INT32 nLineLength, INT32 nMaxLineOffset, UINT32 nStart, BYTE CMYKval[], UINT32& nShift );
	INT32 DecodeHexStringAsRGB( AI5EPSFilter& filter, ADDR& pCurrentLine, INT32& nLineOffset, INT32 nLineLength, INT32 nMaxLineOffset, UINT32 nStart, BYTE RGBval[], UINT32& nShift );

private:
	//	the following maintain the graphics state for bitmaps
	KernelBitmap*	mpNewBitmap;		// the bitmap currently being created
	ImportedBitmaps	mBitmaps;			// the list of imported bitmaps
	INT32			mLastIndex;
};

#endif // !defined(AFX_AI_BMP_H__BEB8C6A1_047C_11D4_836C_006008484641__INCLUDED_)
