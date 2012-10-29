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

// The simple shape editing operations


#ifndef INC_OPSMPSHP
#define INC_OPSMPSHP


class Spread;
class NodeEllipse;
class NodeRect;

#define OPTOKEN_EDITRECT _T("EditRectangle")

/********************************************************************************************

>	class OpEditRectangle : public SelOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/6/94
	Purpose:	This operation edits a NodeRect already in the tree. It is normally
				started when the Rect detects a drag on one of its selected blobs.

********************************************************************************************/

class OpEditRectangle : public SelOperation
{
CC_DECLARE_DYNCREATE(OpEditRectangle);

public:
	// Construction/Destruction
	OpEditRectangle();

	// The all important Do functions
	void DoDrag(DocCoord Anchor, Spread*, NodeRect *pRect, INT32 FixedCorner);
	
	// Virtual functions needed for the dragging operations to work
	virtual void DragPointerMove(DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragFinished(DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL Success, BOOL bSolidDrag);

	// Some Render functions to will draw the EORed path
	virtual void RenderDragBlobs(DocRect, Spread*, BOOL bSolidDrag);

	// These functions required for the OpDescriptor class
	static BOOL Init();
	static OpState GetState(String_256* Description, OpDescriptor*);

private:
	// Function to deal with all the undo stuff
	BOOL CompleteOperation();
	BOOL TransformChildAttrs(NodeRect* pRect);

	// Function to calculate the position of the rectangle after one of the corners moves
	void RebuildParallelogram(DocCoord PointerPos);

// Vars
protected:
	// Information we need to draw the EORed rectangle
	DocCoord  Parallel[4];			// The coords of the parallelogram
	INT32 	  FixedCorner;			// The corner of the rectangle that is not moving

	// Infomation about what we are editing
	NodeRect* 		OldRect;

	BOOL			UseRect;
	NodeRect*		RectPath;
	Spread*   		StartSpread;

	// Mouse Positions
	DocCoord  		StartPoint;
	DocCoord  		LastMousePosition;
};


#endif // INC_OPSMPSHP



