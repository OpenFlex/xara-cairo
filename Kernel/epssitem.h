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

#ifndef _INC_EPS_STACK_ITEM_H
#define _INC_EPS_STACK_ITEM_H

// Forward definitions.
class ListItem;
class FIXEDPOINT;

/********************************************************************************************

>	class EPSStackItem : public ListItem

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	This class provides objects that make up an EPSStack object.  The object
				is polymorphic, and can contain either a INT32, a double, or a TCHAR* string
				object.
	SeeAlso:	EPSStack

********************************************************************************************/

class EPSStackItem : public ListItem
{
	CC_DECLARE_MEMDUMP(EPSStackItem);

public:
	EPSStackItem ();
	~EPSStackItem ();
	
	void Init ( INT32 );
	void Init ( FIXEDPOINT );
	void Init ( double );
	void Init ( TCHAR *Str, BOOL IsName = FALSE );
	void Init ( EPSCommand );
	
	union
	{
		INT32		Long;
		FIXEDPOINT	FixedPoint;
		double		Double;
		TCHAR		*pString;
		EPSCommand	Cmd;
	} Data;

	EPSType Type;
};

#endif
