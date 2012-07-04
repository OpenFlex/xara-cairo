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

// The transform operation that can be used to Shear the selection

#ifndef INC_OPSQUASH
#define INC_OPSQUASH

#include "transop.h"

#define OPTOKEN_SQUASH _T("Squash Transform")


/********************************************************************************************

>	class OpSquashTrans : public TransOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/7/94
	Purpose:	The operation that performs the interactive EORed dragging during a Squash

********************************************************************************************/

class OpSquashTrans : public TransOperation
{

CC_DECLARE_DYNCREATE(OpSquashTrans);

public:
	// Construction/Destruction
	OpSquashTrans();

	// These functions required for the OpDescriptor class
	static BOOL Declare();

private:
	// Function to help at the start of an immediate transform
	virtual void InitTransformImmediate(OpParam*);

	// function to build the appropriate transform matrix
	virtual void InitTransformOnDrag(DocCoord, ClickModifiers);
	virtual void UpdateTransformOnDrag(DocCoord, Spread*, ClickModifiers&);
	virtual void BuildMatrix();
	virtual void SetStartBlob(INT32 StartBlob);
	virtual void UpdateTransformBoundingData();

private:
	// Gather information about the size of the selection
	INT32 SelWidth;
	INT32 SelHeight;

	// Is this a horizontal Shear or a vertical one
	enum SquashFlags { SQUASH_UP, SQUASH_LEFT, SQUASH_RIGHT, SQUASH_DOWN } SquashType;

	// The amount to Scale by - one of these will always be 1
	FIXED16 XScale;
	FIXED16 YScale;

	// The most recent mouse position
	DocCoord LastPos;
};


#endif		// INC_OPSQUASH


