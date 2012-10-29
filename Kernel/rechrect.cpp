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

>	rechrect.cpp

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Purpose:	Implementation of class to handle loading of rectangle records from the new
				file format.

********************************************************************************************/

#include "camtypes.h"

#include "nodershp.h"

#include "cxftags.h"

#include "rechrshp.h"
#include "rechrect.h"

// to match the declare in the header file
CC_IMPLEMENT_DYNAMIC(RectangleRecordHandler, RegularShapeRecordHandler);

/********************************************************************************************

>	UINT32* RectangleRecordHandler::GetTagList()

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Inputs:		-
	Returns:	UINT32* to an array of records handled by this class. The last entry in the
				array is CXFRH_TAG_LIST_END
	Purpose:	Returns an array of records handled by this class.
	See Also:	EllispeRecordHandler::HandleRecord

********************************************************************************************/

UINT32* RectangleRecordHandler::GetTagList()
{
	static UINT32 TagList[] = {TAG_RECTANGLE_SIMPLE,
								TAG_RECTANGLE_SIMPLE_REFORMED,
								TAG_RECTANGLE_SIMPLE_STELLATED,
								TAG_RECTANGLE_SIMPLE_STELLATED_REFORMED,
								TAG_RECTANGLE_SIMPLE_ROUNDED,
								TAG_RECTANGLE_SIMPLE_ROUNDED_REFORMED,
								TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED,
								TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED_REFORMED,
								TAG_RECTANGLE_COMPLEX,
								TAG_RECTANGLE_COMPLEX_REFORMED,
								TAG_RECTANGLE_COMPLEX_STELLATED,
								TAG_RECTANGLE_COMPLEX_STELLATED_REFORMED,
								TAG_RECTANGLE_COMPLEX_ROUNDED,
								TAG_RECTANGLE_COMPLEX_ROUNDED_REFORMED,
								TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED,
								TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED_REFORMED,
								CXFRH_TAG_LIST_END};
	return &TagList[0];
}

/********************************************************************************************

>	BOOL RectangleRecordHandler::HandleRecord(CXaraFileRecord * pCXaraFileRecord)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Inputs:		pCXaraFileRecord - CXaraFileRecord object to read
	Returns:	TRUE if successful, FALSE otherwise
	Purpose:	Handles ellipse type records for the new file format

********************************************************************************************/

BOOL RectangleRecordHandler::HandleRecord(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok;

	switch (pCXaraFileRecord->GetTag())
	{
		case TAG_RECTANGLE_SIMPLE
				: ok = ReadRectangleSimple(pCXaraFileRecord); break;
		case TAG_RECTANGLE_SIMPLE_REFORMED
				: ok = ReadRectangleSimpleReformed(pCXaraFileRecord); break;
		case TAG_RECTANGLE_SIMPLE_STELLATED
				: ok = ReadRectangleSimpleStellated(pCXaraFileRecord); break;
		case TAG_RECTANGLE_SIMPLE_STELLATED_REFORMED
				: ok = ReadRectangleSimpleStellatedReformed(pCXaraFileRecord); break;
		case TAG_RECTANGLE_SIMPLE_ROUNDED
				: ok = ReadRectangleSimpleRounded(pCXaraFileRecord); break;
		case TAG_RECTANGLE_SIMPLE_ROUNDED_REFORMED
				: ok = ReadRectangleSimpleRoundedReformed(pCXaraFileRecord); break;
		case TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED
				: ok = ReadRectangleSimpleRoundedStellated(pCXaraFileRecord); break;
		case TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED_REFORMED
				: ok = ReadRectangleSimpleRoundedStellatedReformed(pCXaraFileRecord); break;
		case TAG_RECTANGLE_COMPLEX
				: ok = ReadRectangleComplex(pCXaraFileRecord); break;
		case TAG_RECTANGLE_COMPLEX_REFORMED
				: ok = ReadRectangleComplexReformed(pCXaraFileRecord); break;
		case TAG_RECTANGLE_COMPLEX_STELLATED
				: ok = ReadRectangleComplexStellated(pCXaraFileRecord); break;
		case TAG_RECTANGLE_COMPLEX_STELLATED_REFORMED
				: ok = ReadRectangleComplexStellatedReformed(pCXaraFileRecord); break;
		case TAG_RECTANGLE_COMPLEX_ROUNDED
				: ok = ReadRectangleComplexRounded(pCXaraFileRecord); break;
		case TAG_RECTANGLE_COMPLEX_ROUNDED_REFORMED
				: ok = ReadRectangleComplexRoundedReformed(pCXaraFileRecord); break;
		case TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED
				: ok = ReadRectangleComplexRoundedStellated(pCXaraFileRecord); break;
		case TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED_REFORMED
				: ok = ReadRectangleComplexRoundedStellatedReformed(pCXaraFileRecord); break;
		default
				: ok = ReadShapeInvalid(pCXaraFileRecord); break;
	}
	
	return ok;
}

