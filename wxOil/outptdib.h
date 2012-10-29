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


// header for OutputDIB

#ifndef INC_OUTPTDIB
#define	INC_OUTPTDIB

#include "ccfile.h"						// needs FilePos
#include "dibconv.h"					// needs DIBConvert
#include "dibutil.h"					// needs FNPTR_SCANLINE

/********************************************************************************************

>	class OutputDIB : public CC_CLASS_MEMDUMP

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/8/94
	Purpose:	Contains functions to write a DIB to a Windows BMP in segments, optionally
				with compression, optionally converting from one depth to another. To use:
				Open a CCFile for write. Call StartFile to write out the header. Call
				WriteBlock to write out each block of the bitmap, starting from low memory.
				When you're done, call TidyUp.

********************************************************************************************/

class OutputDIB : public CC_CLASS_MEMDUMP
{
public:

	OutputDIB();
	virtual ~OutputDIB() {}

	virtual BOOL StartFile( CCLexFile *File, LPBITMAPINFOHEADER lpHeader, LPLOGPALETTE Palette,
							UINT32 OutputDepth, DWORD CompressionType,
							UINT32 FinalHeight, INT32 ExportSize, BOOL SecondPass = FALSE,
							UINT32 DitherType = XARADITHER_ORDERED_GREY );

	virtual BOOL StartFile ( LPBITMAPINFOHEADER lpHeader,
							 LPLOGPALETTE Palette,
							 UINT32 OutputDepth,
							 DWORD CompressionType,
							 UINT32 FinalHeight,
							 INT32 ExportSize,
							 UINT32 DitherType = XARADITHER_ORDERED_GREY );

	virtual BOOL WriteBlock( UINT32 YPos, UINT32 Height, LPBYTE BlockStart, UINT32 InputBPP = 32,
							 INT32 ProgressOffset = 0);
	BOOL SetUpBlock( size_t *pBufSize, size_t *pChunkHeight, DIBConvert **pDoConvert,
					 FNPTR_SCANLINE *pConvertFn );
	virtual BOOL SetUpInfoHeader(const LPBITMAPINFOHEADER lpHeader, const UINT32 OutputDepth,
								 const DWORD CompressionType, const UINT32 FinalHeight, INT32 *); 
//	BOOL SetUpExport( CCLexFile *File, LPBITMAPINFOHEADER lpHeader, LPLOGPALETTE Palette, 
//					  UINT32 DitherType, UINT32 OutputDepth,
//					  DWORD CompressionType, UINT32, LPBYTE,
//					  UINT32 StripSize, INT32 ExportSize, BOOL Forward);
	static BOOL GetNextBlock( UINT32 YPos, UINT32 Height, LPBYTE BlockStart,
							  LPBYTE *Buffer, INT32 *CurrentBlockSize,
							  INT32 *CurrentStartYPos, UINT32 *WrittenSoFar);
	static BOOL SetUpForNextStrip(LPBYTE StartOfBytes, UINT32 StripHeight);
	virtual BOOL TidyUp();

	// Some useful palette fixing functions
	static void PokePaletteEntry(LPLOGPALETTE Palette, INT32 *index,
						 		 BYTE red, BYTE green, BYTE blue);
	static void FixBlackAndWhitePalette(LPLOGPALETTE Palette);
	static void Fix16ColourPalette(LPLOGPALETTE Palette);

	void AlterExportPalette( LPLOGPALETTE pPalette );

	virtual LPBITMAPINFO GetDestBitmapInfo ( void );
	virtual LPBYTE GetDestBitmapBits ( void );

protected:

	UINT32 SourceBitmapDepth;					// depth of source bitmap
	FilePos StartPos;						// where in the file the BMP starts
	CCLexFile *OutputFile;						// file we are writing to
	static BITMAPINFOHEADER BitmapInfo;		// copy of file header (includes output depth,
											// width & height)
	LPLOGPALETTE OutputPalette;				// can be NULL

	UINT32 Dither;							// Type of dithering to use

// for debug purposes
	static INT32 HeightWritten;				// count of the height of the export
	static INT32 HeightWanted;				// the actual height of the export required

	// Required by the Accusoft export functions
	static LPBITMAPINFO lpBitmap;			// can be NULL
	static LPBITMAPINFOHEADER lpBitmapInfo;	// can be NULL
	static LPBYTE ExportBuffer;				// can be NULL
	static DIBConvert *DoExportConvert;		// the convert DIB
	static FNPTR_SCANLINE ExportConvertFn;	// the convert function
	static size_t ExportSourceWidth;		// width of the source DIB
	static size_t ExportDestWidth;			// width of the destination DIB
	static LPBYTE ExportData;				// pointer to the export data 
	static INT32 CurrentYPos;					// current line number
	static size_t ExportChunkHeight;		// Chunk height in use			

	static BOOL OutputForward;				// start from bottom or top of DIB
	static UINT32 CurrentStripSize;			// current size of the strip being rendered
	INT32 CurrentExportSize;					// size set up for the progress bar

	static BOOL IsFirstStrip;
};

#endif
