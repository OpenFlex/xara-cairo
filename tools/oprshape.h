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

// Header for the regular shape operations

#ifndef INC_OPREGSHAPE
#define INC_OPREGSHAPE


#define OPTOKEN_NEWREGSHAPE 	_T("NewRegShape")

class NodeRegularShape;
class Spread;
class Cursor;

/********************************************************************************************

>	class OpNewRegShape : public SelOperation

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/94
	Purpose:	Provides an operation for the regular shape tool to use to create and insert a
				new shape into the document tree (with undo etc...)

********************************************************************************************/
class OpNewRegShape : public SelOperation
{

CC_DECLARE_DYNCREATE(OpNewRegShape)

public:
	enum CreateMode { RADIUS, DIAMETER, BOUNDS };

	// Construction/Destruction
	OpNewRegShape();

	// The all important Do functions
	void DoDrag( Spread* pSpread, DocCoord Anchor, INT32 NumSides, CreateMode DragMode,
													BOOL Circular, BOOL Stellated, BOOL Curved);
	
	// Virtual functions needed for the dragging operations to work
	virtual void DragPointerMove( DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragFinished(	DocCoord PointerPos, 
								ClickModifiers ClickMods, Spread*, 
								BOOL Success, BOOL bSolidDrag);


	// Some Render functions to will draw the EORed path
	void RenderDragBlobs( DocRect, Spread*, BOOL bSolidDrag );
		
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

private:
	// function to do all the work
	BOOL CompleteOperation();
	void InflateShape(DocRect *Bounds, DocCoord* NewCentre, DocCoord* NewMajor, DocCoord* NewMinor);

	// Member vars of the operation
	NodeRegularShape* NewShape;			// Path representing a rectangle
	Spread*		StartSpread;			// The Spread the click started on
	DocCoord	StartPoint;				// The coords the drag started at
	DocCoord	LastPoint;				// The coords the drag was last at
	CreateMode	CreationMode;			// the way the drag changes the shape.
	Cursor*		pCursor;
	BOOL 		IsShiftDown;
	DocCoord	RecentrePoint;
};

#endif 		// INC_OPRSHAPE




