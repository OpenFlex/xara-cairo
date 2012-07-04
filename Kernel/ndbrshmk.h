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


//Nodebrushmaker class

#ifndef INC_NDBRSHMK
#define INC_NDBRSHMK

//#include "tranform.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "docrect.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ink.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "paths.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "blendatt.h"
#include "nodebldr.h"
//#include "trans2d.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "brushref.h"
#include "brshcomp.h"

class RenderRegion;
class GRenderBrush;
class Spread;
class BecomeA;
class HandleBecomeA;
class CCAttrMap;
class Progress;
class BaseCamelotFilter;

class NodeBrush;
class NodeBrushPath;
class CPathPointInfo;

/*
enum PathOffset {OFFSET_NONE,
				 OFFSET_ALTERNATE,
				 OFFSET_LEFT,
				 OFFSET_RIGHT,
				 OFFSET_RANDOM};

const MILLIPOINT MIN_BRUSH_SPACING = 10;
const MILLIPOINT MAX_BRUSH_SPACING = 10000;
const UINT32       MAX_BRUSH_OBJECTS = 20;
*/





/********************************************************************************************

>	class NodeBrushMaker: public NodeRenderableInk

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/10/99
	Purpose:	The NodeBrushMaker class

********************************************************************************************/

class NodeBrushMaker : public NodeRenderableInk
{
	CC_DECLARE_DYNCREATE(NodeBrushMaker);

public:
	typedef std::vector< CPathPointInfo > CListOfPointsToRender;

public:
	NodeBrushMaker();
	NodeBrushMaker(Node* ContextNode,  
			  AttachNodeDirection Direction,    
			  BOOL Locked=FALSE, 
			  BOOL Mangled=FALSE,  
			  BOOL Marked=FALSE, 
			  BOOL Selected=FALSE    
		     ); 
	
	~NodeBrushMaker();
 
	BOOL InitialiseInk(NodeRenderableInk** pInkNode, const UINT32 NumInkNodes = 1, Progress* pProgress = NULL);
	BOOL InitialisePath(NodeBrushPath* pBrushPath);
	void InitialiseBrushArray(UINT32 NumObjects);
	// get the bounding rect 
	virtual DocRect GetBoundingRect(BOOL DontUseAttrs = FALSE, BOOL HitTest = FALSE);
	virtual DocRect GetBlobBoundingRect();

	// the main render function
	virtual void Render(RenderRegion* pRender);
	
	// blob rendering
//	void RenderObjectBlobs(RenderRegion* pRender);
	

	virtual void RenderEorDrag( RenderRegion* );
	//  require transparency ?
//	virtual BOOL NeedsTransparency() const;

//	virtual String Describe(BOOL Plural, BOOL Verbose = TRUE);

	// transformation function
	virtual void Transform( TransformBase& Trans );

	// Version 2 file format functions
//	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
//	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	// Information functions
	virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes
 


	// access functions
	BOOL SetPositionRandomness(double Value);
	BOOL SetAttributeRandomness(double Value);
	BOOL SetSizeRandomness(double Value);
	BOOL SetAlignmentRandomness(double Value);

	double GetPositionRandomness();
	double GetAttrRandomness();
	double GetSizeRandomness();
	double GetAlignmentRandomness();

	void SetGRenderBitmap(GRenderBrush* pGRenderBitmap);
	MILLIPOINT GetBrushSpacing();
	BOOL       SetBrushSpacing(MILLIPOINT Spacing);
	PathOffset GetPathOffsetType();
	MILLIPOINT GetPathOffsetValue();
	void	   SetPathOffsetType(PathOffset Offset);
	void	   SetPathOffsetValue(MILLIPOINT Value);
	void	   SetBlendRef(BlendRef* pBlendRef);
	BOOL	   GetRotated();
	void	   SetRotated(BOOL Rotate);
	void	   SetUsePathCache(BOOL Value);

