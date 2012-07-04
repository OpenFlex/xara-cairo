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
// Implementation of ClipView operations.
//

#include "camtypes.h"		// pre-compiled header
#include "opclip.h"			// our header file
#include "ophist.h"
//#include "clipres.h"		// our resources
//#include "phil.h"			// for _R(IDS_GREY_WHEN_SELECT_INSIDE)

#include "ndclpcnt.h"		// so we can play around with NodeClipViewContainer
#include "nodeclip.h"		// so we can play around with NodeClipView
#include "nodepath.h"

// dynamic class creation stuff.
CC_IMPLEMENT_DYNCREATE(OpApplyClipView, SelOperation);
CC_IMPLEMENT_DYNCREATE(OpRemoveClipView, SelOperation);

DECLARE_SOURCE("$Revision: 1144 $");

#define new CAM_DEBUG_NEW


/********************************************************************************************

>	OpApplyClipView::OpApplyClipView()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Purpose:	Constructor.
	Errors:		
	See also:	

********************************************************************************************/
OpApplyClipView::OpApplyClipView()
{
	// empty.
}



/********************************************************************************************

>	OpApplyClipView::~OpApplyClipView()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Purpose:	Destructor.
	Errors:		
	See also:	

********************************************************************************************/
OpApplyClipView::~OpApplyClipView()
{
	// empty.
}



