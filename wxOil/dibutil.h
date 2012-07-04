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


#ifndef INC_DIBUTIL
#define	INC_DIBUTIL

#include "memblk.h"
#ifndef mmioFOURCC
//#include <mmsystem.h>
#endif

class CCLexFile;
class BaseCamelotFilter;

LPBITMAPINFO AllocDIB( UINT32 Width, UINT32 Height,	UINT32 Depth, LPBYTE *Bits, MemoryBlock *Blk=NULL, BOOL UseLimitedHeap = FALSE);
void FreeDIB( LPBITMAPINFO, LPBYTE, MemoryBlock*Blk=NULL, BOOL UseLimitedHeap = FALSE);
INT32 GetDIBBitsSize( LPBITMAPINFOHEADER bh );

// this is our MS-approved biCompression method for transparent bitmaps
#define	CC_BMPTYPE	mmioFOURCC('R','G','B','T')

// GDraw sometimes read or writes past the end of bitmaps. This constant is the number
// of extra bytes that should be allocated in all bitmaps (always a multiple of 4)
#define	EXTRA_GAVIN_BYTES	4

class BitmapInfo;
class WxBitmap;
class KernelBitmap;
class OILBitmap;

/********************************************************************************************

>  	BitmapConvertHint

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/2/95
	Purpose:	Enum for hinting when converting bitmaps.

********************************************************************************************/

enum BitmapConvertHint
{
	CONVHINT_NONE,				// no hints
	CONVHINT_FINAL24,			// final output 24-bit
	CONVHINT_FINAL16,			// final output 16-bit RGB not known
	CONVHINT_FINAL555,			// final output 15-bit
	CONVHINT_FINAL565,
	CONVHINT_FINAL655,
	CONVHINT_FINAL664,
	CONVHINT_SCREEN8,			// 8-bit screen
	CONVHINT_SCREEN4,			// 4-bit screen
	CONVHINT_METAFILE,
	CONVHINT_PRINTER,			// printer

	CONVHINT_MAXVALUE = CONVHINT_PRINTER
};

/********************************************************************************************

>	class DIBUtil

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/6/94
	Purpose:	Contains static functions for handy DIB manipulation. Never instantiate one
				of these. That would be silly.

********************************************************************************************/

class DIBUtil
{

public:


	static UINT32 ScanlineSize( UINT32 Width, UINT32 Depth );
	static UINT32 ScanlineBytes( UINT32 Width, UINT32 Depth );
	static BOOL PlotDeepDIB( wxDC *phDC, LPBITMAPINFO lpBitmapInfo, LPBYTE lpBits, INT32 , INT32 , INT32 , INT32 , INT32 , INT32 , BitmapConvertHint, HPALETTE = NULL );

	static BOOL CanReadFromFile( const BitmapInfo *pInfo);				// Kernel style BMPs
	static BOOL CanReadFromFile( const LPBITMAPCOREHEADER pCoreHeader);	// old OS/2 1.0 style BMPs
	static BOOL CanReadFromFile( const LPBITMAPINFOHEADER pInfoHeader );// Win 3.0+ style BMPs

	static BOOL ReadFromFile( CCLexFile *, LPBITMAPINFO *Info, LPBYTE *Bits, BOOL = TRUE,
													String_64 *ProgressString = NULL, BaseCamelotFilter *pFilter = NULL);
	static BOOL WriteToFile ( CCLexFile *, LPBITMAPINFO Info, LPBYTE Bits,
							String_64 *ProgressString = NULL, BOOL WriteHeader = TRUE, BaseCamelotFilter *pFilter = NULL);
	static BOOL WriteToFile ( CCLexFile *, LPBYTE Bits, UINT32 Width, UINT32 Height, UINT32 Depth, String_64 *ProgressString = NULL);

