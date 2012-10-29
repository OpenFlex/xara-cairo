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

/********************************************************************************************

>	cxftrans.cpp

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Purpose:	Code for importing and exporting transformation attributes to and
			from the new native file format.

********************************************************************************************/

#include "camtypes.h"
/*
#include "cxftags.h"
#include "cxftrans.h"
*/
/********************************************************************************************

>	BOOL CXaraFileTransforms::Write(BaseCamelotFilter * pFilter, Matrix * pMatrix)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Inputs:		pFilter - Filter to save the record to
				pMatrix	- Matrix to save
	Returns:	BOOL indicating success or not.
	Purpose:	Writes a transformation attribute to the filter

********************************************************************************************/
/*

BOOL CXaraFileTransforms::Write(BaseCamelotFilter * pFilter, Matrix * pMatrix)
{
	// check the arguments
	ERROR2IF(pFilter == NULL, FALSE, "NULL filter pointer passed as argument.");
	ERROR2IF(pMatrix == NULL, FALSE, "NULL matrix pointer passed as argument.");
	
	BOOL Result;

	// !!ACH!!
	// here we just switch on the transform type of the matrix, and assume it gets set
	// properly by whoever created it. What we ought to do is decompose the matrix and
	// decide whcih of the many transform attribute records we ought to output.
	// This works for the moment, but needs changing.
	
	switch (pMatrix->Type)
	{
		case TRANS_IDENTITY   	:	Result = WriteIdentity(pFilter, pMatrix);
									break;
		case TRANS_TRANSLATION	:	Result = WriteTranslation(pFilter, pMatrix);
									break;
		case TRANS_ROTATION		:	Result = WriteRotation(pFilter, pMatrix);
									break;
		case TRANS_SCALE		:	Result = WriteScale(pFilter, pMatrix);
									break;
		case TRANS_SHEAR		:	Result = WriteShearX(pFilter, pMatrix);
									break;
		case TRANS_COMPLEX		:	Result = WriteGeneral(pFilter, pMatrix);
									break;
		default					:	Result = WriteGeneral(pFilter, pMatrix);
									break;
	}

	return Result;
}
*/
/********************************************************************************************

>	BOOL CXaraFileTransforms::WriteIdentity(BaseCamelotFilter * pFilter, Matrix * pMatrix)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Inputs:		pFilter - filter to use
				pMatrix - matrix to save
	Returns:	Bool indicating success
	Purpose:	Writes an identity transform attribute record to the filter

********************************************************************************************/
/*

BOOL CXaraFileTransforms::WriteIdentity(BaseCamelotFilter * pFilter, Matrix * pMatrix)
{
	BOOL ok;

	CXaraFileRecord Rec(TAG_TRANSFORM_IDENTITY, TAG_TRANSFORM_IDENTITY_SIZE);

	ok = Rec.Init();
	
	if (ok) ok = pFilter->Write(&Rec);
	
	return ok;
}
*/
/********************************************************************************************

>	BOOL CXaraFileTransforms::WriteTranslation(BaseCamelotFilter * pFilter, Matrix * pMatrix)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Inputs:		pFilter - filter to use
				pMatrix - matrix to save
	Returns:	boolean value indicating success
	Purpose:	Writes a translation transform attribute to the filter

********************************************************************************************/
/*

BOOL CXaraFileTransforms::WriteTranslation(BaseCamelotFilter * pFilter, Matrix * pMatrix)
{
	BOOL ok;
	INT32 XTrans, YTrans;

	CXaraFileRecord Rec(TAG_TRANSFORM_TRANSLATION, TAG_TRANSFORM_TRANSLATION_SIZE);

	ok = Rec.Init();

	pMatrix->GetTranslation(XTrans, YTrans);

	if (ok) ok = Rec.Write(XTrans);
	if (ok) ok = Rec.Write(YTrans);
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}
*/
/********************************************************************************************

>	BOOL CXaraFileTransforms::WriteRotation(BaseCamelotFilter * pFilter, Matrix * pMatrix)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Inputs:		pFilter - filter to use
				pMatrix - matrix to save
	Returns:	boolean value indicating success
	Purpose:	Writes a rotation transform attribute to the filter

********************************************************************************************/
/*

BOOL CXaraFileTransforms::WriteRotation(BaseCamelotFilter * pFilter, Matrix * pMatrix)
{
	BOOL ok;

	ANGLE Rotation;

	CXaraFileRecord Rec(TAG_TRANSFORM_ROTATION, TAG_TRANSFORM_ROTATION_SIZE);

	ok = Rec.Init();

	if (ok) ok = pMatrix->Decompose(NULL, NULL, &Rotation, NULL, NULL);
	if (ok) ok = Rec.Write( (FLOAT) Rotation.MakeDouble() );
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}
*/
/********************************************************************************************

>	BOOL CXaraFileTransforms::WriteScale(BaseCamelotFilter * pFilter, Matrix * pMatrix)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Inputs:		pFilter - filter to use
				pMatrix - matrix to save
	Returns:	boolean value indicating success
	Purpose:	Writes a scaling transform attribute to the filter

********************************************************************************************/
/*

BOOL CXaraFileTransforms::WriteScale(BaseCamelotFilter * pFilter, Matrix * pMatrix)
{
	BOOL ok;

	FIXED16 Scale;

	CXaraFileRecord Rec(TAG_TRANSFORM_SCALE, TAG_TRANSFORM_SCALE_SIZE);

	ok = Rec.Init();

	if (ok) ok = pMatrix->Decompose(&Scale, NULL, NULL, NULL, NULL);
	if (ok) ok = Rec.Write( (FLOAT) Scale.MakeDouble() );
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}
*/
/********************************************************************************************

>	BOOL CXaraFileTransforms::WriteShearX(BaseCamelotFilter * pFilter, Matrix * pMatrix)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Inputs:		pFilter - filter to use
				pMatrix - matrix to save
	Returns:	boolean indicating success
	Purpose:	Writes a shear parallel to the X axis to the filter

********************************************************************************************/
/*

BOOL CXaraFileTransforms::WriteShearX(BaseCamelotFilter * pFilter, Matrix * pMatrix)
{
	BOOL ok;
	
	ANGLE Shear;

	CXaraFileRecord Rec(TAG_TRANSFORM_SHEAR_X, TAG_TRANSFORM_SHEAR_X_SIZE);

	ok = Rec.Init();

	if (ok) ok = pMatrix->Decompose(NULL, NULL, NULL, &Shear, NULL);
	if (ok) ok = Rec.Write( (FLOAT) Shear.MakeDouble() );
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}
*/
/********************************************************************************************

>	BOOL CXaraFileTransforms::WriteGeneral(BaseCamelotFilter * pFilter, Matrix * pMatrix)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Inputs:		pFilter - filter to use
				pMatrix - matrix to save out
	Returns:	boolean value indicating success
	Purpose:	writes a general transformation matrix to the filter

********************************************************************************************/
/*

BOOL CXaraFileTransforms::WriteGeneral(BaseCamelotFilter * pFilter, Matrix * pMatrix)
{
	BOOL ok;

	FIXED16 abcd[4];
	INT32 ef[2];

	pMatrix->GetComponents(&abcd[0], &ef[0]);

	CXaraFileRecord Rec(TAG_TRANSFORM_GENERAL, TAG_TRANSFORM_GENERAL_SIZE);

	ok = Rec.Init();

	if (ok) ok = Rec.Write( (FLOAT) abcd[0].MakeDouble() );
	if (ok) ok = Rec.Write( (FLOAT) abcd[1].MakeDouble() );
	if (ok) ok = Rec.Write( (FLOAT) abcd[2].MakeDouble() );
	if (ok) ok = Rec.Write( (FLOAT) abcd[3].MakeDouble() );
	if (ok) ok = Rec.Write( ef[0] );
	if (ok) ok = Rec.Write( ef[1] );
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

*/
