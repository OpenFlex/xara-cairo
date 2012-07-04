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

// Palette control for use in the export/create bitmap copy dialog

#ifndef INC_BMPALCTRL
#define INC_BMPALCTRL

// Implementation notes:  The palette contol displays the palette in the
// bitmap export dialog.  This palette has various sort options so the user
// can view the palette in diffrent ways.  To avoid having to change the actual
// bitmap when the user changes the sort type, this controls comunicates with
// the actual palette throught an interface class, BitmapExportPaletteInterface,
// which sits between the palette from the bitmap and the palette that this
// control uses (throught the member variable m_Palette).  Because of this,
// when the palette is comunicating with other parts of camelot, it must take
// into account this sorting and provide indexs into the palette in terms that
// the caller expects (ie sorted or non sorted).

#include "bmpalint.h"

class BitmapExportOptions;
class BmapPrevDlg;

/**************************************************************************************
>	class BitmapExportPaletteControl : public CC_CLASS_MEMDUMP
	Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/11/2000
	Purpose:	Wraps a palette control for use in the export/create bmp copy dialog
**************************************************************************************/
class BitmapExportPaletteControl : public CCObject
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(BitmapExportPaletteControl);
private:
	// Data members
	INT32			m_MouseOverCell;	// Cell that the mouse is over (highlighed cell), -1 means none
	INT32			m_SelectedCell;		// Cell that is selected, -1 means none

	BitmapExportPaletteInterface	m_Palette;

	CWindowID	m_WindowID;

	// Constants (that are set in the constuctor as they are DPI dpenedant)
	INT32 m_nPixelSize;
	INT32 m_nCellWidthPixels;
	INT32 m_nCellHeightPixels;
	INT32 m_nCellWidth;
	INT32 m_nCellHeight;
	INT32 m_nCellsPerLine;

	INT32 m_NumberOfColoursAtLastRedraw; // used so we know when to redraw the background

public:
	// Constants
	enum {
		INVALID_COLOUR_VALUE	= -1 // A value that can never be a colour index
	};

	// Constructors / Destructors
	BitmapExportPaletteControl();
	~BitmapExportPaletteControl();
	void Init(CWindowID wid) { m_WindowID = wid; };

	// Manipulators
	void SetCurrentSortType(BitmapExportPaletteInterface::PaletteSortType newSortType);
	void SetSelectedColourToggleLocked();
	void SetSelectedColourWebSafe();
	bool SetSelectedColourToggleTransparent();
	void SetSelectedColourToggleDeleted();

	// These functions set the selected/hightlighted cell based on an index into
	// the real palette (so 0 is the first colour in the bitmap's palette)
	bool SetSelectedCell(ReDrawInfoType *pInfo, INT32 paletteIndex);
	bool SetHighlightedCell(ReDrawInfoType *pInfo, INT32 paletteIndex);

	// Access functions
	BitmapExportPaletteInterface::PaletteSortType GetCurrentSortType();
	INT32 GetSelectedColour();									// Find out the palette index of the selected colour
	INT32 GetMouseOverColour();									// Find out the palette index of the selected colour
	bool GetSelectedColourLocked();
	bool GetSelectedColourWebSafe();
	bool GetSelectedColourTransparent();
	bool GetSelectedColourDeleted();

	// Message processing funtions
	void MsgMouseMove(ReDrawInfoType *pInfo);
	bool MsgMouseLeftButtonDown(ReDrawInfoType *pInfo);
	void MsgMouseRightButtonUp(ReDrawInfoType *pInfo, BmapPrevDlg *pBmapPrevDlg);

	// Actions
	void Render(ReDrawInfoType *pInfo);
	void RenderSoon();
	void RedrawSelectedCell(ReDrawInfoType *pInfo);

private:
	INT32 GetCellFromPos(INT32 x, INT32 y);
	void RenderGrey(DocRect *pPaletteSize, RenderRegion *pRender);
	void RenderPalette(DocRect *pPaletteSize, RenderRegion *pRender, INT32 controlHeight, DocRect* pClipRect);
	void GetRectForCell(INT32 cell, DocRect *rect, INT32 controlHeight);
	void InvalidateCell(ReDrawInfoType *pInfo, INT32 paletteIndex);
	void DrawCell(DocRect *rect, DocColour colour, INT32 flags, RenderRegion *pRender,
												bool webSafe, bool selected);
	bool IsColourWebSafe(BYTE r, BYTE g, BYTE b);
	void MakeColourWebSafe(BYTE *pColour);

	// These functions set the selected/hightlighted cell based on an index into
	// the sorted palette (so 0 is the top left cell)
	bool SetSelectedCellFromSortedIndex(ReDrawInfoType *pInfo, INT32 paletteIndex);
	bool SetHighlightedCellFromSortedIndex(ReDrawInfoType *pInfo, INT32 paletteIndex);
};

#endif	// INC_BMPALCTRL
