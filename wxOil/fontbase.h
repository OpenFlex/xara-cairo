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

// header file for FontBase class. All other Font classes inside Camelot should be
// derived from this - it acts as an interface layer to the kernel level font manager.
// Currently derived font classes are;
// TTFont	- The TrueType font manager class
// ATMFont	- The ATM font manager class

/*
*/

#ifndef INC_FONTBASE
#define INC_FONTBASE

#include "ccpanose.h"

class  DocCoord;
class CharMetrics;

#define OILFONTLIMIT 2048

// At the moment, text rendering has been implemented for wxGTK-based systems only.
// The higher text rendering levels in the Kernel depend on OILFontManager working,
// so they need to be disabled if we cannot provide the required services.
#ifndef __WXGTK__
#define DISABLE_TEXT_RENDERING 1
#endif

/********************************************************************************************

>	class FontBase : public CCObject
	   		
	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95
	Purpose:	A class which all Oil level fonts should be derived from. Its really
				an abstract class but contains some other functionaity too.

********************************************************************************************/

class FontBase : public CCObject
{
	CC_DECLARE_DYNCREATE(FontBase)
	
	public:
		FontBase();
		virtual BOOL Initialise(String_64 *pFontName);
		virtual BOOL Compare(String_64 *pFontName);

		virtual FontClass GetFontClass() { return FC_UNDEFINED; }
		virtual String_64* GetFontName() { return &TheFontName; }

		virtual void Delete();
		virtual void Dump();

	protected:
		String_64 TheFontName;
};

/********************************************************************************************

>	class OILFontMan : public CCObject
	   		
	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95
	Purpose:	The base font class controller inside the WinOil. The kernel should make
				calls to this font manager class only. The class acts as a switching layer
				calling other OIL level font managers dependent on the type of font in use.

********************************************************************************************/

class OILFontMan : public CCObject
{
	CC_DECLARE_DYNCREATE(OILFontMan)

	public:
		OILFontMan();

		// Functions each OIL font manager should take a role in.
		static BOOL IsOkToCall(FontClass Class);
		static BOOL CacheNamedFont(String_64* pFont, FontClass Class=FC_UNDEFINED, INT32 Pass=1);
		static void ValidateCache();
		static void FindClosestFont();
		static FontBase* CreateNewFont(FontClass Class, String_64* pFontName);
		static OUTLINETEXTMETRIC *GetOutlineTextMetric(FontClass Class, LOGFONT *pLogFont);
		static String_64* GetNativeFontName(FontClass Class, LOGFONT *pLogFont);
		static void InvalidateCharMetrics();
		static BOOL GetCharMetrics(wxDC* pDC, WCHAR ch, CharDescription& FontDesc, CharMetrics* pCharMetrics);
		static MILLIPOINT GetCharsKerning(wxDC* pDC, WCHAR chLeft, WCHAR chRight,
										  CharDescription& FontDesc);

	public:
		// Character cache related functions - other font manglers can use this
		// cache for their own purposes.
		static UINT32 GetOutlineCache(DocCoord** pCoords, PathVerb** pVerbs);
		static void InitialiseOutlineCache();
		static void FinaliseOutlineCache();
		static BOOL AddMoveTo(POINT& p0);
		static BOOL AddLineTo(POINT& p0);
		static BOOL AddBezierTo(POINT& p0, POINT& p1, POINT& p2);
		static BOOL AddMoveTo(DocCoord& p0);
		static BOOL AddLineTo(DocCoord& p0);
		static BOOL AddBezierTo(DocCoord& p0, DocCoord& p1, DocCoord& p2);
		static BOOL ClosePath();

		// character hi resolution metrics stuff.
		static BOOL GetCharPath(FontClass Class,
								CharDescription& ChDesc,
								DocCoord** ppCoords,
								PathVerb** ppVerbs,
								UINT32* pNumCoords,
								wxDC* pDC);

		// checks whether a class is actually known about
		static BOOL LegalFontClass(INT32 Class, FontClass& RealClass);

		// debugging stuff
		#if _DEBUG
		static void DumpEnumLogFont(ENUMLOGFONT* lpelf);
		static void DumpLogFont(LOGFONT* lplf);
		#endif
};


/********************************************************************************************

>	class EnumFonts : public CCObject
	   		
	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/9/95
	Purpose:	A class which allows kernel level and tool functions to inherit the ability
				to enum fonts. The class will call each OIL level font manager to enum their
				own specific set of fonts and the results will be returned to the derived
				NewFont() function. 

********************************************************************************************/

class OILEnumFonts : public CCObject
{
	CC_DECLARE_DYNCREATE( OILEnumFonts )

	public:
		OILEnumFonts();
		void Execute();
		virtual BOOL NewFont(FontClass Class, ENUMLOGFONT FAR* lpelf);
};


#endif
