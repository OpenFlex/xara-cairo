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


#ifndef INC_FEATHRATTR
#define INC_FEATHRATTR

// structs, typedefs, defines
//#include "unittype.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// class definitions
//	1 - call classes member functions,
//	2 - use the class type for one of the members (not required if have pointer to class ??)
//	3 - to derive a superclass??
#include "offattr.h"
//#include "biasgain.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// for MAX_SHADOW_BLUR
#include "bshadow.h"

////////////////////////
// class predeclarations
////////////////////////
class BitmapTranspFillAttribute;
class TranspFillMappingLinearAttribute;
class PaintingModeAttributeValue;
class KernelBitmap;
class BitmapFillAttribute;
class BitmapTranspFillAttribute;
class GRenderRegion;
class CCAttrMap;

/////////////////////////////////////////////////////////////////////
// feather defaults (for zoom 100%; ie 750 MP per PIXEL == PX_MP_VAL)
/////////////////////////////////////////////////////////////////////
#define DEFAULT_FEATHERSIZE_PIX				2
#define DEFAULT_FEATHERSIZE_MP				((MILLIPOINT) (DEFAULT_FEATHERSIZE_PIX * PX_MP_VAL))
#define MAX_FEATHERSIZE_MP MAX_SHADOW_BLUR * PX_MP_VAL		// MAX_SHADOW_BLUR defined in bshadow.h .
															// PX_MP_VAL defined in units.h = mp per pixels @ 100% zoom
#define DEFAULT_GAP_TOLERANCE_MP			((MILLIPOINT) (PX_MP_VAL * 0.75))
															// gaps less than 1.5 pixels wide @ 100% zoom 
															// will not have feathering along their edges
															// NB used as contour width hence min gap = 2*GapToleranceMP wide.

// NB Implications of MAX_FEATHERSIZE_MP:-
//	1	can't ever have greater than 40pixel feather size
//	2	at low zoom can't acheive full 40pix onscreen zoom
//		max pix @ view < 100% = 40pix * ViewScale
//		max pix @ view > 100% = 40pix

////////////
// debugging
////////////
// Create a bitmap copy of the feathered object for comparison with the bitmap generated
// via the offscreen rendering system (ie m_pOffscreenBitmapInfo/Bits inside OffscreenRenderingCompleted)
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

// Ensuring contour code works correctly
BOOL CheckLineAttrs(CCAttrMap* pAttrMap);
BOOL MakeLineAttributeCompleteForContouring(Node* Context, Node* NodeToModify, CCAttrMap* pAttrMap);

/////////////////////////////////////////////////////////////////////////////////////////////
//
//								AttributeValue classes
//
/////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************
>	class FeatherAttrValue : public AttributeValue
	Author:		Ilan_Copelyn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/01/2000
	Purpose:	
	SeeAlso:	
 ********************************************************************************************/

class FeatherAttrValue : public OffscreenAttrValue
{
	CC_DECLARE_DYNCREATE( FeatherAttrValue )

public:

	FeatherAttrValue();
	~FeatherAttrValue();

	// Standard functions required by Attribute framework 
	static BOOL Init();
	virtual void SimpleCopy(AttributeValue *);
//	virtual BOOL IsDifferent(AttributeValue*);  Not applicable
	virtual NodeAttribute *MakeNode();

	// Blending offscreen attrs
	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	// Generic attr rendering functions
	// (rely on GRenderRegion offscreen rendering system create and swap bitmaps)
	virtual void Render(RenderRegion *, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion *, BOOL);

	// Allow derived classes to overide integral parts of the offscreen bmp setup process
	virtual void GetMinimumOffscreenBmpDimensions(UINT32* RequiredWidth, UINT32* RequiredHeight);

