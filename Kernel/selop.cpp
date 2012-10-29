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
#include "ophist.h"
#include "blobs.h"



CC_IMPLEMENT_DYNCREATE(SelOperation, UndoableOperation)

#define new CAM_DEBUG_NEW                                                                    

BOOL SelOperation::RenderEndSelStateBlobs; 
BOOL SelOperation::RenderStartSelStateBlobs; 
BOOL SelOperation::UndoRenderEndSelStateBlobs; 
BOOL SelOperation::UndoRenderStartSelStateBlobs; 

/********************************************************************************************

>	SelOperation::SelOperation()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	SelOperation constructor, calls the constructor of the base  class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

SelOperation::SelOperation(): UndoableOperation()
{
	m_bStartCalled = FALSE;
}

/********************************************************************************************

>	SelOperation::~SelOperation()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	SelOperation destructor 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

SelOperation::~SelOperation()
{
}

/********************************************************************************************

>	BOOL SelOperation::DoStartSelOp(BOOL RenderEndSelStateBlobs, 
									BOOL RenderStartSelBlobs = TRUE)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94
	Inputs:		RenderEndSelStateBlobs: Flag indicating if the blobs should be drawn for 
										the end selection state or not.	

										This flag should be set to TRUE if the bounds of 
										all selected objects at the end of the operation 
										are not invalidated.

				RenderStartSelBlobs: 	Flag indicating if the blobs should be drawn for
										the start selection state or not.

										This flag should be set to TRUE if the bounds of
										all selected objects at the start of an operation
										are not invalidated. 

										All operations which insert a new object 
										into the tree will have RenderStartSelBlobs set
										to TRUE.

				 
	Outputs:	-
	Returns:	TRUE if successful, FALSE if memory ran out (call End)
	 
	Purpose:	This function must be called by all SelOperations. It does the following:

				Records the current selection status  
				
	Errors:		-
	SeeAlso:	SelOperation::End()

********************************************************************************************/


BOOL SelOperation::DoStartSelOp(BOOL renderEndSelStateBlobs, 
								BOOL renderStartSelBlobs,
								BOOL UndorenderEndSelStateBlobs, 
								BOOL UndorenderStartSelBlobs)
{
	SelOperation::RenderStartSelStateBlobs = renderStartSelBlobs;
	SelOperation::RenderEndSelStateBlobs = renderEndSelStateBlobs; 

	if (UndorenderEndSelStateBlobs)
		SelOperation::UndoRenderEndSelStateBlobs = !renderEndSelStateBlobs; 
	else
		SelOperation::UndoRenderEndSelStateBlobs = renderEndSelStateBlobs; 

	if (UndorenderStartSelBlobs)
		SelOperation::UndoRenderStartSelStateBlobs = !renderStartSelBlobs; 
	else
		SelOperation::UndoRenderStartSelStateBlobs = renderStartSelBlobs; 

	// Create a SelectionState object
	ALLOC_WITH_FAIL(SelState, (new SelectionState()), this); 
	if (SelState == NULL)
	{
		return FALSE; // Failure 
	}

	// We have managed to create a SelectionState instance, now lets try and 
	// record the current selections 

	BOOL Success; 
	
	CALL_WITH_FAIL(SelState->Record(), this, Success)

	if (!Success)  // We failed to allocate enough memory to store the selection state
	{
		// There was insufficient memory to record the selections 
		delete SelState; 			// Delete the selection state 
		SelState = NULL; 
		return FALSE; 
	}
	
	// We have successfully managed to create a Selection state, create an action 
	// to restore the selections when executed 

	// Recorded the current selection state ok
 	RestoreSelectionsAction* RestoreAct;  
   	ActionCode ActCode;  

	// Attempt to initialise the action    
    ActCode = RestoreSelectionsAction::Init(this,                    
							     			&UndoActions,  
							     			SelState, 
											FALSE, 					 	// Don't Toggle
											FALSE,		 
											FALSE, 		 				// The SelState is not shared 	
											UndoRenderStartSelStateBlobs, 	// Render the start blobs ?
											UndoRenderEndSelStateBlobs,		// Render the end blobs ?
											FALSE,						// End restore 				
					 			 			( Action**)(&RestoreAct)); 
	
	
#if !defined(EXCLUDE_FROM_RALPH)
	if (RenderEndSelStateBlobs)
	{
		// Remove all existing blobs
		ENSURE(Camelot.FindSelection() != NULL, "There is no SelRange");
		Node* SelNd = Camelot.FindSelection()->FindFirst();
		if (SelNd != NULL)
		{
			Spread* SelSpread = (Spread*) SelNd->FindParent(CC_RUNTIME_CLASS(Spread));
			ENSURE(SelSpread != NULL, "Could not find spread of selected item"); 

			// Remove the blobs
			Camelot.GetBlobManager()->RenderOff(NULL, SelSpread);
		}
	}
#endif

	if (ActCode == AC_FAIL)
	{
		delete SelState; // We won't be needing this 
		return FALSE;  
	} 
	m_bStartCalled = TRUE;
	return TRUE; 
}
 
