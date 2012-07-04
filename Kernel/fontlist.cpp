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


// Implementation code for the font usage list

/*
*/

#include "camtypes.h"
#include "fontlist.h"
//#include "errors.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "node.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "nodetext.h"
//#include "app.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "fontman.h"

DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_MEMDUMP(FontListItem, CC_CLASS_MEMDUMP);
CC_IMPLEMENT_MEMDUMP(FontList, CC_CLASS_MEMDUMP);

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/***********************************************************************************************

> 	FontListItem::FontListItem()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	Inputs:		-
	Returns:	-
	Purpose:	Default constructor.

***********************************************************************************************/

FontListItem::FontListItem()
{
	FontStyle=0;
	FontUsage=0;
	Class=FC_UNDEFINED;
}

/***********************************************************************************************

> 	void FontListItem::Initialise(String_64& String, INT32 Style, FontClass FClass = FC_UNDEFINED)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	Inputs:		String	- Typeface name of item
				Style	- &1 for Bold, &2 for Italic
				FClass	- FontClass of item (TrueType, ATM, etc)
	Returns:	-
	Purpose:	Initalise a fontlist item

***********************************************************************************************/

void FontListItem::Initialise(String_64& String, INT32 Style, FontClass FClass)
{
	ENSURE(FontUsage==0, "None NULL FontListItem initialised!");

	FontName=String;
	FontStyle=Style;
	FontUsage=1;
	Class=FClass;
}



/***********************************************************************************************

>	FontList::FontList()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	Inputs:		-
	Returns:	-
	Purpose:	Default constructor.

***********************************************************************************************/

FontList::FontList()
{
}

/***********************************************************************************************

> 	FontList::~FontList()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	Inputs:		-
	Returns:	-
	Purpose:	Default destructor, will remove all entries in the font list before it gets
				deleted.

***********************************************************************************************/

FontList::~FontList()
{
	TheFontList.DeleteAll();
}



/***********************************************************************************************

> 	BOOL FontList::Build(Document* pDoc)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	Inputs:		pDoc = a pointer to the document to build the fontlist for
	Returns:	TRUE if the font list was successfully built
				FALSE if not
	Purpose:	Builds a list of font names, which are used in this document. Each item in the
				list contains a usage count too.

***********************************************************************************************/

BOOL FontList::Build(Document* pDoc)
{
	ERROR2IF(pDoc==NULL,FALSE,"FontList::Build passed a NULL document");

	// Delete all previous entries
	TheFontList.DeleteAll();

	Node* pNode = pDoc->GetFirstNode();
	ENSURE(pNode != NULL,"No first node!");
	if (!EnumerateItems(pNode))
	{
		TheFontList.DeleteAll();
		return FALSE;
	}
	return TRUE;
}



/***********************************************************************************************

> 	BOOL FontList::EnumerateItems(Node* pNode)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/5/95
	Inputs:		pNode = a pointer to a node to start searching from
	Outputs:	-
	Returns:	TRUE if the whole document tree was searched
				FALSE if failed.
	Purpose:	Scans the entire tree from the node given on entry. All fonts used in this
				(sub)tree are compiled into a list. Font attributes of bold and italic are
				taken into account. Separate records are created if the same fontname has
				different style attributes applied in different areas of the tree. A usage
				count is also kept of every font found.

***********************************************************************************************/

