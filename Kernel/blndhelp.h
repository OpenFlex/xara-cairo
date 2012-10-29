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

// ppbevel - Definition of Blend helper class

#ifndef INC_BLENDHELP
#define INC_BLENDHELP

#include "pathpcs.h"

class BlendNodeParam;
class NodeCompound;

/********************************************************************************************

>	class BlendHelpers : public CCObject

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com> Mc
	Created:	23/2/2000

	Purpose:	This encapsulates the blend functions which are needed to blend compound
				nodes (e.g. shadows etc)

	SeeAlso:	NodeRenderableInk::Blend

********************************************************************************************/
class BlendHelpers : public CCObject
{
	CC_DECLARE_DYNAMIC(BlendHelpers);

public:
	BlendHelpers();
	~BlendHelpers();

	// the blending code (stripped from NodeBlender)
	// get the attribute map at a particular blend step
	BOOL BlendAttributes(BlendNodeParam * pParam, CCAttrMap * pAttrMap);

	// gives the path at a particular blend step
	BOOL BlendPaths(BlendNodeParam * pParam, Path * pPath);

private:
	Trans2DMatrix* GetRotateMatrix(NodeRenderableBounded* pNode,double Angle);

	/////////////////////////////////////////////////////////////////
	// Access funcs for the path arrays
	// Straight out of the blender
	DocCoord*  	GetCoordArray(UINT32 MinSize);
	PathVerb*  	GetVerbArray(UINT32 MinSize);
	PathFlags* 	GetFlagArray(UINT32 MinSize);
	UINT32*     	GetGBlendBuff(UINT32 MinSize);

	BOOL 		ReallocTempBuffers(UINT32 Size);
	void 		DeallocTempBuffers();

	// The following set of vars deal with arrays that are set up by the PreBlend() routine
	// Also, these arrays can also change by calls to the access funcs GetCoordArray(), GetVerbArray() and GetFlagArray()
	UINT32 		m_TempArraySize;
	DocCoord*	m_pTempCoords;
	PathVerb*	m_pTempVerbs;
	PathFlags* 	m_pTempFlags;
	UINT32		m_GBlendBuffSize;
	UINT32*		m_pGBlendBuff;
	UINT32		m_ArrayLength;
} ;

/********************************************************************************************

>	class CompoundNodeBlendBecomeA : public BecomeA

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com> Mc
	Created:	23/2/2000

	Purpose:	Gets the compound node to wrap up any nodes passed to the passback in a
				copy of its tree structure

	SeeAlso:	NodeRenderableInk::Blend

********************************************************************************************/
class CompoundNodeBlendBecomeA : public BecomeA
{
public:
	// inputs -
	// pCompound	-	the compound node
	//
	CompoundNodeBlendBecomeA(BecomeAReason Reason,
					CCRuntimeClass* pClass, 
					UndoableOperation* pOp, 
					BOOL Sel,
					NodeCompound * pCompound,
					BecomeA * pBecomeA) : BecomeA(Reason, pClass, pOp, Sel)
	{
		m_pCompound  = pCompound;
		m_pBecomeA   = pBecomeA;
//		m_Count = 0;
		m_NumPathNodes = 0;
	}					

	BOOL IsCompoundBlendBecomeA() { return TRUE; }

	BOOL PassBack(NodeRenderableInk* pNewNode,
		NodeRenderableInk* pCreatedByNode,
		CCAttrMap* pAttrMap=NULL);

//	void ResetCount() { m_Count = 0; }
	void SetNumPathNodes(UINT32 NumPaths) { m_NumPathNodes = NumPaths; }


private:
	NodeCompound	  * m_pCompound;
	BecomeA			  * m_pBecomeA;
//	UINT32				m_Count; // how many nodes we have converted
	UINT32				m_NumPathNodes; // how many nodes we are going to convert on this pass
} ;

/********************************************************************************************

>	class SumAllPathsElem : public ListItem

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/2/2000
	Purpose:	Element for the list in SumAllPathsPathProcessor
********************************************************************************************/
class SumAllPathsElem : public ListItem
{
	CC_DECLARE_DYNCREATE(SumAllPathsElem);

public:
	SumAllPathsElem()
	{
		m_pAttrMap = NULL;
		m_Path.Initialise();
	}

	SumAllPathsElem(Path * pPath, CCAttrMap * pAttrMap);
	~SumAllPathsElem();

	Path * GetPath() { return &m_Path; }
	CCAttrMap * GetAttrMap() { return m_pAttrMap; }
private:
	Path m_Path;
	CCAttrMap* m_pAttrMap;
} ;

/********************************************************************************************

>	class SumAllPathsPathProcessor : public PathProcessor

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/2/2000
	Purpose:	All paths are placed in the linked list, with their associated attribute
				maps
********************************************************************************************/
class SumAllPathsPathProcessor : public PathProcessor
{
	CC_DECLARE_DYNAMIC(SumAllPathsPathProcessor);
public:
	// inputs - whether we should draw the path passed into the ProcessPath or not
	SumAllPathsPathProcessor(BOOL bDrawOriginalPaths = FALSE);
	
	~SumAllPathsPathProcessor();

	virtual void ProcessPath(Path *pPath,
							 RenderRegion *pRender,
							 PathShape ShapePath = PATHSHAPE_PATH);

	List * GetList() { return &PathList; }

	void SetEnabled(BOOL bEnabled) { m_bEnabled = bEnabled; }

	// CGS:  we need to be to insert paths into the list when doing convert to editable shapes
	// (this is due to the fact that we don't have a RenderRegion - and therefore cannot push
	// a path processor!)
	void InsertSumAllPathsElem (SumAllPathsElem* newElem);

private:
	List PathList;
	BOOL m_bDrawPaths;
	BOOL m_bEnabled;
} ;



#endif

