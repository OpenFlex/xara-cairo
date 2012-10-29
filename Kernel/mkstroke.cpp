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
#include "mkstroke.h" 

// code headers
#include "nodepath.h"
#include "objchge.h"
#include "mkshapes.h" 

#include "nodeblnd.h"

#include "progress.h"
#include "groupops.h"
#include "pathstrk.h"
#include "sgline.h"

// resource headers
#include "bubbleid.h"
//#include "richard3.h"

      

CC_IMPLEMENT_DYNCREATE(OpMakeStroke, SelOperation)  

// ------------------------------------------------------------------------------------------
// OpMakeStroke methods
            
/********************************************************************************************
>	OpMakeStroke::OpMakeStroke() 

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/03/97
	Purpose:	OpMakeStroke constructor
********************************************************************************************/
OpMakeStroke::OpMakeStroke(): SelOperation()								
{                              
}



/********************************************************************************************
>	BOOL OpMakeStroke::Init()

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/03/97
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if the operation could be successfully initialised 
				FALSE if no more memory could be allocated 
				
	Purpose:	OpMakeStroke initialiser method
	Errors:		ERROR will be called if there was insufficient memory to allocate the 
				operation.
	SeeAlso:	-
********************************************************************************************/
BOOL OpMakeStroke::Init()
{
	return (RegisterOpDescriptor(0,							// tool id
	 							_R(IDS_MAKESTROKEOP),			// Ops name
								CC_RUNTIME_CLASS(OpMakeStroke),	// Ops class
	 							OPTOKEN_MAKE_STROKE,		// Op token
	 							OpMakeStroke::GetState,		// Get state function
	 							0,							// help ID
	 							_R(IDBBL_MAKESTROKE),			// Bubble help
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
>	OpState	OpMakeStroke::GetState(String_256*, OpDescriptor*)

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/03/97
	Inputs:		-
	Outputs:	-
	Returns:	The state of the OpMakeStroke
	Purpose:	For finding the OpMakeStroke's state. 
********************************************************************************************/
OpState	OpMakeStroke::GetState(String_256* UIDescription, OpDescriptor*)
{
	OpState OpSt;

	SelRange *pSelRange = GetApplication()->FindSelection(); 

	// Set up the ObjChangeParam so we can ask the selected nodes if they mind being deleted
	ObjChangeFlags cFlags(TRUE);
	ObjChangeParam ObjChange(OBJCHANGE_STARTING,cFlags,NULL,NULL);

	// Will one or more selected nodes allow this op?
	if (!pSelRange->AllowOp(&ObjChange,FALSE))
		OpSt.Greyed = TRUE;

	return(OpSt);   
}



/********************************************************************************************
>	void OpMakeStroke::Do(OpDescriptor*)

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/03/97
	Inputs:		OpDescriptor (unused)
	Outputs:	-
	Returns:	-
	Purpose:	Performs the MakeShapes operation. 
********************************************************************************************/
void OpMakeStroke::Do(OpDescriptor*)
{   
	// Obtain the current selections 
	Range Selection = *GetApplication()->FindSelection();
	Node* CurrentNode = Selection.FindFirst(); 
	BOOL Success = TRUE;		
	
	ERROR3IF(CurrentNode == NULL, "Make shapes called with no nodes selected"); 
	
	if (CurrentNode != NULL) // No nodes selected so End
	{                    
		// Try to record the selection state, don't render the blobs though 
		if (Success)
			Success = DoStartSelOp(FALSE,FALSE);								   

		// First, Make Shapes on everything so they're all simple paths
		String_256 Desc("Building new stroke brush...");
		Progress::Start(FALSE, &Desc);
		OpDescriptor *pOp = OpDescriptor::FindOpDescriptor(OPTOKEN_MAKE_SHAPES);
		if (pOp != NULL)
			pOp->Invoke();

		// Second, Group everything
		pOp = OpDescriptor::FindOpDescriptor(OPTOKEN_GROUP);
		if (pOp != NULL)
			pOp->Invoke();

		pOp = OpDescriptor::FindOpDescriptor(OPTOKEN_GROUP);
		if (pOp != NULL)
			pOp->Invoke();

		// Finally, create a new brush
		PathStrokerVector::BodgeRipSelection(/*(CommandIndex == 0) ? FALSE :*/ TRUE);
		Progress::Stop();

	}                   

	if (!Success)
	{
		InformError();
		FailAndExecute();
	}

 	End(); 
}			

