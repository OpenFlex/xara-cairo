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


/*
*/

#include "camtypes.h"
#include "oiltool.h"
#include "oilmods.h"

DECLARE_SOURCE("$Revision: 751 $");

/********************************************************************************************

>	OILTool::OILTool(UINT32 ModuleID)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/7/93
	Inputs:		ModuleID - the ID of the module that owns this Tool.
	Outputs:	-
	Returns:	-
	Purpose:	Create an OILTool object that can be linked to a Tool object (via a
				ToolListItem object).  This object (the OILTool) knows the instance handle
				of the DLL that contains the tool.
	Errors:		-
	SeeAlso:	Tool; ToolListItem; Module; ModuleListItem

********************************************************************************************/


OILTool::OILTool(UINT32 ModuleID)
{
	// Obtain and remember the Instance handle of the DLL that holds the resources
	// of the parent module of this tool (and hence holds the resources of the tool).
	hInstance = OILModule::GetInstance(ModuleID);
}

/********************************************************************************************

>	HCURSOR OILTool::LoadCursor(UINT32 ID)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/7/93
	Inputs:		ID - The resource ID of the cursor to load.
	Outputs:	-
	Returns:	The handle to the loaded cursor, or NULL if unsuccessful
	Purpose:	Find a cursor resource, which may be in the kernel's resources, or it
				may be from the tool's own resources.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
	
HCURSOR OILTool::LoadCursor(UINT32 ID)
{
	HINSTANCE Inst;
	
	if ((DLLs[0] == (HINSTANCE)HINSTANCE_ERROR || DLLs[0] == 0) || ((ID >= KID_FIRST) && (ID <= KID_LAST)))
		Inst = AfxGetResourceHandle(); 	// Kernel resource - get the HINSTANCE of our dll, or .EXE
	else
		Inst = hInstance; 				// otherwise use the HINSTANCE of the Tool's DLL

	// If the HINSTANCE we have is valid, attempt to load the resource, otherwise
	// return a NULL value.
		
	if (Inst > (HINSTANCE)HINSTANCE_ERROR)
		return ::LoadCursor(Inst, MAKEINTRESOURCE(ID));
	else
		return NULL;
}

/********************************************************************************************

>	HBITMAP OILTool::LoadBitmap(UINT32 ID)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/7/93
	Inputs:		ID - The resource ID of the bitmap to load.
	Outputs:	-
	Returns:	The handle to the loaded bitmap, or NULL if unsuccessful
	Purpose:	Find a bitmap resource, which may be in the kernel's resources, or it
				may be from the tool's own resources.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
	
HBITMAP OILTool::LoadBitmap(UINT32 ID)
{
	HINSTANCE Inst;
	
	if ((DLLs[0] == (HINSTANCE)HINSTANCE_ERROR || DLLs[0] == 0) || ((ID >= KID_FIRST) && (ID <= KID_LAST)))
		Inst = AfxGetResourceHandle(); 	// Kernel resource - get the HINSTANCE of our .EXE
	else
		Inst = hInstance; 				// otherwise use the HINSTANCE of the Tool's DLL
		
	// If the HINSTANCE we have is valid, attempt to load the resource, otherwise
	// return a NULL value.
		
	if (Inst > (HINSTANCE)HINSTANCE_ERROR)
		return ::LoadBitmap(Inst, MAKEINTRESOURCE(ID));
	else
		return NULL;
}

/********************************************************************************************

>	HICON OILTool::LoadIcon(UINT32 ID)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/7/93
	Inputs:		ID - The resource ID of the icon to load.
	Outputs:	-
	Returns:	The handle to the loaded icon, or NULL if unsuccessful
	Purpose:	Find an icon resource, which may be in the kernel's resources, or it
				may be from the tool's own resources.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
	
HICON OILTool::LoadIcon(UINT32 ID)
{
	HINSTANCE Inst;
	
	if ((DLLs[0] == (HINSTANCE)HINSTANCE_ERROR || DLLs[0] == 0) || ((ID >= KID_FIRST) && (ID <= KID_LAST)))
		Inst = AfxGetResourceHandle(); 	// Kernel resource - get the HINSTANCE of our .EXE
	else
		Inst = hInstance; 				// otherwise use the HINSTANCE of the Tool's DLL
		
	// If the HINSTANCE we have is valid, attempt to load the resource, otherwise
	// return a NULL value.
		
	if (Inst > (HINSTANCE)HINSTANCE_ERROR)
		return ::LoadIcon(Inst, MAKEINTRESOURCE(ID));
	else
		return NULL;
}
	
/********************************************************************************************

>	BOOL OILTool::LoadString(UINT32 ID, String*)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/8/93
	Inputs:		ID - The resource ID of the string to load.
	Outputs:	The String that was loaded
	Returns:	TRUE if String is loaded successfully, or FALSE Otherwise
	Purpose:	Find a string resource, which may be in the kernel's resources, or it
				may be from the tool's own resources.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
	
BOOL OILTool::LoadString(UINT32 ID, char* Description)
{
	// Maximum allowable size of a windows string resource
	const INT32 MaxStringSize = 256;

	HINSTANCE Inst;
	
	if ((DLLs[0] == (HINSTANCE)HINSTANCE_ERROR || DLLs[0] == 0) || ((ID >= KID_FIRST) && (ID <= KID_LAST)))
		Inst = AfxGetResourceHandle(); 	// Kernel resource - get the HINSTANCE of our .EXE
	else
		Inst = hInstance; 				// otherwise use the HINSTANCE of the Tool's DLL
		
	// If the HINSTANCE we have is valid, attempt to load the resource, otherwise
	// return FALSE.
		
	if (Inst > (HINSTANCE)HINSTANCE_ERROR)
		return ::LoadString(Inst, ID, Description, MaxStringSize);
	else
		return FALSE;
}
	
