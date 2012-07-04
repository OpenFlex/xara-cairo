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

>	oilpanse.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/07/96
	Purpose:	Specification of the OIL related Panose code
	SeeAlso:	kernel\ccpanose.h, kernel\ccpanose.cpp

********************************************************************************************/

#ifndef INC_OIL_PANOSE
#define INC_OIL_PANOSE

/********************************************************************************************

>	class OILPanose

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/07/96
	Base Class:	-
	Purpose:	Abstract, static class, holding OIL related Panose code
	SeeAlso:	CCPanose (the kernel Panose class)

********************************************************************************************/

class OILPanose
{
private:
	static CDC *pMyCDC;
	static BOOL IsInitialised;

public:
	static BOOL Init(CDC *pCDC);
	static BOOL DeInit();
	static BOOL GetPanoseNumber(ENUMLOGFONT *pEnumLogFont, CCPanose *pPanose);
};

#endif // INC_OIL_PANOSE
