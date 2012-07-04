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

// Header for the envelope mould shapes implementation

#ifndef INC_ENVELOPE
#define INC_ENVELOPE

#include "moldshap.h"
//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "nodemold.h"
#include "gmould.h"

#define ENV_NUMCOORDS		12
#define ENV_NUMCOORDS2X2	24
#define ENV_MAXCOORDS 		24

/********************************************************************************************

>	class MouldEnvelopeBase	: public MouldGeometry

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/12/94
	Purpose:	The envelope mould node. Provides control over a coons patch shape made
				from 4 connected 3rd order bezier splines.

********************************************************************************************/

class MouldEnvelopeBase : public MouldGeometry
{
	friend class RecordEnvelopeAction;

	CC_DECLARE_DYNAMIC(MouldEnvelopeBase);

	public:
		 MouldEnvelopeBase();
		~MouldEnvelopeBase();

		virtual void RenderControlBlobs(RenderRegion* pRegion);
		virtual void RenderDragBlobs(Spread* pSpread);
		virtual void DisableControlBlobs();
		virtual void EnableControlBlobs();
		virtual void ToggleControlBlobs(Spread* pSpread);

		// functions to create a moulded object
		virtual	BOOL MouldPathToPath(Path* pSourcePath, Path* PDestinPath);
	    virtual BOOL MouldBitmapToTile(KernelBitmap* pSourceBlit, KernelBitmap* pDestinBlit);
		virtual BOOL MouldPoint(DocCoord p,DocCoord& q);

        // functions to render an object through the mould
	    virtual	void MouldPathRender(Path* pPath, Spread* pSpread);
	    virtual void MouldBitmapRender(KernelBitmap* pBlit, DocCoord* pParallel, RenderRegion* pRegion);

		virtual DocRect GetSourceRect();

	protected:
		BOOL	Define(Path* const pPath, DocRect* const pOrigBBox, INT32 ncoords);

		RECT 	BuildRectangle(DocRect* const pOrigBBox);
		BOOL 	BuildShape(POINT* pPoints, DocRect* const pOrigBBox);
		BOOL 	ConvertShape(INT32 ncoords, POINT* dPoints, Path* const pPath, const INT32 numcoords);

		void 	RenderGrid(Spread* pSpread);
		void 	RenderGrid(RenderRegion* pRegion);
		void 	RenderGridPoints(RenderRegion* pRegion);

		BOOL	ValidMouldingPath(INT32 ncoords, INT32 nelements, Path* const pPath, UINT32& errorID);
		static  BOOL WillBeValid(INT32 ncoords, POINT* P);

	protected:
		GMould	*pEnvelope;

	private:
		INT32 	BlobState;
};



/********************************************************************************************

>	class MouldEnvelope	: public MouldEnvelopeBase

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/12/94
	Purpose:	The envelope mould node. Provides control over a coons patch shape made
				from 4 connected 3rd order bezier splines.

********************************************************************************************/

class MouldEnvelope : public MouldEnvelopeBase
{
	CC_DECLARE_DYNAMIC(MouldEnvelope);

	public:
		 MouldEnvelope();
		~MouldEnvelope();

		virtual BOOL		Initialise();
		
		virtual BOOL		Validate(Path* const pPath, UINT32& errorID);
		virtual BOOL		Define(Path* const pPath, DocRect* const pRect);
		virtual BOOL		MakeValidFrom(Path **Out, Path *In, INT32 *CornersHint = 0);
		virtual MouldSpace	Describe() {return MOULDSPACE_ENVELOPE;}

		virtual void		Transform(Path* const pPath, DocRect* const pRect, TransformBase& Trans);
		virtual ChangeCode	RecordContext(UndoableOperation*);
		virtual UINT32		GetByteSize() const { return sizeof(MouldEnvelope); };
		
		virtual MouldGeometry* MakeCopy();

	public:
		// none virtual functions local to this class.
		static BOOL WillBeValid(POINT* P);

	protected:
		BOOL CopyContents(MouldEnvelope* pGeom);

	private:
		const INT32 EnvNumCoords;
};



/********************************************************************************************

>	class MouldEnvelope2x2 : public MouldEnvelopeBase

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/11/95
	Purpose:	Another envelope mould. Provides control over a coons patch shape made
				from 2x2 4 connected 3rd order bezier splines.

********************************************************************************************/

class MouldEnvelope2x2 : public MouldEnvelopeBase
{
	CC_DECLARE_DYNAMIC(MouldEnvelope2x2);

	public:
		 MouldEnvelope2x2();
		~MouldEnvelope2x2();

		virtual BOOL		Initialise();

		virtual BOOL		Validate(Path* const pPath, UINT32& errorID);
		virtual BOOL		Define(Path* const pPath, DocRect* const pRect);
		virtual BOOL		MakeValidFrom(Path **Out, Path *In, INT32 *CornersHint = 0);
		virtual MouldSpace	Describe() {return MOULDSPACE_ENVELOPE2X2;}

		virtual void 		Transform(Path* const pPath, DocRect* const pRect, TransformBase& Trans);
		virtual ChangeCode	RecordContext(UndoableOperation*);
		virtual UINT32 		GetByteSize() const { return sizeof(MouldEnvelope2x2); };

		virtual MouldGeometry* MakeCopy();

	public:
		// none virtual functions local to this class.
		static BOOL WillBeValid(POINT* P);

	protected:
		BOOL CopyContents(MouldEnvelope2x2* pGeom);

	private:
		const INT32 EnvNumCoords;
};


/********************************************************************************************

>	class EnvelopeShapes

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/12/94
	Purpose:	The default envelope shapes class. This class provides a bunch of static
				functions to create some default shapes. All shapes are defined on a 
				(0,0),(72000,72000) coordinate system. 

********************************************************************************************/

class EnvelopeShapes
{
	public:
		static BOOL Rectangular(Path* pPath);
		static BOOL Rectangular2x2(Path* pPath);
		static BOOL Circular(Path* pPath);
		static BOOL Concave(Path* pPath);
		static BOOL Banner(Path* pPath);

	private:
		static BOOL MakeEllipse(DocRect* pRect, Path* pPath,PathFlags* pFlags);
};



/********************************************************************************************

	class RecordEnvelopeAction : public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/01/95
	Purpose:	This class records undo/redo information for the Envelope shape object.
	
********************************************************************************************/

class RecordEnvelopeAction : public Action
{
	CC_DECLARE_DYNCREATE(RecordEnvelopeAction)

	public:
		 RecordEnvelopeAction();
		~RecordEnvelopeAction();
		virtual ActionCode Execute();
		static ActionCode Init( Operation* pOp,
								ActionList* pActionList,
								MouldEnvelopeBase* pRecEnvelope,
								Action** NewAction);
	private:
		MouldEnvelopeBase* pCEnvelope;
		POINT RecordArray[ENV_MAXCOORDS];
};

#endif
