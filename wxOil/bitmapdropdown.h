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


// coldrop.h - The Colour Drop-down list support class

#ifndef BITMAPDROPDOWN_H
#define BITMAPDROPDOWN_H

#include "dropdown.h"
//#include "gbrush.h"
//#include "pump.h"



/*************************************************************************
Class         : wxCamBitmapDropdownPopup 
Base Class    : public wxCamVListBoxComboPopu
Author        : Mikhail Tatarnikov
Description   : Represents popup list for the bitmap control.
Pure Virtual  : No
Known Issues  : None
Usage Notes   : Required to specify size of the list - if the bitmap is smaller
				then the control width, the dropdown should be of the bitmap size.
				Also the "unselected" item should be painted separately.
Override Notes: None
**************************************************************************/
class wxCamBitmapDropdownPopup : public wxCamVListBoxComboPopup
{
public:
	wxCamBitmapDropdownPopup(DropDown * pDropDown=NULL) :
		wxCamVListBoxComboPopup(pDropDown)
	{
	} 
	
	// Redraws the combo control itself.
    virtual void PaintComboControl(wxDC& dc, const wxRect& rect);


	// Calculates the dropdown size. We need to override it to allow the dropdown list to have smaller
	// width that the cobobox itself (in  case we have images only).
    virtual wxSize GetAdjustedSize(int /* TYPENOTE: Correct*/ minWidth, int /* TYPENOTE: Correct*/ prefHeight, INT32 maxHeight);
};



/*************************************************************************
Class         : CBDDItemInfo 
Base Class    : none
Author        : Mikhail Tatarnikov
Description   : Item information for Bitmap Dropdown control.
Pure Virtual  : No
Known Issues  : None
Usage Notes   : We need two separate fields for text, since the base DropDown class
				identifies items by their text. So, if all items have no string, they are
				considered the same, and as result some operations (like SetSelection)
				work incorrectly.
Override Notes: None
**************************************************************************/
class CBDDItemInfo
{
public:
	CBDDItemInfo();
	CBDDItemInfo(UINT32 uiBitmapResID, String_256 strText);

	// Accessors
	UINT32	   GetBitmapID();
	BOOL	   HasText();
	String_256 GetText();

	const CBDDItemInfo& operator=(const CBDDItemInfo& rOther);

protected:
	UINT32	   m_uiBitmapResID;
	BOOL	   m_bHasText;
	String_256 m_strText;
};



/*************************************************************************
Class         : CBitmapDropDown 
Base Class    : public DropDow
Author        : Mikhail Tatarnikov
Description   : Represents a combobox with bitmaps and text
Pure Virtual  : No
Known Issues  : None
Usage Notes   : None
Override Notes: The item data is stored in a vector and owned by this class.
**************************************************************************/
class CBitmapDropDown : public DropDown
{
friend class DialogManager;

CC_DECLARE_DYNCREATE(CBitmapDropDown)

// --- Kernelly section

public:			// CBitmapDropDown  management
	CBitmapDropDown();
	virtual ~CBitmapDropDown();

	virtual BOOL Init(CWindowID Window, CGadgetID Gadget);
	
	// Adds a new item (icon + text).
	void AddItem(UINT32 uiBitmapResID, String_256 strText);
	void AddDivider();

	// Select an item.
	void SetSelectedIndex(INT32 iSelectedIndex){DropDown::SetSelectedIndex(iSelectedIndex);}

	// Specify the look of "unselected" item - a bitmap/text that will be drawn when no item is selected.
	void SetUnselectedIntem(UINT32 uiBitmapID, String_256 strText);

	// Deletes an existing item.
	void DeleteItem(INT32 index);

protected:
	// Overrides item data access function.
	void* GetItemData(INT32 iItemIndex);

	// Returns TRUE if the item has an icon. Default is no icon
	virtual BOOL HasIcon(void* pvItemData);
	
	// Returns TRUE if the item has a text label.
	virtual BOOL HasText(void* pvItemData);
	
	virtual wxString GetText(void* pvItemData, INT32 iItem);
	
	// Draw the item.
	virtual wxSize HandleDrawItemInternal(wxDC& dc, const wxRect& Rect, INT32 item, INT32 flags, BOOL Draw);
	
	// Draw the associated icon.
	virtual wxSize DrawIcon(wxDC& dc, const wxRect& Rect, INT32 item, INT32 flags, BOOL Draw);

protected:
	// Items information. No need to delete item data while removing an item.
	std::vector<CBDDItemInfo> m_vecItems;

	// Information about the unselected item.
	CBDDItemInfo m_oUnselectedItemInfo;

// --- Winoily section


};





#endif	// BITMAPDROPDOWN_H

