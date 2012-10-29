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


// Load default brushes on start-up - Implementation

#include "camtypes.h"
#include "loadbrsh.h"
#include "camdoc.h"
#include "camelot.h"
#include "lddirect.h"
#include "colormgr.h"
#include "bmpcomp.h"

CC_IMPLEMENT_MEMDUMP(LoadBrushDirect, LoadDirect);

#define new CAM_DEBUG_NEW

/*****************************************************************************************

>	virtual BOOL LoadBrushDirect::OnLoadDocument(Document* pKernelDoc)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/2/2000
	Inputs:		pKernelDoc = a pointer to the loaded kernel document
	Returns		TRUE if the document was processed correctly
				FALSE if not.
	Purpose:	We need to replace indexed brush colours by local colours - since the linked
				indexed colours get deleted (this especially effects fill ramps!).

				NOTE:  identical to that in void PrintMarksMan::ConvertAllDocColours(Document* pDoc)

*****************************************************************************************/

BOOL LoadBrushDirect::OnLoadDocument(Document* pDoc)
{
	ERROR3IF(pDoc==NULL,"No doc pointer during PrintMarksMan::ConvertAllDocColours!");

	Node *CurNode = Node::DocFindFirstDepthFirst(pDoc);
	Node *NextNode;

	while (CurNode !=NULL)
	{
		// We may be about to chop this node out of the tree, so get the next node now
		NextNode = CurNode->DocFindNextDepthFirst();

		// Use to scan the colour fields of the attribute.
		UINT32 Context = 0;
		DocColour *pColour;

		if (CurNode->IsAnAttribute())
		{
			NodeAttribute *pNodeAttr = (NodeAttribute *) CurNode;

			// Get the next colour field from the attribute
			pColour = pNodeAttr->EnumerateColourFields(Context++);

			while (pColour != NULL)
			{
				// For each colour field, make sure the colour is a local DocColour so that
				// the sub-tree is entirely stand-alone
				if (pColour->FindParentIndexedColour() != NULL)
				{
					ColourGeneric ColDef;
					ColourContext *cc = ColourManager::GetColourContext(pColour->GetColourModel());
					ERROR3IF(cc == NULL, "Can't find colour context?!");

					// Get the IndexedColour definition as a standalone colour definition
					cc->ConvertColour(pColour->FindParentIndexedColour(), &ColDef);

					// Make the DocColour into a simple standalone "lookalike" of the parent colour
					*pColour = DocColour(pColour->GetColourModel(), &ColDef);
				}

				pColour = pNodeAttr->EnumerateColourFields(Context++);
			}
		}
		CurNode = NextNode;
	}

	// All is well we hope.
	return TRUE;
}
