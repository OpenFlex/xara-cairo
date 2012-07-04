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

// The transform operation that can be used to Rotate the selection

#ifndef INC_OPROTATE
#define INC_OPROTATE

#include "transop.h"

#define OPTOKEN_ROTATE _T("RotateTool")


/********************************************************************************************

>	class OpRotateSpin : public TransOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/7/94
	Purpose:	The operation that performs the interactive EORed dragging during a rotation

********************************************************************************************/

class OpRotateTrans : public TransOperation
{

CC_DECLARE_DYNCREATE(OpRotateTrans);

public:
	// Construction/Destruction
	OpRotateTrans();

	// These functions required for the OpDescriptor class
	static BOOL Declare();

private:
	// Function to help at the start of an immediate transform
	virtual void InitTransformImmediate(OpParam*);

	// function to build the appropriate transform matrix
	virtual BOOL ShouldPointerBeOffset();
	virtual void InitTransformOnDrag(DocCoord, ClickModifiers);
	virtual void UpdateTransformOnDrag(DocCoord, Spread*, ClickModifiers&);
	virtual void BuildMatrix();
	virtual void ConstrainDrag(DocCoord*);
	virtual void UpdateTransformBoundingData();

	// a Helper function to work out the angle from the current mouse position
	ANGLE AngleFromCoord( DocCoord );

	// Member vars of the operation
	ANGLE	StartAngle;					// The angle we start the drag at
	ANGLE	ConstrainedStartAngle;		// The constrined version of the start angle
	ANGLE	CurrentAngle;				// The Angle now

	// Flag to note if the constrain key is being used
	BOOL	IsConstrained;
};


#endif		// INC_OPROTATE


