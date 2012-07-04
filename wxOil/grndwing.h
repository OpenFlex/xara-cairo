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


#include "grndrgn.h"

/********************************************************************************************

>	class GRenderWinG : public GRenderRegion

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Purpose:	A GDraw render region that uses normal DIBs for the bitmap and WinG to blit them

********************************************************************************************/

class GRenderWinG : public GRenderRegion
{
	CC_DECLARE_DYNAMIC(GRenderWinG)

public:
	GRenderWinG(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi);
	~GRenderWinG();

	static BOOL Init(BOOL);
	static void Deinit();
	static BOOL CanWinG( UINT32 Depth );

	// here are the function pointer types to the dynamically linked DLL
	// if wing.h ever changes, so will these. They are not Win16-clean, but as we never
	// use them in Win16 I don't care
	// these are public becuase other people might use them
	// (the stdcalls are required to use Pascal conventions)

	typedef HDC (PASCAL *WING_CREATEDC)( void );
	typedef BOOL (PASCAL *WING_RECOMMENDED)( BITMAPINFO FAR *pFormat );
	typedef HBITMAP (PASCAL *WING_CREATEBITMAP)( HDC WinGDC, BITMAPINFO const FAR *pHeader,
        void FAR *FAR *ppBits );
	typedef BOOL (PASCAL *WING_BITBLT)( HDC hdcDest, INT32 nXOriginDest,
        INT32 nYOriginDest, INT32 nWidthDest, INT32 nHeightDest, HDC hdcSrc,
        INT32 nXOriginSrc, INT32 nYOriginSrc );

	// and here's huw users can get to them. The names of the fn pointers are the same
	// as the real fns, except with a 'p' on the front. Don't use these fn pointers if
	// WinGDLL is NULL, as that would be bad

	static HINSTANCE WinGDLL;								// NULL if not loaded

	static WING_CREATEDC		pWinGCreateDC;
	static WING_RECOMMENDED		pWinGRecommendedDIBFormat;
	static WING_CREATEBITMAP	pWinGCreateBitmap;
	static WING_BITBLT			pWinGBitBlt;


private:
	LPBITMAPINFO GetLPBits( INT32 Width, INT32 Height, INT32 Depth, LPBYTE*);
	void FreeLPBits( LPBITMAPINFO, LPBYTE );
	BOOL DisplayBits(LPBITMAPINFO lpDisplayBitmapInfo = NULL, LPBYTE lpDisplayBits = NULL);
	BOOL StartRenderAfter(GMATRIX *GMat);

	// member variables
	HBITMAP WinGBitmap;
	BOOL Inverted;										// FALSE for old fashioned DIB,
														// TRUE for upside-down DIB

	// static variables
	static HDC OffScreenDC;								// a WinGDC really
};
