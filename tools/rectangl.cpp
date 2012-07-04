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

// The Rectangle Tool
// Created by Mario Shamtani on 13/9/93

/*
*/


#include "camtypes.h"
#include "rectangl.h"

#include "oilfiles.h"
#include "oprshape.h"
//#include "mario.h"
//#include "markn.h"
//#include "viewrc.h"

//#include "will2.h"

DECLARE_SOURCE( "$Revision: 1464 $" );

// These are still char* while we wait for resource technology to be developed for modules
TCHAR *		RectangleTool::FamilyName = _T("Shape Tools");
TCHAR * 		RectangleTool::ToolName = _T("Rectangle Tool");
TCHAR *		RectangleTool::Purpose = _T("Manipulating rectangles");
TCHAR *		RectangleTool::Author = _T("Peter Arnold");


CC_IMPLEMENT_MEMDUMP( RectangleTool, QuickShapeBase )

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	RectangleTool::RectangleTool()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/03/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Constructor for the QuickShape tool
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
RectangleTool::RectangleTool() : QuickShapeBase()
{
	CreationMode = OpNewRegShape::BOUNDS;
}



/********************************************************************************************

>	RectangleTool::~RectangleTool()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/03/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	QuickShapes tools destructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
RectangleTool::~RectangleTool()
{

}



/********************************************************************************************

>	void RectangleTool::Describe(void *InfoPtr)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/11/94
	Inputs:		InfoPtr - 	A pointer to a tool info block.
	Outputs:	InfoPtr - 	The structure pointed to by InfoPtr will have had all the info
							that this version of the Tool knows about
	Purpose:	Allows the tool manager to extract information about the tool

********************************************************************************************/

void RectangleTool::Describe(void *InfoPtr)
{
	// Cast structure into the latest one we understand.
	ToolInfo_v1 *Info = (ToolInfo_v1 *) InfoPtr;

	Info->InfoVersion = 1;
	
	Info->InterfaceVersion = GetToolInterfaceVersion();
		
	Info->Version = 1;
	Info->ID      = GetID();
	Info->TextID  = _R(IDS_RECTANGLE_TOOL);

	Info->Family  = FamilyName;
	Info->Name    = ToolName;
	Info->Purpose = Purpose;
	Info->Author  = Author;

	Info->BubbleID = _R(IDBBL_RECT_TOOLBOX);
}



/********************************************************************************************

>	BOOL RectangleTool::Init()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/03/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE/FALSE for success/failure
	Purpose:	Called to initialise the ellipse tool.
	Errors:		-
	SeeAlso:	QuickShapeBase::Init

********************************************************************************************/
BOOL RectangleTool::Init()
{
	pQuickShapeBaseInfoBarOp = new QuickShapeBaseInfoBarOp(this, _R(IDD_RECTTOOLBAR));
	return pQuickShapeBaseInfoBarOp != NULL;

PORTNOTE("dialog", "Removed Bar reading")
#if 0
	BOOL ok = TRUE;

	CCResTextFile file;									// Resource File
	QuickShapeBaseInfoBarOpCreate BarCreate;			// Object that creates QuickShapeBaseInfoBarOp objects

	 		ok = file.open(_R(IDM_RECT_BAR), _R(IDT_INFO_BAR_RES));	// Open resource
	if (ok) ok = DialogBarOp::ReadBarsFromFile(file,BarCreate);	// Read and create info bar
	if (ok) file.close();									 	// Close resource

	ERROR2IF(!ok,FALSE,"Unable to load RectTool.ini from resource"); 

	// Info bar now exists.  Now get a pointer to it
	String_32 str = String_32(_R(IDS_RECTTOOL_INFOBARNAME));
	DialogBarOp* pDialogBarOp = DialogBarOp::FindDialogBarOp(str);
	
	ERROR2IF(pDialogBarOp==NULL, FALSE, "Rectangle infobar not found\n");

	ok = pDialogBarOp->IsKindOf(CC_RUNTIME_CLASS(QuickShapeBaseInfoBarOp));
	if (ok)
	{
		pQuickShapeBaseInfoBarOp = (QuickShapeBaseInfoBarOp*)pDialogBarOp;
		pQuickShapeBaseInfoBarOp->pQuickShapeBase = this;
	}

	ERROR2IF(!ok,FALSE,"Error finding the Rectangle tool info bar");

	return (ok);
#endif
}



/********************************************************************************************

>	virtual BOOL RectangleTool::IsInterestingShape(NodeRegularShape* pShape)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/03/95
	Inputs:		pShape - points to a regular shape in the document
	Outputs:	-
	Returns:	TRUE if the shapes IsCircular flag is set
	Purpose:	For saying that the ellipse tool only processed elipitical shapes.

********************************************************************************************/
BOOL RectangleTool::IsInterestingShape(NodeRegularShape* pShape)
{
	return (pShape->IsARectangle());
}


