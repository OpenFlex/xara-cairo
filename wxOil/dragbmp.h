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

// DragBmp.h - BITMAP DragInformation base class


#ifndef INC_DRAGBMP
#define INC_DRAGBMP

#include "draginfo.h"

class KernelBitmap;
class CWxBitmap;

class SGDisplayItem;


/********************************************************************************************

>	class BitmapDragInformation : public DragInformation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/05/94
	Purpose:	Contains info that a Bitmapdrag may find useful
				
********************************************************************************************/

class BitmapDragInformation : public DragInformation
{ 	
CC_DECLARE_DYNCREATE(BitmapDragInformation)

public:
	BitmapDragInformation();
 	BitmapDragInformation(	KernelBitmap *Bitmap, 
							INT32 xSize,
							INT32 ySize, 
							INT32 xOffset,
							INT32 yOffset,
 							BOOL IsAdjust = FALSE);

	~BitmapDragInformation();

	BOOL StartGalleryItemDrag(SGDisplayItem*);
	
	void OnClick(INT32 Flags, POINT Point);
	
	virtual UINT32 GetCursorID(void);
 	virtual BOOL GetStatusLineText(String_256 * TheText);
	virtual BOOL OnDrawSolidDrag(wxPoint Origin, wxDC * TheDC);

	virtual UINT32 GetCursorID(DragTarget* pDragTarget);
	virtual BOOL GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget);
	virtual BOOL OnDrawSolidDrag(wxPoint Origin,wxDC * TheDC, DragTarget* pDragTarget);

	virtual BOOL HasTransparentMask()	{ return (MaskBitmap != NULL); }
	virtual wxBitmap* GetTransparentMask() { return (MaskBitmap); }

	virtual KernelBitmap* GetSolidDragMask();

	KernelBitmap *GetTheBitmap(void)	{ return TheBitmap; }

	void ApplyBitmapToSelection(void);

	virtual INT32 GetDragTransparency();
	static BOOL Init();

protected:

	BOOL PlotBitmap(CWxBitmap *WinBM, 
					wxPoint Origin, wxSize Size, 
					wxDC * RenderDC);

protected:
 	KernelBitmap *TheBitmap;
 	KernelBitmap *DragMask;

	wxSize DragRect;

	LPBITMAPINFO TempInfo;
	LPBYTE TempBits;

	UINT32 DIBPal;

	wxDC* MemDC;
	wxBitmap* Bitmap;
	wxBitmap* OldBmp;
	wxBitmap* MaskBitmap;

	static INT32 DragTransparency;
};


#endif

