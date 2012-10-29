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


#ifndef	INC_NODEBEVELCONTROLLER
#define	INC_NODEBEVELCONTROLLER

#ifdef BUILDSHADOWS

//#include "control.h"
#include "clipattr.h"

class ContextMenu;
class ExtendParams;
class BlendNodeParam;
class AttrClipView;
class NodeBevel;

/********************************************************************************************

>	class NodeBevelController : public NodeGroup

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/98
	Purpose:	

********************************************************************************************/

class NodeBevelController : public NodeGroup
{
	CC_DECLARE_DYNAMIC( NodeBevelController )    
public:
	NodeBevelController(); 
	NodeBevelController(Node* ContextNode,  
				AttachNodeDirection Direction,  
				BOOL Locked = FALSE, 
				BOOL Mangled = FALSE,  
				BOOL Marked = FALSE, 
				BOOL Selected = FALSE    
				) ;

	~NodeBevelController();

	NodeBevel * GetBevelNode();

	// creates the bevel immediately
	void CreateBevel();

	// copy this node
	virtual Node* SimpleCopy(); 
	void CopyNodeContents(NodeBevelController* pNewNode);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// PreRender functionality for inner bevel object clipping
	virtual void PreExportRender( RenderRegion* pRender ); 
	virtual SubtreeRenderState RenderSubtree(RenderRegion* pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);

	// Virtual rendering functions	     
	virtual BOOL ExportRender( RenderRegion* pRender ); 

	virtual void RenderTinyBlobs(RenderRegion* pRender);

	virtual void Render(RenderRegion* pRender);
	virtual BOOL HidingNode();
	virtual BOOL ShowingNode();

	// test to see if there is a bevel controller in the current selection
	static BOOL SelectionHasBevelNode();

	// test to see if there is a bevel inking node in the current selection
	static BOOL SelectionHasBevelInkNode();

	// get the n'th bevel node in the selection
	static NodeBevelController * GetSelectionBevelNode(INT32 num = 0);
	static NodeBevel * GetSelectionBevelInkNode(INT32 num = 0);

	virtual void Transform( TransformBase& Trans );
	
	DocRect GetBoundingRect(BOOL DontUseAttrs, BOOL HitTest);
	DocRect GetBlobBoundingRect();

	// Karim 14/04/2000 - helper method for marquee selection.
	virtual void SelectInRect(const DocRect& Rect, SelStateAction st);

	// file format stuff
	BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
	
	// same as native in this case
	BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);

	BOOL WritePostChildrenNative(BaseCamelotFilter* pFilter);
	BOOL WritePostChildrenWeb(BaseCamelotFilter* pFilter);

	BOOL LoadBevelFromRecord(CXaraFileRecord* pCXaraFileRecord);

	// change in child ?
	virtual ChangeCode 	OnChildChange(ObjChangeParam* pParam);

	virtual BOOL AllowOp(ObjChangeParam *pParam, BOOL SetOpPermissionState = TRUE,
												 BOOL DoPreTriggerEdit = TRUE);

		// we don't want to have brush attrs applied to us.
	virtual BOOL RequiresAttrib(CCRuntimeClass* pAttribClass, BOOL Search = FALSE);
	virtual BOOL RequiresAttrib(NodeAttribute* pAttr, BOOL Search = FALSE);
	virtual BOOL CanAttrBeAppliedToMe(CCRuntimeClass* pAttribClass);
	
	// have we finished importing yet ?
	BOOL PostImport();

	// tells the bevel node to delete it's data
	void DeleteCache();

	// this renders the light vector (used by the tool !)
	void RenderMyBlobs(RenderRegion * pRender);

	DocRect GetBlobRect() { return m_BlobDocRect; }

	virtual String Describe(BOOL Plural, BOOL Verbose); 

	virtual BOOL OnNodePopUp(Spread*, DocCoord, ContextMenu*);

	BOOL DoBecomeA(BecomeA* pBecomeA);
	BOOL CanBecomeA(BecomeA* pBecomeA);

	// hit testing on children isn't promoted
	BOOL PromoteHitTestOnChildrenToMe() const { return FALSE; }

	BOOL ShouldITransformWithChildren() const { return TRUE; }

	BOOL PostDuplicate(UndoableOperation* pOp);

	void RenderEorDrag(RenderRegion * pRegion);
	virtual BOOL ChildrenAreEorDragRenderedByMe() { return TRUE; }

	virtual BOOL NeedsTransparency() const {return TRUE;}

	// functions to render just the bevel bitmap
	void ReRenderBevelBitmap(double LightAngle);

	virtual NodeRenderableInk * CreateTreeFromNodeToBlend(NodeRenderableInk * pNode, 
		CCAttrMap * pAttrMap);

	// fns to tell this class to start & end blending
	virtual BOOL EndBlendStep(BlendNodeParam * pParam);

	virtual BOOL PromoteAttributeApplicationToMe(CCRuntimeClass *pAttrClass) const;

	BOOL AmDragging() { return m_bDrag; }

	BOOL RegenerateNode(UndoableOperation * pOp, BOOL bCacheRender = FALSE,
		BOOL bInformParents = TRUE);

	// just regenerates my bitmap
	BOOL RegenerateBevelBitmap(UndoableOperation * pOp, BOOL bInformParents = TRUE);

	INT32 ComplexHide(UndoableOperation* pOp, Node* pNextInRange);

	// Diccon added virtual identifier 9/99
	virtual BOOL IsController() { return TRUE;}
	virtual BOOL IsABevelController() const { return TRUE;}
	virtual BOOL GroupCanTransformCached(TransformBase& Trans) const {return Trans.IsTranslation();} //{return FALSE;}

	// retrieves the node that we end up bevelling
	virtual NodeRenderableInk* GetInkNodeFromController() const;

	// Karim MacDonald 25/11/1999
	// virtual Extend functions; see declaration/implementation in Node.
	virtual BOOL IsTypeExtendible() const { return TRUE; }
	virtual DocRect ValidateExtend(const ExtendParams& ExtParams);
	virtual void Extend(const ExtendParams& ExtParams);

	void GetDebugDetails(StringBase* Str);

