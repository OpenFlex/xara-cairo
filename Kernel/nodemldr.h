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

// The NodeMoulder renderable class

#ifndef INC_NODEMOULDER
#define INC_NODEMOULDER

//#include "ink.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "rndrgn.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "selop.h"
//#include "becomea.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "group.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#define OPTOKEN_NODEMOULDER _T("MoulderObject")

class NodeMouldBitmap;
class MouldGeometry;
class NodeBitmap;
class NodeMouldGroup;

class ExtendParams;

/***********************************************************************************************

>	class NodeMoulder : public NodeRenderableInk

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/12/94
	Purpose:	defines the structure of a moulder object. The moulder exists only as a child
				of a mould object, controlling the production and manipulation of moulded 
				versions of associated siblings. ie for each child (C) of a mould object, we 
				create a moulder object (M).
				M controls the actual production and rendering of paths and bitmaps generated
				by C. 
	SeeAlso:	Mould (the parent object)

***********************************************************************************************/

class NodeMoulder : public NodeGroup
{
	// Give my name out in memory dumps
	CC_DECLARE_DYNAMIC( NodeMoulder )

	public:
		 NodeMoulder(); 
		~NodeMoulder();

		NodeMoulder(Node* ContextNode,  
					AttachNodeDirection Direction,  
					BOOL Locked = FALSE, 
					BOOL Mangled = FALSE,  
					BOOL Marked = FALSE, 
					BOOL Selected = FALSE );      
			      
		// Get the node to set itself up
		BOOL Initialise(NodeRenderableInk* ContextNode);

		// virtual admin functions
		virtual Node* SimpleCopy();						// Copies a node
		virtual UINT32 GetNodeSize() const;			 	// Returns size of node in bytes

		// virtual Functions to deal with bounding boxes
		virtual DocRect	GetBoundingRect(BOOL DontUseAttrs=FALSE, BOOL HitTest=FALSE);
		virtual DocRect GetBlobBoundingRect();
				DocRect GetChildBBox(BOOL DontUseAttrs);

		// Rendering Functions
		virtual void PreExportRender( RenderRegion* pRender ); 
		virtual BOOL ExportRender( RenderRegion* pRender ); 
				void Render(RenderRegion* pRender);
		virtual BOOL NeedsToExport(RenderRegion* pRender, BOOL VisibleLayersOnly = FALSE,
								   BOOL CheckSelected = FALSE);

		// 'Make shapes' functions
		virtual BOOL CanBecomeA(BecomeA* pBecomeA); 
		virtual BOOL DoBecomeA(BecomeA* pBecomeA); 
		
		virtual BOOL AllowOp(ObjChangeParam* pParam, BOOL SetOpPermissionState = TRUE,
													 BOOL DoPreTriggerEdit = TRUE);

	    // Responce to clicks from tools
		virtual BOOL OnClick( DocCoord, ClickType, ClickModifiers, Spread * );

		// Other virtual functions
		virtual String Describe(BOOL Plural, BOOL Verbose); 
		virtual void Transform( TransformBase& );				// Transforms this object

		#ifdef _DEBUG
			void ShowDebugTreeDetails() const;					// Debugging function
		#endif
		void GetDebugDetails( StringBase* Str );

		virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

		// Functions that allows ops and other nodes to inform this node of events on it's children
		virtual ChangeCode OnChildChange(ObjChangeParam* pParam);

		// Version 2 file format functions
		virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
		virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
		virtual BOOL CanWriteChildrenWeb(BaseCamelotFilter* pFilter);
		virtual BOOL CanWriteChildrenNative(BaseCamelotFilter* pFilter);

//	virtual BOOL IsValidEffectAttr(CCRuntimeClass* pAttrClass) const {return FALSE;}
	virtual BOOL IsValidEffectAttr(NodeAttribute* pAttr) const {return FALSE;}
	virtual BOOL GroupCanTransformCached(TransformBase& Trans) const {return FALSE;}

	public:
		// specific moulder functions follow
		NodeRenderableInk*	GetProvider() { return pProviderNode; };

		// build functions
		NodePath* 		 CreateMouldPath(NodePath*, MouldGeometry*, UndoableOperation* );
		NodeMouldBitmap* CreateMouldBitmap(NodeBitmap*, MouldGeometry*, UndoableOperation* );
		BOOL 			 CreateMouldedObjects(NodeMouldGroup* pGroup, MouldGeometry*, UndoableOperation* );
		BOOL			 MouldAllChildren(Node* pNode, MouldGeometry* pGeometry, TransformBase& Trans, UndoableOperation* pOp);
		BOOL 			 MouldPath(NodePath*, MouldGeometry*, UndoableOperation*);
		BOOL			 DestroyMouldedObjects();

	private:
		void PreExportCAMEPS(RenderRegion* pRegion);
		BOOL PostExportCAMEPS(RenderRegion* pRegion);
		void PreExportAWEPS(RenderRegion* pRegion);
		BOOL PostExportAWEPS(RenderRegion* pRegion);
		BOOL CreateMouldObjsWithUndo(NodeMouldGroup* pGroup, MouldGeometry*, UndoableOperation* );
		BOOL CreateMouldObjsWithoutUndo(NodeMouldGroup* pGroup, MouldGeometry* pGeometry);

		void CopyNodeContents(NodeMoulder* pCopyOfNode);

	private:
		NodeRenderableInk* pProviderNode;

};


#endif
