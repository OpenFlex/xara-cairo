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

>	cxfpoly.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/06/96
	Purpose:	Abstract class holding exporting code for polygons in the new file format

********************************************************************************************/

#ifndef INC_CXF_POLYGON
#define INC_CXF_POLYGON

/********************************************************************************************

>	class CXaraFilePolygon

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/06/96
	Base Class:	CXaraFileRegularShape
	Purpose:	Abstract class holding exporting code for polygon for the new file format
	SeeAlso:	class NodeRe

********************************************************************************************/

class CXaraFilePolygon : public CXaraFileRegularShape
{
public:
	static BOOL WritePolygon(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WritePolygonComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WritePolygonComplexReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WritePolygonComplexStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WritePolygonComplexStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WritePolygonComplexRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WritePolygonComplexRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WritePolygonComplexRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WritePolygonComplexRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
};

#endif // include INC_CXF_POLYGON