/********************************************************************************************

>	const INT32 RectangleRecordHandler::NumberOfSides;

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	11/06/96
	Purpose:	Holds the number of sides a rectangle has - errm, 4.

********************************************************************************************/

const INT32 RectangleRecordHandler::NumberOfSides = 4;

/********************************************************************************************

>	BOOL RectangleRecordHandler::ReadRectangleSimple(CXaraFileRecord *pCXaraFileRecord)
	BOOL RectangleRecordHandler::ReadRectangleSimpleReformed(CXaraFileRecord *pCXaraFileRecord)
	BOOL RectangleRecordHandler::ReadRectangleSimpleStellated(CXaraFileRecord *pCXaraFileRecord)
	BOOL RectangleRecordHandler::ReadRectangleSimpleRounded(CXaraFileRecord *pCXaraFileRecord)
	BOOL RectangleRecordHandler::ReadRectangleSimpleRoundedStellated(CXaraFileRecord *pCXaraFileRecord)
	BOOL RectangleRecordHandler::ReadRectangleComplex(CXaraFileRecord *pCXaraFileRecord)
	BOOL RectangleRecordHandler::ReadRectangleComplexStellated(CXaraFileRecord *pCXaraFileRecord)
	BOOL RectangleRecordHandler::ReadRectangleComplexRounded(CXaraFileRecord *pCXaraFileRecord)
	BOOL RectangleRecordHandler::ReadRectangleComplexRoundedStellated(CXaraFileRecord *pCXaraFileRecord)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Inputs:		pCXaraFileRecord - pointer to the record to read
	Returns:	TRUE if successfull, false otherwise
	Purpose:	Reads in an rectangle record

********************************************************************************************/

