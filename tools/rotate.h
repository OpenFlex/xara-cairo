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

// The Rotation Tool



#ifndef INC_ROTATE
#define INC_ROTATE


class Cursor;
class RotateInfoBarOp;


/********************************************************************************************

>	class RotateTool : public Tool_v1

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/7/94
	Purpose:	Implementation of the Rotate Tool

********************************************************************************************/

class CCAPI RotateTool : public Tool_v1
{
// Give my name in memory dumps
CC_DECLARE_MEMDUMP(RotateTool);

public:
	RotateTool();
	~RotateTool();
	BOOL Init();
	void Describe(void* InfoPtr);
	UINT32 GetID() { return TOOLID_ROTATE; };
	
	// Event Handlers
	virtual void SelectChange(BOOL);
	virtual void OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	virtual void RenderToolBlobs(Spread*, DocRect*);
	
private:
	static 	char* FamilyName;	// The Tools Family Name
	static 	char* ToolName;		// The Tool Name
	static 	char* Purpose;		// What the tool is for
	static 	char* Author;		// Who wrote it
	
	// info about clicks as they arrive
	DocCoord ClickStart;		// Where the first click was clicked
	Spread*  StartSpread;		// The spread where we received the first click

	// The Centre of rotation and the bounding box of the selection
	DocCoord CentreOfRot;
	DocRect  SelectionBox;

	// A count of the number of selected object when the tool was selected
	BOOL	 IsSelection;

	// The tools cursor
	Cursor* pRotateCursor;

	// The info bar
	RotateInfoBarOp* pInfoBarOp;
};


#endif



