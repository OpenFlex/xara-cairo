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

>	cxfellp.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Purpose:	Class for exporting ellipses in the new file format

********************************************************************************************/

#ifndef INC_CXF_ELLIPSE
#define INC_CXF_ELLIPSE

/********************************************************************************************

>	class CXaraFileEllipse : public CXaraFileRegularShape

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/06/96
	Base Class:	CXaraFIleRegularShape
	Purpose:	Abstract class holding code for exporting ellipses in the new file format
	SeeAlso:	class NodeRegularShape

********************************************************************************************/

class CXaraFileEllipse : public CXaraFileRegularShape
{
	// this is an abstract class, so no object of this class will (should) be created
public:
	static BOOL WriteEllipse(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteEllipseSimple(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
	static BOOL WriteEllipseComplex(BaseCamelotFilter * pFilter, NodeRegularShape * pShape);
};

#endif // include INC_CXF_ELLIPSE
