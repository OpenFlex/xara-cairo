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


// Encapsulates a set of colours exported to a file.

/*
*/

#include "camtypes.h"

#include "expcol.h"
#include "colourix.h"


CC_IMPLEMENT_MEMDUMP(ExportColour, ListItem)
CC_IMPLEMENT_MEMDUMP(ExportColourList, List)
CC_IMPLEMENT_MEMDUMP(ExportedColours, CCObject)

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	ExportColour::ExportColour(IndexedColour *pNewCol, INT32 NewRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		pNewCol			- the colour to put in the list.
				RecordNumber	- the number of the record that this colour definition has been
								  saved in.
	Purpose:	Create a new export colour list item from the given indexed colour.
	SeeAlso:	ExportColourList;

********************************************************************************************/

ExportColour::ExportColour(IndexedColour *pNewCol, INT32 NewRecordNumber)
{
	// Initialise our class variables to these specified values.
	pCol = pNewCol;
	RecordNumber = NewRecordNumber;
}

/********************************************************************************************

>	ExportColour::ExportColour(PColourRGBT *pNewRGBCol, INT32 NewRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/6/96
	Inputs:		pNewRGBCol		- the simple RGB colour to put in the list.
				RecordNumber	- the number of the record that this colour definition has been
								  saved in.
	Purpose:	Create a new export colour list item from the given indexed colour.
	SeeAlso:	ExportColourList;

********************************************************************************************/

ExportColour::ExportColour(PColourRGBT *pNewRGBCol, INT32 NewRecordNumber)
{
	// Initialise our class variables to these specified values.
	// Indexed colour is NULL, which means use the simple colour in searching
	pCol = NULL;
	SimpleRGBColour = *pNewRGBCol;
	RecordNumber = NewRecordNumber;
}

/********************************************************************************************

>	ExportColourList::~ExportColourList()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroy the list of exported colours.
	SeeAlso:	ExportedColours

********************************************************************************************/

ExportColourList::~ExportColourList()
{
	// Destroy the list of colours which we may have
	//ExportColour* pExportedColour = (ExportColour *)GetHead();
	//while (pExportedColour)
	//{
	//	delete pExportedColour;

		// Try the next colour in the list
//		pExportedColour = (ExportColour *)Colours.GetNext(pExportedColour);
//	}
	
	DeleteAll();
}

/********************************************************************************************

>	ExportColour *ExportColourList::AddColour(IndexedColour *pCol, INT32 NewRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		pNewCol			- the colour to put in the list.
				RecordNumber	- the number of the record that this colour definition has been
								  saved in.
	Returns:	Pointer to the newly added colour, or 
				NULL if out of memory => ERROR1
	Purpose:	Add a new colour to the list of exported colours.
	Errors:		Out of memory => ERROR1
	SeeAlso:	ExportColour

********************************************************************************************/

ExportColour *ExportColourList::AddColour(IndexedColour *pCol, INT32 NewRecordNumber)
{
	ExportColour *pNewCol = new ExportColour(pCol, NewRecordNumber);

	// Check for out of memory
	if (pNewCol == NULL)
		return NULL;

	// Add to the list and return success
	AddTail(pNewCol);
	return pNewCol;
}

/********************************************************************************************

>	ExportColour *ExportColourList::AddColour(PColourRGBT *pNewRGBCol, INT32 NewRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/6/96
	Inputs:		pNewRGBCol		- the simple RGB colour to put in the list.
				RecordNumber	- the number of the record that this colour definition has been
								  saved in.
	Returns:	Pointer to the newly added colour, or 
				NULL if out of memory => ERROR1
	Purpose:	Add a new colour to the list of exported colours.
	Errors:		Out of memory => ERROR1
	SeeAlso:	ExportColour

********************************************************************************************/

ExportColour *ExportColourList::AddColour(PColourRGBT *pNewRGBCol, INT32 NewRecordNumber)
{
	ExportColour *pNewCol = new ExportColour(pNewRGBCol, NewRecordNumber);

	// Check for out of memory
	if (pNewCol == NULL)
		return NULL;

	// Add to the list and return success
	AddTail(pNewCol);
	return pNewCol;
}

/********************************************************************************************

>	ExportedColours::ExportedColours()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Construct the class which encapsulates a list of exported colours.
	SeeAlso:	ExportedColours

********************************************************************************************/

ExportedColours::ExportedColours()
{
}

/********************************************************************************************

>	ExportedColours::~ExportedColours()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroy the class which encapsulates a list of exported colours.
	SeeAlso:	ExportedColours

********************************************************************************************/

ExportedColours::~ExportedColours()
{
}

/********************************************************************************************

>	BOOL ExportedColours::AddColour(IndexedColour *pNewCol, INT32 RecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		pNewCol			- the colour to put in the list.
				RecordNumber	- the number of the record that this colour definition has been
								  saved in.
	Returns:	TRUE if the colour could be added;
				FALSE if not
	Purpose:	Add the specified colour to the list of already exported colours.
	Errors:		-
	SeeAlso:	ExportColourList;

********************************************************************************************/

BOOL ExportedColours::AddColour(IndexedColour *pNewCol, INT32 RecordNumber)
{
	// Add the colour onto our list
	ExportColour * pExpCol = Colours.AddColour(pNewCol, RecordNumber);
	if (pExpCol)
		return TRUE;
	
	return FALSE;
}

/********************************************************************************************

>	BOOL ExportedColours::AddColour(PColourRGBT *pNewRGBCol, INT32 RecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/6/96
	Inputs:		pNewRGBCol		- the simple RGB colour to put in the list.
				RecordNumber	- the number of the record that this colour definition has been
								  saved in.
	Returns:	TRUE if the colour could be added;
				FALSE if not
	Purpose:	Add the specified colour to the list of already exported colours.
	Errors:		-
	SeeAlso:	ExportColourList;

********************************************************************************************/

BOOL ExportedColours::AddColour(PColourRGBT *pNewRGBCol, INT32 RecordNumber)
{
	// Add the colour onto our list
	ExportColour * pExpCol = Colours.AddColour(pNewRGBCol, RecordNumber);
	if (pExpCol)
		return TRUE;
	
	return FALSE;
}

/********************************************************************************************

>	ExportColour *ExportedColours::GetColour(IndexedColour *pSearchCol)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		pSearchCol			- the colour to search for in the list.
	Returns:	if the item is found then returns		- Pointer to the exported colour list item
				if the item is not found then returns	- NULL.
	Purpose:	Find an indexed colour in the exported list.
	SeeAlso:	ExportColourList

********************************************************************************************/

ExportColour *ExportedColours::GetColour(IndexedColour *pSearchCol)
{
	if (pSearchCol == NULL)
	{
		ERROR3("ExportedColours::GetColour - searching for a null indexed colour!");
	}

	ExportColour* pExportedColour = (ExportColour *)Colours.GetHead();
	while (pExportedColour)
	{
		// Compare the indexed colour pointers and return the match if they are the same
		if (pExportedColour->pCol == pSearchCol)
			return pExportedColour;
		
		// Try the next colour in the list
		pExportedColour = (ExportColour *)Colours.GetNext(pExportedColour);
	}

	// No - return failure.
	return NULL;
}

/********************************************************************************************

>	ExportColour *ExportedColours::GetColour(PColourRGBT *pSearchRGBCol)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/6/96
	Inputs:		pSearchRGBCol		- the simple RGB colour to search for in the list.
	Returns:	if the item is found then returns		- Pointer to the exported colour list item
				if the item is not found then returns	- NULL.
	Purpose:	Find a simpple RGB colour in the exported list.
	SeeAlso:	ExportColourList

********************************************************************************************/

ExportColour *ExportedColours::GetColour(PColourRGBT *pSearchRGBCol)
{
	if (pSearchRGBCol == NULL)
	{
		ERROR3("ExportedColours::GetColour (Simple )- searching for a null indexed colour!");
	}

	ExportColour* pExportedColour = (ExportColour *)Colours.GetHead();
	while (pExportedColour)
	{
		// Only check if this is a simple colour
		if (pExportedColour->pCol == NULL)
		{
			// Compare the simple RGB colours and return the match if they are the same
			if (
				pExportedColour->SimpleRGBColour.Red == pSearchRGBCol->Red &&
				pExportedColour->SimpleRGBColour.Green == pSearchRGBCol->Green &&
				pExportedColour->SimpleRGBColour.Blue == pSearchRGBCol->Blue &&
				pExportedColour->SimpleRGBColour.Transparent == pSearchRGBCol->Transparent
			   )
				return pExportedColour;
		}
		
		// Try the next colour in the list
		pExportedColour = (ExportColour *)Colours.GetNext(pExportedColour);
	}

	// No - return failure.
	return NULL;
}
