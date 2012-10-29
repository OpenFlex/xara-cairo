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


// header for OutputPNG

#ifndef INC_OUTPTPNG
#define	INC_OUTPTPNG

//#include "outptgif.h"					// TI_GIF_TRANSINTER	
#include <png.h>
//#include "accuflts.h"					// PNG

class BaseCamelotFilter;

/********************************************************************************************

>	class OutputPNG : public OutputDIB

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/96
	Purpose:	Contains functions to write a DIB to a PNG in segments, optionally
				with compression, optionally converting from one depth to another. To use:
				Open a CCFile for write. Call StartFile to write out the header. Call
				WriteBlock to write out each block of the bitmap, starting from low memory.
				When you're done, call TidyUp.
				Similar to OutputDIB and OutputGIF but strangely enough writes the data as
				a PNG instead of a BMP or via the AccusoftFilters. 
	SeeAlso:	OutputDIB; OutputGIF;

********************************************************************************************/

class OutputPNG : public OutputDIB
{
public:

	OutputPNG();

	virtual BOOL StartFile( LPBITMAPINFOHEADER lpHeader, LPLOGPALETTE Palette,
							UINT32 OutputDepth, DWORD CompressionType,
							UINT32 FinalHeight, INT32 ExportSize, UINT32 DitherType);
	virtual BOOL ReStartFile(LOGPALETTE* pNewPal);
	virtual BOOL WriteBlock( UINT32 YPos, UINT32 Height, LPBYTE BlockStart, UINT32 InputBPP = 32,
							 INT32 ProgressOffset = 0);
	virtual BOOL SetUpInfoHeader(const LPBITMAPINFOHEADER lpHeader, const UINT32 OutputDepth,
								 const DWORD CompressionType, const UINT32 LIneWidth, const UINT32 FinalHeight,
								 INT32 *PalSize); 
	virtual BOOL TidyUp();

	// Useful routines for calling to output the GIF data itself
	BOOL OutputPNGHeader(CCLexFile *File, INT32 TransColour, BOOL InterlaceState = 0);
	BOOL OutputPNGHeader(CCLexFile *File, LPBITMAPINFOHEADER pInfo,
						 BOOL InterlaceState, INT32 TransparentColour,
						 LPLOGPALETTE pPalette = NULL, LPRGBQUAD pQuadPalette = NULL);
	BOOL OutputPNGBits(CCLexFile *File, LPBYTE pBlockStart, BOOL OneBlock = TRUE,
					   BaseCamelotFilter *pFilter = NULL);

	virtual LPBITMAPINFO GetDestBitmapInfo ( void );
	virtual LPBYTE GetDestBitmapBits ( void );

private:
	// The buffer to hold the destination bitmap before we actually write it out to file
	LPBITMAPINFO DestBitmapInfo;
	LPBYTE DestBitmapBytes;
	LPBYTE pNextStrip;

	// PNG related items (NOTE: p at end means pointer and hence implied *)
	png_structp png_ptr;
	png_infop info_ptr;
	png_colorp palette;
	int num_palette;
	png_byte* trans;
	int num_trans;

	BOOL CleanUpPngStructures();

	// Some useful variables
	INT32 Width;						// Width of the image
	INT32 Height;						// Height of the image

	BOOL Interlace;					// Use interlace or not
	BOOL Transparent;				// Use transparency or not

	INT32 BitsPerPixel;				// Colour depth required
    INT32 InitCodeSize;				// starting size of the bitmap data to compress

	LPBYTE DataBuffer;				// Start of buffer to compress
	//INT32 DataBufferSize;				// size of the data buffer
	UINT32 WidthOfLine;				// word/byte rounded line width rather than the pixel width
};
#endif // INC_OUTPTPNG
