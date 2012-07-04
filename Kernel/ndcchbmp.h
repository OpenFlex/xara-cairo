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

// Node representing a bitmap object.

#ifdef _BUILD_CACHE_COMPOUND

#ifndef INC_NODECACHEBMP
#define INC_NODECACHEBMP

#include "nodebmp.h"
//#include "bitmap.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class ExtendParams;

class NodeCacheBitmap : public NodeBitmap
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(NodeCacheBitmap);

public:
	NodeCacheBitmap();
	NodeCacheBitmap(Node* ContextNode,
					AttachNodeDirection Direction,
					BOOL Locked = FALSE,
					BOOL Mangled = FALSE,
					BOOL Marked = FALSE,
					BOOL Selected = FALSE
					);

	virtual String Describe(BOOL Plural, BOOL Verbose); 
	virtual BOOL IsBounded() { return FALSE; }
	virtual Node* SimpleCopy();
	void CopyNodeContents(NodeBitmap* NodeCopy);
	virtual void Render( RenderRegion* pRender );
	virtual void RenderTinyBlobs(RenderRegion* pRender);			// Actually want orignal shapes blobs to be drawn
    virtual BOOL ShowingNode();
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
	virtual BOOL NeedsTransparency() const { return TRUE; }
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Bitmap Setup Function
	BOOL InitCacheBitmapNode(DocRect pRect, KernelBitmap* pKernelBMP = NULL, BOOL JustDoKernelBMP = FALSE);

	// Regenerate the Bitmaps Shape using a new DocRect
	BOOL ReshapeBitmap(DocRect* pRect = NULL);

	// Karim MacDonald 09/12/1999
	// TransformTranslateObject method overridden from class NodeRenderable.
	virtual void TransformTranslateObject(const ExtendParams& ExtParams);
}; 


/***********************************************************************************************

>	class CacheBitmapRecordHandler : public CamelotRecordHandler

	Author:		Ilan_Copelyn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/99
	Purpose:	Need to override default behaviour of bitmap import/export. No bmp data
				needs to be saved as it will be regenerated.
	SeeAlso:	NodeCacheBitmap::WritePreChildrenNative()

***********************************************************************************************/

class CacheBitmapRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CacheBitmapRecordHandler);

public:
	CacheBitmapRecordHandler() : CamelotRecordHandler() {}
	~CacheBitmapRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

private:
	BOOL HandleCacheBitmapRecord(CXaraFileRecord* pCXaraFileRecord);
};
 
#endif  // INC_NODECACHEBMP

#endif
