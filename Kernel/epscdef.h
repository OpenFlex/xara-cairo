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

#ifndef INC_EPS_COMMENT_DEF
#define INC_EPS_COMMENT_DEF

/********************************************************************************************

>	class EPSCommentDef

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com> (from Tim's code)
	Created:	27/4/00
	Purpose:	Describes an EPS/DSC comment, and describes how to handle it.
				There are four fields:

				StartMarker - a string which is the start of the comment block, 
							  e.g. "%%BeginSetup"

				EndMarker   - a string which is the end of the comment block,
							  e.g. "%%EndSetup"

				ProcessContents - a boolean; if TRUE, all comments found within the
								  comment block should be passed around to the document
								  components for processing as usual.
								  If FALSE, then all lines in the comment block should
								  be completely ignored.

				Nesting		- the current nesting level of this comment - this is set up
							  to be 0 before loading a new file, and means we can cope
							  with, e.g. nested documents correctly.

********************************************************************************************/

class EPSCommentDef
{
public:
	// Constructor and destructor.
	EPSCommentDef ( void );
	EPSCommentDef ( const EPSCommentDef &NewValue );
	EPSCommentDef ( TCHAR	*pStart,
					TCHAR	*pEnd,
					BOOL	DoProcessContents,
					UINT32	NestingDepth );
	~EPSCommentDef ( void );

	// Access functions.
	void Add ( EPSCommentDef *pNewItem );
	EPSCommentDef& operator= ( const EPSCommentDef &NewValue );
	EPSCommentDef* GetNext ( void );

	// Member variables.
	String_64		StartMarker;
	String_64		EndMarker;
	BOOL			ProcessContents;
	UINT32			Nesting;

private:
	// Pointer to the next instance in the linked list.
	EPSCommentDef	*mpNext;
};

// An empty definition to pass back when problems occur.
const EPSCommentDef EmptyDefinition ( _T(""), _T(""), FALSE, 0 );

#endif
