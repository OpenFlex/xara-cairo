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


#ifndef INC_INSERTND
#define INC_INSERTND

// InsertNode - a node which indicates the current insertion position in each document

//#include "node.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************
>	class InsertionNode : public Node

Created:	04/07/94
Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
Purpose:	The insertion node is used to locate the position in the 
			tree where new objects are inserted. A pointer to the 
			insertion node is stored in the Document object.

			There will be only one instance of an InsertionNode in 
			each camelot document. It will live as a last child of 
			the the selected spread's active layer.



*********************************************************************/

class InsertionNode : public Node
{
	CC_DECLARE_DYNAMIC( InsertionNode ) 

public:
	InsertionNode(Document* pownerDoc) : Node() { pOwnerDoc = pownerDoc; };
	~InsertionNode();
    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes
	virtual BOOL IsAnInsertionNode() const { return TRUE; }

protected:
	Document* pOwnerDoc;	
	virtual Node* SimpleCopy();
};

#endif
