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

// Header for the mould tools operations. These operations act as a common
// library for controlling various mould types. 

#ifndef INC_MOULDEDIT
#define INC_MOULDEDIT

#include "nodemold.h"

class MouldPerspective;
class NodeMouldPath;

#define OPTOKEN_DRAGVANISHPOINT _T("DragVanishPoint")

/*******************************************************************************************

>	class OpMouldLibSel: public SelOperation

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/01/95
	Purpose:	Provides a library of undoable functions for moulding objects.

********************************************************************************************/

class OpMouldLibSel: public SelOperation
{
	CC_DECLARE_DYNCREATE( OpMouldLibSel ) 

	public:
		OpMouldLibSel();

	protected:
		static BOOL	IsAMouldSelected(NodeMould** pNodeMould);

		BOOL		CreateNewMould(Path* pShape,
								   MouldSpace m_space,
								   BOOL FitSelection,
								   BOOL LockAspect);

		BOOL		AllMouldObjects(List* pNodeList);

		NodeMould*	DoCreateMould(Path* pShape, 
								  MouldSpace mSpace,
								  List* NodeList,
								  DocRect* pBounds,
								  BOOL ScaleToFit,
								  BOOL LockAspect);

		BOOL		DoRemoveAllMoulds(List* pNodeList);
		
		BOOL		DoRemoveMould(NodeMould* pMould, BOOL PutOnClip);
		
		BOOL		DoReplaceAllMoulds(	List* pNodeList,
										Path* pShape,
										MouldSpace mSpace,
										BOOL ScaleToFit,
										BOOL LockAspect);
		
		BOOL		DoReplaceMould(	NodeMould* pMould,
									Path* pShape,
									MouldSpace mSpace,
									BOOL ScaleToFit,
									BOOL LockAspect);
		
		BOOL		DoRecordGeometry(NodeMould* pMould);
		
		BOOL		DoCreateOrReplaceMould( SelRange* pSelected,
											Path* pShape,
											MouldSpace m_space,
											BOOL ScaleToFit,
											BOOL LockAspect);

	private:
		DocRect*	FindScaleRect(DocRect* pSRect, 
								  DocRect* pDRect,
								  BOOL ScaleToFit,
								  BOOL LockAspect);
		
		BOOL		LocaliseMouldAttributes(NodeMould* pMould);
		BOOL		LocaliseObjectAttrs(NodeRenderableInk* pParent, NodeRenderableInk* pInkNode);
		BOOL		HideAllMouldAttrs(NodeMould* pMould);

};



/*******************************************************************************************

>	class OpMouldLib: public UndoableOperation

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/01/95
	Purpose:	Provides a library of undoable functions for moulding objects.

********************************************************************************************/

class OpMouldLib: public UndoableOperation
{
	CC_DECLARE_DYNCREATE( OpMouldLib ) 

	public:
		OpMouldLib();

	protected:
		BOOL		DoRotateMould(NodeMould* pMould);
};



/********************************************************************************************

>	class RecordGeometryAction: public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/03/95
	Purpose:	This action records the current mould geometry being used by a particular
				mould node. Once recorded this allows the geometry to be changed. During
				undo the old geometry will be replaced but not initialised.
	SeeAlso:	NodeMould::SaveContext()

********************************************************************************************/

class RecordGeometryAction: public Action
{                                
	CC_DECLARE_DYNCREATE( RecordGeometryAction )

	public:
		 RecordGeometryAction(); 
		~RecordGeometryAction();
		virtual ActionCode Execute();   
	 
		static ActionCode Init(Operation* const pOp, 
							   ActionList* pActionList,
							   NodeMould* const pMould,
							   Action** NewAction);

		static ActionCode DoRecord(	Operation* const pOp, 
									NodeMould* const pMould);
 
	private:
		NodeMould*		pSavedMould;
		MouldGeometry*	pSavedGeometry;
};



/********************************************************************************************

>	class SaveDetachAction: public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/01/95
	Purpose:	This action saves and restores the detach flags inside a mould object
	SeeAlso:	-

********************************************************************************************/

class SaveDetachAction: public Action
{                                
	CC_DECLARE_DYNCREATE( SaveDetachAction )

	public:
		SaveDetachAction(); 
		virtual ActionCode Execute();   
		static ActionCode Save(Operation* const pOp, NodeMould* const pMould); 
		static ActionCode Init(Operation* const pOp, 
							   ActionList* pActionList,
							   NodeMould* const pMould,
							   Action** NewAction);
 
	private:
		NodeMould* 	pCurrMould;
		BOOL 		CurrDetached;
};


/********************************************************************************************

>	class InvalidateRectAction: public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/01/95
	Purpose:	When executed this action will Force a redraw of a bounding rectangle
				over a certain spread
	SeeAlso:	-

********************************************************************************************/

class InvalidateRectAction: public Action
{                                
	CC_DECLARE_DYNCREATE( InvalidateRectAction )

