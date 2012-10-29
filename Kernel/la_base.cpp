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

	Line-attributes combo-box OpDescriptor abstract base class.

*/

#include "camtypes.h"
#include "lineattr.h"
#include "attrappl.h"
//#include "mario.h"
//#include "simon.h"
//#include "justin.h"
#include "la_base.h"

#define new CAM_DEBUG_NEW


/********************************************************************************************
>	OpChangeLineAttribOpDesc::OpChangeLineAttribOpDesc(UINT32 nTxtID,
												   	   const TCHAR* lpcszToken,
												   	   UINT32 nBubbleID,
												   	   UINT32 nControlID)
	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/3/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Simply calls the UndoableOpDescriptor::UndoableOpDescriptor	base class
	Errors:		-
	SeeAlso:	UndoableOpDescriptor::UndoableOpDescriptor
********************************************************************************************/

OpChangeLineAttribOpDesc::OpChangeLineAttribOpDesc(UINT32 nTxtID,
												   const TCHAR* lpcszToken,
												   UINT32 nBubbleID,
												   UINT32 nControlID)
  :	UndoableOpDescriptor(0,
  						 nTxtID,
  						 CC_RUNTIME_CLASS(OpApplyAttribToNode),
  						 (TCHAR*) lpcszToken,
  						 GetState,
  						 0,
  						 nBubbleID,
  						 0,
  						 nControlID,
  						 TRUE,							// will receive messages
  						 FALSE,
  						 FALSE)
{
	// Empty.
}



/********************************************************************************************
>	void OpChangeLineAttribOpDesc::SetGadgetText(const String& strGadgetText)

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/95
	Inputs:		strGadgetText			the text to show in the OpDescriptor's gadgets
	Purpose:	Sets the text in the combos associated with this OpDescriptor.
********************************************************************************************/

void OpChangeLineAttribOpDesc::SetGadgetText(const String& strGadgetText)
{
	// Create a list for the dialogue manager to put gadget ID's on.
	List* pGadgetList = new List;
	if (pGadgetList == NULL)
	{
		InformError(_R(IDE_NOMORE_MEMORY));
		return;
	}

	// Obtain a list of all the combo controls.
	if (BuildGadgetList(pGadgetList))
	{
		// Iterate over each control in the list.
		for (GadgetListItem* pGadgetItem = (GadgetListItem*) pGadgetList->GetHead(); 
			 pGadgetItem != NULL; 
			 pGadgetItem = (GadgetListItem*) pGadgetList->GetNext(pGadgetItem))
		{
			// Set each control to display the text.
			pGadgetItem->pDialogOp->SetStringGadgetValue(pGadgetItem->gidGadgetID, 
														    ((String&) strGadgetText),
														    FALSE, -1);
		}

		// Tidy up.
		pGadgetList->DeleteAll();
	}

	// Deallocate gadget list.
	delete pGadgetList;
} 



/********************************************************************************************
	BOOL OpChangeLineAttribOpDesc::SetCurrentSelJoin()

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/3/95
	Outputs:	-
	Returns:	FALSE if we run out of memory etc.
	Purpose:	Sets the currently selected line width value. 

				If no objects are selected, or no selected objects require a join type
				attribute then the current join type attribute for the tool is displayed.

				If all selected objects (which require a join type) share the same join 
				type attribute then this is displayed.
				
				if the selected objects have more than one join type value then the 
				string 'MANY' is displayed. 

	Errors:		ERROR is set if we run out of memory
	Scope:		private
	SeeAlso:	-
********************************************************************************************/

BOOL OpChangeLineAttribOpDesc::SetCurrentSelectedAttrib()
{
	// Nothing to do if no current document.
	if (Document::GetCurrent() == NULL)
	{
/*		TRACEUSER( "JustinF", _T("No current document in OpChangeLineAttribOpDesc")
							 "::SetCurrentSelectedAttrib\n");
*/		
		// There is no document so blank all gadgets.
		SetGadgetText(String(_T("")));
		return TRUE;
	}

	// Determine if there is a common attribute.
	NodeAttribute* pAttr;
	SelRange::CommonAttribResult eResult;
	eResult = GetApplication()->
				 FindSelection()->
					 FindCommonAttribute(GetAttribRuntimeClass(), &pAttr);

	// Work out what to put in the combo-box according to the returned result.
	UINT32 nTxtID;
	switch (eResult)
	{
		case SelRange::ATTR_COMMON:
		case SelRange::ATTR_NONE:
		{
			// If there isn't an attribute we just return (this logic is copied from the
			// line-width combo OpDescriptor code).
			if (pAttr == NULL)
			{
/*				TRACEUSER( "JustinF", _T("No attribute in OpChangeLineAttribOpDesc")
									 "::SetCurrentSelectedAttrib\n");
*/				return TRUE;
			}

			// Check for something screwy.
			ERROR3IF(pAttr->GetRuntimeClass() != GetAttribRuntimeClass(),
					 "Wrong kind of attribute in OpChangeLineAttribOpDesc"
					 "::SetCurrentSelectedAttrib");

			// There is, so call the derived class to provide some text.
			nTxtID = ConvertAttribToStringID(pAttr);
			if (nTxtID == 0)
			{
				ERROR3("Unexpected attribute type in OpChangeLineAttribOpDesc"
					   "::SetCurrentSelectedAttrib!");
				return FALSE;
			}
			break; 
		}

		case SelRange::ATTR_MANY:
			nTxtID = _R(IDS_MANY);
			break;

		default:
			ERROR3("Unexpected case in OpChangeLineAttribOpDesc::SetCurrentSelectedAttrib!");
			return FALSE;
	}

	// Set the gadget's text.
	SetGadgetText(String(nTxtID));
	return TRUE;
}



