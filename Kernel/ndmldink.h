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

// The NodeMouldInk renderable class

#ifndef INC_NODEMOULDINK
#define INC_NODEMOULDINK

//#include "ink.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class NodeMould;
class kernelBitmap;

/***********************************************************************************************

>	class NodeMouldBitmap : public NodeRenderableInk

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/12/94
	Purpose:	This class controls the renderable mould objects. ie those objects which
				are moulded and rendered in one action. It will live under Moulder objects
				along with NodePaths eg

					NodeMoulder
						NodePath -> NodePath -> NodeMouldBitmap -> NodePath -> NodeMouldBitmap
						 etc

***********************************************************************************************/

class NodeMouldBitmap: public NodeRenderableInk
{
	CC_DECLARE_DYNAMIC( NodeMouldBitmap );

	public:
		NodeMouldBitmap();
		NodeMouldBitmap(Node* ContextNode,  
				  AttachNodeDirection Direction,    
				  BOOL Locked=FALSE, 
				  BOOL Mangled=FALSE,  
				  BOOL Marked=FALSE, 
				  BOOL Selected=FALSE    
			     ); 

		~NodeMouldBitmap();

		// Virtual rendering functions	     
		virtual void Render(RenderRegion* pRegion);

		// Other virtual functions
		virtual String Describe(BOOL Plural, BOOL Verbose); 
		virtual Node* SimpleCopy();  
	    virtual UINT32 GetNodeSize() const;

		virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	private:
		void CopyNodeContents(NodeMouldBitmap* pCopyOfNode);

};


#endif


