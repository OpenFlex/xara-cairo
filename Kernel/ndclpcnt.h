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
// Declaration of NodeClipViewController.
//

#ifndef INC_NDCLPCNT
#define INC_NDCLPCNT


#include "opclip.h"		// for reference to OpApplyClipView

class NodeClipView;
class ExtendParams;
class CXaraFileRecord;

/********************************************************************************************

>	class NodeClipViewController : public NodeGroup

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/01/2000
	Purpose:	ClipView controller node.
				This is the node which does all the hard work with respect to clipview 
				functionality. Initially at least, it is really a more-or-less normal group, 
				with special rendering qualities. The bottom-most (in a z-order sense) 
				NodeRenderableInk in the group is rendered, then its path is used to create a 
				clipping region, into which all other members of the group are rendered.

	Notes:		This is how you create a ClipView group in the tree:

					1.	Set up the tree structure (ignoring attributes):

							NCVC
							 |
							 |--{ Keyhole }--{ NCV }--{ Clipped Node N1 }--{ N2 }-- - etc.

					2.	Call the NCVC's UpdateKeyholePath() method.
						This method should really be public, but is not, to emphasize that
						you shouldn't just call it from anywhere, as it also marks the cached
						keyhole path as valid. To invalidate the cache (you shouldn't usually
						need to), you must call MarkKeyholeValid(), or if you need update on
						undo/redo, invoke an UpdateCachedKeyholePathAction.

					3.	Call the NCVC's InvalidateBoundingRect() method.
	See also:	

********************************************************************************************/
class NodeClipViewController : public NodeGroup
{
// Give my name out in memory dumps.
CC_DECLARE_DYNCREATE(NodeClipViewController);

// methods and classes which need to be able to invoke UpdateKeyholePath().
friend class NodeClipView;
friend void OpApplyClipView::Do(OpDescriptor* pOpDesc);
friend class UpdateCachedKeyholePathAction;

public:
	// construction/destruction and initialisation.
	NodeClipViewController();
	NodeClipViewController(	Node* pContextNode,
							AttachNodeDirection Direction,
							BOOL Locked		= FALSE,
							BOOL Mangled	= FALSE,
							BOOL Marked		= FALSE,
							BOOL Selected	= FALSE );
	~NodeClipViewController();

	// debug-tree details - only required in non-release builds.
	virtual void GetDebugDetails(StringBase* pStr);

	// virtual ID function.
	virtual BOOL IsANodeClipViewController() const { return TRUE; }

	// bounding information.
	virtual DocRect GetBoundingRect(BOOL DontUseAttrs = FALSE, BOOL HitTest = FALSE);
	virtual DocRect GetBlobBoundingRect();
	virtual DocRect GetEorDragBoundingRect();

	// render this node.
	virtual SubtreeRenderState RenderSubtree(RenderRegion* pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);
	virtual void RenderEorDrag( RenderRegion* pRender );
	virtual void RenderEorDragSelectedChildren(Node* pParent, RenderRegion* pRender);
	virtual BOOL ChildrenAreEorDragRenderedByMe();

	// our blob-rendering methods.
	virtual void RenderTinyBlobs(RenderRegion* pRender);
	virtual void RenderToolObjectBlobs(RenderRegion* pRender);

	// Virtual rendering functions	 (added 8th November 2000 - ChrisG)    
	virtual void PreExportRender( RenderRegion* pRender ); 
	virtual BOOL ExportRender( RenderRegion* pRender ); 

protected:
	virtual void RenderClipViewBlobs(RenderRegion* pRegion);

public:
	// deals with mouse clicks on this node.
	virtual BOOL OnClick(	DocCoord dcClickPos, ClickType cType,
							ClickModifiers cMods, Spread* pSpread );
protected:
	// handlers for the various types of clicks which a NodeClipViewController can receive.
	virtual BOOL HandleKeyholeBlobClick(ClickType cType);
	virtual BOOL HandleContentsBlobClick(ClickType cType);

public:
	// used to convert to paths - see mkshapes.cpp.
	virtual BOOL CanBecomeA(BecomeA* pBecomeA);
	virtual BOOL DoBecomeA(BecomeA* pBecomeA);
	virtual NodeGroup* BecomeAGroup(UndoableOperation* pUndoOp);
	virtual BOOL GroupCanTransformCached(TransformBase& Trans) const {return TRUE;}

private:
	// helper methods for DoBecomeA.
	BOOL KeyholeDoBecomeA(BecomeA* pBecomeA);
	BOOL MakeShapeAndLine(NodePath* pNodePath, BecomeA* pBecomeA, BOOL bClipToKeyhole);
	BOOL InsertClippedNode(	NodePath* pNewNode, NodePath* pDestNode,
							AttachNodeDirection Direction,
							UndoableOperation* pUndoOp,
							BOOL bClipToKeyhole );
	BOOL PassBackClippedNode(NodePath* pNewNode, BecomeA* pBecomeA, BOOL bClipToKeyhole);
	BOOL InkHasClearLineColour(NodeRenderableInk* pInkNode);
	BOOL RemoveInkLineWidth(NodeRenderableInk* pInk);
	BOOL CopyInkFillColourFromLine(NodeRenderableInk* pInk);
	BOOL CopyInkTransparencyFromLine(NodeRenderableInk* pInk);

