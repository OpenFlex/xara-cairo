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


#ifndef INC_CCLISTGADGET
#define INC_CCLISTGADGET

#include <afx.h>
#include <afxtempl.h>
#include <afxcoll.h>

#define ID_HEADER	179 // an arbitrary ID for the header
// These defines have to be even to avoid having to pad bitmap scanlines
// **************************************************************************************************
#define SWITCH_MARGIN	8 // the margin (in pixels) we leave to the left of the first switch 
#define SWITCH_SEPARATOR 4 // the width (in pixels) separating two consecutive switches
#define SWITCH_WIDTH	12 // width of switch bitmap
//***************************************************************************************************
#define SWITCH_HEIGHT	12   // height of switch bitmap
#define SWITCHES_SUPPORTED	3 // max no of switches supported
#define COLOUR_PATCH_WIDTH	12
#define COLOUR_PATCH_HEIGHT	12
#define MAX_NO_ITEMS 64 // maximum no of items the list can have - quite conservative to save Win32s GDI memory


/********************************************************************************************

>	class CCListGadget	:	public CC_CLASS_MEMDUMP

	Author:		Adrian_Stoicar (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/08/96
	Purpose:	 wrapper class for the Win95 listview control

	SeeAlso:	PrintSepsTab; PrintImagesetterTab;

********************************************************************************************/

class CCListGadget	:	public CC_CLASS_MEMDUMP
{
CC_DECLARE_MEMDUMP(CCListGadget)

public:
	CCListGadget() {};
	~CCListGadget();

	// Static function to create a new gadget from a res template ID and a window ID/handle
	// On creation all list gadgets are added to a global list
	static CCListGadget* Create(CWindowID parentID, CGadgetID gadgetID);

	// Static function to retrieve a pointer to a list gadget knowing its resource ID and the parent's handle
	static CCListGadget* GetGadget(CWindowID parentID, CGadgetID gadgetID);

	// Function to create a custom header from a bitmap resource
	BOOL CreateCustomHeader (UINT32 bitmapID);

	// Function to add switches (ex. check/tick boxes) to the list control. Up to 3 switches per item are supported.
	BOOL SetSwitches(UINT32 noOfSwitches, UINT32 idBitmapOn, UINT32 idBitmapOff, UINT32 idDisabledBitmapOn, UINT32 idDisabledBitmapOff);

	// Gets the current number of switches
	UINT32 GetNumberOfSwitches();

	// Sets the text for a non-custom header
	BOOL SetHeaderString(StringBase& string, UINT32 colIndex);

	// Function to set the columns for the list
	BOOL SetNumberOfColumns(UINT32 nColumns);

	// Gets the current number of columns
	UINT32 GetNumberOfColumns();

	// Changes the width of a column. By default all columns created by SetColumns() have the same width
	BOOL SetColumnWidth(INT32 colIndex, INT32 width);

	// Retrieves the current width of a column based on its 0-based index
	INT32 GetColumnWidth(INT32 columnIndex);

	// Sets the state of a switch (determines whether the bitmapOn or bitmapOf is shown)
	BOOL SetSwitchState(BOOL state, UINT32 itemIndex, UINT32 switchIndex);

	// Retrieves the current state of a switch (ON/OFF)
	BOOL GetSwitchState(UINT32 itemIndex, UINT32 switchIndex);

	// Adds an item to the list (pItemImage points to an optional bitmap associated with the item and displayed to its right
	BOOL AddItem(StringBase& itemString, KernelBitmap* pItemImage = 0);

	// Used if the the listitem is a actually a colour - it displays a square colour patch next to the color name
	BOOL AddColourListItem(StringBase& colourName, INT32 red, INT32 green, INT32 blue, BOOL IsSpotColour = FALSE);

	// Adds an item to the list, creating the associated image from a bitmap resource ID
	BOOL AddItem(StringBase& itemString, UINT32 bitmapEnabledID, UINT32 bitmapDisabledID);

	// Inserts an item at a certain position in the list
	BOOL InsertItem(UINT32 index, StringBase& itemString, KernelBitmap* pItemImage = 0);

	// Inserts an item at a certain position in the list, creating the associated image from a bitmap resource ID
	BOOL InsertItem(UINT32 index, StringBase& itemString, UINT32 bitmapID);

	// Sets the text for an item or one of its components
	BOOL SetItemString(StringBase& itemString, UINT32 itemIndex, UINT32 columnIndex);

	// Retrieve the text of an item or one of its components
	BOOL GetItemString(StringBase& itemString, UINT32 itemIndex, UINT32 columnIndex);
	
	// Does exactly that
	BOOL DeleteAllItems();

	// Returns the index of the item currently selected, -1 if none
	INT32 GetSelectedItemIndex();

	// Sets the given item to be selected (and deselects all other items)
	void SetSelectedItemIndex(INT32 NewSel);
	
	// Returns the number of items contained in the list
	INT32 GetItemCount();



private:
	CGadgetID listID; // the resource template ID
	CWindowID formID; // the handle of the parent dialog box or tab
	CFont gadgetFont; // used only on Win32s
	UINT32 columns; 
	UINT32 switches;
	BOOL isEnabled;
	HBITMAP CreateScreenCompatibleBitmap(INT32 width, INT32 height);
	HIMAGELIST CreateImageList(INT32 imageWidth, INT32 imageHeight);
	HIMAGELIST hStateEnabled; // handle to state image list to be shown when the control is enabled (white background)
	HIMAGELIST hStateDisabled; // handle to state image list to be shown when the control is disabled ( gray background)
	HIMAGELIST hImageListEnabled; // handle to the the item image list - in the enabled state
	HIMAGELIST hImageListDisabled; // handle to the item image list - when disabled
	HWND hHeader;
	HBITMAP hHeaderBitmap;
	INT32 switchColumnWidth; // width of the bitmap containing the switches - needed when resizing the columns
	INT32 SwitchLeftCoord[3]; // we only support up to 3 switches !
	CCListGadget(CWindowID parentID, CGadgetID gadgetID); // private constructor, called by ::Create()
	BOOL SetBitmapBkgToSystem(HBITMAP hBitmap); // will set the bkg of the bitmap to the bkg of dialog boxes - called when the colour scheme changes
	BOOL AddToList(); // add the gadget to the global list
	BOOL isColourList;
	// Function to handle clicks inside the client area - called by the DialogManager
	// Returns TRUE if the click resulted in a change in the state of the control, FALSE othewise
	BOOL OnGadgetClicked();
	static BOOL OnSysColorChange(CWindowID dialogID);
	// We are using our own enabler function as the Windows one looks awful (called by the DialogManager)
	// DO NOT call DialogManager::EnableGadget on a control before you have created it!
	BOOL SetEnabled(BOOL enabled);
	// Clean-up function - called by the DialogManager when the associated interface object receives WM_DESTROY
	static void OnDialogClose(CWindowID dialogID);
	// The actual killer function 
	void DestroyGadget();
	// Support class - entry in the global list
	class ListEntry	: public CObject
	{
	public:
		ListEntry(CWindowID wndID, CGadgetID gdgtID, CCListGadget* ptrListGadget)	:	parentID(wndID), gadgetID(gdgtID), pListGadget(ptrListGadget) {};
		CWindowID parentID;
		CGadgetID gadgetID;
		CCListGadget* pListGadget;
	};
	// The global list - actually, an array
	static CTypedPtrArray<CObArray, ListEntry*> GadgetList;
	friend class DialogManager;
};

	

#endif
