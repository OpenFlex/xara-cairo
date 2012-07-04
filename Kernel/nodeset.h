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

#ifndef INC_NODESET
#define INC_NODESET

/********************************************************************************************

>	class NodeSet

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/10/94
	Purpose:	Provide a mechanism for marking a set of nodes for redrawing.  This 
				mechanism is independent of the number of render regions associated with a 
				particular tree, as it stores a list of pointers to nodes, rather than 
				marking the nodes themselves.
				The NodeSet can be instructed to mark or unmark all nodes in the set.  This
				allows us to selectively render these nodes without interfering with other
				render regions, because when we start rendering, we mark the nodes, render 
				the marked nodes, unmark the nodes, and then we have stopped rendering.
				This means we only ever mark nodes while the render region is actively
				rendering, and as there can only ever be one render region actively
				rendering at one time (including the possibility of background rendering)
				then we don't get any interaction between render regions.
	SeeAlso:	DynamicArray; DocView::ForceRedraw

********************************************************************************************/

class NodeSet : public CCObject
{
CC_DECLARE_MEMDUMP(NodeSet)

public:
	NodeSet(BOOL Strict = FALSE);
	BOOL AddNode(Node*);
	void MakeEmpty();
	void MarkNodes();
	void UnmarkNodes();

protected:
	BOOL				m_fStrictSet;
	std::vector<Node*>	m_NodeSet;	
};

#endif  // INC_NODESET


