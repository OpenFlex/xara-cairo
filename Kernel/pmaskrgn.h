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

// The Printing Masked Render Region

#ifndef INC_PMASKRGN
#define INC_PMASKRGN

#include "maskedrr.h"


/********************************************************************************************

>	class PrintingMaskedRenderRegion : public MaskedRenderRegion

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/95
	Purpose:	This is a simplified version of the MaskedRenderRegion. It does not have to
				cope with a mix of complex and simple shapes to be rendered, but knows that
				there will be a run of complex shapes and then all the rest will be simple.

********************************************************************************************/

class PrintingMaskedRenderRegion : public MaskedRenderRegion
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(PrintingMaskedRenderRegion)

public:
	// Construction/Destruction etc
	PrintingMaskedRenderRegion(DocRect, Matrix, FIXED16, double, BOOL Printing);
	~PrintingMaskedRenderRegion();
	
	// Function to tell us if we are in a complex run or not
	void SetMaskDrawingMode(BOOL OnOff);

	// Render Functions we have to overide
	virtual void DrawPathToOutputDevice(Path *PathToRender, PathShape shapePath=PATHSHAPE_PATH);
	virtual void DrawRect(DocRect *RectToRender);
	virtual void DrawLine(const DocCoord &StartPoint, const DocCoord &EndPoint);
	virtual void DrawPixel(const DocCoord &Point);

	// Functions that are supposed to draw bitmaps
	virtual void DrawBitmap(const DocCoord &Point, KernelBitmap* pBitmap);
	virtual void DrawBitmap(const DocCoord &Point, UINT32 BitmapID, UINT32 ToolID = NULL);
	virtual BOOL DrawTransformedBitmap(NodeBitmap *pNodeBitmap);

	// Function to handle the rendering of chars into the mask
	virtual BOOL RenderChar(WCHAR ch, Matrix* pMatrix);

	// Used to calculate the size of the render region required
	virtual WinRect CalculateWinRect( Matrix& RenderMatrix, const DocRect& docrect,
									  const double dpi);
	virtual GMATRIX MakeGavinMatrix(Matrix NewRenderMatrix, DocRect ClipRect, double dPixelsPerInch, BOOL bMasterCapture);

// Karim 19/12/2000
// Overrides so that PrintingMaskedRenderRegion does not render offscreen attrs.
// The printing loops are fairly loopy & need looking at, but in any case I see
// no current point in rendering a bitmap-processing attr into a mask.
public:
	virtual void SetOffscreen(OffscreenAttrValue*)
	{
	}
	virtual void RestoreOffscreen(OffscreenAttrValue*)
	{
	}

// Member vars
private:
	BOOL IsComplexRun;
};

#endif  // INC_PMASKRGN