	public:
		InvalidateRectAction(); 
		virtual ActionCode Execute();   
	 
		static ActionCode DoRecord(	Operation* const pOp, 
									const DocRect& Rect,
									Spread* pSpread);

		static ActionCode Init(Operation* const pOp, 
							   ActionList* pActionList,
							   const DocRect& Rect,
							   Spread* pSpread,
							   Action** NewAction);

 
	private:
		DocRect InvalidRect;
		Spread* InvalidSpread;

};



/********************************************************************************************

>	class RedrawBoundsAction : public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/12/95
	Purpose:	An action to record the bounds of the mould. This op differs from
				RecordBoundsAction in that it does not use GetUnionBlobBounds() which is
				really bad for perspectives as this includes the vanishing points which
				results in a vast area of the document being redrawn. So we have to do
				everything separately
	SeeAlso:
		
********************************************************************************************/

class RedrawBoundsAction : public Action
{
	CC_DECLARE_DYNCREATE(RedrawBoundsAction)

	public:
		RedrawBoundsAction();
		virtual ActionCode Execute();
		
		static ActionCode DoRecord( Operation* pOp,
									NodeMould* WhichNode,
									BOOL Redraw);
		
		static ActionCode Init( Operation* pOp,
								ActionList* pActionList,
								NodeMould* WhichNode,
								Action** NewAction);

		static void RedrawNode(Operation* pOp, NodeMould* pNode);
	
	protected:
		NodeMould* ChangedNode;
};


/***********************************************************************************************

>	class OpDragOrigin : public UndoableOperation

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/01/95
	Purpose:	defines an operation for dragging perspective mould vanishing points around

***********************************************************************************************/

class OpDragOrigin : public UndoableOperation
{
	CC_DECLARE_DYNCREATE(OpDragOrigin);

	public:
		OpDragOrigin();

		static BOOL Init();
		static OpState GetState(String_256* Description, OpDescriptor*);

				void DoDragVanishPoint(Spread*, const DocCoord&, ClickModifiers, NodeMould*, BOOL);
		virtual void DragPointerMove(DocCoord Pos, ClickModifiers Mods, Spread* pSpread, BOOL bSolidDrag);
		virtual void DragFinished(DocCoord Pos, ClickModifiers Mods, Spread* pSpread, BOOL Success, BOOL bSolidDrag);
		virtual void RenderDragBlobs(DocRect, Spread*, BOOL bSolidDrag);
		virtual void GetOpName(String_256* OpName);

	private:
		DocRect CalcBlobClipRect();

	private:
		Spread*	 			StartSpread;
		NodeMould*			pEditMould;
		NodeMouldPath*		pEditMouldPath;
		Path*				pEditPath;
		MouldPerspective*	pEditGeometry;
		DocRect				EditRect;
		DocCoord			Blob;
};



/********************************************************************************************

>	class BuildMouldAction: public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/01/95
	Purpose:	When executed this action will get the mould to rebuild itself.
	SeeAlso:	-

********************************************************************************************/

class BuildMouldAction: public Action
{                                
	CC_DECLARE_DYNCREATE( BuildMouldAction )

	public:
		BuildMouldAction(); 
		virtual ActionCode Execute();   
	 
		static ActionCode DoRecord(	Operation* const pOp, NodeMould* pMould);

		static ActionCode Init(Operation* const pOp, 
							   ActionList* pActionList,
							   NodeMould* pMould,
							   Action** NewAction);

 	private:
		NodeMould* pBuildMould;
};



/********************************************************************************************

>	class StartRebuildMouldAction: public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/01/95
	Purpose:	When executed this action will get the mould to rebuild itself.
	SeeAlso:	-

********************************************************************************************/

class StartRebuildMouldAction: public Action
{                                
	CC_DECLARE_DYNCREATE( StartRebuildMouldAction )

	public:
		StartRebuildMouldAction(); 
		virtual ActionCode Execute();   
	 
		static ActionCode DoRecord(	Operation* const pOp, NodeMould* pMould);

		static ActionCode Init(Operation* const pOp, 
							   ActionList* pActionList,
							   NodeMould* pMould,
							   Action** NewAction);

 	private:
		NodeMould* pRebuildMould;
};


/********************************************************************************************

>	class EndRebuildMouldAction: public Action

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/01/95
	Purpose:	When executed this action will get the mould to rebuild itself.
	SeeAlso:	-

********************************************************************************************/

class EndRebuildMouldAction: public Action
{                                
	CC_DECLARE_DYNCREATE( EndRebuildMouldAction )

	public:
		EndRebuildMouldAction(); 
		virtual ActionCode Execute();   
	 
		static ActionCode DoRecord(	Operation* const pOp, NodeMould* pMould);

		static ActionCode Init(Operation* const pOp, 
							   ActionList* pActionList,
							   NodeMould* pMould,
							   Action** NewAction);

 	private:
		NodeMould* pRebuildMould;
};
#endif	

