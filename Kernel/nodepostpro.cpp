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


/*
*/

#include "camtypes.h"
#include "nodepostpro.h"
#include "attrmap.h"

// Resource headers
//#include "resource.h"
//#include "mario.h"
#include "lineattr.h"

DECLARE_SOURCE( "$Revision: 1282 $" );

CC_IMPLEMENT_DYNCREATE(NodeEffect, NodeCompound)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/***********************************************************************************************

>	NodeEffect::NodeEffect(Node* 	ContextNode,
						AttachNodeDirection Direction,
						const DocRect& 		BoundingRect,
						BOOL				Locked = FALSE,
						BOOL 				Mangled = FALSE,
						BOOL 				Marked = FALSE,
						BOOL 				Selected = FALSE,
						BOOL 				Renderable = FALSE
						)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/09/2004
	Inputs:		ContextNode: Pointer to a node which this node is to be attached to.
				MonoOn Direction: MonoOff
				Specifies the direction in which the node is to be attached to the
				ContextNode. The values this variable can take are as follows:
								  
				PREV      : Attach node as a previous sibling of the context node
				NEXT      : Attach node as a next sibling of the context node
				FIRSTCHILD: Attach node as the first child of the context node
				LASTCHILD : Attach node as a last child of the context node

				BoundingRect: Bounding rectangle

				The remaining inputs specify the status of the node:
			
				Locked:     Is node locked ?
				Mangled:    Is node mangled ?
				Marked:     Is node marked ?
				Selected:   Is node selected ?

	Purpose:	This constructor initialises the nodes flags and links it to ContextNode in the
				direction specified by Direction. All neccesary tree links are updated.
	Note:		SetUpShape() must be called before the NodeRegularShape is in a state in which
				it can be used.
    SeeAlso:	NodeRegularShape::SetUpShape
    Errors:		An ENSURE will occur if ContextNode is NULL

***********************************************************************************************/
NodeEffect::NodeEffect(Node* ContextNode,  
					AttachNodeDirection Direction,  
					BOOL Locked, 
					BOOL Mangled,  
					BOOL Marked, 
					BOOL Selected    
			  ) : NodeCompound(ContextNode, Direction, Locked, Mangled, Marked, Selected )
{                         
	m_strPostProID = String(_T(""));
}                        
 
/*********************************************************************************************

>	NodeEffect::NodeEffect() 

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/09/2004
	Purpose:	
	Note:		
	SeeAlso:	

**********************************************************************************************/
NodeEffect::NodeEffect() : NodeCompound()
{
	m_strPostProID = String(_T(""));
}

/*********************************************************************************************

>	NodeEffect::~NodeEffect() 

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/09/2004
	Purpose:	Destructor
	Note:		
	SeeAlso:	

**********************************************************************************************/
NodeEffect::~NodeEffect()
{
}




/********************************************************************************************

>	SubtreeRenderState NodeEffect::RenderSubtree(RenderRegion* pRender, Node** ppNextNode, BOOL bClip)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/09/2004
	Inputs:		pRender - The region render into (or use as context for decisions about subtree)
				ppNextNode - Address of node pointer for next node to render or run to after this
				bClip - flag indicating whether to clip or not
	Purpose:	Do clever stuff on the way into a subtree, possibly modifying rendering
				behaviour.

********************************************************************************************/

SubtreeRenderState NodeEffect::RenderSubtree(RenderRegion* pRender, Node** ppNextNode, BOOL bClip)
{
	if (pRender == NULL)							// If no render region supplied, assume we need to be rendered
		return SUBTREE_ROOTANDCHILDREN;

	// Go find out about my bounding rectangle
	DocRect BoundingRect = GetBoundingRect();
	DocRect ClipRect = pRender->GetClipRect();

	if (bClip && !ClipRect.IsIntersectedWith(BoundingRect))	// If not within the clipping rect then
		return SUBTREE_NORENDER;					// Don't render us or our children

	// Ask Helper function to set up cacheing for me...
// AMB wonders whethere this was commented out during porting - 20051212
//	if (RenderCached(pRender))						// If we can find a cached bitmap for this node and render it
//	{
//		return SUBTREE_NORENDER;					// Then tell the renderer to move on without doing any more...
//	}

	return SUBTREE_ROOTANDCHILDREN;					// Else we must render ourselves and our children
}



/********************************************************************************************

>	void NodeEffect::RenderAfterSubtree(RenderRegion* pRender)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/09/2004
	Inputs:		pRender - The region to render into
	Purpose:	Capture the group as a cached bitmap

********************************************************************************************/

