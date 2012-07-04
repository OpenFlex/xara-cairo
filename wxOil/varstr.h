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


#ifndef INC_STRINGVAR
#define INC_STRINGVAR

#include "basestr.h"


/*************************************************************************************
	class StringVar : public StringBase
	
	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30th January 2006
	Purpose:	Extends its String base class to become self-sizing.
				This means that we need to override only functions in StringBase
				that try to create or extend the text allocation.

*************************************************************************************/

class CCAPI StringVar : public StringBase
{
public:
	static BOOL Init();

public:
	// Constructors
	StringVar(const TCHAR *psz = TEXT(""));
	StringVar(const StringBase &other);
	StringVar(UINT32 resID, UINT32 hinst = 0);
	StringVar(const wxString& wxs);

	// operator>>?
	// Insert?

	// Concatenation operators
	StringVar& operator+=(const StringBase& rhs);
	StringVar& operator+=(const TCHAR* s);
	StringVar& operator+=(const TCHAR ch);

	// Assignment operators
	StringVar& operator=(const StringBase& rhs);
	StringVar& operator=(const TCHAR* s);
	StringVar& operator=(const TCHAR ch);

#if !defined(EXCLUDE_FROM_XARLIB)
	// Special internationalisation stuff...
	virtual void MakePercent(INT32 Value);
	virtual void MakePercent(double Value);
	virtual void MakePercent(TCHAR *Value);
#endif

private:
	// Worker functions
	void SafeCat(const TCHAR* string);
	void SafeCopy(const TCHAR* string, UINT32 maxlen=0);
	void EnsureAlloc(UINT32 newlen);

};




#endif	// INC_STRINGVAR



////////////////////////////////////////////////////////////////////////////////////////
