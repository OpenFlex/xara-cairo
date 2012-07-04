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

/*
 *  */


#ifndef INC_SELOP
#define INC_SELOP         

#include "undoop.h"


/********************************************************************************************

>	class SelOperation: public UndoableOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94
	Purpose:	A SelOperation  
				
				  
	SeeAlso:	TransOperation

********************************************************************************************/

class CCAPI SelOperation:public UndoableOperation
{
	CC_DECLARE_DYNCREATE( SelOperation )   

public: 
  	SelOperation(); 
	virtual ~SelOperation(); 
 	BOOL DoStartSelOp(BOOL RenderEndSelStateBlobs,
 					  BOOL RenderStartSelStateBlobs=TRUE,
 					  BOOL UndoRenderEndSelStateBlobs=FALSE,
 					  BOOL UndoRenderStartSelStateBlobs=FALSE
					 );

	virtual void End(); 

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return TRUE; }

	virtual BOOL GetStarted() const { return m_bStartCalled; }

	// --------------------------------------------------------------------------------------
	// Phil 16/02/2005
	//
	// Functions for applying attributes to nodes
	// Previously in OpApplyAttribstoSelected
	// Moved here so that any op can apply attributes and have the correct actions added
	// to its own undo lists
	//
public:
	static BOOL  DoApply(SelOperation* pOp,
						 Node* CurrentNode,
						 NodeAttribute* Attrib, 
						 BOOL Mutate, 
						 BOOL InvalidateRegion = TRUE, 
						 BOOL KeepExistingCharacteristics = TRUE,
						 BOOL bOptimise = TRUE,
						 BOOL* AttribWasRequired = NULL,
						 BOOL* pbCanDiscardUndo = NULL
						 );
	static BOOL InvalidateNodeRegion(	SelOperation* pOp,
										NodeRenderableBounded* CurrentNode, 
										NodeAttribute* Attrib, 
										BOOL Mutate);
	static BOOL ReleaseCachedForAttrApply(NodeRenderableBounded* pNode, BOOL bEffectRootOnly);

	virtual BOOL DoAttributesSelected(List& AttribsToApply, UINT32 OpName, BOOL bPasteAttrs);
	virtual BOOL DoApplyAttribsToSelection(OpParam* pOpParam, BOOL bClearIfNoneApplied = FALSE);
	virtual BOOL DoApplyToSelection(List* Attribs, List* AttrGroupList, BOOL* pAttribWasRequired);
	virtual BOOL DoApply(Node* CurrentNode,
						 NodeAttribute* Attrib, 
						 BOOL Mutate, 
						 BOOL InvalidateRegion = TRUE, 
						 BOOL KeepExistingCharacteristics = TRUE,
						 BOOL* AttribWasRequired = NULL,
						 BOOL* pbCanDiscardUndo = NULL
						 );

protected:
	virtual BOOL ApplyAttributeToBrush(Node* pCurrentNode, NodeAttribute* pAttr);
	virtual BOOL ApplyLineWidthToBrush(AttrBrushType* pAttrBrush, NodeRenderableInk* pBrushedNode,
								NodeAttribute* pAttr);
	virtual BOOL ApplyStrokeColourToBrush(AttrBrushType* pAttrBrush, NodeRenderableInk* pBrushedNode);
	virtual BOOL ApplyTransparencyToBrush(AttrBrushType* pAttrBrush, NodeRenderableInk* pBrushedNode);

	virtual BOOL ApplyBrushAttr(Node* pCurrentNode, AttrBrushType* pAttrBrush);	

private:
	BOOL DoEndSelOp();   // Called by End()
	// A pointer to a selection state object required by RestoreSelections actions. 
	// Created in DoStartSelectionOp()	
	SelectionState* SelState; 

	// Flag so that derived member funcs can determine whether StartSelOp has been called
	// on this op yet
	BOOL m_bStartCalled;

	// Used in the End() method to dermine if we should save the selection state at the end of 
	// the operation or not. 
	static BOOL RenderEndSelStateBlobs;
	static BOOL RenderStartSelStateBlobs; 
	static BOOL UndoRenderEndSelStateBlobs;
	static BOOL UndoRenderStartSelStateBlobs; 
 
};							  

#endif 
	 
