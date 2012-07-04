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


#ifndef INC_OFFSCREENATTR
#define INC_OFFSCREENATTR

// structs, typedefs, defines

// class definitions
//	1 - call classes member functions,
//	2 - use the class type for one of the members (not required if have pointer to class ??)
//	3 - to derive a superclass??
//#include "attrval.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "gla.h"

////////////////////////
// class predeclarations
////////////////////////
class KernelBitmap;
class GRenderRegion;

////////////
// debugging
////////////
// Create a bitmap copy of the feathered object for comparison with the bitmap generated
// via the offscreen rendering system (ie m_pOffscreenBitmapInfo/Bits inside GoingOutOfScope)
// NB Set _DEBUG_OFFSCREEN_PIXEL_WIDTH, leave _DEBUG_OFFSCREEN_MP_WIDTH as is
// ( See notes in fthrattr.cpp for useage guidelines )
//#define _DEBUG_OFFSCREEN_PIXEL_WIDTH		44
//#define _DEBUG_OFFSCREEN_MP_WIDTH			_DEBUG_OFFSCREEN_PIXEL_WIDTH * 750

/////////////////////////////////////////////////////////////////////////////////////////////
//
//								Helper functions
//
/////////////////////////////////////////////////////////////////////////////////////////////
// Conversion between millipoints and pixels at current view scale
FIXED16 GetCurrentViewScale();
MILLIPOINT ConvertMeasurementToMillipointsAtCurrentViewScale(INT32 Width, UnitType type);
UINT32 ConvertMillipointsToPixelsAtCurrentViewScale(MILLIPOINT mp);
INT32 PixelsPerMeterAtCurrentViewScale();

/////////////////////////////////////////////////////////////////////////////////////////////
//
//								AttributeValue classes
//
/////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************
>	class OffscreenAttrValue : public GeometryLinkedAttrValue
	Author:		Ilan_Copelyn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/06/2000
	Purpose:	Provides a superclass from which you can derive attributes which require
				the nodes which they affect to be rendered offscreen.
	SeeAlso:	
	Notes:		This attribute is not meant to be instantated directly!
				It has no AttrIndex and is not added to the default attribute table
				when the attribute manager initialises itself
 ********************************************************************************************/

class OffscreenAttrValue : public GeometryLinkedAttrValue
{
	CC_DECLARE_DYNAMIC( OffscreenAttrValue )
	
protected:
	OffscreenAttrValue();		// not meant to be instantiated directly
public:
	~OffscreenAttrValue();

public:
	// Standard functions required by Attribute framework 
	virtual BOOL IsDifferent(AttributeValue*);

	// Karim 17/08/2000
	// This override is required so that the m_fForceTransparency flag is copied around.
	virtual void SimpleCopy(AttributeValue *pOther)
	{
		GeometryLinkedAttrValue::SimpleCopy(pOther);
		m_fForceTransparency = ((OffscreenAttrValue*)pOther)->m_fForceTransparency;
	}

	// Generic attr rendering functions (rely on GRenderRegion offscreen rendering system to do the work)
	virtual void Restore(RenderRegion *, BOOL);
	virtual void Render(RenderRegion *, BOOL Temp = FALSE);

	// Query function for GRenderRegion
//	virtual BOOL OffscreenBmpRectMayExceedViewableRect() { return FALSE; }	// not used at the moment. might by required though
	virtual DocRect	GetOffscreenBoundingRect();
	virtual void	SetOffscreenBoundingRect(const DocRect drOffBB) { m_OffBB = drOffBB; }

	// Allow derived classes to overide integral parts of the offscreen bmp setup process
	virtual BOOL DoesOffscreenBmpRequireTransp(GRenderRegion* pGRR = NULL);
	BOOL TestNodeForTransparency(Node* pNode = NULL);
	virtual void GetMinimumOffscreenBmpDimensions(UINT32* RequiredWidth, UINT32* RequiredHeight) { *RequiredWidth=0;*RequiredHeight=0; }
	virtual BOOL DoesOffscreenBMPCaptureBackground() {return FALSE;}

	// Karim 17/08/2000 - force this attr to always use a transparency-capable offscreen bmp.
	void SetAlwaysUseTransparency()		{ m_fForceTransparency = TRUE; }
	// Karim 17/08/2000
	// let this attr choose whether or not to use a transparency-capable offscreen bitmap.
	void UnsetAlwaysUseTransparency()	{ m_fForceTransparency = FALSE; }

	// Overide this to use the offscreen bitmap
	virtual void OffscreenRenderingCompleted(RenderRegion *pRender, LPBITMAPINFO lpBitmapInfo, LPBYTE lpBits, DocRect BitmapRect) = 0;

	//-------------------------------------------------------------------------------------------------------------
	//	Debugging your offscreen attribute
	//
#ifdef _DEBUG_OFFSCREEN_PIXEL_WIDTH
protected:
	// Debugging function. Creates bitmap of a node using new GRenderBitmap RR.
	// Useful for comparing to offscreen bitmap.
	KernelBitmap* CreateIntermediateBitmap( GRenderRegion* GRR, Node* pNode, double ScreenResMultiplier, 
											UINT32 bpp, BOOL UseInternalFmt );
	BOOL RenderDebuggingBitmaps(GRenderRegion* GRR, Node* pNode, double ScreenResMultiplier,
											UINT32 bpp, BOOL UseInternalFmt );
#endif

protected:
	//-------------------------------------------------------------------------------------------------------------
	//										Member Variables
	//

	// Offscreen rendering attributes:
	DocRect						m_OffBB;

	// Karim 16/08/2000
	// a record of whether or not our linked node requires transparency.
	BOOL						m_fForceTransparency;
//	DocRect						m_ViewBB;

#ifdef _DEBUG_OFFSCREEN_PIXEL_WIDTH
	// Debugging members
	KernelBitmap*				md_NodeBmp;
	KernelBitmap*				md_SlicedBmp;
#endif


	//-------------------------------------------------------------------------------------------------------------

#ifdef DEBUGOFFSCREENATTRS
private:
	// Debug render-twice flag. See OffscreenAttrValue::Render() for more info.
	BOOL m_fHasBeenRendered;
#endif
};


#endif //INC_OFFSCREENATTR
