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



#include "camtypes.h"

#include "brshgdgt.h"
#include "brushdlg.h"

#define new CAM_DEBUG_NEW					// use camelot new

CBrushGadget::CBrushGadget ()
	: pOwningBar_m( 0 ),
	  GadgetID_m( 0 ),
	  BubbleID_m( 0 ),
	  StatusID_m( 0 ),
	  pDialog_m( 0 )
{
	DisableTimeStampingInDlg = FALSE;
	EditingBrushDefinition = FALSE;
	pDialog_m = NULL;
}

CBrushGadget::~CBrushGadget ()
{
	delete (pDialog_m);
}

void  CBrushGadget::LinkControlButton
(
	InformationBarOp*	pOwningBar,
	CGadgetID			GadgetID,
	UINT32				BubbleID,
	UINT32				StatusID
)
{ 
	if((pOwningBar != 0) && (GadgetID != 0) && (BubbleID != 0) && (StatusID != 0))
	{
		/// set members
		{
			pOwningBar_m  =  pOwningBar;
			GadgetID_m    =  GadgetID;
			InfobarGadgetID_m = -1;				// set this to an (obviously) invalid value
												// we use to route our data back to the relevant
												// infobar button ....  (which originiates from
												// within the CBiasGainGadget on the
												// CBiasGainDlg
			BubbleID_m    =  BubbleID;
			StatusID_m    =  StatusID;
			//useFillProfile = FALSE;
			//useTranspFillProfile = FALSE;
		}

		HWND gadget = ::GetDlgItem (pOwningBar->WindowID, GadgetID);
		SendMessage (gadget, EM_SETREADONLY, FALSE, 0);	// Clear the Read Only Flag
		pOwningBar->SetGadgetHelp (GadgetID, BubbleID, StatusID);
	}
}

void  CBrushGadget::Message (DialogMsg* pMessage)
{
//	Message( pMessage,  CProfileBiasGain() );
}

void  CBrushGadget::CloseDialog ()
{
	if(pDialog_m != 0)
	{
		DialogMsg  MessageCancel (0, DIM_CANCEL, GadgetID_m);

		pDialog_m->Message (&MessageCancel);

		// the above also (indirectly) retoggles the controlling buttons state
		//pOwningBar_m->SetLongGadgetValue (GadgetID_m, 0);
	}
}

void  CBrushGadget::DialogHasOpened ()
{
}


void  CBrushGadget::DialogHasClosed ()
{
	if (pDialog_m != NULL)
		delete (pDialog_m);
	pDialog_m = NULL;

	// and retoggle the controlling button if we are launched from a bar
//	if (pOwningBar_m != NULL)
//		pOwningBar_m->SetLongGadgetValue (GadgetID_m, 0);
}


CGadgetID  CBrushGadget::GetGadgetID () const
{
	return (GadgetID_m);
}


void CBrushGadget::GetDialogTitle (String_256& DlgTitle) const
{
	DlgTitle.Load (BubbleID_m);
}

void CBrushGadget::HandleBrushButtonClick (BrushData* AppliedBrush, AttrBrushType* pBrush)
{
	if (AppliedBrush == NULL)
	{
		ERROR3("Invalid input parameters");
		return;
	}
	
	if (!(IsDialogOpen ()))
	{
		pDialog_m = new CBrushEditDlg();
		BOOL bMany = FALSE, bAllSameType = TRUE;
								
		//CProfileBiasGain* appliedBiasGain = GetProfileFromSelection (ProfileGadgetID, &bMany, &bAllSameType);

		//if (bAllSameType != FALSE)
		//{
		pDialog_m->InvokeVia (*(this), AppliedBrush, pBrush, bMany);
		//}
	}
	else
	{
		CloseDialog ();
	}
}

void CBrushGadget::HandleBrushButtonClick (BrushHandle Handle)
{
	if (Handle == BrushHandle_NoBrush)
		return;
	if (!(IsDialogOpen ()))
	{
		pDialog_m = new CBrushEditDlg();
						
		pDialog_m->InvokeVia (*(this), Handle);
	}
	else
	{
		CloseDialog ();
	}
}

void CBrushGadget::HandleBrushButtonClick (BrushData* AppliedBrush, AttrBrushType* pBrush, AttrBrushType* pOrigBrush)
{
	if (AppliedBrush == NULL || pBrush == NULL)
	{
		ERROR3("Invalid input parameters");
		return;
	}
	
	if (!(IsDialogOpen ()))
	{
		pDialog_m = new CBrushEditDlg();
		BOOL bMany = FALSE, bAllSameType = TRUE;
								
		//CProfileBiasGain* appliedBiasGain = GetProfileFromSelection (ProfileGadgetID, &bMany, &bAllSameType);

		//if (bAllSameType != FALSE)
		//{
		pDialog_m->InvokeVia (*(this), AppliedBrush, pBrush, pOrigBrush, bMany);
		//}
	}
	else
	{
		CloseDialog ();
	}
}

void CBrushGadget::ReInitialiseDialog (BrushData* pData)
{
	if (/*(ReInitOn != NULL) &&*/ (pDialog_m != NULL))
	{
		if (pData != NULL )
		{
			pDialog_m->ReInitialiseDialog (pData);
		}
	}
}
