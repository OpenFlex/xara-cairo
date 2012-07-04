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

#ifndef INC_EPS_COMMENT_LIST
#define INC_EPS_COMMENT_LIST

// Forward definition.
class EPSCommentDef;

/********************************************************************************************

>	class EPSCommentList : public CCObject

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/00
	Purpose:	Wraps up the EPSCommentDef structs into a list class. This will allow me to
				have a changeable list for different versions of the file, and as a result
				the whole importing of comments much less restrictive, but at the penalty of
				a speed hit. Looking up a token will be on O(n) operation, rather than the
				much quicker array look-up that currently exists.
	SeeAlso:	EPSFilter

********************************************************************************************/

class EPSCommentList : public CCObject
{
	CC_DECLARE_DYNAMIC( EPSCommentList );

public:
	// Constructor and destructor.
	EPSCommentList	( void );
	~EPSCommentList	( void );

	// Access functions.
	BOOL Add ( TCHAR	*pStart,
			   TCHAR	*pEnd,
			   BOOL		DoProcessComments,
			   UINT32		NestingDepth );

	const EPSCommentDef& ReturnElement ( INT32 Index );

private:
	// Member variables.
	EPSCommentDef	*mpCommentList;
	INT32				mListSize;
};

#endif
