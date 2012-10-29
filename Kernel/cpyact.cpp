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

// Implementation of CopyObjectsToClipboardAction
/*
*/

#include "camtypes.h"
#include "cpyact.h"
#include "clipint.h" // Internal clipboard
#include "ophist.h"


CC_IMPLEMENT_DYNCREATE( CopyObjectsToClipboardAction, Action )


#define new CAM_DEBUG_NEW

/********************************************************************************************

>	CopyObjectsToClipboardAction::CopyObjectsToClipboardAction()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	CopyObjectsToClipboardAction constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
    
CopyObjectsToClipboardAction::CopyObjectsToClipboardAction()
{
}

/********************************************************************************************

>	CopyObjectsToClipboardAction::~CopyObjectsToClipboardAction()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	CopyObjectsToClipboardAction destructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
   
             
CopyObjectsToClipboardAction::~CopyObjectsToClipboardAction() 
{
}   


/********************************************************************************************

>	virtual ActionCode CopyObjectsToClipboardAction::Execute()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/93
	Inputs:		-
	Outputs:	ActionCode indicating if the action was successfully executed or not
	Returns:	-
	Purpose:	Executes the CopyObjectsToClipboardAction which when executed on an undo list
				does nothing except spawn a redo  CopyObjectsToClipboardAction

				When executed on a redo action list copies all objects to the clipboard
	Errors:		-
	SeeAlso:	-
    
    
********************************************************************************************/
 
ActionCode CopyObjectsToClipboardAction::Execute()
{  
    ActionCode ActCode;  
    
    // Create the twin action 
	CopyObjectsToClipboardAction* CpyObjAct; 

	if ( (ActCode = CopyObjectsToClipboardAction::Init(pOperation, 
			 			    			  	  pOppositeActLst, 
								   			  NodeRange, 
							  	   			  (Action**)(&CpyObjAct)))
		!= AC_FAIL)  
	{   
		// Is this a redo action ?
		if  (pOppositeActLst == pOperation->GetUndoActionList())
		{
			BOOL CopiedOK; 
		
			// After the operation ends we will need to inform all DocComponents in the clipboard
			// of the outcome.
			pOperation->InformDocComponentsOfOperationsOutcome(InternalClipboard::Instance()); 

			// Inform all DocComponents in the clipboard that a copy is about to take place
			BOOL ok;
			CALL_WITH_FAIL(InternalClipboard::Instance()->StartComponentCopy(), pOperation, ok)
			if (!ok)
			{
				// Start Component copy has failed so abort operation
				// Note that AbortComponentCopy will get called in the ops end method
				return AC_FAIL;
			} 


			// Copy the selection to the clipboard
			CALL_WITH_FAIL(InternalClipboard::CopyObjects(NodeRange, pOperation), pOperation, CopiedOK)

			if (!CopiedOK)
			{
				return AC_FAIL; 
			}

			// Now try and copy accross the component data
			CALL_WITH_FAIL(InternalClipboard::CopyComponentData(GetWorkingDoc()),
																pOperation,
																CopiedOK)
			if (!CopiedOK) return AC_FAIL; 
		}
		// else do nothing
	};  
			        
	return ActCode;
}     


/********************************************************************************************

>	static ActionCode CopyObjectsToClipboardAction::Init(Operation* const pOp, 
						   						ActionList* pActionList, 
						   						Range NodeRange, 
						  						Action** NewAction) 
	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/93  
	
	Inputs:		pOp: The operation to which the action should be added
				
				pActionList: The action list in the operation object
				
							 
				NodeRange: 	 The range of nodes to copy 


 	Outputs:    NewAction:   A pointer to the action if it could be allocated. 

	Returns:	AC_FAIL:     There was not enough room in the operation history for the 
							 action and the user did not wish to continue. Usually 
							 End() should be called in this situation. 
				         
				AC_NORECORD: There was not enough room in the operation history for
							 the action, but the user requested that he wished to 
							 continue without undo. 
				
				AC_OK      : The action was successfully initialised and added to the 
							 operation. 
				         
				           
	Purpose:	To check that there is sufficient room for the action in the operation
				history, and if there is, then to add the action to the operations 
				action list. 
				
				The function calls the Action::Init function passing the runtime class 
				of a CopyObjectsToClipboardAction.
	Errors:		-
	SeeAlso:	Action::Init

********************************************************************************************/

ActionCode CopyObjectsToClipboardAction::Init(Operation* const pOp, 
						   			 ActionList* pActionList, 
						   			 Range NodeRange, 
						  			 Action** NewAction) 

{ 
	ActionCode Ac = (Action::Init(pOp,
					 			  pActionList,
					 			  sizeof(CopyObjectsToClipboardAction),
					 			  CC_RUNTIME_CLASS(CopyObjectsToClipboardAction), 
					 			  NewAction));   
						   
	if (Ac != AC_FAIL)
		if (*NewAction != NULL)  
		{
			// Store the range and transform in the action 
			((CopyObjectsToClipboardAction*)(*NewAction))->NodeRange = NodeRange;
		}
                
	return (Ac); 
} 

