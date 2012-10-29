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
// Declaration of ClipRegionAttribute.
//

#ifndef INC_CLIPATTR
#define INC_CLIPATTR

//#include "clipres.h"

/********************************************************************************************

>	class ClipRegionAttribute : public AttributeValue

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Purpose:	

	See also:	

********************************************************************************************/
class ClipRegionAttribute : public AttributeValue
{
// Runtime class information.
CC_DECLARE_DYNCREATE(ClipRegionAttribute)

public:
	// construction/destruction
	ClipRegionAttribute();
	~ClipRegionAttribute();

	// methods required for AttributeValue implementation
	virtual void Render(RenderRegion* pRender, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion* pRender, BOOL Temp);
	virtual void GoingOutOfScope(RenderRegion* pRender);
	virtual void SimpleCopy(AttributeValue* pSource);
	virtual NodeAttribute* MakeNode();
	virtual BOOL IsDifferent(AttributeValue* pOther);

	// static initialisation function, to register this attribute with Camelot.
	static BOOL Init();

	// member access functions.
	Path*	GetClipPath() const { return m_pClipPath; }
	void	SetClipPath(Path* pClipPath) { m_pClipPath = pClipPath; }

//	not really sure what this is for...
//	virtual INT32 operator=(AttributeValue& Attrib) { return TRUE; }

	void	SetResponsibleForGrouping  (BOOL starts) { m_bResponsibleForGrouping = starts; }
	BOOL	IsResponsibleForGrouping () { return m_bResponsibleForGrouping; }

// member variables.
private:
	// the path which this attribute should cause output to be clipped to.
	Path*	m_pClipPath;
	BOOL	m_bResponsibleForGrouping;
};

class AttrClipView : public NodeAttribute
{
CC_DECLARE_DYNAMIC(AttrClipView)

public:
	AttrClipView();
	~AttrClipView();
	AttrClipView(Node* ContextNode,  
				 AttachNodeDirection Direction,    
				 BOOL Locked=FALSE, 
				 BOOL Mangled=FALSE,  
				 BOOL Marked=FALSE, 
				 BOOL Selected=FALSE);

	// Traditional Node functionality
	virtual void Render( RenderRegion* pRender );

#ifdef _DEBUG
	void GetDebugDetails(StringBase* Str);
#endif

	// Traditional NodeAttribute functionality
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	Node* SimpleCopy();
	virtual UINT32 GetAttrNameID() { return _R(IDS_CLIPVIEW_ATTR_ID); }
	virtual AttrIndex GetAttributeIndex () { return ATTR_CLIPVIEW; }
	virtual UINT32 GetNodeSize() { return sizeof(AttrClipView); }
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);

	// Node charateristics tests
	virtual BOOL NeedsTransparency() const { return FALSE; }

	// prevent feathering in incompatible circumstances
	virtual SubtreeRenderState RenderSubtree(RenderRegion *pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE) {return SUBTREE_ROOTONLY; }
	virtual BOOL IsAClipViewAttr() const { return TRUE; }

	// support layering and remove redundant attrs
	virtual BOOL CanBeMultiplyApplied()	{ return TRUE; }
	virtual BOOL ShouldBeOptimized() { return FALSE; }

	// dynamic attribute functions and flags
	virtual void Transform(TransformBase& Trans);
	virtual BOOL Blend(BlendAttrParam* pBlendParam);
	virtual BOOL ContainsAttributeValue(AttributeValue* pVal);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	// New Function local to this attribute only!
	// It`s mainly used for turning the attribute off when exporting AI EPS
	void EnableRendering(BOOL DoEnableRendering = TRUE) { m_DoRender = DoEnableRendering; }
	
	// Small function which lets the caller find out if the attribute is disabled or not.
	BOOL GetRenderStatus() { return m_DoRender; }

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

private:
	void CopyNodeContents(NodeAttribute *pCopy);
	BOOL m_DoRender;

public:
	ClipRegionAttribute Value;
};


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



#endif	// INC_CLIPATTR
