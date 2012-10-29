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
#include "mkshapes.h" 

// code headers
#include "nodepath.h"
#include "objchge.h"

#include "nodeblnd.h"
#include "bubbleid.h"

// resource headers
//#include "simon.h"
//#include "extendres.h"
      

CC_IMPLEMENT_DYNCREATE(OpMakeShapes, SelOperation)  
CC_IMPLEMENT_DYNCREATE(OpMakeNodesShapes, UndoableOperation);

// ------------------------------------------------------------------------------------------
// OpMakeShapes methods
            
/********************************************************************************************
>	OpMakeShapes::OpMakeShapes() 

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Purpose:	OpMakeShapes constructor
********************************************************************************************/
OpMakeShapes::OpMakeShapes(): SelOperation()								
{                              
}



/********************************************************************************************
>	BOOL OpMakeShapes::Init()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if the operation could be successfully initialised 
				FALSE if no more memory could be allocated 
				
	Purpose:	OpMakeShapes initialiser method
	Errors:		ERROR will be called if there was insufficient memory to allocate the 
				operation.
	SeeAlso:	-
********************************************************************************************/
BOOL OpMakeShapes::Init()
{
	return (RegisterOpDescriptor(0,							// tool id
	 							_R(IDS_MAKESHAPESOP),			// Ops name
								CC_RUNTIME_CLASS(OpMakeShapes),	// Ops class
	 							OPTOKEN_MAKE_SHAPES,		// Op token
	 							OpMakeShapes::GetState,		// Get state function
	 							0,							// help ID
	 							_R(IDBBL_MAKESHAPES),			// Bubble help
	 							0,							// Bitmap ID
								0,							// Control ID
								SYSTEMBAR_ILLEGAL,			// Bar to appear on
								TRUE,						// Recieve messages
								FALSE,						// Smart
								FALSE,						// Clean
								0,							// One open string ID
	GREY_WHEN_NO_CURRENT_DOC | GREY_WHEN_NO_SELECTION | DONT_GREY_WHEN_SELECT_INSIDE));
}



/********************************************************************************************
>	OpState	OpMakeShapes::GetState(String_256*, OpDescriptor*)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Inputs:		-
	Outputs:	-
	Returns:	The state of the OpMakeShapes
	Purpose:	For finding the OpMakeShapes's state. 
********************************************************************************************/
OpState	OpMakeShapes::GetState(String_256* UIDescription, OpDescriptor*)
{
	OpState OpSt;

	SelRange Sel(*(GetApplication()->FindSelection())); 
	RangeControl rg = Sel.GetRangeControlFlags();
	rg.PromoteToParent = TRUE;
	Sel.Range::SetRangeControl(rg);


	// Set up the ObjChangeParam so we can ask the selected nodes if they mind being deleted
	ObjChangeFlags cFlags(TRUE);
	ObjChangeParam ObjChange(OBJCHANGE_STARTING,cFlags,NULL,NULL);

	// Will one or more selected nodes allow this op?
	if (!Sel.AllowOp(&ObjChange,FALSE))
		OpSt.Greyed = TRUE;

	return(OpSt);   
}



