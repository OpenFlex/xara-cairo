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


#include "camtypes.h"
#include "fthrconv.h"
#include "bshadow.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//
//								Shadow convolution (modified from bshadow.cpp code)
//
/////////////////////////////////////////////////////////////////////////////////////////////
const double HalfX = 0.4999999999999 ;

//
// The following three functions rely on the rounding more being
// round to nearest.
//
inline UINT32 FloorSqrt( const double D )
{
#if defined(_M_IX86)
	UINT32 I ;
	__asm	fld		D
	__asm	fsqrt
	__asm	fsub	HalfX
	__asm	fistp	I
	return I ;
#else
	return (UINT32)sqrt(D) ;
#endif
}

/******************************************************************************************************/

/*
 Modification:-
 Function used to expect the bitmap of an object to be the dimensions of its bounding
 rectangle (ie bbox coords pixel aligned and dimensions converted to pixels, at current zoom)

 Given such a bitmap it expected to generate a bitmap which was nBlur pixels greater on all
 sides (ie dimensions increased by 2*nBlur) to cater for the amount of blurring which would
 extend beyond the dimensions of the src bitmap for any parts of the object which touched the
 src bitmaps border

 Feathering doesn't require this blurring outside the objects outline. Also we don't always
 pass in a full bitmap of the object.

 Modified the function to expect the src bitmap (ie pForegroundBits) to include the extra
 feathersized region which is needed to ensure that the bitmap lying nBlur pixels within the
 borders of the pForegroundBits is properly shadowed.

 Hence the intermediate version of the src bmp (from which the convolution is calculated)
 merely differs from pForeGroundBits in width, by DWORD alignment.

 The destination bitmap into which the convolution calculations are place, ForeGroundSize -
 2*nBlur pixels, wide.(DWORD aligned?).

 Thus the destination bitmap is the same dimensions as the viewable rectangle

ALSO 
changed to return lpBitmapInfo and modify a LPBYTE*

USED to expect blur to be entire blur region (ie twice feather size)
ie (from old code)
	double fNewBlur = fBlur/2.0 ;
	if ( fNewBlur>MAX_SHADOW_BLUR )
		fNewBlur = MAX_SHADOW_BLUR ;
	UINT32 nBlur = (UINT32)fNewBlur ;
  
*/
LPBITMAPINFO Shadow32BppBitmap(const UINT32 nBlur, LPBITMAPINFO pSrcInfo, LPBYTE pSrcBits32, LPBYTE* pDestBits)
{
	ERROR2IF(pSrcInfo->bmiHeader.biBitCount!=32, NULL, "Only supports 32bpp bitmap feathering");

	// Size of the original src bitmap
	CSize SrcBmpSize(pSrcInfo->bmiHeader.biWidth, pSrcInfo->bmiHeader.biHeight);
	CSize InnerBmpSizeCheck(SrcBmpSize.cx - 2*nBlur,SrcBmpSize.cy - 2*nBlur);
	// check convolution code will be OK
	if(!(InnerBmpSizeCheck.cx>1 && InnerBmpSizeCheck.cy>1))
	{
		// Gavin's CompileCode asm function (called from GenerateWallShadow) can't handle this
		ENSURE(FALSE, "Conv code cannot create bmp with width or height of 1.");
		return NULL;
	}

	//////////////////////////////////////////
	// The pSrcBits32 have to be DWORD aligned
	//////////////////////////////////////////
	// NB: OffscreenBMP's always 32Bpp. However if feathering an OffscreenBMP, the byte
	// width of pSrcInfo (ie pSrcInfo->bmiHeader.biWidth / 4) is won't always be DWORD
	// aligned (ie won't necessarily be an exact multiple of 4)
	// See note in GRenderRegion::CreateOffscreenState where buffer allocated
	const UINT32 DWordWidth = DIBUtil::ScanlineSize(SrcBmpSize.cx, 8);
	// Could be up to 3 pixels wider than the source
	UINT32 DWordPadding = DWordWidth - SrcBmpSize.cx;
	BOOL DWordAligned = (DWordPadding==0)? TRUE: FALSE;

	CSize DWordSrcBmpSize(DWordWidth, SrcBmpSize.cy);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Copy src into DWORD aligned 8bpp bmp to pass into gavin's routine (pBitmapToShadow)
	///////////////////////////////////////////////////////////////////////////////////////////
	BYTE* pBitmapToShadow = new BYTE[DWordSrcBmpSize.cx*DWordSrcBmpSize.cy];
	// If the src bmp requires no dword alignment. then we simply need to transfer T value of BGRT
	// pixel in the 32bpp src (ie 4th BYTE of every 4 BYTES) to pBitmapToShadow
	//
	// NB if src bitmap is the offscreen bmp, then it will be DWORD aligned. Also, our background
	// bits are pre-initialised to 0x000000FF. Hence anything outside the nodes path in the offscreen
	// bitmap will already have a T value of 0xFF.
	//
	// For non-DWORD aligned src bmps, we need to ensure that the DWORD padded bytes get set to 0xFF

	// Now, set up the pointers to do the transfer of bits from one bitmap to the other
	// and move the destination pointer into position
//	CONST BYTE* pSrc  = (CONST BYTE *)pSrcBits32 + 3 ;	// T value of pSrcBits32 BGRT value
	CONST BYTE* pSrc  = (CONST BYTE *)pSrcBits32;	// R value of pSrcBits32 BGRT value
	BYTE* pDest = (BYTE *)pBitmapToShadow;

	UINT32 ForegroundScanlineSize = SrcBmpSize.cx * 4;
	// transfer the source bitmap into this larger bitmap to be shadowed
	for ( UINT32 i=0 ; i<(UINT32)DWordSrcBmpSize.cy ; i++ )
	{
		CONST BYTE* pNextSrcLine  = pSrc +ForegroundScanlineSize;
			  BYTE* pNextDestLine = pDest+DWordSrcBmpSize.cx;
		for ( UINT32 j=0 ; j<(UINT32)SrcBmpSize.cx ; j++ )
		{
			*pDest++ = *pSrc;
			pSrc += 4;
		}

		// set dword padding bits to background colour expected by convolution code
		if (!DWordAligned)
		{
			for(j=0; j<DWordPadding; j++)
				*pDest++ = 0xFF;		// NB corresponds to memset(,0xFF,..) from bshadow.cpp code
		}

		pSrc  = pNextSrcLine;
		pDest = pNextDestLine;
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	// Allocate dib for convolved bmp and set up info to pass to convolution function 
	/////////////////////////////////////////////////////////////////////////////////
	// Bitmap to shadow info headers
	BITMAPINFOHEADER SourceBI;
	SourceBI.biBitCount = 8;
	SourceBI.biWidth    = SrcBmpSize.cx;
	SourceBI.biHeight	= SrcBmpSize.cy;
	SourceBI.biPlanes   = 1;

	// Alloc a DIB to shadow into (also sets up info header)
	CSize InnerBmpSize(SrcBmpSize.cx - 2*nBlur,SrcBmpSize.cy - 2*nBlur);
	LPBITMAPINFO pDestInfo = AllocDIB( InnerBmpSize.cx, InnerBmpSize.cy, 8, pDestBits, NULL, TRUE);
	if(pDestInfo==NULL)
	{
		ENSURE(FALSE,"Failed to allocate space for shadow bitmap!");
		delete [] pBitmapToShadow;
		return NULL;
	}
	pDestInfo->bmiHeader.biXPelsPerMeter = pSrcInfo->bmiHeader.biXPelsPerMeter;
	pDestInfo->bmiHeader.biYPelsPerMeter = pSrcInfo->bmiHeader.biYPelsPerMeter;

	/////////////////////////////////////////////////////////////////////////////////
	// set up the row & columns - a circular patch
	/////////////////////////////////////////////////////////////////////////////////
	DWORD Left [CBitmapShadow::MAX_ROW_OFFSETS] ;
	DWORD Right[CBitmapShadow::MAX_ROW_OFFSETS] ;
	DWORD Low  [CBitmapShadow::MAX_ROW_OFFSETS] ;
	DWORD High [CBitmapShadow::MAX_ROW_OFFSETS] ;
	UINT32 nSize = nBlur*2+1 ;
	double S  = nBlur ;
	const double R2 = nBlur * nBlur;
	UINT32 nLine = nBlur ;
	UINT32 nArea = 0 ;
	UINT32 nRows = 0 ;
	for ( UINT32 r=0 ; r<nSize ; ++r )
	{
		const double Radius2 = R2-S*S ;
		if ( Radius2>=0 )
		{
			const UINT32 nRadius = FloorSqrt(Radius2) ;
			 Left[nRows] = nLine-nRadius ;
			Right[nRows] = nLine+nRadius+1 ;
			if ( Left[nRows]<Right[nRows] )
			{
				  Low[nRows] = (nBlur-nRadius  )*DWordSrcBmpSize.cx+r ;
				 High[nRows] = (nBlur+nRadius+1)*DWordSrcBmpSize.cx+r ;
				nArea += Right[nRows]-Left[nRows] ;
				nRows++ ;
			}
		}
		S-- ;
		nLine += DWordSrcBmpSize.cx ;
	}

	UINT32 nTableSize = nArea*255 ;
	UINT32 nInc = 0xffffffffu/nTableSize ;
	UINT32 nShift = 0 ;
	while ( nTableSize>=CBitmapShadow::TABLE_SIZE )
	{
		nTableSize >>= 1 ;
		nShift++ ;
	}
	nInc <<= nShift ;
	BYTE* pTranslationTable = new BYTE[nTableSize+1] ;
	UINT32 nCount = 0 ;
	for ( i=0 ; i<=nTableSize ; ++i )
	{
		pTranslationTable[i] = nCount>>24 ;
		nCount += nInc ;
	}


	/////////////////////////////////////////////////////////////////////////////////
	// call gavin's routine to do the shadowing
	/////////////////////////////////////////////////////////////////////////////////
	CBitmapShadow::GenerateWallShadow(
		&SourceBI, pBitmapToShadow,
		&pDestInfo->bmiHeader, *pDestBits,
		nRows, Left,Right,
		nRows, Low,High,
		nShift,pTranslationTable
	) ;	

	/////////////////////////////////////////////////////////////////////////////////
	// clean up intermediate bitmap and translation table
	/////////////////////////////////////////////////////////////////////////////////
	delete [] pBitmapToShadow;
	delete [] pTranslationTable;

	return pDestInfo;
}


LPBITMAPINFO Shadow8BppBitmap(const UINT32 nBlur, LPBITMAPINFO pSrcInfo, LPBYTE pSrcBits8, LPBYTE* pDestBits)
{
	ERROR2IF(pSrcInfo->bmiHeader.biBitCount!=8, NULL, "Only supports 8bpp bitmap feathering");

	// Size of the original src bitmap
	CSize SrcBmpSize(pSrcInfo->bmiHeader.biWidth, pSrcInfo->bmiHeader.biHeight);
	CSize InnerBmpSizeCheck(SrcBmpSize.cx - 2*nBlur,SrcBmpSize.cy - 2*nBlur);
	// check convolution code will be OK
	if(!(InnerBmpSizeCheck.cx>1 && InnerBmpSizeCheck.cy>1))
	{
		// Gavin's CompileCode asm function (called from GenerateWallShadow) can't handle this
		ENSURE(FALSE, "Conv code cannot create bmp with width or height of 1.");
		return NULL;
	}

	//////////////////////////////////////////////
	// The pSrcBits8 must already be DWORD aligned
	//////////////////////////////////////////////
	const UINT32 DWordWidth = DIBUtil::ScanlineSize(SrcBmpSize.cx, 8);
	// Could be up to 3 pixels wider than the source
	UINT32 DWordPadding = DWordWidth - SrcBmpSize.cx;
	BOOL DWordAligned = (DWordPadding==0)? TRUE: FALSE;

	CSize DWordSrcBmpSize(DWordWidth, SrcBmpSize.cy);
	BYTE* pBitmapToShadow=NULL;
	if(DWordAligned)
	{
		pBitmapToShadow = pSrcBits8;
	}
	else
	{
		// assuming that 8bpp buffer is actually dword aligned
		// NB all buffers allocated by DIBUtil::Alloc dib are actually DWORD aligned even though
		// the bitmap info width/heigth info doesn't reflect this

		pBitmapToShadow = pSrcBits8;
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	// Allocate dib for convolved bmp and set up info to pass to convolution function 
	/////////////////////////////////////////////////////////////////////////////////
	// Bitmap to shadow info headers
	BITMAPINFOHEADER SourceBI;
	SourceBI.biBitCount = 8;
	SourceBI.biWidth    = SrcBmpSize.cx;
	SourceBI.biHeight	= SrcBmpSize.cy;
	SourceBI.biPlanes   = 1;

	// Alloc a DIB to shadow into (also sets up info header)
	CSize InnerBmpSize(SrcBmpSize.cx - 2*nBlur,SrcBmpSize.cy - 2*nBlur);
	LPBITMAPINFO pDestInfo = AllocDIB( InnerBmpSize.cx, InnerBmpSize.cy, 8, pDestBits, NULL, TRUE);
	if(pDestInfo==NULL)
	{
		ENSURE(FALSE,"Failed to allocate space for shadow bitmap!");
		return NULL;
	}
	pDestInfo->bmiHeader.biXPelsPerMeter = pSrcInfo->bmiHeader.biXPelsPerMeter;
	pDestInfo->bmiHeader.biYPelsPerMeter = pSrcInfo->bmiHeader.biYPelsPerMeter;

	/////////////////////////////////////////////////////////////////////////////////
	// set up the row & columns - a circular patch
	/////////////////////////////////////////////////////////////////////////////////
	DWORD Left [CBitmapShadow::MAX_ROW_OFFSETS] ;
	DWORD Right[CBitmapShadow::MAX_ROW_OFFSETS] ;
	DWORD Low  [CBitmapShadow::MAX_ROW_OFFSETS] ;
	DWORD High [CBitmapShadow::MAX_ROW_OFFSETS] ;
	UINT32 nSize = nBlur*2+1 ;
	double S  = nBlur ;
	const double R2 = nBlur * nBlur;
	UINT32 nLine = nBlur ;
	UINT32 nArea = 0 ;
	UINT32 nRows = 0 ;
	for ( UINT32 r=0 ; r<nSize ; ++r )
	{
		const double Radius2 = R2-S*S ;
		if ( Radius2>=0 )
		{
			const UINT32 nRadius = FloorSqrt(Radius2) ;
			 Left[nRows] = nLine-nRadius ;
			Right[nRows] = nLine+nRadius+1 ;
			if ( Left[nRows]<Right[nRows] )
			{
				  Low[nRows] = (nBlur-nRadius  )*DWordSrcBmpSize.cx+r ;
				 High[nRows] = (nBlur+nRadius+1)*DWordSrcBmpSize.cx+r ;
				nArea += Right[nRows]-Left[nRows] ;
				nRows++ ;
			}
		}
		S-- ;
		nLine += DWordSrcBmpSize.cx ;
	}

	UINT32 nTableSize = nArea*255 ;
	UINT32 nInc = 0xffffffffu/nTableSize ;
	UINT32 nShift = 0 ;
	while ( nTableSize>=CBitmapShadow::TABLE_SIZE )
	{
		nTableSize >>= 1 ;
		nShift++ ;
	}
	nInc <<= nShift ;
	BYTE* pTranslationTable = new BYTE[nTableSize+1] ;
	UINT32 nCount = 0 ;
	for (UINT32 i=0 ; i<=nTableSize ; ++i )
	{
		pTranslationTable[i] = nCount>>24 ;
		nCount += nInc ;
	}


	/////////////////////////////////////////////////////////////////////////////////
	// call gavin's routine to do the shadowing
	/////////////////////////////////////////////////////////////////////////////////
	CBitmapShadow::GenerateWallShadow(
		&SourceBI, pBitmapToShadow,
		&pDestInfo->bmiHeader, *pDestBits,
		nRows, Left,Right,
		nRows, Low,High,
		nShift,pTranslationTable
	) ;	

	/////////////////////////////////////////////////////////////////////////////////
	// clean up intermediate bitmap and translation table
	/////////////////////////////////////////////////////////////////////////////////
//	delete [] pBitmapToShadow;
	delete [] pTranslationTable;

	return pDestInfo;
}
