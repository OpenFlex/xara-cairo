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

// AttrAppl.h - The OpApplyAttributeToSelected class

#ifndef INC_ATTRAPPL
#define INC_ATTRAPPL

#define OPTOKEN_APPLYATTRIB 			_T("ApplyAttribute")
#define OPTOKEN_APPLYATTRIBS 			_T("ApplyAttributes")
#define OPTOKEN_REPEATAPPLYATTRIB 		_T("RepeatApplyAttribute")
#define OPTOKEN_APPLYTONODE 			_T("ApplyAttributeToNode")
#define OPTOKEN_REPLACEATTRS 			_T("ReplaceAttributes")
#define OPTOKEN_APPLYATTRINTERACTIVE	_T("ApplyAttributeInteractive")


class AttrBrushType;
//class AttrFillGeometry;

/********************************************************************************************

>	class OpApplyAttrib : public SelOperation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/1/95
	Purpose:	Virtual base class for ops that apply attibutes.

********************************************************************************************/

class CCAPI OpApplyAttrib: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpApplyAttrib )    

public:
	virtual CCRuntimeClass* GetValueChangeType();
	virtual BOOL IsMergeableApplyOp();
	virtual void SetMergeable(BOOL bNewState) {MergeRepeats = bNewState;}

	// DMc
	// fn which tests the PromoteAttributeApplicationToMe of all compound nodes above the given node
	static NodeRenderableInk * FindCompoundNodeWhichRequiresAttribute(NodeRenderableInk * pStartNode,
																	CCRuntimeClass *pAttribClass);

	NodeAttribute * GetAttributeToApply() { return m_pAttr; }
	static BOOL KeepExistingCharacteristics(AttrFillGeometry*, AttrFillGeometry*);	// Should be member of AttrFillGeometry

	static BOOL DoApplyToSelection(SelOperation* pOp, NodeAttribute* Attrib, BOOL bMutate, BOOL bOptimise);

protected:
	BOOL DoInvalidateRegions(Range* NodeRange, 
							NodeAttribute* Attrib, 
							BOOL Mutate,
							NodeAttribute* OtherAttr,
							BOOL OtherMutate);

	CCRuntimeClass* ValueChangeType;
	BOOL MergeRepeats;

	// attribute to apply
	NodeAttribute * m_pAttr;
};




/********************************************************************************************

>	class OpApplyAttribToSelected: public OpApplyAttrib

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the OpApplyAttribToSelected operation.
				It applies the specified attribute to all selected objects

********************************************************************************************/

class CCAPI OpApplyAttribToSelected: public OpApplyAttrib
{

	CC_DECLARE_DYNCREATE( OpApplyAttribToSelected )    

public:
	OpApplyAttribToSelected();
	static BOOL		Init();	
	static OpState	GetState(String_256*, OpDescriptor*);		
	void DoWithParam(OpDescriptor* OpDesc, OpParam* pOpParam);	
	virtual void GetOpName(String_256* OpName); // Overloaded so that we can store the undo string in 
												// the operation rather than the OpDescriptor. 

protected:
	BOOL ApplyToSelection(NodeAttribute* Attrib, BOOL Mutate);
	UINT32 UndoAttribStrID; 	// Undo string resource ID

};




/********************************************************************************************

>	class OpApplyAttrInteractive: public OpApplyAttrib

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/08/2005
	Purpose:	-

********************************************************************************************/

class CCAPI OpApplyAttrInteractive: public OpApplyAttrib
{
	CC_DECLARE_DYNCREATE(OpApplyAttrInteractive)

public:
	OpApplyAttrInteractive();
	static BOOL		Init();
	static OpState	GetState(String_256*, OpDescriptor*);
	virtual void	GetOpName(String_256* OpName);

	virtual void	DragFinished(DocCoord PointerPos,
								 ClickModifiers ClickMods,
								 Spread* pSpread,
								 BOOL Success,
								 BOOL bSolidDrag);

	virtual BOOL	DoDragAttr(AttrValueChange* pNewValue);
	virtual BOOL	DragAttrChanged(AttrValueChange* pNewValue);
	virtual BOOL	DragAttrFinished(AttrValueChange* pNewValue, BOOL bSuccess = TRUE);
	virtual void	PerformMergeProcessing();

private:
	UINT32			m_UndoAttribStrID; 	// Undo string resource ID
	List			m_AttrGroupList;
	AttrTypeSet		m_AttrTypes;
};




/********************************************************************************************

>	class ApplyAttribsToSelectedParam : public OpParam

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95
	Purpose:	Parameters for the OpApplyAttribsToSelected operation. See 	
				OpApplyAttribsToSelected::DoWithParam for a description.

	SeeAlso:	OpApplyAttribsToSelected
	SeeAlso:	OpParam


********************************************************************************************/


class ApplyAttribsToSelectedParam: public OpParam
{
	CC_DECLARE_MEMDUMP( ApplyAttribsToSelectedParam )    

public:
 	ApplyAttribsToSelectedParam(List* attribsToApply,
 								UINT32 undoAttribStrID,  
								List* attrGroupList, 	
								BOOL* success, 
								BOOL* anyAttrsApplied)
		{ AttribsToApply = attribsToApply; 
		  UndoAttribStrID = undoAttribStrID;	
		  AttrGroupList = attrGroupList;  
		  Success = success; 
		  AnyAttrsApplied = anyAttrsApplied;}; 
								 			
