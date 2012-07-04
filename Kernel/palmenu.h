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



/******************************************************************************************

>	class PaletteContextMenu
	class OpPalettePopupCommand

	Author:		Alex_Price (Xara Group Ltd) <camelotdev@xara.com>

	Created:	09/08/99

	Purpose:	These 2 classes create and handle the right-click menu for the palette
				control in the bitmap export dialog palette tab.

	Remarks:	These classes are based on the classes 'PreviewContextMenu'. and
				'OpPreviewPopupCommand' for the bitmap preview image right-click menu

******************************************************************************************/


#include "contmenu.h"

class BitmapExportPaletteControl;
class BmapPrevDlg;

#define OPTOKEN_PALETTE_LOCKED					_T("Palette:Locked")
#define OPTOKEN_PALETTE_WEB_SAFE				_T("Palette:WebSafe")
#define OPTOKEN_PALETTE_TRANSPARENT_BACKGROUND	_T("Palette:Transparent Background")
#define OPTOKEN_PALETTE_TRANSPARENT				_T("Palette:Transparent")

#define OPTOKEN_PALETTE_DELETE					_T("Palette:Delete")
#define OPTOKEN_PALETTE_RESTORE					_T("Palette:Restore")

#define OPTOKEN_PALETTE_SYSTEM_COLOURS			_T("Palette:SystemColours")

#define OPTOKEN_PALETTE_SORT_BY_USE				_T("Palette:SortByUse")
#define OPTOKEN_PALETTE_SORT_BY_LUMINANCE		_T("Palette:SortByLuminance")
#define OPTOKEN_PALETTE_SORT_BY_HUE				_T("Palette:SortByHue")


class PaletteContextMenu : public ContextMenu
{
public:
	// the only necessary function
	virtual	BOOL Build();
};


class OpPalettePopupCommand : public Operation
{
	CC_DECLARE_DYNCREATE( OpPalettePopupCommand );

protected:
	static BOOL InitPolymorphicCommand( TCHAR *OpToken, UINT32 MenuTextID );

public:
	static BOOL Init(BitmapExportPaletteControl *, BmapPrevDlg *);
	static OpState GetCommandState( String_256 *ShadeReason, OpDescriptor *pOpDesc );
	virtual void Do(OpDescriptor* pOpDesc);

private:
	//  A pointer to the dialog containing the palette control.
	static BitmapExportPaletteControl	*m_pPaletteControl;
	static BmapPrevDlg					*m_pBmapPrevDlg;
};


