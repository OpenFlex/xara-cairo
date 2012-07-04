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

>	cxfpoly.cpp

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/06/96
	Purpose:	Importing and exporting code for polygons to and from the new
				file format.
	SeeAlso:	Class NodeRegularShape

********************************************************************************************/

#include "camtypes.h"

//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "paths.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "nodershp.h"
#include "cxftags.h"
//#include "cxfdefs.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "camfiltr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "cxfile.h"
//#include "cxfrec.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "cxfrgshp.h"
#include "cxfpoly.h"

/********************************************************************************************

>	BOOL CXaraFilePolygon::WritePolygon(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFilePolygon::WritePolygonComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFilePolygon::WritePolygonComplexReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFilePolygon::WritePolygonComplexStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFilePolygon::WritePolygonComplexStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFilePolygon::WritePolygonComplexRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFilePolygon::WritePolygonComplexRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFilePolygon::WritePolygonComplexRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFilePolygon::WritePolygonComplexRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/06/96
	Inputs:		pFilter - filter to use
				pShape  - regular shape to save to filter
	Returns:	boolean value indicating success of writing record to filter
	Purpose:	Writes a polygon record to the filter

********************************************************************************************/

BOOL CXaraFilePolygon::WritePolygon(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	// we need to determine how is polygon has been altered, i.e. rotated, rounded, stellated
	// or reformed. using this information we jump to one of the following functions to write
	// the information out for us.

	const INT32 REFORMED	= 0x1;
	const INT32 STELLATED	= 0x2;
	const INT32 ROUNDED	= 0x4;

	INT32 PolygonType = 0;

	if (IsReformed(pShape)) PolygonType |= REFORMED;
	if (IsStellated(pShape)) PolygonType |= STELLATED;
	if (IsRounded(pShape)) PolygonType |= ROUNDED;

	switch (PolygonType)
	{
		case 0							: ok = WritePolygonComplex(pFilter, pShape); break;
		case REFORMED					: ok = WritePolygonComplexReformed(pFilter, pShape); break;
		case STELLATED					: ok = WritePolygonComplexStellated(pFilter, pShape); break;
		case STELLATED|REFORMED			: ok = WritePolygonComplexStellatedReformed(pFilter, pShape); break;
		case ROUNDED					: ok = WritePolygonComplexRounded(pFilter, pShape); break;
		case ROUNDED|REFORMED			: ok = WritePolygonComplexRoundedReformed(pFilter, pShape); break;
		case ROUNDED|STELLATED			: ok = WritePolygonComplexRoundedStellated(pFilter, pShape); break;
		case ROUNDED|STELLATED|REFORMED	: ok = WritePolygonComplexRoundedStellatedReformed(pFilter, pShape); break;
		default							: ok = WriteShapeInvalid(pFilter, pShape); break;
	}

	return ok;
}

BOOL CXaraFilePolygon::WritePolygonComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_POLYGON_COMPLEX, TAG_POLYGON_COMPLEX_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteUINT16(GetNumberOfSides(pShape));
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetMinorAxis(pShape),0,0);
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFilePolygon::WritePolygonComplexReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_POLYGON_COMPLEX_REFORMED, TAG_POLYGON_COMPLEX_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteUINT16(GetNumberOfSides(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetUTMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetUTMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteMatrix(GetTransformMatrix(pShape));
	if (ok) ok = Rec.WritePath(GetEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFilePolygon::WritePolygonComplexStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_POLYGON_COMPLEX_STELLATED, TAG_POLYGON_COMPLEX_STELLATED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteUINT16(GetNumberOfSides(pShape));
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFilePolygon::WritePolygonComplexStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_POLYGON_COMPLEX_STELLATED_REFORMED, TAG_POLYGON_COMPLEX_STELLATED_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteUINT16(GetNumberOfSides(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetUTMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetUTMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteMatrix(GetTransformMatrix(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = Rec.WritePath(GetPrimaryEdgePath(pShape));
	if (ok) ok = Rec.WritePath(GetSecondaryEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFilePolygon::WritePolygonComplexRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_POLYGON_COMPLEX_ROUNDED, TAG_POLYGON_COMPLEX_ROUNDED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteUINT16(GetNumberOfSides(pShape));
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteDOUBLE(GetCurvature(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFilePolygon::WritePolygonComplexRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_POLYGON_COMPLEX_ROUNDED_REFORMED, TAG_POLYGON_COMPLEX_ROUNDED_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteUINT16(GetNumberOfSides(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetUTMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetUTMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteMatrix(GetTransformMatrix(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetCurvature(pShape));
	if (ok) ok = Rec.WritePath(GetEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFilePolygon::WritePolygonComplexRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_POLYGON_COMPLEX_ROUNDED_STELLATED, TAG_POLYGON_COMPLEX_ROUNDED_STELLATED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteUINT16(GetNumberOfSides(pShape));
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetPrimaryCurvature(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetSecondaryCurvature(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFilePolygon::WritePolygonComplexRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_POLYGON_COMPLEX_ROUNDED_STELLATED_REFORMED, TAG_POLYGON_COMPLEX_ROUNDED_STELLATED_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteUINT16(GetNumberOfSides(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetUTMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetUTMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteMatrix(GetTransformMatrix(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetPrimaryCurvature(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetSecondaryCurvature(pShape));
	if (ok) ok = Rec.WritePath(GetPrimaryEdgePath(pShape));
	if (ok) ok = Rec.WritePath(GetSecondaryEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

