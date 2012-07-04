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
// EditSel.cpp
//
// Edit the selected item whatever that item is...
//
/*
*/

#include "camtypes.h"
//#include "app.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "editsel.h"
//#include "phil.h"
#include "helpids.h"
//#include "resource.h"
//#include "barsdlgs.h"
//#include "ink.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "spread.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "tool.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "simon.h"
#include "blobs.h"

///////////////////////////////////////////////////////////////////////////////////////////
//									EditSelectionOp

/******************************************************************************************
>	EditSelectionOp::EditSelectionOp()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/01/2004
	Purpose:	Constructs a new EditSelectionOp object: setting default operation flags, and 
				adding it to the Live list. 
******************************************************************************************/

CC_IMPLEMENT_DYNCREATE(EditSelectionOp, Operation)

EditSelectionOp::EditSelectionOp(): Operation()
{
}


/******************************************************************************************
>	void EditSelectionOp::Do(OpDescriptor*)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/01/2004
	Inputs:		An Operation Descriptor
	Purpose:	Actually "DO" a select all operation.
********************************************************************************************/

void EditSelectionOp::Do(OpDescriptor*)
{
	Range* pSelection = GetApplication()->FindSelection();

	if (pSelection)
	{
		Node* pNode = pSelection->FindFirst();
		if (pNode)
		{
			TCHAR* pOpToken = pNode->GetDefaultOpToken();
			if (pOpToken)
			{
				OpDescriptor* pOpDesc = OpDescriptor::FindOpDescriptor(pOpToken);
				if (pOpDesc)
				{
					pOpDesc->Invoke();
					return;
				}
			}
		}
	}

	End();
}


/********************************************************************************************
>	OpState EditSelectionOp::GetState(String_256* UIDescription, OpDescriptor*)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/01/2004
	Inputs:		String - representing the operation description which may be updated
				OpDescriptor - To help update the state
	Purpose:	Find the state of the EditSelectionOp operation.
********************************************************************************************/

OpState EditSelectionOp::GetState(String_256* UIDescription, OpDescriptor*)
{
	INT32 NumSelObjs=GetApplication()->FindSelection()->Count();

	// If no objects are selected, state this as the reason why it's disabled..
	if (NumSelObjs==0)
	{
		*UIDescription = String_256(_R(IDS_NO_OBJECTS_SELECTED));
	}

	// Never ticked, greyed if no selected objects
	return OpState(FALSE, NumSelObjs==0);
}


/********************************************************************************************
>	BOOL EditSelectionOp::Init()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/01/2004
	Purpose:	Create an OpDescriptor for the Select All operation
********************************************************************************************/

BOOL EditSelectionOp::Init()
{
	BTNOP(EDIT_EDITSELECTION,EditSelectionOp,EDIT);
	return(TRUE);
}


