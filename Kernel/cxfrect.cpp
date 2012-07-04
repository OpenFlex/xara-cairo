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

>	cxfrect.cpp

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Purpose:	Importing and exporting code for rectangles to and from the new
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
#include "cxfrect.h"

/********************************************************************************************

>	BOOL CXaraFileRectangle::WriteRectangle(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleSimple(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleSimpleReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleSimpleStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleSimpleStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleSimpleRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleSimpleRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleSimpleRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleSimpleRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleComplexReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleComplexStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleComplexStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleComplexRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleComplexRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleComplexRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileRectangle::WriteRectangleComplexRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Inputs:		pFilter - filter to use
				pShape  - regular shape to save to filter
	Returns:	boolean value indicating success of writing record to filter
	Purpose:	Writes a regular shape record to the filter

********************************************************************************************/

BOOL CXaraFileRectangle::WriteRectangle(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	// we need to determine how is rectangle has been altered, i.e. rotated, rounded, stellated
	// or reformed. using this information we jump to one of the following functions to write
	// the information out for us.

	const INT32 REFORMED	= 0x1;
	const INT32 STELLATED	= 0x2;
	const INT32 ROUNDED	= 0x4;
	const INT32 COMPLEX	= 0x8;

	INT32 RectangleType = 0;

	if (IsReformed(pShape)) RectangleType |= REFORMED;
	if (IsStellated(pShape)) RectangleType |= STELLATED;
	if (IsRounded(pShape)) RectangleType |= ROUNDED;
	if (IsComplex(pShape)) RectangleType |= COMPLEX;

	switch (RectangleType)
	{
		case 0									: ok = WriteRectangleSimple(pFilter, pShape); break;
		case REFORMED							: ok = WriteRectangleSimpleReformed(pFilter, pShape); break;
		case STELLATED							: ok = WriteRectangleSimpleStellated(pFilter, pShape); break;
		case STELLATED|REFORMED					: ok = WriteRectangleSimpleStellatedReformed(pFilter, pShape); break;
		case ROUNDED							: ok = WriteRectangleSimpleRounded(pFilter, pShape); break;
		case ROUNDED|REFORMED					: ok = WriteRectangleSimpleRoundedReformed(pFilter, pShape); break;
		case ROUNDED|STELLATED					: ok = WriteRectangleSimpleRoundedStellated(pFilter, pShape); break;
		case ROUNDED|STELLATED|REFORMED			: ok = WriteRectangleSimpleRoundedStellatedReformed(pFilter, pShape); break;
		case COMPLEX							: ok = WriteRectangleComplex(pFilter, pShape); break;
		case COMPLEX|REFORMED					: ok = WriteRectangleComplexReformed(pFilter, pShape); break;
		case COMPLEX|STELLATED					: ok = WriteRectangleComplexStellated(pFilter, pShape); break;
		case COMPLEX|STELLATED|REFORMED			: ok = WriteRectangleComplexStellatedReformed(pFilter, pShape); break;
		case COMPLEX|ROUNDED					: ok = WriteRectangleComplexRounded(pFilter, pShape); break;
		case COMPLEX|ROUNDED|REFORMED			: ok = WriteRectangleComplexRoundedReformed(pFilter, pShape); break;
		case COMPLEX|ROUNDED|STELLATED			: ok = WriteRectangleComplexRoundedStellated(pFilter, pShape); break;
		case COMPLEX|ROUNDED|STELLATED|REFORMED	: ok = WriteRectangleComplexRoundedStellatedReformed(pFilter, pShape); break;
		default									: ok = WriteShapeInvalid(pFilter, pShape); break;
	}

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleSimple(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_SIMPLE, TAG_RECTANGLE_SIMPLE_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleSimpleReformed(BaseCamelotFilter *pFilter, NodeRegularShape *pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_SIMPLE_REFORMED, TAG_RECTANGLE_SIMPLE_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = Rec.WritePath(GetEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}
	
BOOL CXaraFileRectangle::WriteRectangleSimpleStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_SIMPLE_STELLATED, TAG_RECTANGLE_SIMPLE_STELLATED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleSimpleStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_SIMPLE_STELLATED_REFORMED, TAG_RECTANGLE_SIMPLE_STELLATED_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = Rec.WritePath(GetPrimaryEdgePath(pShape));
	if (ok) ok = Rec.WritePath(GetSecondaryEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleSimpleRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_SIMPLE_ROUNDED, TAG_RECTANGLE_SIMPLE_ROUNDED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetCurvature(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleSimpleRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_SIMPLE_ROUNDED_REFORMED, TAG_RECTANGLE_SIMPLE_ROUNDED_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetCurvature(pShape));
	if (ok) ok = Rec.WritePath(GetEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleSimpleRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED, TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetPrimaryCurvature(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetSecondaryCurvature(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleSimpleRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED_REFORMED, TAG_RECTANGLE_SIMPLE_ROUNDED_STELLATED_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetPrimaryCurvature(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetSecondaryCurvature(pShape));
	if (ok) ok = Rec.WritePath(GetPrimaryEdgePath(pShape));
	if (ok) ok = Rec.WritePath(GetSecondaryEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_COMPLEX, TAG_RECTANGLE_COMPLEX_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetMinorAxis(pShape),0,0);
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleComplexReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_COMPLEX_REFORMED, TAG_RECTANGLE_COMPLEX_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoordTrans(GetUTMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetUTMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteMatrix(GetTransformMatrix(pShape));
	if (ok) ok = Rec.WritePath(GetEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleComplexStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_COMPLEX_STELLATED, TAG_RECTANGLE_COMPLEX_STELLATED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteDOUBLE(GetStellationRadius(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetStellationOffset(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleComplexStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_COMPLEX_STELLATED_REFORMED, TAG_RECTANGLE_COMPLEX_STELLATED_REFORMED_SIZE);

	ok = Rec.Init();
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

BOOL CXaraFileRectangle::WriteRectangleComplexRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_COMPLEX_ROUNDED, TAG_RECTANGLE_COMPLEX_ROUNDED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteDOUBLE(GetCurvature(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleComplexRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_COMPLEX_ROUNDED_REFORMED, TAG_RECTANGLE_COMPLEX_ROUNDED_REFORMED_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoordTrans(GetUTMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetUTMinorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteMatrix(GetTransformMatrix(pShape));
	if (ok) ok = Rec.WriteDOUBLE(GetCurvature(pShape));
	if (ok) ok = Rec.WritePath(GetEdgePath(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileRectangle::WriteRectangleComplexRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED, TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED_SIZE);

	ok = Rec.Init();
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

BOOL CXaraFileRectangle::WriteRectangleComplexRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED_REFORMED, TAG_RECTANGLE_COMPLEX_ROUNDED_STELLATED_REFORMED_SIZE);

	ok = Rec.Init();
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