BOOL RectangleRecordHandler::ReadRectangleSimple(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;

	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pRectangle, Height, Width);

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleSimpleReformed(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape *pRectangle;
	DocCoord CentrePoint;
	INT32 Width;
	INT32 Height;

	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pRectangle, Height, Width);

	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath1));

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);
	
	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleSimpleStellated(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;
	double StellationRadius;
	double StellationOffset;

	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsStellated(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pRectangle, Height, Width);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationRadius);
	if (ok) ok = SetStellationRadius(pRectangle, StellationRadius);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationOffset);
	if (ok) ok = SetStellationOffset(pRectangle, StellationOffset);

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleSimpleStellatedReformed(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;
	double StellationRadius;
	double StellationOffset;

	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsStellated(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pRectangle, Height, Width);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationRadius);
	if (ok) ok = SetStellationRadius(pRectangle, StellationRadius);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationOffset);
	if (ok) ok = SetStellationOffset(pRectangle, StellationOffset);

	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath1));
	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath2));

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleSimpleRounded(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;
	double Curvature;
	
	pRectangle = new NodeRegularShape;


	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsRounded(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pRectangle, Height, Width);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&Curvature);
	if (ok) ok = SetCurvature(pRectangle, Curvature);

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleSimpleRoundedReformed(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;
	double Curvature;
	
	pRectangle = new NodeRegularShape;


	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsRounded(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pRectangle, Height, Width);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&Curvature);
	if (ok) ok = SetCurvature(pRectangle, Curvature);

	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath1));

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleSimpleRoundedStellated(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;
	double StellationRadius;
	double StellationOffset;
	double PrimaryCurvature;
	double SecondaryCurvature;
	
	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsRounded(pRectangle, TRUE);
	if (ok) ok = SetIsStellated(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pRectangle, Height, Width);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationRadius);
	if (ok) ok = SetStellationRadius(pRectangle, StellationRadius);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationOffset);
	if (ok) ok = SetStellationOffset(pRectangle, StellationOffset);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&PrimaryCurvature);
	if (ok) ok = SetPrimaryCurvature(pRectangle, PrimaryCurvature);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&SecondaryCurvature);
	if (ok) ok = SetSecondaryCurvature(pRectangle, SecondaryCurvature);

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleSimpleRoundedStellatedReformed(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;
	double StellationRadius;
	double StellationOffset;
	double PrimaryCurvature;
	double SecondaryCurvature;
	
	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsRounded(pRectangle, TRUE);
	if (ok) ok = SetIsStellated(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pRectangle, Height, Width);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationRadius);
	if (ok) ok = SetStellationRadius(pRectangle, StellationRadius);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationOffset);
	if (ok) ok = SetStellationOffset(pRectangle, StellationOffset);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&PrimaryCurvature);
	if (ok) ok = SetPrimaryCurvature(pRectangle, PrimaryCurvature);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&SecondaryCurvature);
	if (ok) ok = SetSecondaryCurvature(pRectangle, SecondaryCurvature);

	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath1));
	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath2));
	
	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleComplex(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	
	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pRectangle, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pRectangle, MinorAxis);

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleComplexReformed(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	Matrix TransformMatrix;
	
	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pRectangle, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pRectangle, MinorAxis);

	if (ok) ok = pCXaraFileRecord->ReadMatrix(&TransformMatrix);
	if (ok) ok = SetTransformMatrix(pRectangle, TransformMatrix);

	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath1));

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleComplexStellated(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	double StellationRadius;
	double StellationOffset;

	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsStellated(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pRectangle, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pRectangle, MinorAxis);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationRadius);
	if (ok) ok = SetStellationRadius(pRectangle, StellationRadius);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationOffset);
	if (ok) ok = SetStellationOffset(pRectangle, StellationOffset);

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleComplexStellatedReformed(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	Matrix TransformMatrix;
	double StellationRadius;
	double StellationOffset;

	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsStellated(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pRectangle, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pRectangle, MinorAxis);

	if (ok) ok = pCXaraFileRecord->ReadMatrix(&TransformMatrix);
	if (ok) ok = SetTransformMatrix(pRectangle, TransformMatrix);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationRadius);
	if (ok) ok = SetStellationRadius(pRectangle, StellationRadius);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationOffset);
	if (ok) ok = SetStellationOffset(pRectangle, StellationOffset);

	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath1));
	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath2));

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleComplexRounded(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	double Curvature;
	
	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsRounded(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pRectangle, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pRectangle, MinorAxis);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&Curvature);
	if (ok) ok = SetCurvature(pRectangle, Curvature);

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleComplexRoundedReformed(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	Matrix TransformMatrix;
	double Curvature;
	
	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsRounded(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pRectangle, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pRectangle, MinorAxis);

	if (ok) ok = pCXaraFileRecord->ReadMatrix(&TransformMatrix);
	if (ok) ok = SetTransformMatrix(pRectangle, TransformMatrix);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&Curvature);
	if (ok) ok = SetCurvature(pRectangle, Curvature);

	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath1));

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleComplexRoundedStellated(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord CentrePoint;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	double StellationRadius;
	double StellationOffset;
	double PrimaryCurvature;
	double SecondaryCurvature;
	
	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsRounded(pRectangle, TRUE);
	if (ok) ok = SetIsStellated(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pRectangle, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pRectangle, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pRectangle, MinorAxis);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationRadius);
	if (ok) ok = SetStellationRadius(pRectangle, StellationRadius);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationOffset);
	if (ok) ok = SetStellationOffset(pRectangle, StellationOffset);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&PrimaryCurvature);
	if (ok) ok = SetPrimaryCurvature(pRectangle, PrimaryCurvature);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&SecondaryCurvature);
	if (ok) ok = SetSecondaryCurvature(pRectangle, SecondaryCurvature);

	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

BOOL RectangleRecordHandler::ReadRectangleComplexRoundedStellatedReformed(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pRectangle;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	Matrix TransformMatrix;
	double StellationRadius;
	double StellationOffset;
	double PrimaryCurvature;
	double SecondaryCurvature;
	
	pRectangle = new NodeRegularShape;

	if (ok) ok = SetupShape(pRectangle);
	if (ok) ok = SetNumberOfSides(pRectangle, NumberOfSides);
	if (ok) ok = SetIsRounded(pRectangle, TRUE);
	if (ok) ok = SetIsStellated(pRectangle, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pRectangle, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pRectangle, MinorAxis);

	if (ok) ok = pCXaraFileRecord->ReadMatrix(&TransformMatrix);
	if (ok) ok = SetTransformMatrix(pRectangle, TransformMatrix);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationRadius);
	if (ok) ok = SetStellationRadius(pRectangle, StellationRadius);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&StellationOffset);
	if (ok) ok = SetStellationOffset(pRectangle, StellationOffset);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&PrimaryCurvature);
	if (ok) ok = SetPrimaryCurvature(pRectangle, PrimaryCurvature);

	if (ok) ok = pCXaraFileRecord->ReadDOUBLE(&SecondaryCurvature);
	if (ok) ok = SetSecondaryCurvature(pRectangle, SecondaryCurvature);

	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath1));
	if (ok) ok = pCXaraFileRecord->ReadPath(&(pRectangle->EdgePath2));
	
	if (ok) ok = InvalidateCache(pRectangle);
	if (ok) ok = InsertNode(pRectangle);

	return ok;
}

/********************************************************************************************

>	void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);


	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/08/96
	Inputs:		pCXaraFileRecord - CXaraFileRecord holding the record in question
				Str - StringBase to add our information to
	Returns:	-
	Purpose:	Returns textual information on this record

********************************************************************************************/

