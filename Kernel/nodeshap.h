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

// NodeSimpleShape class. This provides a base class for all simple primitve shapes
// eg, Rectangles and Ellipses.

#ifndef INC_NODESHAP
#define INC_NODESHAP


class RenderRegion;
class Spread;
class BecomeA;


/***********************************************************************************************

>	class NodeSimpleShape : public NodeRenderableInk

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/93
	Purpose:	A NodeSimpleShape is the base class for several primitive shapes that are
				bounded by a Parallelogram. This class contains 2 Pure Virtual functions that
				need to be re-written in base classes. These should be the only functions that
				need re-writting in most cases. They build a path for the shape given a
				bounding parallelogram.

***********************************************************************************************/

class NodeSimpleShape : public NodeRenderableInk
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(NodeSimpleShape);

public:
	NodeSimpleShape(); 
	
	NodeSimpleShape(Node* ContextNode,  
				AttachNodeDirection Direction,  
				BOOL Locked = FALSE, 
				BOOL Mangled = FALSE,  
				BOOL Marked = FALSE, 
				BOOL Selected = FALSE    
			  );

	// Initialise the path
	BOOL SetUpPath(INT32 RequiredSize=12, INT32 BlockSize=12);
	virtual Node* SimpleCopy();
	void CopyNodeContents(NodeSimpleShape* NodeCopy);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Functions to re-build the path from the parallelogram
	virtual void CreateShape(DocRect NewRect);
	virtual void UpdateShape();

	// virtual Functions to deal with bounding boxes
	virtual DocRect	GetBoundingRect(BOOL DontUseAttrs=FALSE, BOOL HitTest=FALSE);
	virtual DocRect GetBlobBoundingRect();

	// Rendering Functions
	virtual void Render( RenderRegion* pRender );
	virtual void RenderEorDrag( RenderRegion* );

	// Selection functions.
	virtual void RenderObjectBlobs(RenderRegion* pRender);
	virtual void RenderTinyBlobs(RenderRegion* pRender);

	// Functions to transform the shape
	virtual void Transform( TransformBase& );

	// Information functions
	virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes
 
	// Make Shapes functions
	virtual BOOL CanBecomeA(BecomeA* pBecomeA);
	virtual BOOL DoBecomeA(BecomeA* pBecomeA);

	// Debugging function
	#ifdef _DEBUG
		void	ShowDebugTreeDetails() const;
	#endif
	void GetDebugDetails( StringBase* Str );

	// Functions to deal with messages
	virtual BOOL OnClick( DocCoord, ClickType, ClickModifiers, Spread* );

	// Function to decide if a coord is close to any of the control points
	BOOL IsNearControlHandle(DocCoord Coord, INT32* CoordNum);
 
	// Decides what to do about a drag on a blob
	virtual void HandleBlobDrag( DocCoord&, Spread*, INT32 );

	// The natty Snap functions
	virtual BOOL Snap(DocCoord* pDocCoord);
	virtual BOOL Snap(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);
	virtual BOOL SnapToCoords(DocCoord* pDocCoord);

	virtual double GetRotationAngle();

	// Karim MacDonald 25/11/1999
	// Extend functions.
	// Note that if a sub-class returns TRUE from IsTypeExtendible, it must
	// also provide complete implementations of ValidateExtend and Extend,
	// which should usually check/extend its children.
public:
	virtual BOOL IsTypeExtendible() const { return TRUE; }
	virtual DocRect ValidateExtend(const ExtendParams& ExtParams);
	virtual void Extend(const ExtendParams& ExtParams);

	// Data vars
public:
	Path	 InkPath;			// The path that contains the shape
	DocCoord Parallel[4];		// 4 coords to represent the parallelogram that the shape fits in
}; 




#endif	// INC_NODESHAP