/********************************************************************************************

>	static BOOL OpApplyClipView::Init()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
BOOL OpApplyClipView::Init()
{
	return RegisterOpDescriptor(0,								// Tool ID
 								_R(IDS_APPLY_CLIPVIEW),				// String resource ID
								CC_RUNTIME_CLASS(OpApplyClipView),	// Runtime class
 								OPTOKEN_APPLY_CLIPVIEW,			// Token string
 								OpApplyClipView::GetState,		// GetState function
								0,								// Help ID
								_R(IDBBL_APPLY_CLIPVIEW),			// Bubble ID
								0,								// Resource ID
								0,								// Control ID
								SYSTEMBAR_ILLEGAL,				// Bar ID
								TRUE,							// Receive system messages
								FALSE,							// Smart duplicate operation
								FALSE,							// Clean operation
								0,								// No vertical counterpart
								GREY_WHEN_NO_CURRENT_DOC |
								DONT_GREY_WHEN_SELECT_INSIDE);	// automatic state checking.
}



/********************************************************************************************

>	static OpState OpApplyClipView::GetState(String_256* pstrDescription, OpDescriptor* pOpDesc)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
OpState OpApplyClipView::GetState(String_256* pstrDescription, OpDescriptor* pOpDesc)
{
	// default is an unticked, *GREYED*, on-menu state.
	OpState OpSt;
	OpSt.Greyed = TRUE;
	*pstrDescription = String_256(_R(IDS_CLIPVIEW_NEEDS_MULTIPLE_NODES));

	// obtain the app's current selection.
	// we want to treat bevels/contours etc. as atomic objects.
	Range Sel(*(GetApplication()->FindSelection()));
	RangeControl rc = Sel.GetRangeControlFlags();
	rc.PromoteToParent = TRUE;
	Sel.Range::SetRangeControl(rc);

	// is there actually anything in the selection?
	Node* pNode = Sel.FindFirst();
	if (pNode != NULL)
	{
		// yes - then is it only one node?
		if (Sel.FindNext(pNode) == NULL)
		{
			// yes - then if that node is a NodeClipViewController, remove ourself from the menu.
			if (pNode->IsANodeClipViewController())
			{
				OpSt.RemoveFromMenu = TRUE;
				pstrDescription->Empty();
			}
		}

		// two or more nodes - that's ok, but only if there is currently no select-inside.
		else if (Sel.ContainsSelectInside())
		{
			*pstrDescription = String_256(_R(IDS_GREY_WHEN_SELECT_INSIDE));
		}
		else
		{
			OpSt.Greyed = FALSE;
			pstrDescription->Empty();
		}
	}

	return OpSt;
}



/********************************************************************************************

>	virtual void OpApplyClipView::GetOpName(String_256* pstrOpName)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
void OpApplyClipView::GetOpName(String_256* pstrOpName)
{
	*pstrOpName = String_256("ClipView Object(s)");
}



/********************************************************************************************

>	virtual void OpApplyClipView::Do(OpDescriptor* pOpDesc, OpParam* pOpParam)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
void OpApplyClipView::Do(OpDescriptor* pOpDesc)
{
	// obtain the current selection.
	Range Sel(*(GetApplication()->FindSelection()));
	RangeControl rc = Sel.GetRangeControlFlags();
	rc.PromoteToParent = TRUE;
	Sel.Range::SetRangeControl(rc);

	// check that at least two nodes are selected.
	Node* pNode = NULL;
	Node* pFirstNode = Sel.FindFirst();
	if (pFirstNode != NULL)
		pNode = Sel.FindNext(pFirstNode);
		
	if (pFirstNode == NULL || pNode == NULL)
	{
		ERROR3("OpApplyClipView invoked with less than two selected nodes. This should never occur.");
		End();
		return;
	}

	// render blobs off for tools which don't automatically redraw their blobs.
	Tool* pTool = Tool::GetCurrent();
	Spread* pSpread = Document::GetSelectedSpread();
	if (pSpread != NULL && pTool != NULL && !pTool->AreToolBlobsRenderedOnSelection())
		pTool->RenderToolBlobs(pSpread, NULL);

	// record the current selection state and if required, render off any selection blobs.
	if (!DoStartSelOp(FALSE, FALSE))
	{
		End();
		return;
	}

	// invalidate the region bounding the selection.
	// the commented code doesn't do the job properly (doesn't tackle undo)
	// though it should - I get the feeling I'm not using it correctly.
	// so we'll just have to invalidate the selection node by node.
//	if (!DoInvalidateNodesRegions(Sel, TRUE, FALSE, FALSE))
//	{
//		End();
//		return;
//	}
	Node* pSelNode = Sel.FindFirst();
	while (pSelNode != NULL)
	{
		if (pSelNode->IsAnObject())
		{
			if (!DoInvalidateNodeRegion((NodeRenderableInk*)pSelNode, TRUE))
			{
				End();
				return;
			}
		}
		pSelNode = Sel.FindNext(pSelNode);
	}

	// we need to insert the controller node at the position of the highest
	// selected node in the z-order, ie last in the selection, so find it.
	Node* pLastNode = NULL;
	while (pNode != NULL)
	{
		pLastNode = pNode;
		pNode = Sel.FindNext(pLastNode);
	}	// loop terminates with pNode == NULL, pLastNode == last-node-in-sel.

	// create a new NodeClipViewController, which we will shortly insert into the tree;
	// note that ALLOC_WITH_FAIL automatically calls FailAndExecute() if things go wrong.
	NodeClipViewController* pClipViewController = NULL;
	ALLOC_WITH_FAIL(pClipViewController, new NodeClipViewController, this);
	BOOL ok = (pClipViewController != NULL);

	// put an action to hide the NodeClipViewController onto the undo action-list,
	// so that if the user presses undo then it will be hidden.
	if (ok)
	{
		HideNodeAction* pUndoHideNodeAction = NULL;
		ActionCode ac = HideNodeAction::Init(this,
											&UndoActions,
											pClipViewController,
											FALSE,		// don't include subtree size
											(Action**)&pUndoHideNodeAction,
											FALSE);		// don't tell subtree when undone
		if (ac == AC_FAIL)
		{
			delete pClipViewController;
			End();
			return;
		}
		else
		{
			// right! we've got our node, we've got our action - lets stick it in the tree
			// (at a position just next to the last node which will go in the group).
			pClipViewController->AttachNode(pLastNode, NEXT);
		}
	}

	// move each item from the selection into our ClipView group,
	// remembering to deselect them as we go.
	// TODO:
	//	sneaky suspicion I should be putting this in a Do fn in UndoableOperation...
	if (ok)
	{
		pNode = Sel.FindNext(pFirstNode);				// the node we're moving now.
		ok = DoMoveNode(pFirstNode, pClipViewController, FIRSTCHILD);
		if (ok)
			((NodeRenderable*)pFirstNode)->DeSelect(FALSE);
	}

	Node* pNextNode		= NULL;							// the next node to move.
	Node* pAnchorNode	= pFirstNode;					// the node we've just moved.
	while (ok && pNode != NULL)
	{
		// get the next node to move.
		pNextNode = Sel.FindNext(pNode);

		// now move the current node next to the anchor and deselect it.
		ok = DoMoveNode(pNode, pAnchorNode, NEXT);
		if (ok)
			((NodeRenderable*)pNode)->DeSelect(FALSE);

		// get the new anchor node and the next node to move.
		pAnchorNode = pNode;
		pNode = pNextNode;
	}

	// try and locate a suitable candidate for a keyhole node.
	Node* pKeyhole = NULL;
	if (ok)
	{
		// now get the keyhole node, which is the first object-node child of the NCVC.
		pKeyhole = pClipViewController->FindFirstChild();
		while (pKeyhole != NULL && !pKeyhole->IsAnObject())
		{
			pKeyhole = pKeyhole->FindNext();
		}

		// doh! can't find _one_ NodeRenderableInk child! I don't know...
		if (pKeyhole == NULL)
		{
			ok = FALSE;
			ERROR2RAW("ClipViewController has no object children");
		}
	}

	// now attach a new NodeClipView, as the immediate NEXT-sibling of the keyhole node.
	NodeClipView* pClipView = NULL;
	if (ok)
	{
		ALLOC_WITH_FAIL(pClipView, new NodeClipView(pKeyhole, NEXT), this);
		ok = (pClipView != NULL);
	}

	// wow - succeeded! now all we need to do is some house-keeping.
	if (ok)
	{
		// tell the new NodeClipViewController that its current keyhole path is now invalid.
		pClipViewController->MarkKeyholeInvalid();

		// invalidate ours and our parent's bounding rects. our bounding rect is almost
		// certainly already invalid, as we haven't done anything to make it valid yet.
		// this is why we invalidate *both* rects - just to cover all cases.
		pClipViewController->InvalidateBoundingRect();
		Node* pParent = pClipViewController->FindParent();
		if (pParent != NULL && pParent->IsBounded())
			((NodeRenderableBounded*)pParent)->InvalidateBoundingRect();

		// select the new NodeClipViewController, but don't draw any blobs yet.
		pClipViewController->Select(FALSE);

		// invalidate the region bounding the selection.
		if (!DoInvalidateNodesRegions(*(GetApplication()->FindSelection()), TRUE, FALSE, FALSE))
		{
			End();
			return;
		}

		// factor out any common attributes.
		if (!DoFactorOutCommonChildAttributes(pClipViewController))
		{
			End();
			return;
		}
		
		// render blobs back on if the current tool doesn't automatically redraw its blobs.
		if (pSpread != NULL && pTool != NULL && !pTool->AreToolBlobsRenderedOnSelection())
			pTool->RenderToolBlobs(pSpread, NULL);
	}
	else
	{
		FailAndExecute();
	}

	// end the operation.
 	End();
}



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



/********************************************************************************************

>	OpRemoveClipView::OpRemoveClipView()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Purpose:	Constructor.
	Errors:		
	See also:	

********************************************************************************************/
OpRemoveClipView::OpRemoveClipView()
{
	// empty.
}



