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


// Context sensitive menu for the colour editor


#ifndef INC_COLMENU
#define INC_COLMENU

#include "contmenu.h"
//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]



// --- Colour editor menu commands - defined in colmenu.cpp
extern String_32 ColCmd_Help;
extern String_32 ColCmd_Name;
extern String_32 ColCmd_HSV;
extern String_32 ColCmd_RGB;
extern String_32 ColCmd_CMYK;
extern String_32 ColCmd_Grey;
extern String_32 ColCmd_EditParent;
#ifdef WEBSTER
extern String_32 ColCmd_NewNColour;
#endif //WEBSTER




/********************************************************************************************

>	class ColEditContextMenu : public ContextMenu

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95
	Purpose:	Implements the colour editor context sensitive menus

********************************************************************************************/

class ColEditContextMenu : public ContextMenu
{
	CC_DECLARE_MEMDUMP(ColEditContextMenu);

public:
	ColEditContextMenu();

	virtual BOOL Build(void);
			// Builds a pop-up menu over the editor
};




/********************************************************************************************

>	class OpColEditCommand : public Operation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95

	Purpose:	A polymorphic Op which is used for all generic colour editor "commands".

				A colour editor command is an OpToken along the lines "DoSomething"
				where "DoSomething" indicates a command supported by the editor.

********************************************************************************************/

class OpColEditCommand : public Operation
{
CC_DECLARE_DYNCREATE(OpColEditCommand);

public:
	static BOOL Init(void);
				// Initialises the Ops that the colour editor can use

protected:
	static BOOL InitPolymorphicCommand(StringBase *OpToken, UINT32 MenuTextID);
				// Called by Init() to create another OpDescriptor for this Op.

public:
	static OpState GetCommandState(String_256 *ShadeReason, OpDescriptor *pOpDesc);
				// The GetState method goes by a different name to avoid clashes with
				// derived classes. This one calls the editor to determine the state.
				
	virtual void Do(OpDescriptor* pOpDesc);
				// Calls the editor with a command based on the OpDescriptor OpToken
};


#endif

