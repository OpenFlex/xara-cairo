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

#ifndef INC_NODESHADOW
#define INC_NODESHADOW

#ifdef BUILDSHADOWS

#include "nodecont.h"
#include "nodebmp.h"

//#include "combshps.h"
//#include "ink.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "paths.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "fillattr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "biasgain.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "becomea.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "pathpcs.h"
//#include "biasgain.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "gconsts.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class NodeShadowController;
class TrapsList;
class CShadowerFlat;
class CBitmapShadow;
class ExtendParams;
class NodeShadowPassback;

class GRenderRegion;
class GRenderRegionWrapper;
class BitmapTranspFillAttribute;


/***********************************************************************************************

>	class NodeShadow : public NodeRenderableInk

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/94
	Purpose:	

***********************************************************************************************/

class NodeShadow : public NodeRenderableInk
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(NodeShadow);

public:
	NodeShadow(); 
	~NodeShadow(); 
	
	NodeShadow(Node* ContextNode,  
				AttachNodeDirection Direction,  
				BOOL Locked = FALSE, 
				BOOL Mangled = FALSE,  
				BOOL Marked = FALSE, 
				BOOL Selected = FALSE    
			  );

	// Initialise the shape
	BOOL SetUpShape();
	virtual Node* SimpleCopy();
	void CopyNodeContents(NodeShadow* NodeCopy);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	virtual BOOL IsAShadow() const { return TRUE; } 

	// we don't want to have brush attrs applied to us.
	virtual BOOL CanAttrBeAppliedToMe(CCRuntimeClass* pAttribClass);

	// virtual Functions to deal with bounding boxes
	virtual DocRect	GetBoundingRect(BOOL DontUseAttrs = FALSE, BOOL HitTest = FALSE);
	virtual DocRect GetBlobBoundingRect();

	// Rendering Functions
	virtual void Render( RenderRegion* pRender );
	virtual void RenderEorDrag( RenderRegion* );

	virtual void PreExportRender( RenderRegion* pRender ); 
	virtual BOOL ExportRender( RenderRegion* pRender ); 

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
	virtual BOOL CanWriteChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL CanWriteChildrenNative(BaseCamelotFilter* pFilter);

	// Selection functions.
	virtual void RenderObjectBlobs(RenderRegion* pRender);
	virtual void RenderTinyBlobs(RenderRegion* pRender);

	// Functions to transform the shape
	virtual void Transform( TransformBase& );

	// Information functions
	virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes
	virtual String Describe(BOOL Plural, BOOL Verbose);
	virtual BOOL NeedsTransparency() const {return TRUE;}
 
	// Make Shapes functions
	virtual BOOL CanBecomeA(BecomeA* pBecomeA);
	virtual BOOL DoBecomeA(BecomeA* pBecomeA);

	// Debugging function
	void ShowDebugTreeDetails() const;
	void GetDebugDetails( StringBase* Str );

	// Functions to deal with messages
	virtual BOOL OnClick( DocCoord, ClickType, ClickModifiers, Spread*);
	virtual BOOL OnNodePopUp(Spread* pSpread, DocCoord PointerPos, ContextMenu* pMenu);

	// The natty Snap functions
	virtual BOOL Snap(DocCoord* pDocCoord);
	virtual BOOL Snap(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);
	virtual BOOL SnapToCoords(DocCoord* pDocCoord);

	void DeleteCurrentShadowStuff();
	void DeleteCache();
	void DeleteAndRefreshCache();
	virtual NodeCompound* GetParentController() const;

	virtual BOOL PostImport();
	BOOL PostDuplicate(UndoableOperation* pOp);		// function called after node has been copied.

	virtual BOOL NeedsParent(Node* pNode) const;

	virtual BOOL AllowOp(ObjChangeParam *pParam, BOOL SetOpPermissionState = TRUE,
												 BOOL DoPreTriggerEdit = TRUE);

	virtual BOOL MarqueeSelectNode() const { return FALSE; }

	virtual BOOL ReleaseCached( BOOL bAndParents = TRUE,
								BOOL bAndChildren = TRUE,
								BOOL bSelf = TRUE,
								BOOL bAndDerived = TRUE);

