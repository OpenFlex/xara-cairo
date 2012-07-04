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


// class NodeRenderableInk

#ifndef INC_INK
#define	INC_INK

#include "node.h"
#include "clikmods.h"
#include "binds.h"
#include "bitmap.h"

class Spread;
class RenderRegion;
class BaseDocument;
class Cursor;
class ContextMenu;
class CCAttrMap;
class BlendNodeParam;
class AttrFillGeometry;
class AttrBrushType;
class AttrStrokeType;

/***********************************************************************************************

>    Class NodeRenderableInk: public NodeRenderableBounded

     Author:       Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
     Created:      19/5/93
     Base Classes: NodeRenderable, Node, CCObject
     Purpose:      This abstract class describes a renderable ink node. A property of Ink nodes 
     			   is that they should be rendered after their children have been rendered.   
				      
				   See the Node class for an important note about producing derived 
				   classes of Node.  

	 SeeAlso:      NodeRenderable
     Errors:       -                   
			    
***********************************************************************************************/


class NodeRenderableInk: public NodeRenderableBounded
{
	CC_DECLARE_DYNAMIC( NodeRenderableInk ) 

public:

	static BOOL Init();

	NodeRenderableInk(); 

	NodeRenderableInk(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE);

	virtual BOOL IsAnObject() const;		// yes, this is an object
	virtual BOOL IsSetCandidate() const;	// yes, this is a candidate for set membership
	virtual BOOL IsRenderedAsInk() const {return TRUE;}

	// virtual Functions to deal with bounding boxes
	//virtual void UpdateInkBoundingRect();

	virtual BOOL CanTransform();

	// Custom export rendering code.
	virtual BOOL ExportRender ( RenderRegion *pRender );

	// Virtual Selection functions
//	virtual void RenderFillBlobs(RenderRegion* pRender);
	virtual void RenderAppliedFillBlobs(RenderRegion* pRender);
	virtual void RenderArtisticBlobs(RenderRegion* pRender);
	virtual void RenderEorDrag( RenderRegion* );
	virtual void RenderEffectBlobs(RenderRegion* pRender);

	// fn which recursively eor renders all the children of this node
	virtual void RenderEorDragChildren(RenderRegion * pRender);

	// DMc - whether the eor drag for all children is dealt with by this node,
	virtual BOOL ChildrenAreEorDragRenderedByMe() { return FALSE; }

	virtual void ClearSubSelection( BOOL ReDraw );
	virtual BOOL CanSelectAsCompoundParent();
	virtual BOOL CanSelectAsSimple();
	
	// Functions for responding to clicks etc
	virtual BOOL OnClick(DocCoord, ClickType, ClickModifiers, Spread*);
	virtual BOOL OnMouseMove(const DocCoord&, Spread*, ClickModifiers);
	virtual BOOL GetStatusInfo(String_256** ppStatusText, Cursor** ppStatusCursor);
	virtual BOOL OnBlobPopUp(Spread*, DocCoord, ContextMenu*);
	virtual BOOL OnNodePopUp(Spread*, DocCoord, ContextMenu*);

	// Other virtual functions

	// These stand for things you can do to the selection in SelectAllInRect.
	enum SelStateAction { CLEAR, SET, TOGGLE };

	// Selection methods
	static void DeselectAll(BOOL RenderBlobs = TRUE, BOOL InformImmediate = TRUE);
	virtual void SelectInRect(const DocRect& Rect, SelStateAction st);

	// This could be a method of layer but I think it's best to keep it with DeselectAll()
	static void DeselectAllOnLayer(Layer* Layer);
	static void SelectAllInRect( DocRect, Spread*, SelStateAction st = SET );

	// Invalidates the bounding rectangle of the node 
	void RedrawObject(); 

	//Attribute methods 
	void ApplyAttributeToObject(NodeAttribute* Attribute, BOOL Redraw);
	BOOL ApplyAttributes(CCAttrMap* pAttribMap,BOOL RequiredAttrsOnly = FALSE); // Note: Also normalises the attrs after application

	// Used to determine if the node requires an AttribClass attribute to render itself
	virtual BOOL RequiresAttrib(CCRuntimeClass* AttribClass, BOOL Search = FALSE);
	// This function is more accurate than the above, some nodes require only specific instances of a 
	// class.
	virtual BOOL RequiresAttrib(NodeAttribute* pAttrib, BOOL Search = FALSE);
	// This fn is not to be confused with RequiresAttrib it determines if an attribute of type 
	// AttrType can be directly applied to the object.
	virtual BOOL CanAttrBeAppliedToMe(CCRuntimeClass* AttrType);
	// Before applying an attribute to an object this function should be called to return
	// the actual object the attribute should be applied to.
	virtual NodeRenderableInk* GetObjectToApplyTo(CCRuntimeClass* AttrType);
	// Every Ink object has an associated current attribute group, If an attribute is applied to
	// the object, and it needs to become current then the attribute group specified will get updated.
	virtual CCRuntimeClass* GetCurrentAttribGroup(); 

