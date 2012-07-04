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


// base class of GDrawContext for virtualising multiple GDraws

/*
*/

#include "camtypes.h"
// camconfig.h must be included immediately after camtypes.h
//#include "camconfig.h"

#include "gdrawcon.h"

/********************************************************************************************

>	GDrawContext::GDrawContext()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/7/94
	Purpose:	Constructor. Most inherited classes will use this one. It does nothing.

********************************************************************************************/ 

GDrawContext::GDrawContext()
{
}

/********************************************************************************************

>	GDrawContext::~GDrawContext()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/7/94
	Purpose:	Destructor. Most inherited classes will use this one. It does nothing.

********************************************************************************************/ 

GDrawContext::~GDrawContext()
{
}

/********************************************************************************************

>	BOOL GDrawContext::SetDefaultBitmapParameters()

	Author:		Alex Bligh
	Created:	19/05/2005
	Purpose:	Sets the default bitmap parameters so a bitmap plot afterwards does not
				depend on the prior GDrawContext state

******************************************************************************************/ 

BOOL GDrawContext::SetDefaultBitmapParameters()
{
	BOOL ok= TRUE;
	for (INT32 i=0; i<=3; i++) ok &=
		SetBias(i, 0.0) &&
		SetGain(i, 0.0) &&
		SetInputRange(i, 0x00, 0xff) &&
		SetOutputRange(i, 0x00, 0xff) &&
		TRUE;

	ok &=
		SetBrightness(0.0) &&
		SetContone(0) &&
		SetContrast(0.0) &&
		SetGamma(1.0) &&
		SetPostGamma(1.0) &&
		SetSaturation(0.0) &&
		Sharpen(0) &&
		TRUE;
	
	SetMaxFilterSize(100);
	SetTileSmoothingFlag( FALSE );
	SetTileFilteringFlag( FALSE );
	return ok;
}

