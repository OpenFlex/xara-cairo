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

// 

#include "camtypes.h"

// temp bodge, must be here to avoid Rect problems
#include "makebmp.h"		// MakeBitmapFilter;

#include "bfxopun.h"		// useful Bfx plug-in related undoable operations
#include "bfxop.h"			// useful Bfx plug-in related operations
//#include "plugres.h"		// _R(IDS_PLUGIN_FAMILY)

#include "plugmngr.h"		// main plug-in manager
#include "bfxitem.h"		// useful Bfx plug-in related items
//#include "app.h"			// GetApplication() - in camtypes.h [AUTOMATICALLY REMOVED]

//#include "bitmap.h"			// KernelBitmap - in camtypes.h [AUTOMATICALLY REMOVED]

//#include "simon.h"			// _R(IDS_NO_DOC) _R(IDS_NO_OBJECTS_SELECTED)
//#include "nodebmp.h"		// NodeBitmap
//#include "fillattr.h"		// AttrFillGeometry

// Place any IMPLEMENT type statements here
CC_IMPLEMENT_DYNCREATE(BfxPlugInUndoOp, PlugInUndoOp);

// We want better memory tracking
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	BfxPlugInUndoOp::BfxPlugInUndoOp()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/3/97
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for BfxPlugInUndoOp operation. It is undoable.
				It is derived off PlugInUndoOp which is derived off
				SelOperation as we are working off the selection.
	Errors:		None

********************************************************************************************/

BfxPlugInUndoOp::BfxPlugInUndoOp()
{
}

/********************************************************************************************

>	static BOOL BfxPlugInUndoOp::Init()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/3/97
	Returns:	TRUE if the Op was started ok
	Purpose:	Creates all the opDescriptors that call this operation.

********************************************************************************************/

BOOL BfxPlugInUndoOp::Init()
{
	BOOL ok = TRUE;
	// Set up some standard operations
	//ok = ok && RegisterOpToken(OPTOKEN_Bfx_UNDO_PLUGINS, _R(IDS_Bfx_PLUGINS),
	//						   CC_RUNTIME_CLASS(BfxPlugInUndoOp), BfxPlugInUndoOp::GetState);
	//ok = ok && RegisterOpToken(OPTOKEN_Bfx_UNDO_APPLYLAST, _R(IDS_Bfx_APPLYLAST),
	//						   CC_RUNTIME_CLASS(BfxPlugInUndoOp), BfxPlugInUndoOp::GetState);

	return ok;
}

/********************************************************************************************

>	static BOOL BfxPlugInUndoOp::CheckBitmapWithPlugIn(const String_256& OpName,
													   KernelBitmap * pBitmap,
													   BOOL IncludeUniqueName = TRUE,
													   BOOL IncludeUndoAbleSig = FALSE)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/3/97
	Inputs:		OpName				- the name of the OpToken being requested.
				pBitmap				- the bitmap being checked.
				IncludeUniqueName	- Set to True (Default) if want the
						unique name of the plug-in added to the OpToken
				IncludeUndoAbleSig	- Set to True is want the unique undoable
						sig added to the OpToken. (Default = FALSE.)
	Returns:	True if the item is ok with the plug-in, False otherwise
	Purpose:	To ask the plug-in which matches the OpName whether the
				bitmap is ok.
				Assumes only working on Bfx plug-ins. Not that this should
				make much difference at present.
	SeeAlso:	PLugInOp::CheckBitmapWithPlugIn;

********************************************************************************************/

BOOL BfxPlugInUndoOp::CheckBitmapWithPlugIn(const String_256& OpName, KernelBitmap * pBitmap,
											BOOL IncludeUniqueName, BOOL IncludeUndoAbleSig)
{
	// If no bitmap then always return False
	if (pBitmap == NULL)
		return FALSE;

	// Search the plug-ins list for the specified plug-in and check
	// that this colour depth is ok with it
	INT32 ColourDepth = pBitmap->GetBPP();
	BOOL GreyScale = pBitmap->IsGreyscale();
	PlugInManager* pManager = GetApplication()->GetPlugInManager();
	if (pManager)
	{
		PlugInItem * pPlugIn = pManager->GetFirstPlugIn();
		String_32 OpToken;
		// Add the unique undo signature
		String_32 UndoSig(TEXT(PLUGIN_UNDO_SIG));
		while (pPlugIn)
		{
			// If we are to include the unique name in the test then do so
			if (IncludeUniqueName)
				OpToken = pPlugIn->GetUniqueID();
			else
				OpToken.Empty();
			if (IncludeUndoAbleSig)
				OpToken += UndoSig;
			OpToken += pPlugIn->GetPlugInName();
			if (OpName == OpToken)
			{
				// Ask the plug-in item whether it likes this colour depth
				// Returns True if likes it, False otherwise, so we must negate this to
				// set the greyed state.
				return pPlugIn->IsBitmapModeOk(ColourDepth, GreyScale);
			}
			
			pPlugIn = pManager->GetNextPlugIn(pPlugIn);
		}
	}

	// Cannot find plug-in so return False
	return FALSE;
}

