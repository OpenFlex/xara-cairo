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


// Encapsulates a set of bitmaps exported to a file.

/*
*/

#include "camtypes.h"

#include "expbmp.h"

DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_MEMDUMP(ExportBitmap, ListItem)
CC_IMPLEMENT_MEMDUMP(ExportBitmapList, List)
CC_IMPLEMENT_MEMDUMP(ExportedBitmaps, CCObject)

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	ExportBitmap::ExportBitmap(KernelBitmap *pNewBmp, INT32 NewRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pNewBmp			- the Bitmap to put in the list.
				RecordNumber	- the number of the record that this Bitmap definition has been
								  saved in.
	Purpose:	Create a new export Bitmap list item from the given indexed Bitmap.
	SeeAlso:	ExportBitmapList;

********************************************************************************************/

ExportBitmap::ExportBitmap(KernelBitmap *pNewBmp, INT32 NewRecordNumber)
{
	ERROR3IF(pNewBmp->HasBeenDeleted(), "Trying to export a deleted bitmap");

	// Initialise our class variables to these specified values.
	pBmp = pNewBmp;
	RecordNumber = NewRecordNumber;
}

/********************************************************************************************

>	ExportBitmapList::~ExportBitmapList()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroy the list of exported Bitmaps.
	SeeAlso:	ExportedBitmaps

********************************************************************************************/

ExportBitmapList::~ExportBitmapList()
{
	// Destroy the list of Bitmaps which we may have
	//ExportBitmap* pExportedBitmap = (ExportBitmap *)GetHead();
	//while (pExportedBitmap)
	//{
	//	delete pExportedBitmap;

		// Try the next Bitmap in the list
//		pExportedBitmap = (ExportBitmap *)Bitmaps.GetNext(pExportedBitmap);
//	}
	
	DeleteAll();
}

/********************************************************************************************

>	ExportBitmap *ExportBitmapList::AddBitmap(KernelBitmap *pBmp, INT32 NewRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pNewBmp			- the Bitmap to put in the list.
				RecordNumber	- the number of the record that this Bitmap definition has been
								  saved in.
	Returns:	Pointer to the newly added Bitmap, or 
				NULL if out of memory => ERROR1
	Purpose:	Add a new Bitmap to the list of exported Bitmaps.
	Errors:		Out of memory => ERROR1
	SeeAlso:	ExportBitmap

********************************************************************************************/

ExportBitmap *ExportBitmapList::AddBitmap(KernelBitmap *pBmp, INT32 NewRecordNumber)
{
	ERROR2IF(pBmp->HasBeenDeleted(), NULL, "Trying to add a deleted bitmap to the export list");

	ExportBitmap *pNewBmp = new ExportBitmap(pBmp, NewRecordNumber);

	// Check for out of memory
	if (pNewBmp == NULL)
		return NULL;

	// Add to the list and return success
	AddTail(pNewBmp);
	return pNewBmp;
}

/********************************************************************************************

>	ExportedBitmaps::ExportedBitmaps()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Construct the class which encapsulates a list of exported Bitmaps.
	SeeAlso:	ExportedBitmaps

********************************************************************************************/

ExportedBitmaps::ExportedBitmaps()
{
}

/********************************************************************************************

>	ExportedBitmaps::~ExportedBitmaps()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroy the class which encapsulates a list of exported Bitmaps.
	SeeAlso:	ExportedBitmaps

********************************************************************************************/

ExportedBitmaps::~ExportedBitmaps()
{
}

/********************************************************************************************

>	BOOL ExportedBitmaps::AddBitmap(KernelBitmap *pBmp, INT32 RecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pNewBmp			- the Bitmap to put in the list.
				RecordNumber	- the number of the record that this Bitmap definition has been
								  saved in.
	Returns:	TRUE if the Bitmap could be added;
				FALSE if not
	Purpose:	Add the specified Bitmap to the list of already exported Bitmaps.
	Errors:		-
	SeeAlso:	ExportBitmapList;

********************************************************************************************/

BOOL ExportedBitmaps::AddBitmap(KernelBitmap *pBmp, INT32 RecordNumber)
{
	ERROR2IF(pBmp->HasBeenDeleted(), FALSE, "Trying to add a deleted bitmap to the export list");

	// Add the Bitmap onto our list
	ExportBitmap * pNewBmp = Bitmaps.AddBitmap(pBmp, RecordNumber);
	if (pNewBmp)
		return TRUE;
	
	return FALSE;
}

/********************************************************************************************

>	ExportBitmap *ExportedBitmaps::GetBitmap(KernelBitmap *pSearchBmp)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pSearchBmp			- the Bitmap to search for in the list.
	Returns:	if the item is found then returns		- Pointer to the exported Bitmap list item
				if the item is not found then returns	- NULL.
	Purpose:	Find an indexed Bitmap in the exported list.
	SeeAlso:	ExportBitmapList

********************************************************************************************/

ExportBitmap *ExportedBitmaps::GetBitmap(KernelBitmap *pSearchBmp)
{
	if (pSearchBmp == NULL)
	{
		ERROR3("ExportedBitmaps::GetBitmap - searching for a null indexed Bitmap!");
	}

	ERROR2IF(pSearchBmp->HasBeenDeleted(), NULL, "Why am I looking for a deleted bitmap ?");

	ExportBitmap* pExportedBitmap = (ExportBitmap *)Bitmaps.GetHead();
	while (pExportedBitmap)
	{
		// Compare the indexed Bitmap pointers and return the match if they are the same
		if (pExportedBitmap->pBmp == pSearchBmp)
			return pExportedBitmap;
		
		// Try the next Bitmap in the list
		pExportedBitmap = (ExportBitmap *)Bitmaps.GetNext(pExportedBitmap);
	}

	// No - return failure.
	return NULL;
}


/********************************************************************************************

>	ExportBitmap* ExportedBitmaps::EnumerateBitmaps(ExportBitmap* pExpBmp)

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/96
	Inputs:		-
	Returns:	if the item is found then returns		- Pointer to the exported Bitmap list item
				if the item is not found then returns	- NULL.
	Purpose:	-
	SeeAlso:	ExportBitmapList

********************************************************************************************/

ExportBitmap* ExportedBitmaps::EnumerateBitmaps(ExportBitmap* pExpBmp)
{
	if (pExpBmp == NULL)
		return (ExportBitmap *)Bitmaps.GetHead();

	return (ExportBitmap *)Bitmaps.GetNext(pExpBmp);
}
