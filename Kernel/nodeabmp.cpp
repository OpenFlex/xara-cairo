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
// NodeAnimatingBitmap
//
// This class is like a plain ol' NodeBitmap, but instead manages a collection of
// related bitmaps, such as an animating GIF.
//

#include "camtypes.h"

#include "nodeabmp.h"
#include "bmpcomp.h"

CC_IMPLEMENT_DYNAMIC(NodeAnimatingBitmap, NodeBitmap)



NodeAnimatingBitmap::NodeAnimatingBitmap()
  :	m_pBmpRefs(0),
	m_nBmpCount(0)
{

}



NodeAnimatingBitmap::NodeAnimatingBitmap(Node* ContextNode, AttachNodeDirection Direction, 
										 BOOL Locked, BOOL Mangled, BOOL Marked, BOOL Selected)
  :	NodeBitmap(ContextNode, Direction, Locked, Mangled, Marked, Selected),
	m_pBmpRefs(0),
	m_nBmpCount(0)
{

}



NodeAnimatingBitmap::~NodeAnimatingBitmap()
{

}



String NodeAnimatingBitmap::Describe(BOOL Plural, BOOL Verbose)
{
	// TEMP: this is candy-floss for now.
	return NodeBitmap::Describe(Plural, Verbose);
}



UINT32 NodeAnimatingBitmap::GetNodeSize() const
{
	return sizeof(*this);
}



Node* NodeAnimatingBitmap::SimpleCopy()
{
	NodeAnimatingBitmap* pCopy = new NodeAnimatingBitmap;
	if (pCopy) CopyNodeContents(pCopy);
	return pCopy;
}



void NodeAnimatingBitmap::CopyNodeContents(NodeAnimatingBitmap* pCopy)
{
	// Copy the base class followed by members specific to this derived class.
	NodeBitmap::CopyNodeContents(pCopy);
	if (pCopy->AllocBitmapRefs(m_nBmpCount))
		for (UINT32 i = 0; i < m_nBmpCount; i++)
			pCopy->m_pBmpRefs[i] = m_pBmpRefs[i];
}



/***********************************************************************************************
>   void NodeAnimatingBitmap::PolyCopyNodeContents(NodeRenderable* pNodeCopy)

    Author:     Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
    Created:    18/12/2003
    Outputs:    -
    Purpose:    Polymorphically copies the contents of this node to another
	Errors:     An assertion failure will occur if NodeCopy is NULL
    Scope:      protected
								     
***********************************************************************************************/

void NodeAnimatingBitmap::PolyCopyNodeContents(NodeRenderable* pNodeCopy)
{
	ENSURE(pNodeCopy, "Trying to copy a node's contents into a NULL node");
	ENSURE(IS_A(pNodeCopy, NodeAnimatingBitmap), "PolyCopyNodeContents given wrong dest node type");

	if (IS_A(pNodeCopy, NodeAnimatingBitmap))
		CopyNodeContents((NodeAnimatingBitmap*)pNodeCopy);
}



KernelBitmap* NodeAnimatingBitmap::EnumerateBitmaps(UINT32 nCount)
{
	return (nCount < m_nBmpCount) ? m_pBmpRefs[nCount].GetBitmap() : 0;
}



KernelBitmapRef* NodeAnimatingBitmap::GetBitmapRef()
{
	return &m_pBmpRefs[m_nCurrentBmp];
}



KernelBitmap* NodeAnimatingBitmap::GetBitmap()
{
	KernelBitmap* pBitmap = m_pBmpRefs[m_nCurrentBmp].GetBitmap();
	if (pBitmap && pBitmap->HasBeenDeleted())
	{	
		// If necessary (due to the crud that is the bitmap system) use the default bitmap instead.
		ERROR2IF(pBitmap->GetParentBitmapList() == NULL, NULL, "Deleted bitmap has no parent list");
		pBitmap = pBitmap->GetParentBitmapList()->FindDefaultBitmap();

		// There should always be a default bitmap in the list
		ERROR2IF(pBitmap == NULL, 0L, "Couldn't find the default bitmap");
	}
	
	return pBitmap;
}



BOOL NodeAnimatingBitmap::AllocBitmapRefs(INT32 nCount)
{
	ERROR3IF(m_pBmpRefs != 0, "Bitmaps already allocated in NodeAnimatingBitmap::AllocBitmapRefs");
	ERROR3IF(nCount <= 0, "Invalid count in NodeAnimatingBitmap::AllocBitmapRefs");
	m_pBmpRefs = new KernelBitmapRef[nCount];
	return m_pBmpRefs != 0;
}