public:
	// the data members for the bevel
	// public for easy access
	INT32 m_BevelType;
	INT32 m_Indent;
	LineCapType m_LType;

	double m_LightAngle;
	BOOL m_bOuter;
	INT32 m_Contrast;
	double m_Tilt;
	
	// boolean which tells GetBoundingRect to include the blobs
	BOOL m_bIncludeBlobsInBoundingRect;

	// points determining the fill control points
	DocCoord m_BMPCentre;
	DocCoord m_BMPPoint1;
	DocCoord m_BMPPoint2;

	// the rect of the (original) selection
	DocRect m_SelectedRect;

protected:
	void ApplyRelevantAttributes (CCAttrMap* ptrBevelMap, CCAttrMap* oldPathMap,
								  CCAttrMap* newPathMap, CCAttrMap* pMap,
								  CCAttrMap* pSingleMap);

	// PreRender Function of inner bevels
	BOOL PreApplyClipViewNode(RenderRegion* pRender);

protected:
	DocRect m_BlobDocRect;
	DocCoord m_BlobCentre;
	
	// indicates that a drag is in progress
	BOOL m_bDrag;

	BOOL m_HaveDoneApplyTest;

	// indicates that the last bounding rect passed back was for the tool
	// used to see if we need to re-generate the bounding rect 
	BOOL m_bBoundingRectIsForTool;

	FIXED16 m_LastZoom;

	BOOL m_PerformedExtend;

	BOOL m_LastColoursTransparency;

	// New ClipView Attribute for rendering Inner bevels
	AttrClipView* m_pClipViewAttribute;

	Path m_PathToClipVeiw;
	NodeBevel* m_pBevel;

	double m_LastClipZoom;

} ;

/***********************************************************************************************

>	class BevelNodeTreeFactory : public CompoundNodeTreeFactory

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/8/99
	Purpose:	Creates a new bevel node with the given parameters

***********************************************************************************************/
class BevelNodeTreeFactory : public CompoundNodeTreeFactory
{
	CC_DECLARE_DYNCREATE(BevelNodeTreeFactory);

public:
	// constructor which sets up the class factory to create nodes the same as given
	BevelNodeTreeFactory(NodeBevelController * pController);
	~BevelNodeTreeFactory();

	// given a list of NodeListItems, shadows them
	virtual NodeCompound * CreateNode(List *pList, UndoableOperation * pOp = NULL);

	void SetBevelType(INT32 Type)				{ m_BevelType = Type; }
	void SetBevelLightAngle(INT32 Angle)	{ m_BevelLightAngle = Angle; }
	void SetBevelIndent(INT32 Indent)			{ m_BevelIndent = Indent; }
	void SetBevelContrast(INT32 Contrast)		{ m_BevelContrast = Contrast; }

private:
	List m_ControllerAttributeList;
	List m_BevelNodeAttributeList;

	INT32 m_BevelType;
	INT32 m_BevelLightAngle;
	INT32 m_BevelIndent;
	INT32 m_BevelContrast;
} ;


#endif
#endif
