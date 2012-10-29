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

// The Ellipse Tool
// Created by Rik on 31/5/94

/*
*/

#include "camtypes.h"
#include "eliptool.h"

#include "oilfiles.h"
#include "oprshape.h"
//#include "markn.h"
//#include "rik.h"
//#include "viewrc.h"

//#include "will2.h"


// These are still char* while we wait for resource technology to be developed for modules
TCHAR*		EllipseTool::FamilyName = _T("Shape Tools");
TCHAR* 		EllipseTool::ToolName = _T("Ellipse Tool");
TCHAR*		EllipseTool::Purpose = _T("Manipulating ellipses");
TCHAR*		EllipseTool::Author = _T("Peter Arnold");


CC_IMPLEMENT_MEMDUMP( EllipseTool, QuickShapeBase )

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	EllipseTool::EllipseTool()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/03/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Constructor for the QuickShape tool
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
EllipseTool::EllipseTool() : QuickShapeBase()
{
	CreationMode = OpNewRegShape::BOUNDS;
}



/********************************************************************************************

>	EllipseTool::~EllipseTool()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/03/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	QuickShapes tools destructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
EllipseTool::~EllipseTool()
{

}



/********************************************************************************************

>	void EllipseTool::Describe(void *InfoPtr)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/11/94
	Inputs:		InfoPtr - 	A pointer to a tool info block.
	Outputs:	InfoPtr - 	The structure pointed to by InfoPtr will have had all the info
							that this version of the Tool knows about
	Purpose:	Allows the tool manager to extract information about the tool

********************************************************************************************/

void EllipseTool::Describe(void *InfoPtr)
{
	// Cast structure into the latest one we understand.
	ToolInfo_v1 *Info = (ToolInfo_v1 *) InfoPtr;

	Info->InfoVersion = 1;
	
	Info->InterfaceVersion = GetToolInterfaceVersion();
		
	Info->Version = 1;
	Info->ID      = GetID();
	Info->TextID  = _R(IDS_ELLIPSE_TOOL);

	Info->Family  = FamilyName;
	Info->Name    = ToolName;
	Info->Purpose = Purpose;
	Info->Author  = Author;

	Info->BubbleID = _R(IDBBL_ELIP_TOOLBOX);
}



/********************************************************************************************

>	BOOL EllipseTool::Init()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/03/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE/FALSE for success/failure
	Purpose:	Called to initialise the ellipse tool.
	Errors:		-
	SeeAlso:	QuickShapeBase::Init

********************************************************************************************/
BOOL EllipseTool::Init()
{
	BOOL ok = TRUE;

	pQuickShapeBaseInfoBarOp = new QuickShapeBaseInfoBarOp(this, _R(IDD_ELLIPSETOOLBAR));
	return pQuickShapeBaseInfoBarOp != NULL;

PORTNOTE("dialog", "Removed Bar reading")
#if 0
	CCResTextFile file;									// Resource File
	QuickShapeBaseInfoBarOpCreate BarCreate;			// Object that creates QuickShapeBaseInfoBarOp objects

	 		ok = file.open(_R(IDM_ELLIPSE_BAR), _R(IDT_INFO_BAR_RES));	// Open resource
	if (ok) ok = DialogBarOp::ReadBarsFromFile(file,BarCreate);	// Read and create info bar
	if (ok) file.close();									 	// Close resource

	ERROR2IF(!ok,FALSE,"Unable to load EllipseTool.ini from resource"); 

	// Info bar now exists.  Now get a pointer to it
	String_32 str = String_32(_R(IDS_ELIPTOOL_INFOBARNAME));
	DialogBarOp* pDialogBarOp = DialogBarOp::FindDialogBarOp(str);
	
	ERROR2IF(pDialogBarOp==NULL, FALSE, "Ellipse infobar not found\n");

	ok = pDialogBarOp->IsKindOf(CC_RUNTIME_CLASS(QuickShapeBaseInfoBarOp));
	if (ok)
	{
		pQuickShapeBaseInfoBarOp = (QuickShapeBaseInfoBarOp*)pDialogBarOp;
		pQuickShapeBaseInfoBarOp->pQuickShapeBase = this;
	}
#endif
	ERROR2IF(!ok,FALSE,"Error finding the Ellipse tool info bar");

	return (ok);
}



/********************************************************************************************

>	virtual BOOL EllipseTool::IsInterestingShape(NodeRegularShape* pShape)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/03/95
	Inputs:		pShape - points to a regular shape in the document
	Outputs:	-
	Returns:	TRUE if the shapes IsCircular flag is set
	Purpose:	For saying that the ellipse tool only processed elipitical shapes.

********************************************************************************************/
BOOL EllipseTool::IsInterestingShape(NodeRegularShape* pShape)
{
	return pShape->IsCircular();
}