protected:
	void InitialiseMemberVars();
	virtual void RenderBitmap(RenderRegion* pRender);

public:
	BOOL GenerateShadow();

	BOOL GenerateShadowForBlends(List * pList, RenderRegion * pRegion);

	void UpdateAfterWallOffset();

	BOOL GenerateShadowBitmap(KernelBitmap* pSilhouetteBmp, const double pixBlurDiameter);
	BOOL GenerateSelectionBitmap(Range * pSelRng);
	void HaveChangedShadow() { m_bHaveTransformed = TRUE; }
	void SetBitmapShadowRendering(BOOL OnOrOff) { m_RenderBitmaps = OnOrOff; }
	BOOL AmDoingACopy() { return m_bAmCopying; }
	void SetAmCopying() { m_bAmCopying = TRUE; }
	void SetAmLoading() { m_bAmLoading = TRUE; }

	// Get shadow darkness, from 0.0 (transparent) to 1.0 (opaque).
	double	GetDarkness()				{ return m_dDarkness; }

	void	SetDarkness(double Darkness);

	// Get shadow transparency, from 0 (opaque) to 255 (transparent).
	UINT32 GetTransp()			{ return (UINT32)(0.5 + 255.0 * (1.0 - m_dDarkness)); }

	// Set shadow transparency, from 0 (opaque) to 255 (transparent).
	void SetTransp(UINT32 Transp)	{ SetDarkness( (double)(255 - Transp) / 255.0 ); }

	void SetBiasGain(CProfileBiasGain &gain);
	CProfileBiasGain &GetBiasGain();
	CProfileBiasGain* GetBiasGainPtr();

	// Karim MacDonald 25/11/1999
	// virtual Extend functions; see declaration/implementation in Node.
public:
	virtual BOOL IsTypeExtendible() const { return TRUE; }
	virtual DocRect ValidateExtend(const ExtendParams& ExtParams);
	virtual void Extend(const ExtendParams& ExtParams);

	virtual INT32 EstimateNodeComplexity (OpParam* details);

#ifdef NEW_SHADOW_RENDER
public:
	BOOL	MakeShadow(LPBITMAPINFO lpInfo, LPBYTE lpBits, DocRect orect);
	BOOL	RenderShadow(RenderRegion* pRender);
	BOOL	NeedsRemake();
	BOOL	TransformShadow(TransformBase& Trans);

#endif

protected:
	KernelBitmap*				m_ShadowBitmap;
	BitmapTranspFillAttribute*	m_pBMPTransFill;
	Path					    m_Path;
	Path						m_NonTranslatedPath;
	
	INT32	m_ShadowWidth;
	INT32	m_ShadowHeight;

	BOOL	m_bHaveTransformed;
	BOOL	m_RenderBitmaps;
	BOOL	m_bAmCopying;
	BOOL	m_bAmLoading;
	double	m_dDarkness;

	DocRect	m_SelectedRect;
	INT32		m_PreviousBlur;
	
	BOOL SetupTransFill();

	// turns the 24 - bit kernel bitmap into an 8 bit greyscale
	BOOL Create8BitBitmap(KernelBitmap * pSrcBitmap, KernelBitmap ** ppDestBitmap);

	void CreateBitmapPath(const DocRect& drInkForShadowing, double PixelWidth, const double pixBlurDiameter);

	// DMc the bitmap shadower (not the COM shadower flat)
	CBitmapShadow * m_pShadower;

	// the bitmap offset for floor shadows
	INT32 m_BitmapXOffset;

	CProfileBiasGain m_BiasGain;

	NodePath * CreateShadowPassbackNode();

	BOOL RenderBitmapForDisplay(RenderRegion* pRegion, List* pList = NULL);
	BOOL RenderBitmapForDisplay();

	BOOL ApplyProfileToShadowBitmap();

	// shadow cache state information.
	// a note of the pixel width which was requested the last time we generated a shadow.
	MILLIPOINT m_LastRequestedPixWidth;

	// shadow cache state information.
	// a note of the quality setting at which our last shadow was generated.
	enum Quality::Fill m_LastQualitySetting;

	// we need to store the actual width (in millipoints) of a pixel
	// from our shadow bitmap. this takes into account any scaling
	// of the bitmap if there is not enough memory to do a full scale shadow.
	double m_LastActualPixWidth;
};



