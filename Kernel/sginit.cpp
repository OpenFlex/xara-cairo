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

// init.cpp - Centralised initialisation for galleries

#include "camtypes.h"
#include "sginit.h"

#include "layergal.h"	// For OpDisplayLayerGallery et al
#include "newcol.h"		// For NewColourDlg
#include "sgbitmap.h"	// For OpDisplayBitmapGallery
#include "sgcolour.h"	// For OpDisplayColourGallery && ColourSGallery::Init
//#include "sgfonts.h"	// For OpDisplayFontsGallery
//#include "sglcart.h"	// For OpDisplayLibClipartGallery et al
//#include "sglfills.h"	// For OpDisplayLibFillsGallery
#include "sgline.h"		// For OpDisplayLineGallery
#include "ngdialog.h"	// For OpDisplayNameGallery & OpNGPropertyIndexDesc
#include "layerprp.h"	// For LayerPropertiesDlg::Init()
#include "aprps.h"
//#include "frameops.h"	// OpGrabFrame::Init()

// Taken out by vector stroking code Neville 2/10/97
#ifdef VECTOR_STROKING
//#include "sglinepr.h"	// For SGalleryLinePropertiesDlg::Init()
#endif

DECLARE_SOURCE("$Revision: 1464 $");

CC_IMPLEMENT_MEMDUMP(SGInit, CC_CLASS_MEMDUMP)

#define new CAM_DEBUG_NEW
													   

#ifndef EXCLUDE_GALS

/********************************************************************************************

>	static BOOL SGInit::Init(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/2/94
	Purpose:	Initialises the supergallery system
				(Registers Ops for displaying galleries, reads preferences, etc)

********************************************************************************************/

BOOL SGInit::Init(void)
{
	// Declare the global supergallery preferences...
	Camelot.DeclareSection(TEXT("Displays"), 8);
	Camelot.DeclarePref(TEXT("Displays"), TEXT("FixedGalleryColours"),
							&SuperGallery::UseFixedColourSet);

//////////////////////////////////////////////////////////////////////////////////////////
	// I'm putting this in here - cause I can't find a better place - and seeing as these
	// are mostly display preferences anyway, it makes sense
	static INT32 defaultCompoundToEditableShapesBitmapDPI = 96;
	Camelot.DeclarePref(TEXT("Displays"), TEXT("CompCToEDPI"), &defaultCompoundToEditableShapesBitmapDPI, 10, 1000);
//////////////////////////////////////////////////////////////////////////////////////////

	// And initialise each of the derived SuperGallery systems...
	BOOL ok = (	SGalleryOptionsDlg::Init()			&&
				SGallerySearchDlg::Init()			&&
				SGallerySortDlg::Init()				&&

PORTNOTE("galleries", "Excluded various galleries")
#ifndef STANDALONE
#ifndef EXCLUDE_FROM_XARALX
				OpDisplayFrameGallery::Init()		&&
#endif // EXCLUDE_FROM_XARALX
				OpLayerGalChange::Init()			&&
#ifndef EXCLUDE_FROM_XARALX
				OpGrabFrame::Init()					&&
#endif // EXCLUDE_FROM_XARALX
// WEBSTER - markn 15/1/97
// Removed some init functions that no longer exist
#ifndef WEBSTER
				OpDisplayLayerGallery::Init()		&&
				LayerNameDlg::Init()				&&
				LayerPropertyTabsDlg::Init()		&&				

				OpDisplayLineGallery::Init()		&&
#ifdef _DEBUG // For now name gallery only on debug builds
				OpDisplayNameGallery::Init()		&&
#endif
#endif // WEBSTER				
// Taken out by vector stroking code Neville 2/10/97
#ifndef EXCLUDE_FROM_XARALX
#ifdef VECTOR_STROKING
				SGalleryLinePropertiesDlg::Init()	&&
#endif // VECTOR_STROKING	
#endif			
				ColourSGallery::Init()				&&
				OpDisplayColourGallery::Init()		&&
				ColourNameDlg::Init()				&&
				NewColourDlg::Init()				&&
				OpDisplayBitmapGallery::Init()		&&
#ifndef EXCLUDE_FROM_XARALX
				OpDisplayFontsGallery::Init()		&&
#endif // EXCLUDE_FROM_XARALX
#endif // STANDALONE
#ifndef EXCLUDE_FROM_XARALX
				LibClipartSGallery::Init()			&&
				OpDisplayLibClipartGallery::Init()	&&

#ifndef STANDALONE
				LibFillsSGallery::Init()			&&
				OpDisplayLibFillsGallery::Init()	&&
#endif

				Library::InitLibPrefs() &&
#endif // EXCLUDE_FROM_XARALX
				TRUE
			);
	
	return ok;
}


/********************************************************************************************

>	static void SGInit::DeInit(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/2/94
	Purpose:	De-Initialises the supergallery system

********************************************************************************************/

void SGInit::DeInit(void)
{
// WEBSTER - markn 15/1/97
// Removed some deinit functions that no longer exist

	// Nothing much to deinit as yet
PORTNOTE("galleries", "disabled various galleries deinit")
#ifndef STANDALONE
#ifndef WEBSTER
	LayerPropertyTabsDlg::Deinit();	
#endif	// WEBSTER	
	GIFAnimationPropertyTabsDlg::Deinit();
#ifndef EXCLUDE_FROM_XARALX
	OpGrabFrame::DeInit();
#endif
#endif
}

#endif

/********************************************************************************************

>	static void SGInit::UpdateGalleryButton(char *OpToken, BOOL IsVisible)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/2/94
	Purpose:	Helper function for gallery display Ops - whenever the gallery visibility
				changes, this should be called to update the button for it

********************************************************************************************/

void SGInit::UpdateGalleryButton(ResourceID OpToken, BOOL IsVisible)
{
	// Update all button controls that invoke this Op
	OpDescriptor* pOpDesc = OpDescriptor::FindOpDescriptor(OpToken);
	if (pOpDesc!=NULL)
	{
		// Found the opdescriptor. Now find all the gadgets associated with it
		List Gadgets;
		if (pOpDesc->BuildGadgetList(&Gadgets))
		{
			// Found some. Set the controls accordingly
			GadgetListItem* pGadgetItem = (GadgetListItem*) Gadgets.GetHead();

			while (pGadgetItem != NULL)
			{
				// Set the gadget
				pGadgetItem->pDialogOp->SetBoolGadgetSelected(pGadgetItem->gidGadgetID,
																	IsVisible);
				// Find the next gadget
				pGadgetItem = (GadgetListItem*) Gadgets.GetNext(pGadgetItem);
			}
	
			// Clean out the list
			Gadgets.DeleteAll();
		}
	}
}
