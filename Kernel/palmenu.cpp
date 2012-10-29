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
#include "palmenu.h"
//#include "bmpreres.h"
#include "bmpalctrl.h"
#include "bmapprev.h"


//  An implementation to match the declaration in the header file.
CC_IMPLEMENT_DYNCREATE(OpPalettePopupCommand, Operation)

//  Initialise the static variable.
BitmapExportPaletteControl *OpPalettePopupCommand::m_pPaletteControl = 0;
BmapPrevDlg *OpPalettePopupCommand::m_pBmapPrevDlg = 0;

//  This will get Camelot to display the filename and linenumber of any memory allocations
//  that are not released at program exit
#define new CAM_DEBUG_NEW


/******************************************************************************************
>	INT32 PaletteContextMenu :: Build()
	Author:		Alex_Price (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/08/99
	Inputs:		-
	Returns:	TRUE if everything went OK, and FALSE otherwise.
	Purpose:	This function builds the menu.
******************************************************************************************/
BOOL PaletteContextMenu::Build()
{
	//  Use this variable to hold the status of the menu build. If it goes FALSE, 
	//  then something went wrong.
	BOOL ok = TRUE;

	//  Add all the menu items, together with separators.
	if( ok ) 
		ok = ok && BuildCommand( OPTOKEN_PALETTE_LOCKED );
	if( ok ) 
		ok = ok && BuildCommand( OPTOKEN_PALETTE_WEB_SAFE );
	if( ok )
		ok = ok && BuildCommand( OPTOKEN_PALETTE_TRANSPARENT_BACKGROUND );
	if( ok ) 
		ok = ok && BuildCommand( OPTOKEN_PALETTE_TRANSPARENT, TRUE );


	if( ok ) 
		ok = ok && BuildCommand( OPTOKEN_PALETTE_RESTORE );
	if( ok )
		ok = ok && BuildCommand( OPTOKEN_PALETTE_DELETE, TRUE);

	if( ok ) 
		ok = ok && BuildCommand( OPTOKEN_PALETTE_SYSTEM_COLOURS, TRUE );

	if( ok ) 
		ok = ok && BuildCommand( OPTOKEN_PALETTE_SORT_BY_USE );
	if( ok ) 
		ok = ok && BuildCommand( OPTOKEN_PALETTE_SORT_BY_LUMINANCE );
	if( ok ) 
		ok = ok && BuildCommand( OPTOKEN_PALETTE_SORT_BY_HUE );

	return ok;
}

	
/******************************************************************************************

>	static BOOL OpPreviewPopupCommand::InitPolymorphicCommand( TCHAR *OpToken, UINT32 MenuTextID )
 
	Author:		Alex_Price (Xara Group Ltd) <camelotdev@xara.com>

	Created:	09/08/99

	Inputs:		OpToken - the token of a menu operation
				MenuTextID - the resource string of the menu command.

	Returns:	TRUE if everything went OK, and FALSE otherwise.

	Purpose:	This function registers a menu operation.

******************************************************************************************/

BOOL OpPalettePopupCommand::InitPolymorphicCommand( TCHAR *OpToken, UINT32 MenuTextID )
{
	return(RegisterOpDescriptor(0,									// Tool ID 
								MenuTextID,		 					// String resource ID
								CC_RUNTIME_CLASS(OpPalettePopupCommand),// Runtime class
								OpToken, 							// Token string
								OpPalettePopupCommand::GetCommandState,	// GetState function
								0,									// help ID
								0,									// bubble help
								0,									// resource ID
								0,									// control ID
								SYSTEMBAR_ILLEGAL,					// Bar ID
								FALSE,								// Receive system messages
								FALSE,								// Smart duplicate operation
								TRUE,								// Clean operation
								NULL,								// No vertical counterpart
								0,									// String for one copy only error
								DONT_GREY_WHEN_SELECT_INSIDE		// Auto state flags
								));
}


