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

#ifndef INC_OPSHEAR
#define INC_OPSHEAR

#include "transop.h"

#define OPTOKEN_SHEAR _T("Shear Transform")


/********************************************************************************************

>	class OpShearTrans : public TransOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/7/94
	Purpose:	The operation that performs the interactive EORed dragging during a shear

********************************************************************************************/

class OpShearTrans : public TransOperation
{

CC_DECLARE_DYNCREATE(OpShearTrans);

public:
	// Construction/Destruction
	OpShearTrans();

	// These functions required for the OpDescriptor class
	static BOOL Declare();

private:
	// function to build the appropriate transform matrix
	virtual void InitTransformImmediate(OpParam* pParam);
	virtual void InitTransformOnDrag(DocCoord, ClickModifiers);
	virtual void UpdateTransformOnDrag(DocCoord, Spread*, ClickModifiers& ClickMods);
	virtual void BuildMatrix();
	virtual void SetStartBlob(INT32 StartBlob);
	virtual void ConstrainDrag(DocCoord*);

private:
	// Gather information about the size of the selection
	INT32 SelWidth;
	INT32 SelHeight;

	// Is this a horizontal Shear or a vertical one
	BOOL IsHorizontal;

	// Is this a Shear below/left of the origin?
	BOOL IsNegative;

	// The amount to shear by
	FIXED16 ShearBy;

	// The most recent mouse position
	DocCoord LastPos;
};


#endif		// INC_OPSHEAR