	// methods for keeping our cached keyhole path up to date.
	// please only use these inline validation methods to set/check keyhole validity.
	BOOL UpdateKeyholePath();
	BOOL IsKeyholeValid()	  const { return m_fKeyholeValid; }
	void MarkKeyholeValid()		{ m_fKeyholeValid = TRUE;  }
	void MarkKeyholeInvalid()	{ m_fKeyholeValid = FALSE; }

public:
	// return the required path flatness for ClipView groups.
	static INT32 EstimatePathFlatness();

	// AllowOp / OnChildChange function pair.
	// Called on this node in response to any operation which may affect the node.
	virtual BOOL AllowOp(ObjChangeParam *pParam, BOOL SetOpPermissionState = TRUE,
												 BOOL DoPreTriggerEdit = TRUE);
	virtual ChangeCode OnChildChange(ObjChangeParam* pParam);

	// return a description, for use in menus, infobar etc.
	virtual String Describe(BOOL Plural, BOOL Verbose);
	virtual UINT32 GetNodeSize() const;

	// transform this node.
	void Transform(TransformBase &Trans);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	// called on nodes after a document is imported.
	virtual BOOL PostImport();

	// whether this node is a controller node or not.
	// AFAIK this method is used solely by OpEditBlendEndObject for update,
	// when moving one of the end-objects of a blend-ona-path which lies within
	// a controller structure. Strikes me as a tad silly...
	virtual BOOL IsController() { return TRUE; }

	// retrieves this node's associated NodeClipView child.
	// returns NULL if there is no associated NodeClipView.
	NodeClipView* GetClipView(BOOL ReportErrors = TRUE);


	// get a pointer to the cached InkPath of this node's keyhole.
	Path* GetKeyholePath() { return &m_KeyholePath; }

	// test whether a particular ink-node is a keyhole node for this NCVC.
	BOOL OwnsAsKeyholeNode(const Node* pTestNode);

	// some constants we require for half-decent path clipping.
	static const INT32 CLIPVIEW_TOLERANCE;
	static const INT32 CLIPVIEW_SOURCEFLATNESS;
	static const INT32 CLIPVIEW_CLIPFLATNESS;

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	// copy methods. (Q: is there a reason why CopyNodeContents() is not virtual?)
	// Phil 19/12/2003 A: Yes. Because it takes a typed input parameter
	//						However, I have just added PolyCopyNodeContents which takes a NodeRenderable*
	virtual Node* SimpleCopy();
	void CopyNodeContents(NodeClipViewController* pNodeCopy);

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Member variables
//

private:
	// our cached keyhole path, and whether it is valid or not.
	Path m_KeyholePath;
	BOOL m_fKeyholeValid;

	// the bounding rectangles of our ClipView-group blobs.
	DocRect	m_drKeyholeBlobRect;
	DocRect m_drContentsBlobRect;
};



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



/********************************************************************************************

>	class ClipViewRecordHandler : public CamelotRecordHandler

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/01/2000
	Purpose:	Handles the reading of all ClipView records.
	See also:	

********************************************************************************************/
class ClipViewRecordHandler : public CamelotRecordHandler
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(ClipViewRecordHandler)

public:
	// functions that must be implemented.
	ClipViewRecordHandler();
	~ClipViewRecordHandler();
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);
};



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



/********************************************************************************************

>	class UpdateCachedKeyholePathAction : public Action

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Purpose:	Cause a NodeClipViewController node to update it cached keyhole path when
				an operation is undone or redone.
	Notes:		Invoking this action via its Init() method has no _direct_ effect, save to
				set the action to trigger on undo/redo.

********************************************************************************************/
class UpdateCachedKeyholePathAction : public Action
{
// dynamic class creation.
CC_DECLARE_DYNCREATE(UpdateCachedKeyholePathAction)

public:
	// required Action methods.
	UpdateCachedKeyholePathAction();
	~UpdateCachedKeyholePathAction();
	static ActionCode Init(	UndoableOperation* pUndoOp,
							ActionList* pActionList,
							NodeClipViewController* pUpdateNCVC );
	virtual ActionCode Execute();

private:
	// initialise our own information.
	void SetNCVCToUpdate(NodeClipViewController* pNCVC);

	// member variables.
	NodeClipViewController* m_pNCVC;
};



#endif	// INC_NDCLPCNT

