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
// Declaration of NodeClipView.
//

#ifndef INC_NODECLIP
#define INC_NODECLIP

//#include "node.h"			// derivation from NodeRenderableInk. - in camtypes.h [AUTOMATICALLY REMOVED]
#include "clipattr.h"		// for our ClipRegionAttribute member.

/********************************************************************************************

>	class NodeClipView : public NodeRenderableInk

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10 February 2000
	Purpose:	ClipView node.
				This node works in tandem with NodeClipViewController to provide clipview 
				functionality. It sits underneath a NodeClipViewController, between the 
				keyhole node and the clipped nodes, so that it is rendered after the keyhole 
				node. Its Render() method saves GDraw's current clipping region and applies a 
				new region, derived from the keyhole node's outline.
	See also:	

********************************************************************************************/
class NodeClipView : public NodeRenderableInk
{
// Give my name out in memory dumps.
CC_DECLARE_DYNCREATE(NodeClipView);

// we don't mind NodeClipViewController accessing our protected methods.
friend class NodeClipViewController;
//friend class ClipRegionAttribute;

public:
	// construction/destruction and initialisation.
	NodeClipView();
	NodeClipView(	Node* pContextNode,  
					AttachNodeDirection Direction,
					BOOL Locked		= FALSE,
					BOOL Mangled	= FALSE,
					BOOL Marked		= FALSE,
					BOOL Selected	= FALSE );
	~NodeClipView();

	// virtual ID function.
	virtual BOOL IsANodeClipView() const { return TRUE; }

	// bounding information.
	virtual DocRect GetBoundingRect(BOOL DontUseAttrs = FALSE, BOOL HitTest = FALSE);
	virtual DocRect GetBlobBoundingRect();

	// render this node.
	virtual SubtreeRenderState RenderSubtree(RenderRegion* pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);
	virtual void Render(RenderRegion* pRender);
	void RenderClipAttr(RenderRegion* pRender);
	virtual void RenderEorDrag( RenderRegion* pRender );

	// we don't want to ever have any children, so we reject all attributes out of hand.
	virtual BOOL RequiresAttrib(CCRuntimeClass * , BOOL )		{ return FALSE; }
	virtual BOOL RequiresAttrib(NodeAttribute * , BOOL )		{ return FALSE; }
	virtual BOOL CanAttrBeAppliedToMe(CCRuntimeClass* AttrType)	{ return FALSE; }

	// return a description, for use in menus, infobar etc.
	virtual String Describe(BOOL Plural, BOOL Verbose);

	// get the size of this node.
	virtual UINT32 GetNodeSize() const;

	// transform this node.
	void Transform(TransformBase &Trans);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	// called on nodes after a document is imported.
	virtual BOOL PostImport();

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// ClipView-specific methods.
	//

	// set GDraw'c clipping region to, and restore it back over, the path of our keyhole node.
	void SetGDrawClippingRegion(RenderRegion* pRender);
	BOOL RestoreGDrawClippingRegion(BOOL fFirstInRenderLoop = FALSE);

	// this allows our NCVC to give us a path to clip to.
	void SetClipPath(Path* pClipPath) { m_ClipRegionAttribute.SetClipPath(pClipPath); }

	// copy methods. (Q: is there a reason why CopyNodeContents() is not virtual?)
	// Phil 19/12/2003 A: Yes. Because it takes a typed input parameter
	//						However, I have just added PolyCopyNodeContents which takes a NodeRenderable*
	virtual Node* SimpleCopy();
	void CopyNodeContents(NodeClipView* pNodeCopy);

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Member variables
//

private:
	BOOL				m_bRenderingForward;
	BYTE *				m_pRegion;
	GCONTEXT *			m_pContext;
	CONST REGION *		m_pSavedRegion;
	BOOL				m_bGDrawClipRegionSet;
	RECT				m_SavedClipRect;

private:
	ClipRegionAttribute		m_ClipRegionAttribute;

};



#endif	// INC_NODECLIP
