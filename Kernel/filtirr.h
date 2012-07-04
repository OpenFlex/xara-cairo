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

// Imagemap render region

#ifndef IMAGEMAPRENDERREGION
#define IMAGEMAPRENDERREGION

//#include "rndrgn.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "rrcaps.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "filtimop.h"
#include "imagemap.h"

class CCLexFile;

/********************************************************************************************

>	class ImagemapRenderRegion : public RenderRegion

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	The render region for the imagemap filter.

				This render region has as a member an "Imagemap", which
				is a list of clickable areas.

				The render region works as follows. The Imagemap starts
				off empty. Then, whenever something is rendered into this 
				render region and there is a current WebAddressAttribute with
				a non-empty URL, a clickable area is added to the imagemap.

********************************************************************************************/


class ImagemapRenderRegion : public RenderRegion
{
	CC_DECLARE_DYNAMIC(ImagemapRenderRegion)
	
public:
	ImagemapRenderRegion();
	ImagemapRenderRegion(ImagemapFilterOptions ifoOptions);

	//Destructor
public:
	~ImagemapRenderRegion();


	BOOL Init();

public:
	BOOL StopRender()	{return TRUE;}

	void DrawPathToOutputDevice(Path *PathToRender, PathShape shapePath);
	void DrawRect(DocRect *RectToRender);
	void DrawDragRect(DocRect *RectToRender);
	void DrawLine(const DocCoord &StartPoint, const DocCoord &EndPoint);
	void DrawPixel(const DocCoord &Point);
	void DrawBlob(DocCoord p, BlobType type);
	void DrawCross(const DocCoord &Point, const UINT32 Size);

	void DrawBitmap(const DocCoord &Point, KernelBitmap* pBitmap) {}
	void DrawBitmap(const DocCoord &Point, UINT32 BitmapID, UINT32 ToolID = NULL) {}

	void DrawBitmapBlob(const DocCoord &Point, KernelBitmap* BlobShape) {}
	void DrawBitmapBlob(const DocCoord &Point, ResourceID resID ) {}

	void GetRenderRegionCaps(RRCaps* pCaps);

	// virtual Functions to help with rendering
	virtual BOOL WantsGrids();

	INT32 Write(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);

	BOOL IsEmpty()
	{
		return m_Imagemap.IsEmpty();
	}


protected:
	void InitClipping()	{}
	void InitAttributes()	{}
	void SetOSDrawingMode()	{}
	void SetQualityLevel()	{}
	MILLIPOINT CalcPixelWidth();
	MILLIPOINT CalcScaledPixelWidth();

	//Toolkit functions
protected:
	void AddRectangleToImagemap(DocRect rectToAdd, WebAddressAttribute* pwaaCurrent);
	void AddCircleToImagemap(Path* ppthToAdd, WebAddressAttribute* pwaaCurrent);
	void AddPathToImagemap(Path* ppthToScale, WebAddressAttribute* pwaaCurrent);


	//Member variables
protected:
	// A set of ImagemapFilterOptions
	ImagemapFilterOptions m_Options;	

	//A list of clickable areas
	Imagemap m_Imagemap;

};



#endif // IMAGEMAPRENDERREGION

