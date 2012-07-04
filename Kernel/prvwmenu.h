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


// A dialog box for previwing bitmaps

#ifndef INC_PREVIEWDLGMENU
#define INC_PREVIEWDLGMENU

#include "contmenu.h"
#include "bmpexprw.h"

// the optokens for the menu commands
#define OPTOKEN_PREVIEW_ZOOM_TOOL				_T("Preview:Zoom")
#define OPTOKEN_PREVIEW_PUSH_TOOL				_T("Preview:Push")
#define OPTOKEN_PREVIEW_COLOUR_SELECTOR_TOOL	_T("Preview:Selector")
#define OPTOKEN_PREVIEW_ZOOM_TO_FIT				_T("Preview:Fit")
#define OPTOKEN_PREVIEW_ZOOM_TO_100				_T("Preview:100")
#define OPTOKEN_PREVIEW_1TO1					_T("Preview:1:1")
#define OPTOKEN_PREVIEW_HELP					_T("Preview:Help")

/********************************************************************************************

>	class PreviewContextMenu : public ContextMenu

	Author:		Stefan_Stoykov (Xara Group Ltd) <camelotdev@xara.com> (based on Neville's code)
	Created:	11/4/97
	Purpose:	The context menu for the bitmap preview dialog

********************************************************************************************/

class PreviewContextMenu : public ContextMenu
{
public:
	// the only necessary function
	virtual	BOOL		Build();
};


/********************************************************************************************

>	class OpPreviewPopupCommand : public Operation

	Author:		Stefan_Stoykov (Xara Group Ltd) <camelotdev@xara.com> (based on Neville's code)
	Created:	11/4/97
	Purpose:	The context menu handling for the bitmap preview dialog

********************************************************************************************/

class OpPreviewPopupCommand : public Operation
{
	CC_DECLARE_DYNCREATE(OpPreviewPopupCommand);

public:
	static BOOL Init(void);
				// Initialises the Ops that the dialog can use

protected:
	static BOOL InitPolymorphicCommand(TCHAR *OpToken, UINT32 MenuTextID);
				// Called by Init() to create another OpDescriptor for this Op.

public:
	static OpState GetCommandState(String_256 *ShadeReason, OpDescriptor *pOpDesc);
				// The GetState method goes by a different name to avoid clashes with
				// derived classes. This one calls the editor to determine the state.
				
	virtual void Do(OpDescriptor* pOpDesc);
				// Calls the dialog with a command based on the OpDescriptor OpToken

public:
	// pointer to the dialog
	static BitmapExportPreviewDialog *m_pDialog;
};



#endif  // INC_PREVIEWDLGMENU


