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

#ifndef BITMAPGRIDDROPDOWN_H
#define BITMAPGRIDDROPDOWN_H

#include "griddropdown.h"
//#include "gbrush.h"
//#include "pump.h"


class LineAttrItem;
class GRenderRegion;


/*************************************************************************
Class         : CBGDDItemInfo
Base Class    : public CGridComboUserData
Author        : Mikhail Tatarnikov
Description   : Items base class for for CBitmapGridDropDown control.
Pure Virtual  : DrawItem - the derived classes has to implement their own drawing.
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDItemInfo : public CGridComboUserData
{
public:
	CBGDDItemInfo(String_256 strLabel = String_256());
	virtual ~CBGDDItemInfo();

	String_256 GetLabel();

	virtual void DrawItem(wxDC& dc, const wxRect& rect, INT32 iFlags) const = 0;

protected:
	String_256 m_strLabel;
};



/*************************************************************************
Class         : CBGDDWxBitmapItem
Base Class    : public CBGDDItemInfo
Author        : Mikhail Tatarnikov
Description   : Item for displaying a wxBitmap.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDWxBitmapItem : public CBGDDItemInfo
{
public:
	CBGDDWxBitmapItem(wxBitmap* pBitmap, BOOL bAutodelete = TRUE,
					  String_256 strLabel = String_256(),
					  BOOL		 bStretch = TRUE);
	virtual ~CBGDDWxBitmapItem();

	virtual void DrawItem(wxDC& dc, const wxRect& rect, INT32 iFlags) const;

protected:
	wxBitmap* m_pBitmap;
	BOOL	  m_bDelete;
	BOOL	  m_bStretch;
};



/*************************************************************************
Class         : CBGDDResourceItem
Base Class    : public CBGDDWxBitmapItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a resource-stored bitmap.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDResourceItem : public CBGDDWxBitmapItem
{
public:
	CBGDDResourceItem(UINT32 uiBitmapResID,
					  String_256 strLabel = String_256(),
					  BOOL		 bStretch = TRUE);
	virtual ~CBGDDResourceItem();
};


/*************************************************************************
Class         : CBGDDCachedItem
Base Class    : public CBGDDWxBitmapItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a resource-stored bitmap.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: The derived classes should override either RenderItemToBitmap or
				or GetWxBitmap method - whatever fits best.
**************************************************************************/
class CBGDDCachedItem : public CBGDDItemInfo
{
public:
	CBGDDCachedItem(String_256 strLabel = String_256());
	virtual ~CBGDDCachedItem();

	virtual void DrawItem(wxDC& dc, const wxRect& rect, INT32 iFlags) const;

protected:
	// Get the representation of the item (of the Kernel Bitmap)
	virtual wxBitmap* RenderItemToBitmap(wxSize szBitmap) const;
	virtual void	  RenderItemToGRenderRegion(GRenderRegion* pRenderRegion, DocRect drcItem) const;

private:
	wxBitmap*	GetWxBitmap(wxSize szBitmap) const;
	static BOOL DoesCacheItemSizeMatch(const pair<wxSize, wxBitmap*>* poItem, wxSize szBitmap);

private:
	typedef	std::vector<pair<wxSize, wxBitmap*>*> TDCacheCollection;
	mutable TDCacheCollection m_colCache;
};



/*************************************************************************
Class         : CBGDDKernelBitmapItem
Base Class    : public CBGDDCachedItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a KernelBitmap.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDKernelBitmapItem : public CBGDDCachedItem
{
public:
	CBGDDKernelBitmapItem(KernelBitmap* pKernelBitmap, BOOL bAutodelete = TRUE,
						  String_256 strLabel = String_256(),
						  BOOL		 bStretch = TRUE);
	virtual ~CBGDDKernelBitmapItem();

protected:
	virtual wxBitmap* RenderItemToBitmap(wxSize szBitmap) const;

protected:
	KernelBitmap* m_pKernelBitmap;
	BOOL		  m_bDeleteKernelBitmap;
	BOOL		  m_bStretch;
};






/*************************************************************************
Class         : CBGDDStrokeItem
Base Class    : public CBGDDCachedItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a stroke.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDStrokeItem : public CBGDDCachedItem
{
public:
	CBGDDStrokeItem(LineAttrItem* plaiStroke, BOOL bAutodelete = TRUE, String_256 strLabel = String_256());
	virtual ~CBGDDStrokeItem();

protected:
	virtual void RenderItemToGRenderRegion(GRenderRegion* pRenderRegion, DocRect drcItem) const;

protected:
	LineAttrItem* m_plaiStroke;
	BOOL		  m_bDelete;
};





/*************************************************************************
Class         : CBGDDBrushItem
Base Class    : public CBGDDCachedItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a brush.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDBrushItem : public CBGDDCachedItem
{
public:
	CBGDDBrushItem(AttrBrushType* pabtBrush, BOOL bAutodelete = TRUE, String_256 strLabel = String_256());
	virtual ~CBGDDBrushItem();

protected:
	virtual void RenderItemToGRenderRegion(GRenderRegion* pRenderRegion, DocRect drcItem) const;

protected:
	AttrBrushType* m_pabtBrush;
	BOOL		   m_bDelete;
};












/*************************************************************************
Class         : CBitmapGridDropDown
Base Class    : public CGridDropDown
Author        : Mikhail Tatarnikov
Description   : Control class for wxGridCombo control that stores and displays
				items as images.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBitmapGridDropDown : public CGridDropDown
{
friend class DialogManager;


public:
	CBitmapGridDropDown();
	virtual ~CBitmapGridDropDown();

	void AddItem(UINT32 uiBitmapResID, String_256 strLabel = String_256(), BOOL bStretch = TRUE);
	void AddItem(wxBitmap* pBitmap, BOOL bDelete = TRUE, String_256 strLabel = String_256(), BOOL bStretch = TRUE);
	void AddItem(KernelBitmap* pBitmap, BOOL bDelete = TRUE, String_256 strLabel = String_256(), BOOL bStretch = TRUE);
	void AddItem(LineAttrItem* plaiStroke, BOOL bDelete = TRUE, String_256 strLabel = String_256());
	void AddItem(AttrBrushType* pabtBrush, BOOL bDelete = TRUE, String_256 strLabel = String_256());

	void SetUnselectedItem(UINT32 uiBitmapResID, String_256 strLabel = String_256());
	void SetUnselectedItem(wxBitmap* pBitmap, String_256 strLabel = String_256());

	void SelectByLabel(String_256 strLabel);

protected:
	CBGDDItemInfo* GetItemData(INT32 iItem);

	virtual void DrawItemCore(wxDC& dc, const wxRect& rect, INT32 iItem, INT32 iFlags);

	wxBitmap*	  PreviewBrush(AttrBrushType* pabtBrush);
	KernelBitmap* PreviewStroke(LineAttrItem* plaiStroke);

protected:
	CBGDDItemInfo* m_poUnselectedItem;
};





#endif	// BITMAPGRIDDROPDOWN_H

