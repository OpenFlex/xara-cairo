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

// REGION.CPP
//
// Created: 08/6/93 by Will
//

#include "camtypes.h"
#include "region.h"

DECLARE_SOURCE("$Revision: 751 $");

/********************************************************************************************

>	Region::Region()

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/6/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default Constructor for Region Class. Creats a Null region.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

Region::Region()
{
	CurrentRegion.lox = 0;
	CurrentRegion.loy = 0;
	CurrentRegion.hix = 0;
	CurrentRegion.hiy = 0;
}

/********************************************************************************************

>	Region::Region(DocRect RectRegion)

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/6/93
	Inputs:		A DocRect describing the bounding rectangle of the region.
	Outputs:	-
	Returns:	-
	Purpose:	Creates a Region from the specified rectangle.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

Region::Region(DocRect RectRegion)
{
	CurrentRegion = RectRegion;
}

/********************************************************************************************

>	BOOL Region::MergeRegion(Region *RegionToMerge)

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/6/93
	Inputs:		A pointer to a region to merge
	Outputs:	-
	Returns:	TRUE if merged OK, or FALSE if failed.
	Purpose:	Merges one region with another.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL Region::MergeRegion(Region *RegionToMerge)
{
	return FALSE;
}
