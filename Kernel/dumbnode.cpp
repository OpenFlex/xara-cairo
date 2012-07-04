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

DECLARE_SOURCE("$Revision: 1282 $");

#include "dumbnode.h"
//#include "errors.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "mario.h"

/********************************************************************************************

>	StartDocument::StartDocument(Node* ContextNode,  
	 						 AttachNodeDirection Direction, 
	 		  				 BOOL Locked=0, 
	 		  				 BOOL Mangled=0,  
	 		    			 BOOL Marked=0, 
	 		  				 BOOL Selected=0, 
	 		  				 BOOL Renderable=0)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/12/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	StartDocument constructor 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

	
StartDocument::StartDocument(Node* ContextNode,  
	 						 AttachNodeDirection Direction, 
	 		  				 BOOL Locked, 
	 		  				 BOOL Mangled,  
	 		    			 BOOL Marked, 
	 		  				 BOOL Selected, 
	 		  				 BOOL Renderable):Node(ContextNode, Direction, Locked, Mangled,
		 		        							  Marked, Selected, Renderable)
{ 
} 

/***********************************************************************************************
> Node* StartDocument::SimpleCopy() 

    Author:     Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
    Created:    28/4/93
	
	Inputs:         - 
    Outputs:    
    Returns:    A copy of the node, or NULL if memory runs out 
		 
    Purpose:    This method returns a shallow copy of the node with all Node pointers NULL. 
				The function is virtual, and must be defined for all derived classes.  
	       
   	       
	Errors:     If memory runs out when trying to copy, then ERROR is called with an out of memory
				error and the function returns NULL. 
 
        
    Scope:      protected  
**********************************************************************************************/

Node* StartDocument::SimpleCopy()
{
	StartDocument* NodeCopy; 
	NodeCopy = new StartDocument();       
	ERRORIF(NodeCopy == NULL, _R(IDE_NOMORE_MEMORY), NULL); 
	CopyNodeContents(NodeCopy);   
	return (NodeCopy);
}   

/********************************************************************************************

>	virtual UINT32 StartDocument::GetNodeSize() const

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/93
	Inputs:		-
	Outputs:	-
	Returns:	The size of the node in bytes
	Purpose:	For finding the size of the node 
				
	SeeAlso:	Node::GetSubtreeSize

********************************************************************************************/

UINT32 StartDocument::GetNodeSize() const 
{     
	return (sizeof(StartDocument)); 
}   

/********************************************************************************************

>	BOOL StartDocument::IsPaper() const

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/11/94
	Returns:	TRUE => we are a paper node.
	Purpose:	Indicate that we ARE paper! (Overrides virtual func in Node.)
	SeeAlso:	Node::IsPaper

********************************************************************************************/

BOOL StartDocument::IsPaper() const
{
	return TRUE;
}











/********************************************************************************************

>	EndDocument::EndDocument(Node* ContextNode,  
		 		  AttachNodeDirection Direction, 
		 		  BOOL Locked=0, 
		 		  BOOL Mangled=0,  
		 		  BOOL Marked=0, 
		 		  BOOL Selected=0, 
		 		  BOOL Renderable=0)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/12/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	EndDocument constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/



EndDocument::EndDocument(Node* ContextNode,  
		 		  AttachNodeDirection Direction, 
		 		  BOOL Locked, 
		 		  BOOL Mangled,  
		 		  BOOL Marked, 
		 		  BOOL Selected, 
		 		  BOOL Renderable):Node(ContextNode, Direction, Locked, Mangled,
		 		         				  Marked, Selected, Renderable)
{ 
} 


/***********************************************************************************************
> Node* EndDocument::SimpleCopy() 

    Author:     Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
    Created:    28/4/93
	
	Inputs:         - 
    Outputs:    
    Returns:    A copy of the node, or NULL if memory runs out 
		 
    Purpose:    This method returns a shallow copy of the node with all Node pointers NULL. 
				The function is virtual, and must be defined for all derived classes.  
	       
   	       
	Errors:     If memory runs out when trying to copy, then ERROR is called with an out of memory
				error and the function returns NULL. 
 
        
    Scope:      protected  
**********************************************************************************************/

Node* EndDocument::SimpleCopy()
{
	EndDocument* NodeCopy; 
	NodeCopy = new EndDocument();       
	ERRORIF(NodeCopy == NULL, _R(IDE_NOMORE_MEMORY), NULL); 
	CopyNodeContents(NodeCopy);   
	return (NodeCopy);
}  

/********************************************************************************************

>	virtual UINT32 EndDocument::GetNodeSize() const

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/93
	Inputs:		-
	Outputs:	-
	Returns:	The size of the node in bytes
	Purpose:	For finding the size of the node 
				
	SeeAlso:	Node::GetSubtreeSize

********************************************************************************************/

UINT32 EndDocument::GetNodeSize() const 
{     
	return (sizeof(EndDocument)); 
}   

/********************************************************************************************

>	BOOL EndDocument::IsPaper() const

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/11/94
	Returns:	TRUE => we are a paper node.
	Purpose:	Indicate that we ARE paper! (Overrides virtual func in Node.)
	SeeAlso:	Node::IsPaper

********************************************************************************************/

BOOL EndDocument::IsPaper() const
{
	return TRUE;
}




