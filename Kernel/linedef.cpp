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


// The line definition class implementation.  An abstract base class from which to
// derive the definitions of things like strokes, brushes.

#include "camtypes.h"
#include "linedef.h"
#include "colormgr.h"
//#include "spread.h" - in camtypes.h [AUTOMATICALLY REMOVED]

CC_IMPLEMENT_DYNAMIC(LineDefinition, CCObject)



/********************************************************************************************

>	LineDefinition::LineDefinition()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/2/97

	Purpose:	default constructor, please don't use it though, i am only keeping it around so 
				I can integrate the StrokeDefinition stuff

********************************************************************************************/

LineDefinition::LineDefinition()
{
	// set to NULL or else CascadeDelete fails in the destructor
	m_pTree = NULL;
}

/********************************************************************************************

>	LineDefinition::LineDefinition(Node *pLineTree);

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/2/97

	Inputs:		pLineTree - A pointer to a Spread node which is the root of a clipart
							  subtree which should be used for this Line definition. It
							  must obey these rules:
								* It must be a Spread
								* It must not be linked into any other parent tree structure
								* It should contain at least one path node (or else the Line
								  will appear "blank"). You should do Make Shapes on the 
								  subtree so that text, blends, quickshapes, etc are all in
								  path form
								* It should be attribute complete, or close thereto

	Purpose:	Constructor

	SeeAlso:	LineComponent::AddNewLine

********************************************************************************************/

LineDefinition::LineDefinition(Node *pLineTree)
{
	ERROR3IF(pLineTree == NULL, "Illegal NULL param");
	ERROR3IF(!pLineTree->IsSpread(), "LineDefinitions must begin with a Spread (for now, at least)");
	ERROR3IF(pLineTree->FindParent() != NULL, "Line Definition looks like it's linked into a tree!");

	m_pTree	  = pLineTree;

	// Check the subtree to see if it contains any transparency
	m_bNeedsTrans = m_pTree->ChildrenNeedTransparency();

	IOStore = 0;

	m_Name = TEXT("Custom line");

	m_bOverridesFill  = FALSE;
	m_bOverridesTrans = FALSE;
}



/********************************************************************************************

>	LineDefinition::~LineDefinition()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/2/97

	Purpose:	Destructor

********************************************************************************************/

LineDefinition::~LineDefinition()
{
	if (m_pTree	!= NULL)
	{
		m_pTree->CascadeDelete();
		delete m_pTree;
	}
}



/********************************************************************************************

>	void LineDefinition::SetLineName(StringBase *pName)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/3/97

	Purpose:	Sets the name text string for this Line

********************************************************************************************/

void LineDefinition::SetLineName(StringBase *pName)
{
	ERROR3IF(pName == NULL, "Illegal NULL param");

	pName->Left(&m_Name, 31);
}



/********************************************************************************************

>	virtual BOOL LineDefinition::NeedsTransparency() const

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/97

	Returns:	TRUE if this Line needs transparency in order to render

	Purpose:	Determine if this Line needs transparency in order to render.

********************************************************************************************/

BOOL LineDefinition::NeedsTransparency() const
{
	return(m_bNeedsTrans);
}


/********************************************************************************************

>	static void LineDefinition::ConvertIndexedColours(Node* pRoot) 

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/97
	Inputs :	pRoot - the root of the subtree that is about to passed in to create a linedef
				Note that this node must actually be a SPREAD, as that is what we expect
	Ouputs:     pSpread with all its indexed colours converted to local doccolours
	Returns:	-

	Purpose:	To convert all the colours in the subtree that we wish to use to make a 
				brush definition
********************************************************************************************/

void LineDefinition::ConvertIndexedColours(Spread* pRoot)
{
	if (pRoot == NULL)
	{
		ERROR3("Spread is NULL");
		return;
	}
	// start at the layer
	Node* pNode = pRoot->FindFirstChild();
	pNode = pNode->FindFirstChild();

	// traverse across the layer
	while (pNode != NULL)
	{
		// search depth first as we may have a group
		Node *pCurNode = pNode->FindFirstDepthFirst();
		Node *pNextNode;

		while (pCurNode !=NULL)
		{
			// We may be about to chop this node out of the tree, so get the next node now
			pNextNode = pCurNode->FindNextDepthFirst(pNode);
	
			// Use to scan the colour fields of the attribute.
			if (pCurNode->IsAnAttribute())
			{
				UINT32 Context = 0;
				NodeAttribute *pNodeAttr = (NodeAttribute *) pCurNode;

				// Get the next colour field from the attribute
				DocColour *pColour = pNodeAttr->EnumerateColourFields(Context++);
				
				while (pColour != NULL)
				{
					// For each colour field, make sure the colour is a local DocColour so that
					// the sub-tree is entirely stand-alone
					IndexedColour* pIndexCol = pColour->FindParentIndexedColour();
					if (pIndexCol != NULL)
					{
						ColourGeneric ColDef;
						ColourContext *cc = ColourManager::GetColourContext(pColour->GetColourModel());
						ERROR3IF(cc == NULL, "Can't find colour context?!");

						// Get the IndexedColour definition as a standalone colour definition
						cc->ConvertColour(pIndexCol, &ColDef);

						// Make the DocColour into a simple standalone "lookalike" of the parent colour
						*pColour = DocColour(pColour->GetColourModel(), &ColDef);

						// if the parent colour was named then set the reserved flag
						if (pIndexCol->IsNamed())
							pColour->SetReservedFlag(COL_NAMED);
					}
						pColour = pNodeAttr->EnumerateColourFields(Context++);
				}
			}
			pCurNode = pNextNode;
		}
		
		pNode = pNode->FindNext(CC_RUNTIME_CLASS(NodeRenderableInk));
	}
}