/********************************************************************************************

>	OpRemoveClipView::~OpRemoveClipView()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Purpose:	Destructor.
	Errors:		
	See also:	

********************************************************************************************/
OpRemoveClipView::~OpRemoveClipView()
{
	// empty.
}



/********************************************************************************************

>	static BOOL OpRemoveClipView::Init()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
BOOL OpRemoveClipView::Init()
{
	return RegisterOpDescriptor(0,								// Tool ID
 								_R(IDS_REMOVE_CLIPVIEW),				// String resource ID
								CC_RUNTIME_CLASS(OpRemoveClipView),	// Runtime class
 								OPTOKEN_REMOVE_CLIPVIEW,			// Token string
 								OpRemoveClipView::GetState,		// GetState function
								0,								// Help ID
								_R(IDBBL_REMOVE_CLIPVIEW),			// Bubble ID
								0,								// Resource ID
								0,								// Control ID
								SYSTEMBAR_ILLEGAL,				// Bar ID
								TRUE,							// Receive system messages
								FALSE,							// Smart duplicate operation
								FALSE,							// Clean operation
								0,								// We can have many instances
																//			of this operation.
								DONT_GREY_WHEN_SELECT_INSIDE);	// We don't ever want to be
																// automatically greyed out.
}



/********************************************************************************************

>	static OpState OpRemoveClipView::GetState(String_256* pstrDescription, OpDescriptor* pOpDesc)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Inputs:		pstrDescription
				pOpDesc
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
OpState OpRemoveClipView::GetState(String_256* pstrDescription, OpDescriptor* pOpDesc)
{
	// default is an unticked, ungreyed, *NOT* on-menu state.
	OpState OpSt;
	OpSt.RemoveFromMenu = TRUE;

	// obtain the app's current selection.
	// we want to treat bevels/contours etc. as atomic objects.
	Range Sel(*(GetApplication()->FindSelection()));
	RangeControl rc = Sel.GetRangeControlFlags();
	rc.PromoteToParent = TRUE;
	Sel.Range::SetRangeControl(rc);

	// we only show ourself if the selection consists of one lone NodeClipViewController.
	Node* pNode = Sel.FindFirst();
	if (pNode != NULL && pNode->IsANodeClipViewController())
	{
		if (Sel.FindNext(pNode) == NULL)
		{
			OpSt.RemoveFromMenu = FALSE;

			// if it's selected inside, we gray ourself and give a reason.
			if (Sel.ContainsSelectInside())
			{
				OpSt.Greyed = TRUE;
				*pstrDescription = String_256(_R(IDS_GREY_WHEN_SELECT_INSIDE));
			}
		}
	}

	return OpSt;
}



/********************************************************************************************

>	virtual void OpRemoveClipView::GetOpName(String_256* pstrOpName)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
void OpRemoveClipView::GetOpName(String_256* pstrOpName)
{
	*pstrOpName = String_256("Remove ClipView");
}



/********************************************************************************************

>	virtual void OpRemoveClipView::Do(OpDescriptor* pOpDesc, OpParam* pOpParam)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
void OpRemoveClipView::Do(OpDescriptor* pOpDesc)
{
	// try to record the selection state.
	if (DoStartSelOp(FALSE, FALSE))
	{
		// obtain the current selection.
		Range Sel(*(GetApplication()->FindSelection()));
		RangeControl rc = Sel.GetRangeControlFlags();
		rc.PromoteToParent = TRUE;
		Sel.Range::SetRangeControl(rc);

		// check that the selection is one lone NodeClipViewController.
		BOOL ok = FALSE;
		Node* pFirstNode = Sel.FindFirst();
		if (pFirstNode != NULL && pFirstNode->IsANodeClipViewController())
			if (Sel.FindNext(pFirstNode) == NULL)
				ok = TRUE;

		// remove tool blobs and localise any common attributes.
		Tool* pTool = NULL;
		Spread* pSpread = NULL;
		if (ok)
		{
			// render blobs off for tools which don't automatically redraw their blobs.
			pTool = Tool::GetCurrent();
			pSpread = Document::GetSelectedSpread();
			if (pSpread != NULL && pTool != NULL && !pTool->AreToolBlobsRenderedOnSelection())
				pTool->RenderToolBlobs(pSpread, NULL);

			// invalidate the region of screen covering the selection.
			DoInvalidateNodesRegions(*(GetApplication()->FindSelection()), TRUE, FALSE, FALSE);

			// localise any common attributes.
			ok = DoLocaliseCommonAttributes((NodeGroup*)pFirstNode);
		}

		// deselect and hide the NCVC.
		NodeHidden* pHiddenNode = NULL;
		if (ok)
		{
			// deselect the NCVC, but don't ask for its blobs to be redrawn.
			((NodeRenderable*)pFirstNode)->DeSelect(FALSE);
			ERROR3IF(pFirstNode->IsSelected(), "Deselect failed to deselect current node");

			// hide the NodeClipViewController.
			ok = DoHideNode(pFirstNode, FALSE, &pHiddenNode, FALSE);
			ERROR3IF(!ok, "Unable to hide NodeClipViewController!");
		}

		// hide the NCVC's NodeClipView node.
		if (ok)
		{
			NodeHidden* pDummy;
			NodeClipView* pClipView = ((NodeClipViewController*)pFirstNode)->GetClipView();
			ok = DoHideNode(pClipView, FALSE, &pDummy, FALSE);
			ERROR3IF(!ok, "Unable to hide NodeClipView!");
		}

		// show and select the NCVC's children.
		// a straight loop-over should do, as it should skip the now-hidden NodeClipView.
		if (ok)
		{
			// get the first child node (the NCVC's keyhole node).
			Node* pChildNode = pFirstNode->FindFirstChild();
			if (pChildNode == NULL)
				TRACEUSER( "Karim", _T("OpRemoveClipView::Do(); Found an empty NodeClipViewController!\n"));

			// move and select the child nodes in turn.
			Node* pAnchorNode = pHiddenNode;
			Node* pNextChildNode = NULL;
			while (pChildNode != NULL)
			{
				// get the next child-node.
				pNextChildNode = pChildNode->FindNext();

				// if the node is not a NodeHidden then move the node to its new location in 
				// the tree - there is no need to render the node.
				if (!pChildNode->IsAnAttribute() && !pChildNode->IsNodeHidden())
				{
					// move pChildNode to be the next-sibling of the anchor node.
					ok = DoMoveNode(pChildNode, pAnchorNode, NEXT);
					if (!ok)
						break;

					pAnchorNode = pChildNode;
				}

				// select the child node and invalidate its bounding rect,
				// but don't bother redrawing its blobs yet.
				if (pChildNode->IsAnObject())
				{
					((NodeRenderableInk*)pChildNode)->Select(FALSE);
					((NodeRenderableInk*)pChildNode)->InvalidateBoundingRect();
					ok = this->DoInvalidateNodeRegion(((NodeRenderableInk*)pChildNode), TRUE);
					if (!ok)
						break;
				}

				pChildNode = pNextChildNode;
			}
		}

		// render blobs back on for tools which don't automatically redraw their blobs.
		if (ok)
		{
			if (pSpread != NULL && pTool != NULL && !pTool->AreToolBlobsRenderedOnSelection())
				pTool->RenderToolBlobs(pSpread, NULL);
		}

		// fail gracefully if things went pear-shaped.
		else
			FailAndExecute();
	}

	End();
}			



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------




