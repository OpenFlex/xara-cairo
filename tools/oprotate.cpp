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

// The Rotate transform Operation

/*
*/

#include "camtypes.h"
#include "oprotate.h"

//#include "rik.h"
#include "selector.h"
//#include "clikdrag.h"



// An implement to match the Declare in the .h file.
CC_IMPLEMENT_DYNCREATE(OpRotateTrans, TransOperation)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW




/********************************************************************************************

>	OpRotateTrans::OpRotateTrans()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/93
	Purpose:	Constructor. Does nothing.

********************************************************************************************/

OpRotateTrans::OpRotateTrans(): TransOperation()
{
	// Set status help text
	StatusHelpID = _R(IDS_ROTATETRANS_STATUS1);
	StatusHelpID2 = _R(IDS_ROTATETRANS_STATUS2);
	CanScaleLines = FALSE;
}





/********************************************************************************************

>	void OpRotateTrans::InitTransformImmediate(OpParam* pOpParam)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/94
	Inputs:		pOpParam - The parameters that were passed into the operation
	Purpose:	Sets up the transform ready for an immediate rotation. This is called from
				DoWithParam()
	SeeAlso:	TransOperation::DoWithParam()

********************************************************************************************/

void OpRotateTrans::InitTransformImmediate(OpParam* pOpParam)
{
	// Do a rotation right now
	StartAngle = (ANGLE)0;
	
	// Rotate by the number of degrees pointed to by Param2
	CurrentAngle = * ((ANGLE*)( PVOID(pOpParam->Param2) ) );
	IsConstrained = FALSE;
}




/********************************************************************************************

>	ANGLE OpRotateTrans::AngleFromCoord(DocCoord Pos)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/94
	Inputs:		Pos - The coord to find the angle to
	Returns:	the angle to the coord
	Scope:		Private
	Purpose:	Finds the angle from the centre of rotation that the coord is

********************************************************************************************/

ANGLE OpRotateTrans::AngleFromCoord(DocCoord Pos)
{
	// find the difference between the centre of rotation and the point
	INT32 dx = Pos.x - CentreOfTrans.x;
	INT32 dy = Pos.y - CentreOfTrans.y;

	if ((dx==0) && (dy==0))
	{
		// Oh no, the mouse is directly over the centre of rotation
		return StartAngle;
	}

	// go find the angle to the cursor position from the centre of rotation
	double Angle = atan2((double)dy, (double)dx);

	// convert it to degrees and return it
	Angle = (Angle/(2*PI)) * 360.0;

	return (ANGLE)(Angle);
}



/********************************************************************************************

>	virtual BOOL OpRotateTrans::ShouldPointerBeOffset()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/9/94
	Returns:	FALSE
	Purpose:	Tells the base class of the operation that we want our mouse coords to be
				left alone

********************************************************************************************/

BOOL OpRotateTrans::ShouldPointerBeOffset()
{
	return FALSE;
}


/********************************************************************************************

>	virtual void OpRotateTrans::InitTransformOnDrag(DocCoord PointerPos, ClickModifiers ClickMods)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Inputs:		PointerPos - The position of the mouse at the start of the drag
				ClickMods - the keyboard modifiers that were active at the start of the drag
	Purpose:	Sets up the parameters needed to build the transform matrix at the start
				of the drag. This base class version of this function does nothing.

********************************************************************************************/

void OpRotateTrans::InitTransformOnDrag(DocCoord PointerPos, ClickModifiers ClickMods)
{
	// Make sure that the angle is correctly set taking into account that the
	// start position may be in the same place as the Centre of Rotation (or along
	// one of its axis
	StartAngle = AngleFromCoord(PointerPos);

	// Work out the constrained start angle as well (just in case we need it)
	DocCoord ConstrainedCoord = PointerPos;
	DocView::ConstrainToAngle(CentreOfTrans, &ConstrainedCoord);
	ConstrainedStartAngle = AngleFromCoord(ConstrainedCoord);

	// Constrain the mouse position if required (45 degrees until we get a better system)
	if (ClickMods.Constrain)
	{
		CurrentAngle = ConstrainedStartAngle;
		IsConstrained = TRUE;
	}
	else
	{	
		CurrentAngle = StartAngle;
		IsConstrained = FALSE;
	}
}




