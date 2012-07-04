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


#ifndef INC_USERATTR
#define INC_USERATTR

class BlendAttrParam;
class BaseCamelotFilter;
class Style;

/********************************************************************************************

>	class UserAttribute : public AttributeValue

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
					(Actually, it was more likely to be Graham, cos Tim quit a few months before)

	Created:	15/06/94
					(More like mid '96 if you ask me)

	Purpose:	Represent a line width of a path.  This may be a simple stroking operator
				such as a constant line width, or a complex one such as variable line
				widths or an airbrush stroke operator.
					(I'd say it stores a "key" string and an associated "value" string
					for implementation of URLs and other such stuff, but if you say it
					stores a line width, who am I to argue? ;-)

********************************************************************************************/

class UserAttribute : public AttributeValue
{
	CC_DECLARE_DYNCREATE(UserAttribute)
public:
	static BOOL Init();

	UserAttribute();
	UserAttribute& operator=(const UserAttribute& other);

	virtual void Restore(RenderRegion *, BOOL);
	virtual void Render(RenderRegion *, BOOL Temp = FALSE);
	virtual NodeAttribute *MakeNode();
	BOOL IsDifferent(AttributeValue *pAttr);
	virtual void SimpleCopy(AttributeValue *);

	// This blend the attribute value with the one provided by pBlendParam
	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	// Extra virtual function for stroke type attributes.
	virtual BOOL RenderStroke(RenderRegion *, Path *) { return FALSE; }

	StringBase	 Key;
	StringBase	 LongKey;
	StringBase	 Value;
	const Style* m_pStyle;		// used by StyleReferenceAttribute
};


/***********************************************************************************************

>	class AttrUser : public NodeAttribute

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/6/93

	Purpose:	User Attribute Node

***********************************************************************************************/

class AttrUser : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrUser)

public:
	AttrUser(); 
	AttrUser(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 
	AttrUser(const StringBase& NewKey, const StringBase& NewSubKey, const StringBase& NewValue);
	AttrUser(const StringBase& NewLongKey, const StringBase& NewValue);

	virtual void Render( RenderRegion* pRender );

	virtual Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void); 
	virtual BOOL IsUserAttribute() const		{ return TRUE; }

	void ShowDebugTreeDetails() const;			// Debugging function

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void Transform( TransformBase& );

	// Yes, user attributes can be applied more than once to the same object
	virtual BOOL CanBeMultiplyApplied()		{ return TRUE; }
	virtual BOOL ShouldBeOptimized();
	virtual BOOL EffectsParentBounds()		{ return TRUE; }

	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	virtual AttributeValue* GetAttributeValue() { return &Value; }
	virtual CCRuntimeClass* GetAttributeType() { return CC_RUNTIME_CLASS(AttrUser); }
	virtual AttributeIdentifier	GetAttributeClassID() const;
	virtual AttrIndex GetAttributeIndex () { return ATTR_USERATTRIBUTE; }

	virtual VisibleAttribute* CreateVisibleAttribute() const;

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	BOOL ShouldBecomeCurrent();

	StringBase& GetWebAddress();

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	void CopyNodeContents( AttrUser* NodeCopy );

	static const TCHAR s_KeyDelimiter;

public:
	UserAttribute Value;
};



#endif // INC_USERATTR
