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

// Header for the Node operations

#ifndef INC_OPNODE
#define INC_OPNODE

#define OPTOKEN_DELETEATTR		_T("RemoveAttrFromSel")

/********************************************************************************************

>	class RemoveAttributeParam : public OpParam

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/11/96

	Purpose:	Parameter for OpRemoveAttributeFromSelection, giving the ClassID of the
				attributes to remove from the selection.

	Notes;		Ideally, there would be no data members in the base class and unfortunately
				we can't derive protected cos we need to convert to the base.
				Anyway, don't access the base class members directly.

********************************************************************************************/
class RemoveAttributeParam : public OpParam
{
	CC_DECLARE_DYNAMIC(RemoveAttributeParam);

public:
	RemoveAttributeParam(AttributeIdentifier AttrClassToDelete) : 
						m_AttrID(AttrClassToDelete) {}

	operator OpParam&()	{	return *this;	}
	AttributeIdentifier GetAttrIDToDelete() const	{	return m_AttrID;	}

private:
	AttributeIdentifier	m_AttrID;
};
/********************************************************************************************

>	class OpRemoveAttributeFromSelection : public SelOperation

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/11/96

	Purpose:	Delete a Node from the tree

********************************************************************************************/
class OpRemoveAttributeFromSelection : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpRemoveAttributeFromSelection)

public:
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	virtual void GetOpName(String_256* pOpName);

protected:
	NodeAttribute* FindAttributeOfClassID(Node* const pNode, AttributeIdentifier AttrID);
	BOOL DoRemove(NodeAttribute* const pOldAttr);

private:		
};


#endif 		// INC_OPNODE
