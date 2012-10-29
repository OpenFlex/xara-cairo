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

// The NodeMouldGroup renderable class

#ifndef INC_NODEMOULDGROUP
#define INC_NODEMOULDGROUP


//#include "selop.h"
#include "moldshap.h"

#define OPTOKEN_NODEMOULDGROUP _T("MouldGroupObject")

class ExtendParams;


/***********************************************************************************************

>	Union MouldedObjectUnion
	enum MouldedTypeEnum

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/12/94
	Purpose:	These structures describe the type of object held within the mould list item

***********************************************************************************************/

enum MouldedType {
	MOULD_UNDEFINED,
	MOULD_PATH,
	MOULD_BITMAP
};




/***********************************************************************************************

>	class NodeMouldGroup : public NodeGroup

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/12/94
	Purpose:	defines the structure of a mould group object. This object lives inside a 
				NodeMould and keeps track of all mould source objects. 

***********************************************************************************************/

class NodeMouldGroup: public NodeGroup
{

	CC_DECLARE_DYNAMIC( NodeMouldGroup );    

	public: 
		NodeMouldGroup(); 
		NodeMouldGroup(Node* ContextNode,  
				  AttachNodeDirection Direction,    
				  BOOL Locked=FALSE, 
				  BOOL Mangled=FALSE,  
				  BOOL Marked=FALSE, 
				  BOOL Selected=FALSE    
			     ); 

		~NodeMouldGroup();

		virtual void 	PreExportRender(RenderRegion* pRender);
		virtual BOOL 	ExportRender(RenderRegion* pRender);
		virtual SubtreeRenderState RenderSubtree(RenderRegion *pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);
		virtual BOOL 	NeedsToExport(RenderRegion* pRender, BOOL VisibleLayersOnly = FALSE,
									  BOOL CheckSelected = FALSE);

		// eor-drag rendering functions.
		// we do none, so they both do very little :o)
		virtual void RenderEorDrag(RenderRegion* pRender) {}
		virtual void RenderEorDragChildren(RenderRegion* pRender) {}

		// We don't want the hidden ink-nodes within a NodeMouldGroup to be accounted for
		// when the bounds for a drag are calculated.
		virtual DocRect GetEorDragBoundingRect() { return DocRect(0, 0, 0, 0); }

		virtual DocRect GetBoundingRect(BOOL DontUseAttrs=FALSE, BOOL HitTest=FALSE);
		virtual DocRect GetBlobBoundingRect();
				DocRect GetChildrensBounds(BOOL DontUseAttrs = FALSE);
		virtual void 	Transform(TransformBase&);
		virtual BOOL ChildrenAreEorDragRenderedByMe() { return TRUE; }

		// Other virtual functions
		virtual String Describe(BOOL Plural, BOOL Verbose); 
		virtual Node* SimpleCopy();  
	    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes
		virtual BOOL ShouldBeRendered() const;

		// Functions to deal with messages
		virtual BOOL OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
		virtual BOOL HidingNode();
		virtual BOOL ShowingNode();

		// Fuctions that allows ops and other nodes to inform this node of events on it's children
		virtual ChangeCode OnChildChange(ObjChangeParam* pParam);

		// Version 2 file format functions
		virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
		virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	// Karim MacDonald 25/11/1999
	// Extend functions.
	// Note that if a sub-class returns TRUE from IsTypeExtendible, it must
	// also provide complete implementations of ValidateExtend and Extend,
	// which should usually check/extend its children.
	// A MouldGroup node acts like a hidden node, as Mould extension is handled solely
	// by the relevant NodeMouldPath.
	public:
		virtual BOOL IsTypeExtendible() const { return FALSE; }
		virtual DocRect ValidateExtend(const ExtendParams& ExtParams)
		{
			return DocRect(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX);
		}
		virtual void Extend(const ExtendParams& ExtParams) {}

		virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

//	virtual BOOL IsValidEffectAttr(CCRuntimeClass* pAttrClass) const {return FALSE;}
	virtual BOOL IsValidEffectAttr(NodeAttribute* pAttr) const {return FALSE;}

	private:
		void CopyNodeContents(NodeMouldGroup* pCopyOfNode);

		// CAM/AW EPS output functions
		void PreExportNATEPS(RenderRegion* pRegion);
		BOOL PostExportNATEPS(RenderRegion* pRegion);
		void PreExportAWEPS(RenderRegion* pRegion);
		BOOL PostExportAWEPS(RenderRegion* pRegion);

	private:
		String_32 MouldGroupName; // The name of the mould group

};


#endif