/********************************************************************************************

>	BOOL SelOperation::DoEndSelOp() 

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	This function gets called automatically by End()

				It Invalidates the rectangle covered by the selection and its blobs	

	Scope:		protected
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL SelOperation::DoEndSelOp() 
{
	// Create a SelectionState object
	ALLOC_WITH_FAIL(SelState, (new SelectionState()), this); 
	if (SelState == NULL)
	{
		return FALSE; // Failure 
	}

	// We have managed to create a SelectionState instance, now lets try and 
	// record the current selections 

	BOOL Success; 

	CALL_WITH_FAIL(SelState->Record(), this, Success)

	if (!Success)  // We failed to allocate enough memory to store the selection state
	{
		// There was insufficient memory to record the selections 
		delete SelState; 			// Delete the selection state 
		SelState = NULL; 
		return FALSE; 
	}

	// We have successfully managed to create a Selection state, create an action 
	// to restore the selections when executed 

	// Recorded the current selection state ok
	RestoreSelectionsAction* RestoreAct;  
   	ActionCode ActCode;  

	// Attempt to initialise the action    
    ActCode = RestoreSelectionsAction::Init(this,                    
							     			&UndoActions,  
							     			SelState, 
											FALSE, 		// Don't Toggle
											FALSE,		
											FALSE, 		// The SelState is not shared
											UndoRenderStartSelStateBlobs,
											UndoRenderEndSelStateBlobs,	
											TRUE,		// restore at start of undo				
					 			 			( Action**)(&RestoreAct)); 
	if (ActCode == AC_FAIL)
	{
		delete SelState; // We won't be needing this 
		return FALSE;  
	}

	// OK the operation should have finished playing with the selection states, so we can turn
	// the blob rendering back on. If the operation needs to render the end SelState blobs then
	// this is done.
	
	// If the operation needs to restore the blobs then do so
	
#if !defined(EXCLUDE_FROM_RALPH)
	if (RenderEndSelStateBlobs)
	{
		ENSURE(Camelot.FindSelection() != NULL, "There is no SelRange");
		Node* SelNd = Camelot.FindSelection()->FindFirst();
		if (SelNd != NULL)
		{
			Spread* SelSpread = (Spread*) SelNd->FindParent(CC_RUNTIME_CLASS(Spread));
			ENSURE(SelSpread != NULL, "Could not find spread of selected item"); 

			// Put the blobs back
			Camelot.GetBlobManager()->RenderOn(NULL, SelSpread);
		}
	}
#endif

	m_bStartCalled = FALSE;
	return TRUE; 
}


/********************************************************************************************

>	virtual void SelOperation::End()


	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Calls DoEndSelOp(), then Operation::End()
	Errors:		-
	SeeAlso:	-

********************************************************************************************/


void SelOperation::End()
{
	if (OpStatus == DO && (!OpFlags.Failed))
	{
		DoEndSelOp();	   // We don't want to perform this if we are undoing or 
	}
	Operation::End(); 
}
