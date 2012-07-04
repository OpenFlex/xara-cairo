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

// The Snap class - used to do all types of snapping in Camelot

#ifndef INC_SNAP
#define INC_SNAP

class Spread;
class DocView;
class DocCoord;
class DocRect;
class Node;
class Layer;
class Path;

enum GuidelineType	{ GUIDELINE_NOTYPE, GUIDELINE_HORZ, GUIDELINE_VERT };

/********************************************************************************************

>	class CSnap : public CC_CLASS_MEMDUMP

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/9/94
	Purpose:	Performs the snapping required by Camelot

********************************************************************************************/

class CSnap : public CC_CLASS_MEMDUMP
{
CC_DECLARE_MEMDUMP(CSnap);

public:
	CSnap(DocView* pThisDocView,Spread* pThisSpread);

	// General snap functions of DocView.
	BOOL Snap(DocCoord* pDocCoord, BOOL TryMagSnap = TRUE,
								   BOOL TryGridSnap = TRUE);
	BOOL Snap(DocRect* pDocRect, const DocCoord& PrevCoord, const DocCoord& CurCoord);

	BOOL TryToSnapToObject(Node* pNode, DocCoord* pDocCoord);

	BOOL SnapToGrids(DocCoord* pDocCoord);
	BOOL SnapToGuidelines(DocCoord* pDocCoord,GuidelineType Type = GUIDELINE_NOTYPE);

	void SetSpread(Spread* pThisSpread) { pSpread = pThisSpread; }

	static MILLIPOINT GetSnapDist() { return SnapDist; }
	static MILLIPOINT GetSnapToCoordDist() { return SnapToCoordDist; }

	static BOOL SnapCoordToPath(DocCoord* pDocCoord, Path* pPath);

	static BOOL SnapRectToRect(DocRect* pSnappedRect, const DocRect& RefRect);

private:
	// Internal snap-to-grid funcs
	BOOL SnapToGrids(DocRect* pDocRect, const DocCoord& PrevCoord, const DocCoord& CurCoord);

	// Internal snap-to-objects funcs
	// if Magnetic is TRUE, only magnetic objects are snapped to, otherwise all objects are snapped to.
	BOOL SnapToObjects(Node* pRootNode,DocCoord* pDocCoord,BOOL Magnetic,BOOL GuideLayersOnly);
	BOOL SnapToObjects(DocRect* pDocRect, const DocCoord& PrevCoord, const DocCoord& CurCoord, BOOL Magnetic,BOOL GuideLayersOnly);

	// Internal snap-to-guidelines funcs
	BOOL SnapToGuidelines(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);
	BOOL SnapToGuidesInLayer(Layer* pLayer,DocCoord* pDocCoord,GuidelineType Type);

	// Internal snap-to-guide-objects funcs
	BOOL SnapToGuideObjects(DocCoord* pDocCoord);
	BOOL SnapToGuideObjects(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);

	// Internal snap-to-pages funcs
	BOOL SnapToPages(DocCoord* pDocCoord);
	BOOL SnapToPages(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);

	// Internal snap-to-value function
	static BOOL SnapToValue(const INT32 RefValue, INT32* pTestValue, INT32* pLockedValue);

private:
	void CalcSnapDist();
	
	DocView*	pDocView;
	Spread*		pSpread;
	Node*		pLastSnappingObject;

	// This is how close a point needs to be to a shape before it can snap to it
	// It is relative to the scale factor of the CSnap object's DocView, and is calculated
	// when the CSnap object is constructed
	static MILLIPOINT SnapDist;
	static MILLIPOINT SnapToCoordDist;

	// This flag controls the snapping of points to the pages in the relevant spread
	// Page boundary snapping will only occur when 'snap to objects' is turned on.
	static BOOL TrySnapToPages;
};

#endif  // INC_SNAP
