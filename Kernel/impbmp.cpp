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

#include "impbmp.h"
//#include "bitmap.h" - in camtypes.h [AUTOMATICALLY REMOVED]

DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_MEMDUMP(ImportBitmap, ListItem)
CC_IMPLEMENT_MEMDUMP(ImportBitmapList, List)
CC_IMPLEMENT_MEMDUMP(ImportedBitmaps, CCObject)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	ImportBitmap::ImportBitmap(KernelBitmap *pNewCol, INT32 NewRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pNewBmp			- the Bitmap to put in the list.
				RecordNumber	- the number of the record that this Bitmap definition has been
								  saved in.
	Purpose:	Create a new export Bitmap list item from the given indexed Bitmap.
	SeeAlso:	ImportBitmapList;

********************************************************************************************/

ImportBitmap::ImportBitmap(KernelBitmap *pNewBmp, INT32 NewRecordNumber)
{
	// Initialise our class variables to these specified values.
	pBmp = pNewBmp;
	RecordNumber = NewRecordNumber;
}

/********************************************************************************************

>	ImportBitmapList::~ImportBitmapList()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroy the list of exported Bitmaps.
	SeeAlso:	ImportedBitmaps

********************************************************************************************/

ImportBitmapList::~ImportBitmapList()
{
	// Destroy the list of Bitmaps which we may have
	//ImportBitmap* pExportedBitmap = (ImportBitmap *)GetHead();
	//while (pExportedBitmap)
	//{
	//	delete pExportedBitmap;

		// Try the next Bitmap in the list
//		pExportedBitmap = (ImportBitmap *)Bitmaps.GetNext(pExportedBitmap);
//	}
	
	DeleteAll();
}

/********************************************************************************************

>	ImportBitmap *ImportBitmapList::AddBitmap(KernelBitmap *pBmp, INT32 NewRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pNewBmp			- the Bitmap to put in the list.
				RecordNumber	- the number of the record that this Bitmap definition has been
								  saved in.
	Returns:	Pointer to the newly added Bitmap, or 
				NULL if out of memory => ERROR1
	Purpose:	Add a new Bitmap to the list of exported Bitmaps.
	Errors:		Out of memory => ERROR1
	SeeAlso:	ImportBitmap

********************************************************************************************/

ImportBitmap *ImportBitmapList::AddBitmap(KernelBitmap *pBmp, INT32 NewRecordNumber)
{
	ImportBitmap *pNewBmp = new ImportBitmap(pBmp, NewRecordNumber);

	// Check for out of memory
	if (pNewBmp == NULL)
		return NULL;

	// Add to the list and return success
	AddTail(pNewBmp);
	return pNewBmp;
}

/********************************************************************************************

>	ImportedBitmaps::ImportedBitmaps()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Construct the class which encapsulates a list of exported Bitmaps.
	SeeAlso:	ImportedBitmaps

********************************************************************************************/

ImportedBitmaps::ImportedBitmaps()
{
}

/********************************************************************************************

>	ImportedBitmaps::~ImportedBitmaps()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroy the class which encapsulates a list of exported Bitmaps.
	SeeAlso:	ImportedBitmaps

********************************************************************************************/

ImportedBitmaps::~ImportedBitmaps()
{
	// Delete all the bitmaps in the list, as copies will have been made to
	// put in the tree

	ImportBitmap* pBitmap = (ImportBitmap *)Bitmaps.GetHead();
	while (pBitmap != NULL)
	{
		if (pBitmap->pBmp &&
			pBitmap->pBmp->GetParentBitmapList() == NULL)
		{
			// Only delete the bitmap if it has a NULL parent bitmap list,
			// because otherwise it means they are being used
			delete pBitmap->pBmp;
		}

		// Try the next Bitmap in the list
		pBitmap = (ImportBitmap *)Bitmaps.GetNext(pBitmap);
	}

}

/********************************************************************************************

>	BOOL ImportedBitmaps::AddBitmap(KernelBitmap *pBmp, INT32 RecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pNewBmp			- the Bitmap to put in the list.
				RecordNumber	- the number of the record that this Bitmap definition has been
								  saved in.
	Returns:	TRUE if the Bitmap could be added;
				FALSE if not
	Purpose:	Add the specified Bitmap to the list of already exported Bitmaps.
	Errors:		-
	SeeAlso:	ImportBitmapList;

********************************************************************************************/

BOOL ImportedBitmaps::AddBitmap(KernelBitmap *pBmp, INT32 RecordNumber)
{
	// Add the Bitmap onto our list
	ImportBitmap * pNewBmp = Bitmaps.AddBitmap(pBmp, RecordNumber);
	if (pNewBmp)
		return TRUE;
	
	return FALSE;
}

/********************************************************************************************

>	KernelBitmap *ImportedBitmaps::GetBitmap(INT32 ReqRecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		ReqRecordNumber	- the record number to search the list for
	Returns:	Pointer to the KernelBitmap if successful;
				NULL if not found.
	Purpose:	Searches for a previously imported bitmap definition. Used by the native/web
				filter to convert a bitmap reference in a record to an KernelBitmap. This
				must have already been imported in the file as the rule is that reference to
				bitmaps can only be made if the bitmap definition has already been output.
	Errors:		-
	SeeAlso:	ImportedBitmaps; BitmapListComponent;

********************************************************************************************/

KernelBitmap *ImportedBitmaps::GetBitmap(INT32 ReqRecordNumber)
{
	// Work our way through the list of imported bitmaps until we find the required record number
	ImportBitmap* pBitmap = (ImportBitmap *)Bitmaps.GetHead();
	while (pBitmap != NULL)
	{
		if (pBitmap->RecordNumber == ReqRecordNumber)
			return pBitmap->pBmp;

		// Try the next Bitmap in the list
		pBitmap = (ImportBitmap *)Bitmaps.GetNext(pBitmap);
	}

	// Something went a bit wrong and we didn't find the requested record number
	// return NULL to the caller 
	return NULL;
}

