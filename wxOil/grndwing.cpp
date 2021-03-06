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


// GDraw rendering via WinG libraries


#include "camtypes.h"
#include "grndwing.h"
#include "oilmods.h"
#include "camelot.h"

CC_IMPLEMENT_DYNAMIC( GRenderWinG, GRenderRegion )

HDC GRenderWinG::OffScreenDC;





HINSTANCE GRenderWinG::WinGDLL;								// NULL if not loaded


GRenderWinG::WING_CREATEDC		GRenderWinG::pWinGCreateDC;
GRenderWinG::WING_CREATEBITMAP	GRenderWinG::pWinGCreateBitmap;
GRenderWinG::WING_BITBLT		GRenderWinG::pWinGBitBlt;
GRenderWinG::WING_RECOMMENDED	GRenderWinG::pWinGRecommendedDIBFormat;


static BITMAPINFOHEADER RecommendedDIB;

/********************************************************************************************

>	BOOL GRenderWinG::Init(BOOL FirstTime)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Inputs:		FirstTime is TRUE if called on startup, FALSE if called subsequently
				(e.g. screen mode change).
	Outputs:	-
	Returns:	TRUE if we can use WinG, FALSE if we cannot.
	Purpose:	Determines whether WinG is available on this platform.
	Errors:		-
	Scope:		Public static

********************************************************************************************/

BOOL GRenderWinG::Init( BOOL FirstTime )
{
	if (!FirstTime)
	{
		// only a screen mode change so don't redo DLL etc, just get new DC
		if (WinGDLL)
		{
			// kill old one
			if (OffScreenDC)
				DeleteDC( OffScreenDC );

			// go get new one
			OffScreenDC = pWinGCreateDC();
			if (OffScreenDC)
				return TRUE;
		}
		return FALSE;
	}

#if WIN32
	// lets see if the DLL is there

	// on NT 3.1 the DLL init code fails the load and produces an ugly dialog, so we don't
	// bother
	if (IsWin32NT())
	{
		const WORD Ver = LOWORD( GetVersion() );
		if (
			(LOBYTE(Ver) == 3) &&					// NT 3.5 is minimum requirement
			(HIBYTE(Ver) < 50)
		   )
			return FALSE;
	}

	// try the DLL now
	WinGDLL = LoadLibrary("WING32.DLL");
	if (WinGDLL)
	{
		// (ordinal values extracted from DLL using DUMPBIN -export)

		pWinGCreateDC =		(WING_CREATEDC)		GetProcAddress( WinGDLL, MAKEINTRESOURCE(0x3e9) );
		pWinGCreateBitmap =	(WING_CREATEBITMAP)	GetProcAddress( WinGDLL, MAKEINTRESOURCE(0x3eb) );
		pWinGBitBlt =		(WING_BITBLT)		GetProcAddress( WinGDLL, MAKEINTRESOURCE(0x3f2) );
		pWinGRecommendedDIBFormat =
							(WING_RECOMMENDED)	GetProcAddress( WinGDLL, MAKEINTRESOURCE( 0x3ea ) );

		if (
			(pWinGCreateDC == NULL)		||
			(pWinGCreateBitmap == NULL)	||
			(pWinGBitBlt == NULL) 		||
			(pWinGRecommendedDIBFormat==NULL)
		   )
		{
			TRACE( _T("WinG32 DLL entrypoints missing!\n"));
			FreeLibrary( WinGDLL );
			WinGDLL = NULL;
			return FALSE;
		}
	}
	else
	{
		TRACE( _T("WinG DLL not found (error %d)\n"), GetLastError() );
		return FALSE;
	}

	// remember the DLL handle so it gets cleaned up for us always on exit
	ExtraDLLs[ WinG_DLL ] = WinGDLL;

	RecommendedDIB.biSize = sizeof(BITMAPINFOHEADER);

	// excuse the seemingly rampant cast but I think the official prototype is wrong
	const BOOL ok = pWinGRecommendedDIBFormat( (LPBITMAPINFO)&RecommendedDIB );
		
	if (IsUserName("Andy"))
	{
		TRACE( _T("Recommended bitmap:\n"));
		if (ok)
		{
			TRACE( _T("%dx%d height=%d comp=%d\n"),
					(INT32)RecommendedDIB.biPlanes,
					(INT32)RecommendedDIB.biBitCount,
					(INT32)RecommendedDIB.biHeight,
					(INT32)RecommendedDIB.biCompression
				);
		}
		else
			TRACE( _T("ERROR - isnt one\n"));
	}

	OffScreenDC = pWinGCreateDC();
	if (OffScreenDC)
		return TRUE;

#endif

	// if we get here it means we failed
	return FALSE;
}

