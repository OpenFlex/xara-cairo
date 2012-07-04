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

>	cxfellp.cpp

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Purpose:	Importing and exporting code for regular shapes to and from the new
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
#include "cxfellp.h"

/********************************************************************************************

>	BOOL CXaraFileEllipse::WriteEllipse(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileEllipse::WriteEllipseSimple(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
	BOOL CXaraFileEllipse::WriteEllipseComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Inputs:		pFilter - filter to use
				pShape  - shape to save out
	Returns:	boolean value indicating success or writing record
	Purpose:	Writes an ellipse record to the filter

********************************************************************************************/

BOOL CXaraFileEllipse::WriteEllipse(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	// need to determine whether this is a simple shape or not, i.e. is the corresponding matrix
	// the identity matrix?

	if (IsSimple(pShape))
	{
		ok = WriteEllipseSimple(pFilter, pShape);
	}
	else
	{
		ok = WriteEllipseComplex(pFilter, pShape);
	}

	return ok;
}

BOOL CXaraFileEllipse::WriteEllipseSimple(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_ELLIPSE_SIMPLE, TAG_ELLIPSE_SIMPLE_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteINT32(GetWidth(pShape));
	if (ok) ok = Rec.WriteINT32(GetHeight(pShape));
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

BOOL CXaraFileEllipse::WriteEllipseComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape)
{
	BOOL ok;

	CamelotFileRecord Rec(pFilter,TAG_ELLIPSE_COMPLEX, TAG_ELLIPSE_COMPLEX_SIZE);

	ok = Rec.Init();
	if (ok) ok = Rec.WriteCoord(GetCentrePoint(pShape));
	if (ok) ok = Rec.WriteCoordTrans(GetMajorAxis(pShape),0,0);
	if (ok) ok = Rec.WriteCoordTrans(GetMinorAxis(pShape),0,0);
	if (ok) ok = pFilter->Write(&Rec);

	return ok;
}

