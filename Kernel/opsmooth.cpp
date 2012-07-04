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

// Implementation file for operation to smooth whole paths
// or between selected points

/*
*/

#include "camtypes.h"
//#include "resource.h"
//#include "barsdlgs.h" 
//#include "mike.h"
//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "opsmooth.h"
//#include "app.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "nodepath.h"
#include "ophist.h"
//#include "jim.h"

DECLARE_SOURCE("$Revision: 1282 $");
CC_IMPLEMENT_DYNCREATE( OpSmoothSelection, SelOperation )

#define new CAM_DEBUG_NEW


/********************************************************************************************

>	OpSmoothSelection::OpSmoothSelection() 

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/10/94
	Purpose:	OpSmoothSelection() constructor
	SeeAlso:	-

********************************************************************************************/

OpSmoothSelection::OpSmoothSelection()
{
	// Dummy constructor
}
  


/********************************************************************************************

>	BOOL OpSmoothSelection::Init()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/7/94
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if the operation could be successfully initialised 
				FALSE if no more memory could be allocated 
				
	Purpose:	OpDeletePoints initialiser method
	Errors:		ERROR will be called if there was insufficient memory to allocate the 
				operation.
	SeeAlso:	-

********************************************************************************************/

BOOL OpSmoothSelection::Init()
{
	return (RegisterOpDescriptor(0,									// tool ID
 								_R(IDS_SMOOTHSELECTIONOP),				// string resource ID
								CC_RUNTIME_CLASS(OpSmoothSelection),// runtime class for Op
 								OPTOKEN_SMOOTHSELECTION,			// Ptr to token string
 								OpSmoothSelection::GetState,		// GetState function
 								0,									// help ID
 								_R(IDBBL_SMOOTHSELECTIONOP),			// bubble help ID
 								_R(IDD_BARCONTROLSTORE),				// resource ID
								_R(IDC_BTN_SMOOTHSELECTIONOP),			// control ID
								SYSTEMBAR_EDIT,						// Group bar ID
								TRUE, 								// Receive messages
								FALSE,								// Smart
								FALSE,								// Clean
								0,									// One open Instance ID
								(GREY_WHEN_NO_CURRENT_DOC | GREY_WHEN_NO_SELECTION)
 								)); 

}               


/********************************************************************************************

>	OpState	OpSmoothSelection::GetState(String_256*, OpDescriptor*)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/10/94
	Inputs:		-
	Outputs:	-
	Returns:	The state of the OpSmoothSelection
	Purpose:	For finding the OpSmoothSelection state. 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

OpState	OpSmoothSelection::GetState(String_256* UIDescription, OpDescriptor*)
{
	OpState OpSt;
	String_256 DisableReason; 

   	OpSt.Greyed = FALSE;
	BOOL FoundSelected = FALSE;

	// Go through the selection until we find a selected point

	SelRange* Selected = GetApplication()->FindSelection();
	Node* pNode = Selected->FindFirst();

	while (pNode)
	{
		if (pNode->GetRuntimeClass() == CC_RUNTIME_CLASS(NodePath))
		{
			if (((NodePath*)pNode)->InkPath.NumSplinters() >0 )
			{
				FoundSelected = TRUE;
				break;
			}

		}
		pNode = Selected->FindNext(pNode);
	}

	// The operation is disabled if there are no complex paths selected

	if (!FoundSelected)
	{
		OpSt.Greyed = TRUE;
		DisableReason = String_256(_R(IDS_NEEDS_SELECTED_POINT));
		*UIDescription = DisableReason;
	}

	return(OpSt);   
}



/********************************************************************************************

>	void OpSmoothSelection::GetOpName(String_256* OpName)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/10/94
	Inputs:		-
	Outputs:	The undo string for the operation
	Returns:	
	Purpose:	The GetOpName fn is overridden so that we return back a description
				appropriate to the type of attribute that the operation applies.
					
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void OpSmoothSelection::GetOpName(String_256* OpName)
{
	*OpName = String_256(_R(IDS_UNDO_SMOOTHSELECTIONOP));
}






/********************************************************************************************

> void OpSmoothSelection::Do(OpDescriptor* opDesc)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>		
	Created:	20/10/94
	Inputs:		pointer to an OpDescriptor (unused)
	Outputs:	-
	Returns:	-
	Purpose:	This operation will smooth all selected paths within the current document
				Before smoothing any complete path, the path is searched for selected points
				The action of the smooth given a number of selected points is as follows
				No sel points:	Smooth the whole path
				One sel point:	Smooth the whole path.
								Could smooth from the start of the path to this point but
								the user does not generally known which part is the start
								of the path.
				Two sel points:	Smooth the section of path lying between these points.
				Even number:	Smooth using inside/outside section processing.
								(a,b) (c,d) .... (y,z) etc are regions for smoothing
				Odd number:		Smooth as for even number apart from last region
								(a,b) (c,d)	........ (f,g,h)
	Errors:		failandexecute will be called if the operation fails in some way, most
				likely when no memory is available. 

********************************************************************************************/

