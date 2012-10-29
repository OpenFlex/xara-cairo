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

// The Masked Render Region

#ifndef INC_MASKEDRR
#define INC_MASKEDRR

#include "grndbmp.h"

class FlatTranspFillAttribute;
class StrokeTranspAttribute;


/********************************************************************************************

<	struct MaskRegion

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/4/95
	Comment:	This struct holds info that is used by the MaskedRenderRegion::GetFirstMaskRegion
				and MaskedRenderRegion::GetNextMaskRegion. This struct is used to define the
				1 pixel high regions that are extracted from the mask a scan line at a time.
				It is a simple struct with the following public member vars in it :-
				INT32 x - The X coord of the start of the masked region
				INT32 y - The Y Coord of the start of the masked region
				INT32 Length - The length in pixels of the masked region, or 0 if there are no
				more regions in the mask
	SeeAlso:	MaskedRenderRegion::GetFirstMaskRegion; MaskedRenderRegion::GetNextMaskRegion

********************************************************************************************/

struct MaskRegion
{
	INT32 x;
	INT32 y;
	INT32 Length;
};



/********************************************************************************************

>	class MaskedRenderRegion : public GRenderBitmap

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/95
	Purpose:	The Masked Render region is used when rendering to regions that can not
				do all the fabby things that GRender Regions are capable of (eg Transparancy).
				They are used as part of the 3 phase rendering process, in the middle phase.
				In this phase all the objects that are deemed to be too complicated to be
				rendered by the host render region are actually rendered into a GRenderRegion.
				Each of the individual objects that are complex are also rendered into this
				Mono Masked Render Region. At the end of the process this Masked Render region
				is used to identify the minimum area of the render region that needs to be
				blitted into the host render region.

********************************************************************************************/

class MaskedRenderRegion : public GRenderBitmap
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(MaskedRenderRegion)

public:
	// Construction/Destruction etc
	MaskedRenderRegion(DocRect, Matrix, FIXED16, double);
	~MaskedRenderRegion();
	
	// Start render function
	BOOL StartRender();

	// Function to tell us about the host render region
	void SetHostCaps(RRCaps* pCaps);

	// Render Functions we have to overide
	virtual void DrawPathToOutputDevice(Path *PathToRender, PathShape shapePath=PATHSHAPE_PATH);
	virtual void DrawRect(DocRect *RectToRender);
	virtual void DrawLine(const DocCoord &StartPoint, const DocCoord &EndPoint);
	virtual void DrawPixel(const DocCoord &Point);

	// Functions that are supposed to draw bitmaps
	virtual void DrawBitmap(const DocCoord &Point, KernelBitmap* pBitmap);
	virtual void DrawBitmap(const DocCoord &Point, UINT32 BitmapID, UINT32 ToolID = NULL);
	virtual BOOL DrawTransformedBitmap(NodeBitmap *pNodeBitmap);

	// Other Pure virtual drawing functions that have to be overidden
	virtual void DrawDragRect(DocRect *RectToRender);
	virtual void DrawBlob(DocCoord p, BlobType type);
	virtual void DrawCross(const DocCoord &Point, const UINT32 Size);
	virtual void DrawBitmapBlob(const DocCoord &Point, KernelBitmap* BlobShape);
	virtual void DrawBitmapBlob(const DocCoord &Point, ResourceID resID );

	// Function to help out during the masked blit
	BOOL SpreadMask();
	INT32 FindCoverage(BOOL AnyCoverageReturns100 = FALSE);
	INT32 FindMaskDpi();
	//FIXED16 FindMaskDpi();

	// Functions to help find all the regions in the mask that need plotting
	void GetFirstMaskRegion(MaskRegion* pMaskInfo);
	void GetNextMaskRegion(MaskRegion* pMaskInfo);

public:
	virtual void SetOffscreen(OffscreenAttrValue*)
	{
	}
	virtual void RestoreOffscreen(OffscreenAttrValue*)
	{
	}

protected:
	// Function to help the GetFirst/NextMaskRegion functions
	void ScanMaskFrom(MaskRegion* pMaskInfo);

	// Function to help the AboutToRenderComplex/SimpleShape functions
	void SetNextShapeColour(DocColour& RequiredCol);

	// The colours
	DocColour Black;
	DocColour White;

// Member vars
protected:
	// The Host render regions caps
	RRCaps HostCaps;

	// Some attrs used as we go
	FlatTranspFillAttribute* pFillAttr;
	StrokeTranspAttribute* pStrokeAttr;

	static INT32 BitCountTable[256];
};

#endif  // INC_MASKEDRR

 
