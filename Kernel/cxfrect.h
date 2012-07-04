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

>	cxfrect.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Purpose:	Abstract lass holding exporting code for rectangles in the new file format

********************************************************************************************/

#ifndef INC_CXF_RECTANGLE
#define INC_CXF_RECTANGLE

/********************************************************************************************

>	class CXaraFileRectangle

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Base Class:	CXaraFileRegularShape
	Purpose:	Abstract class holding exporting code for rectangles for the new file format
	SeeAlso:	class NodeRe

********************************************************************************************/

class CXaraFileRectangle : public CXaraFileRegularShape
{
public:
	static BOOL WriteRectangle(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleSimple(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleSimpleReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleSimpleStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleSimpleStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleSimpleRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleSimpleRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleSimpleRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleSimpleRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleComplexReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleComplexStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleComplexStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleComplexRounded(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleComplexRoundedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleComplexRoundedStellated(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteRectangleComplexRoundedStellatedReformed(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
};

#endif // include INC_CXF_RECTANGLE
