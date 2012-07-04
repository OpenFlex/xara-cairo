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


// Implementation of the AboutDlg class
// (This code derived from layerdlg.cpp)

/* 
*/ 

#include "camtypes.h"
 
#include "aboutdlg.h"   
//#include "aboutres.h"   
//#include "app.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "camelot.h"
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "dlgmgr.h"
#include "dragmgr.h"
//#include "ensure.h"   - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "errors.h"  - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "mario.h"
//#include "ollie.h"
//#include "release.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "bubbleid.h"

#include "ccdc.h"			// For render-into-dialogue support
#include "dlgcol.h"
//#include "fillattr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "grnddib.h"
#include "cversion.h"
#include "product.h"
// Added by Craig Hamilton 21/12/00.
//#include "registry.h"
// End added.

#include "menuops.h"

CC_IMPLEMENT_DYNCREATE(AboutDlg, DialogOp)   


// This line MUST go after all CC_IMPLEMENT lines
#define new CAM_DEBUG_NEW

#if defined(DIALOGOP_ABOUT_BOX)
#ifndef STANDALONE
const INT32			AboutDlg::IDD = _R(IDD_ABOUTDLG);	// The dialogs id
#else
const INT32			AboutDlg::IDD = _R(IDD_ABOUTDLG_SA);	// The dialogs id
#endif

const CDlgMode		AboutDlg::Mode = MODELESS; 		// The dialog is modeless  

AboutDlg*			AboutDlg::TheDlg = NULL;
double				AboutDlg::CurrentAngle = -1.0;
#endif

/********************************************************************************************
>	AboutDlg::AboutDlg()
	virtual AboutDlg::~AboutDlg()


	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	AboutDlg (About Camelot dialogue) constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

#if defined(DIALOGOP_ABOUT_BOX)
AboutDlg::AboutDlg()
  : DialogOp(AboutDlg::IDD, AboutDlg::Mode) 
{   
	TheDlg = this;
	if (CurrentAngle >= 0.0)
		GetApplication()->RegisterIdleProcessor(IDLEPRIORITY_HIGH, this);
}


AboutDlg::~AboutDlg()
{   
	TheDlg = NULL;
	GetApplication()->RemoveIdleProcessor(IDLEPRIORITY_HIGH, this);
	if (CurrentAngle >= 0.0)
		CurrentAngle = -1.0;
	else
		CurrentAngle = 0.0;
}
#else
AboutDlg::AboutDlg()
{   
}

AboutDlg::~AboutDlg()
{   
}
#endif

#if defined(DIALOGOP_ABOUT_BOX)
/********************************************************************************************

>	MsgResult AboutDlg::Message(Msg* Message);

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Handles all the About dialog's messages 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

MsgResult AboutDlg::Message(Msg* Message)
{
	if (IS_OUR_DIALOG_MSG(Message))
	{
		DialogMsg* Msg = (DialogMsg*)Message;
		
		if ((Msg->DlgMsg == DIM_COMMIT) || (Msg->DlgMsg == DIM_CANCEL))
		{
			Close(); // Close and destroy the dialog 
			End();
			return (DLG_EAT_IF_HUNGRY(Msg));  	 
		}

		if (Msg->DlgMsg == DIM_REDRAW)
		{
			// We don't care which redraw gadget we're drawing - they're all
			// redrawn the same! Grab the redraw information
			ReDrawInfoType *RedrawInfo = (ReDrawInfoType *) Msg->DlgMsgParam;

			// Get a render region: Use a virtual coord space of (0,0) to (dx, dy)
			DocRect VirtualSize(0, 0, RedrawInfo->dx, RedrawInfo->dy);

			RenderRegion *pRender;
			pRender = CreateGRenderRegion(&VirtualSize, RedrawInfo);
			if (pRender != NULL)
			{
				// Interlock redraw with the drag manager to ensure we don't redraw over any drag blobs
				DragManagerOp::RedrawStarting(WindowID, Msg->GadgetID);

				DialogColourInfo RedrawColours;			// Object supplying Host OS redraw colours

				pRender->SaveContext();

				DocColour	colTrans( COLOUR_TRANS );
				pRender->SetLineColour( colTrans );

				LinearFillAttribute GradFill;
				ColourHSVT ColDef;
				if (CurrentAngle >= 0.0)
				{
					if (Msg->GadgetID == _R(IDC_STRIPE1))
						CurrentAngle = (CurrentAngle >= 1.0) ? 0.0 : CurrentAngle + 0.001;

					ColDef.Hue = (Msg->GadgetID == _R(IDC_STRIPE1)) ? CurrentAngle : 1.0 - CurrentAngle;
					ColDef.Saturation = 1.0;
					ColDef.Value = 0.9;
				}
				else
				{
					ColDef.Hue = 0.0;
					ColDef.Saturation = 0.0;
					ColDef.Value = 0.0;
				}
				GradFill.Colour		= DocColour(COLOURMODEL_HSVT, (ColourGeneric*) &ColDef);
				if (CurrentAngle < 0.0)
					ColDef.Value = 0.75;
				GradFill.EndColour	= DocColour(COLOURMODEL_HSVT, (ColourGeneric*) &ColDef);

				DocCoord ThePoint(0, 0);
				GradFill.SetStartPoint(&ThePoint);
				ThePoint = DocCoord(RedrawInfo->dx, 0);
				GradFill.SetEndPoint(&ThePoint);
				GradFill.SetEndPoint2(NULL);

				pRender->SetFillGeometry(&GradFill, FALSE);			// Set Grad-filled

				FillEffectAltRainbowAttribute AltRainbow;
				if (CurrentAngle >= 0.0)
					pRender->SetFillEffect(&AltRainbow, FALSE);		// Set alt-rainbow fill

				// And create and render a rectangular path (must use a path to get grad fill)
				Path SquarePath;
				SquarePath.Initialise(12, 12);
				SquarePath.FindStartOfPath();

				SquarePath.InsertMoveTo(VirtualSize.lo);
				SquarePath.InsertLineTo(DocCoord(VirtualSize.hi.x, VirtualSize.lo.y));
				SquarePath.InsertLineTo(VirtualSize.hi);
				SquarePath.InsertLineTo(DocCoord(VirtualSize.lo.x, VirtualSize.hi.y));
				SquarePath.IsFilled = TRUE;

				pRender->DrawPath(&SquarePath);		// Render the value square

				pRender->RestoreContext();

				DestroyGRenderRegion(pRender);

				// And turn off the drag redraw interlock
				DragManagerOp::RedrawFinished();
			}
		}
	}
	return DialogOp::Message(Message);  
}  



BOOL AboutDlg::OnIdleEvent()
{
	InvalidateGadget(_R(IDC_STRIPE1));
	InvalidateGadget(_R(IDC_STRIPE2));

	PaintGadgetNow(_R(IDC_STRIPE1));
	PaintGadgetNow(_R(IDC_STRIPE2));

	return TRUE;
}
#endif


/********************************************************************************************

>	OpState	AboutDlg::GetState(String_256*, OpDescriptor*)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Returns the OpState of the About Dialogue operation
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

OpState	AboutDlg::GetState(String_256*, OpDescriptor*)
{    
	OpState OpSt;
	OpSt.Greyed = false;
	
	return(OpSt);
}

/********************************************************************************************

>	BOOL AboutDlg::Init()

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/94
	Inputs:		-
	Outputs:	-
	Returns:	FALSE if it fails (due to lack of memory)
	Purpose:	Creates an OpDescriptor for an About dialog
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL AboutDlg::Init()
{  
	return (RegisterOpDescriptor(
 								0,
 								_R(IDS_ABOUTDLG2), 
								CC_RUNTIME_CLASS(AboutDlg),
 								OPTOKEN_ABOUTDLG,
 								AboutDlg::GetState,
 								0,	/* help ID */
 								_R(IDBBL_ABOUTDLG),
								0,
 								0,	/* bitmap ID */
 								SYSTEMBAR_ILLEGAL,				// Bar ID
								FALSE,							// Recieve system messages
								FALSE,							// Smart duplicate operation
								TRUE,							// Clean operation
								0,								// No vertical counterpart
								_R(IDS_BARSINFO_ONE)				// String for one copy only
								));

}   
 
