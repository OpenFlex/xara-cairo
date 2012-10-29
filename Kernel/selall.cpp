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
// SelAll.cpp
//
// Operations to Select All and Select none
//
/*
*/

#include "camtypes.h"
#include "selall.h"
//#include "phil.h"
#include "helpids.h"
//#include "resource.h"
//#include "barsdlgs.h"
//#include "simon.h"
#include "blobs.h"

///////////////////////////////////////////////////////////////////////////////////////////
//									SelectAllOp

/******************************************************************************************
>	SelectAllOp::SelectAllOp()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Purpose:	Constructs a new SelectAllOp object: setting default operation flags, and 
				adding it to the Live list. 
******************************************************************************************/

CC_IMPLEMENT_DYNCREATE(SelectAllOp, Operation)

SelectAllOp::SelectAllOp(): Operation()
{
}


/******************************************************************************************
>	void SelectAllOp::Do(OpDescriptor*)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Inputs:		An Operation Descriptor
	Purpose:	Actually "DO" a select all operation.
********************************************************************************************/

void SelectAllOp::Do(OpDescriptor*)
{
	Spread* pSelSpread = Document::GetSelectedSpread();
//	Document * pDoc = Document::GetCurrent();

	// Only select all if we have a selected spread
	if (pSelSpread != NULL)
	{
		// Get the current tool
		Tool* pTool = Tool::GetCurrent();
		BlobManager* pBlobManager = Camelot.GetBlobManager();
		ENSURE(pBlobManager, "Can't get BlobManager");

		// Render off tool blobs if the tool dosen't do it itself on SelChange messages
		if (pTool!=NULL && !pTool->AreToolBlobsRenderedOnSelection())
//			pTool->RenderToolBlobsOff(pSelSpread,NULL);
			pBlobManager->RenderToolBlobsOff(pTool, pSelSpread, NULL);

		// ensures all blobs removed
		NodeRenderableInk::DeselectAll(TRUE);

		// get a rect encompassing the whole spread (and all objects on it)
		// NB just getting bounds of all objects => blob redraw probs
		DocRect PasteBounds	= pSelSpread->GetBoundingRect();
		DocRect PasteRect	= pSelSpread->GetPasteboardRect();
		PasteBounds = PasteBounds.Union(PasteRect);

		// Convert those Document Coords into Spread Coords
		pSelSpread->DocCoordToSpreadCoord(&PasteBounds);

		// select all selectable objects in the spread
		NodeRenderableInk::SelectAllInRect(PasteBounds,pSelSpread,NodeRenderableInk::SET);

		// Get the current tool to put its blobs back on
		if (pTool!=NULL && !pTool->AreToolBlobsRenderedOnSelection())
//			pTool->RenderToolBlobsOn(pSelSpread,NULL);
			pBlobManager->RenderToolBlobsOn(pTool, pSelSpread, NULL);

	}
	End();
}


/********************************************************************************************
>	OpState SelectAllOp::GetState(String_256* UIDescription, OpDescriptor*)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Inputs:		String - representing the operation description which may be updated
				OpDescriptor - To help update the state
	Purpose:	Find the state of the SelectAllOp operation.
********************************************************************************************/

OpState SelectAllOp::GetState(String_256* UIDescription, OpDescriptor*)
{
	return OpState(FALSE,FALSE);		// Never ticked, never greyed!
}


/********************************************************************************************
>	BOOL SelectAllOp::Init()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Purpose:	Create an OpDescriptor for the Select All operation
********************************************************************************************/

BOOL SelectAllOp::Init()
{
	BTNOP(EDITSELECTALL,SelectAllOp,EDIT);
	return(TRUE);
}


///////////////////////////////////////////////////////////////////////////////////////////
//									SelectNoneOp

/******************************************************************************************
>	SelectNoneOp::SelectNoneOp()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Purpose:	Constructs a new SelectNoneOp object: setting default operation flags, and 
				adding it to the Live list. 
******************************************************************************************/

CC_IMPLEMENT_DYNCREATE(SelectNoneOp, Operation)

SelectNoneOp::SelectNoneOp(): Operation()
{
}


/******************************************************************************************
>	void SelectNoneOp::Do(OpDescriptor*)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Inputs:		An Operation Descriptor
	Purpose:	Actually "DO" a select all operation.
********************************************************************************************/

void SelectNoneOp::Do(OpDescriptor*)
{
	Spread* pSelSpread = Document::GetSelectedSpread();

	// Only deselect all if we have a selected spread
	if (pSelSpread != NULL)
	{
		// Get the current tool
		Tool* pTool = Tool::GetCurrent();

		NodeRenderableInk::DeselectAll(TRUE);

		// Get the tool to remove all its blobs before we deselect the nodes.
		// Only do this if the current tool dosent update itself on sel changed messages
		if (pTool!=NULL && !pTool->AreToolBlobsRenderedOnSelection())
			pTool->RenderToolBlobs(pSelSpread,NULL);
	}

	End();
}


/********************************************************************************************
>	OpState SelectNoneOp::GetState(String_256* UIDescription, OpDescriptor*)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Inputs:		String - representing the operation description which may be updated
				OpDescriptor - To help update the state
	Purpose:	Find the state of the SelectNoneOp operation.
********************************************************************************************/

OpState SelectNoneOp::GetState(String_256* UIDescription, OpDescriptor*)
{
	INT32 NumSelObjs=GetApplication()->FindSelection()->Count();

	// If no objects are selected, state this as the reason why it's disabled..
	if (NumSelObjs==0)
	{
		*UIDescription = String_256 (_R(IDS_NO_OBJECTS_SELECTED));
	}

	// Never ticked, greyed if no selected objects
	return OpState(FALSE, NumSelObjs==0);
}


/********************************************************************************************
>	BOOL SelectNoneOp::Init()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Purpose:	Create an OpDescriptor for the Select All operation
********************************************************************************************/

BOOL SelectNoneOp::Init()
{
	BTNOP(EDITSELECTNONE,SelectNoneOp,EDIT);
	return(TRUE);
}





