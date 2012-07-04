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

//

#ifndef INC_UNICODEMANAGER
#define INC_UNICODEMANAGER

#if !defined(__WXMSW__)
#define	ANSI_CHARSET		0
#define SHIFTJIS_CHARSET	1
#endif


/**************************************************************************************
>	class UnicodeManager : public CCObject

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/7/96
	Purpose:	Class for containing all Unicode related methods
**************************************************************************************/
class UnicodeManager : public CCObject
{
public:

	// Conversion to/from ASCII or DBCS and Unicode
	static inline UINT32 ComposeMultiBytes(BYTE LeadChar, BYTE TrailChar)			{return (LeadChar<<8) + TrailChar;}
	static void DecomposeMultiBytes(UINT32 MBChar, BYTE* LeadChar, BYTE* TrailChar);
PORTNOTE("other","IsDBCSLeadByte always return false on platform != Windows")
#if defined( __WXMSW__ )
	static inline BOOL IsDBCSLeadByte(BYTE TestChar)							{ return ::IsDBCSLeadByte(TestChar); }
#else
	static inline BOOL IsDBCSLeadByte(BYTE TestChar)							{ return false; }
#endif
	static UINT32 UnicodeToMultiByte(WCHAR UnicodeChar);
	static WCHAR MultiByteToUnicode(UINT32 MBChar);
	
	// For determining operating system support
	static BOOL IsUnicodeCompleteOS();
	static BOOL IsDBCSOS();
	static UINT32 GetFontCharSet();
};


#endif	// INC_UNICODEMANAGER
