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



#include "camtypes.h"
#include "camelot.h"
#include "errors.h"
#include "palman.h"
#include "cartprov.h"

#include "fileinfolist.h"



/******************************************************************************
Function  : CFileInfoList::CListRow::CListRow
Author    : Mikhail Tatarnikov
Purpose   : ListRow constructor
Returns   : void
Exceptions: 
Parameters: [in] CFileInfoList* plstParent - list control to represent;
            [in] INT32			iRow	   - the row to represent.
Notes     : The constructor is private, only CFileInfoList can create it.
******************************************************************************/
CFileInfoList::CListRow::CListRow(CFileInfoList* plstParent, INT32 iRow)
{
	m_plstParent = plstParent;
	m_iRow		 = iRow;
}

CFileInfoList::CListRow::~CListRow()
{
}

CFileInfoList::CListRow::CListRow(const CListRow& roOtherRow)
{
	m_plstParent = roOtherRow.m_plstParent;
	m_iRow		 = roOtherRow.m_iRow;
}
	
const CFileInfoList::CListRow& CFileInfoList::CListRow::operator= (const CListRow& roOtherRow)
{
	m_plstParent = roOtherRow.m_plstParent;
	m_iRow		 = roOtherRow.m_iRow;
	
	return roOtherRow;
}
			
/******************************************************************************
Function  : CFileInfoList::CListRow::SetBitmap
Author    : Mikhail Tatarnikov
Purpose   : Set a bitmap to the row
Returns   : void
Exceptions: 
Parameters: [in] UINT32 uiBitmapID - a new row bitmap.
Notes     : 
******************************************************************************/
void CFileInfoList::CListRow::SetBitmap(UINT32 uiBitmapID)
{
	m_plstParent->SetRowBitmap(m_iRow, uiBitmapID);
}

/******************************************************************************
Function  : CFileInfoList::CListRow::SetText
Author    : Mikhail Tatarnikov
Purpose   : Set text to display
Returns   : void
Exceptions: 
Parameters: [in] INT32		iColumn - column where the text should go;
            [in] String_256 strText - new text.
Notes     : 
******************************************************************************/
void CFileInfoList::CListRow::SetText(INT32 iColumn, String_256 strText)
{
	m_plstParent->SetRowText(m_iRow, iColumn, strText);
}














CFileInfoList::CFileInfoList()
{
	m_widParentDlg = 0;
	m_gdgidGadget  = 0;
}


CFileInfoList::~CFileInfoList()
{
}


/******************************************************************************
Function  : CFileInfoList::GetListCtrl
Author    : Mikhail Tatarnikov
Purpose   : Helper function to retrieve the actual list control
Returns   : wxListCtrl* - the list control associated with this object.
Exceptions: 
Parameters: None
Notes     : 
******************************************************************************/
wxListCtrl* CFileInfoList::GetListCtrl()
{
	wxWindow* pwndGadget = DialogManager::GetGadget(m_widParentDlg, m_gdgidGadget);
	if (!pwndGadget)
		return NULL;
	
	if (!pwndGadget->IsKindOf(CLASSINFO(wxListCtrl)))
		return NULL;
	
	wxListCtrl* plstList = (wxListCtrl*)pwndGadget;
	
	return plstList;
}


wxImageList* CFileInfoList::GetImageList()
{
	wxListCtrl* pListCtrl = GetListCtrl();
	wxImageList* pilImageList = pListCtrl->GetImageList(m_ciImageListType);
	
	return pilImageList;
}




/******************************************************************************
Function  : CBitmapDropDown::Init
Author    : Mikhail Tatarnikov
Purpose   : Initialize the control
Returns   : BOOL - TRUE if success, FALSE otherwise.
Exceptions: 
Parameters: [in] CWindowID Window - the parent window, NULL to deinitialize;
            [in] CGadgetID Gadget - the control ID.
Notes     : 
******************************************************************************/
BOOL CFileInfoList::Init(CWindowID widParentDlg, CGadgetID gdgidGadget)
{
	// Obtain the gadget and check if it has an appropriate class (we can
	// be attached to a wxListCtrl only).
	wxWindow* pwndGadget = DialogManager::GetGadget(widParentDlg, gdgidGadget);
	if (pwndGadget && pwndGadget->IsKindOf(CLASSINFO(wxListCtrl)))
	{
		m_widParentDlg = widParentDlg;
		m_gdgidGadget  = gdgidGadget;
		
		return(TRUE);
	}
	
	ERROR3("CBitmapDropDown::Init failed - illegal Gadget");
	return(FALSE);
}

