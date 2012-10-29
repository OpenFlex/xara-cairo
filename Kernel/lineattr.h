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


// Line Attribute definitions

#ifndef INC_LINEATTR
#define INC_LINEATTR

#include "fillattr2.h"

class BlendAttrParam;
class BaseCamelotFilter;

/*Remember:: (Bodge)

The NodeSize fns for those attributes which contain pointers will need changing 
when we have decided what their format is to be. 

Same for the operator== fns


Simon
*/


/***********************************************************************************************

>	class AttrLineWidth : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/6/93
	Purpose:	Line Width Attribute class.

***********************************************************************************************/

class AttrLineWidth : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrLineWidth)

public:
	AttrLineWidth(); 
	AttrLineWidth(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void); 

	void ShowDebugTreeDetails() const;			// Debugging function

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void Transform( TransformBase& );
	virtual BOOL EffectsParentBounds() { return TRUE; }

	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrLineWidth); }
	virtual AttrIndex GetAttributeIndex () { return ATTR_LINEWIDTH; }

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	virtual NodeAttribute* GetOtherAttrToApply(BOOL* IsMutate);
	virtual BOOL OtherAttrIsAppliedSelectively() const { return TRUE; }
	virtual BOOL IsALineWidthAttr() const;
	virtual BOOL NeedsToRenderAtEachBrushStroke() const;

private:
	void CopyNodeContents( AttrLineWidth* NodeCopy );

public:
	LineWidthAttribute Value;
};

/********************************************************************************************

>	class AttrStrokeColour : public AttrFillGeometry

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/6/94
	Purpose:	Stroke Colour Attribute class.

********************************************************************************************/

class AttrStrokeColour : public AttrFillGeometry
{
	CC_DECLARE_DYNCREATE(AttrStrokeColour)
	
public:
	AttrStrokeColour(); 
	AttrStrokeColour(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void);

	virtual DocRect GetBlobBoundingRect() { return DocRect(0,0,0,0); }
	virtual BOOL EffectsParentBounds();

	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrStrokeColour); }
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual AttrIndex GetAttributeIndex () { return ATTR_STROKECOLOUR; }

	virtual AttrFillGeometry* ChangeAttrValue(AttrValueChange*);

	virtual BOOL IsAStrokeColour() const { return TRUE; } 

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
	virtual BOOL WriteColourDefinitions (BaseCamelotFilter* pFilter);


#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

private:
	void CopyNodeContents( AttrStrokeColour* NodeCopy );

public:
	StrokeColourAttribute Value;
};

/********************************************************************************************

>	class AttrStrokeTransp : public AttrFillGeometry

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/94
	Purpose:	Stroke Transparency Attribute class.

********************************************************************************************/

class AttrStrokeTransp : public AttrFillGeometry
{
	CC_DECLARE_DYNCREATE(AttrStrokeTransp)
	
public:
	AttrStrokeTransp(); 
	AttrStrokeTransp(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void);

	virtual DocRect GetBlobBoundingRect() { return DocRect(0,0,0,0); }

	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrStrokeTransp); }
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual AttrIndex GetAttributeIndex () { return ATTR_STROKETRANSP; }

	virtual AttrFillGeometry* ChangeAttrValue(AttrValueChange*);

	virtual BOOL IsAStrokeTransp() const { return TRUE; }

#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	// Wasn't present before 19/11/97 Neville
	virtual BOOL NeedsTransparency() const;

private:
	void CopyNodeContents( AttrStrokeTransp* NodeCopy );

public:
	StrokeTranspAttribute Value;
};

/***********************************************************************************************

>	class AttrStrokeColourChange : public AttrValueChange

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/8/94
	Purpose:	Change Stroke colour Attribute class.
				This Attribute never exists in the Tree.  It is used for changing the colours
				of an existing Stroke.
	SeeAlso:	AttrFillGeometry

***********************************************************************************************/

class AttrStrokeColourChange : public AttrValueChange
{
	CC_DECLARE_DYNCREATE(AttrStrokeColourChange)
	
public:
	//AttrStrokeColourChange() : AttrValueChange() {}

	AttrStrokeColourChange(BOOL bLineWidth=FALSE) : AttrValueChange() { m_bLineWidth = bLineWidth;}

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrStrokeColour); }

	virtual AttrFillGeometry* MutateFill(AttrFillGeometry* FillToMutate);

	// This routine returns any secondary attribute that needs to be changed,
	// when this attribute is changed.
	virtual NodeAttribute* GetOtherAttrToApply(BOOL* IsMutate);

	virtual UINT32 GetAttrNameID(void);

	virtual BOOL EffectsParentBounds();

protected:
	StrokeColourAttribute Value;

private:
	// Olivier 17/03/97
	// This boolean is used with the line width.
	// When "none" is selected in the line width combo-box, 
	// it will display "Undo line width change" rather than 
	// "Undo line colour change" in the undo list.
	BOOL m_bLineWidth;
};

/***********************************************************************************************

>	class AttrStrokeTranspChange : public AttrValueChange

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/8/94
	Purpose:	Change Stroke transparency Attribute class.
				This Attribute never exists in the Tree.  It is used for changing the transp
				of an existing Stroke.
	SeeAlso:	AttrFillGeometry

***********************************************************************************************/

class AttrStrokeTranspChange : public AttrValueChange
{
	CC_DECLARE_DYNCREATE(AttrStrokeTranspChange)
	
public:
	AttrStrokeTranspChange() : AttrValueChange() {}

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrStrokeTransp); }

	virtual AttrFillGeometry* MutateFill(AttrFillGeometry* FillToMutate);

	virtual UINT32 GetAttrNameID(void);

