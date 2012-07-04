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


#ifndef NODEPOSTPRO_H
#define NODEPOSTPRO_H

//#include "ink.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "nodecomp.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CCAttrMap;

#define POSTPRO_ID_SHADOW				TEXT("Camelot/Internal/Shadow")
#define POSTPRO_DISPLAYNAME_SHADOW		TEXT("Shadow")
#define POSTPRO_ISDESTRUCTIVE_SHADOW	FALSE

#define POSTPRO_ID_FEATHER				TEXT("Camelot/Internal/Feather")
#define POSTPRO_DISPLAYNAME_FEATHER		TEXT("Feather")
#define POSTPRO_ISDESTRUCTIVE_FEATHER	FALSE


/***********************************************************************************************

>	class NodeEffect : public NodeCompound

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/09/2004
	Purpose:	Encapsulates everything to do with post processor nodes
				PostProcessor nodes are compound nodes which take the rendered output of their
				children and change it in some way.
				They are compound nodes so that they have a user-controlled position in the
				rendering order.

***********************************************************************************************/

class NodeEffect : public NodeCompound
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(NodeEffect);

public:
	NodeEffect();
	~NodeEffect();

	NodeEffect(Node* ContextNode,
				AttachNodeDirection Direction,
				BOOL Locked = FALSE,
				BOOL Mangled = FALSE,
				BOOL Marked = FALSE,
				BOOL Selected = FALSE
			  );

// Overrides
	virtual SubtreeRenderState	RenderSubtree(RenderRegion* pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);
	virtual void				RenderAfterSubtree(RenderRegion* pRender);
	virtual Node*				SimpleCopy();  
	virtual void				PolyCopyNodeContents(NodeRenderable* pNodeCopy);
	virtual BOOL				IsEffect() const {return TRUE;}
	virtual BOOL				IsController() {return TRUE;}

//	virtual BOOL				IsValidEffectAttr(CCRuntimeClass* pAttrClass) const;
	virtual BOOL				IsValidEffectAttr(NodeAttribute* pAttr) const;

// Specialist functions
	virtual BOOL				IsLockedEffect() {return FALSE;}
	virtual BOOL				CompareState(NodeEffect* pPPNode) {return FALSE;}
	virtual String_256			GetPostProcessorID() const {return m_strPostProID;}
	virtual void				SetPostProcessorID(String_256 strNewID) {m_strPostProID = strNewID;}
	virtual BOOL				IsFeatherEffect() {return FALSE;}
	virtual BOOL				IsPassThroughEffect() const {return FALSE;}	// User can NOT see original object through effects by default
	virtual BOOL				CanBeUnlocked() const {return TRUE;}

	void						CopyNodeContents(NodeEffect* pCopyOfNode);

protected:
	String_256					m_strPostProID;				// The unique ID of this XPE effect

};



#endif	// NODEPOSTPRO_H