/******************************************************************************
Function  : CFileInfoList::AddColumn
Author    : Mikhail Tatarnikov
Purpose   : Add a new column
Returns   : void
Exceptions: 
Parameters: [in] String_64 strHeader - column label;
            [in] INT32	   iWidth	 - column width;
            [in] INT32	   iFormat	 - column format (see wxListCtrl::InsertColumn).
Notes     : 
******************************************************************************/
void CFileInfoList::AddColumn(String_64 strHeader, INT32 iWidth, INT32 iFormat)
{
	wxListCtrl* plstList = GetListCtrl();
	INT32 iColNum = plstList->GetColumnCount();
	plstList->InsertColumn(iColNum, strHeader, iFormat, iWidth);
}


/******************************************************************************
Function  : CFileInfoList::AddRow
Author    : Mikhail Tatarnikov
Purpose   : Adds a new row
Returns   : CFileInfoList::CListRow - an object to represet the new created row.
Exceptions: 
Parameters: None
Notes     : 
******************************************************************************/
CFileInfoList::CListRow CFileInfoList::AddRow()
{
	wxListCtrl* plstList = GetListCtrl();
	
	INT32 iRowsCount = plstList->GetItemCount();
	plstList->InsertItem(iRowsCount, _T(""));
	
	return CListRow(this, iRowsCount);
}
	
/******************************************************************************
Function  : CFileInfoList::Clear
Author    : Mikhail Tatarnikov
Purpose   : Removes all elements from the list
Returns   : void
Exceptions: 
Parameters: None
Notes     : 
******************************************************************************/
void CFileInfoList::Clear()
{
	wxListCtrl* plstList = GetListCtrl();
	plstList->DeleteAllItems();

	
	plstList->AssignImageList(NULL, m_ciImageListType);
}


/******************************************************************************
Function  : CFileInfoList::SetRowBitmap
Author    : Mikhail Tatarnikov
Purpose   : Set a bitmap to the row.
Returns   : void
Exceptions: 
Parameters: [in] INT32  iRow	   - row to set the bitmap to;
            [in] UINT32 uiBitmapID - new bitmap ID.
Notes     : 
******************************************************************************/
void CFileInfoList::SetRowBitmap(INT32 iRow, UINT32 uiBitmapID)
{
	wxListCtrl* plstList = GetListCtrl();
	if (plstList == NULL)
		return;
	
	// Load the bitmap
	wxBitmap* pBitmap = CamArtProvider::Get()->FindBitmap(uiBitmapID, CAF_DEFAULT);
	if (pBitmap == NULL)
		return;
	
	// Obtain the control's image list and add the new bitmap into it.
	wxImageList* pilImageList = GetImageList();
	
	// Check if we have to create an image list ourselves.
	if (pilImageList == NULL)
	{
		pilImageList = new wxImageList(pBitmap->GetWidth(), pBitmap->GetHeight(), true, 0);
		plstList->AssignImageList(pilImageList, m_ciImageListType);
	}
	
	INT32 iBitmapIndex = pilImageList->Add(*pBitmap);
	
	// Finally set the item information.
	plstList->SetItem(iRow, 0, _T(""), iBitmapIndex);
}

/******************************************************************************
Function  : CFileInfoList::SetRowText
Author    : Mikhail Tatarnikov
Purpose   : Set new text to a row
Returns   : void
Exceptions: 
Parameters: [in] INT32		iRow	- row to set the text to;
            [in] INT32		iColumn - column to set the text to;
            [in] String_256 strText - new text.
Notes     : 
******************************************************************************/
void CFileInfoList::SetRowText(INT32 iRow, INT32 iColumn, String_256 strText)
{
	wxListCtrl* plstList = GetListCtrl();
	plstList->SetItem(iRow, iColumn, strText);
}