BOOL FontList::EnumerateItems(Node* pNode)
{
	while (pNode!=NULL)
	{
		if (IS_A(pNode,TextChar))
		{
			TextChar* pChar = (TextChar*)pNode;
			AppliedAtts.RemoveAll();

			if (pChar->FindAppliedAttributes(&AppliedAtts))
			{
				void* pFontName;

				if( AppliedAtts.Lookup( CC_RUNTIME_CLASS(AttrTxtFontTypeface), pFontName ) )
				{
					void *pBold, *pItalic;
					INT32 style=0;

					if( AppliedAtts.Lookup( CC_RUNTIME_CLASS(AttrTxtBold), pBold ) )
					{
						AttrTxtBold* pBoldAttr = (AttrTxtBold*) pBold;
						TxtBoldAttribute* pAttr = &(pBoldAttr->Value);
						if ((pAttr) && (pAttr->BoldOn))
							style+=1;
					}

					if( AppliedAtts.Lookup(  CC_RUNTIME_CLASS(AttrTxtItalic), pItalic ) )
					{
						AttrTxtItalic* pItalicAttr = (AttrTxtItalic*)pItalic;
						TxtItalicAttribute* pAttr = &(pItalicAttr->Value);
						if ((pAttr) && (pAttr->ItalicOn))
							style+=2;
					}

					AttrTxtFontTypeface* pFontAttr = (AttrTxtFontTypeface*)pFontName;

					FontClass Class = FONTMANAGER->GetFontClass(pFontAttr->Value.HTypeface);

				 	String_64 FName;
					if (FONTMANAGER->GetFontName(pFontAttr->Value.HTypeface, FName))
					{
						FontListItem* FListObj = FindFontMatch(FName,style);
						if (FListObj)
							FListObj->IncUsage();
						else
						{
							FListObj = new FontListItem;
							if (!FListObj)
								return FALSE;

							FListObj->Initialise(FName,style, Class);
							AddItem(FListObj);
						}
					}
				}
			}
		}

		Node* qNode=pNode->FindFirstChild();
		if (qNode)
		{
			if (!EnumerateItems(qNode))
				return FALSE;
		}

		pNode=pNode->FindNext();
	}

	return TRUE;
}



/***********************************************************************************************

> 	FontListItem* FontList::FindFontMatch(const String_64& FName, INT32 style, FontClass Class = FC_UNDEFINED)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/12/94
	Inputs:		fname = a font name to search for
				style = a style word
						b0 = 1 then bold is current
						b1 = 1 then italic is current
				Class = Font class of item
	Outputs:	-
	Returns:	NULL if unable to find a match for this font name in the list
	Purpose:	Trys to find the font name in our list

***********************************************************************************************/

FontListItem* FontList::FindFontMatch(const String_64& fname, INT32 style, FontClass Class)
{
	FontListItem* pFont = GetFirstItem();
	while (pFont!=NULL)
	{
		if ( (pFont->GetFontName()==fname) && 
			 (pFont->GetFontStyle()==style) &&
 			 ((pFont->GetFontClass()==Class) || Class == FC_UNDEFINED)
		   )
			return pFont;

		pFont = GetNextItem(pFont);
	}
	return NULL;
}


/***********************************************************************************************

> 	BOOL FontList::AddItem(FontListItem* pFListItem)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/12/94
	Inputs:		pFListItem = ptr to a font item to add to our list
	Outputs:	-
	Returns:	TRUE if successfully initialises, FALSE otherwise
	Purpose:	Adds a font list item to our list

***********************************************************************************************/

BOOL FontList::AddItem(FontListItem* pFListItem)
{
	TheFontList.AddTail(pFListItem);
	return TRUE;
}


/***********************************************************************************************

>	FontListItem* FontList::GetFirstItem()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	Inputs:		-
	Outputs:	-
	Returns:	First Font object in the list, or NULL if the list is empty
	Purpose:	Lets you get the first Font object in the list

***********************************************************************************************/

FontListItem* FontList::GetFirstItem()
{
	return ((FontListItem*)TheFontList.GetHead());
}

/***********************************************************************************************

>	FontListItem* FontList::GetNextItem(FontListItem* pCurrFontItem)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	Inputs:		pCurrFontItem = ptr the current font item in the list
	Outputs:	-
	Returns:	Returns the next font item after pCurrFontItem, 
				or NULL if there isn't a next one
	Purpose:	Lets you get the next font item in the list

***********************************************************************************************/

FontListItem* FontList::GetNextItem(FontListItem* pCurrFontItem)
{
	return ((FontListItem*)TheFontList.GetNext(pCurrFontItem));
}




/*
BOOL KernCode::ExportRender(RenderRegion* pRegion)
{
#if EXPORT_TEXT
 	if (pRegion->IsKindOf(CC_RUNTIME_CLASS(EPSRenderRegion)))
	{
		EPSExportDC *pDC=(EPSExportDC*)pRegion->GetRenderDC();

		// Use illustrator 3.0 compatible token.
		// Any vertical movement is done by BaselineShift
		INT32 autokern = 0;
		pDC->OutputValue(autokern);
		pDC->OutputValue(Value.x);
 		pDC->OutputToken("Tk");
		pDC->OutputNewLine();
		return TRUE;
	}
#endif
	return FALSE;
}
*/
