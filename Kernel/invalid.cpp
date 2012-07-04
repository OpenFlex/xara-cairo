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

// The Invalidate an arbitary region action

/*
*/

#include "camtypes.h"
#include "invalid.h"
//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// declare the source
DECLARE_SOURCE("$Revision: 1282 $");

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
CC_IMPLEMENT_DYNCREATE(InvalidateArbitaryAction, Action)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW



/********************************************************************************************

>	InvalidateArbitaryAction::InvalidateArbitaryAction()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/8/94
	Purpose:	dummy constructor

********************************************************************************************/

InvalidateArbitaryAction::InvalidateArbitaryAction()
{
}
	

/********************************************************************************************

>	ActionCode InvalidateArbitaryAction::Init(Operation* const pOp, ActionList* pActionList,
								Spread* pSpread, DocRect& InvalidRect, Action** NewAction)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/8/94
	Inputs:		pOp - The operation that this action is being created from
				pActionList - The action list that it should be in
				pSpread - The spread that the region to invalidate is on
				InvalidateRect - The region that requires invalidating
	Outputs:	NewAction - Will hold a pointer to an action
	Returns:	an action code
	Purpose:	Creates a new InvalidateArbitaryAction that invalidates an arbitary region
				in the document

********************************************************************************************/

ActionCode InvalidateArbitaryAction::Init(Operation* const pOp, ActionList* pActionList, Spread* pSpread, 
						   const DocRect& InvalidRect, Action** NewAction)
{
	// go and ask the base class to do all its fabby stuff
	ActionCode Ac = Action::Init(pOp, pActionList, sizeof(InvalidateArbitaryAction), 
								 CC_RUNTIME_CLASS(InvalidateArbitaryAction), NewAction);
	
	// If we got something resonable back, then set up our infomation
	if (*NewAction!=NULL)
	{
		((InvalidateArbitaryAction*)(*NewAction))->InvalidRect = InvalidRect;
		((InvalidateArbitaryAction*)(*NewAction))->pSpread = pSpread; 
	}

	// Whatever happen, we have to tell someone
	return Ac; 
}


/********************************************************************************************

>	virtual ActionCode InvalidateArbitaryAction::Execute()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/8/94
	Returns:	An Action Code
	Purpose:	Invalidates the region in the action and builds the appropriate undo/redo
				info to do it again later.

********************************************************************************************/

ActionCode InvalidateArbitaryAction::Execute()
{
	// Attempt to initialise the action    
	InvalidateArbitaryAction* InvRgnAct;  
    ActionCode ActCode = InvalidateArbitaryAction::Init(pOperation, pOppositeActLst, pSpread,
    					 InvalidRect, (Action**)(&InvRgnAct));
    
	// See if it worked
    if (ActCode != AC_FAIL)
	{   
		// Find out about the current document
		Document* pDocument = GetWorkingDoc();
		ENSURE(pDocument!=NULL, "There was no document in InvalidateArbitaryAction::Execute()" );
		
		// actually invalidate the region
		if (pDocument != NULL)
			pDocument->ForceRedraw(pSpread, InvalidRect, TRUE);
	}

	// return the action code we got back earlier
	return ActCode;
}