	NodeAttribute* GetChildAttrOfType(CCRuntimeClass* ReqdAttrib);
	BOOL HasAttrTypesOn(NodeRenderableInk* Object);
    
	BOOL CopyChildrenAsShapes(Node* pDestin);
		
	// Version 2 file format functions
	virtual BOOL ReadPostChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL ReadPostChildrenNative(BaseCamelotFilter* pFilter);

	virtual BOOL WriteBeginChildRecordsWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WriteBeginChildRecordsNative(BaseCamelotFilter* pFilter);
	virtual BOOL WriteEndChildRecordsWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WriteEndChildRecordsNative(BaseCamelotFilter* pFilter);

	virtual BOOL WriteBoundsRecord(BaseCamelotFilter* pFilter);
	virtual BOOL WillWriteBounds(BaseCamelotFilter* pFilter);

	// Progressive rendering & the new file format
	virtual	BOOL AreYouSafeToRender();

	// Find the first/next attribute from this object of the given run-time class (NB. not AttributeType),
	// or null if there isn't one.

	// return the applied brush attribute
	AttrBrushType* GetAppliedBrushAttribute();

	AttrStrokeType* GetActiveStroke();
		// check to see if we have a variable width stroke applied to us, and get the real path
	virtual NodePath* GetVariableWidthStrokePath();
	virtual NodePath* GetSmoothVariableWidthStrokePath();

	virtual BOOL GetAreaDetails(XLONG* pxlArea, XLONG* pXLPerimeter) {return FALSE;}

	virtual BOOL CanSupplyDirectBitmap() {return FALSE;}
	virtual BOOL GetDirectBitmap(RenderRegion* pRender, LPBITMAPINFO* plpInfo, LPBYTE* plpBits, DocRect* pRect, Matrix* pMat, double* pdRes) {return FALSE;}
	virtual BOOL RenderDirectBitmapState(RenderRegion* pRender) {return FALSE;}

private:
	BOOL	SafeToRender;

protected:
	// Function to help calculate the bounding rects of objects that contain a path
	BOOL CalculatePathBoundingRect(Path& BoundPath, BOOL DontUseAttrs, DocRect* pRect);

	virtual Node* SimpleCopy(void);
	
////////////////////////////////////////////////////////////////////////////////////////////
//	Hit-testing data and functions.

public:
	
	// perform simple hit-testing
	static NodeRenderableInk* FindSimpleAtPoint(Spread* pSpread, 
												DocCoord dcPoint, 
												Node* pHighNode = NULL,
												Node** ppInterruptNode = NULL);
	// read the documents screen-colour at the supplied hit-test position
	static NodeRenderableInk* FindSimpleAtPointForColourPicker(Spread* pSpread, 
															   DocCoord dcPoint,
															   Pixel32bpp& Pix,
															   Node* pHighNode = NULL,
															   Node** ppInterruptNode = NULL);
	// read the documents screen-colour at the supplied hit-test position (but only for the
	// supplied node)
	static NodeRenderableInk* FindColourForNodeRenderableAtPoint (Spread* pSpread,
																  DocCoord dcPoint,
																  Pixel32bpp& Pix,
																  Node* pThisNode,
																  AttrFillGeometry* pThisFill);
	// perform compound hit testing
	static NodeRenderableInk* FindCompoundAtPoint(Spread* pSpread, DocCoord dcPoint, Node* pHighNode = NULL);
	
	// This finds a compound object, eg. a group, that contains the given simple object.
	static NodeRenderableInk* FindCompoundFromSimple(NodeRenderableInk* pSimpleNode,
													 Node* pSiblingNode = NULL);

	// This finds a group including then given node, or NULL if it isn't in a group.
//	static NodeRenderableInk* FindHigherGroup(NodeRenderableInk* pStartNode);
	static NodeRenderableInk* FindInnerCompound(Node* pLowNode, Node* pHighNode);

	// Find which attributes are applied to a node...
	// ExcludeIndirectlyAppliedGLAs added by Ilan (17/5)
	BOOL FindAppliedAttributes(CCAttrMap* pAttribMap,
								INT32 nMax = 5000,
								INT32* nFound = NULL,
								BOOL ExcludeIndirectlyAppliedGLAs = FALSE,
								BOOL bStrictEffectStatus = TRUE) const;