protected:
	StrokeTranspAttribute Value;
};

/***********************************************************************************************

>	class AttrStrokeTranspTypeChange : public AttrValueChange

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/8/94
	Purpose:	Change Stroke transparency Attribute class.
				This Attribute never exists in the Tree.  It is used for changing the transp
				of an existing Stroke.
	SeeAlso:	AttrFillGeometry

***********************************************************************************************/

class AttrStrokeTranspTypeChange : public AttrValueChange
{
	CC_DECLARE_DYNCREATE(AttrStrokeTranspTypeChange)
	
public:
	AttrStrokeTranspTypeChange() : AttrValueChange() {}

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrStrokeTransp); }

	virtual AttrFillGeometry* MutateFill(AttrFillGeometry* FillToMutate);

	virtual UINT32 GetAttrNameID(void);

protected:
	StrokeTranspAttribute Value;
};

/***********************************************************************************************

>	class AttrStartArrow : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/93
	Purpose:	Start Arrow Attribute class.
	SeeAlso:	ArrowRec

***********************************************************************************************/

class AttrStartArrow : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrStartArrow)
	
public:
	
	AttrStartArrow(); 
	AttrStartArrow(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	virtual BOOL EffectsParentBounds();
	virtual DocRect GetAttrBoundingRect(NodeRenderableInk* pParent = NULL, CCAttrMap* pAttribMap = NULL);

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrStartArrow); }
	virtual AttrIndex GetAttributeIndex () { return ATTR_STARTARROW; }

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);
	virtual UINT32 GetAttrNameID(void); 


#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif
	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents( AttrStartArrow* NodeCopy );

public:
	StartArrowAttribute Value;
};

/***********************************************************************************************

>	class AttrEndArrow : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/93
	Purpose:	End Arrow Attribute class.
	SeeAlso:	ArrowRec

***********************************************************************************************/

class AttrEndArrow : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrEndArrow)
	
public:
	AttrEndArrow(); 
	AttrEndArrow(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	virtual BOOL EffectsParentBounds();
	virtual DocRect GetAttrBoundingRect(NodeRenderableInk* pParent = NULL, CCAttrMap* pAttribMap = NULL);

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrEndArrow); }
	virtual AttrIndex GetAttributeIndex () { return ATTR_ENDARROW; }

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);
	virtual UINT32 GetAttrNameID(void); 


#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif
	void GetDebugDetails(StringBase* Str);
    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents( AttrEndArrow* NodeCopy );

public:
	EndArrowAttribute Value;
};

/***********************************************************************************************

>	class AttrStartCap : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/93
	Purpose:	Start Cap Attribute class.
	SeeAlso:	LineCapType

***********************************************************************************************/

class AttrStartCap : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrStartCap)
	
public:
	AttrStartCap(); 
	AttrStartCap(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);
	virtual UINT32 GetAttrNameID(void); 

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrStartCap); }
	virtual AttrIndex GetAttributeIndex () { return ATTR_STARTCAP; }

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual BOOL EffectsParentBounds() { return TRUE; }

#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif
	void GetDebugDetails(StringBase* Str);

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents( AttrStartCap* NodeCopy );

public:
	StartCapAttribute Value;
};

/***********************************************************************************************

>	class AttrJoinType : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/93
	Purpose:	JoinType Attribute class.
	SeeAlso:	JointType

***********************************************************************************************/

class AttrJoinType : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrJoinType)
	
public:
	AttrJoinType(); 
	AttrJoinType(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void);

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrJoinType); }
	virtual AttrIndex GetAttributeIndex () { return ATTR_JOINTYPE; }

	virtual BOOL EffectsParentBounds() { return TRUE; }

#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif
	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents( AttrJoinType* NodeCopy );

public:
	JoinTypeAttribute Value;
};

/***********************************************************************************************

>	class AttrMitreLimit : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/93
	Purpose:	Mitre Limit Attribute class.

***********************************************************************************************/

class AttrMitreLimit : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrMitreLimit)
	
public:
	AttrMitreLimit(); 
	AttrMitreLimit(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);
	virtual UINT32 GetAttrNameID(void); 

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrMitreLimit); }
	virtual AttrIndex GetAttributeIndex () { return ATTR_MITRELIMIT; }

	virtual BOOL EffectsParentBounds() { return TRUE; }

#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif
	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents( AttrMitreLimit* NodeCopy );

public:
	MitreLimitAttribute Value;
};

/***********************************************************************************************

>	class AttrWindingRule : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/93
	Purpose:	Winding Rule Attribute class.
	SeeAlso:	WindingType

***********************************************************************************************/

class AttrWindingRule : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrWindingRule)
	
public:
	AttrWindingRule(); 
	AttrWindingRule(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void);

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrWindingRule); }
	virtual AttrIndex GetAttributeIndex () { return ATTR_WINDINGRULE; }

#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif
	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents( AttrWindingRule* NodeCopy );

public:
	WindingRuleAttribute Value;
};

/***********************************************************************************************

>	class AttrDashPattern : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/93
	Purpose:	Dash Pattern Attribute class.
	SeeAlso:	DashRec

***********************************************************************************************/

class AttrDashPattern : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrDashPattern)
	
public:
	AttrDashPattern(); 
	AttrDashPattern(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void);

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrDashPattern); }

	virtual AttrIndex GetAttributeIndex () { return ATTR_DASHPATTERN; }

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

#ifdef _DEBUG
	void ShowDebugTreeDetails() const;			// Debugging function
#endif
	void GetDebugDetails(StringBase* Str);

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents( AttrDashPattern* NodeCopy );

public:
	DashPatternAttribute Value;
};

#endif