	static void Convert16to24( INT32 PixelWidth, LPBYTE InputBits, LPBYTE OutputBits );
	static void Convert32to24( INT32 PixelWidth, LPBYTE InputBits, LPBYTE OutputBits );
	static void Convert32to24Alpha( INT32 PixelWidth, LPBYTE InputBits, LPBYTE OutputBits, COLORREF Colour );
	static void Convert32to32( INT32 PixelWidth, LPBYTE InputBits, LPBYTE OutputBits );
	static void Convert8to8( INT32 PixelWidth, LPBYTE InputBits, LPBYTE OutputBits );

	static HPALETTE MakeIdentityPalette(PALETTEENTRY aRGB[], INT32 nColors);

	static BitmapConvertHint CalcConvertHint(DWORD ScreenBPP, wxDC *pTestHDC );
	static DWORD GetGavinBlitFormat(DWORD ScreenBPP, DWORD BitmapBPP, BitmapConvertHint ScreenHint);

	static BOOL MakeTransparentBitmap(LPBITMAPINFO pPseudoColourInfo, LPBYTE pPseudoColourBits,
									  LPBITMAPINFO pMonochromeInfo, LPBYTE pMonochromeBits,
									  const BYTE TransCol);
	static BOOL MakeBitmapMask(LPBITMAPINFO pPseudoColourInfo, LPBYTE pPseudoColourBits,
									  LPBITMAPINFO pMonochromeInfo, LPBYTE pMonochromeBits,
									  const BYTE TransCol);

	static BOOL MakeBitmapSmaller(UINT32 OldWidth, UINT32 OldHeight, UINT32 BaseX, UINT32 BaseY, 
								  UINT32 NewWidth, UINT32 NewHeight, UINT32 BPP, LPBYTE pBits);

	static BOOL Init();

	static UINT32 CalcPaletteSize(UINT32 Depth, bool bUsingBitFields, UINT32 UsedColours = 0);

	static BOOL CopyBitmap(LPBITMAPINFO pSourceInfo, LPBYTE pSourceBits,
						   LPBITMAPINFO *pDestInfo, LPBYTE *pDestBits);
	static BOOL CopyEntireBitmap(LPBITMAPINFO pSourceInfo, LPBYTE pSourceBits,
								 LPBITMAPINFO *pDestInfo, LPBYTE *pDestBits);
	static BOOL CopyPalette(LPRGBQUAD pSourcePalette, LPRGBQUAD pDestPalette, UINT32 NumberOfColours);

	static KernelBitmap *CopyKernelBitmap(KernelBitmap *pKernelBitmap, BOOL IsTemp = FALSE);
	
	static BOOL CountColoursUsed(BITMAPINFO* pInfo, BYTE* pBits, UINT32** pResultsArray);
	static INT32 FindLeastUsedColour(BITMAPINFO* pInfo, UINT32* pResultsArray);

	static BOOL CopyBitmapSection(LPBITMAPINFO pSourceInfo, LPBYTE pSourceBits,
								  LPBITMAPINFO pDestInfo,	LPBYTE pDestBits,
								  INT32 SourceTop, INT32 SourceLeft);

#if !defined(EXCLUDE_FROM_RALPH)
	// Gavin's palette optimisation routines
	static BOOL Optimal4bppPaletteInitialise_1stPass() ;
	static BOOL Optimal4bppPaletteInitialise_2ndPass() ;
	static BOOL GenOptimal4bppPaletteStats_1stPass( RGBQUAD* pBitmap, size_t Size ) ;
	static BOOL GenOptimal4bppPaletteStats_2ndPass( RGBQUAD* pBitmap, size_t Size ) ;
	static BOOL GenOptimal4bppPalette( PLOGPALETTE pPalette, const size_t MaxColours ) ;

	static size_t GetOptimal8bppPaletteWorkspaceSize() ;
	static BOOL Optimal8bppPaletteInitialise( INT32* Stats ) ;
	static BOOL GenOptimal8bppPaletteStats( INT32* Stats, RGBQUAD* pBitmap, size_t Size ) ;
	static BOOL GenOptimal8bppPalette( INT32* Stats, PLOGPALETTE pPalette, const size_t MaxColours ) ;

