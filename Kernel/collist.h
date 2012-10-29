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


// collist.h - the ColourList class


#ifndef INC_COLLIST
#define INC_COLLIST


class BaseDocument;

class IndexedColour;
class Document;



/***********************************************************************************************

>	class ColourList : public List

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Purpose:	A colour list is held by each document to store the list of available
				IndexedColours for use by that document. (This colour list is displayed
				in the ColourBar/ColourGallery via the ColGalDisplayList which references
				colours held in the ColourList).

				The ColourList also provides a couple of special access methods for
				determining the number of visible/undeleted colours in the document
				(deleted colours are still held in this list, but are marked deleted
				for undo purposes - if scanning the ColourList, remember to check
				IndexedColours IsDeleted() flag) -- See the Undeleted list operators
				provided by this class to save you loads of effort.

				The Colour list also includes another simple List of unnamed colours
				which are used for local colour attributes in a document. Unnamed
				colours are simply stored in this list, and are simpler than named 
				colours...

	SeeAlso:	IndexedColour; ColGalDisplayList; BaseDocument; List

***********************************************************************************************/

class ColourList : public List
{
CC_DECLARE_MEMDUMP(ColourList)

public:		// Construction/Initialisation
	ColourList();
	~ColourList();

	void Init(BaseDocument *ParentDocument);

public:		// Overridden List interface
	void AddHead(ListItem *);			// Overridden List members: You MUST use AddItem
	void AddTail(ListItem *);

	BOOL AddItem(IndexedColour *NewColour);	// Add a colour, ensuring it has a unique name


	// Overrides (well, they would be if the base class had made these virtual!) which call
	// the base class after first ensuring the name is unique
	LISTPOS InsertBefore(LISTPOS here, ListItem* item);
	ListItem *InsertBefore(ListItem* here, ListItem* item);

	LISTPOS InsertAfter(LISTPOS here, ListItem* item);
	ListItem *InsertAfter(ListItem* here, ListItem* item);

	// Override DeleteAll to do safe deletion of linked colours
	virtual void DeleteAll();
	

public:		// Special ColourList listy methods
	UINT32 GetUndeletedCount(void);
	IndexedColour *FindUndeletedItem(INT32 Index);
	IndexedColour *GetUndeletedHead(void);
	IndexedColour *GetUndeletedNext(IndexedColour *ThisItem);
		// Count/Find/Head/Next functions which ignore 'deleted' IndexedColours

	inline BaseDocument *GetParentDocument(void);
		// Find the document in which this colour list resides

private:
	BaseDocument *ParentDoc;

public:		// Special linking inheritance support
	IndexedColour **CompileInheritanceArray(IndexedColour *Parent);
		// Compiles a NULL-terminated array of pointers to all colours which are linked
		// to this, both directly and indirectly (i.e. an array listing the entire
		// inheritance 'subtree' from (and including) 'Parent')

	void RemoveLinksToColour(IndexedColour *DeadColour);
		// Ensures no other colours have this colour as a linked parent

	BOOL IsColourInUseInDoc(IndexedColour *TheColour, BOOL IgnoreColourGallery = FALSE);
		// Determines if a colour is used in the document either directly (DocColour Ref)
		// or indirectly (parent/ancestor of a linked/tint colour which is used in the doc)

	void InvalidateInheritanceCache(void);
		// Invalidates the cached results of the above function

private:	// Private variables for inheritance support
	IndexedColour *ArrayParent;				// Current parent of the cached array
	IndexedColour **InheritanceArray;		// Cached array of all offspring of ArrayParent

public:		// Named colour support
	BOOL NamedColourExists( PCTSTR pName );
	BOOL NamedColourExists(const StringBase *pName);
		// Returns TRUE if the given name is in use by any item in this colour list

	BOOL GenerateUniqueColourName(const StringBase *pPrefix, String_64 *pResult);
		// Outputs a name (Based on pPrefix) that is unique in this ColourList
		// Returns TRUE if the output name is different from the pPrefix string

private:	// Private data for named colour support
	INT32 LastUnnamedColour;					// Kept to optimise unnamed colour naming

public:		// Unnamed colour storage support
	inline List *GetUnnamedColours(void);

private:	// Private data for unnamed colours
	List UnnamedColours;
};



/**********************************************************************************************

>	inline BaseDocument *ColourList::GetParentDocument(void)

	Author: 	Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/11/94
	Returns:	The document in which this colour list resides
	Purpose:	To find the parent document of this colour list

**********************************************************************************************/

BaseDocument *ColourList::GetParentDocument(void)
{
	ERROR3IF(ParentDoc == NULL, "Uninitialised ColourList detected!");
	return(ParentDoc);
}



/**********************************************************************************************

>	inline List *ColourList::GetUnnamedColours(void)

	Author: 	Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/3/95
	Returns:	The storage-list containing this document's unnamed colours
	Purpose:	To find the unnamed colours for this document

**********************************************************************************************/

List *ColourList::GetUnnamedColours(void)
{
	return(&UnnamedColours);
}


#endif

