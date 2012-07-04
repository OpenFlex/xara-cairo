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

>	rechrshp.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Purpose:	Base class record handler for regular shapes

********************************************************************************************/


#ifndef INC_RECH_REGULARSHAPE
#define INC_RECH_REGULARSHAPE

/********************************************************************************************

>	class RegularShapeRecordHandler

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/96
	Base Class:	CamelotRecordHandler
	Purpose:	Base record handler for regular shapes, used when importing regular shapes
				from the new file format.

********************************************************************************************/

class RegularShapeRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(RegularShapeRecordHandler);

public:
	RegularShapeRecordHandler() {};
	~RegularShapeRecordHandler() {};
	
	// functions that must be implemented
	UINT32* GetTagList();
	BOOL HandleRecord(CXaraFileRecord* pCXaraFileRecord);

private:
	// functions for reading regular shapes from the file
	BOOL ReadShapeGeneralPhase1(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadShapeGeneralPhase2(CXaraFileRecord *pCXaraFileRecord);

protected:
	virtual BOOL ReadShapeInvalid(CXaraFileRecord *pCXaraFileRecord);
	
protected:
	// functions for creating regular shapes and filling in their data structures.

	BOOL SetupShape(NodeRegularShape *pShape);
	BOOL InvalidateCache(NodeRegularShape *pShape);

	BOOL SetCentrePoint(NodeRegularShape *pShape, const DocCoord & CentrePoint);
	BOOL SetUTCentrePoint(NodeRegularShape *pShape, const DocCoord & UTCentrePoint);
	BOOL SetMajorAxis(NodeRegularShape *pShape, const DocCoord & MajorAxis);
	BOOL SetMinorAxis(NodeRegularShape *pShape, const DocCoord & MinorAxis);
	BOOL SetHeightAndWidth(NodeRegularShape *pShape, const INT32 & Height, const INT32 & Width);
	BOOL SetNumberOfSides(NodeRegularShape *pShape, const INT32 & NumSides);
	
	BOOL SetCurvature(NodeRegularShape *pShape, const double &Curvature);
	BOOL SetPrimaryCurvature(NodeRegularShape *pShape, const double & PrimaryCurvature);
	BOOL SetSecondaryCurvature(NodeRegularShape *pShape, const double & SecondaryCurvature);
	BOOL SetStellationRadius(NodeRegularShape *pShape, const double & StellationRadius);
	BOOL SetStellationOffset(NodeRegularShape *pShape, const double & StellationOffset);
	
	BOOL SetTransformMatrix(NodeRegularShape *pShape, const Matrix & NewMatrix);
	
	BOOL SetIsCircular(NodeRegularShape *pShape, const BOOL & IsCircular);
	BOOL SetIsStellated(NodeRegularShape *pShape, const BOOL & IsStellated);
	BOOL SetIsRounded(NodeRegularShape *pShape, const BOOL & Value);

	BOOL SetFlags(NodeRegularShape *pShape, const BYTE &Value);

#ifdef XAR_TREE_DIALOG
public:
	virtual void GetRecordDescriptionText(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeShapeGeneralPhase1(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeShapeGeneralPhase2(CXaraFileRecord *pRecord, StringBase *pStr);
	virtual void DescribeInvalid(CXaraFileRecord *pRecord, StringBase *pStr);
#endif
};

#endif // INC_RECH_REGULARSHAPE
