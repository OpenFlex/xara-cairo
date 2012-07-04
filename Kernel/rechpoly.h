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

>	rechpoly.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/06/96
	Purpose:	Handles rectangle type records from the new file format

********************************************************************************************/

#ifndef INC_RECH_POLYGON
#define INC_RECH_POLYGON

/********************************************************************************************

>	class PolygonRecordHandler

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/06/96
	Base Class:	RegularShapeRecordHandler
	Purpose:	Record handler for polygons, used when importing polygons from the new
				file format. Derived from the regular shape record handler, so we use all
				the functions in that class to complete the regular shape.

********************************************************************************************/

class PolygonRecordHandler : public RegularShapeRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(PolygonRecordHandler);

public:
	PolygonRecordHandler() {};
	~PolygonRecordHandler() {};

	// functions that must be implemented
	UINT32* GetTagList();
	BOOL HandleRecord(CXaraFileRecord* pCXaraFileRecord);

private:
	BOOL ReadPolygonSimple(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonSimpleReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonSimpleStellated(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonSimpleStellatedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonSimpleRounded(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonSimpleRoundedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonSimpleRoundedStellated(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonSimpleRoundedStellatedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonComplex(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonComplexReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonComplexStellated(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonComplexStellatedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonComplexRounded(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonComplexRoundedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonComplexRoundedStellated(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadPolygonComplexRoundedStellatedReformed(CXaraFileRecord *pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
public:
	virtual void GetRecordDescriptionText(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribePolygonComplex(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribePolygonComplexReformed(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeInvalid(CXaraFileRecord *pRecord, StringBase *pStr);
#endif
};


#endif // INC_RECH_RECTANFLE