	List* AttribsToApply;
	List* AttrGroupList;
	UINT32 UndoAttribStrID;  // The name of the operation used for undo (eg. Paste Attributes)
	BOOL* Success;		   // Has the operation actually failed
	BOOL* AnyAttrsApplied; // Have any attributes been applied by the op. (Has it done anything?)
}; 

/********************************************************************************************

>	class OpApplyAttribsToSelected: public OpApplyAttrib

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/10/95
	Purpose:	This class represents the OpApplyAttribsToSelected operation.
				It applies the specified set of attributes to all selected objects
	SeeAlso:	ApplyAttribsToSelectedParam

********************************************************************************************/

class CCAPI OpApplyAttribsToSelected: public OpApplyAttrib
{         
	CC_DECLARE_DYNCREATE( OpApplyAttribsToSelected )    

public:
	OpApplyAttribsToSelected();
	static BOOL		Init();	
	static OpState	GetState(String_256*, OpDescriptor*);		
	void DoWithParam(OpDescriptor* OpDesc, OpParam* pOpParam);	
	virtual void GetOpName(String_256* OpName); // Overloaded so that we can store the undo string in 
												// the operation rather than the OpDescriptor.

	List * GetAttributeList() { return m_pAttribList; }

protected:
	UINT32 UndoAttribStrID; 					// Undo string resource ID 
	List *m_pAttribList;
};


/********************************************************************************************

>	class OpRepeatApplyAttribToSelected: public OpApplyAttrib

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/3/95
	Purpose:	This class represents the OpApplyAttribToSelected operation.
				It applies the specified attribute to all selected objects

********************************************************************************************/

class CCAPI OpRepeatApplyAttribToSelected: public Operation
{         

	CC_DECLARE_DYNCREATE( OpRepeatApplyAttribToSelected )    

public:
	OpRepeatApplyAttribToSelected();
	static BOOL		Init();	
	static OpState	GetState(String_256*, OpDescriptor*);		
	void DoWithParam(OpDescriptor* OpDesc, OpParam* pOpParam);	
	virtual void GetOpName(String_256* OpName); // Overloaded so that we can store the undo string in 
												// the operation rather than the OpDescriptor.  
public:
	// Fill blob selection state, for operation merge code
	static FillBlobSelectionState FillBlobState;

protected:
	BOOL ApplyToSelection(NodeAttribute* Attrib, BOOL Mutate);		   
	virtual BOOL DoApply(Node* CurrentNode, NodeAttribute* Attrib, BOOL Mutate, BOOL bEffectRootOnly);
};

/********************************************************************************************

>	class OpApplyAttribToNode: public OpApplyAttrib

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/1/95
	Purpose:	This class represents the OpApplyAttribsToSelected operation.
				It applies the attribute to a specified object

********************************************************************************************/

class CCAPI OpApplyAttribToNode: public OpApplyAttrib
{         

	CC_DECLARE_DYNCREATE( OpApplyAttribToNode )    

public:
	OpApplyAttribToNode();
	static BOOL		Init();	
	static OpState	GetState(String_256*, OpDescriptor*);		
	void DoWithParam(OpDescriptor* OpDesc, OpParam* pOpParam);	
	virtual void GetOpName(String_256* OpName); // Overloaded so that we can store the undo string in 
												// the operation rather than the OpDescriptor.  
private:
	BOOL DoApplyAttrib(NodeRenderableInk* InkNode, 
					   NodeAttribute* NewAttr, 
					   AttrTypeSet* pAttrTypesToBeApplied, 
					   ObjectSet* pLocalisedCompounds,
					   BOOL InvalidateBounds=FALSE);		   

	UINT32 UndoAttribStrID; 	// Undo string resource ID 
};

/********************************************************************************************

>	class OpReplaceAttributes: public SelOperation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/1/95
	Purpose:	This class represents the OpReplaceAttributes operation.
				It replaces specific attributes with a new one.

********************************************************************************************/

class CCAPI OpReplaceAttributes: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpReplaceAttributes )    

public:
	OpReplaceAttributes();
	static BOOL		Init();	
	static OpState	GetState(String_256*, OpDescriptor*);		
	void DoWithParam(OpDescriptor* OpDesc, OpParam* pOpParam);	
	virtual void GetOpName(String_256* OpName); // Overloaded so that we can store the undo string in 
												// the operation rather than the OpDescriptor.  

	// DMc - we need to get the attribute change 
	NodeAttribute * GetAttribute() { return m_pAttr; }

private:
	BOOL DoReplace(NodeAttribute* NewAttr, NodeAttribute* OldAttr);
	UINT32 UndoAttribStrID; 	// Undo string resource ID 
	NodeAttribute * m_pAttr;
};


/********************************************************************************************

>	class ReplaceAttributesParam : public OpParam

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/01/2005
	Purpose:	The parameter for the OpReplaceAttributes operation

********************************************************************************************/
class ReplaceAttributesParam : public OpParam
{
	CC_DECLARE_DYNCREATE(ReplaceAttributesParam)

public:
	ReplaceAttributesParam() {m_pAttr = NULL; m_pOldAttrs = NULL;}

	ReplaceAttributesParam(NodeAttribute* pAttrib, List* pOldAttrs)
	{
		m_pAttr = pAttrib;
		m_pOldAttrs = pOldAttrs;
	}

	NodeAttribute* m_pAttr;
	List* m_pOldAttrs;
};



#endif

