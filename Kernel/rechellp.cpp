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

>	rechellp.cpp

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Purpose:	Functions for the class to handle importing ellipse records from
			the new file format

********************************************************************************************/

#include "camtypes.h"

#include "nodershp.h"

#include "cxftags.h"

#include "rechrshp.h"
#include "rechellp.h"

// to match the declare in the header file
CC_IMPLEMENT_DYNAMIC(EllipseRecordHandler, RegularShapeRecordHandler);

/********************************************************************************************

>	UINT32* EllipseRecordHandler::GetTagList()

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Inputs:		-
	Returns:	UINT32* to an array of records handled by this class. The last entry in the
				array is CXFRH_TAG_LIST_END
	Purpose:	Returns an array of records handled by this class.
	See Also:	EllispeRecordHandler::HandleRecord

********************************************************************************************/

UINT32* EllipseRecordHandler::GetTagList()
{
	static UINT32 TagList[] = {TAG_ELLIPSE_SIMPLE,
								TAG_ELLIPSE_COMPLEX,
								CXFRH_TAG_LIST_END};
	return &TagList[0];
}

/********************************************************************************************

>	BOOL EllispeRecordHandler::HandleRecord(CXaraFileRecord * pCXaraFileRecord)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Inputs:		pCXaraFileRecord - CXaraFileRecord object to read
	Returns:	TRUE if successful, FALSE otherwise
	Purpose:	Handles ellipse type records for the new file format

********************************************************************************************/

BOOL EllipseRecordHandler::HandleRecord(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok;

	switch (pCXaraFileRecord->GetTag())
	{
		case TAG_ELLIPSE_SIMPLE		: ok = ReadEllipseSimple(pCXaraFileRecord); break;
		case TAG_ELLIPSE_COMPLEX	: ok = ReadEllipseComplex(pCXaraFileRecord); break;
		default						: ok = ReadShapeInvalid(pCXaraFileRecord); break;
	}
	
	return ok;
}

/********************************************************************************************

>	BOOL EllipseRecordHandler::ReadEllipseSimple(pCXaraFileRecord); break;
	BOOL EllipseRecordHandler::ReadEllipseComplex(pCXaraFileRecord); break;

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Inputs:		pCXaraFileRecord - pointer to the record to read
	Returns:	TRUE if successfull, false otherwise
	Purpose:	Reads in an ellise record

********************************************************************************************/

BOOL EllipseRecordHandler::ReadEllipseSimple(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape * pEllipse;
	DocCoord CentrePoint;
	INT32 Height;
	INT32 Width;

	pEllipse = new NodeRegularShape;

	if (ok) ok = SetupShape(pEllipse);
	if (ok) ok = SetIsCircular(pEllipse, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pEllipse, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadINT32(&Width);
	if (ok) ok = pCXaraFileRecord->ReadINT32(&Height);
	if (ok) ok = SetHeightAndWidth(pEllipse, Height, Width);

	if (ok) ok = InvalidateCache(pEllipse);
	if (ok) ok = InsertNode(pEllipse);

	return ok;
}

BOOL EllipseRecordHandler::ReadEllipseComplex(CXaraFileRecord *pCXaraFileRecord)
{
	BOOL ok = TRUE;

	NodeRegularShape *pEllipse;
	DocCoord CentrePoint;
	DocCoord MajorAxis;
	DocCoord MinorAxis;

	pEllipse = new NodeRegularShape;

	if (ok) ok = SetupShape(pEllipse);
	if (ok) ok = SetIsCircular(pEllipse, TRUE);

	if (ok) ok = pCXaraFileRecord->ReadCoord(&CentrePoint);
	if (ok) ok = SetCentrePoint(pEllipse, CentrePoint);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MajorAxis,0,0);
	if (ok) ok = SetMajorAxis(pEllipse, MajorAxis);

	if (ok) ok = pCXaraFileRecord->ReadCoordTrans(&MinorAxis,0,0);
	if (ok) ok = SetMinorAxis(pEllipse, MinorAxis);

	if (ok) ok = InvalidateCache(pEllipse);
	if (ok) ok = InsertNode(pEllipse);

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
void EllipseRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase *pStr)
{
	if (pRecord != NULL && pStr != NULL)
	{
		// Call base class first
		// This outputs the tag and size
		CamelotRecordHandler::GetRecordDescriptionText(pRecord,pStr);

		switch (pRecord->GetTag())
		{
			case TAG_ELLIPSE_SIMPLE : DescribeEllipseSimple(pRecord, pStr); break;
			case TAG_ELLIPSE_COMPLEX : DescribeEllipseComplex(pRecord, pStr); break;
			default : DescribeInvalid(pRecord, pStr); break;
		}
	}
}

void EllipseRecordHandler::DescribeEllipseSimple(CXaraFileRecord *pRecord, StringBase *pStr)
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

	(*pStr) += _T("Simple ellipse\r\n\r\n");

	camSprintf(s,_T("Centre point\t= %d, %d\r\n"),CentrePoint.x,CentrePoint.y);
	(*pStr) += s;
	camSprintf(s,_T("Width\t\t= %d\r\n"),Width);
	(*pStr) += s;
	camSprintf(s,_T("Height\t\t= %d\r\n"),Height);
	(*pStr) += s;
}

void EllipseRecordHandler::DescribeEllipseComplex(CXaraFileRecord *pRecord, StringBase *pStr)
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

	(*pStr) += _T("Complex ellipse\r\n\r\n");
	camSprintf(s,_T("Centre point\t= %d, %d\r\n"),CentrePoint.x,CentrePoint.y);
	(*pStr) += s;
	camSprintf(s,_T("Major axis\t\t= %d, %d\r\n"),MajorAxis.x,MajorAxis.y);
	(*pStr) += s;
	camSprintf(s,_T("Minor axis\t\t= %d, %d\r\n"),MinorAxis.x,MinorAxis.y);
	(*pStr) += s;
}

void EllipseRecordHandler::DescribeInvalid(CXaraFileRecord *pRecord, StringBase *pStr)
{
	if (pRecord == NULL || pStr == NULL)
		return;

	(*pStr) += _T("Invalid ellipse\r\n");
}
#endif