/********************************************************************************************

>	class BitmapShadower

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/10/2000

	Purpose:	Encapsulates the shadow silhouette bitmap creation process.

	See also:	NodeShadow::RenderBitmapForDisplay(), NodeShadow::GenerateShadowBitmap().

********************************************************************************************/
class BitmapShadower
{
public:
	static BitmapShadower* CreateSilhouetteBitmap(	NodeShadowController* pControl,
													GRenderRegion* pGRR = NULL,
													List* pList = NULL );

	// get a ptr to the shadow bitmap.
	// the caller of this function takes responsibility for deleting the returned KernelBitmap.
	KernelBitmap* GetSilhouetteBitmap()
	{
		KernelBitmap* pBmp = m_pSilhouetteBitmap;
		m_pSilhouetteBitmap = NULL;
		return pBmp;
	}

	// get the blur diameter (in pixels) for the shadow bitmap.
	double			GetPixBlurDiameter()	const { return m_pixBlurDiameter; }

	// get actual pixel width at which the shadow bitmap should be rendered, to come out the right size.
	double			GetActualPixelWidth()	const { return m_ActualPixelWidth; }

	// get the onscreen bounds of the shadow bitmap.
	DocRect			GetBitmapBounds()		const { return m_drShadowedBounds; }

	~BitmapShadower();

private:
	BitmapShadower();

	BOOL Initialise(NodeShadowController* pControl, GRenderRegion* pGRR, List* pList);
	BOOL DoCreateSilhouetteBitmap();

	BOOL CalculateBoundsAndScale1();
	BOOL CalculateBoundsAndScale2WithGRR();
	BOOL CalculateBoundsAndScale2NoGRR();
	BOOL CreateOffscreenRR();
	BOOL RenderShadowedNodeOffscreen();

	GRenderRegion*			m_pGRR;

	NodeShadowController*	m_pControl;
	NodeShadow*				m_pShadow;
	NodeRenderableInk*		m_pShadowedNode;
	List*					m_pShadowedList;
	enum ShadowType			m_ShadowType;

	DocRect					m_drShadowedBounds;
	double					m_ShadowScaleFactor;
	double					m_ActualPixelWidth;
	double					m_pixBlurDiameter;

	GRenderRegionWrapper*	m_pRendWrap;
	GRenderRegion*			m_pOffscreenRR;

	KernelBitmap*			m_pSilhouetteBitmap;
};



/***********************************************************************************************

>	class NodeShadowBecomeA : public BecomeA

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/12/199
	Purpose:	Does the become A for generating all the path so that the NodeShadowPassback
				will work

***********************************************************************************************/
class NodeShadowBecomeA : public BecomeA
{
public:
	NodeShadowBecomeA(	BecomeAReason Reason,
					CCRuntimeClass* pClass, 
					UndoableOperation* pOp, 
					BOOL Sel,
					Path * pSummedPath) : BecomeA( Reason, pClass, pOp, Sel)
	{
		m_pPath = pSummedPath;
	}

	virtual BOOL PassBack(NodeRenderableInk* pNewNode,NodeRenderableInk* pCreatedByNode,CCAttrMap* pAttrMap);
private:
	Path * m_pPath;
};



#endif	// BUILDSHADOWS

#endif  // NODESHADOW
