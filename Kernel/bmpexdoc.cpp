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


#include "camtypes.h"

#include "bmpexdoc.h"
#include "layer.h"
//#include "spread.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "will2.h"		// For layer name
#include "nodebmp.h"
#include "bitmpinf.h"
//#include "fillval.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#include "lineattr.h"	// AttrStrokeColour
//#include "fillattr.h"	// AttrFillGeometry - in camtypes.h [AUTOMATICALLY REMOVED]

DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_DYNAMIC(BitmapExportDocument, Document)

#define new CAM_DEBUG_NEW


/********************************************************************************************

>	BitmapExportDocument::BitmapExportDocument(BOOL fHide = TRUE)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		fHide - whether this document is invisible or not (default is invisible)
	Purpose:	BitmapExportDocument constructor.

********************************************************************************************/

BitmapExportDocument::BitmapExportDocument(BOOL fHide)
  : Document(fHide),
	pBitmapNode(0)
{
	// Empty.
}



/********************************************************************************************

>	BOOL BitmapExportDocument::Init(KernelBitmap* pBitmap, const DocRect& RectToExport)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pBitmap - pointer to the kernel bitmap to be inserted into the document
							(can't be const 'cos KernelBitmapRef::SetBitmap isn't)
				RectToExport - DocRect reference of the rectangle to export	
	Returns:	FALSE if it failed
	Purpose:	This method initialises the document
				It calls down to Document::Init, then adds an insertion Layer node to the
				bottom of the basic doc tree.
				It then adds a totally transparent NodeRectangle and a NodeBitmap with the
				default NodeBitmap attributes referencing the specified KernelBitmap
	SeeAlso:	Document::Init; Document::InitTree

********************************************************************************************/

BOOL BitmapExportDocument::Init(KernelBitmap* pBitmap, const DocRect& RectToExport)
{
	// Don't attach any CCamDoc.
	if (!Document::Init(0)) return(FALSE);

	Node *pSpread = FindFirstSpread();
	ERROR3IF(pSpread == NULL, "No Spread in document!");

	Node *pLayer = pSpread->FindFirstChild();
	ERROR3IF(pLayer == NULL, "No Spread-child in document!");

	// Store away the rectangle
	ExportRect = RectToExport;

	// Now scan the children of the first spread until we find a layer, or run out of nodes
	while (pLayer != NULL && !pLayer->IsLayer())
		pLayer = pLayer->FindNext();

	if (pLayer == NULL)		// No Layer, so we'd better add one for ourselves
	{
		String_256 LayerID = String_256(_R(IDS_K_CLIPINT_LAYERNAME));
		pLayer = new Layer(pSpread, LASTCHILD, LayerID);
		if (pLayer == NULL)
			return(InitFailed());
	}

	// Create a new NodeRect
	NodeRect* pRectNode = new NodeRect(pLayer, FIRSTCHILD);

	// Failed so cleanup and exit
	if (pRectNode == NULL)
		return(InitFailed());

	// Initilaise the node
	if (!pRectNode->SetUpPath(6,6))
		return(InitFailed());

	// Create the rectangle
	pRectNode->CreateShape(ExportRect);

	// Give the rectangle a line colour
#if 0
	// This memory leaks a StrokeColourAttribute
	StrokeColourAttribute* pAttrValue = new StrokeColourAttribute(DocColour(COLOUR_TRANS));
	if (pAttrValue == NULL)
		return(InitFailed());
	
	NodeAttribute* pAttr = pAttrValue->MakeNode();
	if (pAttr == NULL)
		return(InitFailed());

	// Attach the attribute to the rectangle
	pAttr->AttachNode(pRectNode, FIRSTCHILD);
#else
	// Do what ApplyDefaultBitmapAttrs does
	Node* pLineColAttr = new AttrStrokeColour();
	if (pLineColAttr == NULL)
		return(InitFailed());

	DocColour none(COLOUR_NONE);
	((AttrFillGeometry*)pLineColAttr)->SetStartColour(&none);
	pLineColAttr->AttachNode(pRectNode, FIRSTCHILD);
#endif

	// Create a NodeBitmap (don't attach it to the tree straight away 'cos we
	// have to put the attributes on it first)

	pBitmapNode = new NodeBitmap();
	if (pBitmapNode == NULL)
		return(InitFailed());

	if (!pBitmapNode->SetUpPath(6,6))
		return(InitFailed());

	pBitmapNode->CreateShape(ExportRect);

	if (!SetBitmap(pBitmap))
		return(InitFailed());

	// Set the bitmap's attributes
	// This must be done before the NodeBitmap is inserted into the tree
	if (!pBitmapNode->ApplyDefaultBitmapAttrs(NULL))
		return(InitFailed());

	// Attach it to the tree as the next sibling of the rectangle
	pBitmapNode->AttachNode(pRectNode, NEXT);

	// Success...
	return(TRUE);
}



