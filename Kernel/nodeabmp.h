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

#ifndef NODEABMP_H
#define NODEABMP_H

#include "nodebmp.h"


class NodeAnimatingBitmap : public NodeBitmap
{
	CC_DECLARE_DYNAMIC(NodeAnimatingBitmap)

public:
	
	// Creation & destruction.
	NodeAnimatingBitmap();
	NodeAnimatingBitmap(Node* ContextNode,  
						AttachNodeDirection Direction,  
						BOOL Locked = FALSE, 
						BOOL Mangled = FALSE,  
						BOOL Marked = FALSE, 
						BOOL Selected = FALSE);
	
	virtual ~NodeAnimatingBitmap();

	// Standard Node functions.
	virtual String Describe(BOOL Plural, BOOL Verbose);
	virtual UINT32 GetNodeSize() const;
	virtual Node* SimpleCopy();
	void CopyNodeContents(NodeAnimatingBitmap* pCopy);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Standard bitmap functions.
	virtual KernelBitmap* EnumerateBitmaps(UINT32 Count);
	virtual KernelBitmapRef* GetBitmapRef();
	virtual KernelBitmap* GetBitmap();

private:

	// Implementation.
	BOOL AllocBitmapRefs(INT32 nCount);

	// Data members.
	KernelBitmapRef* m_pBmpRefs;					// pointer to an array of contained bitmap refs
	UINT32			 m_nBmpCount;					// how many refs in the array
	UINT32			 m_nCurrentBmp;					// the 'current' sub-bitmap representing this
};

#endif	// !NODEABMP_H
