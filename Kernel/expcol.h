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


// Encapsulates a set of colours exported from a file.

#ifndef INC_EXPCOL
#define INC_EXPCOL


class ColourListComponent;
class IndexedColour;

/********************************************************************************************

>	class ExportColour : public ListItem

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Purpose:	Represents a colour object that has been saved out into the file already.
				This enables any other references to the colour to be output as we have a
				mechanism to remember that a colour definition has already been saved into
				the file and the record number it was saved under.
	SeeAlso:	ColourListComponent;

********************************************************************************************/

class ExportColour : public ListItem
{
	CC_DECLARE_MEMDUMP(ExportColour)

public:
	// Adds a newly saved colour to the list
	ExportColour( IndexedColour *pNewCol,  INT32 NewRecordNumber);

	// Adds a newly exported simple colour to the list.
	ExportColour( PColourRGBT *pNewRGBCol,  INT32 NewRecordNumber);

	// Pointer to the colour that has been exported.
	IndexedColour *pCol;

	// If it is a simple colour then pCol will be NULL and we will need to save out the RGB
	// colour. This will be saved in a *packed* (8-bit components) colour structure
	PColourRGBT SimpleRGBColour;

	// If saved		- this will be the record number that the colour definition is saved in
	// If unsaved	- this will be zero to indicate this fact
	INT32 RecordNumber;
};

/********************************************************************************************

>	class ExportColourList : public List

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Purpose:	Holds a list of colours that have been exported when we are saving a Version
				2 Native Camelot document out to file.
	SeeAlso:	ExportColour; 

********************************************************************************************/

class ExportColourList : public List
{
	CC_DECLARE_MEMDUMP(ExportColourList)

public:
	~ExportColourList();

public:
	ExportColour *AddColour( IndexedColour *pCol,  INT32 RecordNumber);	
	ExportColour *AddColour( PColourRGBT *pNewRGBCol,  INT32 RecordNumber);	
};

/********************************************************************************************

>	class ExportedColours : public CCObject

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/96
	Purpose:	Encapsulate the process of maintaining an list of colours already exported 
				from the current document out to file.
	SeeAlso:	NewExportColour; ExportColourList

********************************************************************************************/

class ExportedColours : public CCObject
{
	CC_DECLARE_MEMDUMP(ExportedColours)

public:
	ExportedColours();
	~ExportedColours();

	// Functions to add a newly exported colour to the list.
	BOOL AddColour( IndexedColour *pNewCol,  INT32 RecordNumber);

	// Functions to add a newly exported simple colour to the list.
	BOOL AddColour( PColourRGBT *pNewRGBCol,  INT32 RecordNumber);

	// Finds if we already have this colour in the list
	ExportColour *GetColour( IndexedColour *pSearchCol);

	// Finds if we already have this simple RGB colour in the list
	ExportColour *GetColour( PColourRGBT *pNewRGBCol);

protected:
	// The list of colours to add
	ExportColourList Colours;
};


#endif  // INC_EXPCOL


