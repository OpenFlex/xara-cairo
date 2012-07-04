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

/********************************************************************************************

>	oilpanse.cpp

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/07/96
	Purpose:	Implementation of the OIL related Panose code
	SeeAlso:	kernel\ccpanose.h, kernel\ccpanose.cpp

********************************************************************************************/

#include "camtypes.h"

#include "ccpanose.h"
#include "oilpanse.h"

/********************************************************************************************

>	HDC OILPanose::MyDC
	BOOL OILPanose::IsInitialised

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	24/07/96
	Purpose:	Static member variables of the OILPanose class

********************************************************************************************/

CDC *OILPanose::pMyCDC = NULL;
BOOL OILPanose::IsInitialised = FALSE;

/********************************************************************************************

>	BOOL OILPanose::Init(CDC *pCDC)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/07/96
	Inputs:		pCDC	- pointer to a CDC to use
	Returns:	TRUE if successful, FALSE otherwise
	Purpose:	Initialises the static member varibles of this class.
	See Also:	OILPanose::DeInit();

	Since DC's are in _very_ short supply, you must only call Init when needed, and call
	DeInit as soon as possible afterwards. There's no problem under NT, but both Win95 and
	Win3.11 have a limited supply of DCs.

********************************************************************************************/

BOOL OILPanose::Init(CDC *ptr)
{
	ERROR2IF(ptr==NULL, FALSE, "Parameter ptr == NULL");
	ERROR2IF(IsInitialised==TRUE, FALSE, "OILPanose::Init called when IsInitialised==TRUE.");

	pMyCDC = ptr;
	IsInitialised=TRUE;

	return TRUE;
}

/********************************************************************************************

>	BOOL OILPanose::DeInit()

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/07/96
	Inputs:		-
	Returns:	TRUE if sucessful, FALSE otherwise
	Purpose:	Deinitialises this, the OILPanose class.
	See Also:	void OILPanose::Init()

********************************************************************************************/

BOOL OILPanose::DeInit()
{
	ERROR2IF(IsInitialised==FALSE, FALSE, "OILPanose::DeInit called when IsInitialised==FALSE");

	pMyCDC = NULL;
	IsInitialised = FALSE;

	return TRUE;
}

/********************************************************************************************

>	BOOL OILPanose::GetPanoseNumber(ENUMLOGFONT *pEnumLogFont, CCPanose *pPanose)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/07/96
	Inputs:		pEnumLogFont	- pointer to an ENUMLOGFONT structure
				pPanose			- pointer to an CCPanose structure
	Outputs:	Enters values into the CCPanose structure pointed to by pPanose.
	Purpose:	Platform depenedent method of getting the Panose number for a font

********************************************************************************************/

BOOL OILPanose::GetPanoseNumber(ENUMLOGFONT *pEnumLogFont, CCPanose *pPanose)
{
	ERROR2IF(pEnumLogFont==NULL, FALSE, "Parameter pEnumLogFont == NULL.");
	ERROR2IF(pPanose==NULL, FALSE, "Parameter pPanose == NULL.");
	ERROR2IF(IsInitialised==FALSE, FALSE, "Class OILPanose not initialised.");

	BOOL ok = FALSE;

	// watch closely - it gets fairly involved down here

	CFont *pNewCFont;

	pNewCFont = new CFont;

	if (pNewCFont->CreateFontIndirect(&(pEnumLogFont->elfLogFont)) != NULL)
	{
		// success, managed to get create a new font. now select it into the CDC we have
		CFont *pOldCFont;
		pOldCFont = pMyCDC->SelectObject(pNewCFont);

		if (pOldCFont!=NULL)
		{
			// success, managed to select the font into the DC

			TEXTMETRIC MyTextMetric;

			if (pMyCDC->GetTextMetrics(&MyTextMetric) != 0)
			{
				// great, we've got the TextMetric structure. now check to see if its
				// a TrueType font or not - only TrueType fonts have Panose information
				if ((MyTextMetric.tmPitchAndFamily & TMPF_TRUETYPE) == TMPF_TRUETYPE)
				{
					// its a TrueType font, so get the Panose number and run
					INT32 Value;
					OUTLINETEXTMETRIC *pOutlineTextMetric;

					// find out how much space we need for the information
					Value = pMyCDC->GetOutlineTextMetrics(NULL, NULL);

					// claim a block of memory at least this size
					pOutlineTextMetric = (OUTLINETEXTMETRIC *) malloc(Value);
					ERROR2IF(pOutlineTextMetric==NULL, FALSE, "Out of memory.");

					// now get the OutlineTextMetric structure
					Value = pMyCDC->GetOutlineTextMetrics(Value, pOutlineTextMetric);
					
					ERROR3IF(Value==FALSE, "Unable to retrieve OUTLINETEXTMETRIC information");

					// hurray, we've finally found what we were looking for - celebrate! ;)
					// now copy the information into the CCPanose strucure
					pPanose->SetFamilyType(pOutlineTextMetric->otmPanoseNumber.bFamilyType); 
					pPanose->SetSerifStyle(pOutlineTextMetric->otmPanoseNumber.bSerifStyle); 
					pPanose->SetWeight(pOutlineTextMetric->otmPanoseNumber.bWeight); 
					pPanose->SetProportion(pOutlineTextMetric->otmPanoseNumber.bProportion); 
					pPanose->SetContrast(pOutlineTextMetric->otmPanoseNumber.bContrast); 
					pPanose->SetStrokeVariation(pOutlineTextMetric->otmPanoseNumber.bStrokeVariation); 
					pPanose->SetArmStyle(pOutlineTextMetric->otmPanoseNumber.bArmStyle); 
					pPanose->SetLetterform(pOutlineTextMetric->otmPanoseNumber.bLetterform); 
					pPanose->SetMidline(pOutlineTextMetric->otmPanoseNumber.bMidline); 
					pPanose->SetXHeight(pOutlineTextMetric->otmPanoseNumber.bXHeight); 
					
					// finally free the memory we had claimed
					free((void *) pOutlineTextMetric);
				}
				else
				{
					// its not a TrueType font, so set the Panose number to some safe value
					pPanose->SetAllToAny();
				}

			}
			else
			{
				ERROR3("Unable to retrieve TEXTMETRIC structure from CDC.");
				ok = FALSE;
			}

			pMyCDC->SelectObject(pOldCFont);
		
			
		}
		else
		{
			ERROR3("Unable to select CFont object into the CDC.");
			ok = FALSE;
		}
	}
	else
	{
		ERROR3("Unable to create font.");
		ok = FALSE;
	}

	delete pNewCFont;

	return ok;
}