/********************************************************************************************

>	BOOL BitmapExportDocument::SetBitmap(KernelBitmap* pBitmap)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/6/96
	Inputs:		pBitmap - pointer to the kernel bitmap to be inserted into the document
							(can't be const 'cos KernelBitmapRef::SetBitmap isn't)
	Returns:	FALSE if it failed
	Purpose:	This function sets the bitmap method initialises the document
				It is an internal method, called by Initialise()
				It calls down to Document::Init, then adds an insertion Layer node to the
				bottom of the basic doc tree.
				It then adds a NodeBitmap referencing the specified KernelBitmap

********************************************************************************************/

BOOL BitmapExportDocument::SetBitmap(KernelBitmap* pBitmap)
{
	TRACEUSER( "Gerry", _T("BitmapExportDocument::SetBitmap()\n"));

	ERROR2IF(pBitmap == NULL, FALSE, "NULL bitmap passed to SetBitmap()\n");
	ERROR2IF(pBitmapNode == NULL, FALSE, "pBitmapNode is NULL in SetBitmap()\n");

	// Attach the bitmap to our node
	//
	// Note: Neville 18/9/97 
	// If the bitmap is a lone bitmap i.e. not attached to any document, then we
	// must attach it properly to this document so that it gets cleaned out
	// rather than memory leaking. If not, then we are just temporarily using
	// the bitmap and so everything should be ok. We need to work in the following
	// situations:-
	// - Selecting multiple bitmaps in the bitmap gallery and saving as animated GIF.
	//	 Here we are passed a list of bitmaps which are already in use in the source
	//   document.
	// - Making a new clipart index for bitmaps. Here we are passed a brand spanking
	//   new bitmap which is not on any lists. This used to memory leak.
	BitmapList* pBmpList = pBitmap->GetParentBitmapList();
	if (pBmpList != NULL)
	{
		// This will memory leak a kernel bitmap each time if it is not on a parent
		// document list. You will also end up with a KernelBitmap which contains
		// a deleted ActualBitmap pointer, which is very bad!
		pBitmapNode->GetBitmapRef()->SetBitmap(pBitmap);
	}
	else
	{
		// This is the same technique that the BaseBitmapFilter uses and so must be correct!
		pBitmapNode->GetBitmapRef()->Attach(pBitmap, this);
		if (pBitmapNode->GetBitmap() != pBitmap)
		{
			// It didn't use the bitmap we gave it, so we can delete it
			delete pBitmap;
		}
	}
	
	BitmapInfo Info;
	pBitmapNode->GetBitmap()->ActualBitmap->GetInfo(&Info);

	// Calculate the rectangle for this bitmap
	// We make it as large as possible (within the ExportRect)
	// without changing the aspect ration

	INT32 RectWidth = ExportRect.Width();
	INT32 RectHeight = ExportRect.Height();

	double xScale = (double) RectWidth / (double) Info.RecommendedWidth;
	double yScale = (double) RectHeight / (double) Info.RecommendedHeight;

	DocRect BitmapRect;

	BitmapRect.lo.x = 0;
	BitmapRect.lo.y = 0;

	if (xScale < yScale)
	{
		// Bitmap will be full width
		BitmapRect.hi.x = RectWidth;
		BitmapRect.hi.y = (INT32) ((double) Info.RecommendedHeight * xScale);

		// Center the bitmap vertically in the rectangle
		BitmapRect.Translate(0, (RectHeight - BitmapRect.Height()) / 2);
	}
	else
	{
		// Bitmap will be full height
		BitmapRect.hi.x = (INT32) ((double) Info.RecommendedWidth * yScale);
		BitmapRect.hi.y = RectHeight;

		// Center the bitmap horizontally in the rectangle
		BitmapRect.Translate((RectWidth - BitmapRect.Width()) / 2, 0);
	}

	// Delete the node's path
	// Because CreateShape inserts a rectangle at the beginning of the path
	pBitmapNode->InkPath.DeleteFromElement(0);

	// And create the shape
	pBitmapNode->CreateShape(BitmapRect);

	return(TRUE);
}



/********************************************************************************************

>	BOOL BitmapExportDocument::InitFailed(void)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/6/96
	Inputs:		-
	Returns:	See Document::InitFailed()
	Purpose:	This function deletes the NodeBitmap and then calls Document::InitFailed()
	SeeAlso:	Document::InitFailed

********************************************************************************************/

BOOL BitmapExportDocument::InitFailed(void)
{
	if (pBitmapNode)
	{
		delete pBitmapNode;
		pBitmapNode = NULL;
	}

	return(Document::InitFailed());
}
