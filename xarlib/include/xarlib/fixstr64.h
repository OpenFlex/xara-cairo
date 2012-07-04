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



#ifndef INC__FIXSTRING64
#define INC__FIXSTRING64

#include "xarlib/basestr.h"


/*************************************************************************************
	class String_64 : public StringBase
	
	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12th August 1993	
	Purpose:	Extends its String base class to become fixed-length and atomically
				allocatable, ie. a failed constructor call for this class will never
				leave the object in an illegal state.
*************************************************************************************/

class CCAPI String_64 : public StringBase
{
	static const INT32 FIX_LEN_BUFSIZE;

private:
	void CopyConstruct( const StringBase &other );
	
public:
	String_64(const TCHAR* psz = TEXT(""));
	String_64( const StringBase &other )	{ CopyConstruct( other ); }
	String_64( const String_64 &other )		{ CopyConstruct( other ); }
	String_64(UINT32 resID, UINT32 hinst = 0);
	String_64(const wxString& wxs);
	virtual ~String_64();

	virtual BOOL Alloc(INT32 nSize);

private:
	TCHAR fixedbuf[FIX_LEN_BUFM(64)];
};




/**************************************************************************************
>	virtual String_64::~String_64()

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12th August 1993
	Purpose:	Destroys this fixed-length string.
***************************************************************************************/

inline String_64::~String_64()
{
	// If the string is using the fixed-length buffer then make sure the
	// base class doesn't try to delete[] it.
	if (text == fixedbuf) text = 0;
}

#endif	// INC__FIXSTRING64



////////////////////////////////////////////////////////////////////////////////////////