	static size_t GetOptimalPaletteWorkspaceSize() ;
	static BOOL OptimalPaletteInitialise( void* Stats ) ;
	static BOOL ExactPaletteInitialise( LPLOGPALETTE pExactPalette );
	static BOOL GenOptimalPaletteStats( void* Stats, RGBQUAD* pBitmap, size_t Size ) ;
	static BOOL GenOptimalPalette( void* Stats, PLOGPALETTE pPalette, const size_t MaxColours ) ;
#endif

	static BOOL GenGreyscalePalette(LPRGBQUAD lpPalette, const size_t PaletteSize);

	static BOOL Convert24to8( LPBITMAPINFO pSourceInfo, LPBYTE pSourceBits,
							  LPBITMAPINFO *pDestInfo, LPBYTE *pDestBits,
							  RGBTRIPLE *pPalette, UINT32 NumberOfPaletteEntries );

	static BOOL Convert32to8( LPBITMAPINFO pSourceInfo, LPBYTE pSourceBits,
							  LPBITMAPINFO *pDestInfo, LPBYTE *pDestBits,
							  RGBTRIPLE *pPalette, UINT32 NumberOfPaletteEntries );

	static BOOL Convert8to32( LPBITMAPINFO pSourceInfo, LPBYTE pSourceBits, RGBQUAD* pPalette,
							  LPBITMAPINFO pDestInfo, LPBYTE pDestBits);

	// WEBSTER - markn 29/1/97
	// Code to put contone bitmap technology into Webster, post-accusoft
	static OILBitmap*	Create8bppGreyscaleBitmap(KernelBitmap* pSrcBitmap);
	static BOOL			ConvertTo8Greyscale(LPBITMAPINFO pSourceInfo,LPBYTE pSourceBits,LPBITMAPINFO *ppDestInfo, LPBYTE *ppDestBits);
	static BOOL			GenGreyscalePaletteTriple(RGBTRIPLE* pPalette, const size_t PaletteSize);

	// Useful frame generation routines
	static BOOL	GenerateDifferenceBitmap(LPBITMAPINFO pPreviousInfo,LPBYTE pPreviousBits,
										 LPBITMAPINFO pCurrentInfo,LPBYTE pCurrentBits,
										 LPBITMAPINFO *ppDestInfo, LPBYTE *ppDestBits,
										 INT32 TransColour, BOOL * pFoundBadOverlay = NULL);
	static BOOL	GenerateSubRegionBitmap(LPBITMAPINFO pSourceInfo,LPBYTE pSourceBits,
										LPBITMAPINFO *ppDestInfo, LPBYTE *ppDestBits, INT32 TransColour,
										UINT32 *pLeftOffset, UINT32 *pTopOffset);

	// Allocate a LOGPALETTE of the correct size
	static LPLOGPALETTE AllocateLogPalette(const UINT32 PaletteSize);

	// Allocate a LOGPALETTE and copy the palette from the specified bitmap into it 
	static LPLOGPALETTE CopyBitmapPaletteIntoLogPalette(KernelBitmap * pBitmap);

	// Transferred from bfxalu 10/11/97 Neville
	static BOOL IsGreyscaleBitmap(KernelBitmap * pKB);
	static BOOL IsGreyscaleBitmap(OILBitmap * pOilBmp);

	static BOOL CalculateNumberOfColoursInBitmap( LPLOGPALETTE pExactPalette, RGBQUAD* pBitmap, size_t Size );

	static void InvertAlpha(LPBITMAPINFO lpBitmapInfo, LPBYTE lpBits);
#ifdef _DEBUG
	static void FillColour24(LPBITMAPINFO lpBitmapInfo, LPBYTE lpBits);
#endif
	static void MakeAlphaIntoGreyscale(LPBITMAPINFO lpBitmapInfo, LPBYTE lpBits);
};


// we use pointers to functions for the different scanline conversions. This might seem
// a tad un-OOPs but this way we can do assembler-versons of these as required. The following
// typedef is a pointer to one of these functions
typedef void (*FNPTR_SCANLINE)(INT32 PixelWidth, LPBYTE InputBits, LPBYTE OutputBits);



#endif