#ifdef XAR_TREE_DIALOG
void RectangleRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase *pStr)
{
	if (pRecord != NULL && pStr != NULL)
	{
		// Call base class first
		// This outputs the tag and size
		CamelotRecordHandler::GetRecordDescriptionText(pRecord,pStr);

		switch (pRecord->GetTag())
		{
			case TAG_RECTANGLE_SIMPLE :
			case TAG_RECTANGLE_SIMPLE_REFORMED :
			case TAG_RECTANGLE_SIMPLE_STELLATED :
			case TAG_RECTANGLE_SIMPLE_STELLATED_REFORMED :
			case TAG_RECTANGLE_SIMPLE_ROUNDED :
			case TAG_RECTANGLE_SIMPLE_ROUNDED_REFORMED :
			case TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED :
			case TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED_REFORMED :
				(*pStr) += _T("Rectangle simple\r\n\r\n");
				DescribeRectangleSimple(pRecord, pStr);
				break;

			case TAG_RECTANGLE_COMPLEX :
			case TAG_RECTANGLE_COMPLEX_STELLATED :
			case TAG_RECTANGLE_COMPLEX_ROUNDED :
			case TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED :
				(*pStr) += _T("Rectangle complex\r\n\r\n");
				DescribeRectangleComplex(pRecord, pStr);
				break;

			case TAG_RECTANGLE_COMPLEX_REFORMED :
			case TAG_RECTANGLE_COMPLEX_STELLATED_REFORMED :
			case TAG_RECTANGLE_COMPLEX_ROUNDED_REFORMED :
			case TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED_REFORMED :
				(*pStr) += _T("Rectangle complex reformed\r\n\r\n");
				DescribeRectangleComplexReformed(pRecord, pStr);
				break;

			default : DescribeInvalid(pRecord, pStr); break;
		}
	}
}

void RectangleRecordHandler::DescribeRectangleSimple(CXaraFileRecord *pRecord, StringBase *pStr)
{
	if (pRecord == NULL || pStr == NULL)
		return;

	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;

	TCHAR s[256];

	BOOL ok = TRUE;
	if (ok) ok = pRecord->ReadCoord(&CentrePoint);
	if (ok) ok = pRecord->ReadINT32(&Width);
	if (ok) ok = pRecord->ReadINT32(&Height);

	camSprintf(s,_T("Centre point\t= %d, %d\r\n"),CentrePoint.x,CentrePoint.y);
	(*pStr) += s;
	camSprintf(s,_T("Width\t\t= %d\r\n"),Width);
	(*pStr) += s;
	camSprintf(s,_T("Height\t\t= %d\r\n"),Height);
	(*pStr) += s;
}

void RectangleRecordHandler::DescribeRectangleComplex(CXaraFileRecord *pRecord, StringBase *pStr)
{
	if (pRecord == NULL || pStr == NULL)
		return;

	DocCoord CentrePoint;
	DocCoord MajorAxis;
	DocCoord MinorAxis;
	TCHAR s[256];

	BOOL ok = TRUE;

	if (ok) ok = pRecord->ReadCoord(&CentrePoint);
	if (ok) ok = pRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = pRecord->ReadCoordTrans(&MinorAxis,0,0);

	camSprintf(s,_T("Centre point\t= %d, %d\r\n"),CentrePoint.x,CentrePoint.y);
	(*pStr) += s;
	camSprintf(s,_T("Major axis\t\t= %d, %d\r\n"),MajorAxis.x,MajorAxis.y);
	(*pStr) += s;
	camSprintf(s,_T("Minor axis\t\t= %d, %d\r\n"),MinorAxis.x,MinorAxis.y);
	(*pStr) += s;
}

void RectangleRecordHandler::DescribeRectangleComplexReformed(CXaraFileRecord *pRecord, StringBase *pStr)
{
	if (pRecord == NULL || pStr == NULL)
		return;

	DocCoord MajorAxis;
	DocCoord MinorAxis;
	TCHAR s[256];

	BOOL ok = TRUE;

	if (ok) ok = pRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = pRecord->ReadCoordTrans(&MinorAxis,0,0);

	camSprintf(s,_T("Major axis\t\t= %d, %d\r\n"),MajorAxis.x,MajorAxis.y);
	(*pStr) += s;
	camSprintf(s,_T("Minor axis\t\t= %d, %d\r\n"),MinorAxis.x,MinorAxis.y);
	(*pStr) += s;
}

void RectangleRecordHandler::DescribeInvalid(CXaraFileRecord *pRecord, StringBase *pStr)
{
	if (pRecord == NULL || pStr == NULL)
		return;

	(*pStr) += _T("Invalid rectangle\r\n");
}
#endif


