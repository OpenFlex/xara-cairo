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
*/

#include "camtypes.h"
#include "noderect.h"

// Code headers
#include "aw_eps.h"
#include "opsmpshp.h"

// Resource headers
//#include "simon.h"


// Put my version Number into the About box
DECLARE_SOURCE( "$Revision: 1315 $" );

// Declare class and give details in memory dumps
CC_IMPLEMENT_DYNCREATE(NodeRect, NodeSimpleShape)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/***********************************************************************************************

>   NodeRect::NodeRect(	Node* 				ContextNode,  
						AttachNodeDirection Direction,  
						const DocRect& 		BoundingRect, 
						BOOL				Locked = FALSE, 
						BOOL 				Mangled = FALSE,  
						BOOL 				Marked = FALSE, 
						BOOL 				Selected = FALSE, 
						BOOL 				Renderable = FALSE
						)

    Author: Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
    Created:22/9/93             
    
    Inputs: ContextNode: Pointer to a node which this node is to be attached to.     
		
			Direction: 
			
				Specifies the direction in which the node is to be attached to the 
				ContextNode. The values this variable can take are as follows: 
								  
				PREV      : Attach node as a previous sibling of the context node
				NEXT      : Attach node as a next sibling of the context node
				FIRSTCHILD: Attach node as the first child of the context node
				LASTCHILD : Attach node as a last child of the context node                               
					      
			BoundingRect: Bounding rectangle  
								  
			The remaining inputs specify the status of the node: 
			
			Locked:     Is node locked ?
			Mangled:    Is node mangled ?
			Marked:     Is node marked ?
			Selected:   Is node selected ?
			
    Purpose: This constructor initialises the nodes flags and links it to ContextNode in the
			direction specified by Direction. All neccesary tree links are updated.         
			
	Note:   SetUpPath() must be called before the NodeRect is in a state in which it can be 
			used. 		
                
    SeeAlso: SetUpPath   
    
    Errors: An assertion error will occur if ContextNode is NULL

***********************************************************************************************/

NodeRect::NodeRect(Node* ContextNode,  
					AttachNodeDirection Direction,  
					BOOL Locked, 
					BOOL Mangled,  
					BOOL Marked, 
					BOOL Selected    
			  ):NodeSimpleShape(ContextNode, Direction, Locked, Mangled, Marked, Selected )  
{                         
}                        
 
/*********************************************************************************************

>    NodeRect::NodeRect() 

     Author:    Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
     Created:   22/9/93
     Purpose: This constructor creates a NodeRect linked to no other with all status
		 	  flags false and an uninitialized bounding rectangle.           
			
     Note:    SetUpPath() must be called before the NodeRect is in a state in which it can be 
			  used. 		
                
     SeeAlso: SetUpPath                                                        

**********************************************************************************************/
/* Technical Notes:   

The default constructor is required so that SimpleCopy will work 
*/  

NodeRect::NodeRect(): NodeSimpleShape()
{
}



/***********************************************************************************************

>	virtual Node* NodeRect::SimpleCopy()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/5/93
	Returns:	Pointer to a Node
	Purpose:	Makes a copy of all the data in the node

***********************************************************************************************/

Node* NodeRect::SimpleCopy()
{
	// Make a new NodeSimpleShape and then copy things into it
	NodeRect* NodeCopy = new NodeRect();
    if (NodeCopy)
    	CopyNodeContents(NodeCopy);
    
	return NodeCopy;
}            




/********************************************************************************************

>	virtual String NodeRect::Describe(BOOL Plural, BOOL Verbose = TRUE)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/6/93
	Inputs:		Plural: Flag indicating if the string description should be plural or
				singular. 
	Retuns:		Description of the object                                    
	Purpose:	To return a description of the NodeRect object in either the singular or the 
				plural. This method is called by the DescribeRange method.
				The description will always begin with a lower case letter.   
	Errors:		A resource exception will be thrown if a problem occurs when loading the 
				string resource. 

********************************************************************************************/
              
String NodeRect::Describe(BOOL Plural, BOOL Verbose) 
{     
	if (Plural)
		return(String(_R(IDS_RECTANGLE_DESCRP)));  
	else
		return(String(_R(IDS_RECTANGLE_DESCRS))); 
}; 


/********************************************************************************************

>	void NodeRect::PreExportRender(RenderRegion* pRegion)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/08/94
	Inputs:		pRegion - the render region we are exporting to.
	Purpose:	Output data required to mark this object as a rectangle as opposed to an
				arbitrary path.

********************************************************************************************/

void NodeRect::PreExportRender(RenderRegion* pRegion)
{
#ifdef DO_EXPORT
	if (pRegion->IsKindOf(CC_RUNTIME_CLASS(ArtWorksEPSRenderRegion)))
	{
		// Output "ArtWorks rectangle" token
		EPSExportDC *pDC = (EPSExportDC *) pRegion->GetRenderDC();
		pDC->OutputToken(_T("ar"));
		pDC->OutputNewLine();
	}
#endif
}


