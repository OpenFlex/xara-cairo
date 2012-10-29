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



#include "camtypes.h" 

/********************************************************************************************

>	OilCoord WorkCoord::ToOil(const WorkCoord& scrollOffset)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/8/93
	Inputs:		Scroll offset.
	Outputs:	None
	Returns:	None.
	Purpose:	Converts a WorkCoord to an OilCoord.
	Errors:		None.

********************************************************************************************/

OilCoord WorkCoord::ToOil(const WorkCoord& scrollOffset)
{
	OilCoord result( INT32(x - scrollOffset.x), INT32(y - scrollOffset.y) );
	
	return result;
}

/********************************************************************************************

>	void WorkCoord::ToOil(const WorkCoord& scrollOffset, OilCoord *result)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/8/93
	Inputs:		Scroll offset.
	Outputs:	None
	Returns:	None.
	Purpose:	Converts a WorkCoord to an OilCoord.
	Errors:		None.

********************************************************************************************/

void WorkCoord::ToOil(const WorkCoord& scrollOffset, OilCoord *result)
{
	result->x = INT32(x - scrollOffset.x); 
	result->y = INT32(y - scrollOffset.y);
}
 
