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
// */ 

#include "camtypes.h"
#include "sentryop.h" 


CC_IMPLEMENT_DYNCREATE(SentryOperation, Operation)

#define new CAM_DEBUG_NEW                                                                    

/********************************************************************************************

>	SentryOperation::SentryOperation()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	SentryOperation constructor, calls the constructor of the base  class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

SentryOperation::SentryOperation(): Operation()
{
}

/********************************************************************************************

>	SentryOperation::~SentryOperation()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	SentryOperation destructor 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

SentryOperation::~SentryOperation()
{
}