/********************************************************************************************

>	OpState	BfxPlugInUndoOp::GetState(String_256* pUIDescription, OpDescriptor* pOpDesc)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/3/97
	Inputs:		pOpDesc			- the OpDescriptor for the operation 
	Outputs:	pUIDescription	- if the Operation is enabled Then return the name of the operation to 
								 be undone Else return the reason why it is disabled
	Returns:	OpState the state of the operation
	Purpose:	To provide greying and ticking functionality for the
				operation.
	Errors:		-
	SeeAlso:	OpConvertToBitmap::GetState;

********************************************************************************************/

OpState	BfxPlugInUndoOp::GetState(String_256* pUIDescription, OpDescriptor* pOpDesc)
{
	OpState OpSt;
	String_256 DisableReason;

	// Ensure that a document exists
	if (Document::GetSelected() == NULL)
	{
		// There is no selected document
		OpSt.Greyed = TRUE;

		// Load reason why operation is disabled
		DisableReason = String_256(_R(IDS_NO_DOC));
		if (pUIDescription)
		   	*pUIDescription = DisableReason;	     
	   	return OpSt;                                 
	}

	// See if there is a bitmap in the current selection
	KernelBitmap *pBitmap = NULL;
	BOOL FoundBitmap = FALSE;

	SelRange *pSelRange = GetApplication()->FindSelection();
	if (pSelRange)
	{
		// Look for bitmap nodes and bitmap fills
		AttrFillGeometry* pFillAttr;
		FoundBitmap = pSelRange->FindBitmap(&pBitmap, NULL, NULL, &pFillAttr);
	}

	if (!FoundBitmap)
	{
		OpSt.Greyed = TRUE; 
		// Load reason why operation is disabled
		DisableReason = String_256(_R(IDS_NO_OBJECTS_SELECTED));
		if (pUIDescription)
	   		*pUIDescription = DisableReason;	        
	}
	else
	{
		if (pBitmap)
		{
			// We are always available at present if there is a bitmap
			OpSt.Greyed = FALSE;

/*			// If we have a valid bitmap then checks that it is of the correct type
			INT32 ColourDepth = pBitmap->GetBPP();

			// Only allow bitmaps of 24bpp or of 8bpp greyscale
			if (ColourDepth == 24 || (ColourDepth == 8 && pBitmap->IsGreyscale()))
			{
				// Check the bitmap depth with the plug-in itself
				// Returns True if likes it, False otherwise, so we must negate this to
				// set the greyed state.
				OpSt.Greyed = !CheckBitmapWithPlugIn(pOpDesc->Token, pBitmap, TRUE, TRUE);
			}
			else
				OpSt.Greyed = TRUE;
*/
		}
	}
	
	return OpSt;   
}

/********************************************************************************************

>	void BfxPlugInUndoOp::Do(OpDescriptor*)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/3/97
	Inputs:		pOpDesc		the OpDescriptor of the item to invoke
	Outputs:	None
	Returns:	None
	Purpose:	Invokes the plug-in specified by the OpDescriptor.
	Errors:		if no OpDescriptor is supplied
	SeeAlso:	OpConvertToBitmap::Do;

********************************************************************************************/