	// Offscreen rendering functions.
	virtual void OffscreenRenderingCompleted(RenderRegion *pRender, LPBITMAPINFO lpBitmapInfo, LPBYTE lpBits, DocRect BitmapRect);
	virtual BOOL DoesOffscreenBmpRequireTransp(GRenderRegion* pGRR);
	virtual BOOL DoesOffscreenBMPCaptureBackground() {return TRUE;}		// Return TRUE if you can make this work
																		// During rotated printing (it works on screen)
	virtual BOOL CreateFeatherTransp(GRenderRegion* pGRR,
								     Path* pPath,
									 double dPixelWidth,
									 BitmapTranspFillAttribute** ppFeatherTransp,
									 KernelBitmap** ppFeatherBitmap);

private:
	// Internal helper functions used in rendering the feather bitmap
	KernelBitmap*	CreateFeatherBitmap(GRenderRegion* pGRR, double pixBlurDiameter);
	LPBITMAPINFO	CreateSilhouetteBitmap(GRenderRegion* GRR, LPBYTE* ppBmpBits, Path* pOutline = NULL);

	void SetupFeatherBitmapPalette(KernelBitmap* pFeatherBMP);
	void CreateBitmapFill(KernelBitmap* pBitmap, DocRect* dr, BitmapFillAttribute* BmpFill);
	void CreateBitmapFillRot90(KernelBitmap* pBitmap, DocRect* dr, BitmapFillAttribute* BmpFill);
	void CreateBitmapTranspFill(KernelBitmap* pFeather, DocRect* dr, BitmapTranspFillAttribute* BmpTranspFill);
	Path* GetVisibleBoundingPath();

public:
	// Creation/modification triggered by Feather Ops
	BOOL SetupFeather(Node* pNode, INT32 Width = DEFAULT_FEATHERSIZE_MP, UnitType type = MILLIPOINTS);
	BOOL ChangeFeatherProfile(CProfileBiasGain &biasgain);
	BOOL ChangeFeatherSize(INT32 , UnitType );

public:
	// Queries to support feather control UI updating (feather only)

	MILLIPOINT GetFeatherSize();
	double GetFeatherPixelSize(double fPixelWidth);
	CProfileBiasGain GetProfile() { return m_Profile; }
	CProfileBiasGain* GetProfilePtr() { return &m_Profile; }		// return pointer to profile

	// Set functions for saving/loading feather attrs and change operations
	MILLIPOINT SetFeatherSize(MILLIPOINT sz);
	void SetFeatherProfile(CProfileBiasGain &biasgain);
	virtual void SetLinkedNode(NodeRenderableBounded* pNode);

public:
	//-------------------------------------------------------------------------------------------------------------
	//									New attribute systems support
	//
	// Feather attributes are linked to the objects geometry in the following ways:-
	//		need bounding rects of objects to determine offscreen bitmap size
	//		need bounding/outer contour path of objects to create feather mask
	//

	virtual BOOL CanBeRenderedDirectly();

	// Caching and regenerating objects outercontour.
	BOOL GenerateOuterContour();
	Path* GetOuterContour() { return m_pOuterContour; }
	BOOL RegenerateOuterContourOnNextRedraw(UndoableOperation* pOp=NULL);
	void SetOuterContour(Path* pNewOuterContour) { m_pOuterContour = pNewOuterContour; }
	//-------------------------------------------------------------------------------------------------------------

private:
	//-------------------------------------------------------------------------------------------------------------
	//										Member Variables
	// Feather Attribute state members:
	CProfileBiasGain			m_Profile;
	MILLIPOINT					m_FeatherSize;
	MILLIPOINT					m_GapSize;
	Path*						m_pOuterContour;		// used only in rendering but is cached
														// updated by AllowOps
	DocRect						m_drFeatherBB;			// the rect we render the feather transp bmp through.

	BOOL						m_bCached;

	// The maximum feather size which we allow the user to play with.
	// This constant is defined at the top of fthrattr.cpp .
	static const MILLIPOINT MaxUserFeatherSize;

#ifdef _DEBUG_OFFSCREEN_PIXEL_WIDTH
	// Debugging
	KernelBitmap*				md_ShadBmp;	
#endif
};


