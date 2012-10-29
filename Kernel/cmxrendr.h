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

// CMX Render Region, for exporting

#ifndef __CMXRENDR_H
#define __CMXRENDR_H

#include "vectrndr.h"
#include "nodeshad.h"

class NodeBevel;
class NodeBevelBegin;
class CCLexFile;
class CMXExportDC;

class CMXRenderRegion : public VectorFileRenderRegion
{
	CC_DECLARE_DYNAMIC(CMXRenderRegion)

	friend class NodeBitmap;
	
public:

	CMXRenderRegion(DocRect ClipRect, Matrix ConvertMatrix, FIXED16 ViewScale);

	BOOL AttachDevice(View* ViewToAttach, CNativeDC* DCToAttach, Spread* SpreadToAttach, bool fOwned = false );
	BOOL InitDevice();

	virtual void DrawPathToOutputDevice ( Path		*PathToRender,
										  PathShape	shapePath );

	BOOL ExportPath(Path *PathToRender, BOOL DataOnly);
	BOOL ExportBevel ( NodeBevel *pBevel );
	BOOL ExportBevelBegin ( NodeBevelBegin *pBevel );
	BOOL ExportShadow ( OILBitmap	*pBitmap,
						UINT32		Darkness,
						DocRect		&Bounds );

	void GetRenderRegionCaps(RRCaps* pCaps);

	// virtual Functions to help with rendering
	virtual BOOL WantsGrids();

	// thing to set a flag for exporting bitmaps
	void SetAreExportingContoneBitmap(BOOL flag) {AreExportingContoneBitmap = flag;};
	BOOL GetAreExportingContoneBitmap(void) {return AreExportingContoneBitmap;};

protected:

	void OutputFontName();
	INT32 GetFontStyle();

	void ResetOutputAttributes();

	AttributeEntry *LastOutputAttrs;

	CCLexFile* ExportFile;
	CMXExportDC *cmxDC;

	// This render regions caps. We keep a cached version here as it can be needed in rendering
	RRCaps Caps;

	BOOL AreExportingContoneBitmap;
};

#endif // __CMXRENDR_H

