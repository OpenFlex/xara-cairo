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

// cmx data defn -- fns implimented in cmxifltr.cpp

#ifndef CMXIDATA_H
#define CMXIDATA_H

#include "cmxibits.h"
#include "nodetext.h"

class CMXImportLayer;
class CMXImportFilter;
class CMXImportRImage;
class CMXImportProecdure;

// class containing all the data we use for an import -- nice way of getting rid
// of any problem bits
class CMXImportFilterDataSet : public CCObject
{
	CC_DECLARE_DYNAMIC(CMXImportFilterDataSet);

public:
	CMXImportFilterDataSet(CMXImportFilter *pFilter);
	~CMXImportFilterDataSet();

	// progress object
	Progress *pProgress;
	INT32 CommandsInPage;

	// positions of things within the file
	INT32 IndexFilePosition;
	INT32 MasterIndexEntries[cmxMASTERIN_MAXENTRY];

	// flags
	BOOL InPage;				// whether we're currently processing a page (set to FALSE to finish it)
	BOOL ObjFilled;
	BOOL RemoveLens;			// need to remove a transparency attribute we applied?
	BOOL EndSectionFound;		// whether we've just encountered a EndSection command

	// dodgy objects
	INT32 AttributesApproximated;
	INT32 ObjectsApproximated;
	INT32 ClippingsApproximated;	// only set if clipped objects have outlines

	// lists of stuff
	List Layers;

	// handy bits
	CMXImportLayer *pCurrentLayer;
	Matrix BaseMatrix;				// base matrix which is the CMX -> Cam coord scale, translation matrix
	Matrix *pCurrentMatrix;			// pointer to the current transformation matrix
	double BaseScaleFactor;			// base scale factor
	Path *pClippingPath;			// path to clip objects to, or NULL
	BOOL HaveFirstObjInBoundsRect;	// flag
	DocRect AllObjectsBoundsRect;	// bounds of all objects we did

	// stacks...
	CMXImportStack TransformStack;
	CMXImportStack ClipperStack;

	TextStory*		pTextStory; 
	TextLine*		pTextLine;
	cmxiRenderAttr	textRenderAttributes;

	// arrays of references...
	INT32 NumColours;
	CMXImportColour *Colours;
	INT32 NumOutlines;
	CMXImportOutline *Outlines;
	INT32 NumPens;
	CMXImportPen *Pens;
	INT32 NumLineStyles;
	CMXImportLineStyle *LineStyles;
	INT32 NumRImages;
	CMXImportRImage *RImages;
	INT32 NumProcedures;
	CMXImportProcedure *Procedures;
	INT32 NumDotDashes;
	CMXImportDotDash *DotDashes;
	INT32 NumArrowShapes;
	CMXImportArrowShape *ArrowShapes;
	INT32 NumArrowheads;
	CMXImportArrowheads *Arrowheads;
	INT32 NumBitmaps;
	CMXImportBitmap *Bitmaps;
	INT32 NumFonts;
	CMXImportFont *Fonts;
	INT32	NumCharInfo;
	cmxiCharInfo *CharInfos;
	INT32 currentRef;
	INT32 currentSize;
	Justification	textJustification;
	//	That's to get round some corelism
	BOOL TextFrameRead;
	
};

#endif // CMXIDATA_H

