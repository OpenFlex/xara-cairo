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


// Bevel Attribute definitions

#ifndef INC_BEVELATTR
#define INC_BEVELATTR


class BevelAttributePathProcessor;

/********************************************************************************************

>	class BevelAttributeValueIndent : public AttributeValue

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Sets the indent attribute
	SeeAlso:	

********************************************************************************************/

class BevelAttributeValueIndent : public AttributeValue
{
	CC_DECLARE_DYNCREATE(BevelAttributeValueIndent)
public:
	BevelAttributeValueIndent();
	BevelAttributeValueIndent(INT32 val) { m_Indent = val; }
	virtual void Restore(RenderRegion *, BOOL);
	virtual void Render(RenderRegion *, BOOL Temp = FALSE);
	virtual NodeAttribute *MakeNode();
	BOOL IsDifferent(AttributeValue *pAttr);
	virtual void SimpleCopy(AttributeValue *);
	
	static BOOL Init();

public:
	// the value
	INT32 m_Indent;

	
};

/********************************************************************************************

>	class AttrBevel : public NodeAttribute

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Base class for bevel attributes
	SeeAlso:	
	Nodes:		Does nothing really but allow IsKindOf to pick up on bevel attributes

********************************************************************************************/
class AttrBevel : public NodeAttribute
{
CC_DECLARE_DYNCREATE(AttrBevel)
public:
	AttrBevel();
	AttrBevel(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 
} ;

/***********************************************************************************************

>	class AttrBevelIndent : public AttrBevel

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Bevel indent attribute

***********************************************************************************************/

class AttrBevelIndent : public AttrBevel
{
	CC_DECLARE_DYNCREATE(AttrBevelIndent)

public:
	AttrBevelIndent(); 
	AttrBevelIndent(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrBevelIndent); }
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual AttrIndex GetAttributeIndex () { return ATTR_BEVELINDENT; }

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void); 

	void ShowDebugTreeDetails() const;			// Debugging function

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void Transform( TransformBase& );
	virtual BOOL EffectsParentBounds() { return TRUE; }

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	void SetValue(INT32 NewValue) { Value.m_Indent = NewValue; }

	BOOL Blend(BlendAttrParam* pBlendParam);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

private:
	void CopyNodeContents( AttrBevelIndent* NodeCopy );

public:
	BevelAttributeValueIndent Value;
};

/********************************************************************************************

>	class BevelAttributeValueLightAngle : public AttributeValue

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Sets the indent attribute
	SeeAlso:	

********************************************************************************************/

class BevelAttributeValueLightAngle : public AttributeValue
{
	CC_DECLARE_DYNCREATE(BevelAttributeValueLightAngle)
public:
	BevelAttributeValueLightAngle();
	BevelAttributeValueLightAngle(INT32 val) { m_LightAngle = val; }
	virtual void Restore(RenderRegion *, BOOL);
	virtual void Render(RenderRegion *, BOOL Temp = FALSE);
	virtual NodeAttribute *MakeNode();
	BOOL IsDifferent(AttributeValue *pAttr);
	virtual void SimpleCopy(AttributeValue *);

	static BOOL Init();

public:
	// the value
	INT32 m_LightAngle;
};

/***********************************************************************************************

>	class AttrBevelLightAngle : public AttrBevel

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Bevel indent attribute

***********************************************************************************************/

class AttrBevelLightAngle : public AttrBevel
{
	CC_DECLARE_DYNCREATE(AttrBevelLightAngle)

public:
	AttrBevelLightAngle(); 
	AttrBevelLightAngle(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrBevelLightAngle); }
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual AttrIndex GetAttributeIndex () { return ATTR_BEVELLIGHTANGLE; }

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void); 

	void ShowDebugTreeDetails() const;			// Debugging function

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void Transform( TransformBase& );
	virtual BOOL EffectsParentBounds() { return FALSE; }

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	void SetValue(INT32 NewValue) { Value.m_LightAngle = NewValue; }

	BOOL Blend(BlendAttrParam* pBlendParam);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

private:
	void CopyNodeContents( AttrBevelLightAngle* NodeCopy );

public:
	BevelAttributeValueLightAngle Value;
};

/********************************************************************************************

>	class BevelAttributeValueContrast : public AttributeValue

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Sets the indent attribute
	SeeAlso:	

********************************************************************************************/

class BevelAttributeValueContrast : public AttributeValue
{
	CC_DECLARE_DYNCREATE(BevelAttributeValueContrast)
public:
	BevelAttributeValueContrast();
	BevelAttributeValueContrast(INT32 val) { m_Contrast = val; }
	virtual void Restore(RenderRegion *, BOOL);
	virtual void Render(RenderRegion *, BOOL Temp = FALSE);
	virtual NodeAttribute *MakeNode();
	BOOL IsDifferent(AttributeValue *pAttr);
	virtual void SimpleCopy(AttributeValue *);

	static BOOL Init();

public:
	// the value
	INT32 m_Contrast;
};

/***********************************************************************************************

>	class AttrBevelContrast : public AttrBevel

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Bevel indent attribute

***********************************************************************************************/

class AttrBevelContrast : public AttrBevel
{
	CC_DECLARE_DYNCREATE(AttrBevelContrast)

public:
	AttrBevelContrast(); 
	AttrBevelContrast(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrBevelContrast); }
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual AttrIndex GetAttributeIndex () { return ATTR_BEVELCONTRAST; }

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void); 

	void ShowDebugTreeDetails() const;			// Debugging function

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void Transform( TransformBase& );
	virtual BOOL EffectsParentBounds() { return FALSE; }

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	void SetValue(INT32 NewValue) { Value.m_Contrast = NewValue; }

	BOOL Blend(BlendAttrParam* pBlendParam);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

