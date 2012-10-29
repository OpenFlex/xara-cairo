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

// implementation file for TrueType Font manager winoil inclusion

/*
*/

#include "camtypes.h"
#include "ttfonts.h"
#include "fontman.h"
#include "textfuns.h"
#include "oilpanse.h"

DECLARE_SOURCE( "$Revision: 1282 $" );

CC_IMPLEMENT_DYNCREATE( TTFontMan, CCObject )
CC_IMPLEMENT_DYNCREATE( TTFont, FontBase )

#define new CAM_DEBUG_NEW     

/********************************************************************************************

>	TTFont::TTFont()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/09/95				
	Purpose:	Default constructor

********************************************************************************************/

TTFont::TTFont()
{
}

/********************************************************************************************

>	TTFont::~TTFont()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/09/95				
	Purpose:	destructor for the TTFont class

********************************************************************************************/

TTFont::~TTFont()
{
}

/********************************************************************************************

>	void TTFont::Dump()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/09/95
	Purpose:	Dump the contents of this cache entry out

********************************************************************************************/

void TTFont::Dump()
{
	FontBase::Dump();
	TRACE( _T(" FontClass = TrueType\n"));
}

/********************************************************************************************

>	TTFontMan::TTFontMan() 

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/09/95				
	Purpose:	Default constructor

********************************************************************************************/

TTFontMan::TTFontMan()
{
}

/********************************************************************************************

	static BOOL TTFontMan::IsOkToCall()

	Author: 	Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/9/95
	Returns:	TRUE if the TrueType mangler is actually running and can be used on this OpSys
	Purpose:	Determine whether we can make further calls to the TrueType Manager

********************************************************************************************/

BOOL TTFontMan::IsOkToCall()
{
	// Currently its always true as this is the winoil
	return TRUE;
}

/********************************************************************************************

>	static BOOL TTFontMan::CacheNamedFont(String_64* pFontName)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/9/95
	Inputs:		pFontName = a pointer to a fontname to find and cache
	Outputs:	-
	Returns:	TRUE if the font has been cached
				FALSE if not.
	Purpose:	This function attempts to cache a font of the true type variety. It caches
				the font in the kernels font list, and hence can be accessed via 
				FONTMANAGER-> calls

********************************************************************************************/

BOOL TTFontMan::CacheNamedFont(String_64* pFontName)
{
	CDC Screen;
	if (Screen.CreateIC(TEXT("DISPLAY"), 0, 0, 0))
	{
		Application* pApp = GetApplication();
		FontManager* pFontMan = pApp->GetFontManager();
		ERROR2IF(pFontMan == NULL,FALSE,"NULL FontManager ptr");
		pFontMan->ClearTempFont();
		EnumFontFamilies(Screen.m_hDC,
						 NULL,
						 (FONTENUMPROC) TTFontMan_CallBackCacheNamedFont,
						 (LPARAM)pFontName);
		Screen.DeleteDC();
		return pFontMan->TempFontValid();
	}
	return FALSE;
}

/********************************************************************************************

>	static BOOL TTFontMan::CacheCompatibleFont(String_64* pFontName)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/9/95
	Inputs:		pFontName = a pointer to a fontname to find and cache
	Outputs:	-
	Returns:	-
	Purpose:	This function attempts to cache a font of the ATM variety

********************************************************************************************/

BOOL TTFontMan::CacheCompatibleFont(String_64* pFontName)
{
	return FALSE;
}

/********************************************************************************************

>	static void TTFontMan::ValidateCache()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/9/95
	Purpose:	This function will attempt to recache all true type fonts within the kernels
				font manager cache.

********************************************************************************************/

void TTFontMan::ValidateCache()
{
	CDC Screen;
	if (Screen.CreateIC(TEXT("DISPLAY"), 0, 0, 0))
	{
		EnumFontFamilies(Screen.m_hDC,
						 NULL,
						 (FONTENUMPROC) TTFontMan_CallBackValidateFont,
						 NULL);
		Screen.DeleteDC();
	}
}

/********************************************************************************************

>	static void TTFontMan::FindClosestFont()

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/08/96
	Purpose:	Enumerates all the fonts, looking for a match to a panose number

********************************************************************************************/

void TTFontMan::FindClosestFont()
{
	CDC Screen;
	if (Screen.CreateIC(TEXT("DISPLAY"), 0, 0, 0))
	{
		EnumFontFamilies(Screen.m_hDC,
						 NULL,
						 (FONTENUMPROC) TTFontMan_CallBackFindClosestFont,
						 NULL);
		Screen.DeleteDC();
	}
}

/********************************************************************************************

>	TTFont* TTFontMan::CreateNewFont(String_64* pFontName)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/9/95
	Inputs:		pFontName = a pointer to a fontname
	Returns:	NULL if no true type font structure has been created
				A pointer to a true type font structure if successfull.
	Purpose:	This function attempts to create a font instance and will be called by
				the font manager when new fonts are added.

********************************************************************************************/

