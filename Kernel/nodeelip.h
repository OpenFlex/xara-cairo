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

// NodeEllipse - The Ellipse Class

#ifndef INC_NODEELIP
#define INC_NODEELIP


#include "nodeshap.h"


/********************************************************************************************

>	class NodeEllipse : public NodeSimpleShape

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/6/94
	Purpose:	This is the Ellipse shape. It is based on the NodeSimpleShape, which means
				that it is fitted into a parallelogram. It is actually made up of 4 bezier
				curve sections.
	SeeAlso:	NodeSimpleShape; NodeRect

********************************************************************************************/

class NodeEllipse : public NodeSimpleShape
{
// Give my name out in memory dumps
CC_DECLARE_DYNCREATE(NodeEllipse);

public:
	NodeEllipse();
	NodeEllipse(	Node* ContextNode,
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

	// The Blob bounding rect for ellipses is slightly different
	virtual DocRect GetBlobBoundingRect();

	// Information functions
	virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	// Functions to deal with messages
	//virtual BOOL OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	// Decides what to do about a drag on a blob
	virtual void HandleBlobDrag( DocCoord&, Spread*, INT32 );

	static void CalcEllipseEdge(const DocCoord&, const DocCoord&, DocCoord*, DocCoord*, DocCoord*);
};



#endif // INC_NODEELIP


