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

/*
 * */
// The BaseDocument class

#ifndef INC_BASEDOC
#define INC_BASEDOC

#include "listitem.h"
#include "colcarry.h"

class DocComponent;
class ColourList;
class Node;

class ExportHint;

/********************************************************************************************

< TAG_LAST_VALID

	Comment:	This tag value indicate the range of valid tags that can be used in a
				document.  0 is not used, so the tags 1 to TAG_LAST_VALID are the only ones
				that can be used in a document.
	SeeAlso:	Node::GetTag; TAG_NOT_IN_DOC

********************************************************************************************/ 

#define TAG_LAST_VALID 	(0xFFFFFFFE)


/********************************************************************************************

< TAG_NOT_IN_DOC

	Comment:	This tag value is used to indicate that a node is not in a document yet.
	SeeAlso:	Node::GetTag; TAG_LAST_VALID

********************************************************************************************/ 

#define TAG_NOT_IN_DOC 	(0xFFFFFFFF)


/*********************************************************************************************
>	class BaseDocument: public ListItem

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com> 
	Created:	20/07/94
	Purpose:	A simple base class document object 
	Errors:		-
*********************************************************************************************/

class BaseDocument : public ListItem
{
	CC_DECLARE_DYNAMIC(BaseDocument);

///////////////////////////////////////////////////////////////////////////////////////
// Construction & destruction

public:
	BaseDocument(BOOL fHide = TRUE);
	virtual ~BaseDocument();
	BOOL Init();			// Initialise document, cf. Document::Init
	
	BOOL FixColourRefsAfterCopy(BaseDocument* SourceDocument);

	// Post import related funcs
	void PostImport();
	BOOL CheckReferences();
	BOOL CheckFontSubstitution();
	BOOL CheckEffects();

	ListRange* GetEffectsList(UINT32 iMaxItems);

///////////////////////////////////////////////////////////////////////////////////////
// Visibility - determining if a document is hidden, or is the clipboard
// (Hidden/clipboard docs have no associated Views, and are not in the application
// list of documents. Some code may need to be careful when in the clipboard.
// Hidden/Clipboard documents may or may not have a CCamDoc attached)

protected:
	BOOL IsHidden;

public:
	BOOL IsAHiddenDoc() const				{ return IsHidden; };
			// Returns TRUE if this document is hidden (is not shown in any UI)

	BOOL IsNotAHiddenDoc() const			{ return !IsHidden; };
			// Returns TRUE if this document is NOT hidden (is not shown in any UI)

public:
	ExportHint* GetExportHint(void) { return(m_pExportHint); };

protected:
	ExportHint* m_pExportHint;



///////////////////////////////////////////////////////////////////////////////////////
// All about Nodes . . .

protected:
	Node* TreeStart;						// address of first object in our tree
	INT32 NodesInTree;						// count of objects in our tree

public:
	Node* GetFirstNode() const;

	void DeleteContents(); 

	TAG NewTag();

	void IncNodeCount();
	void DecNodeCount();

	INT32 NodesInDocument() const;


///////////////////////////////////////////////////////////////////////////////////////
// The document components for this document

public:
	BOOL InitDocComponents(void);		// Internal init/deiit of components. Also
	void DestroyDocComponents(void);	// used by when clearing the clipboard doc.

	void AddDocComponent(DocComponent *);
	DocComponent *GetDocComponent(CCRuntimeClass *);
	DocComponent *GetDocComponentKindOf(CCRuntimeClass *);
	DocComponent *EnumerateDocComponents(DocComponent*);


///////////////////////////////////////////////////////////////////////////////////////
// Colour: Default colour context array, document IndexedColour list

protected:
	ColourContextArray	DefaultColourContexts;

public:
	ColourContextArray *GetDefaultColourContexts(void);
	ColourList *GetIndexedColours(void);

	virtual BOOL StartComponentCopy();
	virtual BOOL EndComponentCopy(); 
	virtual void AbortComponentCopy();  

protected:
	List *DocComponents;

private:
	TAG TagCounter;						// unique ID for nodes
};

#endif	// INC_BASEDOC
