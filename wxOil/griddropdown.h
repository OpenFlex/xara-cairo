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


// GridDropDown.h - The grid Drop-down list base class

#ifndef WXOIL_GRIDDROPDOWN_H
#define WXOIL_GRIDDROPDOWN_H

#include "gridcombo.h"

// class DialogManager;
class CGridDropDown;



/*************************************************************************
Class         : wxCamGridPopup
Base Class    : public wxGridComboPopup
Author        : Mikhail Tatarnikov
Description   : Customization of the wxGridComboPopup.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class wxCamGridPopup : public wxGridComboPopup
{
// friend class CGridDropDown;
public:
	wxCamGridPopup(CGridDropDown* pDropDown, wxGridCombo* pCombo);
	virtual ~wxCamGridPopup();

	virtual void DrawItem(wxDC& dc, const wxRect& rect, int /* TYPENOTE: Correct */ iItem, INT32 iFlags);

protected:
	CGridDropDown* m_pDropDown;
};




/*************************************************************************
Class         : CGridDropDown
Base Class    : public ListItem
Author        : Mikhail Tatarnikov
Description   : Control class for wxGridCombo control.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CGridDropDown : public ListItem
{
	friend class wxCamGridPopup;

public:			// Creation/destruction
	CGridDropDown();
	virtual ~CGridDropDown();	

	virtual BOOL Init(CWindowID ParentWindow, CGadgetID ParentControl);

	static void KillDropDownsByWindow(CWindowID Window);

	// Sets/gets the index of the selected item
	void  SetSelected(INT32 iSelectedIndex);
	INT32 GetSelected();

	// Set the columns number.
	void SetColumns(INT32 iColumns);

	// Sets the size of items (images).
	void   SetItemSize(wxSize szItem);
	wxSize GetItemSize();
	
	// Determines how many items are in the list
	INT32 GetItemsNum(void);

	// Removes all entries from the combobox.
	void Clear(void);

	// Deletes an item
	void DeleteItem(INT32 index);


protected:
	static List CurrentDropDowns;					// A list of all currently active dropdowns

	virtual void KillList() {} // allow reclaiming of memory on death

// --- Winoily section

protected:		// Methods that must be overridden by derived classes

	virtual void DrawItem(wxDC& dc, const wxRect& rect, INT32 iItem, INT32 iFlags);

	virtual wxRect PreDrawItem(wxDC& dc, const wxRect& rect, INT32 iItem, INT32 iFlags);
	virtual void   DrawItemCore(wxDC& dc, const wxRect& rect, INT32 iItem, INT32 iFlags) = 0;
	virtual void   PostDrawItem(wxDC& dc, const wxRect& rect, INT32 iItem, INT32 iFlags);

	void SetListRedraw(BOOL Enable);	// Enables/disables redraw of the list (use while adding items)

protected:		// Useful methods to call from derived classes

	// Adds an item to the end of the list
	void AddItem(CGridComboUserData* pItemData);

	// Retrieves the data associated with a given item
	CGridComboUserData* GetItemData(INT32 iItem);

	// Get a pointer to the combo box
	wxGridCombo* GetBox();

	// Helper functions.
	void DrawShadedRect(wxDC& dc, const wxRect& rect, const wxPen& pen1, const wxPen& pen2);


protected:
	BOOL			m_bInitialised;						// TRUE once we have been initialised

	CWindowID		m_widParentDlg;					// CWindowID of the parent window
	CGadgetID		m_gidParentGadget;					// Gadget ID of the combo box
	wxCamGridPopup* m_pPopup;				// Pointer to the popup control
};


#endif // WXOIL_GRIDDROPDOWN_H