/********************************************************************************************

>	virtual void OpRotateTrans::UpdateTransformOnDrag(DocCoord PointerPos, Spread*,
								ClickModifiers&)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Inputs:		PointerPos - The latest position of the mouse
				Spread - The spread the that mouse is over
				ClickModifiers - The click modifiers that were in place at
				this point on the drag
	Purpose:	Does the calculations needed when the mouse moves to keep all the params
				needed to build the rotation matrix up to date.

********************************************************************************************/

void OpRotateTrans::UpdateTransformOnDrag(DocCoord PointerPos, Spread* pClickSpread,
										  ClickModifiers& ClickMods)
{
	// Make sure that the cursor does not wrap around at the edge of spreads
	if (pClickSpread != StartSpread)
		PointerPos = MakeRelativeToSpread(StartSpread, pClickSpread, PointerPos);

	// Calc the new angle, based on the new mouse position
	CurrentAngle = AngleFromCoord(PointerPos);

	// See if the constrain key is in use
	if (ClickMods.Constrain)
	{
		IsConstrained = TRUE;
		BoundingData.Rotation = CurrentAngle - ConstrainedStartAngle;
	}
	else
	{
		BoundingData.Rotation = CurrentAngle - StartAngle;
		IsConstrained = FALSE;
	}

	BoundingData.RotateChanged = TRUE;
	// See also UpdateTransformBoundingData function in this file.
}



/********************************************************************************************

>	void OpRotateTrans::BuildMatrix()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Purpose:	Builds the transform matrix required to rotate the selection about the
				point CentreOfRot by the required number of degrees

********************************************************************************************/

void OpRotateTrans::BuildMatrix()
{
	// Build a matrix to transform the objects at render time by the required offsets
	// First off, work out the angle to rotate by
	ANGLE  RotateBy;
	if (IsConstrained)
		RotateBy = CurrentAngle - ConstrainedStartAngle;
	else
		RotateBy = CurrentAngle - StartAngle;

	// Translate to the origin
	Transform = Matrix(-CentreOfTrans.x, -CentreOfTrans.y);

	// Rotate by the angle
	Matrix RotateIt(RotateBy);

	// translate back again
	Matrix TransFromOrigin(CentreOfTrans.x, CentreOfTrans.y);

	// Combine the 3 of them into a single matrix
	Transform *= RotateIt;
	Transform *= TransFromOrigin;
}





/********************************************************************************************

>	virtual void OpRotateTrans::ConstrainDrag(DocCoord* PointerPos)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Inputs:		PointerPos - The current position of the mouse that needs to be constrained
	Outputs:	PointerPos - The position of the mouse after it has been constrained
	Purpose:	Will constrain the mouse position to lie along rays from the centre of
				rotation at the constrain angle apart (45 degrees by default)

********************************************************************************************/

void OpRotateTrans::ConstrainDrag(DocCoord* PointerPos)
{
	// Rotate want to use the constrain to angle variation of the constrain system
	DocView::ConstrainToAngle(CentreOfTrans, PointerPos);
}


/********************************************************************************************

>	BOOL OpRotateTrans::Declare()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/7/93
	Returns:	TRUE if all went OK, False otherwise
	Purpose:	Adds the operation to the list of all known operations

********************************************************************************************/

BOOL OpRotateTrans::Declare()
{
	return (RegisterOpDescriptor(
								0, 
								_R(IDS_ROTATESPIN),
								CC_RUNTIME_CLASS(OpRotateTrans),
								OPTOKEN_ROTATE,
								TransOperation::GetState)); 
}



/********************************************************************************************

>	void OpRotateTrans::UpdateTransformBoundingData()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/9/94
	Purpose:	Override the base class version of this fn to ensure that new bounds
				are calculated and placed in the BoundingData structure.

********************************************************************************************/

void OpRotateTrans::UpdateTransformBoundingData()
{
#ifndef STANDALONE
	ComputeNewBounds();

	// Tell the tool about the current transform bounding data
	pSelTool->DragMove(&BoundingData);
#endif
}




