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


// Encapsulates a set of colours imported from a file.

#ifndef INC_IMPCOL
#define INC_IMPCOL

//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "colourix.h"
//#include "colmodel.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class ColourListComponent;

/********************************************************************************************

<	ImportedNewColour

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18 03 95
	Purpose:	A structure to hold a new colour, which can be represented in any colour
				model. Uses a ColourGeneric which must be cast because C++ can't do unions
				in any useful way.
	SeeAlso:	ImportedColours

********************************************************************************************/

typedef struct
{
	ColourModel		Model;
	ColourGeneric	Colour;
} ImportedNewColour;

/********************************************************************************************

>	class NewColour : public ListItem

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/94
	Purpose:	Represents a new colour object to be added to a document after a file
				has beeen imported.  It holds information on whether the colour name
				will need to be mangled
	SeeAlso:	NewColourList; ImportedColours

********************************************************************************************/

class NewColour : public ListItem
{
	CC_DECLARE_MEMDUMP(NewColour)

public:
	NewColour(IndexedColour*, BOOL);

	// Adds a colour to the list which duplicates this name
	BOOL AddDuplicateColour(IndexedColour **pNewCol, BOOL AlreadyExists);

	// Pointer to the new colour - can point to a colour that already exists in the document.
	IndexedColour *pCol;

	// This is TRUE if this colour is one that already exists in the document.
	// (i.e. pCol points to a colour that is in the document)
	BOOL AlreadyExistsInDoc;

	// TRUE if colour *name* has been defined more than once in the file being imported.
	// In this case, there is a list of such dupes (see pNextDuplicate, below)
	BOOL Duplicate;

	// Cached CMYK definition for comparing colours on CMYK values.
	PColourCMYK ColDefn;

	// If Duplicate is TRUE, this points to another imported colour that uses the same
	// name as this one.  Hence we have a simple one-way linked list here - this is
	// enough for our purposes.
	NewColour *pNextDuplicate;

// New bits for native/web file filter
	// If loaded	- this will be the record number that the colour definition has been loaded from
	// If unsaved	- this will be zero to indicate the fact that this colour has not been imported
	INT32 RecordNumber;

	// the desired entry number for this colour in the list
	UINT32 EntryNumber;
};



/********************************************************************************************

>	class NewColourList : public List

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/94
	Purpose:	Holds a list of colours that are imported while importing a file into
				a Camelot document.
	SeeAlso:	NewColour; ImportedColours

********************************************************************************************/

class NewColourList : public List
{
	CC_DECLARE_MEMDUMP(NewColourList)

public:
	NewColour *AddColour(IndexedColour *pCol, BOOL AlreadyExists);	

	// We need to over-ride this because some items hold more than one colour.
	DWORD GetCount() const;							
};


class NewColourInfo
{
public:
	NewColourInfo();

public:
	// Field that says what kind of colour this is.
	IndexedColourType Type;

	// Flag for each colour component - defaults to no inheritance at all - only used
	// if Type is NEWCOLOUR_LINKED.
	BOOL Inherits[4];

	// Tint value - only used if Type is COLOURTYPE_TINT. 
	// (defaults to 100%, i.e. original colour)
	FIXED24 TintValue;
	FIXED24 ShadeValue;

	// Tint modifier - if it is COLOURTYPE_TINT, this flag is TRUE if the tint is really a shade!
	// (Shades are treated as special cases of tints for historical reasons)
	BOOL TintIsShade;

// New bits for native/web file filter
	// Flags whether this colour is being imported by the web/native filter and therefore
	// has a different way of defining the parent colour
	BOOL WebNativeColour;

	// Pointer to the colour that has been imported.
	IndexedColour *pParentCol;

	// If loaded	- this will be the record number that the colour definition has been loaded from
	// If unsaved	- this will be zero to indicate the fact that this colour has not been imported
	INT32 RecordNumber;
	
	// the desired entry number for this colour in the list
	UINT32 EntryNumber;
};



