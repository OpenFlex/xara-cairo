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


/*
*/


#include "camtypes.h"
#include "nodeelip.h"

//#include "app.h"
#include "aw_eps.h"
#include "blobs.h"
//#include "docview.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "opsmpshp.h"
//#include "osrndrgn.h"
//#include "rik.h"

DECLARE_SOURCE( "$Revision: 1315 $" );

// Declare this class and give my name for bad memory handling
CC_IMPLEMENT_DYNCREATE(NodeEllipse, NodeSimpleShape)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/***********************************************************************************************

>	NodeEllipse::NodeEllipse(	Node* ContextNode,  
						AttachNodeDirection Direction,  
						BOOL Locked, 
						BOOL Mangled,  
						BOOL Marked, 
						BOOL Selected    
						)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/6/94
    Inputs: 	ContextNode - Pointer to a node which this node is to be attached to.
				Direction - Specifies the direction in which the node is to be attached to the
				ContextNode.
				BoundingRect - The Bounding rectangle  
	Purpose:	This constructor initialises the nodes flags and links it to ContextNode in the
				direction specified by Direction. All neccesary tree links are updated.         			
	Note:		SetUpPath() must be called before the NodeRect is in a state in which it can be 
				used. 		
	SeeAlso:	SetUpPath   
	Errors:		An assertion error will occur if ContextNode is NULL

***********************************************************************************************/

NodeEllipse::NodeEllipse(	Node* ContextNode,  
						AttachNodeDirection Direction,  
						BOOL Locked, 
						BOOL Mangled,  
						BOOL Marked, 
						BOOL Selected    
					  ):NodeSimpleShape(ContextNode, Direction, Locked, Mangled, Marked, Selected )  
{                         
}                        
 
/*********************************************************************************************

>	NodeEllipse::NodeEllipse()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/6/94
	Purpose:	This constructor creates a NodeRect linked to no other with all status
				flags false and an uninitialized bounding rectangle.           			
	Note:		SetUpPath() must be called before the NodeRect is in a state in which it can be 
				used. 		                
	SeeAlso:	SetUpPath                                                        

**********************************************************************************************/
/* Technical Notes:   

The default constructor is required so that SimpleCopy will work 
*/  

NodeEllipse::NodeEllipse(): NodeSimpleShape()
{
}

/***********************************************************************************************

>	virtual Node* NodeEllipse::SimpleCopy()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/5/93
	Returns:	Pointer to a Node
	Purpose:	Makes a copy of all the data in the node

***********************************************************************************************/

Node* NodeEllipse::SimpleCopy()
{
	// Make a new NodeSimpleShape and then copy things into it
	NodeEllipse* NodeCopy = new NodeEllipse();
    if (NodeCopy)
    	CopyNodeContents(NodeCopy);
    
	return NodeCopy;
}            


/********************************************************************************************

>	virtual String NodeEllipse::Describe(BOOL Plural, BOOL Verbose = TRUE) 

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/6/94
	Inputs:		Plural: Flag indicating if the string description should be plural or
				singular. 
	Retuns:		Description of the object                                    
	Purpose:	To return a description of the NodeRect object in either the singular or the 
				plural. This method is called by the DescribeRange method.
				The description will always begin with a lower case letter.   
	Errors:		A resource exception will be thrown if a problem occurs when loading the 
				string resource. 

********************************************************************************************/
              
String NodeEllipse::Describe(BOOL Plural, BOOL Verbose) 
{     
	if (Plural)
		return(String(_R(IDS_ELLIPSE_DESCRP)));  
	else
		return(String(_R(IDS_ELLIPSE_DESCRS))); 
}

/********************************************************************************************

>	void NodeEllipse::PreExportRender(RenderRegion* pRegion)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/08/94
	Inputs:		pRegion - the render region we are exporting to.
	Purpose:	Output data required to mark this object as an ellipse, as opposed to an
				arbitrary path.

********************************************************************************************/

void NodeEllipse::PreExportRender(RenderRegion* pRegion)
{
#ifdef DO_EXPORT
	if (pRegion->IsKindOf(CC_RUNTIME_CLASS(ArtWorksEPSRenderRegion)))
	{
		// Output "ArtWorks ellipse" token
		EPSExportDC *pDC = (EPSExportDC *) pRegion->GetRenderDC();

		// Output the 3 coords defining the ellipse's bounding parallelogram
		pDC->OutputCoord(Parallel[0]);
		pDC->OutputCoord(Parallel[1]);
		pDC->OutputCoord(Parallel[2]);

		// And the token itself
		pDC->OutputToken(_T("ae"));
		pDC->OutputNewLine();
	}
#endif
}




