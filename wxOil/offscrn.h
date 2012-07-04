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


#ifndef INC_OFFSCREEN_RR
#define INC_OFFSCREEN_RR

// structs, typedefs, defines
//#include "gconsts.h"		// GCONTEXT - in camtypes.h [AUTOMATICALLY REMOVED]

// class definitions
//	1 - call classes member functions,
//	2 - use the class type for one of the members (not required if have pointer to class ??)
//	3 - to derive a superclass??

// class predeclarations
class GRenderDIB;
class GRenderRegion;
class ConcurrentRenderer;

// constants for view scaling.
// the pixel values apply for 100% zoom.
#define PIXELS_PER_INCH			96.0
#define MILLIPOINTS_PER_INCH	72000.0
#define INCHES_PER_METRE		(100.0 / 2.54)


/////////////////////////////////////////////////////////////////////////////////////////////
//
//								GRenderRegionWrappers
//
/////////////////////////////////////////////////////////////////////////////////////////////
/*
This class encapsulates the functionality required to temporarily use GDraw to render
into a new bitmap, and then return it to the state that it was in.

It is intended for use when you need to render a bitmap dynamically inside any of the 
following functions:-
1) Node::Render
2) Node::PreRenderChildren
3) Node::GoingOutOfScope
4) Node::ExportRender
5) Node::PreExportRender

It is designed to create bitmaps based on the screen resolution.
*/
class GRenderRegionWrapper : public CCObject // CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(GRenderRegionWrapper)

public:

	GRenderRegionWrapper() {}
	~GRenderRegionWrapper() {}

	// Setup and restore
	static GRenderRegionWrapper* GetAppropriateRenderWrapper (
					GRenderRegion* pActiveRR,
					double ResFactor,
					DocRect AreaOfDocumentToRender,
					UINT32 bpp,
					BOOL NeedsTransp
			);
	static ConcurrentRenderer* GetConcurrentRenderer (
					GRenderRegion*	pSourceRR,
					double			ResFactor,
					DocRect			AreaOfDocumentToRender,
					UINT32			bpp,
					BOOL			NeedsTransp
			);
	virtual BOOL Initialise(
					GRenderRegion* pActiveRR,
					double ResFactor,
					DocRect AreaOfDocumentToRender,
					UINT32 bpp,
					BOOL NeedsTransp
			) = 0;
	virtual BOOL RestorePreviousRendererState() = 0;
	static void NewWrappedRRCreated(GRenderRegion* pGrr);

	// Under the hood access
	virtual GRenderRegion* GetRenderRegion() = 0;
	void GetBitmapPointers(LPBITMAPINFO* bi, LPBYTE *by);

// Karim 06/07/2000
// I'm commenting these pre-processor directives out, to fix a bug with the new shadowing
// code, where shadows at anything other than 100% zoom are incorrectly scaled. This is a
// BODGE, and this code should be revisited at a later date.

//#ifdef _DEBUG
	static void GetBitmapPointers(GRenderRegion* pGrr, LPBITMAPINFO* bi, LPBYTE *by);
//#endif
	void SetBitmapPointers(LPBITMAPINFO bi, LPBYTE by);

	// Extract bmp in a convenient form
	KernelBitmap* GetKernelBitmap();
};

// Borrows GDraw from currently active RR by leveraging GRenderRegions offscreen rendering
// system
// Should be faster than ConcurrentRenderer because it doesn't need to create a new GRenderRegion
// class
class GDrawBorrower: public GRenderRegionWrapper
{
public:

	GDrawBorrower();
	~GDrawBorrower();

	virtual BOOL Initialise(
					GRenderRegion* pActiveRR,
					double ResFactor,
					DocRect AreaOfDocumentToRender,
					UINT32 bpp,
					BOOL NeedsTransp
			);
	virtual BOOL RestorePreviousRendererState();
	virtual GRenderRegion* GetRenderRegion()  { return m_pBorrowedRR; }

private:
	GRenderRegion* m_pBorrowedRR;
};

// 'Quick' in that it saves you having to construct a GRenderDIB and manually perform all
// the initialisation steps which are required before you can render using the GRenderDIB
// class
class QuickRenderer : public GRenderRegionWrapper
{
public:

	QuickRenderer();
	~QuickRenderer();

	virtual BOOL Initialise(
					GRenderRegion* pActiveRR,
					double ResFactor,
					DocRect AreaOfDocumentToRender,
					UINT32 bpp,
					BOOL NeedsTransp
			);
	virtual BOOL RestorePreviousRendererState();
	virtual GRenderRegion* GetRenderRegion() { return (GRenderRegion*) m_pNewRR; }

	static GRenderDIB* CreateGRenderDIB(
					double ResFactor,
					DocRect AreaOfDocumentToRender,
					UINT32 bpp,
					BOOL NeedsTransp,
					Matrix* pMat = NULL);

protected:
	void RestoreSimple();
	GRenderDIB* m_pNewRR;
};

// Saves GDraw context of currently active GRenderRegion
// Creates a new GRenderDIB (using QuickRenderer static fn)
class ConcurrentRenderer : public QuickRenderer
{
public:

	ConcurrentRenderer();
	~ConcurrentRenderer();

	virtual BOOL Initialise(
					GRenderRegion* pActiveRR,
					double ResFactor,
					DocRect AreaOfDocumentToRender,
					UINT32 bpp,
					BOOL NeedsTransp
			);
	virtual BOOL RestorePreviousRendererState();

private:
	GDrawContext* m_pOldGD;
	GDrawContext* m_pNewGD;
	View* m_pView;
};

#endif //INC_OFFSCREEN_RR
