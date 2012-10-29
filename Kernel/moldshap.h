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

// Header for the mould tool shapes implementation

#ifndef INC_MOULDSHAPES
#define INC_MOULDSHAPES

#include "nodemold.h"

class KernelBitmap;
// class NodeMould;

#define MOULD_V1THRESHOLD		1024
#define MOULD_V2THRESHOLD		32
#define MOULD_CURRTHRESHOLD		32


struct DPOINT {
	double x, y ;
} ;

/********************************************************************************************

>	class MouldGeometry

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/94
	Purpose:	An abstract base class for mould shapes.

********************************************************************************************/

class MouldGeometry	: public CCObject
{
	CC_DECLARE_DYNAMIC(MouldGeometry);

	public:
		MouldGeometry();
		
		// Shape initialisation functions
		virtual BOOL Validate(Path* const pPath, UINT32& errorID) {return FALSE;}
		virtual BOOL Define(Path* const pPath, DocRect* const pRect) {return FALSE;}
		virtual MouldSpace Describe() {return MOULDSPACE_UNDEFINED;}
		virtual BOOL MakeValidFrom(Path **Out, Path *In, INT32 *CornersHint = 0) {return FALSE;}

		// functions to create a moulded object
	    virtual	BOOL MouldPathToPath(Path* pSourcePath, Path* PDestinPath) {return FALSE;};
	    virtual BOOL MouldBitmapToTile(KernelBitmap* pSourceBlit, KernelBitmap* pDestinBlit) {return FALSE;};
		virtual BOOL MouldPoint(DocCoord p,DocCoord& q) { q=p; return FALSE; }

        // functions to render an object through the mould
	    virtual	void MouldPathRender(Path* pPath, RenderRegion* pRegion);
	    virtual void MouldBitmapRender(KernelBitmap* pBlit, DocCoord* pParallel, RenderRegion* pRegion);

		// functions to render mould blobs
        virtual void RenderControlBlobs(RenderRegion* pRegion) {};
		virtual void RenderDragBlobs(Spread* pSpread) {};
		virtual void DisableControlBlobs() {};
		virtual void EnableControlBlobs() {};
		virtual void ToggleControlBlobs(Spread* pSpread) {};

		// functions concerned with bounding boxes
		virtual DocRect GetBlobBoundingRect() { return DocRect(0,0,0,0); };
		virtual void GetDebugDetails(StringBase*) {};
		virtual DocRect GetSourceRect() { return DocRect(0,0,0,0);};

		// function to actually do things with a mould
        virtual BOOL OnClick(DocCoord, ClickType, ClickModifiers, Spread*, NodeMould*);
		virtual BOOL OnMouseMove(DocCoord, Spread*, ClickModifiers, INT32*,INT32*);
		virtual void Transform(Path* const pNewPath, DocRect* const pRect, TransformBase& Trans) {};
		virtual MouldGeometry* MakeCopy();
		virtual ChangeCode RecordContext(UndoableOperation*) {return CC_OK;}
		virtual ChangeCode RecordBlobs(UndoableOperation*, Spread*) {return CC_OK;}
		virtual UINT32 GetByteSize() const { return sizeof(MouldGeometry); };

		virtual void SetThreshold(const INT32 t);
				INT32 GetThreshold() const { return MouldThreshold; }

	protected:
		BOOL 	CopyContents(MouldGeometry* pGeom);
		DocRect ConvRectToDocRect(RECT& rect0);
		RECT	ConvDocRectToRect(DocRect& rect0);

	protected:
		INT32	MouldThreshold;
};



/********************************************************************************************

>	class MouldTransform : public TransformBase

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/01/95
	Purpose:	Defines the mould transform class. This class is used by a moulder when
				it needs to ask other objects to transform themselves geometrically.
				It provides various functions for nodes to call to transform coordinates
				or paths.

********************************************************************************************/

class MouldTransform : public TransformBase
{
	CC_DECLARE_DYNAMIC(MouldTransform)

	public:
		 MouldTransform(MouldGeometry* pGeom);
		~MouldTransform();

		virtual void Transform( DocCoord* Coords, INT32 NumCoords);
		virtual BOOL IsInvertable() { return FALSE; }
		virtual BOOL TransformPath( Path* const pSource, Path* pDestin);

	private:
		MouldGeometry* pMouldGeom;

};

#endif