/********************************************************************************************
	virtual void OpChangeLineAttribOpDesc::OnControlCreate(OpDescControlCreateMsg* pCreateMsg);

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/3/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	This function is called whenever a combo control associated with the 
	`			OpDescriptor gets created. 
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

void OpChangeLineAttribOpDesc::OnControlCreate(OpDescControlCreateMsg* pCreateMsg)
{
	// Initialise the combo-box with the join types.
	DialogOp* pDlg = pCreateMsg->pDlgOp;									    
	CGadgetID SetGadgetID = pCreateMsg->SetGadgetID;
	
	// Set each item in the combo-box.
	for (INT32 i = 0; ; i++)
	{
		UINT32 nStringID = GetItemStringID(i);
		if (nStringID == 0) break;
		pDlg->SetStringGadgetValue(SetGadgetID, String(nStringID));
	}
	
	// Update the current selection within the combo etc.
	pDlg->SetComboListLength(SetGadgetID);
	SetCurrentSelectedAttrib(); 
}



/********************************************************************************************
>	virtual void OpChangeLineAttribOpDesc::OnSelectionChange(OpDescControlMsg* pSelChangedMsg, 
														     List* pGadgetList)
																		 	
	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/3/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	This function gets called whenever a selection is made from a combo
				box. It invokes the operation to set the line width.
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

void OpChangeLineAttribOpDesc::OnSelectionChange(OpDescControlMsg* pSelChangedMsg, List*)
{
	// Get the relevant fields.
	DialogOp* pDlg = pSelChangedMsg->pDlgOp;									    
	CGadgetID idSetGadgetID = pSelChangedMsg->SetGadgetID;

	// Try to get the text entered (or selected) within the combo.
	BOOL fValid;
	String_256 strEntered = pDlg->GetStringGadgetValue(idSetGadgetID, &fValid, -1);
	if (!fValid)
	{
		TRACEUSER( "JustinF", _T("Invalid text in OpChangeLineAttribOpDesc::OnSelectionChange\n"));
		Beep();
		SetCurrentSelectedAttrib();
		return;
	}

	INT32 nItemIndex;
	// Compare the string to each item that was placed in the combo list.
	for (nItemIndex = 0; ; nItemIndex++)
	{
		// Ask the derived class to provide the string at the given index position.
		UINT32 nTxtID = GetItemStringID(nItemIndex);
		
		// If there are no more strings then simply reset the combo to the current value.
		// The user has entered junk!
		if (nTxtID == 0)
		{
			// This will "recalc" the current value and set it.
			Beep();
			SetCurrentSelectedAttrib();
			return;
		}

		// Compare the two strings.  If they match then break out now.
		if (strEntered == String_256(nTxtID)) break;
	}

	// Obtain the index selected in the combo and pass to the derived class, which will
	// create the appropriate attribute.
	NodeAttribute* pAttr = GetNewAttrib(nItemIndex);
	if (pAttr == NULL)
	{
		TRACEUSER( "JustinF", _T("Out of memory in OpChangeLineAttribOpDesc")
							 "::OnSelectionChange\n");
		return;
	}

	// Pass it to the attribute manager.
	AttributeManager::AttributeSelected(pAttr); 

	// Update all list-boxes.  Note we must do this even if we have just set a new
	// attribute, as a SelChanging message will not be always be broadcast.
	SetCurrentSelectedAttrib();
}



/********************************************************************************************
>	virtual BOOL OpChangeLineAttribOpDesc::OnSelChangingMsg(SelChangingMsg::SelectionState state)

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/7/94
	Inputs:		-
	Outputs:	-
	Returns:	FALSE if we run out of memory
	Purpose:	This gets called when the selection state has changed.
	Errors:		-
	SeeAlso:	SelChangingMsg
********************************************************************************************/
/*
// Don't freak Justin. This This fn is replaced by OnCommonAttrsChangedMsg which handles
// all cases when the common attributes should be re-displayed. See the Message.doc file
// for more details if your curious.
BOOL OpChangeLineAttribOpDesc::OnSelChangingMsg(SelChangingMsg::SelectionState state)
{
	return (state == SelChangingMsg::SELECTIONCHANGED) ? SetCurrentSelectedAttrib()
													   : TRUE;
}
*/
/********************************************************************************************

>	virtual BOOL OpChangeLineAttribOpDesc::OnCommonAttrsChangedMsg(SelChangingMsg::SelectionState State)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/7/94
	Returns:	FALSE if we run out of memory
	Purpose:	This gets called when the common attributes have changed

********************************************************************************************/


BOOL OpChangeLineAttribOpDesc::OnCommonAttrsChangedMsg()
{
	return (SetCurrentSelectedAttrib());
}




/********************************************************************************************
>	virtual BOOL OpChangeLineAttribOpDesc::OnDocChangingMsg(Document* pChangingDoc,
														    DocState State)
	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/3/95
	Inputs:		-
	Outputs:	-
	Returns:	
	Purpose:	To update the selection width combo whenever the document changes
	Errors:		-
	SeeAlso:	DocChangingMsg
********************************************************************************************/

BOOL OpChangeLineAttribOpDesc::OnDocChangingMsg(Document*, DocChangingMsg::DocState)
{
	return SetCurrentSelectedAttrib();
}



/********************************************************************************************
>	static OpState OpChangeLineAttribOpDesc::GetState(String_256*, OpDescriptor*); 

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/3/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Generic GetState function for the OpChangeLineAttribOpDesc and derivatives.
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

OpState OpChangeLineAttribOpDesc::GetState(String_256*, OpDescriptor*)
{
	OpState os;
	if (Document::GetSelected() == NULL) os.Greyed = TRUE;
	return os;
}