/******************************************************************************************
>	BOOL OpPalettePopupCommand::Init(BitmapExportPaletteControl *)
	Author:		Alex_Price (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/08/99
	Inputs:		-
	Returns:	TRUE if everything went OK, and FALSE otherwise.
	Purpose:	This function registers all the menu operations by calling InitPolymorphicCommand
******************************************************************************************/
BOOL OpPalettePopupCommand::Init(BitmapExportPaletteControl *pPaletteControl, BmapPrevDlg *pBmapPrevDlg)
{
	m_pPaletteControl	= pPaletteControl;
	m_pBmapPrevDlg		= pBmapPrevDlg;

	InitPolymorphicCommand( OPTOKEN_PALETTE_LOCKED,					_R(IDS_MENU_LOCKED) );
	InitPolymorphicCommand( OPTOKEN_PALETTE_WEB_SAFE,				_R(IDS_MENU_WEB_SAFE) );
	InitPolymorphicCommand( OPTOKEN_PALETTE_TRANSPARENT_BACKGROUND,	_R(IDS_MENU_TRANSPARENT_BACK) );
	InitPolymorphicCommand( OPTOKEN_PALETTE_TRANSPARENT,			_R(IDS_MENU_TRANSPARENT) );

	InitPolymorphicCommand( OPTOKEN_PALETTE_RESTORE,				_R(IDS_MENU_RESTORE) );
	InitPolymorphicCommand( OPTOKEN_PALETTE_DELETE,					_R(IDS_MENU_DELETE) );

	InitPolymorphicCommand( OPTOKEN_PALETTE_SYSTEM_COLOURS,			_R(IDS_MENU_SYSTEM_COLOURS) );

	InitPolymorphicCommand( OPTOKEN_PALETTE_SORT_BY_USE,			_R(IDS_MENU_SORT_BY_USE) );
	InitPolymorphicCommand( OPTOKEN_PALETTE_SORT_BY_LUMINANCE,		_R(IDS_MENU_SORT_BY_LUMINANCE) );
	InitPolymorphicCommand( OPTOKEN_PALETTE_SORT_BY_HUE,			_R(IDS_MENU_SORT_BY_HUE) );

	return TRUE;
}               


/******************************************************************************************
>	OpState	OpPalettePopupCommand::GetCommandState(String_256 *UIDescription, OpDescriptor *pOpDesc)
	Author:		Alex_Price (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/08/99
	Inputs:		UIDescription - ?
				pOpDesc - ?
	Returns:	The state of the OpPreviewPopupCommand operation for the given OpDescriptor
	Purpose:	Handles the putting of tick marks, and greying out of menu items in the menu.
******************************************************************************************/
OpState	OpPalettePopupCommand::GetCommandState( String_256 *UIDescription, OpDescriptor *pOpDesc )
{
	OpState OpSt;
	OpSt.Greyed = FALSE;

	//  Get the properties of the colour under consideration
	BOOL bLocked				= m_pPaletteControl->GetSelectedColourLocked();
	BOOL bDeleted				= m_pPaletteControl->GetSelectedColourDeleted();
	BOOL bWebSafe				= m_pPaletteControl->GetSelectedColourWebSafe();
	BOOL bTransparentBackground	= BmapPrevDlg::m_pExportOptions->IsBackgroundTransparent();
	BOOL bTransparent			= m_pPaletteControl->GetSelectedColourTransparent();
	BOOL bSupportsTransp		= BmapPrevDlg::m_pExportOptions->GetSupportsTransparency();

	//  Locked menu item
	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_LOCKED ) )
	{
		if (bDeleted)
			OpSt.Greyed = TRUE;
		else if (bLocked)
			OpSt.Ticked = TRUE;
	}

	//  WebSafe menu item
	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_WEB_SAFE ) )
	{
		if (bTransparent || bDeleted || bWebSafe)
			OpSt.Greyed = TRUE;
	}

	//  Background transparent menu item
	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_TRANSPARENT_BACKGROUND ) )
	{
		if (bDeleted || !bSupportsTransp)
			OpSt.Greyed = TRUE;
		else if (bTransparentBackground)
			OpSt.Ticked = TRUE;
	}

	//  Transparent menu item
	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_TRANSPARENT ) )
	{
		if (bDeleted || !bSupportsTransp)
			OpSt.Greyed = TRUE;
		else if (bTransparent)
			OpSt.Ticked = TRUE;
	}

	//  Delete menu item
	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_DELETE ) )
	{
		if(bDeleted)
			OpSt.RemoveFromMenu = TRUE;
	}

	//  Restore menu item
	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_RESTORE ) )
	{
		if(!bDeleted)
			OpSt.RemoveFromMenu = TRUE;
	}

	//  The 'Sort by...' menu items.
	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_SORT_BY_USE ) )
		if (m_pPaletteControl->GetCurrentSortType() == BitmapExportPaletteInterface::SORT_USE)
			OpSt.Ticked = TRUE;

	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_SORT_BY_LUMINANCE ) )
		if (m_pPaletteControl->GetCurrentSortType() == BitmapExportPaletteInterface::SORT_LUMINANCE)
			OpSt.Ticked = TRUE;

	if( pOpDesc->Token == String_256( OPTOKEN_PALETTE_SORT_BY_HUE ) )
		if (m_pPaletteControl->GetCurrentSortType() == BitmapExportPaletteInterface::SORT_HUE)
			OpSt.Ticked = TRUE;

	//  Tick it if the 'System Colours' button is pressed in
