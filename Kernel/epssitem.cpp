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
//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "epsstack.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "epssitem.h"

CC_IMPLEMENT_MEMDUMP(EPSStackItem, ListItem)

/********************************************************************************************

>	EPSStackItem::EPSStackItem()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	Initialises a stack item (i.e. sets its type to be EPSTYPE_EMPTY).

********************************************************************************************/

EPSStackItem::EPSStackItem()
{
	Type = EPSTYPE_EMPTY;
	Data.pString = NULL;
}

/********************************************************************************************

>	EPSStackItem::~EPSStackItem()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	Deletes storage associated with an EPSStackItem object.

********************************************************************************************/

EPSStackItem::~EPSStackItem()
{
	// Delete any data that is pointed to, rather than contained by, the stack item.
	if ((Type == EPSTYPE_STRING) || (Type == EPSTYPE_NAME))
	{
		delete Data.pString;
		Data.pString = NULL;
	}
}

/********************************************************************************************

>	void EPSStackItem::Init(INT32 Long)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		Long - the data to put into the stack item.
	Purpose:	Initialise an EPSStackItem object to hold a INT32.

********************************************************************************************/

void EPSStackItem::Init(INT32 Long)
{
	Type = EPSTYPE_INT32;
	Data.Long = Long;
}

/********************************************************************************************

>	void EPSStackItem::Init(FIXEDPOINT FixedPoint)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		FixedPoint - the data to put into the stack item.
	Purpose:	Initialise an EPSStackItem object to hold a fixed point value.

********************************************************************************************/

void EPSStackItem::Init(FIXEDPOINT FixedPoint)
{
	Type = EPSTYPE_FIXEDPOINT;
	Data.FixedPoint = FixedPoint;
}

/********************************************************************************************

>	void EPSStackItem::Init(double Double)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		Double - the data to put into the stack item.
	Purpose:	Initialise an EPSStackItem object to hold a double.

********************************************************************************************/

void EPSStackItem::Init(double Double)
{
	Type = EPSTYPE_DOUBLE;
	Data.Double = Double;
}

/********************************************************************************************

>	void EPSStackItem::Init(TCHAR *pString, BOOL IsName = FALSE)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		pString -  pointer to the data to put into the stack item.
				IsName - this is true if the string is a PostScript name object, and FALSE
				if it is a PostScript string object.
	Purpose:	Initialise an EPSStackItem object to hold a TCHAR * string.  
				The string is copied.

********************************************************************************************/

void EPSStackItem::Init(TCHAR *pString, BOOL IsName)
{
	if (IsName)
		Type = EPSTYPE_NAME;
	else
		Type = EPSTYPE_STRING;
		
	Data.pString = pString;
}

/********************************************************************************************

>	void EPSStackItem::Init(EPSCommand Cmd)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		Cmd - the command to put into the stack item.
	Purpose:	Initialise an EPSStackItem object to hold an EPS command.

********************************************************************************************/

void EPSStackItem::Init(EPSCommand Cmd)
{
	Type = EPSTYPE_COMMAND;
	Data.Cmd = Cmd;
}