TTFont* TTFontMan::CreateNewFont(String_64* pFontName)
{
	TTFont *pFont = new TTFont;
	if (pFont==NULL)
		return NULL;
	if (!pFont->Initialise(pFontName))
	{
		delete pFont;
		return NULL;
	}
	return pFont;
}

/********************************************************************************************

>	OUTLINETEXTMETRIC *TTFontMan::GetOutlineTextMetric(LOGFONT *pLogFont)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/08/96
	Inputs:		pLogFont	- pointer to the LOGFONT describing the font in question
	Returns:	pointer to an OUTLINETEXTMETRIC structure, or NULL if none exists.
	Purpose:	Retrieves the OUTLINETEXTMETRIC structure for a TrueType font

	The caller is responsible for deleting this after use.

********************************************************************************************/

OUTLINETEXTMETRIC *TTFontMan::GetOutlineTextMetric(LOGFONT *pLogFont)
{
	ERROR2IF(pLogFont==NULL, FALSE, "Parameter pLogFont==NULL.");

	// watch closely now - it gets fairly involved down here

	OUTLINETEXTMETRIC *pOutlineTextMetric = NULL;
	INT32 Value;

	CDC DisplayDC;
	if (DisplayDC.CreateIC(TEXT("DISPLAY"), 0, 0, 0))
	{
		CFont *pNewCFont = new CFont;

		if (pNewCFont->CreateFontIndirect(pLogFont) != NULL)
		{
			//		**	**													**   **
			//		 ** **		must remember to select the old CFont		 ** **
			//		  ***		back in again when we've					  ***
			//		 ** **		finished using this new CFont!				 ** **
			//		**   **													**   **
			
			CFont *pOldCFont = DisplayDC.SelectObject(pNewCFont);
			
			if (pOldCFont != NULL)
			{
				TEXTMETRIC MyTextMetric;

				if (DisplayDC.GetTextMetrics(&MyTextMetric) != 0)
				{
					if (MyTextMetric.tmPitchAndFamily & TMPF_TRUETYPE == TMPF_TRUETYPE)
					{
						// its a TrueType font, so get the OUTLINETEXTMETRIC structure and run

						Value = DisplayDC.GetOutlineTextMetrics(NULL, NULL);

						// claim a block of memory for the OUTLINETEXTMETRIC class
						pOutlineTextMetric = (OUTLINETEXTMETRIC *) malloc(Value);

						// now get the OUTLINETEXTMETRIC structure itself
						Value = DisplayDC.GetOutlineTextMetrics(Value, pOutlineTextMetric);

						if (Value==FALSE)
						{
							// failed to get the outline text metrics, so free the memory we claimed
							free(pOutlineTextMetric);
							pOutlineTextMetric=NULL;
						}
					}
					else
					{
						// not a truetype font, so do nothing.
					}
				}
				else
				{
					DisplayDC.SelectObject(pOldCFont);
					DisplayDC.DeleteDC();
					delete pNewCFont;
					ERROR2(NULL, "Unable to retrieve TEXTMETRIC structure from DisplayDC.")
				}

				//		**	**													**   **
				//		 ** **		select the old CFont back into the			 ** **
				//		  ***		DC now we've finished using the 			  ***
				//		 ** **		new CFont!									 ** **
				//		**   **													**   **

				DisplayDC.SelectObject(pOldCFont);
			}
			else
			{
				delete pNewCFont;
				DisplayDC.DeleteDC();
				ERROR2(NULL, "Unable to select font into IC.");
			}
		}
		else
		{
			delete pNewCFont;
			DisplayDC.DeleteDC();
			ERROR2(NULL, "Unable to create font.");
		}
		delete pNewCFont;
		DisplayDC.DeleteDC();
	}
	else
	{
		ERROR2(NULL, "Unable to create an IC.");
	}

	return pOutlineTextMetric;
}

/********************************************************************************************

>	static void TTFontMan::EnumAllFonts(OILEnumFonts* pClass)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/9/95
	Inputs:		pClass = A pointer to an object to call back.
	Purpose:	Gives the kernel a way of enumerating fonts itself

********************************************************************************************/

void TTFontMan::EnumAllFonts(OILEnumFonts* pClass)
{
	CDC Screen;
	if (Screen.CreateIC(TEXT("DISPLAY"), 0, 0, 0))
	{
		EnumFontFamilies(Screen.m_hDC,
						 NULL,
						 (FONTENUMPROC) TTFontMan_CallBackDispatchFont,
						 (LPARAM)pClass);
		Screen.DeleteDC();
	}
}

