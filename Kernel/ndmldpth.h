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

// The NodeMouldPath renderable class

#ifndef INC_NODEMOULDPATH
#define INC_NODEMOULDPATH

#include "nodepath.h"

/***********************************************************************************************

>	class NodeMouldPath : public NodePath

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/01/95
	Purpose:	defines the structure of a node mould path object. This object exists only as
				a child of a mould object, controlling the editing of the mould manifold
	SeeAlso:	Mould (the parent object)

***********************************************************************************************/

class NodeMouldPath : public NodePath
{
	// Give my name out in memory dumps
	CC_DECLARE_DYNCREATE( NodeMouldPath )

	public:
		 NodeMouldPath(); 
		~NodeMouldPath();

		NodeMouldPath(	Node* ContextNode,  
						AttachNodeDirection Direction,  
						BOOL Locked = FALSE, 
						BOOL Mangled = FALSE,  
						BOOL Marked = FALSE, 
						BOOL Selected = FALSE );

		// Virtual rendering functions	     
		virtual BOOL 	ExportRender( RenderRegion* pRender ); 
					
		virtual Node* 	SimpleCopy();
		virtual void 	Render( RenderRegion* pRender );
		virtual void 	RenderEorDrag( RenderRegion* );
		virtual void 	RenderObjectBlobs(RenderRegion* pRender);
		virtual DocRect GetBoundingRect(BOOL DontUseAttrs=FALSE, BOOL HitTest=FALSE);
		virtual CopyType GetCopyType() { return COMPLEXCOPY; };
		virtual INT32	ComplexCopy(CopyStage Stage, Range& RangeToCopy, Node** pOutput);
		virtual void	PolyCopyNodeContents(NodeRenderable* pNodeCopy);

		// Version 2 file format functions
		virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
		virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	protected:
		void CopyNodeContents( NodeMouldPath* NodeCopy );		// Copies the contents of the path

	private:
		BOOL InsideMould();

		// CAM/AW EPS output functions
		BOOL ExportCAMEPS(RenderRegion* pRegion);
		BOOL ExportAWEPS(RenderRegion* pRegion);

};


#endif
