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

>	cxfrgshp.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Purpose:	Abstract Base class for exporting regular shapes

********************************************************************************************/

#ifndef INC_CXF_REGULAR_SHAPE
#define INC_CXF_REGULAR_SHAPE

/********************************************************************************************

>	class CXaraFileRegularShape

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Base Class:	-
	Purpose:	Abstract class holding importing and exporting code for regular
				shapes to and from the new file format
	SeeAlso:	class NodeRegularShape
				(friend class of NodeRegularShape)

********************************************************************************************/

class CXaraFileRegularShape
{
	// this is an abstract class, so no object of this class will (should) be created
public:
	static BOOL WritePreChildrenNative(BaseCamelotFilter * pFilter, NodeRegularShape *pShape);
	static BOOL WritePreChildrenWeb(BaseCamelotFilter * pFilter, NodeRegularShape *pShape);

protected:
	static BOOL WriteShapeNative(BaseCamelotFilter * pFilter, NodeRegularShape *pShape);
	static BOOL WriteShapeWeb(BaseCamelotFilter *pFilter, NodeRegularShape *pShape);

	static BOOL FixOldShape(NodeRegularShape *pShape);

	static BOOL WriteShapeGeneral(BaseCamelotFilter * pFilter, NodeRegularShape *pShape);
	static BOOL WriteShapeInvalid(BaseCamelotFilter * pFilter, NodeRegularShape *pShape);


// other functions
public:
	static BOOL IsEllipse(NodeRegularShape *pShape);
	static BOOL IsRectangle(NodeRegularShape *pShape);
	static BOOL IsSimple(NodeRegularShape *pShape);
	static BOOL IsComplex(NodeRegularShape *pShape);
	static BOOL IsRounded(NodeRegularShape *pShape);
	static BOOL IsStellated(NodeRegularShape *pShape);
	static BOOL IsReformed(NodeRegularShape *pShape);

protected:
	static BYTE GetFlags(NodeRegularShape *pShape);

	static DocCoord GetCentrePoint(NodeRegularShape *pShape);
	static DocCoord GetMajorAxis(NodeRegularShape *pShape);
	static DocCoord GetMinorAxis(NodeRegularShape *pShape);
	static DocCoord GetUTCentrePoint(NodeRegularShape *pShape);
	static DocCoord GetUTMajorAxis(NodeRegularShape *pShape);
	static DocCoord GetUTMinorAxis(NodeRegularShape *pShape);
	
	static INT32 GetHeight(NodeRegularShape *pShape);
	static INT32 GetWidth(NodeRegularShape *pShape);

	static UINT16 GetNumberOfSides(NodeRegularShape *pShape);

	static double GetCurvature(NodeRegularShape *pShape);
	static double GetPrimaryCurvature(NodeRegularShape *pShape);
	static double GetSecondaryCurvature(NodeRegularShape *pShape);
	
	static double GetStellationRadius(NodeRegularShape *pShape);
	static double GetStellationOffset(NodeRegularShape *pShape);

	static Matrix GetTransformMatrix(NodeRegularShape *pShape);

	static Path * GetEdgePath(NodeRegularShape *pShape);
	static Path * GetPrimaryEdgePath(NodeRegularShape *pShape);
	static Path * GetSecondaryEdgePath(NodeRegularShape *pShape);

// member variables
protected:
	const static double mEpsilon;
};

#endif // include CXF_REGULAR_SHAPE
