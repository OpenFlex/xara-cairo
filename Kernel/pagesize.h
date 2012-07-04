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

//
// Encapsulates the page sizes available in Camelot.

#ifndef INC_PAGESIZES
#define INC_PAGESIZES

//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "units.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// Page sizes that are allowed in the sizes list
// The ordering of the ids must correspond to the ordering of the page size
// definitions in PageSizesList::InitPageSizes()
enum PageId {CUSTOM, A0, A1, A2, A3, A4, A5, A6, USLEGAL, USLETTER, FANFOLD}; 

// These are now loaded in and will be calculated as the page size is defined
// just need the new last ID = the next ID to be used when the neex page is defined 
// Above still required as if no ini files is found or problems happen with the ini
// file then we use the built in defaults
#define LASTPAGE A0; 

class CCLexFile;

/********************************************************************************************

>	class PageSize : public ListItem

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>		
	Created:	12/12/94	
	Purpose:	Encapsulates all the page size information and functionality in one class.
				The class knows what size an A4 page is and what its textual name is.

********************************************************************************************/

class CCAPI PageSize : public ListItem
{
	CC_DECLARE_DYNAMIC(PageSize);

public:
	PageSize();								// Constructor

	// Initialisation
	virtual BOOL Init(PageId NewId, String_32 *Name, double PageWidth, double PageHeight,
					  UnitType Units);

	PageId GetPageId();		 				// Returns page id
	String_32 *GetPageName();				// returns name of page
	INT32 GetPageWidth();					// returns width of page
	INT32 GetPageHeight();					// returns height of page

protected:
	PageId Id;								// id assigned to this page e.g. A4
	String_32 PageName;						// Textual page name for use in lists etc.
	INT32 PageWidth;							// Width of this page in millipoints
	INT32 PageHeight;						// Height of this page in millipoints
	double PageWidthInMM;					// Width of this page in mm
	double PageHeightInMM;					// Height of this page in mm
};

/********************************************************************************************

>	class PageSizesList : public List

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>		
	Created:	12/12/94	
	Purpose:	Encapsulates all the page size information and functionality in one class.
				The class knows what size an A4 page is and what its textual name is.

********************************************************************************************/

class PageSizesList : public List
{
	CC_DECLARE_DYNAMIC(PageSizesList);

public:
	PageSizesList();						// Constructor
	~PageSizesList();						// Destructor

	BOOL InitPageSizes();					// set up all page sizes available
	BOOL DeinitPageSizes();					// remove all page sizes available

	PageSize *GetFirstPageSize();
	PageSize *GetNextPageSize(PageSize*);

	// Function to declare a page size to the PageSizes system
	BOOL DeclarePageSize(PageId NewId, String_32 *Name, double Width, double Height,
						 UnitType Units, PageSize **pPageSize);

	BOOL DeclarePageSize(PageId NewId, ResourceID r, double Width, double Height,
						UnitType Units, PageSize **pPageSize)
						{ String_32 Name(r); return DeclarePageSize(NewId, &Name, Width, Height, Units, pPageSize); }

	// Useful functions which are supplied by each page size in the list
	String_32* GetTextualDescription(PageId ThisId);
	PageId GetPageIdFromSize(INT32 Width, INT32 Height);
	BOOL GetSizeFromPageId(PageId ThisId, INT32 *Width, INT32 *Height);

private:
	// Functions for reading page sizes from either the resource or from
	// an ini file
	BOOL ReadPageSizes();

	BOOL ReadPageSizesFromDisk();
	BOOL ReadPageSizesFromRes();
	BOOL ReadPageSizesFromFile(CCLexFile& file);

	BOOL ReadPageSizesList(CCLexFile& file);

	// Main function that actually does the reading in of the data
	BOOL ReadPageSizeDef(CCLexFile& file, String_32* pPageName, double* pWidth, 
						 double* pHeight, UnitType* pUnits);

	// This stores the next page id that is going to be allocated when a new page
	// is created. 
	INT32	MaxPageId;

	// This stores the error id for later use. 
	UINT32 ErrorId;
};

#endif  // INC_PAGESIZE


