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

// Operation for doing an interactive Translation of the selection

/*
*/

#include "camtypes.h"
#include "tranlate.h"

//#include "rik.h"
//#include "clikdrag.h"

// Register my files version number
DECLARE_SOURCE("$Revision: 1282 $");

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_DYNCREATE(OpTranslateTrans, TransOperation)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW





/********************************************************************************************

>	OpTranslateTrans::OpTranslateTrans()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/93
	Purpose:	Constructor. Does nothing.

********************************************************************************************/

OpTranslateTrans::OpTranslateTrans(): TransOperation()
{
	//Set status line help
	StatusHelpID = _R(IDS_TRANSLTRANS_STATUS1);
	StatusHelpID2 = _R(IDS_TRANSLTRANS_STATUS2);
	CanScaleLines = FALSE;
}




/********************************************************************************************

>	void OpTranslateTrans::InitTransformImmediate(OpParam* pOpParam)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/94
	Inputs:		pOpParam - The parameters that were passed into the operation
	Purpose:	Sets up the transform ready for an immediate translation. This is called from
				DoWithParam()
	SeeAlso:	TransOperation::DoWithParam()

********************************************************************************************/

void OpTranslateTrans::InitTransformImmediate(OpParam* pOpParam)
{
	// Set the initial position
	StartPos = DocCoord(0,0);
	RawStartPos = StartPos;
	MagStartPos = StartPos;

	// and copy the offset to translate by from Param2
	DocCoord* Offset = (DocCoord*)( PVOID(pOpParam->Param2) );
	LastPos.x = Offset->x;
	LastPos.y = Offset->y;

	OriginalGridOffset.x=0;
	OriginalGridOffset.y=0;
}


/********************************************************************************************

>	virtual void OpTranslateTrans::InitTransformOnDrag(DocCoord PointerPos, ClickModifiers ClickMods)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Inputs:		PointerPos - The position of the mouse at the start of the drag
				ClickMods - the keyboard modifiers that were active at the start of the drag
	Purpose:	Sets up the parameters needed to build the transform matrix at the start
				of the drag. This base class version of this function does nothing.

********************************************************************************************/

void OpTranslateTrans::InitTransformOnDrag(DocCoord PointerPos, ClickModifiers ClickMods)
{
	// make a note of the current mouse position
	LastPos = PointerPos;

	// Record the offset from the mouse pos to the grid
	OriginalGridOffset = GetStartPos();
	DocView::ForceSnapToGrid(StartSpread, &OriginalGridOffset);
	OriginalGridOffset = GetStartPos() - OriginalGridOffset;
}




/********************************************************************************************

>	virtual void OpTranslateTrans::UpdateTransformOnDrag(DocCoord PointerPos, Spread* pSpread,
									ClickModifiers& ClickMods)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Inputs:		PointerPos - The latest position of the mouse
	Purpose:	Does the calculations needed when the mouse moves to keep all the params
				needed to build the rotation matrix up to date.

********************************************************************************************/

void OpTranslateTrans::UpdateTransformOnDrag(DocCoord PointerPos, Spread* pSpread, ClickModifiers& ClickMods)
{
	if (!ClickMods.Constrain)
	{
		// Apply snapping to the pointer pos
		// First apply magnetic snapping alone
		if (MagneticGripPoint && DocView::SnapSelected(pSpread, &PointerPos, TRUE, FALSE))
		{
			// Magnetic snapping worked!
		}
		else
		{
			// Magnetic snapping failed!
			// If magnetic snapping failed then try grid snapping
			// on the adjusted coordinate
			if (ClickMods.Alternative1)
			{
				PointerPos = PointerPos - OriginalGridOffset;
				DocView::SnapSelected(pSpread, &PointerPos, FALSE, TRUE);
				PointerPos = PointerPos + OriginalGridOffset;
			}
			else
			{
				DocCoord Offset = PointerPos - LastPos;
				DocRect Bounds(	BoundingData.x, BoundingData.y,
								BoundingData.x+BoundingData.Width, BoundingData.y+BoundingData.Height
							   );
				Bounds.lo = Bounds.lo + Offset;
				Bounds.hi = Bounds.hi + Offset;
				DocRect SnappedBounds = Bounds;
				DocView::SnapSelected(pSpread,&SnappedBounds,LastRawPos,RawPos);
				PointerPos = PointerPos + (SnappedBounds.lo - Bounds.lo);
			}
		}
	}

	// Work out the offset from the last mouse pos
	INT32 dx = PointerPos.x - LastPos.x;
	INT32 dy = PointerPos.y - LastPos.y;

	// Add the offset into the structure
	BoundingData.x += dx;
	BoundingData.y += dy;
	BoundingData.XYChanged = TRUE;

	// Make a mental note of the current position
	LastPos = PointerPos;

	// Update the current spread (must do this if CanChangeSpread returns TRUE)
	CurrentSpread = pSpread;
}



/********************************************************************************************

>	virtual BOOL OpTranslateTrans::CanChangeSpread()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/June/2006
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if this transform allows the drag to be transferred to another spread
	Purpose:	Tell the baseclass functions whether to draw drag feedback only on the start
				spread or to allow drag rendering to be done on other spreads too.

********************************************************************************************/

BOOL OpTranslateTrans::CanChangeSpread()
{
	return TRUE;
}


/********************************************************************************************

>	void OpTranslateTrans::BuildMatrix()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Purpose:	Builds the transform matrix required to rotate the selection about the
				point CentreOfRot by the required number of degrees

********************************************************************************************/

void OpTranslateTrans::BuildMatrix()
{
	// Build a translation matrix by takeing the offset from the last mouse position
	// to the start mouse position
		Transform = Matrix(LastPos.x-GetStartPos().x, LastPos.y-GetStartPos().y);
}



/********************************************************************************************

>	virtual BOOL OpTranslateTrans::ShouldPointerBeOffset()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/9/94
	Returns:	FALSE
	Purpose:	Tells the base class of the operation that we want our mouse coords to be
				left alone

********************************************************************************************/

BOOL OpTranslateTrans::ShouldPointerBeOffset()
{
	return FALSE;
}




/********************************************************************************************

>	virtual void OpTranslateTrans::ConstrainDrag(DocCoord* PointerPos)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Inputs:		PointerPos - The current position of the mouse that needs to be constrained
	Outputs:	PointerPos - The position of the mouse after it has been constrained
	Purpose:	Will constrain the mouse position to lie along rays from the centre of
				rotation at the constrain angle apart (45 degrees by default)

********************************************************************************************/

void OpTranslateTrans::ConstrainDrag(DocCoord* PointerPos)
{
	// Lock the mouse to move along the axis or diagonally
	DocCoord Blobby = GetStartPos();
	DocView::ConstrainToAngle(Blobby, PointerPos);
}


/********************************************************************************************

>	BOOL OpTranslateTrans::Declare()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/7/93
	Returns:	TRUE if all went OK, False otherwise
	Purpose:	Adds the operation to the list of all known operations

********************************************************************************************/

BOOL OpTranslateTrans::Declare()
{
	return (RegisterOpDescriptor(0, _R(IDS_SELECTOR_MOVE), CC_RUNTIME_CLASS(OpTranslateTrans),
								OPTOKEN_TRANSLATE, TransOperation::GetState)); 
}
