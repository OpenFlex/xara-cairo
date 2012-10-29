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


/*
//*/

#include "camtypes.h"
#include "qualops.h"
#include "menuops.h"
//#include "mario.h"
//#include "resource.h"
//#include "rik.h"
//#include "barsdlgs.h"
#include "bubbleid.h"
#include "brushmsg.h"


CC_IMPLEMENT_DYNAMIC(QualitySliderDescriptor, OpDescriptor)
CC_IMPLEMENT_DYNCREATE(OpQuality, Operation)

#define new CAM_DEBUG_NEW


/********************************************************************************************

>	QualitySliderDescriptor::QualitySliderDescriptor(UINT32 toolID,
						 							UINT32 txID,
						 							CCRuntimeClass* Op,
						 							TCHAR* tok,
						 							pfnGetState gs,
						 							UINT32 helpId,
						 							UINT32 bubbleID,
						 							UINT32 resourceID,
						 							UINT32 controlID,
						 							BOOL ReceiveMessages,
						 							BOOL Smart,
						 							BOOL Clean)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/11/94
	Inputs:		As for OpDescriptor
	Purpose:	Builds a new Quality Slider Op Descriptor
	SeeAlso:	OpDescriptor::OpDescriptor

********************************************************************************************/

QualitySliderDescriptor::QualitySliderDescriptor(
						 	UINT32 toolID,                    // Tool (Module) Identifier
						 	UINT32 txID,                      // String Resource ID
						 	CCRuntimeClass* Op,				// pointer to the Op's runtime class object
						 	TCHAR* tok,						// pointer to the token string
						 	pfnGetState gs,					// pointer to the GetState function
						 	UINT32 helpId,				// help identifier 
						 	UINT32 bubbleID,				// string resource for bubble help
						 	UINT32 resourceID,			// resource ID
						 	UINT32 controlID,				// control ID within resource
						 	BOOL ReceiveMessages, 		
						 	BOOL Smart, 
						 	BOOL Clean 
						   )
	: OpDescriptor(toolID, txID, Op, tok, gs, helpId, bubbleID, resourceID, controlID,
					ReceiveMessages, Smart, Clean, 0, GREY_WHEN_NO_CURRENT_DOC | DONT_GREY_WHEN_SELECT_INSIDE)
{
	// Does nothing
}


	 

/********************************************************************************************

>	void QualitySliderDescriptor::OnControlCreate(OpDescControlCreateMsg* CreateMsg)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/11/94
	Inputs:		CreateMsg - Details about the control being created
	Purpose:	Gets called when the control is first created to allow me to init it.

********************************************************************************************/

void QualitySliderDescriptor::OnControlCreate(OpDescControlCreateMsg* CreateMsg)
{
	// Get the dialog op details I need
	DialogOp* pDialogOp = CreateMsg->pDlgOp;
	CGadgetID GadgetID = CreateMsg->SetGadgetID;

	// And ask the control to use bitmaps
	pDialogOp->SetGadgetRange(GadgetID, 10, 110, 25);
	BOOL IsHorizontal = TRUE;
	if	(pDialogOp->IsKindOf(CC_RUNTIME_CLASS(DialogBarOp)))
		 IsHorizontal = ((DialogBarOp *) pDialogOp)->IsHorizontal();
	
	if(IsHorizontal)
		pDialogOp->SetGadgetBitmaps(GadgetID, _R(IDB_QUALITYBASE),_R(IDB_QUALITYSLIDER));
	else
		pDialogOp->SetGadgetBitmaps(GadgetID, _R(IDB_QUALITYBASEVERT), _R(IDB_QUALITYSLIDERVERT));

	// If there is a view, set the position of the slider according to the
	// selected view's view quality
	DocView* pDocView = DocView::GetSelected();
	INT32 NewQuality;
	if (pDocView!=NULL)
	{
		// Ask the view about its view quality and set the sliders position
		NewQuality = pDocView->RenderQuality.GetQuality();
	}
	else
	{
		// Use the default quality value
		NewQuality = Quality::DefaultQuality.QualityValue;
	}

	// Set the slider position
	pDialogOp->SetLongGadgetValue(GadgetID, NewQuality /*110-NewQuality+10*/);
}



/********************************************************************************************

>	BOOL QualitySliderDescriptor::OnDocViewMsg(DocView* pDocView, DocViewMsg::DocViewState State)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Inputs:		pDocView - The new docview that is becoming active.
	Returns:	TRUE if it happened
	Purpose:	Respond to a DocView changing message

********************************************************************************************/

