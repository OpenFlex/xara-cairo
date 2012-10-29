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

// UserCoords - ie SpreadCoords relative to the user specified origin

/*
*/

#include "camtypes.h"
#include "usercord.h"

DECLARE_SOURCE("$Revision: 1282 $");

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/********************************************************************************************
>	DocCoord UserCoord::ToSpread(Spread* pSpread)

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/9/95
	Inputs:		pSpread -
	Returns:	SpreadCoord
	purpose:	Convert between UserCoords and SpreadCoords (AKA DocCoords - Aarrgghh!)
********************************************************************************************/

DocCoord UserCoord::ToSpread(Spread* pSpread)
{
	DocCoord UserOrigin(0,0);
	if (pSpread!=NULL)
		UserOrigin=pSpread->GetUserOrigin();
	else
		ERROR3("UserCoord::ToSpread() - pSpread==NULL");

	return DocCoord(this->x+UserOrigin.x, this->y+UserOrigin.y);
}
