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


/*
*/

// RNDCTRL.CPP
//
// Created: 29/6/93 by Will
//

#include "camtypes.h"
#include "rndctrl.h"

DECLARE_SOURCE("$Revision: 751 $");

/********************************************************************************************

>	RenderControl::RenderControl()

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/5/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default Constructor for RenderControl Class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

RenderControl::RenderControl()
{
}

/********************************************************************************************

>	BOOL RenderControl::StopRendering()

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/5/93
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if you should stop
	Purpose:	Called by a rendering routine to determine whether it should stop or not
	Errors:		-
	SeeAlso:	-

********************************************************************************************/


BOOL RenderControl::StopRendering()
{
	return FALSE;	// Force foreground rendering for now !!
}
