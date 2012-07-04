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


// dropdown.h - The Drop-down list base class

#ifndef INC_DROPDOWN
#define INC_DROPDOWN

//#include "dlgtypes.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]


class DialogManager;
class DropDown;



class wxCamVListBoxComboPopup : public wxVListBoxComboPopup
{
friend class DropDown;
public:
	wxCamVListBoxComboPopup(DropDown * pDropDown=NULL);
	~wxCamVListBoxComboPopup();

	virtual void	OnDrawItem(wxDC& dc, const wxRect& rect, int /*TYPENOTE: CORRECT*/ item, int /*TYPENOTE: CORRECT*/ flags) const;
	virtual wxCoord OnMeasureItem(size_t item) const;
	virtual wxCoord OnMeasureItemWidth(size_t item) const;

protected:
	DropDown* m_pDropDown;
};




class DropDown : public ListItem
{
friend class DialogManager;
friend class wxCamVListBoxComboPopup;

CC_DECLARE_DYNCREATE(DropDown)

public:			// Creation/destruction
	DropDown();
	virtual ~DropDown();	

	virtual BOOL Init(CWindowID ParentWindow, CGadgetID ParentControl);

	static void KillDropDownsByWindow(CWindowID Window);

protected:
	static List CurrentDropDowns;					// A list of all currently active dropdowns

	virtual void KillList() {} // allow reclaiming of memory on death

// --- Winoily section

protected:		// Methods that must be overridden by derived classes
	virtual BOOL HasIcon(void * ItemData);
				// Returns TRUE if the item has an icon. Default is no icon

	virtual BOOL DrawIcon(void * ItemData, wxDC& dc, wxRect& IconRect, BOOL Disabled, INT32 flags);
				// Handles redraw of the icon, if any. Default is nothing gets drawn

	virtual wxSize DrawText(void * ItemData, wxDC& dc, wxRect& TextRect, INT32 item, INT32 flags, BOOL Draw);
				// Handles redraw of the text for an item. Default draws the text
				// returned by GetText. You this probably do not need to override this

	virtual wxString GetText(void * ItemData, INT32 Item) {return wxEmptyString;}
				// By default returns a dummy string


public:			// Useful methods
	void ClearList(void);
				// Clears all items in the list


protected:		// Useful methods to call from derived classes
	void SetListRedraw(BOOL Enable);
				// Enables/disables redraw of the list (use while adding items)

	void AddItem(void * ItemData);
				// Adds an item to the end of the list

	void DeleteItem(INT32 index);
				// Deletes an item

	void SetSelectedIndex(INT32 SelectedIndex);
				// Sets the index of the selected item

	void * GetItemData(INT32 ItemIndex);
				// Retrieves the data associated with a given item

	INT32 GetNumberOfItems(void);
				// Determines how many items are in the list

	wxOwnerDrawnComboBox * GetBox();
				// Get a pointer to the combo box

// --- Base class stuff you shouldn't have to mess with

protected:
	virtual wxSize HandleDrawItemInternal(wxDC& dc, const wxRect& Rect, INT32 item, INT32 flags, BOOL Draw);
				// Draws the item HandleDrawItem

protected:
	BOOL Initialised;								// TRUE once we have been initialised

	CWindowID ParentDlg;							// CWindowID of the parent window
	CGadgetID ParentGadget;							// Gadget ID of the combo box
	wxCamVListBoxComboPopup * m_pPopup;				// Pointer to the popup control
};


#endif