/********************************************************************************************

>	void GRenderWinG::Deinit()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Purpose:	Tidies up WinG before exit. Frees up necessary resources etc.
	Errors:		-
	Scope:		Static

********************************************************************************************/

void GRenderWinG::Deinit()
{
	if (OffScreenDC)
	{
		DeleteDC(OffScreenDC);
		OffScreenDC = NULL;
	}
}

/********************************************************************************************

>	BOOL GRenderWinG::CanWinG( UINT32 Depth )

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Inputs:		Pixel depth required
	Returns:	TRUE if GRenderWinG can be done at such a depth, FALSE if cannot
	Purpose:	Use before creating GRenderWinGs inc case they are not supported. Currently
				only uses WinG if depth matches the recommended format.
	Errors:		-
	Scope:		Static public

********************************************************************************************/

BOOL GRenderWinG::CanWinG( UINT32 Depth )
{
	if (
		WinGDLL								&&		// must have DLL
		OffScreenDC							&&		// and screen DC
		(RecommendedDIB.biPlanes == 1)		&&		// mono planar
		(Depth == RecommendedDIB.biBitCount)		// and correct depth
	   )
		return TRUE;

	return FALSE;
}

/********************************************************************************************

>	GRenderWinG::GRenderWinG(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	GRenderWinG constructor. Doesn't do anything actually, just calls base class.
				INT32 dpi changed to FIXED16 dpi (12/12/95) to improve the range of values allowed
				at the < 1000dpi settings that we will be using.
	Errors:		-
	SeeAlso:	GRenderRegion::GRenderRegion

********************************************************************************************/

GRenderWinG::GRenderWinG(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi)
	: GRenderRegion( ClipRegion, ConvertMatrix, ViewScale, Depth, dpi)
{
	WinGBitmap = NULL;
	Inverted = FALSE;
}

/********************************************************************************************

>	LPBITMAPINFO GRenderWinG::GetLPBits( INT32 Width, INT32 Height, INT32 Depth, LPBYTE*lplpBits)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Inputs:		Bitmap characteristics.
	Outputs:	*lplpBits is made to point to the bytes of the bitmap.
	Returns:	The bitmap header, or NULL if not enough memory.
	Purpose:	Allocates a bitmap header and the bitmap bytes.
	Errors:		-
	SeeAlso:	GRenderWinG::FreeLPBits

********************************************************************************************/

LPBITMAPINFO GRenderWinG::GetLPBits( INT32 Width, INT32 Height, INT32 Depth, LPBYTE*lplpBits)
{
	// get a bitmap header with no bits
	const LPBITMAPINFO bmInfo = AllocDIB( Width, Height, Depth, NULL );
	if (!bmInfo)
		return NULL;

	// tell it the sort of palette we want - we want Gavin's
	if (Depth==8)
	{
	#if 0
		RGBQUAD *rgb = bmInfo->bmiColors;
		LPPALETTEENTRY lpPal = GetRecommendedPalette()->palPalEntry;

		size_t i ;
		for ( i=0 ; i<256 ; i++ )
		{
			rgb->rgbRed = lpPal->peRed;
			rgb->rgbGreen = lpPal->peGreen;
			rgb->rgbBlue = lpPal->peBlue;
			rgb->rgbReserved = 0;
			rgb ++;
			lpPal++;
		}
	#else

		GetSystemPaletteEntries (
			RenderDC->m_hDC, 0, 256, (LPPALETTEENTRY) bmInfo->bmiColors
		) ;
		RGBQUAD *rgb = bmInfo->bmiColors ;					// Swap R and B.
		size_t i ;
		for ( i=0 ; i<256 ; i++ )
		{
			BYTE t = rgb->rgbRed ;
			rgb->rgbRed = rgb->rgbBlue ;
			rgb->rgbBlue = t ;
			rgb ++ ;
		}
	#endif
	}

	// if WinG wants it upside-down then go for it
	if (RecommendedDIB.biHeight == -1)
	{
		Inverted = TRUE;
		bmInfo->bmiHeader.biHeight = -bmInfo->bmiHeader.biHeight;
	}
	else
		Inverted = FALSE;

	// now get a lovely WinG bitmap
	WinGBitmap = pWinGCreateBitmap( OffScreenDC, bmInfo, (void FAR* FAR *)lplpBits );
	if (WinGBitmap==NULL)
	{
		TRACE( _T("WinGCreateBitmap failed\n"));
		FreeDIB( bmInfo, NULL );
		return NULL;
	}

	// turn it back the other way else Gavin is likely to get confused
	if (Inverted)
		bmInfo->bmiHeader.biHeight = -bmInfo->bmiHeader.biHeight;

	//TRACE( _T("WinG Alloc %lx=%lx:%lx\n"), this, bmInfo, *lplpBits);
	return bmInfo;
}