void BfxPlugInUndoOp::Do(OpDescriptor* pOpDesc)
{
	// Store away a copy of the OpDescriptor for later use
	m_pOpDesc = pOpDesc;

	// Search the plug-ins list for the specified plug-in and invoke it
	PlugInManager* pManager = GetApplication()->GetPlugInManager();
	if (pManager == NULL)
	{
		ERROR3("Called BfxPlugInUndoOp with no PlugInManager");
		End();
		return; 
	}

	SelRange *pSelRange = GetApplication()->FindSelection();
	if (pSelRange == NULL)
	{
		ERROR3("Called BfxPlugInUndoOp with no selection range!");
		End();
		return; 
	}

	KernelBitmap *		pBitmap = NULL;
	KernelBitmapRef *	pFoundBitmapRef = NULL;
	NodeBitmap *		pFoundNode = NULL;
	AttrFillGeometry *	pFoundFillAttribute = NULL;
	BOOL FoundBitmap = pSelRange->FindBitmap(&pBitmap, &pFoundBitmapRef, &pFoundNode, &pFoundFillAttribute);
	if (!FoundBitmap || pBitmap == NULL || pFoundBitmapRef == NULL)
	{
		ERROR3("Called BfxPlugInUndoOp with no selected bitmap in the range!");
		End();
		return; 
	}

	// We need to invalidate the region
	Range Sel(*pSelRange);
	if (!DoInvalidateNodesRegions(Sel, TRUE))
	{
		End();
		return; 
	} 

	PlugInItem * pPlugIn = pManager->GetFirstPlugIn();
	PlugInItem * pPlugInToApply = NULL;
	BOOL Found = FALSE;
	String_32 OpToken;
	// Add the unique undo signature
	String_32 UndoSig(TEXT(PLUGIN_UNDO_SIG));
	while (pPlugIn && !Found)
	{
		OpToken = pPlugIn->GetUniqueID();
		OpToken += UndoSig;
		OpToken += pPlugIn->GetPlugInName();
		if (pOpDesc->Token == OpToken)
		{
			// Note the plug-in for later use
			pPlugInToApply = pPlugIn;
			Found = TRUE;
			break;
		}

		pPlugIn = pManager->GetNextPlugIn(pPlugIn);
	}

	if (!DoStartSelOp(FALSE,FALSE))  // Try to record the selection state , don't render the blobs though 
	{
		FailAndExecute(); 
		End();
		return; 
	}
         
	// We have searched high and low for the plug-in to apply.
	// We should have found it by now and so can get on to actually using it
	Document * pDocument = Document::GetSelected();
	// If we haven't found one or there is no selected document then get out now
	if (pPlugInToApply == NULL || pDocument == NULL)
	{
		FailAndExecute();
		End();
		return; 
	}

	// We have found the desired plug-in so use it to do its stuff
	KernelBitmap* pBitmapCreated = NULL;

	BOOL AppliedOk = TRUE;
	AppliedOk = pPlugInToApply->Apply(pBitmap, pDocument, &pBitmapCreated);

	// the brightness and resize plugins are causing access violations when we simply press ok
	// within their dialog boxes.  This is caused through pBitmapCreated having been deleted.
	// i'm not exactly sure where the problem is occuring, but the following code fixes the problem.
	// the following code also guards against this sort of thing in general ....
	
	// lets just check the actual bitmap that has been returned.  If this is NULL, or 0xdddddddd
	// then we cannot allow the op to continue ....

	if (AppliedOk)
	{	// verify that please ....
		if (!pBitmapCreated)
		{
			AppliedOk = FALSE;
		}
		else
		{
			if (pBitmapCreated->HasBeenDeleted ())
			{
				AppliedOk = FALSE;		// although everything appeared to work, the bitmap has been deleted
										// => abort the op
			}
		}
	}

	if (!AppliedOk)
	{
		FailAndExecute(); 
		End();
		return; 
	}

#if 0
    // Use the special Bitmap filter as a temp bodge to stick the new bitmap in the tree   
	MakeBitmapFilter* pBitmapFilter = new MakeBitmapFilter();
	if (pBitmapFilter == NULL)
	{
		FailAndExecute();
		End();
		return; 
	}
	
	if (!pBitmapFilter->InsertBitmapIntoDocument(this, pBitmapCreated, pDocument))
	{
		delete pBitmapFilter;
		FailAndExecute();
		End();
		return; 
	}

	delete pBitmapFilter;

#else			
	// Create an action to Undo the resizing operation
	ActionApplyPlugInToBitmap *APR;

	ActionCode ApplyPlugInAction = ActionApplyPlugInToBitmap::Init( this,
 																	&UndoActions,
 																	sizeof(ActionApplyPlugInToBitmap),
																	pDocument,
																	pBitmap,
																	pFoundBitmapRef,
																	pFoundNode,
																	pFoundFillAttribute,
  																	(Action**)(&APR)
																	);

	// If the init happened ok then go and do the first operation
	if (ApplyPlugInAction != AC_FAIL) 
	{
		// Apply the initial 'Do' operation - switch the node or fill to use the
		// new bitmap that the plug-in has generated.
		if (pFoundNode != NULL)
		{
			// Its a node bitmap so change its bitmap reference to be the new one
			pFoundBitmapRef->Attach(pBitmapCreated, pDocument);

			// Say that the bitmap has changed
			//DoInvalidateNodeRegion((NodeRenderableInk*)pFoundNode, TRUE);
		}
		else if (pFoundFillAttribute != NULL)
		{
			// Its a bitmap fill so change its bitmap reference to be the new one
			pFoundBitmapRef->Attach(pBitmapCreated, pDocument);
		}
		else
		{
			ERROR3("Called ActionApplyPlugInToBitmap::Execute with no node or fill selected!");
			FailAndExecute();
			End();
			return; 
		}
	}
	else
	{
		FailAndExecute();
		End();
		return;
	}
#endif

	// Make sure that the new selection is up to date
	pSelRange = GetApplication()->FindSelection();
	if (pSelRange == NULL || !DoInvalidateNodesRegions(*pSelRange, TRUE))
	{
		// We need to invalidate the region
		FailAndExecute();
		End();
		return; 
	} 

 	End(); 
	return;
}

