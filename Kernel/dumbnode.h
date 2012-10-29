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


#ifndef INC_DUMBNODE
#define INC_DUMBNODE

// A collection of nodes which do nothing but sit there.


/********************************************************************
>	class StartDocument : public Node

Created:	17/5/93
Author:		Jim_Lynn (Xara Group Ltd) <camelotdev@xara.com>
Purpose:	This object type has no purpose other than to sit at the 
			beginning of the tree. It never has children, is not renderable
			and not selectable. It can never be deleted. There is only 
			ever one and it is always the first object in the tree. It
			exists so that object can be inserted at the head of the tree
			without the pointer from the document to the tree having to 
			be relinked - any object to be inserted at the head of the 
			tree should be inserted after the StartOfDocument object.

*********************************************************************/

class StartDocument : public Node
{
public:
	StartDocument() : Node() {};
	
    // To replace StartDocument(Node* ContextNode etc.           
	StartDocument(Node* ContextNode,  
		 		  AttachNodeDirection Direction, 
		 		  BOOL Locked=0, 
		 		  BOOL Mangled=0,  
		 		  BOOL Marked=0, 
		 		  BOOL Selected=0, 
		 		  BOOL Renderable=0); 

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual BOOL IsPaper() const;				// Override func in base class

   	   
protected:
	
	virtual Node* SimpleCopy();

// No members, no functions, nothing
// Might need some debugging info, but that's it!

};


/********************************************************************
>	class EndDocument : public Node

Created:	17/5/93
Author:		Jim_Lynn (Xara Group Ltd) <camelotdev@xara.com>
Purpose:	An object which is always the last object in the tree. This 
			ensures that we are always able to add objects at the end, 
			just by inserting them before the EndOfDocument object

*********************************************************************/

class EndDocument : public Node
{
public:

	EndDocument() : Node() {};
	
    EndDocument(Node* ContextNode,  
		 		  AttachNodeDirection Direction, 
		 		  BOOL Locked=0, 
		 		  BOOL Mangled=0,  
		 		  BOOL Marked=0, 
		 		  BOOL Selected=0, 
		 		  BOOL Renderable=0); 

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual BOOL IsPaper() const;				// Override func in base class


protected:
	virtual Node* SimpleCopy();
};

#endif	// ifndef INC_DUMBNODE
