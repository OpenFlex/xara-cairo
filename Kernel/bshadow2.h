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

#ifndef _BITMAPSHADOW2_H_
#define _BITMAPSHADOW2_H_

#ifdef BUILDSHADOWS

const UINT32 MAX_SHADOW_BLUR	= 100 ;		// Maximum amount of blur
const UINT32 MAX_CONTOUR		= 100 ;		// Maximum contour pixel size.
const double MIN_BLUR_DIAMETER  = 0.71 ;	// Minimum blur diameter is sqrt(0.5), rounded up
											// a little to safely avoid boundary conditions.

enum {
	MAX_ROW_OFFSETS = MAX_SHADOW_BLUR*2+1,	// Maximum size of shadow mask.
	TABLE_SIZE = 0x800						// Maximum lookup table size for shadow generation.
} ;

bool GenerateWallShadow(
	CONST BITMAPINFOHEADER* pSourceInfo,
	CONST BYTE*             pSourceBitmap,
	CONST BITMAPINFOHEADER* pDestinationInfo,
		  BYTE*             pDestinationBitmap,
	CONST UINT32   nRowOffsets,
	CONST UINT32*  pLeftOffsets,
	CONST UINT32* pRightOffsets,
	CONST UINT32 nColumnOffsets,
	CONST UINT32*   pLowOffsets,
	CONST UINT32*  pHighOffsets,
	CONST UINT32 nTranslationShift,
	CONST BYTE*  pTranslationTable
) ;

bool GenerateFloorShadow(
	void* pCode,
	CONST BITMAPINFOHEADER* pSourceInfo,
	CONST BYTE*             pSourceBitmap,
	CONST BITMAPINFOHEADER* pDestinationInfo,
		  BYTE*             pDestinationBitmap,
	CONST UINT32   nRowOffsets,
	CONST INT32*  pLeftOffsets,
	CONST INT32* pRightOffsets,
	CONST UINT32  nTranslationShift,
	CONST BYTE*  pTranslationTable
) ;

void ContourBitmap( 
	BYTE*		 pBits8, 
	const UINT32 uByteWidth8,
	BYTE*		pDBits8,
	BITMAPINFO* pDInfo8, 
	const double fContour,
	const UINT32 uContour
) ;

// Karim 02/08/2000
// made this static so it can be called by GenerateWallShadow().

#if defined(__WXMSW__)
	void CompileShadowCode(
		BYTE* pCode,
		UINT32  nWidth,
		UINT32  nRows,
		CONST DWORD* pLeft,
		CONST DWORD* pRight,
		UINT32  nShift,
		CONST BYTE* pScale
	) ;
#endif

#endif

#endif //_BITMAPSHADOW_H_




