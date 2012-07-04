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


//GRenderBrush - render region used for drawing brush strokes



#include "grndrgn.h"
#include "grnddib.h"

class DocRect;

#ifndef INC_GRNDBRSH
#define	INC_GRNDBRSH

#include "grndrgn.h"

/********************************************************************************************

>	class GRenderBrush : public GRenderDIB

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com> 
	Created:	20/12/99
	Purpose:	A GDraw render region that uses normal DIBs for the bitmap.
				It serves a particularly special purpose in that it provides a number of 
				functions that allow us to blit to the screen very quickly without 
				getting tangled up in the render loop.  This is so that we can draw brush 
				strokes and have them appear on the screen in real time.
				This is achieved by maintaining not one but  four static
				bitmaps.  These work in the following way:

				The main bitmap (lpbits) needs to have the current view rendered into it before
				beginning the brush stroke.
				lpbrushbits - bitmap which has the brush rendered into it.
				
				What we do instead of rendering is to simply combine the brush bitmap with 
				the view bitmap, copy the results to lppreconvertbits and either blit it or 
				convert it(if we are on a <24bit device).

********************************************************************************************/

class GRenderBrush : public GRenderDIB
{
	CC_DECLARE_DYNAMIC(GRenderBrush)

public:
	GRenderBrush(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi);
	~GRenderBrush();

	 
	void DrawToScreenNow(); // the top level function that gets whatever is in the
							// is in the changed BBox onto the screen
	
public:   // access functions
	void SetChangedBBox(DocRect Rect);

public: // functions you need to call to set up the bitmaps
		// before you draw anything
	
	BOOL InitialiseBrushBitmaps(DocRect BrushRect);
	void SetupMainBitmap();
	
	// plots the brush into the main bitmap
	BOOL PlotBrushIntoBigBitmap(DocRect BrushRect);
	
	// captures the screen as a bitmap
	BOOL CaptureView(Spread* pSpread);
	
	// sets the window to the top of the z-order
	BOOL MoveWindowToFront();
	
	BOOL ResetMatrix();

	void Blackout();

	static BOOL Convert16to32( LPBITMAPINFO pSourceInfo, LPBYTE pSourceBits, RGBQUAD* pPalette,
							  LPBITMAPINFO pDestInfo, LPBYTE pDestBits);
	UINT32  GetScreenDepth() { return (UINT32)ScreenDepth; }

protected: // helper functions
	BOOL ConvertBrushBitmap();   // converts the brush bitmap to the right depth
	BOOL TestConvertBitmap();
	
	BOOL ClipBrushBitmaps(RECT* pUsedRect, INT32* pHeight);  //makes sure we only blit the 
														   // the size of the usedrect
	void SetupBitmap(LPBITMAPINFO pBitmapInfo, LPBYTE pBits);
	BOOL InitialiseBrushBitmaps(INT32 Width, INT32 Height, INT32 RenderDepth, INT32 DeviceDepth);

	BOOL CaptureViewByRendering(); // renders the view into our bitmap

PORTNOTE("other", "Disable HDC stuff")
#ifndef EXCLUDE_FROM_XARALX
	// test to split up the captureview fns for better profiling
	BOOL Blit(HDC DestDC, HDC SourceDC, INT32 Height, INT32 Width, INT32 Left, INT32 Top);
	BOOL GetBits(HDC hDC, HBITMAP hBitmap, INT32 Height, LPBYTE lpbits, LPBITMAPINFO lpInfo);
#endif

	virtual void FreeLPBits( LPBITMAPINFO, LPBYTE );

// Karim 21/07/2000
// Overrides so that GRenderBrush doesn't have to worry about feathers
// (which are offscreen attrs).
public:
	virtual void SetOffscreen(OffscreenAttrValue*) {}
	virtual void RestoreOffscreen(OffscreenAttrValue*) {}

//#ifdef NEWFASTBRUSHES
	// CGS 16/1/2001
	// allow us to optimise the code within DrawToScreenNow - so that we do NOT always have
	// to expensively grab hold of the views DC within an interactive loop ....
	void SetView (View*	v)			{ m_pView = v; }
	void SetCamView (CCamView* v)	{ m_pCCamView = v; }
PORTNOTE("other", "Disable HDC stuff")
#ifndef EXCLUDE_FROM_XARALX
	void SetCDC (CDC* cdc)			{ m_pDevContext = cdc; }
	void SetHDC (HDC hdc)			{ m_DeviceHdc = hdc; }
#endif
//#endif

protected:	// Data

	LPBITMAPINFO lpPreConvertBrushBitmapInfo;	
	LPBYTE lpPreConvertBrushBits;
	LPBITMAPINFO lpPostConvertBrushBitmapInfo;
	LPBYTE lpPostConvertBrushBits;
	LPBITMAPINFO lpBrushBitmapInfo;
	LPBYTE lpBrushBits;

	LPBITMAPINFO lpTestInfo;
	LPBYTE		 lpTestBits;

	RGBQUAD* m_pPalette;

//#ifdef NEWFASTBRUSHES
	// CGS 16/1/2001
	// allow us to optimise the code within DrawToScreenNow - so that we do NOT always have
	// to expensively grab hold of the views DC within an interactive loop ....
	View*	m_pView;
	CCamView* m_pCCamView;
PORTNOTE("other", "Disable HDC stuff")
#ifndef EXCLUDE_FROM_XARALX
	CDC* m_pDevContext;
	HDC m_DeviceHdc;
#endif
//#endif
};
	
#endif
