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

CC_IMPLEMENT_DYNAMIC ( EPSCommentList, CCObject )

/********************************************************************************************

>	EPSCommentList::EPSCommentList ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Inputs:		-
	Returns:	-
	Purpose:	Creates the class, and sets all the variables to be a default value.
	SeeAlso:	EPSCommentList::~EPSCommentList

********************************************************************************************/

EPSCommentList::EPSCommentList ( void )
{
	// Set the comment list pointer to be NULL, so as to avoid any problems with adding
	// items to it.
	mpCommentList	= NULL;
	mListSize		= 0;
}

/********************************************************************************************

>	EPSCommentList::~EPSCommentList ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Inputs:		-
	Returns:	-
	Purpose:	Destroys the class, and all of its member variables.
	SeeAlso:	EPSCommentList::EPSCommentList

********************************************************************************************/

EPSCommentList::~EPSCommentList ( void )
{
	// Delete the list. This invokes a recursive call to remove all successive items.
	delete mpCommentList;
}

/********************************************************************************************

>	BOOL EPSCommentList::Add ( TCHAR	*pStart,
							   TCHAR	*pEnd,
							   BOOL		DoProcessComments,
							   UINT32		NestingDepth )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Inputs:		pStart				- Pointer to the comment starting a comment block.
				pEnd				- Pointer to the comment that ends this block.
				DoProcessComments	- Do the comments need processing?
				NestingDepth		- The depth to which comments can be nested.
	Returns:	TRUE				- Success.
				FALSE				- The object was not created.
	Purpose:	Adds a list item to the end of mpCommentList record.
	SeeAlso:	EPSCommentDef::EPSCommentDef

********************************************************************************************/

BOOL EPSCommentList::Add ( TCHAR	*pStart,
						   TCHAR	*pEnd,
						   BOOL		DoProcessComments,
						   UINT32		NestingDepth )
{
	// Create a new EPSCommentDef, and assign the appropriate values.
	EPSCommentDef	*pNewDef	= new EPSCommentDef ( pStart, pEnd, DoProcessComments,
													  NestingDepth );

	// Determine whether something was created.
	if ( pNewDef != NULL )
	{
		// Add it to the end of the list.
		if ( mpCommentList == NULL )
		{
			// The pointer is NULL, so just assign the value.
			mpCommentList = pNewDef;
		}
		else
		{
			// There already is a list, so add this to it.
			mpCommentList->Add ( pNewDef );
		}

		// Maintain a count of the number of elements in the list.
		mListSize ++;

		return TRUE;
	}
	else
	{
		// Not enough memory.
		return FALSE;
	}
}

/********************************************************************************************

>	const EPSCommentDef& EPSCommentList::ReturnElement ( INT32 Index );

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/00
	Inputs:		Index	- The number of the element to be accessed.
	Returns:	&pItem	- A reference to an item in the list.
	Purpose:	Returns a reference to the nth item in the linked list, where n = Index.

********************************************************************************************/

const EPSCommentDef& EPSCommentList::ReturnElement ( INT32 Index )
{
	// Set up the local variables.
	EPSCommentDef	*pItem	= mpCommentList;
	EPSCommentDef	*pNext	= NULL;
	INT32				Count	= 0;

	// Ensure that the comment list has been initialised.
	ERROR1IF ( pItem == NULL, EmptyDefinition,
			   "The comment list hasn't been initialised!" );

	// Catch out-of-bounds calls.
	if ( Index >= mListSize )
		return EmptyDefinition;

	// Loop through the list until there are no more items, or we reach the right index.
	while ( pNext = pItem->GetNext (), Count < Index && pNext != NULL )
	{
		pItem = pNext;
		Count ++;
	}

	// Return the appropriate list item.
	return *pItem;
}
