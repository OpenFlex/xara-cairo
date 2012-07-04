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

// Flip operation

#ifndef INC_OPFLIP
#define INC_OPFLIP

#include "transop.h"

#define OPTOKEN_FLIP _T("Flip Transform")


/********************************************************************************************

>	class OpFlipTrans : public TransOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/7/94
	Purpose:	This operation allows you to flip the selection either vertically or
				horizontally. It only has an immediate version and no interactive version

********************************************************************************************/

class OpFlipTrans : public TransOperation
{

CC_DECLARE_DYNCREATE(OpFlipTrans);

public:
	// Construction/Destruction
	OpFlipTrans();

	// These functions required for the OpDescriptor class
	static BOOL Declare();

private:
	// function to build the appropriate transform matrix and start the op
	virtual void InitTransformImmediate(OpParam* pOpParam);
	virtual void BuildMatrix();
	virtual void SetStartBlob(INT32 StartBlob);

private:
	// Is this a horizontal Shear or a vertical one
	BOOL IsHorizontal;
};

#endif  // INC_OPFLIP


