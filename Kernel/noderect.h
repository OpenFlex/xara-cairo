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


#ifndef INC_NODERECT
#define INC_NODERECT

#include "nodeshap.h"

/***********************************************************************************************

>	class NodeRect : public NodeSimpleShape

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>, Changed by Rik
	Created:	22/9/93
	Purpose:	A Node rect represents a rectangle object in the tree. It is derived from
				NodeSimple Shape that contains most of the functionality it needs. Simple
				Shapes are a group of nodes that are based around a parallelogram. The shape
				is fitted into a parallelogram so that it can be transformed while keeping
				its own identity (ie, it does not have to be turned into a NodePath)

***********************************************************************************************/

class NodeRect : public NodeSimpleShape
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(NodeRect);

public:
	NodeRect(); 	
	NodeRect(	Node* ContextNode,  
				AttachNodeDirection Direction,  
				BOOL Locked = FALSE, 
				BOOL Mangled = FALSE,  
				BOOL Marked = FALSE, 
				BOOL Selected = FALSE    
			  );
	
	virtual Node* SimpleCopy();
	virtual String Describe(BOOL Plural, BOOL Verbose);

	// For exporting
	void PreExportRender(RenderRegion* pRegion);

	// Functions to re-build the path from the parallelogram
	virtual void CreateShape(DocRect NewRect);
	virtual void UpdateShape();

	// Information functions
	virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	// The snap to coords function is slightly different from the simple shapes one
	virtual BOOL SnapToCoords(DocCoord* pDocCoord);

	// Decides what to do about a drag on a blob
	virtual void HandleBlobDrag( DocCoord&, Spread*, INT32 );
}; 

#endif
