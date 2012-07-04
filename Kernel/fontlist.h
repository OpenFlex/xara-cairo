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


// The header file for class descriptions of the font usage list.
           
/*
*/

#ifndef INC_FONTLIST
#define INC_FONTLIST

//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "attrmap.h"
//#include "fontbase.h"

class Document;
class Node;

/***********************************************************************************************

>	class FontListItem: public ListItem

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	Purpose:	A class to describe the structure of an item held in the font usage list.
				An item simply contains a fontname and a usage count

***********************************************************************************************/

class FontListItem: public ListItem
{
	CC_DECLARE_MEMDUMP(FontListItem);

public:
	FontListItem();

	void		Initialise(String_64& String, INT32 Style, FontClass = FC_UNDEFINED);
	void		IncUsage() { FontUsage++; }

	String_64	GetFontName() { return FontName; }
	INT32		GetFontStyle() { return	FontStyle; }
	INT32		GetFontUsage() { return	FontUsage; }
	FontClass	GetFontClass() { return	Class; }

private:
	String_64	FontName;
	INT32		FontStyle;
	INT32		FontUsage;
	FontClass	Class;
};


/***********************************************************************************************

>	class FontList : public CC_CLASS_MEMDUMP

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/12/94
	Purpose:	A class which can be used to create a font usage list. Create an instance of
				this class and pass its Build() function a particular document pointer. The
				function will create a list of used fonts in that particular document, each
				item of which will contain a font name and usage count

***********************************************************************************************/

class FontList : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(FontList);

public:
	 FontList();
	~FontList();

	BOOL 			Build(Document* pDoc);
	BOOL			AddItem(FontListItem* pFontListObj);
	FontListItem*	GetFirstItem();
	FontListItem*	GetNextItem(FontListItem* pCurrItem);
	FontListItem*	FindFontMatch(const String_64& FName, INT32 style, FontClass Class = FC_UNDEFINED);

private:
	BOOL 			EnumerateItems(Node* pNode);

private:
	List			TheFontList;
	CCAttrMap		AppliedAtts;
};


#endif
