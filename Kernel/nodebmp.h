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


// Node representing a bitmap object.

#ifndef INC_NODEBMP
#define INC_NODEBMP


#include "noderect.h"
//#include "xpehost.h"	// For OPTOKEN_XPE_EDIT

class SelOperation;
class AttrBitmapTranspFill;

/********************************************************************************************

>	class NodeBitmap : public NodeRect

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	A class for including bitmap objects within the tree.
	SeeAlso:	NodeRect, KernelBitmap

********************************************************************************************/

class NodeBitmap : public NodeRect
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(NodeBitmap);

public:
	NodeBitmap(); 	
	NodeBitmap(	Node* ContextNode,
				AttachNodeDirection Direction,
				BOOL Locked = FALSE,
				BOOL Mangled = FALSE,
				BOOL Marked = FALSE,
				BOOL Selected = FALSE
			  );

	virtual Node* SimpleCopy();
	void CopyNodeContents(NodeBitmap* NodeCopy);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);
	virtual String Describe(BOOL Plural, BOOL Verbose);

	virtual KernelBitmap *EnumerateBitmaps(UINT32 Count);
	virtual double GetEffectiveBitmapMinDPI(KernelBitmap* pBitmap);
	virtual BOOL ReplaceBitmap(KernelBitmap* pOrigBitmap, KernelBitmap* pNewBitmap);

	// Function for interrogation by clipboard to determine exportable data types
	virtual BOOL SupportsClipboardFormat(InternalClipboardFormat *Format) const;

	UINT32 GetBitmapDPI();

	// Render the bitmap
	virtual void Render( RenderRegion* pRender );
	virtual void PreExportRender(RenderRegion* pRender );
	virtual BOOL ExportRender( RenderRegion* pRender ); 
	virtual INT32 GetSizeOfExport(Filter*);

	virtual BOOL RequiresAttrib(NodeAttribute* pAttrib, BOOL Search = FALSE);
	virtual BOOL ApplyDefaultBitmapAttrs(UndoableOperation* pOp, AttrBitmapTranspFill* pTranspBitmap = NULL);

	// Popup menus
	virtual	BOOL OnNodePopUp(Spread* pSpread, DocCoord PointerPos, ContextMenu* pMenu);

	// Information functions
	virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes
	virtual BOOL IsABitmap() const;
	virtual BOOL NeedsTransparency() const;

	// Make Shapes functions
	virtual BOOL CanBecomeA(BecomeA* pBecomeA);
	virtual BOOL DoBecomeA(BecomeA* pBecomeA);

	// AllowOp stuff
	BOOL AllowOp(ObjChangeParam*, BOOL);
	BOOL MakeContoneBitmap(UndoableOperation*);

	static KernelBitmap* CheckGreyscaleBitmap(KernelBitmap* pBitmap, UINT32 PromptID, UINT32 OkID);

	KernelBitmapRef BitmapRef;

	virtual KernelBitmapRef* GetBitmapRef() { return &BitmapRef; }
	virtual KernelBitmap* GetBitmap();

	virtual BOOL HidingNode();
	virtual BOOL ShowingNode();

	virtual void SetStartColour(DocColour*);
	virtual void SetEndColour(DocColour*);

	virtual DocColour* GetStartColour();
	virtual DocColour* GetEndColour();

	virtual BOOL GetApplyContoneColour() {return ApplyContoneColour;};

	// For render region capabilities
	BOOL HasSimpleOrientation(RenderRegion *);

	virtual BOOL OnClick(DocCoord PointerPos,
						 ClickType Click,
						 ClickModifiers ClickMods,
						 Spread* pSpread);

PORTNOTE("other","Change GetDefaultOpToken - OPTOKEN_XPE_EDIT reference")
	// Find out the optoken of the default operation for this node. (See EditSelectionOp and Return hotkey.)
	virtual TCHAR* GetDefaultOpToken() {return _T("None");}
		
	virtual void SetAspectRatio(double dExWidth, double dExHeight, BOOL bPathAndFill);
	virtual BOOL ReleaseCached(BOOL bAndParents = TRUE, BOOL bAndChildren = TRUE, BOOL bSelf = TRUE, BOOL bAndDerived = TRUE);

	// Functions to give effects info about this instance of the bitmap so that
	// they can operate in the the upright bitmap domain, then do the appropriate
	// instance transformation at the top of the effects stack
	virtual DocRect GetOriginalBitmapRect();
	virtual Matrix GetInstanceTransform();

	virtual BOOL CanSupplyDirectBitmap() {return TRUE;}
	virtual BOOL GetDirectBitmap(RenderRegion* pRender, LPBITMAPINFO* plpInfo, LPBYTE* plpBits, DocRect* pRect, Matrix* pMat, double* pdRes);

protected:
	virtual BOOL HasBitmapAttrs();

public:
	// new file format export functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
	
protected:
	DocColour Colour;
	DocColour EndColour;

	BOOL ApplyContoneColour;
}; 

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

// Optoken for the CreateNodeBitmap operation
#define OPTOKEN_CREATENODEBITMAP _T("CreateNodeBitmap")	

/********************************************************************************************

>	class OpCreateNodeBitmap: public UndoableOperation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/3/95
	Purpose:	Creates a new Node Bitmap, at a specific position on the page.
	SeeAlso:	-

********************************************************************************************/

class CCAPI OpCreateNodeBitmap: public UndoableOperation
{         
	CC_DECLARE_DYNCREATE( OpCreateNodeBitmap );

public:
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		

	void DoWithParam(OpDescriptor* OpDesc, OpParam* pOpParam);	
	virtual void GetOpName(String_256* OpName); // Overloaded so that we can store the undo string in 
												// the operation rather than the OpDescriptor.  

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return TRUE; }
};  

/********************************************************************************************

>	class ChangeBitmapPtrAction : public Action

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/94
	Purpose:	An action which undoes the modification of Grad Fill data. This action can
				be used for undoing changing control points.
	SeeAlso:	-

********************************************************************************************/

class ChangeBitmapPtrAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeBitmapPtrAction)

public:
	ChangeBitmapPtrAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							Action** NewAction);
	void StoreChanges(NodeBitmap* pBmpNode);

	KernelBitmapRef* GetBitmapRef() { return &BitmapRef; }
	KernelBitmap* GetBitmap() { return BitmapRef.GetBitmap(); }

protected:

	NodeBitmap* 		pChangedBmpNode;
	KernelBitmapRef 	BitmapRef;
};

#endif  // INC_NODEBMP