#if defined(DIALOGOP_ABOUT_BOX)
/********************************************************************************************

>	BOOL AboutDlg::Create()

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/94
	Inputs:		-
	Outputs:	-
	Returns:	FALSE if it fails
	Purpose:	Creates an About dialog (without showing it), and fills in its info fields
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL AboutDlg::Create()
{                            
	if (DialogOp::Create())
	{  
		InitDialog();		// Set the initial control values
		return TRUE; 
    }

	return FALSE;
}           
#endif


/********************************************************************************************

>	void AboutDlg::Do(OpDescriptor*)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates and shows an About Dialog
	Errors:		-
	SeeAlso:	-

********************************************************************************************/


void AboutDlg::Do(OpDescriptor*)
{
#if defined(DIALOGOP_ABOUT_BOX)
	Create();
	Open();
#else	
	CCamApp::DoAboutBox();
	End();
#endif
}


#if defined(DIALOGOP_ABOUT_BOX)

/********************************************************************************************

>	BOOL AboutDlg::InitDialog()

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/94
	Inputs:		-
	Outputs:	-
	Returns:	FALSE if initialisation failed
	Purpose:	Initialises an AboutDlg ready for being shown
	Errors:		-
	SeeAlso:	-

********************************************************************************************/


BOOL AboutDlg::InitDialog()
{	
	String_64	Text1, Text2, ProdDetailed;

	// add the static RETAIL version number that the user sees and that is used 
	// to determine if new versions are available. 

	Text1 = TEXT(PRODUCT_RETAIL_VERSION_NO "  " __DATE__);

	// the product name we display here should be the more detailed name of this product
	// (e.g. Xara Xtreme Plus, Xara Xtreme Pro.)

	ProdDetailed = _T("Banana hammock");

	Text2.MakeMsg(_R(IDS_CAMVERSION), &ProdDetailed, &Text1);

	SetStringGadgetValue(_R(IDC_CAMVERSION), &Text2);		// (Camelot program version number)

/*#ifndef STANDALONE
	Text1 = (LPCTSTR) ReleaseInfo::GetLicensee();		// (Licensee)
	SetStringGadgetValue(_R(IDC_LICENSEE), &Text1);

	Text1 = (LPCTSTR) ReleaseInfo::GetCompany();		// (Organisation)
	SetStringGadgetValue(_R(IDC_COMPANY), &Text1);

	wxString	serialNumber = OpRegister::GetSerialNumber();
	Text1 = (LPCTSTR) serialNumber;
	SetStringGadgetValue(_R(IDC_SERIAL), &Text1);
	// End altered.

#endif */

  	return TRUE; 
}
#endif
