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


// Platform dependent parts of the debug tree display


#include "camtypes.h"

#include "oildbug.h"


/********************************************************************************************

>	void DebugTreeInfo::AddDebugInfo(INT32 Index, void *Ref)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/94
	Inputs:		Index - the index of the item to associate the datum with.
				Ref - the datum to associate with the list item.
	Purpose:	Associate a piece of data with a given item in the listbox of the tree
				dialog.
	SeeAlso:	DebugTreeInfo::GetDebugInfo

********************************************************************************************/

void DebugTreeInfo::AddDebugInfo(INT32 Index, void *Ref)
{
	PORTNOTETRACE("other","DebugTreeInfo::AddDebugInfo - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	// Take the easy way out under Windows - let the list box do all the hard work.
	::SendMessage( (HWND)WindowID, LB_SETITEMDATA, (WPARAM) Index, (LPARAM) Ref );
#endif
}

/********************************************************************************************

>	void *DebugTreeInfo::GetDebugInfo(INT32 Index)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/94
	Inputs:		Index - the index of the listbox item to examine.
	Returns:	The datum for the specified listbox item.
	Purpose:	Retrieve the piece of data associated with a list item (from the list box
				of the tree dialog).
	SeeAlso:	DebugTreeInfo::AddDebugInfo

********************************************************************************************/

void *DebugTreeInfo::GetDebugInfo(INT32 Index)
{
	PORTNOTETRACE("other","DebugTreeInfo::GetDebugInfo - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	// Take the easy way out under Windows - let the list box do all the hard work.
	INT32				nVal = INT32(::SendMessage((HWND) WindowID, LB_GETITEMDATA, (WPARAM) Index, 0));
	if( -1 == nVal )
		return NULL;
	return (void *)nVal
#else
	return NULL;
#endif
}

/********************************************************************************************

>	void DebugTreeInfo::OutputDebugLine(TCHAR *Str)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/94
	Inputs:		Str - the string to dump
	Purpose:	Output a string to whatever debug console type device this OS supports.

********************************************************************************************/

void DebugTreeInfo::OutputDebugLine(TCHAR *Str)
{
#if defined(__WXMSW__)
	OutputDebugString( Str );
#else
	#pragma error( "Not impl'ed from this architechure" );
#endif
}


/********************************************************************************************

>	static void DebugTreeInfo::OutputDebug(TCHAR *Str)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/94
	Inputs:		Str - the string to dump
	Purpose:	Output a string to whatever debug console type device this OS supports.
				(This version is static so anyone can use it. It's implemented as a separate
				 function so that I can guarantee not to upset OutputDebugLine above...)

********************************************************************************************/

void DebugTreeInfo::OutputDebug(TCHAR *Str)
{
#if defined(__WXMSW__)
	OutputDebugString( Str );
#elif defined(__WXGTK__)
	camPrintf( Str );
#else
	#pragma error( "Not impl'ed from this architechure" );
#endif
}


