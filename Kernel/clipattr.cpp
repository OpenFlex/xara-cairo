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
// Implementation of ClipRegionAttribute.
//

#include "camtypes.h"	// pre-compiled header
#include "clipattr.h"	// our own header file
#include "grndrgn.h"	// for GRenderRegion.
//#include "mario.h"			// _R(IDE_NOMORE_MEMORY)
#include "blendatt.h"		// BlendAttrParam

DECLARE_SOURCE("$Revision: 1361 $")

// runtime class creation stuff.
CC_IMPLEMENT_DYNCREATE(ClipRegionAttribute, AttributeValue)
CC_IMPLEMENT_DYNAMIC(AttrClipView, NodeAttribute)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW



/********************************************************************************************

>	ClipRegionAttribute::ClipRegionAttribute()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
ClipRegionAttribute::ClipRegionAttribute()
{
	m_pClipPath	= NULL;
	m_bResponsibleForGrouping = FALSE;
}



/********************************************************************************************

>	ClipRegionAttribute::~ClipRegionAttribute()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
ClipRegionAttribute::~ClipRegionAttribute()
{
	if (m_pClipPath != NULL)
		m_pClipPath = NULL;
}



/********************************************************************************************

>	virtual void ClipRegionAttribute::Render(RenderRegion* pRender, BOOL Temp = FALSE)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
void ClipRegionAttribute::Render(RenderRegion* pRender, BOOL Temp)
{
// DEBUG:
//	TRACEUSER( "Karim", _T("ClipRegionAttribute::Render; 0x%x with path 0x%x\n"), (DWORD)this,
//																			(DWORD)m_pClipPath);
//	TRACEUSER( "Karim", _T("pClipAttr 0x%x Render()'ed by RR 0x%x\n"),
//									(DWORD)this, (DWORD)pRender);
	pRender->SetClipRegion(this, Temp);
}



/********************************************************************************************

>	virtual void ClipRegionAttribute::Restore(RenderRegion* pRender, BOOL Temp)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
void ClipRegionAttribute::Restore(RenderRegion* pRender, BOOL Temp)
{
// DEBUG:
//	TRACEUSER( "Karim", _T("ClipRegionAttribute::Restore; 0x%x with path 0x%x\n"), (DWORD)this,
//																			(DWORD)m_pClipPath);
//	TRACEUSER( "Karim", _T("pClipAttr 0x%x Restore()'ed by RR 0x%x\n"),
//									(DWORD)this, (DWORD)pRender);
	pRender->RestoreClipRegion(this, Temp);
}



/********************************************************************************************

>	virtual void ClipRegionAttribute::GoingOutOfScope(RenderRegion* pRender)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
void ClipRegionAttribute::GoingOutOfScope(RenderRegion* pRender)
{
// DEBUG:
//	TRACEUSER( "MarkH", _T("ClipRegionAttribute::GoingOutOfScope; 0x%x with path 0x%x\n"), (DWORD)this,
//																			(DWORD)m_pClipPath);
}



/********************************************************************************************

>	virtual void ClipRegionAttribute::SimpleCopy(AttributeValue* pSource)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Inputs:		pSource		the ClipRegionAttribute to copy.
	Outputs:	This ClipRegionAttribute becomes a copy of pSource.

	Purpose:	Make this attribute into a straight copy of the given attribute.

	Notes:		Note that NO error checking is done in this routine (bad?), so MAKE SURE
				that the pointer you pass in as pSource is a VALID ClipRegionAttribute.

********************************************************************************************/
void ClipRegionAttribute::SimpleCopy(AttributeValue* pSource)
{
// DEBUG:
//	TRACEUSER( "Karim", _T("ClipRegionAttribute::SimpleCopy; 0x%x with path 0x%x\n"), (DWORD)this,
//																			(DWORD)m_pClipPath);
	m_pClipPath = ((ClipRegionAttribute*)pSource)->m_pClipPath;
}



/********************************************************************************************

>	NodeAttribute* AttributeValue::MakeNode()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12 April 2000
	Returns:	NULL always.
	Purpose:	This method is here so that an AttributeValue can build and return a 
				corresponding NodeAttribute, for insertion into the tree. We don't do
				this, as we're not linked with NodeAttributes at all.

********************************************************************************************/
NodeAttribute* ClipRegionAttribute::MakeNode()
{
	return NULL;
}



