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


// NodeBrushPath class

#include "nodepath.h"
#include "ndbldpth.h"


class NodeBrush;
class NodeBrushMaker;
class DocCoord;
class ProcessPathDistance;


/********************************************************************************************

>	class NodeBrushMaker: public NodeBlendPath

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/10/99
	Purpose:	The NodeBrushMaker class

********************************************************************************************/

class NodeBrushPath : public NodeBlendPath
{
	CC_DECLARE_DYNCREATE( NodeBrushPath )

public:
	 NodeBrushPath();
	~NodeBrushPath();

	NodeBrushPath(	Node* ContextNode,  
					AttachNodeDirection Direction,  
					BOOL Locked = FALSE, 
					BOOL Mangled = FALSE,  
					BOOL Marked = FALSE, 
					BOOL Selected = FALSE );
	
	virtual Node* 	SimpleCopy();
	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	virtual void RenderEorDrag( RenderRegion* );
	virtual void Render( RenderRegion* pRender);
	virtual void RenderObjectBlobs(RenderRegion* pRender);
	virtual void RenderTinyBlobs(RenderRegion* pRender);
	virtual DocRect GetBoundingRect(); 
	
	// transformation function
	virtual void Transform( TransformBase& Trans );



	void SetPointAtDistance(MILLIPOINT Distance, DocCoord Point);
	INT32 GetNumberOfSteps();
	void SetNumberOfSteps(INT32 Steps);
		
	void IncludePointInBoundingRect(DocCoord Point);

	BOOL	GetPointAtDistance(MILLIPOINT Dist,DocCoord* pPoint,
							   double* pTangent, BOOL UseCache = FALSE);
	void	ResetPathProcCache();
	void	StartedBrush();
	void	StoppedBrush();
	BOOL    InitialisePathProcessor();

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:

	void CopyNodeContents( NodeBrushPath* NodeCopy );		// Copies the contents of the path
	
	ProcessPathDistance* m_pProcessPath;
	INT32 m_NumSteps;
	BOOL m_bDrawingBrush;


private:

	


};
