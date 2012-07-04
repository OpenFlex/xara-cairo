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

#ifndef WXOIL_FILEINFOLIST_H
#define WXOIL_FILEINFOLIST_H

#include <wx/imaglist.h>
#include <wx/listctrl.h>

class CFileInfoList
{
public:
	class CListRow
	{
		private:
			CListRow(CFileInfoList* plstParent, INT32 iRow);
			friend class CFileInfoList;

		public:
			CListRow(const CListRow& roOtherRow);
			~CListRow();
	
			const CListRow& operator= (const CListRow& roOtherRow);
			
			void SetBitmap(UINT32 uiBitmapID);
			void SetText(INT32 iColumn, String_256 strText);
	
		protected:
			CFileInfoList* m_plstParent;
			INT32		  m_iRow;		// The row number this item represents.
	};

public:
	CFileInfoList();
	virtual ~CFileInfoList();
	
public:
	// Initialize the control.
	BOOL Init(CWindowID ParentDlg, CGadgetID GadgetID);
	// Add a new column
	void AddColumn(String_64 strHeader, INT32 iWidth = -1, INT32 iFormat = wxLIST_FORMAT_LEFT);
	// Add a new row.
	CListRow AddRow();

	// Remove all entries from the list control.
	void Clear();
	
protected:
	// Set bitmap to a row. 
	void SetRowBitmap(INT32 iRow, UINT32 uiBitmapID);
	// Set text to a cell.
	void SetRowText(INT32 iRow, INT32 iColumn, String_256 strText);
	
	friend class CListRow;
	
	// Helper functions.
	wxListCtrl*  GetListCtrl();
	wxImageList* GetImageList();
	
protected:
	//	wxImageList* m_imglstListIcons;
	CWindowID m_widParentDlg;
	CGadgetID m_gdgidGadget;
	
	static const INT32 m_ciImageListType = wxIMAGE_LIST_SMALL;
};


#endif	// WXOIL_FILEINFOLIST_H
