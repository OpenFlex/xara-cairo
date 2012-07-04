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
#include "epscdef.h"

/********************************************************************************************

>	EPSCommentDef::EPSCommentDef ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Inputs:		-
	Returns:	-
	Purpose:	Creates the class, and sets all the variables to be a default value.
	SeeAlso:	EPSCommentDef::~EPSCommentDef

********************************************************************************************/

EPSCommentDef::EPSCommentDef ( void )
{
	// Pointers to next and previous items.
	mpNext			= NULL;

	// State variables.
	StartMarker.Empty ();
	EndMarker.Empty ();
	ProcessContents	= FALSE;
	Nesting			= 0;
}

/********************************************************************************************

>	EPSCommentDef::EPSCommentDef ( const EPSCommentDef &NewValue )


	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/00
	Inputs:		NewValue		- The values to be assigned.
	Returns:	-
	Purpose:	Copy constructor.
	SeeAlso:	EPSCommentList::EPSCommentDef

********************************************************************************************/

EPSCommentDef::EPSCommentDef ( const EPSCommentDef &NewValue )
{
	// Copy the data across.
	StartMarker		= NewValue.StartMarker;
	EndMarker		= NewValue.EndMarker;
	ProcessContents	= NewValue.ProcessContents;
	Nesting			= NewValue.Nesting;

	// Default value for the pointer.
	mpNext			= NULL;
}

/********************************************************************************************

>	EPSCommentDef::EPSCommentDef ( TCHAR	*pStart,
								   TCHAR	*pEnd,
								   BOOL		DoProcessComments,
								   UINT32		NestingDepth )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Inputs:		pStart				- Pointer to the comment starting a comment block.
				pEnd				- Pointer to the comment that ends this block.
				DoProcessComments	- Do the comments need processing?
				NestingDepth		- The depth to which comments can be nested.
	Returns:	-
	Purpose:	Creates the class, and sets all the variables to be a passed value.
	SeeAlso:	EPSCommentDef::~EPSCommentDef

********************************************************************************************/

EPSCommentDef::EPSCommentDef ( TCHAR	*pStart,
							   TCHAR	*pEnd,
							   BOOL		DoProcessContents,
							   UINT32		NestingDepth )
{
	// Set the variables according to the passed-in values.
	StartMarker		= pStart;
	EndMarker		= pEnd;
	ProcessContents	= DoProcessContents;
	Nesting			= NestingDepth;

	// Set the values of the pointers.
	mpNext			= NULL;
}

/********************************************************************************************

>	EPSCommentDef::~EPSCommentDef ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Inputs:		-
	Returns:	-
	Purpose:	Destroys the class and all member data.
	SeeAlso:	EPSCommentDef::~EPSCommentDef

********************************************************************************************/

EPSCommentDef::~EPSCommentDef ( void )
{
	// Recursively call down the list.
	if ( mpNext != NULL )
	{
		delete mpNext;
	}
}

/********************************************************************************************

>	void EPSCommentDef::Add ( EPSCommentDef *pNewItem )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Inputs:		pNewItem	- A pointer to the item to be added.
	Returns:	-
	Purpose:	Adds a new item onto the end of the list.
	SeeAlso:	EPSCommentList::Add

********************************************************************************************/

void EPSCommentDef::Add ( EPSCommentDef *pNewItem )
{
	// Recursively call down the list until mpNext is NULL.
	if ( mpNext != NULL )
	{
		mpNext->Add ( pNewItem );
	}
	else
	{
		mpNext = pNewItem;
	}
}

/********************************************************************************************

>	EPSCommentDef& EPSCommentDef::operator= ( const EPSCommentDef &NewValue )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/00
	Inputs:		NewValue		- The values to be assigned.
	Returns:	EPSCommentDef&	- The value being assigned (to allow for chaining).
	Purpose:	Sets the value of an EPSCommentDef to be equal to the passed in value.
	SeeAlso:	EPSCommentList::Add

********************************************************************************************/

EPSCommentDef& EPSCommentDef::operator= ( const EPSCommentDef &NewValue )
{
	StartMarker		= NewValue.StartMarker;
	EndMarker		= NewValue.EndMarker;
	ProcessContents	= NewValue.ProcessContents;
	Nesting			= NewValue.Nesting;

	// Ignore the pointers to avoid confusion with the linked list.

	// Return a reference to the new value to allow chaining of = operators.
	return *this;
}

/********************************************************************************************

>	EPSCommentDef* EPSCommentDef::GetNext ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Inputs:		-
	Returns:	mpNext	- A pointer to the next item in the list.
	Purpose:	Gets the pointer to the next item in the linked list.
	SeeAlso:	EPSCommentDef::Add

********************************************************************************************/

EPSCommentDef* EPSCommentDef::GetNext ( void )
{
	// Return a pointer to the next item in the list.
	return mpNext;
}