BOOL QualitySliderDescriptor::OnDocViewMsg(DocView* pDocView, DocViewMsg::DocViewState State)
{
	// Only respond to the DocView changing
	if (State==DocViewMsg::SELCHANGED)
	{
		// see if it is valid
		if (pDocView != NULL)
		{
			// Its OK, change the sliders
			INT32 NewQuality = pDocView->RenderQuality.GetQuality();

			// update all slider controls that show the view quality
			List Gadgets;
			if (BuildGadgetList(&Gadgets))
			{
				// Found some. Set the controls position according to the quality
				GadgetListItem* pGadgetItem = (GadgetListItem*) Gadgets.GetHead();

				while (pGadgetItem!=NULL)
				{
					// Set the sliders position
					pGadgetItem->pDialogOp->SetLongGadgetValue(pGadgetItem->gidGadgetID, NewQuality /*110-NewQuality+10*/);

					// go find the next gadget
					pGadgetItem = (GadgetListItem*) Gadgets.GetNext(pGadgetItem);
				}
		
				// Clean out the list
				Gadgets.DeleteAll();
			}
		}
	}
	return TRUE;
}



/********************************************************************************************

>	void QualitySliderDescriptor::OnSliderSet(OpDescControlMsg* SelChangedMsg)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/11/94
	Inputs:		SelChangedMsg - The message details
	Purpose:	Informs us when the slider position changes

********************************************************************************************/

void QualitySliderDescriptor::OnSliderSet(OpDescControlMsg* SelChangedMsg)
{
	// Go find the details we need
	DialogOp* pDialogOp = SelChangedMsg->pDlgOp;
	CGadgetID GadgetID = SelChangedMsg->SetGadgetID;

	// get the position of the slider
	BOOL Valid;
	INT32 NewPos = pDialogOp->GetLongGadgetValue(GadgetID, 10, 110, 0, &Valid);

	// If it worked, tell the operation
	if (Valid)
	{
		// Set the opdescriptors idea of the current slider position
		// and call the operation
//		CurrentSliderPos = 110 - NewPos + 10;
		CurrentSliderPos = NewPos;
		Invoke();
	}
}


/********************************************************************************************

>	OpState QualitySliderDescriptor::GetState(String_256*, OpDescriptor*)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/11/94
	Inputs:		None used
	Returns:	Opstate
	Purpose:	Makes the opdescriptor always available

********************************************************************************************/

OpState QualitySliderDescriptor::GetState(String_256*, OpDescriptor*)
{
	// The state is unchanged
	OpState Blobby;
	return Blobby;
}




/********************************************************************************************

>	void QualitySliderDescriptor::Update()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/3/95
	Purpose:	Updates all the slider controls if the view quality has been changed by an
				outside influence (eg when loading a new document)

********************************************************************************************/

void QualitySliderDescriptor::Update()
{
	// Get the "selected" DocView, ie. the view that the user has made top-most.
	DocView* pDocView = DocView::GetSelected();
	if (pDocView!=NULL)
	{
		// Find the Quality slider descriptot
		OpDescriptor* pOpDesc = OpDescriptor::FindOpDescriptor( OPTOKEN_QUALITYSLIDER );
	
		// Update it with values of the Selected DocView.
		if (pOpDesc!= NULL)
			((QualitySliderDescriptor*) pOpDesc)->OnQualityChanged(pDocView);
	}
}


/********************************************************************************************

>	void QualitySliderDescriptor::OnQualityChanged(DocView* pView)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/3/95
	Inputs:		pView - the docview to look at
	Purpose:	Updates all the sliders visible sliders so that they show the changed
				view quality.

********************************************************************************************/

void QualitySliderDescriptor::OnQualityChanged(DocView* pView)
{
	// see if it is valid
	if (pView != NULL)
	{
		// Its OK, change the sliders
		INT32 NewQuality = pView->RenderQuality.GetQuality();

		// update all slider controls that show the view quality
		List Gadgets;
		if (BuildGadgetList(&Gadgets))
		{
			// Found some. Set the controls position according to the quality
			GadgetListItem* pGadgetItem = (GadgetListItem*) Gadgets.GetHead();

			while (pGadgetItem!=NULL)
			{
				// Set the sliders position
				pGadgetItem->pDialogOp->SetLongGadgetValue(pGadgetItem->gidGadgetID, /*110-NewQuality+10*/ NewQuality);

				// go find the next gadget
				pGadgetItem = (GadgetListItem*) Gadgets.GetNext(pGadgetItem);
			}
	
			// Clean out the list
			Gadgets.DeleteAll();
		}
	}
}

