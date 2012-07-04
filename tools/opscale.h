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

// Header file and class definition of the interactive Scale operation

#ifndef INC_OPSCALE
#define INC_OPSCALE


#include "transop.h"

#define OPTOKEN_SCALE _T("Scale")



/********************************************************************************************

>	class OpScaleTrans : public TransOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/94
	Purpose:	This is the interactive and immediate scale operation

********************************************************************************************/

class OpScaleTrans : public TransOperation
{
	// Give my name in memory dumps
	CC_DECLARE_DYNCREATE(OpScaleTrans);

public:
	// Construction/Destruction
	OpScaleTrans();

	// These functions required for the OpDescriptor class
	static BOOL Declare();

	virtual	FIXED16 GetScalar();

protected:
	// function to build the appropriate transform matrix
	virtual void InitTransformImmediate(OpParam*);
	virtual void InitTransformOnDrag(DocCoord, ClickModifiers);
	virtual void UpdateTransformOnDrag(DocCoord, Spread*, ClickModifiers&);
	virtual void BuildMatrix();
	virtual void ConstrainDrag(DocCoord*);
	virtual void UpdateTransformBoundingData();

	// WEBSTER - markn 14/2/97
	// Fix for scaling to work when grid snapping is on
	virtual void SetStartBlob(INT32 ThisStartBlob) { StartBlob = ThisStartBlob; }

private:
	// Member vars of the operation
	// The x & y scale factors
	FIXED16 XScaleFactor;
	FIXED16 YScaleFactor;

	// The width and height of the selection
	INT32 UnitWidth;
	INT32 UnitHeight;

	// WEBSTER - markn 14/2/97
	// Fix for scaling to work when grid snapping is on
	DocCoord PointerStart;
	DocCoord BoundsStartPoint;

	INT32 StartBlob;
};

#endif  // INC_BLANK

