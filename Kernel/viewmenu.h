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

//
// Context sensitive menu for DocViews
//

#ifndef INC_VIEWMENU
#define INC_VIEWMENU

#include "contmenu.h"

class NodeRenderableInk;

/********************************************************************************************

>	class ViewContextMenu : public ContextMenu

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/03/95
	Purpose:	Implements the DocView context sensitive menu

********************************************************************************************/

class ViewContextMenu : public ContextMenu
{
	// Give my name in memory dumps
	// If you need a different sort of decare, replace this one. 
	// See CCObject in the help file for info about DECLARE types
	CC_DECLARE_MEMDUMP(ViewContextMenu);

public:
	BOOL		BuildOverView(Spread* pSpread, DocCoord ClickPos, ClickModifiers ClickMods);

private:
	BOOL		AskBlobsForItems(Spread* pSpread, DocCoord ClickPos, ClickModifiers ClickMods);

	NodeRenderableInk*	FindNodeAtPoint(Spread* pSpread, DocCoord ClickPos);
};

#endif  // INC_VIEWMENU


