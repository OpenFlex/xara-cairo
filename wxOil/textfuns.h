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

// Header for the TextFuns implementation

#ifndef INC_TEXTFUNS
#define INC_TEXTFUNS

#include "fntcache.h"
//#include "textinfo.h"
class CharDescription;
class DocCoord;


// enums ...
enum CharCase { Failed=0, Lower, Upper, Swap, Read, UnknownType };

// constants
const WCHAR FONTEMCHAR = 'M';	// for finding the width of an 'em' etc

/********************************************************************************************
>	class CharMetrics : public CC_CLASS_MEMDUMP

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/3/95
	Purpose:	parameter passing of char metrics
********************************************************************************************/

class CharMetrics : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(CharMetrics);

public:
	CharMetrics();
	void Scale(double ScaleX, double ScaleY);

public:
	MILLIPOINT CharWidth;
	MILLIPOINT FontAscent;
	MILLIPOINT FontDescent;
	MILLIPOINT FontEmWidth;
};

/********************************************************************************************
>	struct MillipointKerningPair

	Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/10/2000
	Purpose:	Same as windows structure KERNINGPAIR but using millipoints
********************************************************************************************/
struct MillipointKerningPair
{
	WORD		wFirst; 
	WORD		wSecond; 
	MILLIPOINT  iKernAmount; 
};

/********************************************************************************************
>	struct FontInfo

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/5/95
	Purpose:	parameter passing of info extracted from a LogFont
********************************************************************************************/

struct FontInfo
{
	WORD       Handle;
	MILLIPOINT Size;
	FIXED16    Aspect;
	BOOL       Bold;
	BOOL       Italic;
	ANGLE      Rotation;
};


/********************************************************************************************
>	class TextManager:	public CCObject

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/1/95
	Purpose:	You name it and its assocaited with text then this probably isn't it
********************************************************************************************/

class TextManager: public CCObject
{
	//CC_DECLARE_DYNAMIC(TextManager)// not required as this is a static class

public:
	static BOOL GetLogFontFromCharDescriptor(wxDC* pDC, CharDescription& ChDesc, LPLOGFONT pLogFont,
												INT32 LogicalHeight=-1);

	static BOOL GetTTCharPath(CharDescription& ChDesc, DocCoord** ppCoords, PathVerb** ppVerbs,
																		UINT32* pNumCoords, wxDC* pDC );

  	static BOOL GetBezierFromChar(wxDC* pDC, WCHAR CharNumber, LPLOGFONT pLogFont,
  								  DWORD* NoElements, POINT* pPolyCordBuffer, BYTE* pPolyVerbBuffer);
  
	static CharCase ProcessCharCase(WCHAR* pChar, CharCase NewState);

	static MILLIPOINT GetDefaultHeight() { return 72000; }	// size of char-paths/advance-widths in caches etc

	static BOOL GetInfoFromLogFont(FontInfo* pFontInfo, LOGFONT* pLogFont, FontClass Class=FC_UNDEFINED);

	static INT32 GetDesignSize(wxDC* pDC);

	static BOOL GetCharWidth(    wxDC* pDC, WCHAR FirstChar, WCHAR LastChar, INT32* pCharWidthsBuf);
	static BOOL GetCharABCWidths(wxDC* pDC, WCHAR FirstChar, WCHAR LastChar, ABC* pCharABCWidthsBuf);

	static INT32	GetKernCount(wxDC* pDC);
	static bool FillKernArray(wxDC* pDC, MillipointKerningPair* pKerningPairs, INT32 count);
};

#endif
