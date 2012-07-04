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


// A GDraw render region for printing.

#ifndef INC_GRNDPRNT
#define INC_GRNDPRNT

#include "grnddib.h"

/********************************************************************************************

>	class GRenderPrint : public GRenderDIB

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/6/94
	Purpose:	A GDraw render region that uses normal DIBs for the bitmap and can output
				the result to a printer.

********************************************************************************************/

class GRenderPrint : public GRenderDIB
{
	CC_DECLARE_DYNAMIC(GRenderPrint)

public:
	GRenderPrint(DocRect ClipRegion, Matrix ConvertMatrix, FIXED16 ViewScale, UINT32 Depth, double dpi);
	~GRenderPrint();

	virtual BOOL StartRender();
	virtual BOOL StopRender();

	virtual BOOL InitDevice();

	// banding functions
	virtual BOOL SetFirstBand();
	virtual BOOL GetNextBand();

protected:
	BOOL OldPlateDisabledState;
	BOOL HaveDisabledPlate;

protected:
	LPBITMAPINFO GetLPBits( INT32 Width, INT32 Height, INT32 Depth, LPBYTE*);
	void FreeLPBits( LPBITMAPINFO, LPBYTE );
	BOOL DisplayBits(LPBITMAPINFO lpDisplayBitmapInfo = NULL, LPBYTE lpDisplayBits = NULL);
};

#endif  // INC_GRNDPRNT