	BOOL FindAppliedAttribute(CCRuntimeClass* AttribType, NodeAttribute** pAttrFound, BOOL bStrict = TRUE);
	NodeAttribute* FindAppliedAttribute(CCRuntimeClass* AttribType, BOOL bExcludeChildAttrs = FALSE, BOOL bStrict = TRUE);

//	virtual BOOL IsValidEffectAttr(CCRuntimeClass* pAttrClass) const {return FALSE;}
	virtual BOOL IsValidEffectAttr(NodeAttribute* pAttr) const {return FALSE;}

	// This function deletes all child attributes from the node which have the same type and value 
	// as the parent/sibling applied attributes.
	void DeleteAppliedAttributes(); 

	/// A function to return a set of the attribute types of all attribute children of
	// the object. 
	BOOL AddChildAttrTypesToSet(AttrTypeSet* pAttrTypeSet); 


	// This helper function allows the static attribute map, compiled during hit-testing,
	// to be reset...
	static void ClearAttribMap();

	// Allow nodes to modify the results of FindSimpleAtPoint
	virtual NodeRenderableInk* FindNodeAtPointHelper(const Spread* pSpread, const DocCoord dcPoint) {return this;}

private:

	// These are private data and functions used by the hit-testing code.
	static BOOL bUseSmartClicks;
	static BOOL AverageHitColour;

	static CCAttrMap* pAttribMap;		// the attribute look-up table
	static INT32 nFoundAttributes;			// how many entries currently in the table
	static INT32 nMaxAttributes;				// the most number of entries in the table

	void RenderAppliedAttributes(RenderRegion* pRegion) const;
	void RenderAppliedClipAttributes(RenderRegion* pRender) const;

	static Node* FindFirstHitTest(Spread* pStartSpread,
								  const DocRect& drClickRect,
								  CCAttrMap* pAttribMap,
								  BOOL bExcludeLayers,
								  Node* pHighNode = NULL );

	static Node* FindNextHitTest(Node* pNode,
								 const DocRect& drClickRect,
								 CCAttrMap* pAttribMap,
								 BOOL bExcludeLayers,
								 BOOL bSkipChildren = FALSE);
	
	static BOOL HitTestChildren(Node* pNode,
								const DocRect& drClickRect,
								BOOL bExcludeLayers);
   		 

////////////////////////////////////////////////////////////////////////////////////////////
// Attribute optimisation routines

public:

	BOOL MakeAttributeComplete(Node* Root = NULL, 
							    BOOL CheckForDuplicates = TRUE, 	
								AttrTypeSet* pAffectedAttrTypes = NULL, 
								BOOL IncludeDefaults = FALSE,
								BOOL bIncludeEffectAttrs = FALSE);

	void NormaliseAttributes();   // Removes superfluous attributes

	BOOL FactorOutCommonChildAttributes(BOOL Global = FALSE, 
										AttrTypeSet* pAffectedAttrTypes = NULL);

	BOOL LocaliseCommonAttributes(BOOL CheckForDuplicates = FALSE, 
								  BOOL Global = FALSE, 
								  AttrTypeSet* pAffectedAttrTypes = NULL,
								  BOOL RecursiveDownwards = FALSE);

public:
	// these two are used to tell compound nodes (or anyone else for that matter)
	// that the blend step is beginning
	// tells nodes that the blend step is beginning
	virtual BOOL BeginBlendStep(BlendNodeParam * pParam) { return TRUE; }

	// tells nodes that the blend step has finished
	virtual BOOL EndBlendStep(BlendNodeParam * pParam) { return TRUE; }

private:
	BOOL FactorOutCommonChildAttrHelper(BOOL Global, 
											  AttrTypeSet* pAffectedAttrTypes);

	BOOL LocaliseCommonAttrHelper(BOOL CheckForDuplicates, 
							 	  BOOL Global, 
							 	  AttrTypeSet* pAffectedAttrTypes,
								  BOOL RecursiveDownwards = FALSE);
							   	

	void DeleteLocalisedAttributes(BOOL Global = FALSE,
								   AttrTypeSet* pAffectedAttrTypes = NULL);

	void DeleteFactoredOutAttribs(BOOL Global = FALSE,
								  AttrTypeSet* pAffectedAttrTypes = NULL);

	    /*
	// The following are sub-functions of MakeAttributeComplete
    BOOL FindRequiredAttribTypes(List* ReqdAttribListPtr); 
    BOOL FindRequiredAttribsTypesRec(Node* SubTree, 
									 MarkedStack* AttribStackPtr, 
									 List* ReqdAttribListPtr);
	*/
	BOOL FindReqdAttribs(List* ReqdAttribList); 
	void RemoveSuperfluousAttribs(); 

	// fns for attribute optimisation called by FactorOutCommonChildAttributes()
	BOOL FindCommonAttributesToFactorOut(CommonAttrSet* CommonAttributeSet);

public:
	virtual BOOL SetParentLayerAsEdited();

public:
	virtual BOOL IsSeeThrough(BOOL CheckIndirectAttrs);
}; 

#endif	
