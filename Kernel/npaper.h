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


// class NodeRenderablePaper

#ifndef INC_NPAPER
#define	INC_NPAPER

#include "node.h"

class View;

/***********************************************************************************************

>    Class NodeRenderablePaper: public NodeRenderableBounded

     Author:       Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
     Date:         19/5/93
     Base Classes: NodeRenderable, Node, CCObject        
     Purpose:      This abstract class describes a renderable paper node. A property of paper 
     			   nodes is that they need to be rendered before their children.    
   
				   See the Node class for an important note about producing derived 
		           classes of Node. 
		            
    SeeAlso:       NodeRenderable
		       
***********************************************************************************************/

class NodeRenderablePaper: public NodeRenderableBounded
{                                  
	CC_DECLARE_DYNAMIC( NodeRenderablePaper ) 

public:                  
	NodeRenderablePaper(); 
	NodeRenderablePaper(Node* ContextNode,  
						AttachNodeDirection Direction,    
						BOOL Locked=FALSE, 
						BOOL Mangled=FALSE,  
						BOOL Marked=FALSE, 
						BOOL Selected=FALSE    
				       );                                               

	virtual SubtreeRenderState RenderSubtree(RenderRegion* pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);
	virtual BOOL NeedsToExport(RenderRegion *pRender, BOOL VisibleLayersOnly = FALSE,
							   BOOL CheckSelected = FALSE);
	BOOL IsPaper() const;
			                                      
	virtual DocRect GetPasteboardRect(BOOL Pixelise = TRUE, View *pView = NULL) const;
	virtual void GetDebugDetails(StringBase* Str);
   
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	virtual Node* SimpleCopy();  
	void CopyNodeContents(NodeRenderablePaper* NodeCopy);   
	
	virtual void ChangePasteboardRect(const DocRect& PasteRect); 
	virtual void SetInitialPasteboardRect(const DocRect& PasteRect);

	// The pasteboard rectangle	                        
 	DocRect PasteboardRect;
};  

#endif