/***********************************************************************************************

>	virtual void NodeEllipse::CreateShape(DocRect NewRect)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/6/94
	Inputs:		DocRect - representing the rectangle to create the shape in
	Purpose:	Creates an Ellipse using a path that fills the rectangle specified.

***********************************************************************************************/

void NodeEllipse::CreateShape(DocRect NewRect)
{
	// Copy the rectangle into the parallelogram
	Parallel[0] = DocCoord(NewRect.lo.x, NewRect.hi.y);
	Parallel[1] = DocCoord(NewRect.hi.x, NewRect.hi.y);
	Parallel[2] = DocCoord(NewRect.hi.x, NewRect.lo.y);
	Parallel[3] = DocCoord(NewRect.lo.x, NewRect.lo.y);

	// Get an array to put the 12 different coords needed to specify an ellipse
	DocCoord NewCoords[12];

	// Calculate the 3 coordinates along each side of the parallelogram
	CalcEllipseEdge(Parallel[0], Parallel[1], &NewCoords[11], &NewCoords[0], &NewCoords[1]);
	CalcEllipseEdge(Parallel[1], Parallel[2], &NewCoords[2], &NewCoords[3], &NewCoords[4]);
	CalcEllipseEdge(Parallel[2], Parallel[3], &NewCoords[5], &NewCoords[6], &NewCoords[7]);
	CalcEllipseEdge(Parallel[3], Parallel[0], &NewCoords[8], &NewCoords[9], &NewCoords[10]);

	// build a path
	InkPath.ClearPath();
	InkPath.FindStartOfPath();

	// Start at bottom left corner
	PathFlags NewFlags;
	NewFlags.IsRotate = TRUE;
	InkPath.InsertMoveTo(NewCoords[0], &NewFlags);
	InkPath.InsertCurveTo(NewCoords[1], NewCoords[2], NewCoords[3], &NewFlags);
	InkPath.InsertCurveTo(NewCoords[4], NewCoords[5], NewCoords[6], &NewFlags);
	InkPath.InsertCurveTo(NewCoords[7], NewCoords[8], NewCoords[9], &NewFlags);
	InkPath.InsertCurveTo(NewCoords[10], NewCoords[11], NewCoords[0], &NewFlags);

	// Close the path properly
	InkPath.CloseSubPath();
}




/***********************************************************************************************

>	virtual void NodeEllipse::UpdateShape()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/6/94
	Purpose:	Updates Ellipse node to fit the current parallelogram

***********************************************************************************************/

void NodeEllipse::UpdateShape()
{
	// make sure the path seems to have the correct number of coords in it
	ENSURE(InkPath.GetNumCoords()==13, "NodeEllipse::UpdateShape found its path corrupt" );

	// Get the array of coords in the path
	DocCoord* Coords = InkPath.GetCoordArray();

	// Update them to what we now have
	CalcEllipseEdge(Parallel[0], Parallel[1], &Coords[11], &Coords[0], &Coords[1]);
	CalcEllipseEdge(Parallel[1], Parallel[2], &Coords[2], &Coords[3], &Coords[4]);
	CalcEllipseEdge(Parallel[2], Parallel[3], &Coords[5], &Coords[6], &Coords[7]);
	CalcEllipseEdge(Parallel[3], Parallel[0], &Coords[8], &Coords[9], &Coords[10]);
	Coords[12] = Coords[0];
}


/********************************************************************************************

>	void NodeEllipse::CalcEllipseEdge(DocCoord& P0, DocCoord& P1, DocCoord* NewCoordA, 
									  DocCoord* NewCoordB, DocCoord* NewCoordC)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/6/94
	Inputs:		P0 - The First Corner of the parallelogram
				P1 - The Second Corner of the parallelogram
	Outputs:	NewCoordA - The coord of the Bezier control point closest to P0
				NewCoordB - The coord of the Bezier Endpoint that is midway between P1 & P1
				NewCoordC - The coord of the Bezier control point closest to P1
	Purpose:	This function is used to fit an Ellipse inside a parallelogram using Bezier
				Curves. Along each side of the parallelogram there will be 3 coordinates (an
				Endpoint and 2 control points). This function calculate the 3 coordinates along
				a single side of the parallelogram (to calc all the control points the function
				would need to be called 4 times). The Coords P1 and P1 are assumed to be
				adjacent coordinates of the parallelogram.
				The maths for calculating coordinates for Rounded Rectangles is very similar.
				I have made optimisations in this function as not as much maths is needed.
				For a full description of the maths used here see the document
				Camelot/doc/ellipse.doc

********************************************************************************************/

