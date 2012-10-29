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

DEFINE_BUFSIZE(32);

/**************************************************************************************
>	String_32::String_32(const TCHAR* psz = 0)

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12th August 1993
	Inputs:		An optional pointer to a (constant) Unicode character array - if
				omitted then the String becomes empty (NOT the null pointer).
	Purpose:	Constructs a string of the appropriate maximum length.
	Errors:		ASSERTion failure if the passed character array is too long for
				this length of string, or if psz is NULL.
	Scope:		Public
***************************************************************************************/

String_32::String_32(const TCHAR* psz)
{
	*(text = fixedbuf) = 0;
	length = FIX_LEN_BUFSIZE;
	if (psz != 0)
	{
		ERROR3IF(camStrlen(psz) >= length, "String_32::String_32 overflow");
		camStrcpy(text, psz);
	}
}



/**************************************************************************************
>	String_32::String_32(const StringBase& other)

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12th August 1993
	Inputs:		A constant reference to another string (can be of any length)
	Purpose:	Duplicates the text of the other string.
	Errors:		ASSERTion failure if this string is not long enough to hold a copy
				of the other string's text, or if the copied String has not been
				allocated.
	Scope:		Public
***************************************************************************************/

void String_32::CopyConstruct( const StringBase &other )
{
	*(text = fixedbuf) = 0;
	length = FIX_LEN_BUFSIZE;
	ERROR3IF((const TCHAR*) other == 0, "StringBase to be copied has not been ALLOCated");
	ERROR3IF(camStrlen((const TCHAR*) other) >= length,
				"Constructed String_32 not large enough to hold StringBase copy");
	camStrcpy(text, (const TCHAR*) other);
}




/**************************************************************************************
>	String_32::String_32(UINT32 resID, UINT32 hinst = 0)

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12th August 1993
	Inputs:		A string resource numeric identifier, an optional resource module
				handle (if not supplied, the default resource module is used).
	Purpose:	Loads the string resource into this String.
	Errors:		ENSURE failure if this string is not long enough to hold the
				resource, or if the resource cannot be found in the module. If it cannot
				be found, a very short temp string is built of the form "<%X:%X>" containing
				the ID and the module number, or if that is too long then simply "!".
	Scope:		Public
	SeeAlso:	SmartLoadString
***************************************************************************************/

String_32::String_32(UINT32 resID, UINT32 hinst)
{
	*(text = fixedbuf) = 0;
	length = FIX_LEN_BUFSIZE;
	if (!Load(resID, hinst))
	{	
		ERROR3("String resource failed to load");
		TCHAR buf[128];
		camSnprintf(buf, 128, TEXT("<%X:%X>"), (INT32) resID, (INT32) hinst);
		camStrcpy(text, (camStrlen(buf) <= 32) ? buf : TEXT("!"));
	}
}



/**************************************************************************************
>	String_32::String_32(const wxString& wxs)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28th January 2006
	Inputs:		A wxString
	Purpose:	Constructs a string of the appropriate maximum length.
	Errors:		ASSERTion failure if the passed character array is too long for
				this length of string, or if psz is NULL.
	Scope:		Public
***************************************************************************************/

String_32::String_32(const wxString& wxs)
{
	*(text = fixedbuf) = 0;
	length = FIX_LEN_BUFSIZE;
	ERROR3IF(wxs.Len() >= length, "String_32::String_32 overflow");
	camStrcpy(text, (LPCTSTR)wxs);
}



/**************************************************************************************
>	virtual BOOL String_32::Alloc(INT32 nSize)

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com> & Andy
	Created:	12th August 1993
	Purpose:	Fixes Alloc() for fixed-length strings, which CAN be safely changed#
				to use a buffer on the heap.
	Scope:		Public
	SeeAlso:	StringBase::Alloc
***************************************************************************************/

BOOL String_32::Alloc(INT32 nSize)
{
	if (text == fixedbuf) text = 0;
	return StringBase::Alloc(nSize);
}

