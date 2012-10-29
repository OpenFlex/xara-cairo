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


// Nodebrush class

#ifndef INC_NODEBRSH
#define INC_NODEBRSH


class NodeBrushMaker;
class NodeBrushPath;



/********************************************************************************************

>	class NodeBrush: public NodeGroup

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/10/99
	Purpose:	The NodeBrush class

********************************************************************************************/

class NodeBrush: public NodeGroup
{
	// Give my name out in memory dumps
	CC_DECLARE_DYNCREATE(NodeBrush);

public:
	NodeBrush();
	NodeBrush(Node* ContextNode,  
			  AttachNodeDirection Direction,    
			  BOOL Locked=FALSE, 
			  BOOL Mangled=FALSE,  
			  BOOL Marked=FALSE, 
			  BOOL Selected=FALSE    
		     ); 
	
	~NodeBrush();

	// get the bounding rect 
	virtual DocRect GetBoundingRect(BOOL DontUseAttrs = FALSE, BOOL HitTest = FALSE);
	virtual DocRect GetBlobBoundingRect();

	// the main render function
	virtual void Render(RenderRegion* pRender);
	virtual SubtreeRenderState RenderSubtree(RenderRegion* pRender, Node** ppNextNode, BOOL bClip = TRUE);

	// blob rendering
	void RenderObjectBlobs(RenderRegion* pRender);
	void RenderTinyBlobs(RenderRegion* pRender);

	//  require transparency ?
//	virtual BOOL NeedsTransparency() const;


	virtual String Describe(BOOL Plural, BOOL Verbose = TRUE);

	// transformation function
	virtual void Transform( TransformBase& Trans ); 


	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
	
	virtual Node* 	HasEditableChild(CCRuntimeClass *ChildClass, Node* pPrevEditable);

		// Fuctions that allows ops and other nodes to inform this node of events on it's children
	virtual ChangeCode 	OnChildChange(ObjChangeParam* pParam);
	virtual BOOL 		AllowOp(ObjChangeParam* pParam,BOOL SetOpPermissionState = TRUE);
	
	
	
	// access functions
	NodeBrushPath* GetNodeBrushPath();
	void SetNodeBrushPath(NodeBrushPath * pPath);
	NodeBrushMaker* GetNodeBrushMaker();
	void SetNodeBrushMaker(NodeBrushMaker* pMaker);
	MILLIPOINT GetBrushSpacing();
	void SetBrushSpacing(MILLIPOINT Value);

	NodeRenderableInk* GetInkNode();
	BOOL ResetBrushPath();
	BOOL ReInitialiseInk();
	
	BOOL ChangeNodeBrushPath(NodeBrushPath* pNewPath);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

//	virtual BOOL IsValidEffectAttr(CCRuntimeClass* pAttrClass) const {return FALSE;}
	virtual BOOL IsValidEffectAttr(NodeAttribute* pAttr) const {return FALSE;}
	virtual BOOL GroupCanTransformCached(TransformBase& Trans) const {return FALSE;}

protected:
// return a copy of this node
	virtual Node* SimpleCopy();

	void CopyNodeContents(NodeBrush* pCopyOfNode);

	String_32 m_BrushName;
	NodeBrushPath* m_pNodeBrushPath;
	NodeBrushMaker* m_pNodeBrushMaker;
private:
	
	
	
};

#endif
