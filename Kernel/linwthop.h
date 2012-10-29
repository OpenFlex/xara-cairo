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
 * */

#ifndef LINWTHOP_H
#define LINWTHOP_H

// OpToken
#define OPTOKEN_CHANGELINEWIDTH _T("ChangeLineWidth")


/********************************************************************************************
>	class ChangeLineWidthOpDesc : public OpDescriptor

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/06/94

	Purpose:	OpDescriptor to allow the user to change the line width of all selected
				objects, or to set the AttributeManager's Current line width attribute if 
				no objects are selected.

				The OpDescriptor Invokes the OpApplyAttribToSelected operation if nodes
				are selected.

********************************************************************************************/

class OpChangeLineWidthOpDesc : public UndoableOpDescriptor
{
public:
	OpChangeLineWidthOpDesc(
						 	UINT32 toolID,                    // Tool (Module) Identifier
						 	UINT32 txID,                      // String Resource ID
						 	CCRuntimeClass* Op,				// pointer to the Op's runtime class object
						 	TCHAR* tok,						// pointer to the token string
						 	pfnGetState gs,					// pointer to the GetState function
						 	UINT32 helpId = 0,				// help identifier 
						 	UINT32 bubbleID = 0,				// string resource for bubble help
						 	UINT32 resourceID = 0,			// resource ID
						 	UINT32 controlID = 0,				// control ID within resource
						 	BOOL ReceiveMessages = TRUE, 		
						 	BOOL Smart = FALSE, 
						 	BOOL Clean = FALSE 
						   );  
	 

	// Virtual fuunctions called from the default Message handler

	// Function to initialise the Combo with line widths. 
	virtual void OnControlCreate(OpDescControlCreateMsg* CreateMsg);
	
	// Function to handle a selection from the combo
	virtual void OnSelectionChange(OpDescControlMsg* SelChangedMsg, List* GadgetList);

	virtual BOOL OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State);

	virtual BOOL OnSelChangingMsg(SelChangingMsg::SelectionState State);
	virtual BOOL OnCommonAttrsChangedMsg();


	// GetState function for the OpDescriptor
	static OpState GetState(String_256* Description, OpDescriptor*); 

	// access fn. to set string in line width gadgets
	BOOL SetLineWidthGadgets(String_256& Str);
private:
	BOOL SetCurrentSelWidth();

	// This function gets called to initialise a controls Combo list
	void InitialiseControl(DialogOp* pDialogOp, CGadgetID gidGadgetID);

	BOOL SetStringInGadgets(String_256& Str);

};

#endif
