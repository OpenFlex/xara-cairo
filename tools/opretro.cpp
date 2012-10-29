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

// The Freehand Retro Fitting operation

/*
*/

#include "camtypes.h"

#include "nodepath.h"
//#include "rik.h"
#include "opretro.h"
#include "objchge.h"


// Set things up so that the tool will be listed in the Dialog box

// Declare the class
CC_IMPLEMENT_DYNCREATE(OpRetroFit, SelOperation)

// Improved memory tracking
#define new CAM_DEBUG_NEW



/********************************************************************************************

>	BOOL OpRetroFit::Declare()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/5/94
	Returns:	TRUE if all went OK, False otherwise
	Purpose:	Adds the operation to the list of all known operations

********************************************************************************************/

BOOL OpRetroFit::Init()
{
	return (RegisterOpDescriptor(
								0, 
								_R(IDS_RETROFITOP),
								CC_RUNTIME_CLASS(OpRetroFit), 
								OPTOKEN_RETROFIT,
								OpRetroFit::GetState,
								0,	/* help ID */
								0,
								0	/* bitmap ID */));
}


/********************************************************************************************

>	OpState OpRetroFit::GetState(String_256* Description, OpDescriptor*)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/5/94
	Outputs:	Description - GetState fills this string with an approriate description
				of the current state of the push tool
	Returns:	The state of the operation, so that menu items (ticks and greying can be
				done properly
	Purpose:	Find out the state of the operation at the specific time

********************************************************************************************/

OpState OpRetroFit::GetState(String_256* Description, OpDescriptor*)
{
	OpState Blobby;
	
	return Blobby;
}






/********************************************************************************************

>	BOOL OpRetroFit::BuildUndo(NodePath* pPreviousNode, NodePath* pNewNode)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/5/94
	Inputs:		pPreviousNode - The original path. We will place our new path immediatly
				after this node in the tree
				pNewNode - The new refitted path.
	Returns:	TRUE if it worked, FALSE if it did not
	Purpose:	Builds the necessary Undo information for the refitting of a freehand path

********************************************************************************************/

BOOL OpRetroFit::BuildUndo(NodePath* pPreviousNode, NodePath* pNewNode)
{
	// A few quick error checks
	ENSURE(pPreviousNode!=NULL, "Previous Node was NULL in RetroFit::BuildUndo()");
	ENSURE(pPreviousNode->IsKindOf(CC_RUNTIME_CLASS(NodePath)), "Previous Node not a path");

	ENSURE(pNewNode!=NULL, "New Node was NULL in RetroFit::BuildUndo()");
	ENSURE(pNewNode->IsKindOf(CC_RUNTIME_CLASS(NodePath)), "New Node not a path");

	// Falg to see if it has worked
	BOOL IsOperationOk = TRUE;

	// Start the undo of the selected item
	IsOperationOk = DoStartSelOp(FALSE);

	// Will the node allow this op to take place?
	ObjChangeFlags cFlags;
	cFlags.ReplaceNode = TRUE;
	ObjChangeParam ObjChange(OBJCHANGE_STARTING,cFlags,pPreviousNode,this);
	if (IsOperationOk)
		IsOperationOk = pPreviousNode->AllowOp(&ObjChange);
	
	// insert our new object
	if (IsOperationOk)
	{
		// Insert the new node into the tree
		IsOperationOk = DoInsertNewNode(pNewNode, pPreviousNode, NEXT, TRUE);
	}

	// Invalidate the region covered by the old node
	if (IsOperationOk)
		IsOperationOk = DoInvalidateNodeRegion(pPreviousNode, TRUE);

	// Make sure everything has worked
	if (IsOperationOk)
	{
		// Remove the old node
		IsOperationOk = DoHideNode(pPreviousNode, TRUE);
	}

	ObjChange.Define(OBJCHANGE_FINISHED,cFlags,pPreviousNode,this);
	IsOperationOk = UpdateChangedNodes(&ObjChange);

	// If something went wrong then fail
	if (!IsOperationOk)
		FailAndExecute();
	
	// End the operation properly
	End();

	// return a value back to the caller
	return IsOperationOk;
}





/********************************************************************************************

>	void OpRetroFit::Do(OpDescriptor* pOpDesc)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/5/94
	Inputs:		pOpDesc - An OpDescriptor thing
	Purpose:	Builds all the undo info etc for retro fitting a freehand path.

********************************************************************************************/

void OpRetroFit::Do(OpDescriptor* pOpDesc)
{
//	if (IsUserName("Rik")) TRACE( _T("Write code here.."));
}



