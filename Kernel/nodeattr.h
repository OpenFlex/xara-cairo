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


// The Node Attribute Class

#ifndef INC_NODEATTR
#define INC_NODEATTR

#include "node.h"

class DocColour;
class AttributeValue;
class BlendAttrParam;
class NodeRenderableInk;
class UndoableOperation;

// Graeme (21/3/00) - This list of attributes was originally in attrmgr.h. I've moved them
// here so that they can be used to identify attribute nodes directly.
typedef enum
{
	ATTR_BAD_ID 	= (UINT32)~1,
	ATTR_STROKECOLOUR = 0,
	ATTR_STROKETRANSP,
	ATTR_FILLGEOMETRY,
	ATTR_TRANSPFILLGEOMETRY,
	ATTR_FILLMAPPING,
	ATTR_TRANSPFILLMAPPING,
	ATTR_FILLEFFECT,
	ATTR_LINEWIDTH,
	ATTR_WINDINGRULE,
	ATTR_JOINTYPE,
	ATTR_QUALITY,
	ATTR_DASHPATTERN,
	ATTR_STARTCAP,
	ATTR_STARTARROW,
	ATTR_ENDARROW,
	ATTR_MITRELIMIT,
	ATTR_USERATTRIBUTE,
	ATTR_WEBADDRESS,
	ATTR_TXTFONTTYPEFACE,
	ATTR_TXTBOLD,
	ATTR_TXTITALIC,
	ATTR_TXTASPECTRATIO,
	ATTR_TXTJUSTIFICATION,
	ATTR_TXTTRACKING,
	ATTR_TXTUNDERLINE,
	ATTR_TXTFONTSIZE,
	ATTR_TXTSCRIPT,
	ATTR_TXTBASELINE,
	ATTR_TXTLINESPACE,
	ATTR_TXTLEFTMARGIN,
	ATTR_TXTRIGHTMARGIN,
	ATTR_TXTFIRSTINDENT,
	ATTR_TXTRULER,
	ATTR_OVERPRINTLINE,
	ATTR_OVERPRINTFILL,
	ATTR_PRINTONALLPLATES,
	ATTR_STROKETYPE,
	ATTR_VARWIDTH,
	ATTR_BEVELINDENT,
	ATTR_BEVELTYPE,
	ATTR_BEVELCONTRAST,
	ATTR_BEVELLIGHTANGLE,
	ATTR_BEVELLIGHTTILT,
	//ATTR_PAINTINGMODE,	// Bye bye painting mode!
	ATTR_BRUSHTYPE,
	ATTR_FEATHER,
	ATTR_CLIPREGION,
	ATTR_CLIPVIEW,

	ATTR_FIRST_FREE_ID,		// Put all new attributes above this line!

	ATTR_MOULD = 0,
	ATTR_ENDCAP = 0
} AttrIndex;

typedef const StringBase&	AttributeIdentifier;
class VisibleAttribute;
extern const String_8 NullString;
/***********************************************************************************************

>	class NodeAttribute : public NodeRenderable

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/6/93
	Purpose:	Abstract class from which various Attribute nodes are derived.

***********************************************************************************************/

class NodeAttribute : public NodeRenderable
{
	CC_DECLARE_DYNAMIC( NodeAttribute );   

public:
	NodeAttribute(); 
	NodeAttribute(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE);

	virtual void Render(RenderRegion* pRender) {};
	virtual SubtreeRenderState RenderSubtree(RenderRegion* pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);
	virtual BOOL NeedsToExport( RenderRegion* pRender, BOOL VisibleLayersOnly = FALSE,
								BOOL CheckSelected = FALSE );
	virtual Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual BOOL IsDifferent(Node *pOther);
	virtual UINT32 GetAttrNameID(void); 
	virtual DocColour *EnumerateColourFields(UINT32 Context);

	virtual CCRuntimeClass* GetAttributeType() { return GetRuntimeClass(); }
	virtual AttributeValue* GetAttributeValue() { return NULL; }
	virtual AttributeIdentifier	GetAttributeClassID() const		{	return NullString;	}
	virtual AttrIndex GetAttributeIndex () { return ATTR_BAD_ID; }
	virtual VisibleAttribute* CreateVisibleAttribute() const	{	return NULL;	}
	virtual BOOL CopyComponentData(BaseDocument* SrcDoc, BaseDocument* NodesDoc); 
	virtual BOOL Blend(BlendAttrParam* pBlendParam);
	virtual BOOL HasEquivalentDefaultValue(BOOL bAppearance = FALSE);

	// This routine returns any secondary attribute that needs to be changed,
	// when this attribute is changed.
	virtual NodeAttribute* GetOtherAttrToApply(BOOL* IsMutate) { return NULL; }

	// This vfn denotes whether the other attribute above will be applied selectively,
	// which prevents OpApplyAttribToSelected::ApplyToSelection() from blanket-applying
	// the other attribute to the selection.
	virtual BOOL OtherAttrIsAppliedSelectively() const { return FALSE; }

	virtual void OnMakeCurrent() {}