private:
	void CopyNodeContents( AttrBevelContrast* NodeCopy );

public:
	BevelAttributeValueContrast Value;
};

/********************************************************************************************

>	class BevelAttributeValueType : public AttributeValue

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Sets the indent attribute
	SeeAlso:	

********************************************************************************************/

class BevelAttributeValueType : public AttributeValue
{
	CC_DECLARE_DYNCREATE(BevelAttributeValueType)
public:
	BevelAttributeValueType();
	~BevelAttributeValueType();
	BevelAttributeValueType(INT32 val);
	virtual void Restore(RenderRegion *, BOOL);
	virtual void Render(RenderRegion *, BOOL Temp = FALSE);
	virtual NodeAttribute *MakeNode();
	virtual NodeAttribute *MakeNode(Node * pNode, AttachNodeDirection Direction);
	BOOL IsDifferent(AttributeValue *pAttr);
	virtual void SimpleCopy(AttributeValue *);
	INT32 operator=(AttributeValue& Attrib);
	INT32 operator==(AttributeValue& Attrib);

	// enables it to pop the path processor
	void GoingOutOfScope(RenderRegion * pRegion);

	static BOOL Init();

	void SetPassbackValue(BOOL b) { m_bPassback = b; }

public:
	// the value
	INT32 m_Type;

	// enables this node in the becomea/passback mechanism
	BOOL m_bPassback;

	// if we enable the passback mechanism, then we MUST hold copies
	// of the other attribute's values - this is because when GoingOutOfScope
	// is called on me, the other attributes could have already been replaced on the
	// stack
	void SetIndent(MILLIPOINT Indent) { m_Indent = Indent; }
	void SetLightAngle(double LightAngle) { m_LightAngle = LightAngle; }
	void SetContrast(INT32 Contrast)	{ m_Contrast = Contrast; }

	MILLIPOINT GetIndent() { return m_Indent; }
	double GetLightAngle() { return m_LightAngle; }
	INT32 GetContrast()	   { return m_Contrast; }

private:
	MILLIPOINT	m_Indent;
	double		m_LightAngle;
	INT32		m_Contrast;

private:
	BevelAttributePathProcessor * m_pProc;

	// creates the bevel bitmap out of the path processor, and the render region's
	// context stack
	KernelBitmap * CreateBevelBitmap(RenderRegion * pRegion);

	// renders the given bitmap
	BOOL RenderBitmap(RenderRegion * pRegion, KernelBitmap * pBitmap,
						Path * pSrcPath, Path * pRenderPath);
};

/***********************************************************************************************

>	class AttrBevelType : public AttrBevel

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Bevel indent attribute

***********************************************************************************************/

class AttrBevelType : public AttrBevel
{
	CC_DECLARE_DYNCREATE(AttrBevelType)

public:
	AttrBevelType(); 
	AttrBevelType(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void); 

	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrBevelType); }
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual AttrIndex GetAttributeIndex () { return ATTR_BEVELTYPE; }

	void ShowDebugTreeDetails() const;			// Debugging function

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void Transform( TransformBase& );
	
	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	void SetValue(INT32 NewValue) { Value.m_Type = NewValue; }

	// the blend function for this value
	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	virtual BOOL EffectsParentBounds() { return Value.m_bPassback; }
	DocRect GetAttrBoundingRect(NodeRenderableInk* pParent = NULL, CCAttrMap* pAttribMap = NULL);

	virtual BOOL CanBecomeA(BecomeA* pBecomeA);
	virtual BOOL DoBecomeA(BecomeA* pBecomeA);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

private:
	void CopyNodeContents( AttrBevelType* NodeCopy );

public:
	BevelAttributeValueType Value;
};

/********************************************************************************************

>	class BevelAttributeValueLightTilt : public AttributeValue

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Sets the indent attribute
	SeeAlso:	

********************************************************************************************/

class BevelAttributeValueLightTilt : public AttributeValue
{
	CC_DECLARE_DYNCREATE(BevelAttributeValueLightTilt)
public:
	BevelAttributeValueLightTilt();
	BevelAttributeValueLightTilt(INT32 val) { m_LightTilt = val; }
	virtual void Restore(RenderRegion *, BOOL);
	virtual void Render(RenderRegion *, BOOL Temp = FALSE);
	virtual NodeAttribute *MakeNode();
	BOOL IsDifferent(AttributeValue *pAttr);
	virtual void SimpleCopy(AttributeValue *);

	static BOOL Init();

public:
	// the value
	INT32 m_LightTilt;
};

/***********************************************************************************************

>	class AttrBevelLightTilt : public AttrBevel

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/98
	Purpose:	Bevel indent attribute

***********************************************************************************************/

class AttrBevelLightTilt : public AttrBevel
{
	CC_DECLARE_DYNCREATE(AttrBevelLightTilt)

public:
	AttrBevelLightTilt(); 
	AttrBevelLightTilt(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 

	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrBevelLightTilt); }
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual AttrIndex GetAttributeIndex () { return ATTR_BEVELLIGHTTILT; }

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void); 

	void ShowDebugTreeDetails() const;			// Debugging function

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void Transform( TransformBase& );
	virtual BOOL EffectsParentBounds() { return FALSE; }

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	void SetValue(INT32 NewValue) { Value.m_LightTilt = NewValue; }

	BOOL Blend(BlendAttrParam* pBlendParam);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

private:
	void CopyNodeContents( AttrBevelLightTilt* NodeCopy );

public:
	BevelAttributeValueLightTilt Value;
};

#endif
