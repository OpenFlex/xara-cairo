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

	la_base.h

	Line-attribute operations.
*/

#ifndef LA_BASE_H
#define LA_BASE_H

//#include "opdesc.h" - in camtypes.h [AUTOMATICALLY REMOVED]


/********************************************************************************************
>	class ChangeLineAttribOpDesc : public UndoableOpDescriptor

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/95
	Purpose:	Abstract base-class OpDescriptor to allow the user to change a line-attribute
				of all selected objects, or to set the AttributeManager's current attribute
				if no objects are selected.

				The OpDescriptor invokes the OpApplyAttribToSelected operation if nodes
				are selected.
********************************************************************************************/

class OpChangeLineAttribOpDesc : public UndoableOpDescriptor
{
public:
	// Creation & destruction.
	OpChangeLineAttribOpDesc(UINT32 nTxtID, const TCHAR* lpcszToken,
							 UINT32 nBubbleID, UINT32 nControlID);   

	// Initialise the gadget.
	virtual void OnControlCreate(OpDescControlCreateMsg* CreateMsg);
	
	// Message handlers.
	virtual void OnSelectionChange(OpDescControlMsg* SelChangedMsg, List* GadgetList);
	virtual BOOL OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State);
	// This fn is now redundant	(replaced by OnCommonAttrsChangedMsg)
	//virtual BOOL OnSelChangingMsg(SelChangingMsg::SelectionState State);
	virtual BOOL OnCommonAttrsChangedMsg();

	// GetState function for the OpDescriptor
	static OpState GetState(String_256* Description, OpDescriptor*); 

protected:
	// This functions sets the given text in all gadgets associated with this OpDescriptor.
	void SetGadgetText(const String& str);

	// This function handles setting the text within the combo (to do this it calls the above
	// SetGadgetText function).  In extreme cases you can override this.
	virtual BOOL SetCurrentSelectedAttrib();
	
	// Derived classes must provide these functions.  This one returns the run-time class
	// of the attribute the derived class is interested in.
	virtual CCRuntimeClass* GetAttribRuntimeClass() const = 0;
	
	// This one returns a string ID which describes the given attribute.
	virtual UINT32 ConvertAttribToStringID(NodeAttribute* pAttr) const = 0;
	
	// This one returns the string ID of the text to put in the combo-box at the given
	// index (position), or 0 if there isn't any item at the given index.
	virtual UINT32 GetItemStringID(INT32 nItemIndex) const = 0;
	
	// This one converts the given combo index position into a pointer to the appropriate
	// kind of attribute.
	virtual NodeAttribute* GetNewAttrib(INT32 nItemIndex) const = 0;
};

#endif	// !LA_BASE_H
