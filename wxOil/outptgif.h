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


// header for OutputGIF

#ifndef INC_OUTPTGIF
#define	INC_OUTPTGIF

#include "ccfile.h"						// needs FilePos
#include "dibconv.h"					// needs DIBConvert
#include "dibutil.h"					// needs FNPTR_SCANLINE
#include "outptdib.h"	
#include "gifutil.h"					// GIF header definitions

#define GIFBITS    		12
#define MAX_LWZ_BITS	12
#define HSIZE  			5003            // 80% occupancy

#define MAXCODE(n_bits)        (((code_int) 1 << (n_bits)) - 1)

#define HashTabOf(i)       htab[i]
#define CodeTabOf(i)    codetab[i]

#define tab_prefixof(i) 		CodeTabOf(i)
#define tab_suffixof(i)        ((char_type*)(htab))[i]
#define de_stack               ((char_type*)&tab_suffixof((code_int)1<<GIFBITS))

class BaseCamelotFilter;
 
/********************************************************************************************

>	class OutputGIF : public OutputDIB

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/4/95
	Purpose:	Contains functions to write a DIB to a GIF in segments, optionally
				with compression, optionally converting from one depth to another. To use:
				Open a CCLexFile for write. Call StartFile to write out the header. Call
				WriteBlock to write out each block of the bitmap, starting from low memory.
				When you're done, call TidyUp.
				Similar to OutputDIB but strangely enough writes the data as a GIF instead
				of a BMP or via the AccusoftFilters. 
	SeeAlso:	OutputDIB;

********************************************************************************************/

class OutputGIF : public OutputDIB
{
public:

	OutputGIF();
	virtual ~OutputGIF() {}

	virtual BOOL StartFile( LPBITMAPINFOHEADER lpHeader, LPLOGPALETTE Palette, UINT32 OutputDepth, DWORD CompressionType,
							UINT32 FinalHeight, INT32 ExportSize, UINT32 DitherType);
	virtual BOOL ReStartFile(LOGPALETTE* pNewPal);
	virtual BOOL WriteBlock( UINT32 YPos, UINT32 Height, LPBYTE BlockStart, UINT32 InputBPP = 32,
							 INT32 ProgressOffset = 0);
	virtual BOOL SetUpInfoHeader(const LPBITMAPINFOHEADER lpHeader, const UINT32 OutputDepth,
								 const DWORD CompressionType, const UINT32 LIneWidth, const UINT32 FinalHeight,
								 INT32 *PalSize); 
	virtual BOOL TidyUp();

	// Useful routines for calling to output the GIF data itself
	BOOL OutputGifFileHeader(CCLexFile *File, LPBITMAPINFOHEADER pInfo, BOOL Enhanced, INT32 TransColour,
							 LPLOGPALETTE pPalette = NULL, LPRGBQUAD pQuadPalette = NULL);
	BOOL OutputGifFileHeader(CCLexFile *File, BOOL Enhanced, INT32 TransColour);
	BOOL OutputGifImageExtensionHeader(CCLexFile *File, BOOL InterlaceState, INT32 TransparentColour,
									   UINT32 Delay, UINT32 RestoreType);
	BOOL OutputGifImageBits(CCLexFile *File, LPBYTE pBlockStart, BOOL Interlace, BOOL LocalColourTable,
							BaseCamelotFilter *pFilter = NULL,
							UINT32 NewWidth = 0, UINT32 NewHeight = 0, UINT32 LeftOffset = 0, UINT32 TopOffset = 0,
							LPRGBQUAD pDestPalette = NULL, UINT32 PaletteColourDepth = 0, UINT32 NewBitsPerPixel = 0);
	BOOL OutputGifTerminator(CCLexFile *File);
	BOOL OutputAnimationControl(CCLexFile *File, unsigned short Repeats);

	virtual LPBITMAPINFO GetDestBitmapInfo ( void );
	virtual LPBYTE GetDestBitmapBits ( void );

	INT32 GetColourDepth(INT32 NumberOfColours);

protected:

	// The buffer to hold the destination bitmap before we actually write it out to file
	LPBITMAPINFO DestBitmapInfo;
	LPBYTE DestBitmapBytes;
	LPBYTE pNextStrip;

	// This stores the pointer to the BaseCamelotFilter, which might be required for progress
	// bar updates.
	BaseCamelotFilter * pCamFilter;

	// Some useful variables
	INT32 Width;						// Width of the image
	INT32 Height;						// Height of the image
	INT32 curx;						// current x position
	INT32 cury;						// current y position
	INT32 CurrentLine;				// count of the lines output so far, used for progress bar
	INT32 CountDown;
	BOOL InterlacingOn;
	INT32 Pass;						// interlaced pass that we are on

	WORD BitsPerPixel;				// Colour depth required
    INT32 InitCodeSize;				// starting size of the bitmap data to compress
	INT32 Background;					// background colour number

	LPBYTE DataBuffer;				// Start of buffer to compress
	//INT32 DataBufferSize;				// size of the data buffer
	UINT32 WidthOfLine;				// word/byte rounded line width rather than the pixel width

	typedef unsigned char char_type;

	INT32 n_bits;                     	// number of bits/code
	code_int maxcode;               	// maximum code, given n_bits

	count_int htab [HSIZE];
	unsigned short codetab [HSIZE];

	code_int free_ent;		// first unused entry

	// block compression parameters -- after all codes are used up,
 	// and compression rate changes, start over.
	INT32 clear_flg;

	INT32 offset;
	INT32 in_count;       // length of input
	INT32 out_count; 		// # of codes output (for debugging)

	// For compress()
	INT32 g_init_bits;

	INT32 ClearCode;
	INT32 EOFCode;

	// for output()
	UINT32 cur_accum;
	INT32 cur_bits;

	INT32 a_count;		// Number of characters so far in this 'packet' (accumulator)
	char accum[ 256 ];	// Define the storage for the packet accumulator

	// Useful routines
	void CompressBlockToFile( LPBYTE Buffer, INT32 init_bits);
	void OutputCode( code_int code );
	void ClearBlock ();
	void ClearHashTable(count_int hsize);
	void CharacterInit();
	void OutputCharacter( INT32 c );
	void FlushCharacters();
	//void init_statics();
	INT32 GIFNextPixel();
	void BumpPixel();
	//BOOL BoundsSafe(INT32 x, INT32 y);
	//INT32 GetPixel(INT32 x, INT32 y);
};

#endif // INC_OUTPTGIF