void OpSmoothSelection::Do(OpDescriptor*)
{
	// Obtain the current selections 
	SelRange* Selected = GetApplication()->FindSelection();
	NodePath* pSmoothNode;

	// Now, because we're going to be doing mad things to the selection, we have to make a list
	// of all the selected nodes, so that adding nodes into the tree won't confuse us

	List* NodeList = Selected->MakeListOfNodes();
	NodeListItem* CurItem = (NodeListItem*)(NodeList->GetHead());

	if (!CurItem)
		goto FailAndDeleteList;

	// remember the selection before the operation
	if (!DoStartSelOp(FALSE,FALSE))
		goto FailAndDeleteList;

	while (CurItem)
	{
		if (CurItem->pNode->GetRuntimeClass() == CC_RUNTIME_CLASS(NodePath))
		{
			// get a pointer to the NodePath
			NodePath* pThisNode = (NodePath*)(CurItem->pNode);

			BOOL ok;
			Node* pnode;

			// Copy the nodepath and all its children, without placing the copy in the tree
			CALL_WITH_FAIL(pThisNode->NodeCopy(&pnode), this, ok);
			if (!ok) goto DeleteList;
			pSmoothNode = (NodePath*)pnode;

			// ok, smooth the nodepaths path data
			double error = SMOOTH_CONSTANT;
			CALL_WITH_FAIL(pSmoothNode->InkPath.SmoothRegions(error, FALSE, TRUE), this, ok);
			if (!ok) goto DeleteListAndPath;

			// update the smoothed paths bounding rectangle
			pSmoothNode->InvalidateBoundingRect();
			pSmoothNode->InkPath.ClearSubSelection();

			// Now stick the new path into the tree
			CALL_WITH_FAIL(DoInsertNewNode(pSmoothNode, pThisNode, NEXT, TRUE), this, ok);
			if (!ok) goto DeleteListAndPath;
			
			// Now we've formed a smoothed path, let's hide the original
			CALL_WITH_FAIL(DoHideNode(pThisNode,TRUE), this, ok);
			if (!ok) goto DeleteList;

		}
		CurItem = (NodeListItem*)(NodeList->GetNext(CurItem));
	}

 	End();

	// delete the nodelist (and all the list items)
	while (!NodeList->IsEmpty())
		delete (NodeListItem*)(NodeList->RemoveHead());
	delete NodeList;
	return;


FailAndDeleteList:
	while (!NodeList->IsEmpty())
		delete (NodeListItem*)(NodeList->RemoveHead());
	delete NodeList;
	FailAndExecute();
	End();
	return;

DeleteListAndPath:
	pSmoothNode->CascadeDelete();
	delete pSmoothNode;
DeleteList:
	while (!NodeList->IsEmpty())
		delete (NodeListItem*)(NodeList->RemoveHead());
	delete NodeList;
	End();
	return;

}