/********************************************************************************************

>	BOOL OpQuality::Init()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/11/94
	Returns:	TRUE if the Quality Op was started ok
	Purpose:	Creates all the opDescriptors that call this operation.

********************************************************************************************/

BOOL OpQuality::Init()
{
	// Register our default quality preference - we default to maximum quality.
	Camelot.DeclareSection( _T("Rendering"), 20 ); 
	Quality::DefaultQuality.QualityValue = QUALITY_MAX;
	Camelot.DeclarePref( _T("Rendering"), _T("DefaultQuality"), 
						&Quality::DefaultQuality.QualityValue, 10, QUALITY_MAX); 

	// Create a new OpDescriptor for the slider
	QualitySliderDescriptor* pOpDesc = new QualitySliderDescriptor(0,
									_R(IDS_VIEWQUALITY), 
									CC_RUNTIME_CLASS(OpQuality), 
									OPTOKEN_QUALITYSLIDER,
									QualitySliderDescriptor::GetState, 
									0, 
									_R(IDBBL_VIEWQUALITYSLIDER),
									_R(IDC_QUALITYSLIDER),
									_R(IDC_QUALITYSLIDER));

	// check that it worked
	if (pOpDesc==NULL)
		return FALSE;

	// and do the same for the menu option descriptors
	if (!Operation::RegisterOpDescriptor(
						0,
						_R(IDS_QUALITY_ANTI_ALIASED),
						CC_RUNTIME_CLASS(OpQuality),
						OPTOKEN_QUALITYANTIALIASED,
						OpQuality::GetState,
						0,								// help ID
						_R(IDBBL_QUALITYANTIALIAS),			// bubble help
						_R(IDD_BARCONTROLSTORE),			// resource ID
						_R(IDC_BTN_WINDOWQUALITYAA),		// control ID
						SYSTEMBAR_WINDOW,				// Bar ID
						TRUE,							// Recieve system messages
						FALSE,							// Smart duplicate operation
						TRUE,							// Clean operation
						0,								// No vertical counterpart
						0,								// String for one copy only error
						(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
						TRUE							// tickable

						))
		return FALSE;

	if (!Operation::RegisterOpDescriptor(
						0,
						_R(IDS_QUALITY_NORMAL),
						CC_RUNTIME_CLASS(OpQuality),
						OPTOKEN_QUALITYNORMAL,
						OpQuality::GetState,
						0,								// help ID
						_R(IDBBL_QUALITYNORMAL),			// bubble help
						_R(IDD_BARCONTROLSTORE),			// resource ID
						_R(IDC_BTN_WINDOWQUALITYNORMAL),	// control ID
						SYSTEMBAR_WINDOW,				// Bar ID
						TRUE,							// Recieve system messages
						FALSE,							// Smart duplicate operation
						TRUE,							// Clean operation
						0,								// No vertical counterpart
						0,								// String for one copy only error
						(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
						TRUE							// tickable
						))
		return FALSE;

	if (!Operation::RegisterOpDescriptor(
						0,
						_R(IDS_QUALITY_SIMPLE),
						CC_RUNTIME_CLASS(OpQuality),
						OPTOKEN_QUALITYSIMPLE,
						OpQuality::GetState,
						0,								// help ID 
						_R(IDBBL_QUALITYSIMPLE),			// bubble help
						_R(IDD_BARCONTROLSTORE),			// resource ID
						_R(IDC_BTN_WINDOWQUALITYSIMPLE),	// control ID
						SYSTEMBAR_WINDOW,				// Bar ID
						TRUE,							// Recieve system messages
						FALSE,							// Smart duplicate operation
						TRUE,							// Clean operation
						0,								// No vertical counterpart
						0,								// String for one copy only error
						(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
						TRUE							// tickable
						))
		return FALSE;

	if (!Operation::RegisterOpDescriptor(
						0,
						_R(IDS_QUALITY_OUTLINE),
						CC_RUNTIME_CLASS(OpQuality),
						OPTOKEN_QUALITYOUTLINE,
						OpQuality::GetState,
						0,								// help ID 
						_R(IDBBL_QUALITYOUTLINE),			// bubble help
						_R(IDD_BARCONTROLSTORE),			// resource ID
						_R(IDC_BTN_WINDOWQUALITYOUTLINE),	// control ID
						SYSTEMBAR_WINDOW,				// Bar ID
						TRUE,							// Recieve system messages
						FALSE,							// Smart duplicate operation
						TRUE,							// Clean operation
						0,								// No vertical counterpart
						0,								// String for one copy only error
						(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
						TRUE							// tickable
						))
		return FALSE;

	return TRUE;
}


// Operations to control Quality options
// there is one operation which is used for all values



/*******************************************************************

>	void OpQuality::Do(OpDescriptor*)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/94
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Sets quality level on current view.
	Errors:		None

*******************************************************************/

void OpQuality::Do(OpDescriptor* OpDesc)
{
	// Find out about the view
	DocView *pDocView = DocView::GetSelected();
	if (pDocView == NULL)
		return;

	// Find out the new quality setting
	INT32 NewQuality = ConvertToValue(OpDesc);

	// Use this as the new default quality.
	Quality::DefaultQuality.SetQuality(NewQuality);

	// tell the selected DocView and get it to redraw itself if it changed
	const BOOL Changed = pDocView->RenderQuality.SetQuality(NewQuality);

	// redraw the document
	if (Changed)
	{
		CBitmapCache* pBC = Camelot.GetBitmapCache();
//		pBC->DeInitialise();						// Brute force cache clear
		if ( pBC )
			pBC->RemoveLowPriorityBitmaps();		// Remove all cached bitmaps but not more permanent ones...???

		pDocView->ForceRedraw();
		BROADCAST_TO_ALL(ScreenChangeMsg());
	}
	

	OpDescriptor* pOpDesc = OpDescriptor::FindOpDescriptor(OPTOKEN_QUALITYSLIDER);
	if (pOpDesc!=NULL)
	{
		// Found the opdescriptor. Now find all the gadgets associated with it
		List Gadgets;
		if (pOpDesc->BuildGadgetList(&Gadgets))
		{
			// Found some. Set the controls position according to the quality
			GadgetListItem* pGadgetItem = (GadgetListItem*) Gadgets.GetHead();

			while (pGadgetItem!=NULL)
			{
				// Set the sliders position
				pGadgetItem->pDialogOp->SetLongGadgetValue(pGadgetItem->gidGadgetID, NewQuality /*110-NewQuality+10*/);

				// go find the next gadget
				pGadgetItem = (GadgetListItem*) Gadgets.GetNext(pGadgetItem);
			}
			
			// Clean out the list
			Gadgets.DeleteAll();
		}
	}

	// and finish
	End();
}

/*******************************************************************

>	OpQuality::OpQuality()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpQuality operation. It is not undoable.
	Errors:		None

*******************************************************************/

OpQuality::OpQuality()
{
}



/*******************************************************************

>	OpState OpQuality::GetState(String_256*, OpDescriptor*)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/4/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available.
	Errors:		None

*******************************************************************/

OpState OpQuality::GetState(String_256*, OpDescriptor* OpDesc)
{
	OpState OpSt;

	const DocView *pDocView = DocView::GetSelected();

	if (
		pDocView &&
		( pDocView->RenderQuality.GetQuality() == ConvertToValue( OpDesc ) )
	   )
		OpSt.Ticked = TRUE;

	return OpSt;
}

/********************************************************************************************

>	INT32 OpQuality::ConvertToValue( OpDescriptor* OpDesc )

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/94
	Inputs:		A pointer to an opdescriptor.
	Outputs:	-
	Returns:	Numeric value for quality based on token in opdescriptor.
	Purpose:	This is how we	use one operation for many levels of quality.
	Scope:		Private, Static

********************************************************************************************/

INT32 OpQuality::ConvertToValue( OpDescriptor* OpDesc )
{
	if( OpDesc->Token == String(OPTOKEN_QUALITYANTIALIASED) )
		return QUALITY_LEVEL_ANTI;
	
	if( OpDesc->Token == String(OPTOKEN_QUALITYNORMAL) )
		return QUALITY_LEVEL_NORMAL;
	
	if (OpDesc->Token == String(OPTOKEN_QUALITYSIMPLE))
		return QUALITY_LEVEL_SIMPLE;
	
	if (OpDesc->Token == String(OPTOKEN_QUALITYOUTLINE))
		return QUALITY_LEVEL_OUTLINE;

	if (OpDesc->Token == String(OPTOKEN_QUALITYSLIDER))
		return ((QualitySliderDescriptor*)OpDesc)->CurrentSliderPos;

	TRACE( _T("Bad opdesc token %s\n"), (TCHAR *)(OpDesc->Token) );
	ENSURE(FALSE, "OpQuality passed bad opdesc");

	return 100;			// default to Normal
}
