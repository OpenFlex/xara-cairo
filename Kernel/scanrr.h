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

// The Scanning Render region class

#ifndef INC_SCANRR
#define INC_SCANRR


/********************************************************************************************

>	class NodeListItemWithDocPtr : public NodeListItem

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/7/2000
	Purpose:	This is used to ensure that blends print correctly.  If a particular
				NodeBlender was classified as simple, and is later used with a blend
				that is complex, then complex blend steps will not render.  This class
				allows us to reclassify a simple node as a complex one.
	SeeAlso:	-

********************************************************************************************/

class NodeListItemWithComplexity : public NodeListItem
{
public:
	CC_DECLARE_DYNAMIC( NodeListItemWithComplexity )
	NodeListItemWithComplexity();							// will contain a NULL pointer
	NodeListItemWithComplexity(Node* WhichNode, BOOL val);	// initialise pNode to be WhichNode
	~NodeListItemWithComplexity() {}						// Nothing to destruct
	
	BOOL wasClassifiedSimple;						// was the node classified as simple?
	INT32 RunLength;
	DocRect BoundsRect;
};

/********************************************************************************************

>	class ScanningRenderRegion : public RenderRegion

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/4/95
	Purpose:	The Scanning Render Region is a special sort of render region that simply
				scans the document and works out where abouts there are complex shapes that
				can not be rendered by a normal OSRenderRegion. Complex shapes are shapes
				that are transparant or any other attribute that we are unable to render
				to normally. The Scanning Render Region is used to help with things like
				printing, Renderable EPS export etc where transparancy is not available.

********************************************************************************************/

class ScanningRenderRegion : public RenderRegion
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(ScanningRenderRegion);

	// Construction and destruction
	ScanningRenderRegion(BOOL Printing);
	~ScanningRenderRegion();

	// Starting and stopping the rendering process
	virtual BOOL StartRender();
	virtual BOOL StopRender();

	// Functions that are meant to do the drawing
	virtual void DrawPathToOutputDevice(Path *PathToRender, PathShape shapePath=PATHSHAPE_PATH);
	virtual void DrawRect(DocRect *RectToRender);
	virtual void DrawLine(const DocCoord &StartPoint, const DocCoord &EndPoint);
	virtual void DrawPixel(const DocCoord &Point);

	// Functions that are supposed to draw bitmaps
	virtual void DrawBitmap(const DocCoord &Point, KernelBitmap* pBitmap);
	virtual void DrawBitmap(const DocCoord &Point, UINT32 BitmapID, UINT32 ToolID = NULL);
	virtual BOOL DrawTransformedBitmap(NodeBitmap *pNodeBitmap);

	// Other Pure virtual drawing functions that have to be overidden
	virtual void DrawDragRect(DocRect *RectToRender);
	virtual void DrawBlob(DocCoord p, BlobType type);
	virtual void DrawCross(const DocCoord &Point, const UINT32 Size);
	virtual void DrawBitmapBlob(const DocCoord &Point, KernelBitmap* BlobShape);
	virtual void DrawBitmapBlob(const DocCoord &Point, ResourceID resID );

	// Pure Virtual functions that have to be overidden to use this class.
	// They all do nothing in this class
	virtual void InitClipping();
	virtual void InitAttributes();
	virtual void SetLineAttributes();
	virtual void SetOSDrawingMode();
	virtual void SetQualityLevel();
	virtual MILLIPOINT CalcPixelWidth();
	virtual MILLIPOINT CalcScaledPixelWidth();

	// Force this to return a sensible value so that the capture system
	// doesn't get horribly upset
	virtual double GetPixelsPerInch() { return 96.0; }

	// Make sure that offscreen attrs are rendered when out of bounds
	virtual BOOL CheckOffscreenBounds() { return(FALSE); }

	// Function to work out what things this type of render region is capable of rendering
	virtual void GetRenderRegionCaps(RRCaps* pCaps);

	// Function to tell the scanning render region what the region it is scanning
	// for can render.
	void SetHostRRCaps(const RRCaps& pCaps);

	// Functions to get at the info held by the scanning render regions
	Node* GetFirstComplexObject();
	Node* GetLastComplexObject();

	// Find the number of nodes in various sections of the tree
	INT32 GetNumComplex();

	// Function to find out the size of the bounding rect that covers all complex shapes
	DocRect GetComplexBounds();

	// Function to find out if we are done yet
	BOOL IsFinished();

	// Functions to get at the list of runs etc
	BOOL IsFirstNodeComplex();
	Node* FindFirstFromList();
	Node* FindNextFromList();
	BOOL IsThisNodeComplex();
	DocRect GetSpanBounds();

	void SetRenderState(Node *RenderState);

protected:
	// Function that is called when a complex shape has been found
	void ComplexShapeFound() { bIsComplex = TRUE; };
	void ComplexShapeFoundHelper();		// CGS (12/10/2000):  MUST take NodeBlenders of compound nodes into account!
	void SimpleShapeFound() { bIsSimple = TRUE; };
	void SimpleShapeFoundHelper();		// CGS (12/10/2000):  MUST take NodeBlenders of compound nodes into account!

public:
	void ComplexShapeFoundWrapper();	// CGS (20/10/2000):  allows us to access ComplexShapeFound directly.
										// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
										// YOU SHOULD ONLY CALL THIS FUNCTION IF YOU KNOW WHAT YOU ARE DOING !!!!!!!
										// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#ifdef _DEBUG
	void DumpNodeRuns();
#endif


protected:
	// Vars that the Scanning render region uses
	// The first and last complex objects
	Node* pFirstComplex;
	Node* pLastComplex;

	// The number of complex shapes in the region
	INT32 NumComplexShapes;

	// a rectangle that holds the bounds of all the complex shapes in the render region
	DocRect ComplexBounds;
	DocRect SpanBounds;

	// List of runs of complex and non-complex nodes
	List NodeRuns;
	NodeListItemWithComplexity* pCurrentListItem;
	BOOL IsFirstComplex;
	BOOL IsThisTheFirstNode;
	BOOL InComplexRun;
	INT32 RunLength;

	BOOL bIsComplex;
	BOOL bIsSimple;
	ClipRegionAttribute* pLastClipAttr;

private:
	// A flag to say if we have finished rendering or not
	BOOL IsFinishedRendering;

	// The Caps for the region we are scanning on behlaf of
	RRCaps HostCaps;
};



#endif  // INC_SCANRR