/********************************************************************************************

>	void GRenderWinG::FreeLPBits( LPBITMAPINFO lpBMI, LPBYTE lpB )

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Inputs:		Bitmap characteristics.
	Outputs:	-
	Returns:	-
	Purpose:	Frees up a bitmap allocated with GetLPBits.
	Errors:		-
	SeeAlso:	GRenderWinG::FreeLPBits

********************************************************************************************/

void GRenderWinG::FreeLPBits( LPBITMAPINFO lpBMI, LPBYTE lpB )
{
	if (WinGBitmap)
	{
		DeleteObject( WinGBitmap );
		WinGBitmap = NULL;
	}
	FreeDIB( lpBMI, NULL );
}

/********************************************************************************************

>	GRenderWinG::~GRenderWinG()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/6/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	GRenderWinG destructor. Frees up the bitmap.
	Errors:		-

********************************************************************************************/

GRenderWinG::~GRenderWinG()
{
	if (LocalBitmap)
	{
		if (HaveRenderedSomething)
			// We're not clean - flush bitmap to screen
			DisplayBits();

//		FreeLPBits( lpBitmapInfo, lpBits );
		FreeOffscreenState();
		lpBitmapInfo = NULL;
		lpBits = NULL;
	}
	// will call GRenderRegions destructor here
}


/********************************************************************************************

>	BOOL GRenderWinG::StartRenderAfter(GMATRIX *GMat)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/94
	Inputs:		Pointer to Gavins matrix created by GRenderRegion::StartRender
	Outputs:	Update matrix if required.
	Returns:	TRUE if worked, FALSE if failed.
	Purpose:	Updates the Gavin matrix to cope with the upside-down nature of DIBs
				if that is the recommended format
	Errors:		Always returns TRUE.
	SeeAlso:	GRenderDDB::StartRenderAfter

********************************************************************************************/

BOOL GRenderWinG::StartRenderAfter(GMATRIX *GMat)
{
	if (Inverted)
	{
		// flip up other way
		GMat->BY = -GMat->BY;

		// calculate the new offset
		//XLONG ydisp = (XLONG)( (WRect.bottom -  WRect.top ) * 72000 ) / (XLONG)(PixelsPerInch.MakeXlong() * ScaleFactor);
		FIXED16 ScaledDpi = FIXED16(PixelsPerInch) * ScaleFactor;
		XLONG Size = (WRect.bottom -  WRect.top ) * 72000;
		XLONG ydisp = Size / ScaledDpi.MakeXlong();

		GMat->CY = -GMat->CY + Mul(-GMat->BY, ydisp);
	}

	// we cannot fail
	return TRUE;
}

/********************************************************************************************

>	BOOL GRenderWinG::DisplayBits(LPBITMAPINFO lpDisplayBitmapInfo = NULL, LPBYTE lpDisplayBits = NULL)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if worked, FALSE if failed.
	Purpose:	Plots the DIB onto the owner device.
	Errors:		-

********************************************************************************************/

BOOL GRenderWinG::DisplayBits(LPBITMAPINFO lpDisplayBitmapInfo, LPBYTE lpDisplayBits)
{
	BOOL ok = FALSE;

	if (lpBitmapInfo && lpBits && RenderDC)
	{
		HBITMAP hOldBitmap;

		hOldBitmap = SelectBitmap( OffScreenDC, WinGBitmap );
		if (hOldBitmap)
		{
			ok = pWinGBitBlt( RenderDC->m_hDC,			// dest
								WRect.left, WRect.top,		// dest XY
								WRect.right-WRect.left,
								WRect.bottom-WRect.top,
								OffScreenDC,				// source
								0,0							// source XY
							);
			SelectBitmap( OffScreenDC, hOldBitmap );
		}
	}
	return ok;
}