/********************************************************************************************

>	class ColourImportContext : public List

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/12/94
	Purpose:	Provides a colour context to use when importing colours, which allows us
				to easily import arbitrarily nested linked colours.
	SeeAlso:	ContextItem; ImportedColours

********************************************************************************************/

class ColourImportContext : public List
{
	CC_DECLARE_MEMDUMP(ColourImportContext);

public:
	ColourImportContext();
	~ColourImportContext();

	BOOL Init();

	void SetContext(IndexedColour*);
	IndexedColour *GetContext();

	BOOL SaveContext();
	BOOL RestoreContext();
	BOOL RestoreContextTo(UINT32);
};


/********************************************************************************************

>	class ImportedColours : public CCObject

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/94
	Purpose:	Encapsulate the process of importing a number of colours into a document.
				This object maintains a list of colours to be imported, and implicitly 
				handles all the merging/duplication problems that may occur.
	SeeAlso:	NewColour; NewColourList

********************************************************************************************/

class ImportedColours : public CCObject
{
	CC_DECLARE_MEMDUMP(ImportedColours)

public:
	ImportedColours(ColourListComponent*, BOOL);
	~ImportedColours();

	BOOL Init();

	// Overloaded functions to add new colours to the table.
	BOOL AddColour(const String_64 *pColName, ColourCMYK  *pCMYK, 
				   NewColourInfo *pLinkInfo = NULL);
	BOOL AddColour(const String_64 *pColName, ColourRGBT  *pRGB,  
				   NewColourInfo *pLinkInfo = NULL);
	BOOL AddColour(const String_64 *pColName, ColourHSVT  *pHSV,  
				   NewColourInfo *pLinkInfo = NULL);
	BOOL AddColour(const String_64 *pColName, ColourGreyT *pGrey, 
				   NewColourInfo *pLinkInfo = NULL);
	BOOL AddColour(const String_64 *pColName, ImportedNewColour *pCol, 
				   NewColourInfo *pLinkInfo = NULL);

	// New function added for native/web import
	BOOL AddTintOrShade(const String_64 *pColName, NewColourInfo *pColourInfo);

	// Functions to add tints/shades and manipulate linked colours
	BOOL AddTint(const String_64 *pColName, UINT32 Tint);
	BOOL AddShade(const String_64 *pColName, INT32 ShadeX, INT32 ShadeY);
	void SetLinkedColourInherits(UINT32 ComponentID);

	// Functions to update the context stack for tinting and linking colours.
	void SaveContext();
	void RestoreContextTo(UINT32 Level);

	// Works out which new colour is referred to by this name
	IndexedColour *GetColour( PCTSTR ColName);

	// Works out which new colour is referred to by this name - intelligently
	// decides whether to use the CMYK definition to resolve ambiguities.
	IndexedColour *GetColour( PCTSTR ColName, const PColourCMYK *Defn);

	// Import has finished successfully- add the colours into the document
	// in an undoable way.
	BOOL AddColoursToDocument();

	BOOL SortColoursByEntryNumber();

	// Import failed - destroy colours and do not add them to the document.
	BOOL DestroyColours();

	// Function for native/web filters to find an indexed colour from the specified
	// record number or colour reference
	IndexedColour *GetColour(INT32 ReqRecordNumber);

protected:
	// The sort comparator we use for SortColoursByEntryNumber()
	static INT32 __cdecl SortComparator(const void *Item1, const void *Item2);

	// The list of colours to add
	NewColourList Colours;

	// A hash table from colour names to NewColour items.
	typedef CMap< String_64, const String_64 &, NewColour *, NewColour * > 	CMapStringToNewColour;
	CMapStringToNewColour	*pColourMap;

	// The colour list component of the destination document.
	ColourListComponent *pColourComponent;

	// Used to remember which colours to link to or tint.
	ColourImportContext Context;

	// Indicates whether to check the CMYK values when servicing calls to GetColour().
	BOOL StrictColourMatching;

protected:
	BOOL AddColour(const String_64 *pColName, IndexedColour **pCol, 
				   NewColourInfo *pLinkInfo = NULL);
};


#endif  // INC_IMPCOL