/***********************************************************************************************

>	virtual void NodeRect::CreateShape(DocRect NewRect)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>, Changed by Rik
	Created:	22/9/93                          
	Inputs:		DocRect - representing the rectangle to be created.
	Purpose:	Creates a rectangle using a path.

***********************************************************************************************/

void NodeRect::CreateShape(DocRect NewRect)
{
	// Copy the rectangle into the parallelogram
	Parallel[0] = DocCoord(NewRect.lo.x, NewRect.hi.y);
	Parallel[1] = DocCoord(NewRect.hi.x, NewRect.hi.y);
	Parallel[2] = DocCoord(NewRect.hi.x, NewRect.lo.y);
	Parallel[3] = DocCoord(NewRect.lo.x, NewRect.lo.y);

	// build a path
	InkPath.FindStartOfPath();

	// Start at bottom left corner
	InkPath.InsertMoveTo(Parallel[0]);
	InkPath.InsertLineTo(Parallel[1]);
	InkPath.InsertLineTo(Parallel[2]);
    InkPath.InsertLineTo(Parallel[3]);
	InkPath.InsertLineTo(Parallel[0]);

	// Close the path properly
	InkPath.CloseSubPath();
}

/***********************************************************************************************

>	virtual void NodeRect::UpdateShape()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>, Changed by Rik
	Created:	22/9/93                          
	Purpose:	Updates rectangle node to fit the current parallelogram

***********************************************************************************************/

void NodeRect::UpdateShape()
{
	// make sure the path seems to have the correct number of coords in it
	ENSURE(InkPath.GetNumCoords()==5, "NodeRect::UpdateShape found its path corrupt" );

	// Get the array of coords in the path
	DocCoord* Coords = InkPath.GetCoordArray();

	// Update them to what we now have
	Coords[0] = Parallel[0];
	Coords[1] = Parallel[1];
	Coords[2] = Parallel[2];
	Coords[3] = Parallel[3];
	Coords[4] = Parallel[0];
}


/********************************************************************************************

>	void NodeRect::HandleBlobDrag(DocCoord& PointerPos, Spread* pSpread, INT32 FixedCorner)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/11/93
	Inputs:		PointerPos - The position the mouse pointer clicked
				pSpread - the spread that the click was on
				FixedCorner - The corner of the parallelogram that will stay fixed during
				the drag
	Purpose:	When a drag is started on one of the paths blobs this is called. It tries to
				fire up an operation that will perform a drag of all the selected points, 
				including all the EORing of the relavent parts of the curve. If it fails it
				will inform the user and not bother.

********************************************************************************************/

void NodeRect::HandleBlobDrag(DocCoord& PointerPos, Spread* pSpread, INT32 FixedCorner)
{
#if !defined(EXCLUDE_FROM_RALPH)
	OpEditRectangle* pOpRect = new OpEditRectangle;
	if (pOpRect == NULL)
	{
		// Failed to get the memory to do the job
		TRACEUSER( "Rik", _T("The Node Rect Edit Operation failed to start\n") );

		// Inform the person doing the clicking that life is not looking so good
		InformError();
	}
	else
	{
		// Start the drag operation and pass in the Anchor Point to the operation
		pOpRect->DoDrag(PointerPos, pSpread, this, FixedCorner);
	}
#endif
}

/********************************************************************************************

>	virtual UINT32 NodeRect::GetNodeSize() const

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/93
	Inputs:		-
	Outputs:	-
	Returns:	The size of the node in bytes 

	Purpose:	For finding the size of the node 
				
	SeeAlso:	Node::GetSubtreeSize

********************************************************************************************/

UINT32 NodeRect::GetNodeSize() const 
{     
	return (sizeof(NodeRect)); 
}  





/********************************************************************************************

>	BOOL NodeRect::SnapToCoords(DocCoord* pDocCoord)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/11/94
	Inputs:		pDocCoord - the coord to try and snap to
	Outputs:	pDocCoord - The snapped coord, if it was close enough to any of the magnetic
				points for a rectangle.
	Returns:	TRUE if it was snapped, FALSE if not
	Purpose:	Snaps the point magnetically to the magnetic coords for a rectangle. These
				are :- The Centre, The Corners, and the midpoints of its edges.

********************************************************************************************/

BOOL NodeRect::SnapToCoords(DocCoord* pDocCoord)
{
#if !defined(EXCLUDE_FROM_RALPH)
	// First try and snap to all the places that the base class snaps for us
	BOOL IsSnapped = NodeSimpleShape::SnapToCoords(pDocCoord);

	// if it did not snap in the base class, try the extra points
	if (IsSnapped==FALSE)
	{
		// Try each of the corner of the rectangle
		for (INT32 i=0; i<4; i++)
		{
			if (IsMagneticallyClose(&Parallel[i], pDocCoord))
				return TRUE;
		}
	}

	// send the result on
	return IsSnapped;
#else
	return FALSE;
#endif
}


