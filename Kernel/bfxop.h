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


// Operations and Context sensitive menu for BFX plug-ins

#ifndef INC_BFXPLUGINOP
#define INC_BFXPLUGINOP

#include "plugop.h"

#define OPTOKEN_BFX_SPECIALEFFECTS _T("BfxSpecialEffects");

/********************************************************************************************

>	class BfxPlugInOp : public PlugInOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/97
	Purpose:	Operation so that a BFX plug-ins can be invoked and used.  

********************************************************************************************/				

class BfxPlugInOp : public PlugInOp
{
	CC_DECLARE_DYNCREATE( BfxPlugInOp );

public:

	BfxPlugInOp();

	virtual void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);	

	// Useful function to ask a plug-in to see whether it likes the selected bitmap
	static BOOL CheckBitmapWithPlugIn(const String_256& OpName, BOOL IncludeUniqueName = TRUE,
									  BOOL IncludeUndoAbleSig = FALSE);

	static BOOL SetBitmapAndDocument(KernelBitmap* pBitmap, Document * pDocument);

private:
	// As we are invoked from a menu item, we need to be told what bitmap we are
	// working on, so these need to be set up before the operation is invoked.
	static KernelBitmap * m_pBitmap;
	static Document * m_pDocument;
};

/********************************************************************************************

>	class BfxPlugInContextMenu : public PlugInsContextMenu

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/97
	Purpose:	Implements the Bfx plug-ins context sensitive menus
	SeeAlso:	ContextMenu

********************************************************************************************/

class BfxPlugInContextMenu : public PlugInsContextMenu
{
	CC_DECLARE_MEMDUMP(BfxPlugInContextMenu);

public:
	//  DO NOT CALL the constructor Default constructor - use the one below
	BfxPlugInContextMenu(KernelBitmap* pBitmap, Document * pDocument);

	virtual BOOL Build();

	static BOOL BuildMenu(KernelBitmap * pBitmap, Document * pDocument,
						  ContextMenu * pContextMenu, MenuItem* pMainRoot = NULL,
						  BOOL AddSeparator = FALSE, BOOL UseUndoable = FALSE);

protected:
	// As we are invoked from a menu item, we need to be told what bitmap we are
	// working on, so these need to be set up before the operation is invoked.
	KernelBitmap * m_pBitmap;
	Document * m_pDocument;
};

#endif // INC_BFXPLUGINOP
