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


#ifndef INC_FTHELPER
#define INC_FTHELPER

class CCLexFile;
struct IFTManipulator;		// MIDL helpfully declares everything struct

/********************************************************************************************

>	class FlareTemplateHelper

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/97
	Purpose:	Static function to convert Flare template file to binary Flare format

********************************************************************************************/


class FlareTemplateHelper
{
public:
	static CCLexFile* ConvertFile(CCLexFile* pFile);

protected:
	static void SetHResultError(HRESULT hr);
	static IFTManipulator* CreateTemplMan(void);
};

#endif	// INC_FTHELPER
