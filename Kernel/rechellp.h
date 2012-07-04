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

>	rechellp.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Purpose:	Handles ellipse type records from the new file format

********************************************************************************************/

#ifndef INC_RECH_ELLIPSE
#define INC_RECH_ELLIPSE

/********************************************************************************************

>	class EllipseRecordHandler

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Base Class:	RegularShapeRecordHandler
	Purpose:	Record handler for ellipses, used when importing ellipses from the new
				file format. Derived from the regular shape record handler, so we use
				all the functions in that class to complete the regular shape.

********************************************************************************************/

class EllipseRecordHandler : public RegularShapeRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(EllipseRecordHandler);

public:
	EllipseRecordHandler() {};
	~EllipseRecordHandler() {};

	// functions that must be implemented
	UINT32* GetTagList();
	BOOL HandleRecord(CXaraFileRecord* pCXaraFileRecord);

private:
	BOOL ReadEllipseSimple(CXaraFileRecord* pCXaraFileRecord);
	BOOL ReadEllipseComplex(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
public:
	virtual void GetRecordDescriptionText(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeEllipseSimple(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeEllipseComplex(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeInvalid(CXaraFileRecord *pRecord, StringBase *pStr);
#endif
};

#endif // INC_RECH_ELLIPSE
