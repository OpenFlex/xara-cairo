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


// header file for GRenderClick and GRenderClickColour classes

#ifndef INC_GRNDCLIK
#define	INC_GRNDCLIK

#include "grnddib.h"
#include "rendbits.h"

/********************************************************************************************

>	class GRenderClick : public GRenderDIB

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/11/94
	Purpose:	Special version of a GRenderRegion that renders into a mono bitmap. It
				is used for hit-detection only. It can also be asked if it is 'blank'.

********************************************************************************************/

class GRenderClick : public GRenderDIB
{
	friend class OSRenderBitmap;

	CC_DECLARE_DYNAMIC(GRenderClick)

public:
	GRenderClick(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi);
	~GRenderClick();

	virtual void DebugMe(INT32 Stretch);
	virtual BOOL ImmediateRender();

	// banding functions
	virtual BOOL SetFirstBand();
	virtual BOOL GetNextBand();

protected:
	LPBITMAPINFO GetLPBits( INT32 Width, INT32 Height, INT32 Depth, LPBYTE*);
	void FreeLPBits( LPBITMAPINFO, LPBYTE );

protected:		// private:
	virtual BitmapContents GetContents( BOOL );
	BOOL DisplayBits(LPBITMAPINFO lpDisplayBitmapInfo = NULL, LPBYTE lpDisplayBits = NULL);
	virtual void SetClean(BOOL bResetChangedBounds, BOOL FillWhite);
	BOOL AttachDevice(View*, wxDC*, Spread* SpreadToAttach = NULL, bool fOwned = false );
	BOOL StartRender();

	// member variables
	LPBYTE pMiddle;							// pointer to byte of centre pixel
	BYTE MiddleMask;						// mask of centre pixel

	// Var to ask the bitmap to be cleared the next time Start Render is called
	BOOL ClearOnStart;
};

/********************************************************************************************

>	class GRenderClickColour : public GRenderClick

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/10/99
	Purpose:	Special version of a GRenderClick that renders into a colour bitmap. It
				is used for colour picker hit-detection/pixel colour detection only.

********************************************************************************************/

class GRenderClickColour : public GRenderClick
{
	friend class OSRenderBitmap;

	CC_DECLARE_DYNAMIC(GRenderClickColour)

public:
	GRenderClickColour(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi);
	~GRenderClickColour();

	virtual void DebugMe(INT32 Stretch);

	Pixel32bpp GetCentrePixel32BPP();
	Pixel32bpp GetAveragePixel32BPP();

private:
	BOOL AttachDevice(View*, wxDC*, Spread* SpreadToAttach = NULL, bool fOwned = false );
	BOOL StartRender();

protected:
	virtual BitmapContents GetContents(BOOL JustMiddle);

};

/********************************************************************************************

>	class GRenderClickColourNoPaper : public GRenderClickColour

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/03/2004
	Purpose:	Special version of a GRenderClick that renders into a colour bitmap. It
				is used for hit-detection.
				The only difference between this and GRenderClickColour is that when
				it attaches to a CCDC that CCDC's NeedsPaper function will return FALSE

********************************************************************************************/

class GRenderClickColourNoPaper : public GRenderClickColour
{
	friend class OSRenderBitmap;

	CC_DECLARE_DYNAMIC(GRenderClickColourNoPaper)

public:
	GRenderClickColourNoPaper(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi);
	~GRenderClickColourNoPaper();

private:
	BOOL AttachDevice(View*, wxDC*, Spread* SpreadToAttach = NULL, bool fOwned = false );
};

#endif