/////////////////////////////////////////////////////////////////////////////////////////////
//
//								NodeAttribute classes
//
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class AttrFeather : public NodeAttribute
	Author:		Ilan_Copelyn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/01/2000
	Purpose:	
	SeeAlso:	
 ********************************************************************************************/

class AttrFeather : public NodeAttribute
{
	CC_DECLARE_DYNAMIC( AttrFeather )
	
public:
	AttrFeather() {}
	~AttrFeather() {}
	AttrFeather(Node* ContextNode,  
				 AttachNodeDirection Direction,    
				 BOOL Locked=FALSE, 
				 BOOL Mangled=FALSE,  
				 BOOL Marked=FALSE, 
				 BOOL Selected=FALSE) : 
		NodeAttribute(ContextNode, Direction, Locked, Mangled, Marked, Selected) {}

	// Traditional Node functionality
	virtual void Render( RenderRegion* pRender );
#ifdef _DEBUG
	void GetDebugDetails(StringBase* Str);
#endif

	// Traditional NodeAttribute functionality
	virtual AttributeValue* GetAttributeValue() { return &Value; }
	Node* SimpleCopy();
	virtual UINT32 GetAttrNameID();
	virtual AttrIndex GetAttributeIndex () { return ATTR_FEATHER; }
	virtual UINT32 GetNodeSize();
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);
	// nb op== is also involved in redundant attribute removal

	// Node charateristics tests
	virtual BOOL NeedsTransparency() const { return TRUE; }
	virtual BOOL IsAFeatherAttr() const;

	// OpFeather triggered functions
	BOOL DoFeather(Node* pNode, INT32 size = DEFAULT_FEATHERSIZE_MP, UnitType type = MILLIPOINTS);
	BOOL DoSetProfile(CProfileBiasGain bg);

	// prevent feathering in incompatible circumstances
	virtual SubtreeRenderState RenderSubtree(RenderRegion* pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);

	// support layering and remove redundant attrs
	virtual BOOL CanBeMultiplyApplied()		{ return TRUE; }
	virtual BOOL ShouldBeOptimized();

	// dynamic attribute functions and flags
	virtual void Transform(TransformBase& Trans);
	virtual BOOL Blend(BlendAttrParam* pBlendParam);
	virtual BOOL IsLinkedToNodeGeometry() { return TRUE; }
	virtual BOOL IsLinkedToThisNode(Node* pNode);

	// support dynamic attribute creation
	virtual BOOL PostDynCreateInit(CCAttrMap* pMap, Path* InkPath, CCRuntimeClass* pCreatorClass);
	virtual BOOL PostDynCreateInit(CCAttrMap* pMap, Node* pNode, CCRuntimeClass* pCreatorClass);
	virtual void PostDynCreateDeInit();

	// gla support
	virtual BOOL LinkedNodeGeometryHasChanged(UndoableOperation* pOp);
	virtual void NewlyCreatedDefaultAttr(NodeDocument* pNode);
	virtual BOOL LinkToGeometry(Node* pContext);
	virtual BOOL ContainsAttributeValue(AttributeValue* pVal);

	// Karim 15/11/2000
	// ID function for attributes which divert rendering offscreen, such as ourself.
	virtual BOOL IsAnOffscreenAttribute() { return TRUE; }
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents(NodeAttribute *pCopy);

public:

	FeatherAttrValue Value;

};


/////////////////////////////////////////////////////////////////////////////////////////////
//
//								Saving and loading
//
/////////////////////////////////////////////////////////////////////////////////////////////


/***********************************************************************************************

>	class FeatherRecordHandler : public CamelotRecordHandler

	Author:		Mark_Howitt (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/96
	Purpose:	Handles the reading of all feather records in the v2 file format
	SeeAlso:	-

***********************************************************************************************/

class FeatherRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(FeatherRecordHandler);

public:
	FeatherRecordHandler() : CamelotRecordHandler() {}
	~FeatherRecordHandler() {}

	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

private:
	BOOL HandleFeatherRecord(CXaraFileRecord* pCXaraFileRecord);
};

#endif //INC_FEATHRATTR
