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


#ifndef INC_RGNLIST
#define INC_RGNLIST

#include "list.h"
#include "listitem.h"
#include "docrect.h"

class RenderRegion;  // #include "rndrgn.h"
class Document;
class View;
class Node;

/***********************************************************************************************

>	class RenderRegionList : public List

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/5/93
	Purpose:	Holds a list of RenderRegion objects for the application to process.
				It should be used to add or remove render regions, or to initiate background
				rendering on idle events.
	SeeAlso:	RenderRegion

***********************************************************************************************/

class CCAPI RenderRegionList : public List
{
CC_DECLARE_MEMDUMP(RenderRegionList);

public:
	// Constructor
	RenderRegionList();
	
	// Destructor
	~RenderRegionList();
	
	// Functions to add and delete render regions from the list.
	void Merge(RenderRegion *NewRegion);
	void Remove(RenderRegion *);
	void Remove(Document *); // Removes all render regions associated with this document
	void Remove(View *); // Removes all render regions associated with this document view
	
	// Functions to do some rendering
	BOOL BackgroundRender();
	void ImmediateRender(BOOL bForceImmediate = FALSE);

	void HandleNodeDeletion(Node* pNode);
	
private:
	// Pointer to the last region rendered
	RenderRegion *LastRendered;
	
	MILLIPOINT PixelWidth;	// The width of a pixel, used for rectangle merging.
	
	// This flag is so we don't do merging checks unnecessarily during background rendering.
	BOOL ListIsOptimal;

	// Functions to compact the render region list, if possible
	void TidyUpAdjacentRegions(RenderRegion*);
	void MergeRenderRegions(RenderRegion* NewRenderRegion);
	void StrictMerge(RenderRegion* pRegionToMerge);
	void RemoveRegionOverlap(RenderRegion* NewRenderRegion);
	void ClipRectsToClient();
	void TryTotalUnion();
	void DoTotalUnion(RenderRegion *pRegion, View *pView, DocRect TotalUnion);

};

#endif
