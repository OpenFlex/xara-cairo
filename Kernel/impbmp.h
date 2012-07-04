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


// Encapsulates a set of bitmaps imported from a file.

#ifndef INC_IMPBMP
#define INC_IMPBMP

//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class BitmapListComponent;
class KernelBitmap;

/********************************************************************************************

>	class ImportBitmap : public ListItem

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Purpose:	Represents a bitmap object that has been loaded in from the file already.
				This enables any other references to the bitmap to be resolved as we have a
				mechanism to remember that a bitmap definition has already been loaded into
				the file and the record number it was loaded under.
	SeeAlso:	BitmapListComponent;

********************************************************************************************/

class ImportBitmap : public ListItem
{
	CC_DECLARE_MEMDUMP(ImportBitmap)

public:
	// Adds a newly saved Bitmap to the list
	ImportBitmap( KernelBitmap *pNewBmp,  INT32 NewRecordNumber);

	// Pointer to the Bitmap that has been exported.
	KernelBitmap *pBmp;

	// If saved		- this will be the record number that the Bitmap definition is saved in
	// If unsaved	- this will be zero to indicate this fact
	INT32 RecordNumber;
};

/********************************************************************************************

>	class ImportBitmapList : public List

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Purpose:	Holds a list of Bitmaps that have been exported when we are saving a Version
				2 Native Camelot document out to file.
	SeeAlso:	ImportBitmap; 

********************************************************************************************/

class ImportBitmapList : public List
{
	CC_DECLARE_MEMDUMP(ImportBitmapList)

public:
	~ImportBitmapList();

public:
	ImportBitmap *AddBitmap( KernelBitmap *pBmp,  INT32 RecordNumber);	
};

/********************************************************************************************

>	class ImportedBitmaps : public CCObject

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Purpose:	Encapsulate the process of maintaining an list of Bitmaps already exported 
				from the current document out to file.
	SeeAlso:	NewImportBitmap; ImportBitmapList

********************************************************************************************/

class ImportedBitmaps : public CCObject
{
	CC_DECLARE_MEMDUMP(ImportedBitmaps)

public:
	ImportedBitmaps();
	~ImportedBitmaps();

	// Functions to add a newly exported Bitmap to the list.
	BOOL AddBitmap( KernelBitmap *pNewBmp,  INT32 RecordNumber);

	// Function for native/web filters to find an kernel bitmap from the specified
	// record number or bitmap reference
	KernelBitmap *GetBitmap(INT32 ReqRecordNumber);

protected:
	// The list of Bitmaps to add
	ImportBitmapList Bitmaps;
};


#endif  // INC_IMPBMP