/********************************************************************************************

>	virtual BOOL ClipRegionAttribute::IsDifferent(AttributeValue* pOther)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
BOOL ClipRegionAttribute::IsDifferent(AttributeValue* pOther)
{
// DEBUG:
//	TRACEUSER( "Karim", _T("ClipRegionAttribute::IsDifferent; we are 0x%x\n"), (DWORD)this);
	ERROR2IF(	GetRuntimeClass() != pOther->GetRuntimeClass(), TRUE,
			   "Attribute difference comparison must be between same types"	);
	return (m_pClipPath != ((ClipRegionAttribute*)pOther)->GetClipPath());
}



/********************************************************************************************

>	static BOOL ClipRegionAttribute::Init()

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20 March 2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	
	Errors:		
	See also:	

********************************************************************************************/
BOOL ClipRegionAttribute::Init()
{
	ClipRegionAttribute* pAttrVal = NULL;
	pAttrVal = new ClipRegionAttribute;
	if (pAttrVal == NULL)
		return FALSE;

	UINT32 ID = AttributeManager::RegisterDefaultAttribute(CC_RUNTIME_CLASS(NodeRenderableInk),
														 pAttrVal);

	if (ID == ATTR_BAD_ID)
		return FALSE;

	ERROR3IF(ID != ATTR_CLIPREGION, "Incorrect ID for attribute!");
	return TRUE;
}

///////////////////////////////////// NEW CLIPVIEW ATTRIBUTE!!! /////////////////////////////
AttrClipView::AttrClipView()
{
	m_DoRender = TRUE;
	Value.SetResponsibleForGrouping (TRUE);
}

AttrClipView::AttrClipView(Node* ContextNode, AttachNodeDirection Direction,
							BOOL Locked, BOOL Mangled, BOOL Marked, BOOL Selected) : 
							NodeAttribute(ContextNode, Direction, Locked, Mangled, Marked, Selected)
{
	m_DoRender = TRUE;
	Value.SetResponsibleForGrouping (TRUE);
}

AttrClipView::~AttrClipView()
{
}

void AttrClipView::Render( RenderRegion* pRender )
{
	// check the pointer and also make sure that we`re allowed to render
	if (!pRender || !m_DoRender)
		return;

	// Don`t need to render when hit testing
	if(!pRender->IsHitDetect())
		Value.Render(pRender);
}

#ifdef _DEBUG
void AttrClipView::GetDebugDetails(StringBase* Str)
{
	// Get our base class debug info.
	NodeRenderable::GetDebugDetails(Str);

	// Output the data for our clipping path.
	Path* pClipPath = Value.GetClipPath();

	if (pClipPath == NULL)
	{
		(*Str) += TEXT( "\r\nNo Clipping Path Data\r\n" );
	}
	else
	{
		(*Str) += TEXT( "\r\nClipping Path Data\r\n" );
		pClipPath->GetDebugDetails(Str);
	}
}
#endif

Node* AttrClipView::SimpleCopy()
{
	AttrClipView* pAttr = new AttrClipView();
	ERRORIF(pAttr==NULL, _R(IDE_NOMORE_MEMORY),NULL);

	CopyNodeContents(pAttr);
	return pAttr;
}



/***********************************************************************************************
>   void AttrClipView::PolyCopyNodeContents(NodeRenderable* pNodeCopy)

    Author:     Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
    Created:    18/12/2003
    Outputs:    -
    Purpose:    Polymorphically copies the contents of this node to another
	Errors:     An assertion failure will occur if NodeCopy is NULL
    Scope:      protected
								     
***********************************************************************************************/

void AttrClipView::PolyCopyNodeContents(NodeRenderable* pNodeCopy)
{
	ENSURE(pNodeCopy, "Trying to copy a node's contents into a NULL node");
	ENSURE(IS_A(pNodeCopy, AttrClipView), "PolyCopyNodeContents given wrong dest node type");

	if (IS_A(pNodeCopy, AttrClipView))
		CopyNodeContents((AttrClipView*)pNodeCopy);
}



void AttrClipView::CopyNodeContents(NodeAttribute *pCopy)
{
	NodeAttribute::CopyNodeContents(pCopy);
	((AttrClipView*)pCopy)->Value.SimpleCopy( &Value );
}

INT32 AttrClipView::operator==(const NodeAttribute& NodeAttrib)
{
	Path* pComparePath = ((ClipRegionAttribute*)&NodeAttrib)->GetClipPath();
	Path* pThisPath = Value.GetClipPath();

	if(pComparePath && pThisPath)
	{
		return pThisPath->ComparePathToPath(pComparePath);
	}

	return -1;
}

void AttrClipView::Transform(TransformBase& Trans)
{
//	static const FIXED16 One(1.0);

//	FIXED16 ScaleFactor = Trans.GetScaleFactor();
}

BOOL AttrClipView::Blend(BlendAttrParam* pBlendParam)
{
	// Don`t want to blend this attribute at the mo!
	return FALSE;
}

BOOL AttrClipView::ContainsAttributeValue(AttributeValue* pVal)
{
	if(!pVal->IS_KIND_OF(ClipRegionAttribute))
	{
		ENSURE(FALSE,"Strange attr value comparison test requested");
		return FALSE;
	}

	return (pVal == &Value);
}

BOOL AttrClipView::WritePreChildrenWeb(BaseCamelotFilter* pFilter)
{
	return TRUE;
}

BOOL AttrClipView::WritePreChildrenNative(BaseCamelotFilter* pFilter)
{
	return TRUE;
}