	// Routines to scan the tree in reverse render order returning attributes which are
	// "in scope" for a given node.
	static NodeAttribute* FindFirstAppliedAttr(Node* pContextNode, Node* pRoot = NULL);
	static NodeAttribute* FindPrevAppliedAttr(Node* pContextNode, Node* pRoot = NULL);

	virtual BOOL IsAnAttribute() const; 
	virtual BOOL IsOrHidesAnAttribute() const;
	virtual BOOL IsRenderedAsInk() const {return TRUE;}

	virtual BOOL IsAValueChange() const; 
	virtual BOOL IsAColourFill() const; 
	virtual BOOL IsATranspFill() const; 
	virtual BOOL IsAStrokeColour() const; 
	virtual BOOL IsAStrokeTransp() const; 

	virtual BOOL IsAFlatFill() const; 
	virtual BOOL IsAGradFill() const; 
	virtual BOOL IsABitmapFill() const; 
	virtual BOOL IsAFractalFill() const;
	virtual BOOL IsALineLevelAttrib() { return FALSE; }; // Is the attribute a text line level attribute
	virtual BOOL IsALineWidthAttr() const;
	virtual BOOL NeedsToRenderAtEachBrushStroke() const;

	// This virtual was added because attributes like the NodeAttrQuality can never be directly
	// applied to an object. 
	virtual BOOL CanBeAppliedToObject() { return TRUE; };

	// This virtual was primarily added to support triggers. If the attribute has exactly the same
	// value then it's not multiply applied. It might be bad if you select the attributes into 
	// render regions since they don't have the notion of multiple attrs of the same type.
	virtual BOOL CanBeMultiplyApplied() { return FALSE; }
	// Template/WizOp attributes need to remain with the objects they were attached to.
	// Hence they are not optimized, whereas the base class is.
	virtual BOOL ShouldBeOptimized()	{ return !IsEffectAttribute(); }

	// Effect Attributes live at different positions in the tree and so don't have
	// the same scope as normal attributes
	virtual BOOL IsEffectAttribute() const;

	BOOL IsADefaultAttr(); 
		// Simple but useful fn to determine if the attribute (which must be in the tree) is a default
  		// attribute

	virtual BOOL EffectsParentBounds();
	virtual DocRect GetAttrBoundingRect(NodeRenderableInk* pParent = NULL, CCAttrMap* pAttribMap = NULL);

	// virtual Transform fn which does nothing in the base class.
	virtual void TransformToNewBounds(DocRect& NewBounds) { return; } 

	virtual BOOL ShouldBecomeCurrent();

#ifdef _DEBUG
	virtual void ShowDebugTreeDetails() const;
#endif

protected:
	virtual void CopyNodeContents( NodeAttribute* NodeCopy );

public:
	// Starting from this attribute, returns the next attribute of the given type
	// that applies to the Node on which Node::FindFirstAttr was called, or null
	// if there isn't one.
	NodeAttribute* FindNextAttr(Node::TypeFunc pfnTest) const;

	// Ilan 27/4/00
	// New extensions to the attribute system - initially created to support feathering attribute

	// Determines whether dynamically created copies of the attribute need special post-copying update
	// Also means that it needs to receive object change messages from any child nodes within its scope
	virtual BOOL IsLinkedToNodeGeometry();
	virtual BOOL IsLinkedToThisNode(Node* pNode);

	// Attributes which are linked to node geometry, require the following additional
	// initialisation functions
	virtual BOOL PostDynCreateInit(CCAttrMap* pMap, Path* InkPath, CCRuntimeClass* pCreatorClass);
	virtual BOOL PostDynCreateInit(CCAttrMap* pMap, Node* pNode, CCRuntimeClass* pCreatorClass);
	virtual void PostDynCreateDeInit();

	// Lets the attribute know that the child objects have changed (nb see notes in definition)
	virtual BOOL LinkedNodeGeometryHasChanged(UndoableOperation* pOp);

	// When compound nodes are dynamically created inside blends to form one of the BlendRefs
	// it is necessary to supply 
	virtual BOOL LinkToGeometry(Node* pContext);
	// Called after a default attribute is created and attached to a NodeDocument
	// (ie when a new document is created)
	virtual void NewlyCreatedDefaultAttr(NodeDocument* pNode);

	// To determine if the NodeAttribute is the container (ie node in the tree) for the supplied AttributeValue
	virtual BOOL ContainsAttributeValue(AttributeValue* pVal);

	// Karim 15/11/2000
	// ID function for an attribute which diverts rendering offscreen, ie its AttributeValue is derived
	// from OffscreenAttrValue, eg AttrFeather.
	virtual BOOL IsAnOffscreenAttribute() { return FALSE; }

	// Allow attributes to supply additional paths into the BecomeA system
	// (E.g. special outline strokes)
//	virtual BOOL DoBecomeAdditionalPath(BecomeA* pBecomeA, NodePath* pNode, NodeRenderableInk* pCreatedByNode, CCAttrMap* pAttrMap) {return FALSE;}

// Karim 13/09/2000
// Virtual override of NodeRenderable::IsSeeThrough() - see base declaration for details.
public:
	virtual BOOL IsSeeThrough(BOOL CheckIndirectAttrs) { return FALSE; }
};

#endif
