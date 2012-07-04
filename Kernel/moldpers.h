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

// Header for the perspective mould shapes implementation

#ifndef INC_PERSPECTIVE
#define INC_PERSPECTIVE

#include "moldshap.h"
#include "nodemold.h"
#include "gmould.h"

#define PER_NUMCOORDS 4
#define PER_UNDEFINED ((INT32)(0x80000000))

typedef enum PerspectiveClick 
{
	PClick_DoNothing,
	PClick_EditVPoint0,
	PClick_EditVPoint1
};


/*******************************************************************************************

>	class GPerspective : Public GMould

	Author:		Gavin_Theobald (Xara Group Ltd) <camelotdev@xara.com> & Mike
	Created:	12/02/94
	Purpose:	The perspective function class.

********************************************************************************************/

class GPerspective : public GMould
{
	CC_DECLARE_MEMDUMP(GPerspective)

	public:
		GPerspective();

		virtual BOOL Redefine( POINT *P ) ;
		virtual void CopyShape( POINT *P ) ;
		virtual BOOL FitPath(CONST POINT *IPoints,	
							 CONST BYTE  *ITypes, 
							 DWORD ILength,
							 LPPOINT OPoints, 
							 LPBYTE  OTypes, 
							 DWORD OLength,	
							 BOOL Close = FALSE);

		BOOL Valid() ;
		BOOL WhichVanishingPoint(POINT v, BOOL& b) ;
		void VanishingPoints( POINT& a, POINT& b ) ;
		INT32 GetVPointState();
		void DragVanishingPoints( POINT& NewI, BOOL Flag, LPPOINT P ) ;

	private:
		virtual void ScaleView();
		virtual void CalcViewBBox();
		virtual void CalcViewConsts();
		virtual void Transform( DPOINT a, DPOINT& b ) ;

		void Intersect( DPOINT I, DPOINT P0, DPOINT P1, DPOINT P2, POINT& O ) ;

	private:
		POINT  P0, P1, P2, P3 ;
		DPOINT V0, V1, V2, V3 ;
		BOOL   I0flag, I1flag ;
		BOOL   I0pos,  I1pos  ;
		DPOINT I0, I1 ;
		DPOINT A, B ;
} ;




/*******************************************************************************************

>	class MouldPerspective: public MouldGeometry

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/12/94
	Purpose:	The perspective mould class. This mould implements a rectangular transform
				with true perspective.

********************************************************************************************/

class MouldPerspective: public MouldGeometry
{
	friend class RecordPerspectiveAction;

	CC_DECLARE_DYNAMIC(MouldPerspective);

	public:
		 MouldPerspective();
		~MouldPerspective();
	
		// funcs to initialise a perspective
		virtual BOOL Validate(Path* const pPath, UINT32& errorID);
		virtual BOOL Define(Path* const pPath, DocRect* const pRect);
		virtual MouldSpace Describe() {return MOULDSPACE_PERSPECTIVE;}
	    
		// functions to create a moulded object
	    virtual	BOOL MouldPathToPath(Path* pSourcePath, Path* PDestinPath);
	    virtual BOOL MouldBitmapToTile(KernelBitmap* pSourceBlit, KernelBitmap* pDestinBlit);
		virtual BOOL MouldPoint(DocCoord p, DocCoord& q);

        // functions to render an object through the mould
	    virtual	void MouldPathRender(Path* pPath, RenderRegion* pRegion);
	    virtual void MouldBitmapRender(KernelBitmap* pBlit, DocCoord* pParallel, RenderRegion* pRegion);

        virtual void RenderControlBlobs(RenderRegion* pRegion);
		virtual void RenderDragBlobs(Spread* pSpread);
		virtual void DisableControlBlobs();
		virtual void EnableControlBlobs();
		virtual void ToggleControlBlobs(Spread* pSpread);
		virtual DocRect GetBlobBoundingRect();
		virtual DocRect GetSourceRect();
		virtual UINT32 GetByteSize() const { return sizeof(MouldPerspective); };

	    virtual BOOL OnClick(DocCoord, ClickType, ClickModifiers, Spread*, NodeMould*);
		virtual BOOL OnMouseMove(DocCoord Coord, Spread* pSpread, ClickModifiers Mods, INT32* ctype, INT32* msgres);
		virtual void Transform(Path* const pPath, DocRect* const pRect, TransformBase& Trans );
		virtual MouldGeometry* MakeCopy();
		virtual ChangeCode RecordContext(UndoableOperation*);
		virtual ChangeCode RecordBlobs(UndoableOperation* pOp, Spread* pSpread);

	public:
		// none virtual functions local to this class.
		void GetVanishingPoints(DocCoord& p0, DocCoord& p1);
		void MoveVanishingPoints(DocCoord p0, DocCoord p1);
		void CopyShape(DocCoord* pCoords);
		BOOL MoveVanishingPoint(DocCoord OldPoint, DocCoord& NewPoint);
		DocRect CalcBlobClipRect(const DocCoord& p0);

		static BOOL WillBeValid(POINT* P);

	protected:
		BOOL CopyContents(MouldPerspective*);
		RECT BuildRectangle(DocRect* const pOrigBBox);

	private:
		void RenderGrid(Spread* pSpread);
		void RenderGrid(RenderRegion* pRegion);
		void RenderGridPoints(RenderRegion* pRegion);
		void RenderVanishingPoints(Spread* pSpread);
		void RenderVanishingPoints(RenderRegion* pRegion);
		void RenderVanishingPoint(Spread* pSpread, const DocCoord& dcPos);
		BOOL BuildShape(POINT* pPoints, DocRect* const pOrigBBox);
		void ShowVPoints();
		PerspectiveClick DetermineClickEffect(DocCoord PointerPos,Spread* pSpread);
		
	private:
		INT32 GridState;
		GPerspective Perspective;

};



/********************************************************************************************

>	class PerspectiveShapes

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/12/94
	Purpose:	The default perspective shapes class. This class provides a bunch of static
				functions to create some default shapes. All shapes are defined on a 
				(0,0),(72000,72000) coordinate system. 

********************************************************************************************/

class PerspectiveShapes
{
	public:
		static BOOL Rectangular(Path* pPath);
		static BOOL LeftWall(Path* pPath);
		static BOOL RightWall(Path* pPath);
		static BOOL Floor(Path* pPath);
		static BOOL Ceiling(Path* pPath);

	private:
		static BOOL MakeShape(Path* pPath, DocCoord* point);

};


/********************************************************************************************

	class RecordPerspectiveAction : public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/01/95
	Purpose:	This class records undo/redo information for the Perspective shape object.
	
********************************************************************************************/

class RecordPerspectiveAction : public Action
{
	CC_DECLARE_DYNCREATE(RecordPerspectiveAction)

	public:
		 RecordPerspectiveAction();
		~RecordPerspectiveAction();
		virtual ActionCode Execute();
		static ActionCode Init( Operation* pOp,
								ActionList* pActionList,
								MouldPerspective* pPerspective,
								Action** NewAction);
	private:
		MouldPerspective*	pCPerspective;
		POINT 				RecordArray[PER_NUMCOORDS];
};


#endif
