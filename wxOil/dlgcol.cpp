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

// Support for kernel use of host Operating System dialogue rendering colours

/*
*/


#include "camtypes.h"

#include "dlgcol.h"


CC_IMPLEMENT_MEMDUMP(DialogColourInfo, CC_CLASS_MEMDUMP)

#define new CAM_DEBUG_NEW


DocColour DialogColourInfo::mDialogBack;
DocColour DialogColourInfo::mTextBack;
DocColour DialogColourInfo::mTextFore;
DocColour DialogColourInfo::mDisabledTextFore;
DocColour DialogColourInfo::mHighlightedTextBack;
DocColour DialogColourInfo::mHighlightedTextFore;
DocColour DialogColourInfo::mButtonFace;
DocColour DialogColourInfo::mButtonHighlight;
DocColour DialogColourInfo::mButtonShadow;



/********************************************************************************************

>	DialogColourInfo::DialogColourInfo()

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/94

	Purpose:	Constructor. Caches the Host Operatig System's dialogue redraw colours,
				ready for use by kernel-rendered dialogues

********************************************************************************************/

DialogColourInfo::DialogColourInfo()
{
	RecacheColours();
}




/********************************************************************************************

	static void GetOSColour(DocColour *Col, INT32 ColID)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/94

	Inputs:		Col - DocColour to be set
				ColID - Windows ID of the system colour to be read (cf ::GetSysColor)

	Outputs:	Col is filled in with an appropriate definition for the colour

	Purpose:	Given a Windows COLORREF colour word, creates an equivalent DocColour

	Notes:		This method may check for specific values and tweak them to get better
				results from GRenderRegions (e.g. GDraw gives a less noticable dither
				for RGB(191,191,191) than for (192,192,192), as it cannot exactly match
				that RGB value- this is the default WIndows background grey, so it is
				important to match it as closely as possible

	Scope:		private (to dlgcol.cpp)

********************************************************************************************/

static void GetOSColour(DocColour *Col, wxSystemColour ColID)
{
	wxColour ColDef = wxSystemSettings::GetColour(ColID);
	
	if (ColDef == wxColour(192, 192, 192))
	{
		*Col = DocColour(191, 191, 191);

		Col->SetSeparable(FALSE);	// UI colours should not colour-separate
		return;
	}
	
	*Col = DocColour((INT32) ColDef.Red(),
					 (INT32) ColDef.Green(),
					 (INT32) ColDef.Blue());

	Col->SetSeparable(FALSE);		// UI colours should not colour-separate
}



/********************************************************************************************

>	void DialogColourInfo::RecacheColours(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/94

	Purpose:	Re-caches the Host Operatig System's dialogue redraw colours, ready for
				use by kernel-rendered dialogues

********************************************************************************************/

void DialogColourInfo::RecacheColours(void)
{
	GetOSColour(&mDialogBack, wxSYS_COLOUR_BTNFACE);

	GetOSColour(&mTextBack, wxSYS_COLOUR_WINDOW);
	GetOSColour(&mTextFore, wxSYS_COLOUR_WINDOWTEXT);

	GetOSColour(&mDisabledTextFore, wxSYS_COLOUR_GRAYTEXT);

	GetOSColour(&mHighlightedTextBack, wxSYS_COLOUR_HIGHLIGHT);
	GetOSColour(&mHighlightedTextFore, wxSYS_COLOUR_HIGHLIGHTTEXT);

	GetOSColour(&mButtonFace, wxSYS_COLOUR_BTNFACE);
	GetOSColour(&mButtonHighlight, wxSYS_COLOUR_BTNHIGHLIGHT);
	GetOSColour(&mButtonShadow, wxSYS_COLOUR_BTNSHADOW);
}




