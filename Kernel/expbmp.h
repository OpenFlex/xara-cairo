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


// Encapsulates a set of bitmaps exported from a file.

#ifndef INC_EXPBMP
#define INC_EXPBMP


class BitmapListComponent;
class KernelBitmap;

/********************************************************************************************

>	class ExportBitmap : public ListItem

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Purpose:	Represents a bitmap object that has been saved out into the file already.
				This enables any other references to the bitmap to be output as we have a
				mechanism to remember that a bitmap definition has already been saved into
				the file and the record number it was saved under.
	SeeAlso:	BitmapListComponent;

********************************************************************************************/

class ExportBitmap : public ListItem
{
	CC_DECLARE_MEMDUMP(ExportBitmap)

public:
	// Adds a newly saved Bitmap to the list
	ExportBitmap( KernelBitmap *pNewBmp,  INT32 NewRecordNumber);

	// Pointer to the Bitmap that has been exported.
	KernelBitmap *pBmp;

	// If saved		- this will be the record number that the Bitmap definition is saved in
	// If unsaved	- this will be zero to indicate this fact
	INT32 RecordNumber;
};

/********************************************************************************************

>	class ExportBitmapList : public List

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Purpose:	Holds a list of Bitmaps that have been exported when we are saving a Version
				2 Native Camelot document out to file.
	SeeAlso:	ExportBitmap; 

********************************************************************************************/

class ExportBitmapList : public List
{
	CC_DECLARE_MEMDUMP(ExportBitmapList)

public:
	~ExportBitmapList();

public:
	ExportBitmap *AddBitmap( KernelBitmap *pBmp,  INT32 RecordNumber);	
};

/********************************************************************************************

>	class ExportedBitmaps : public CCObject

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Purpose:	Encapsulate the process of maintaining an list of Bitmaps already exported 
				from the current document out to file.
	SeeAlso:	NewExportBitmap; ExportBitmapList

********************************************************************************************/

class ExportedBitmaps : public CCObject
{
	CC_DECLARE_MEMDUMP(ExportedBitmaps)

public:
	ExportedBitmaps();
	~ExportedBitmaps();

	// Functions to add a newly exported Bitmap to the list.
	BOOL AddBitmap( KernelBitmap *pNewBmp,  INT32 RecordNumber);

	// Finds if we already have this Bitmap in the list
	ExportBitmap *GetBitmap( KernelBitmap *pSearchBmp);

	// Function for EPS export, so it can enumerate all the bitmaps
	ExportBitmap* EnumerateBitmaps(ExportBitmap* pExpBmp = NULL);

	// How many bitmaps are we exporting ?
	UINT32 GetCount() { return Bitmaps.GetCount(); }

protected:
	// The list of Bitmaps to add
	ExportBitmapList Bitmaps;
};


#endif  // INC_EXPBMP


