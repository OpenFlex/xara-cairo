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


// class for render regions that render via Windows DIBs

#ifndef INC_GRNDDIB
#define	INC_GRNDDIB

#include "grndrgn.h"

/********************************************************************************************

>	class GRenderDIB : public GRenderRegion

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/6/94
	Purpose:	A GDraw render region that uses normal DIBs for the bitmap.

********************************************************************************************/

class GRenderDIB : public GRenderRegion
{
	CC_DECLARE_DYNAMIC(GRenderDIB)

public:
	GRenderDIB(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi);
	~GRenderDIB();

	// Functions to do with Banded rendering
	virtual BOOL SetFirstBand();
	virtual BOOL GetNextBand();
//	virtual void ResetRegion(DocRect &NewClipRect);			moved to GRenderRgion

	// Called when a region changes in size
	virtual void ResizeRegion(DocRect &NewClipRect);

protected:
	LPBITMAPINFO GetLPBits( INT32 Width, INT32 Height, INT32 Depth, LPBYTE*);
	virtual void FreeLPBits( LPBITMAPINFO, LPBYTE );
	LPBYTE ResizeBits( LPBYTE, INT32 );
	virtual BOOL DisplayBits(LPBITMAPINFO lpDisplayBitmapInfo = NULL, LPBYTE lpDisplayBits = NULL);
	INT32 m_test;
};
#endif
