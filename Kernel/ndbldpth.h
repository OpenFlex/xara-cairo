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


#ifndef INC_NODEBLENDPATH
#define INC_NODEBLENDPATH

//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "nodepath.h"
#include "brpress.h"

/***********************************************************************************************

>	class NodeBlendPath : public NodePath

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/4/99
	Purpose:	defines the structure of a node blend path object. This object exists only as
				a child of a blend object
	SeeAlso:	NodeBlend (the parent object)

***********************************************************************************************/

class NodeBlendPath : public NodePath
{	
	// Give my name out in memory dumps
CC_DECLARE_DYNCREATE( NodeBlendPath )

public:
	 NodeBlendPath();
	~NodeBlendPath();

	NodeBlendPath(	Node* ContextNode,  
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

	virtual BOOL	AllowOp(ObjChangeParam* pParam, BOOL SetOpPermissionState,
													BOOL DoPreTriggerEdit = TRUE);
	virtual BOOL	OnEdited(ObjChangeParam* pParam);

	virtual BOOL	DoBecomeA(BecomeA* pBecomeA);

	// Blob rendering
	void RenderBlendBlobs(RenderRegion* pRender);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	virtual BOOL IsANodeBlendPath();


	BOOL		CopyNodePath(NodePath* pNodePathToCopy);
	NodePath*	CreateNodePathCopy();

	double 	GetPathLength();
	BOOL	GetPointAtDistance(MILLIPOINT Dist,DocCoord* pPoint,double* pTangent);
	
	
	void DestroyCachedInformation();

	// DY 9/99 access functions to find out which NBP this is
	INT32 SetPathIndex();
	UINT32 GetPathIndex();

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	void CopyNodeContents( NodeBlendPath* NodeCopy );		// Copies the contents of the path

	double m_CachedPathLength;
	CMap< MILLIPOINT, MILLIPOINT &, CPathPointInfo, CPathPointInfo & > *m_pCachedPointsAtDistance;

	// to keep track of blends containing multiple nodeblendpaths
	UINT32 m_Index;
private:
	BOOL InsideBlend();

	// CAM/AW EPS output functions
	BOOL ExportCAMEPS(RenderRegion* pRegion);
	BOOL ExportAWEPS(RenderRegion* pRegion);



};


/********************************************************************************************

>	class InitNodeBlendPathAction : public Action

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/5/99
	Purpose:	An action which destroys the cached info in a blend path node
	SeeAlso:	-

********************************************************************************************/

class InitNodeBlendPathAction : public Action
{

CC_DECLARE_DYNCREATE(InitNodeBlendPathAction)

public:
	InitNodeBlendPathAction() { m_pNodeBlendPath = NULL; }
	~InitNodeBlendPathAction() {}
	virtual ActionCode Execute();
	static ActionCode Init( UndoableOperation* pOp,ActionList* pActionList,NodeBlendPath* pNodeBlendPath);
protected:
	NodeBlendPath* m_pNodeBlendPath;
};


#endif // INC_NODEBLENDPATH
