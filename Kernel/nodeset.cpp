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


// Implementation of Node sets, i.e. arbitrary collections of nodes.

/*
*/

#include "camtypes.h"

#include "nodeset.h"


DECLARE_SOURCE("$Revision: 751 $");

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

CC_IMPLEMENT_MEMDUMP(NodeSet, CCObject)


/********************************************************************************************

>	NodeSet::NodeSet(BOOL Strict)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/10/94
	Inputs:		Strict - TRUE => Strict set - a node may only be in the set 0 or 1 times.
						FALSE => Not strict - a node may be in the set more than once.
	Purpose:	Create a NodeSet.  It may or may not be a strict set - it depends on the
				"Strict" parameter.  If it is strict, then when nodes are added, the class
				checks that they don't already exist in the set - if they do, it just does
				nothing and returns success.
	SeeAlso:	NodeSet

********************************************************************************************/

NodeSet::NodeSet(BOOL Strict) : m_NodeSet( 50 )
{
	// Remember what kind of set this is.
	m_fStrictSet = Strict;
}


/********************************************************************************************

>	BOOL NodeSet::AddNode(Node *pNode)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/10/94
	Inputs:		pNode - pointer to the Node to add to this NodeSet.
	Returns:	TRUE if the set now contains the specified Node;
				FALSE if out of memory => ERROR1
	Purpose:	Adds the specified node to this node set. If this is a strict set (see the
				NodeSet constructor), then the set is first scanned to see if it already
				contains this node.  If it does, then the set is unchanged and success is
				returned.
	Errors:		Out of memory => ERROR1
	SeeAlso:	NodeSet::NodeSet

********************************************************************************************/

BOOL NodeSet::AddNode(Node *pNode)
{
	ERROR2IF(pNode == NULL, FALSE, "NULL node pointer in NodeSet::AddNode()");

	if( m_fStrictSet )
	{
		// Check to see if we haven't already got this node in the set
		size_t			cNode = m_NodeSet.size();
		for( size_t i = 0; i < cNode; i++ )
		{
			if( m_NodeSet[i] == pNode )
				// Already have this node - return success
				return TRUE;
		}
	}

	// See if we can add another node to this set.
	m_NodeSet.push_back( pNode );

	// Return success to caller
	return TRUE;
}

/********************************************************************************************

>	void NodeSet::MakeEmpty()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/10/94
	Purpose:	Remove all nodes from this NodeSet.
	SeeAlso:	DynamicArray::EmptyArray

********************************************************************************************/

void NodeSet::MakeEmpty()
{
	// Delete all the array elements, and create a new set that are all NULL.
	m_NodeSet.clear();
}


/********************************************************************************************

>	void NodeSet::MarkNodes()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/10/94
	Purpose:	Set the MARKED flag on all Nodes in this NodeSet.
				This is usually done before doing a selective rendering pass on the 
				document tree.
	SeeAlso:	NodeSet::UnmarkNodes

********************************************************************************************/

void NodeSet::MarkNodes()
{

}

/********************************************************************************************

>	void NodeSet::UnmarkNodes()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/10/94
	Purpose:	Clear the MARKED flag on all Nodes in this NodeSet.
				This is usually done after doing a selective rendering pass on the 
				document tree.
	SeeAlso:	NodeSet::MarkNodes

********************************************************************************************/

void NodeSet::UnmarkNodes()
{

}


