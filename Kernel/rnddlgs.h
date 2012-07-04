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

// The base class for dialogs that render into themselves

#ifndef INC_RNDDLGS
#define INC_RNDDLGS

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
class RenderRegion;
class DocRect;
struct ReDrawInfoType;

/********************************************************************************************

>	class RenderDialogOp : public DialogOp

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/10/94
	Purpose:	Acts as a base class for all Dialogs that want to render using render regions
				in them.

	Notes:		This functionality has been moved into DialogOp so that it may be shared
				by DialogBarOps. Thus, you can just derive directly from DialogOp. This
				class may cease to exist soon.

********************************************************************************************/

class RenderDialogOp : public DialogOp
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(RenderDialogOp);

public:
	// Constructor - just passed straight on to the DialogOp
	RenderDialogOp(CDlgResID DialogResID, CDlgMode Mode);
};


#endif  // INC_RNDDLGS