	void SetNumberOfSteps(INT32 Steps);
	BOOL GetStartCoord(DocCoord* Coord);
	void SetStartCoord(DocCoord Coord);
	void RenderStep(INT32 StepNum, Spread* pSpread, CPathPointInfo Point);

	NodeRenderableInk* GetInkNode();
	BOOL PrepareToRender(Spread* pSpread);
	void FinishRender();
	void RecalculateMaxStep();
	void ClearListOfPointsToRender();

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);
	
protected:
	// return a copy of this node
	virtual Node* SimpleCopy();
	void RenderAttributes(RenderRegion* pRender, CCAttrMap* pAttrMap);
	
	void CopyNodeContents(NodeBrushMaker* pCopyOfNode);
	void ResetMembers();
	void RandomizeShape(Trans2DMatrix* TransformMatrix);
	void RandomizeAttributes();
	
	DocCoord SetPosition( CPathPointInfo OriginalPoint, UINT32 AltValue, 
		CListOfPointsToRender::iterator *ListPosition );
	
	BOOL GetGRenderBitmap(DocRect* pRenderRect, GRenderBrush** ppGRender, Spread* pSpread);
	BOOL DrawViewToRenderRegion(Spread* pSpread, RenderRegion* pRender);
	
	void AddPointsInRectToList(DocRect Rect);
	void AddAllPointsToList();
	void RenderBrushObjectAtPoint(CPathPointInfo Point, RenderRegion* pRender);


	// Debugging function
	#ifdef _DEBUG
	void	ShowDebugTreeDetails() const;
	#endif
	void GetDebugDetails( StringBase* Str );
	void GetDebugDetails( StringBase* Str,BlendRef* pBlendRef );


	String_32		   m_BrushMakerName;
	
	NodeRenderableInk* m_pInkNode;			// the node used to create the brush
	BlendRef*		   m_pBlendRef;			// creates and stores the blendpath objects that are rendered
	NodeBrushPath*     m_pNodeBrushPath;     // the path along which to draw the brush
	GRenderBrush* 	   m_pGRender;           // the render region that we use to render the brush objects 
											// with as they are being drawn
	
	GRenderBrush		   *m_pGRenderDIB;
	CListOfPointsToRender	m_ListOfPointsToRender;	// used to store the list of points we need to render
	std::vector< BrushRef * > m_BrushRefPtrArray;		// holds multiple blendrefs used to create the brush objects 
														// (necessary to have an array in case we want to use it as an
														// object sprayer)
	
	MILLIPOINT		   m_BrushSpacing;  // the distance between each brush object


	// the amount of randomness in the brush objects
	double			   m_PositionRandomness;
	double			   m_AttrRandomness;
	double			   m_SizeRandomness;
	double             m_AlignmentRandomness;
	UINT32			   m_AltValue;
	PathOffset		   m_PathOffsetType;
	MILLIPOINT		   m_PathOffsetValue;
	CCAttrMap*         m_pAttrMap;
	
	INT32			   m_BrushStep;  // the current step that is rendering
	INT32               m_MaxStep;	 // the maximum step to render

	MILLIPOINT		   m_CurrentDistance; // the distance along the path that we have reached whilst rendering
	DocCoord           m_StartCoord;      // the starting coordinate of the nodebrushpath

	DocRect            m_BrushBoundingRect;
	

	BOOL			   m_bRandomizeShape;
	BOOL			   m_JustTransformed;  // has the node just been transformed?
	
	BOOL			   m_bFirstRender;
	BOOL			   m_bRotate;

	BOOL			   m_bTile;           // do we tile our fills?
	BOOL			   m_bUsePathCache;   // do we use the cached path processor of the nodebrushpath?

	// the list of transformations from the centre of the blendpath to the centre of 
	// the inknode.  Only really used when making brushes from groups.
	std::vector< BlendPathOffset >	m_OffsetList;
private:

};

#endif