//	if( ( pOpDesc->Token == String_256( OPTOKEN_PALETTE_SYSTEM_COLOURS ) ))
//		if (BmapPrevDlg::IsU
//				( m_pDialog->IsSystemColours() ) )
//			OpSt.Ticked = TRUE;

	return OpSt; 
}


/******************************************************************************************

>	virtual void OpPreviewPopupCommand::Do( OpDescriptor* pOpDesc )
 
	Author:		Alex_Price (Xara Group Ltd) <camelotdev@xara.com>

	Created:	09/08/99

	Inputs:		pOpDesc - ?

	Returns:	-

	Purpose:	Handles the menu selection

******************************************************************************************/

void OpPalettePopupCommand::Do( OpDescriptor* pOpDesc )
{  
	ERROR3IF(!m_pPaletteControl,	"Help, I am the palette right click menu and I can't talk to the palette");
	ERROR3IF(!m_pBmapPrevDlg,		"Help, I am the palette right click menu and I can't talk to the preview dialog");

	//  Get the token of the item selected by the user.
	String_256 s(pOpDesc->Token);


	if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_LOCKED))
		 m_pPaletteControl->SetSelectedColourToggleLocked();
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_WEB_SAFE))
		m_pPaletteControl->SetSelectedColourWebSafe();
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_TRANSPARENT_BACKGROUND))
	{
		BmapPrevDlg::m_pExportOptions->SetBackgroundTransparency(!BmapPrevDlg::m_pExportOptions->IsBackgroundTransparent());
		m_pBmapPrevDlg->DoPreview();
	}
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_TRANSPARENT))
		m_pPaletteControl->SetSelectedColourToggleTransparent();
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_DELETE))
		m_pPaletteControl->SetSelectedColourToggleDeleted();
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_RESTORE))
		m_pPaletteControl->SetSelectedColourToggleDeleted();
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_SYSTEM_COLOURS))
		BmapPrevDlg::m_pExportOptions->SetToUseSystemPalette(!BmapPrevDlg::m_pExportOptions->IsUsingSystemPalette());
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_SORT_BY_USE))
	{
		m_pPaletteControl->SetCurrentSortType(BitmapExportPaletteInterface::SORT_USE);
		m_pPaletteControl->RenderSoon();
	}
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_SORT_BY_LUMINANCE))
	{
		m_pPaletteControl->SetCurrentSortType(BitmapExportPaletteInterface::SORT_LUMINANCE);
		m_pPaletteControl->RenderSoon();
	}
	else if (s.IsIdentical((TCHAR *)OPTOKEN_PALETTE_SORT_BY_HUE))
	{
		m_pPaletteControl->SetCurrentSortType(BitmapExportPaletteInterface::SORT_HUE);
		m_pPaletteControl->RenderSoon();
	}

	BmapPrevDlg::m_pExportOptions->InvalidatePalette();
	m_pBmapPrevDlg->UpdateCurrentTab();
	m_pBmapPrevDlg->DoPreview();

	End();
}

