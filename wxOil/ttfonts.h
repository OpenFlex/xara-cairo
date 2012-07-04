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

// header file for TrueType Font manager winoil inclusion

/*
*/

#ifndef INC_TTFONTS
#define INC_TTFONTS

//#include "ccpanose.h"
#include "fontbase.h"

// Forward definitions
class OILEnumFonts;

/********************************************************************************************
>	class TTFont : public FontBase
	   		
	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95
	Purpose:	A class description of a true type font.
********************************************************************************************/

class TTFont : public FontBase
{
	CC_DECLARE_DYNCREATE(TTFont)

public:
	 TTFont();
	~TTFont();

	virtual FontClass GetFontClass() { return FC_TRUETYPE; };
	virtual void Dump();
};


/********************************************************************************************

>	class TTFontMan : public CCObject
	   		
	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95
	Purpose:	A static class to allow acces to TrueType fonts.

********************************************************************************************/

class TTFontMan : public CCObject
{
	CC_DECLARE_DYNCREATE(TTFontMan)

	friend class OILFontMan;

// constructor
public:
	TTFontMan();

// the support interface (functions in class OILFontMan will use these)
private:
	static BOOL		IsOkToCall();
	static BOOL		CacheNamedFont(String_64* pFont);
	static BOOL		CacheCompatibleFont(String_64* pFont);
	static void		ValidateCache();
	static void		FindClosestFont();
	static TTFont*	CreateNewFont(String_64* pFontName);
	static OUTLINETEXTMETRIC* GetOutlineTextMetric(LOGFONT *pLogFont);

// function called by class EnumFonts as a method for the kernel to enumerate all the installed fonts
public:
	static void		EnumAllFonts(OILEnumFonts* pClass);
};

// functions called as callbacks from some of the previous functions. The names break one
// of the style rules, but this is to re-enforce the fact that while these functions are
// global they should be treated as members of the TTFontMan class.
// They can't be member functions, since they are used as callback functions. The last
// function isn't used as a callback, but is called from the other threee. This way seems
// neatest.

INT32 APIENTRY	TTFontMan_CallBackCacheNamedFont(ENUMLOGFONT FAR* lpelf,
												 NEWTEXTMETRIC FAR* lpntm,
												 INT32 FontType,
												 LPARAM lParam);
INT32 APIENTRY	TTFontMan_CallBackValidateFont(ENUMLOGFONT FAR* lpelf,
											   NEWTEXTMETRIC FAR* lpntm,
											   INT32 FontType,
											   LPARAM lParam);
INT32 APIENTRY	TTFontMan_CallBackDispatchFont(ENUMLOGFONT FAR* lpelf,
											   NEWTEXTMETRIC FAR* lpntm,
											   INT32 FontType,
											   LPARAM lParam);
INT32 APIENTRY	TTFontMan_CallBackFindClosestFont(ENUMLOGFONT FAR* lpelf,
												  NEWTEXTMETRIC FAR* lpntm,
											      INT32 FontType,
											      LPARAM lParam);

#endif
