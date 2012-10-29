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


#include "camtypes.h"                          


#include "insertnd.h"
//#include "mario.h"

CC_IMPLEMENT_DYNAMIC(InsertionNode, Node); 

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/***********************************************************************************************
> Node* InsertionNode::SimpleCopy() 

    Author:     Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
    Created:    04/07/94
	
	Inputs:         - 
    Outputs:    
    Returns:    A copy of the node, or NULL if memory runs out 
		 
    Purpose:    This method returns a shallow copy of the node with all Node pointers NULL. 
				The function is virtual, and must be defined for all derived classes.  
	       
   	       
	Errors:     If memory runs out when trying to copy, then ERROR is called with an out of memory
				error and the function returns NULL. 
 
        
    Scope:      protected  
**********************************************************************************************/

Node* InsertionNode::SimpleCopy()
{
	ERROR3("InsertionNode SimpleCopy called, is this good ???"); 
	InsertionNode* NodeCopy; 
	NodeCopy = new InsertionNode(pOwnerDoc);       
	ERRORIF(NodeCopy == NULL, _R(IDE_NOMORE_MEMORY), NULL); 
	CopyNodeContents(NodeCopy);   
	return (NodeCopy);
}   

/********************************************************************************************

>	virtual UINT32 InsertionNode::GetNodeSize() const

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/93
	Inputs:		-
	Outputs:	-
	Returns:	The size of the node in bytes
	Purpose:	For finding the size of the node 
				
	SeeAlso:	Node::GetSubtreeSize

********************************************************************************************/

UINT32 InsertionNode::GetNodeSize() const 
{     
	return (sizeof(InsertionNode)); 
}   


/********************************************************************************************

>	InsertionNode::~InsertionNode()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/10/95
	Purpose:	This destructor was added by Simon 28/10/95 to solve a problem with Insertion
				Nodes being destroyed. If a layer is deleted which contains an Insertion 
				Node (This can occur when throwing away undo info) then we must inform the
				document containing the InsertionNode, so that it can NULLIFY it's pointer
				to it.

********************************************************************************************/

InsertionNode::~InsertionNode()
{
	ERROR3IF(!pOwnerDoc, "InsertionNode Has no owner doc"); 
	if (pOwnerDoc)
	{
		pOwnerDoc->InsertionNodeDying();
	}		
}
