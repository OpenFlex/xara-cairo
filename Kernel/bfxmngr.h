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


// bfxmngr.h : header file
//

// This file contains specific BFX plug-in manager related items
// At present this includes:-

// BfxHandler
// Defines the characteristics of a BFX plug-in and provides a function
// for parsing them.

#ifndef INC_BFXPLUGINMANAGER
#define INC_BFXPLUGINMANAGER

#include "plugmngr.h"	// PlugInHandler

/**************************************************************************************

>	class BfxHandler : public PlugInHandler

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/97
	Purpose:	Provides BFX plug-in handling characteristics.
				It handles defining what file types BFX plug-ins have and how to
				parse them. As these are the built in filters, they are just added when
				the handler is inited.

**************************************************************************************/

class BfxHandler : public PlugInHandler
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNAMIC(BfxHandler);

public:
	BfxHandler();
	~BfxHandler();

	virtual BOOL Init();

public:
	// Useful helper functions
	virtual BOOL AddFixedPlugIns();

	// Add a plug-in to the list in the plug-in manager
	virtual BOOL AddPlugIn(PlugInItem * pPlugIn, CCRuntimeClass* pClass = CC_RUNTIME_CLASS(PlugInOp),
						   pfnGetState gs = PlugInOp::GetState);

	// go and parse the specified plug-in
	virtual BOOL ParsePlugIn(const PathName& Path, const INT32 PathID);

	// go and add in the any main menu items that this handler requires
	virtual BOOL CreateMainMenuItems(PlugInManager * pManager, MenuItem * pRootMenu,
									 BOOL AddSeparator = FALSE);
	// a handler is asked whether it is going to add menu items so that the manager
	// can decide whether to ask the previous handler to add a separator to the end
	// of its added menus
	// Need to override this if the above function is overriden
	virtual BOOL GoingToAddMainMenuItems() { return TRUE; }

public:
	// define this handler's unique characteristics

	// return a string describing a unique identifier for the plug-ins this handler is interested in
	virtual String_32 GetUniqueID() const; 
	// return a unique type for this kind of plug-in
	virtual TypeOfPlugIn GetTypeOfPlugIn() const;
	// return a string descibing what filetypes the plug-in handler is interested in
	virtual String_32 GetFileTypes() const; 

public:
};

#endif // INC_BFXPLUGINMANAGER
