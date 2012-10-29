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


#ifndef INC_GRNDBMP
#define	INC_GRNDBMP

#include "grnddib.h"

class OILBitmap;

/********************************************************************************************

>	class GRenderBitmap : public GRenderDIB

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/6/94
	Purpose:	A GDraw render region that uses normal DIBs for the bitmap and can save itself
				out into an OIL bitmap.

********************************************************************************************/

class GRenderBitmap : public GRenderDIB
{
//	friend class BMPFilter;
//	friend class AccusoftFilters;
//	friend class TI_GIFFilter;
//	friend class PNGFilter;

	CC_DECLARE_DYNAMIC(GRenderBitmap)

public:
	GRenderBitmap(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi, BOOL Printing = FALSE,
				  UINT32 Dither = XARADITHER_ORDERED_GREY, LPLOGPALETTE pPalette = NULL, BOOL AutoConvert = FALSE);
	~GRenderBitmap();

	static void Deinit(void);

public:
	// non-virtual fns which are unique to this class
	OILBitmap *ExtractBitmap(LPLOGPALETTE pPalette = NULL);
	OILBitmap *ExtractBitmapCopy(LPLOGPALETTE pPalette = NULL, 
								 LPBITMAPINFO pMaskInfo = NULL, LPBYTE pMaskData = NULL, INT32 MaskColour = -1,
								 BOOL LookForDuplicates = FALSE);

	// Access function for thr bitmap data
	// Always use this, NEVER access the data directly, as a conversion may be necessary
	// if using certain dithering techniques
	BOOL GetBitmapData(LPBITMAPINFO* pBitmapInfo, LPBYTE* pBitmapData, BOOL Convert = FALSE);

	LPBITMAPINFO GetBitmapInfo() { return pBitmapInfo; }

	BOOL StartRender();

	// Allow access to the default dither type in GRenderRegion
//	static INT32 GetDefaultDitherType();

	static BOOL DitheringNeeds32bpp(UINT32 Dither);

	// banding functions
	virtual BOOL SetFirstBand();
	virtual BOOL GetNextBand();
	INT32 GetNumBands();
	void SetOverlapBands(BOOL NewVal);
	BOOL SetRenderBottomToTop(BOOL NewVal);
	INT32 GetFullRegionHeight();

	// Used to calculate the size of the render region required
	virtual WinRect CalculateWinRect( Matrix& RenderMatrix, const DocRect& docrect,
									  const double dpi);

	// Special functions to make it safe for us to render when called from within another
	// GRenderRegion-derived rndrgn. If we don't use a different context, GDraw will explode
	// violently. This is used to render 8bpp greyscale bitmaps for stroke transparency masks
	// so the context also includes a hard-wired greyscale palette, to elimnate large setup delays.
	// DO NOT CALL THIS UNLESS YOU REALLY KNOW WHAT YOU'RE DOING. Danger, danger, Will Robinson!
	void UseGreyscaleContextDangerous(void);
	void StopUsingGreyscaleContextDangerous(void);

	virtual GMATRIX MakeGavinMatrix(Matrix NewRenderMatrix, DocRect ClipRect, double dPixelsPerInch, BOOL bMasterCapture);

private:
	GDrawContext *pPreviousGDrawContext;	// Memory of the normal GDrawContext we replaced
											// in a call to UseGreyscaleContextDangerous
	static GDrawContext *pGreyscaleContext;	// Context we replace the normal one with

protected:
	LPBITMAPINFO GetLPBits( INT32 Width, INT32 Height, INT32 Depth, LPBYTE*);
	void FreeLPBits( LPBITMAPINFO, LPBYTE );
	BOOL DisplayBits(LPBITMAPINFO lpDisplayBitmapInfo = NULL, LPBYTE lpDisplayBits = NULL);

	BOOL DoOutputBitmapConversion(LPBITMAPINFO* lpConvInfo, LPBYTE* lpConvBits, LPLOGPALETTE pPalette);

	LPLOGPALETTE GetConversionPalette();

// member vars
protected:
	BOOL OverlapBands;
	BOOL RenderBottomToTop;
	// The following are some new bits added to cope with the conversion needed when using certain
	// dithering techniques

	UINT32 DitherType;		// For 8bbp or less, this is the Dithering to use
	UINT32  uOutputDepth;  	// If different from the actual RR bpp, then the bitmap will
							// be converted before output

	LPLOGPALETTE    pConvPalette;	// Palette to use for conversion to 8bpp or less

	// These are used for the final output bitmap, if a conversion is needed
	LPBITMAPINFO	lpOutputInfo;	
	LPBYTE			lpOutputBits;	

	// Preserve the tiny offsets calculated by OSRenderRegion::CalculateGavinOffsetWinRect
	// so that Captures use the same offsets as the master capture
	//
	// Use of these variables is all done inside MakeGavinMatrix and RELIES upon the master
	// capture being created and set up (thus calling MakeGavinMatrix) before any other
	// captures are set up. This causes these variable to be initialised by the setting of
	// the master capture before they are used during the setting of other captures.
	//
	double			m_dXCentralAdjust;
	double			m_dYCentralAdjust;
};

#if !defined(EXCLUDE_FROM_RALPH)

/********************************************************************************************

>	class GRenderOptPalette : public GRenderBitmap

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/5/96
	Purpose:	A GDraw render region that generates an opimised palette for the output bitmap

********************************************************************************************/

class GRenderOptPalette : public GRenderBitmap
{
	CC_DECLARE_DYNAMIC(GRenderOptPalette)

public:
	GRenderOptPalette(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 SrcDepth, double dpi, BOOL Use8bpp);
	~GRenderOptPalette();

	virtual BOOL GetNextBand();

	// Function to read the optimised palette, when rendering is finished
	LPLOGPALETTE GetOptimisedPalette(UINT32 PaletteSize, UINT32 NumColours, UINT32 ReservedColours = 0, BOOL SnapToBrowserPalette = FALSE);

public:
	// Preference as to whether we round the colours of a 1bpp optimised palette
	static BOOL DoTwoColourRoundingToPrimary;

	static BOOL DoGDrawConversion;
	static BOOL UseOldPalette;

protected:

	void* Stats;	// Pointer to Statistics used to generate the optimised palette
	BOOL UseSpecial8bpp;	// Tells us whether to use 8bpp specific routines

	BOOL m_bTooManyColours;
	LPLOGPALETTE m_pExactPalette;
};

#endif

#endif
