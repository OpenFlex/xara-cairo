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

// The Translation operation

#ifndef INC_TRANLATE
#define INC_TRANLATE

#include "transop.h"

#define OPTOKEN_TRANSLATE _T("Translate")



/********************************************************************************************

>	class OpTranslateTrans : public TransOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/94
	Purpose:	This is the interactive and immediate Translate operation. When doing an
				immediate transform the params to DoWithParams() are as follows :-
				Param1 - All the standard transform data
				Param2 - A pointer to a DocCoord that holds to offset translate by.

********************************************************************************************/

class OpTranslateTrans : public TransOperation
{
	// Give my name in memory dumps
	CC_DECLARE_DYNCREATE(OpTranslateTrans);

public:
	// Construction/Destruction
	OpTranslateTrans();

	// These functions required for the OpDescriptor class
	static BOOL Declare();

	virtual BOOL ShouldPointerBeOffset();

private:
	// Function to help at the start of an immediate transform
	virtual void InitTransformImmediate(OpParam*);

	// function to build the appropriate transform matrix
	virtual void InitTransformOnDrag(DocCoord, ClickModifiers);
	virtual void UpdateTransformOnDrag(DocCoord, Spread*, ClickModifiers&);
	virtual void BuildMatrix();
	virtual void ConstrainDrag(DocCoord*);
	virtual BOOL CanChangeSpread();

	// Member vars of the operation
	DocCoord LastPos;
	DocCoord OriginalGridOffset;
};

#endif  // INC_TRANLATE


