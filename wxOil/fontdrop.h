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


// fontdrop.h - The Colour Drop-down list support class

#ifndef INC_FONTDROP
#define INC_FONTDROP

#include "dropdown.h"
#include "fontbase.h"

class Document;

/********************************************************************************************

>	class FontDropItem : public CCObject

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95
	Purpose:	Item class for the FontDrop system

********************************************************************************************/

class FontDropItem : public ListItem
{
	CC_DECLARE_DYNCREATE(FontDropItem)

	String_64 FontName; 		// Textual name of font in question
	FontClass Type;				// What sort of font are we dealing with ?

	FontDropItem();
	FontDropItem(TCHAR *Name, FontClass FontType);

public:
	String_64	GetFontName() { return FontName; }
	void SetInfo(String_64& theFontName, FontClass theType)
		{ FontName = theFontName; Type = theType; }
};


/********************************************************************************************

>	class FontDropEnumFont : public OILEnumFonts

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95
	Purpose:	Class for enumerating the fonts for the font dropdown system

********************************************************************************************/

class FontDropEnumFont : public OILEnumFonts
{
	CC_DECLARE_DYNCREATE( FontDropEnumFont )
	
	public:
		FontDropEnumFont() { count=0; }
		INT32 GetCount() { return count; };
		virtual BOOL NewFont(FontClass Class, ENUMLOGFONT FAR* lpelf);
	
	private:
		INT32 count;
};


/********************************************************************************************

>	class FontDropDown : public DropDown

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95
	Purpose:	FontDropDown class itself

********************************************************************************************/

class FontDropDown : public DropDown
{
friend class DialogManager;

CC_DECLARE_DYNCREATE(FontDropDown)

// FontDropDown management
public:

	// Default constructor and destructor
	FontDropDown();
	virtual ~FontDropDown();

	// (Re) initialise the font list
	virtual BOOL Init(CWindowID ParentWindow, CGadgetID ParentControl);

	// Kills the list and reclaims any memory...
	void KillList(void);
	
	// Add a single font to the list
	BOOL AddFontToList(TCHAR *FontName, FontClass Type);

	// Fills in the combobox list of available fonts, and selects a useful one
	BOOL FillInFontList();

	// Update the top item above the pull-down
	BOOL SetTopFontName(StringBase* StrValue, FontClass Type, BOOL Deselect = TRUE);

	// Sets the selected item in the list
	BOOL SetSelection(FontDropItem *TheFont);

	// Decodes a selection in the list, returning the font that it references
	FontDropItem *DecodeSelection(INT32 SelectionIndex);


// Overriding methods
protected:

	virtual BOOL HasIcon(void * ItemData);
				// Returns TRUE if the item has an icon. Default is no icon

	virtual BOOL DrawIcon(void * ItemData, wxDC& dc, wxRect& IconRect, BOOL Disabled, INT32 flags);
				// Handles redraw of the icon, if any. Default is nothing gets drawn

	virtual wxString GetText(void * ItemData, INT32 Item);
				// By default returns a dummy string

// Member variables
public:
	// this is required because enumerating fonts uses a callback function...
	static void * CurrentFontDropDown;
	
	// List of font items
	List Fonts;

	BOOL m_MissingItemAdded;

	// We need a special entry for the top item...
	FontDropItem TheTopItem;

protected:
	// True if the item above the list (-1) is being redrawn...

};

/********************************************************************************************

>	class DocumentFontDropDown : public FontDropDown

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/11/95
	Purpose:	DocumentFontDropDown class itself.
				This uses the FontDropDown class to provide a font drop down but overides
				some of the functionality so that it works out the fonts in the current
				document rather than the fonts avalaible in the system.
********************************************************************************************/

class DocumentFontDropDown : public FontDropDown
{

CC_DECLARE_DYNCREATE(DocumentFontDropDown)

// DocumentFontDropDown management
public:

	// Default constructor and destructor
	DocumentFontDropDown();
	virtual ~DocumentFontDropDown();

	// Fills in the combobox list of fonts in the specified document, and selects a useful one
	BOOL FillInFontList(Document * WorkDoc);

};

#endif
