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

>	cxftrans.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Purpose:	Importing and exporting code for transformation attrbiutes to the
			new file format.

********************************************************************************************/

#ifndef INC_CXF_TRANSFORMS
#define INC_CXF_TRANSFORMS

/********************************************************************************************

>	class CXaraFileTransforms

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/96
	Base Class:	-
	Purpose:	Abstract class, holding code for the importing and exporting of
			transform attributes in the new file format.

********************************************************************************************/

/*
class CXaraFileTransforms
{
public:
	static BOOL Write(BaseCamelotFilter * pFilter, Matrix * pMatrix);

private:
	static BOOL WriteIdentity(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteMatrix(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteTranslation(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteGeneral(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteRotation(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteRotationCentre(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteRotationPoint(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteShearX(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteShearY(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteScale(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteScaleX(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteScaleY(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteReflectionX(BaseCamelotFilter * pFilter, Matrix * pMatrix);
	static BOOL WriteReflectionY(BaseCamelotFilter * pFilter, Matrix * pMatrix);
};
*/

#endif		// INC_CXF_TRANSFORMS
