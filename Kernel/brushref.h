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


// The brushref class

#ifndef BRUSHREF
#define BRUSHREF

#include "nodebldr.h"


class BitmapFillAttribute;

/***********************************************************************************************

>	class BlendPathOffset

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/10/99
	Purpose:	Stores the translation of the blendpath to the centre of its parent object.
***********************************************************************************************/

class BlendPathOffset
{
public:
	BlendPathOffset() {m_XOffset = 0; m_YOffset = 0; m_Angle = 0; m_Magnitude = 0;}
	BlendPathOffset(MILLIPOINT X, MILLIPOINT Y) {m_XOffset = X; m_YOffset = Y; 
												CalculateAngleAndMagnitude();}

	void CalculateAngleAndMagnitude();

	// get the polar version
	void GetAngleAndMagnitude(double* pAngle, MILLIPOINT* pMagnitude);
	
	// work out what the offsets would be if it were rotated
	void RotateByAngle(double Angle, MILLIPOINT* pXoffset, MILLIPOINT* pYOffset);

public:  //data
	MILLIPOINT m_XOffset;
	MILLIPOINT m_YOffset;

protected: 
	// the polar representation
	double m_Angle;
	MILLIPOINT m_Magnitude;
};

/***********************************************************************************************

>	class BrushRef : public BlendRef

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/12/99
	Purpose:	'wrapper' for the blendref class for use with the brush.  Contains the information
				that the nodebrushmaker needs to draw the brush objects

***********************************************************************************************/

class BrushRef : public BlendRef
{
	CC_DECLARE_MEMDUMP(BrushRef);

public:
	typedef std::list<BlendPathOffset>	list;
	typedef list::iterator				iterator;

public:
	BrushRef();
	~BrushRef();

	BOOL Initialise(NodeRenderableInk* pInitNode);
	BlendPathOffset* GetFirstOffset( iterator *pHeadPosition );
	BlendPathOffset* GetNextOffset( iterator *pPosition );
	iterator GetEndPosition() { return m_OffsetList.end(); }
	
	DocRect GetBoundingRect();
	void DeleteBitmapFills();  // deletes bitmap fills, use only when camelot is closing
	void DeleteAttributesAndPath(); 
	void FreeAttributes();
	void TranslateTo(DocCoord Target);

	void TransformAttributes(TransformBase& Trans);

	// get the blendpaths to copy their data for rendering
	BOOL MakeCopiesForRendering();
	BOOL UpdateCopies();
	void DeleteRenderCopies();

	// returns the first and subsequent copies of the blendpaths
	Path* GetFirstCopyPath();
	Path* GetNextCopyPath();

	// returns the attribute map pertaining to the current blendpath
	CCAttrMap* GetCurrentAttributeCopy();

protected: //helper functions	
	BOOL SetBitmapFillFlags(); // tells any bitmap fills not to delete themselves normally as we will do it
	
protected:
	NodeRenderableInk*	m_pNode;
	List				m_BlendPathList;
	UINT32				m_NumBlendPaths;
	CMapPtrToPtr*		m_pBlendPathAttrMap;
	DocRect				m_CachedRect;
	// the list of transformations from the centre of the blendpath to the centre of 
	// the inknode.  Only really used when making brushes from groups.
	list				m_OffsetList;

	// our current blendpath for rendering
	BlendPath*			m_pCurrentBlendPath;
};


/***********************************************************************************************

>	class BrushRefBlender : public CC_CLASS_MEMDUMP

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/12/99
	Purpose:	An instance of this class is designed to take two BrushRef objects and blend together
				their paths and attributes, churning out a BlendedBrushRef object at the end.
				It essentially rips off a lot of what the NodeBlender does, except that instead of
				rendering anything or existing in the tree it just produces a blended object.

***********************************************************************************************/

class BrushRefBlender : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(BrushRefBlender);
public:
	BrushRefBlender();
	~BrushRefBlender();

	void SetBrushRef(BrushRef* pBrushRef, BOOL First);
	BrushRef* Blend(BrushRef* pStartBrushRef, BrushRef* pOther, double Ratio);

protected: //helper functions

	BOOL BlendPaths(BlendPath* pBlendPathStart,BlendPath* pBlendPathEnd,double BlendRatio);
	BOOL BlendAttributes(BlendPath* pBlendPathStart, BlendPath* pBlendPathEnd,
						CCAttrMap* pBlendedAttribMap,double BlendRatio);

	BOOL 		ReallocTempBuffers(UINT32 Size);
	void 		DeallocTempBuffers();

	// Access funcs for the path arrays
	DocCoord*  	GetCoordArray(UINT32 MinSize);
	PathVerb*  	GetVerbArray(UINT32 MinSize);
	PathFlags* 	GetFlagArray(UINT32 MinSize);
	UINT32*     	GetGBlendBuff(UINT32 MinSize);


protected: //data
		// the two brushrefs to be blended
	BrushRef* m_pStartBrushRef;  
	BrushRef* m_pEndBrushRef;

	// The following set of vars deal with arrays that are set up by the PreBlend() routine
	// Also, these arrays can also change by calls to the access funcs GetCoordArray(), GetVerbArray() and GetFlagArray()
	UINT32 		m_TempArraySize;
	DocCoord*	m_pTempCoords;
	PathVerb*	m_pTempVerbs;
	PathFlags* 	m_pTempFlags;
	UINT32		m_GBlendBuffSize;
	UINT32*		m_pGBlendBuff;
	UINT32		m_ArrayLength;
	
};	
#endif
