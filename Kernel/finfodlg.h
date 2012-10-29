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


#ifndef INC_FINFODLG
#define INC_FINFODLG

#include "fontbase.h"		// font manager and associated items
#include "fileinfolist.h"

#define OPTOKEN_FINFODLG _T("FileInfo")    

class DocumentFontDropDown;

/********************************************************************************************

>	class FileInfo: public DialogOp

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/08/94
	Purpose:	The file info dialogue shows information on the selected document.
	SeeAlso:	-

********************************************************************************************/

class FileInfo: public DialogOp
{         
	CC_DECLARE_DYNCREATE( FileInfo )  
public:
	FileInfo();	
	~FileInfo();
	void	Do(OpDescriptor*);	     
	static	BOOL Init();                        
	static	OpState GetState(String_256*, OpDescriptor*);	
	virtual	MsgResult Message(Msg* Message);

	static const UINT32 IDD;     
	static const CDlgMode Mode;   
	static FileInfo * CurrentDialog;
	static void Refresh();

private:
	BOOL OnDimCreate();
	BOOL SetDocInfo(BOOL UpdateComment,BOOL UpdateFonts = FALSE);
	BOOL UpdateFontList(Document* WorkDoc);
	BOOL UpdateEffectsList(Document* pWorkDoc);
	BOOL AddToSortedList(List& ItemList, UINT32 idBitmap, String_64& strItemName, String_256& strDetails);

private:
	static DocumentFontDropDown	*NameDropDown;
	List BitmapList;
	MonotonicTime timerSlowJob;
	
	CFileInfoList m_lstctrlExternalResInfo;
}; 

Node* StartTreeScan(Document* pDoc);
Node* GetNextTreeNode(Node* Current);
Node* SkipSubtreeScan(Node* Current);


/********************************************************************************************

>	class RefItem : public ListItem

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/02/2005
	Purpose:	Item class for the Reference sorting system

********************************************************************************************/

class RefItem : public ListItem
{
	CC_DECLARE_DYNCREATE(RefItem)

public:
	RefItem()
	{
		idBitmap = 0;
		strItemName = String( _T("") );
		strDetails = String( _T("") );
	}

	RefItem(UINT32 newidBitmap, String_64& newstrItemName, String_256& newstrDetails)
	{
		idBitmap = newidBitmap;
		strItemName = newstrItemName;
		strDetails = newstrDetails;
	}

public:
	UINT32		idBitmap;			// Resource ID of bitmap
	String_64	strItemName; 		// Textual name of font in question
	String_256	strDetails;			// Text for detailed explanation of state
};


#endif
