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


#ifndef INC_DRAGTOOL
#define INC_DRAGTOOL

//#include "tool.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "transop.h"

/********************************************************************************************
>	class DragTool : public Tool_v1

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/1999
	Purpose:	The Drag tool is a base class for the Selector and Slice tools.
				It acts to give these tools a common heritage, so that TransOperation,
				which handles dragging of objects, can maintain a pointer to them and inform
				them of various events during a drag. At some point in the future (ie maybe
				never, but we can hope...) it may be useful to pull common drag functionality
				up from these two tools, into a base implementation in this class.

				Currently, all the function definitions in this class are purely to allow
				TransOperation's pSelTool data member to be  changed from a SelectorTool*
				to a DragTool*. Default implementation in this class is simply to do nothing.

				CGS:

				The DragTool is also the base class for all tools which require selection
				ability.  A single interface is provided for this pupose:  OnClick ().
				OnClick () actually serves as a wrapper for our selection tool - thereby
				allowing all derived tools to harness the power of our selection tool.

********************************************************************************************/

class CCAPI DragTool : public Tool_v1
{
// own up in memory dumps
CC_DECLARE_MEMDUMP(DragTool);

////////////////////////////////////////////////////////////////////////////////////////////
// Tool interface

public:
	// Function that allows the transform to tell the tool how things are going.
	virtual void DragMove(TransformBoundingData* pBoundingData);

	// This function returns TRUE if the given floating-point value exceeds the range
	// that FIXED16 numbers can represent.
	// *What* it is doing inside a Tool class, I don't know.
	static BOOL BeyondFixedRange(double fpFixedVal);

	// Notify the current tool of click events on the document...
	virtual void OnClick(DocCoord PointerPos, ClickType cType, ClickModifiers cMods, Spread* pSpread);

private:
	// Standard tool static vars
	static 	TCHAR *FamilyName;					// The Tools Family Name
	static 	TCHAR *ToolName;					// The Tool Name
	static 	TCHAR *Purpose;						// What the tool is for
	static 	TCHAR *Author;						// Who wrote it
};

#endif	// INC_DRAGTOOL
