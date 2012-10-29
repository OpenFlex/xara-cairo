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


// OpDescriptor, Operations and Context sensitive menu for plug-ins

#ifndef INC_PLUGINOP
#define INC_PLUGINOP

#include "contmenu.h"

class KernelBitmap;
/********************************************************************************************

>	class PlugInOp : public Operation

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/11/96
	Purpose:	Operation so that a plug-ins can be invoked and used.  

********************************************************************************************/				

#define OPTOKEN_PLUGINS				_T("PlugIns")

class PlugInOp : public Operation
{
	CC_DECLARE_DYNCREATE( PlugInOp );

public:

	PlugInOp();

	virtual void Do(OpDescriptor*);

	static BOOL Init();
	static BOOL RegisterOpToken(TCHAR *OpToken, const String_64& NewMenuText,
								CCRuntimeClass* pClass = CC_RUNTIME_CLASS(PlugInOp),
								pfnGetState gs = GetState);
	static BOOL RegisterOpToken(TCHAR *OpToken, UINT32 MenuTextID,
								CCRuntimeClass* pClass = CC_RUNTIME_CLASS(PlugInOp),
								pfnGetState gs = GetState);
	static OpState GetState(String_256*, OpDescriptor*);	

private:
};


/********************************************************************************************

>	class PlugInsContextMenu : public ContextMenu

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/11/96
	Purpose:	Implements the plug-ins context sensitive menus

	SeeAlso:	ContextMenu

********************************************************************************************/

class PlugInsContextMenu : public ContextMenu
{
	CC_DECLARE_MEMDUMP(PlugInsContextMenu);

public:
	PlugInsContextMenu();
			// Default constructor - DO NOT CALL this constructor - use the one below
	PlugInsContextMenu(KernelBitmap* pBitmap, Document * pDocument);

	virtual BOOL Build(void);
			// Builds a pop-up menu over the gallery list

	static BOOL BuildMenu(KernelBitmap * pBitmap, Document * pDocument,
						  ContextMenu * pContextMenu, MenuItem* pMainRoot = NULL,
						  BOOL AddSeparator = FALSE, BOOL UseUndoable = FALSE);
protected:
	// As we are invoked from a menu item, we need to be told what bitmap we are
	// working on, so these need to be set up before the operation is invoked.
	KernelBitmap * m_pBitmap;
	Document * m_pDocument;
};

/********************************************************************************************

>	class PlugInOpDescriptor : public OpDescriptor

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/12/96
	Purpose:	New PlugInOpDescriptor class whose purpose in life is to allow an OpDescriptor
				to be created which instead of using a resource id to get the menu item/operation
				item text, uses a string resource. This then means we can use the name from the
				plug-in instead of having to resource all names!

********************************************************************************************/

class PlugInOpDescriptor : public OpDescriptor
{
	CC_DECLARE_DYNAMIC( PlugInOpDescriptor );

public:
	PlugInOpDescriptor(const TCHAR* pcszToken, const String_64& NewMenuText,
								CCRuntimeClass* pClass = CC_RUNTIME_CLASS(PlugInOp),
								pfnGetState gs = PlugInOp::GetState);

	// This will use the TextID to obtain a string resource text description of the 
	// operation. 
	virtual BOOL GetText(String_256* Description, OpTextFlags WhichText);

	static OpState GetState(String_256* psName, OpDescriptor* pOpDesc);

protected:
	// Replaces MenuID resource
	String_64 m_MenuText;
};

#endif // INC_PLUGINOP
