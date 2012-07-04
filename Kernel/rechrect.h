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

>	rechrect.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/06/96
	Purpose:	Handles rectangle type records from the new file format
	SeeAlso:	<???>

********************************************************************************************/

#ifndef INC_RECH_RECTANGLE
#define INC_RECH_RECTANGLE

/********************************************************************************************

>	class RectangleRecordHandler

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/06/96
	Base Class:	RegularShapeRecordHandler
	Purpose:	Record handler for rectangles, used when importing rectangles from the new
				file format. Derived from the regular shape record handler, so we use all
				the functions in that class to complete the regular shape.

********************************************************************************************/

class RectangleRecordHandler : public RegularShapeRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(RectangleRecordHandler);

public:
	RectangleRecordHandler() {};
	~RectangleRecordHandler() {};

	// functions that must be implemented
	UINT32* GetTagList();
	BOOL HandleRecord(CXaraFileRecord* pCXaraFileRecord);

private:
	BOOL ReadRectangleSimple(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleSimpleReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleSimpleStellated(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleSimpleStellatedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleSimpleRounded(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleSimpleRoundedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleSimpleRoundedStellated(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleSimpleRoundedStellatedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleComplex(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleComplexReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleComplexStellated(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleComplexStellatedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleComplexRounded(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleComplexRoundedReformed(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleComplexRoundedStellated(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadRectangleComplexRoundedStellatedReformed(CXaraFileRecord *pCXaraFileRecord);

private:
	static const INT32 NumberOfSides;

#ifdef XAR_TREE_DIALOG
public:
	virtual void GetRecordDescriptionText(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeRectangleSimple(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeRectangleComplex(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeRectangleComplexReformed(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeInvalid(CXaraFileRecord *pRecord, StringBase *pStr);
#endif
};


#endif // INC_RECH_RECTANFLE