/********************************************************************************************
>	void OpMakeShapes::Do(OpDescriptor*)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/94
	Inputs:		OpDescriptor (unused)
	Outputs:	-
	Returns:	-
	Purpose:	Performs the MakeShapes operation. 
********************************************************************************************/
void OpMakeShapes::Do(OpDescriptor*)
{   
	// Obtain the current selections 
	Range Selection(*GetApplication()->FindSelection());
	RangeControl rg = Selection.GetRangeControlFlags();
	rg.PromoteToParent = TRUE;
	Selection.Range::SetRangeControl(rg);

	// change the selection flags

	Node* CurrentNode = Selection.FindFirst(); 
	BOOL Success = TRUE;		
	
	ERROR3IF(CurrentNode == NULL, "Make shapes called with no nodes selected"); 
	
	if (CurrentNode != NULL) // No nodes selected so End
	{   
		// We need to invalidate the region
		if (Success)
			Success = DoInvalidateNodesRegions(Selection, TRUE, FALSE, FALSE, FALSE);	// Don't recache
                    
		// Try to record the selection state, don't render the blobs though 
		if (Success)
			Success = DoStartSelOp(FALSE,FALSE);								   

		// The DoMakeShapes function does all the work
		while (Success && CurrentNode!=NULL)
		{
			Node* Next = Selection.FindNext(CurrentNode);

// BODGE - since the group is selected and won't be replaced by anything else, no need to reselect it
// this fixes a bug where make shapes on grouped text stories/molds/blends don't leave the parent group
// selected but selects the objects inside!
			BOOL reselect = !IS_A(CurrentNode,NodeGroup) && !IS_A(CurrentNode,NodeBlend);
//			BOOL ok = TRUE;
		

			ObjChangeFlags cFlags(TRUE);
			ObjChangeParam ObjChange(OBJCHANGE_STARTING,cFlags,NULL,NULL);
			if (CurrentNode->AllowOp(&ObjChange))
			{
				BecomeA BecomeAPath(BECOMEA_REPLACE,CC_RUNTIME_CLASS(NodePath), this, reselect);
				BecomeAPath.SetResultsStayInPlace(TRUE);
				Success = CurrentNode->DoBecomeA(&BecomeAPath);
			}
	
			CurrentNode = Next;
		}

		// We need to invalidate the region again for the new positions
		GetApplication()->FindSelection()->Update();
		if (Success)
			Success = DoInvalidateNodesRegions(*GetApplication()->FindSelection(), TRUE);
	}                   

	if (!Success)
	{
		InformError();
		FailAndExecute();
	}

 	End(); 
}			



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



/********************************************************************************************

>	void OpMakeNodesShapes::DoWithParam(OpDescriptor* pOp, OpParam* pParam)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/11/1999
	Inputs:		pOp			unused pointer to an OpDescriptor.
				pParam		pointer to an OpParamMakeNodesShapes data information structure.

	Outputs:	The list of nodes, passed in through the OpParam, is converted in place
				into paths.
	Purpose:	This undoable operation converts a given list of nodes to editable shapes
				(paths), each new node retaining the selection status of the original.
	See also:	OpParamMakeNodesShapes

********************************************************************************************/
void OpMakeNodesShapes::DoWithParam(OpDescriptor* pOp, OpParam* pParam)
{
	std::list<Node*>* plpNodes = ((OpParamMakeNodesShapes*)pParam)->m_plpNodes;

	Node* pNode;
	BOOL bFirst = FALSE;
	BOOL ok = TRUE;
	for (	std::list<Node*>::iterator iterNode = plpNodes->begin();
			iterNode != plpNodes->end() && ok;
			iterNode++ )
	{
		pNode = *iterNode;
		BecomeA baInfo(BECOMEA_REPLACE, CC_RUNTIME_CLASS(NodePath), this,
											pNode->IsSelected(), bFirst);
		baInfo.SetResultsStayInPlace(TRUE);
		ok = pNode->DoBecomeA(&baInfo);

#ifdef _DEBUG
		if (ok)
			TRACEUSER( "Karim", _T("converted %s to editable shapes\n"), pNode->Name());
#endif

		bFirst = TRUE;
	}

	if (!ok)
	{
		InformError();
		FailAndExecute();
	}

	End();
	return;
}



/********************************************************************************************

>	BOOL OpMakeNodesShapes::Init()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/11/1999
	Returns:	TRUE if successful,
				FALSE otherwise.
	Purpose:	Initialise this operation.

********************************************************************************************/
BOOL OpMakeNodesShapes::Init()
{
	return (RegisterOpDescriptor(0,				// Tool ID
 				_R(IDS_MAKENODESSHAPES),	 		// string resource ID for Op description
				CC_RUNTIME_CLASS(OpMakeNodesShapes),// Op's Runtime class
 				OPTOKEN_MAKE_NODES_SHAPES,		// Op's OPTOKEN string
 				NULL,							// Op's GetState function
				0,								// associated Help system ID
				_R(IDBBL_MAKENODESSHAPES),			// string resource ID for bubble help
				0,								// bitmap ("icon") or resource ID
				0,								// associated gadget control ID
				SYSTEMBAR_ILLEGAL,				// associated info-bar ID
				FALSE,							// receive system messages
				FALSE,							// Op does smart attr optimisation
				FALSE,							// Op doesn't modify document
				0,								// when non-0, only one instance of the
												// Op is permitted, and this is the ID
												// of a string resource explaining why.
				(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC)
				));								// flags indicating conditions when the Op
												// should automatically be greyed/ticked etc.
}
