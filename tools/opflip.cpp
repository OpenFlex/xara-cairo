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

// Flip Operation

/*
*/

#include "camtypes.h"
#include "opflip.h"
//#include "rik.h"

// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
CC_IMPLEMENT_DYNCREATE(OpFlipTrans, TransOperation)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW




/********************************************************************************************

>	OpFlipTrans::OpFlipTrans()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/93
	Purpose:	Constructor. Does nothing but set a flag to a default value.

********************************************************************************************/

OpFlipTrans::OpFlipTrans(): TransOperation()
{
	// Default to horizontal
	IsHorizontal = TRUE;
}



/********************************************************************************************

>	void OpFlipTrans::SetStartBlob(INT32 StartBlob)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/7/94
	Inputs:		StartBlob  - the Number of the blob that the operation was initiated on,
				if applicabale. They are numbered as follows :-
				MonoOn
				1  2  3
				4     5
				6  7  8
				MonoOff
				All operations that were not started from one of the 8 blobs should use 0
	Purpose:	Allows the operations to know how it was started. This operation is
				interested in the horizontal / vertical nature of the transform

********************************************************************************************/

void OpFlipTrans::SetStartBlob(INT32 StartBlob)
{
	// Only blobs 2, 7, 4 and 5 are relavant. All others are a problem
	ENSURE( (StartBlob==2) || (StartBlob==4) || (StartBlob==5) || (StartBlob==7),
			"Flip started on a diagonal startblob. This should not be.");

	// blobs 2 and 7 are the Middle Top and Middle Bottom blobs
	// and would suggest horizontal shearing
	if ((StartBlob==2) || (StartBlob==7))
		IsHorizontal = TRUE;
	else
		IsHorizontal = FALSE;
}





/********************************************************************************************

>	void OpFlipTrans::InitTransformImmediate(OpParam* pOpParam)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/94
	Inputs:		pOpParam - The parameters that were passed into the operation
	Purpose:	Sets up the transform ready for an immediate translation. This is called from
				DoWithParam()
	SeeAlso:	TransOperation::DoWithParam()

********************************************************************************************/

void OpFlipTrans::InitTransformImmediate(OpParam* pOpParam)
{
	// Does nothing
}




/********************************************************************************************

>	void OpFlipTrans::BuildMatrix()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/94
	Purpose:	Builds the transform matrix required to Flip the selection

********************************************************************************************/

void OpFlipTrans::BuildMatrix()
{
	// Translate to the origin
	Transform = Matrix(-CentreOfTrans.x, -CentreOfTrans.y);

	// Flip the selection according to horizontal / vertical ness
	Matrix FlipIt;
	if (IsHorizontal)
		FlipIt = Matrix(FIXED16(-1), FIXED16(1));
	else
		FlipIt = Matrix(FIXED16(1), FIXED16(-1));

	// translate back again
	Matrix TransFromOrigin(CentreOfTrans.x, CentreOfTrans.y);

	// Combine the 3 of them into a single matrix
	Transform *= FlipIt;
	Transform *= TransFromOrigin;
}




/********************************************************************************************

>	BOOL OpFlipTrans::Declare()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/7/93
	Returns:	TRUE if all went OK, False otherwise
	Purpose:	Adds the operation to the list of all known operations

********************************************************************************************/

BOOL OpFlipTrans::Declare()
{
	return (RegisterOpDescriptor(0, _R(IDS_FLIPTRANS), CC_RUNTIME_CLASS(OpFlipTrans),
								OPTOKEN_FLIP, TransOperation::GetState)); 
}