void NodeEllipse::CalcEllipseEdge(const DocCoord& P0, const DocCoord& P1, DocCoord* NewCoordA,
								  DocCoord* NewCoordB, DocCoord* NewCoordC)
{
	// Do the maths. This is described in the document camelot\docs\ellipse.doc
	// Find the length of the first side (pythag)
	INT32 dx = P1.x - P0.x;
	INT32 dy = P1.y - P0.y;
	//double SideLength = sqrt(dx*dx + dy*dy);
	//ENSURE(SideLength!=0.0, "CalcEllipseEdge was thinking of doing a div 0!");

	// This would be different if we were calculating a rounded rectangle
	//double ArcRadius = SideLength / 2.0;
	//double ControlDist = ArcRadius/(SideLength*2.2336);
	// This is equivalent to the above 2 lines, only less maths is needed
	// (ie none as the compiler should do it)
	double ControlDist = 1.0 / (2 * 2.2336);

	// Find the control point closest to P0
	NewCoordA->x = (INT32) (P0.x + (dx * ControlDist));
	NewCoordA->y = (INT32) (P0.y + (dy * ControlDist));

	// Find the mid point of the side, for the middle control point
	NewCoordB->x = (INT32) (P0.x + (dx / 2));
	NewCoordB->y = (INT32) (P0.y + (dy / 2));

	// Find the Control point closest to p1
	NewCoordC->x = (INT32) (P1.x - dx * ControlDist);
	NewCoordC->y = (INT32) (P1.y - dy * ControlDist);
}




/********************************************************************************************

>	DocRect NodeEllipse::GetBlobBoundingRect()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Returns:	The bounding rect of the Ellipse and its blobs
	Purpose:	Calculates the ellipses bounding rect along with its blobs

********************************************************************************************/

DocRect NodeEllipse::GetBlobBoundingRect()
{
#if !defined(EXCLUDE_FROM_RALPH)
	// Find the paths bounding rectangle
	DocRect ShapeRect = GetBoundingRect();
	DocRect Rect(Parallel[0], Parallel[0]);
	Rect.IncludePoint(Parallel[1]);
	Rect.IncludePoint(Parallel[2]);
	Rect.IncludePoint(Parallel[3]);

	// Find the blob manager
	BlobManager* pBlobMgr = GetApplication()->GetBlobManager();
	
	// Get a rect to put the extra rectangle on
	DocRect BlobRect;

	// Get the rect round a blob in the corner of the ellipse and add it to the total
	DocCoord Corner = Rect.HighCorner();
	pBlobMgr->GetBlobRect(Corner, &BlobRect);
	Rect = Rect.Union(BlobRect);

	// and the same with the other corner
	Corner = Rect.LowCorner();
	pBlobMgr->GetBlobRect(Corner, &BlobRect);
	Rect = Rect.Union(BlobRect);

	// and union it with the rect of the shape or things like Linewidth get in the way
	Rect = Rect.Union(ShapeRect);

	// Make sure we include the Bounds of our children
	IncludeChildrensBoundingRects(&Rect);

	// return the rectangle with the blobs included
	return Rect;
#else
	return DocRect(0,0,0,0);
#endif
}




/********************************************************************************************

>	virtual UINT32 NodeEllipse::GetNodeSize() const 

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/6/94
	Returns:	The size of the node in bytes 
	Purpose:	For finding the size of the node 
	SeeAlso:	Node::GetSubtreeSize

********************************************************************************************/

UINT32 NodeEllipse::GetNodeSize() const 
{     
	return (sizeof(NodeEllipse));
}  




/********************************************************************************************

>	virtual void NodeEllipse::HandleBlobDrag(DocCoord& PointerPos, Spread* pSpread, INT32 FixedCorner)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/6/94
	Inputs:		PointerPos - The position the mouse pointer clicked
				pSpread - the spread that the click was on
				FixedCorner - The corner of the parallelogram that will stay fixed during
				the drag
	Purpose:	When a drag is started on one of the paths blobs this is called. It tries to
				fire up an operation that will perform a drag of all the selected points, 
				including all the EORing of the relavent parts of the curve. If it fails it
				will inform the user and not bother.

********************************************************************************************/

void NodeEllipse::HandleBlobDrag(DocCoord& PointerPos, Spread* pSpread, INT32 FixedCorner)
{
/*	OpEditEllipse* pOp = new OpEditEllipse;
	if (pOp==NULL)
	{
		// Failed to get the memory to do the job
		if (IsUserName( "Rik" )) TRACE( _T("The Node Ellipse Edit Operation failed to start\n") );

		// Inform the person doing the clicking that life is not looking so good
		InformError();
	}
	else
	{
		// Start the drag operation and pass in the Anchor Point to the operation
		pOp->DoDrag(PointerPos, pSpread, this, FixedCorner);
	}*/
}