/********************************************************************************************

>	INT32 APIENTRY TTFontMan_CallBackCacheNamedFont(
	ENUMLOGFONT FAR*  lpelf,		// address of logical-font data 
    NEWTEXTMETRIC FAR*  lpntm,		// address of physical-font data 
    INT32 FontType,					// type of font 
    LPARAM lParam 					// address of application-defined data  

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/9/95
	Purpose:	The call back function providing all font data

********************************************************************************************/

INT32 APIENTRY TTFontMan_CallBackCacheNamedFont(
	ENUMLOGFONT FAR*  lpelf,		// address of logical-font data 
    NEWTEXTMETRIC FAR*  lpntm,		// address of physical-font data 
    INT32 FontType,					// type of font 
    LPARAM lParam 					// address of application-defined data  
	)
{
	if (FontType & TRUETYPE_FONTTYPE)
	{
		// find the font name
		String_64 FontName(lpelf->elfLogFont.lfFaceName);

		if (lParam==NULL || (_tcsncicmp(FontName, *((String_64 * )lParam), 64) == 0))
		{
			FontManager* pFontMan = GetApplication()->GetFontManager();
			pFontMan->SetTempFont(FC_TRUETYPE, &FontName, lpelf);
			return FALSE;
		}
	}
    return TRUE;
}

/********************************************************************************************

>	INT32 APIENTRY TTFontMan_CallBackValidateFont(
	ENUMLOGFONT FAR*  lpelf,		// address of logical-font data 
    NEWTEXTMETRIC FAR*  lpntm,		// address of physical-font data 
    INT32 FontType,					// type of font 
    LPARAM lParam 					// address of application-defined data  

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/9/95
	Purpose:	The call back function providing all font data

********************************************************************************************/

INT32 APIENTRY TTFontMan_CallBackValidateFont(
	ENUMLOGFONT FAR*  lpelf,		// address of logical-font data 
    NEWTEXTMETRIC FAR*  lpntm,		// address of physical-font data 
    INT32 FontType,					// type of font 
    LPARAM lParam 					// address of application-defined data  
	)
{
    UNREFERENCED_PARAMETER (lpntm);

	if (FontType & TRUETYPE_FONTTYPE)
	{
		// find the font name
		String_64 FontName(lpelf->elfLogFont.lfFaceName);

		FontManager* pFontMan = GetApplication()->GetFontManager();
		pFontMan->ValidateItem(FC_TRUETYPE, &FontName, lpelf);
	}
    return TRUE;
}

/********************************************************************************************

	INT32 APIENTRY TTFontMan_CallBackDispatchFont(
	ENUMLOGFONT FAR*  lpelf,		// address of logical-font data 
    NEWTEXTMETRIC FAR*  lpntm,		// address of physical-font data 
    INT32 FontType,					// type of font 
    LPARAM lParam 					// address of application-defined data  

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/9/95
	Purpose:	The call back function providing all font data

********************************************************************************************/

INT32 APIENTRY TTFontMan_CallBackDispatchFont(
	ENUMLOGFONT FAR*  lpelf,		// address of logical-font data 
    NEWTEXTMETRIC FAR*  lpntm,		// address of physical-font data 
    INT32 FontType,					// type of font 
    LPARAM lParam 					// address of application-defined data  
	)
{
    UNREFERENCED_PARAMETER (lpntm);

	if ((FontType & TRUETYPE_FONTTYPE) && lpelf->elfLogFont.lfFaceName[0] != TEXT('@'))
	{
		return ((OILEnumFonts*) lParam)->NewFont(FC_TRUETYPE, lpelf);
	}

	return TRUE;
}

/********************************************************************************************

	INT32 APIENTRY TTFontMan_CallBackFindClosestFont(
	ENUMLOGFONT FAR*  lpelf,		// address of logical-font data 
    NEWTEXTMETRIC FAR*  lpntm,		// address of physical-font data 
    INT32 FontType,					// type of font 
    LPARAM lParam 					// address of application-defined data  

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/08/96
	Purpose:	The call back function for finding the closest font

********************************************************************************************/

INT32 APIENTRY TTFontMan_CallBackFindClosestFont(
	ENUMLOGFONT FAR*  lpelf,		// address of logical-font data 
    NEWTEXTMETRIC FAR*  lpntm,		// address of physical-font data 
    INT32 FontType,					// type of font 
    LPARAM lParam 					// address of application-defined data  
	)
{
    UNREFERENCED_PARAMETER (lpntm);

	if (FontType & TRUETYPE_FONTTYPE)
	{
		// find the font name
		String_64 FontName(lpelf->elfLogFont.lfFaceName);

		FontManager* pFontMan = GetApplication()->GetFontManager();
		return pFontMan->FindClosestFontFullTry(FC_TRUETYPE, &FontName, lpelf);
	}
	
    return TRUE;
}