void NodeEffect::RenderAfterSubtree(RenderRegion* pRegion)
{
	// Deal with group transparency capture
	// Call Helper function to run all my cacheing functionality for me...
//	CaptureCached(pRegion);
}




/***********************************************************************************************
> Node* NodeEffect::SimpleCopy()  

    Author:     Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
    Created:    09/09/2004
	Inputs:     -  
    Outputs:    
    Returns:    A copy of the node, or NULL if memory has run out 
		 
    Purpose:    This method returns a shallow copy of the node with all Node pointers NULL. 
				The function is virtual, and must be defined for all derived classes.  
	            
	Errors:     If memory runs out when trying to copy, then ERROR is called with an out of memory
				error and the function returns NULL.                                                                      
                                                                                 
**********************************************************************************************/

Node* NodeEffect::SimpleCopy()
{
	NodeEffect* NodeCopy; 
	NodeCopy = new NodeEffect();
	ERRORIF(NodeCopy == NULL, _R(IDE_NOMORE_MEMORY), NULL); 
	CopyNodeContents(NodeCopy);   		
	return (NodeCopy);
}   



   
/***********************************************************************************************

>	void NodeEffect::CopyNodeContents(Node* pCopyOfNode)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/09/2004
	Inputs:		pCopyOfNode - The node to copy data to
	Outputs:	-
	Returns:	-
	Purpose:	Copies the data from this node to pCopyOfNode by first calling the base class to get it to
				copy its stuff, and then copying its own stuff
	Scope:		protected
	SeeAlso:	NodeGroup::CopyNodeContents

***********************************************************************************************/

void NodeEffect::CopyNodeContents(NodeEffect* pCopyOfNode)
{
	NodeCompound::CopyNodeContents(pCopyOfNode);

	// Copy member vars here
	pCopyOfNode->m_strPostProID = m_strPostProID;
}




/***********************************************************************************************
>   void NodeEffect::PolyCopyNodeContents(NodeRenderable* pNodeCopy)

    Author:     Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
    Created:    09/09/2004
    Outputs:    -
    Purpose:    Polymorphically copies the contents of this node to another
	Errors:     An assertion failure will occur if NodeCopy is NULL
    Scope:      protected
								     
***********************************************************************************************/

void NodeEffect::PolyCopyNodeContents(NodeRenderable* pNodeCopy)
{
	ENSURE(pNodeCopy, "Trying to copy a node's contents into a NULL node");
	ENSURE(IS_A(pNodeCopy, NodeEffect), "PolyCopyNodeContents given wrong dest node type");

	if (IS_A(pNodeCopy, NodeEffect))
		CopyNodeContents((NodeEffect*)pNodeCopy);
}




/********************************************************************************************

>	void NodeEffect::IsValidEffectAttr(CCRuntimeClass* pAttrClass) const

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/01/2005
	Inputs:		Attribute class
	Returns:	TRUE if the attr class is a valid effect attr
	Purpose:	Determine whether this type of attribute can be an effect attribute
				On this node at this time.

********************************************************************************************/

/*BOOL NodeEffect::IsValidEffectAttr(CCRuntimeClass* pAttrClass) const
{
	return (AttrFillGeometry::s_bGroupTransparency &&
			(pAttr->IsATranspFill() ||
			 pAttr->IsKindOf(CC_RUNTIME_CLASS(AttrTranspChange)) ||
			 pAttr->IsKindOf(CC_RUNTIME_CLASS(AttrStrokeTranspChange)
			 )
			);
}*/

	
	
	
/********************************************************************************************

>	void NodeEffect::IsValidEffectAttr(NodeAttribute* pAttr) const

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/01/2005
	Inputs:		Attribute
	Returns:	TRUE if the attr is a valid effect attr
	Purpose:	Determine whether this attribute instance can be an effect attribute
				On this node at this time.

********************************************************************************************/

BOOL NodeEffect::IsValidEffectAttr(NodeAttribute* pAttr) const
{
	CCRuntimeClass* pAttrType = pAttr->GetAttributeType();

	return (pAttr->IsATranspFill() ||
			pAttrType == CC_RUNTIME_CLASS(AttrTranspFillGeometry) || //->IsKindOf(CC_RUNTIME_CLASS(AttrTranspChange)) ||
			pAttrType == CC_RUNTIME_CLASS(AttrStrokeTransp) || //pAttr->IsKindOf(CC_RUNTIME_CLASS(AttrStrokeTranspChange)) ||
			pAttrType == CC_RUNTIME_CLASS(AttrTranspFillMapping)
			);
}




