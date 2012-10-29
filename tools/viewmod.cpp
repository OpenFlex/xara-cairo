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
#include "nodecont.h"
#include "viewmod.h"
//#ifndef _AFXDLL
// tools that can go in DLLs go here
#include "pushtool.h"
#include "zoomtool.h"
#include "freehand.h"
#include "pentool.h"
#include "blndtool.h"
#include "beztool.h"
#include "filltool.h"
//#include "gridtool.h"
#include "regshape.h"
#include "rectangl.h"
#include "moldtool.h"
#include "texttool.h"
#include "shadtool.h"	// shadow tool header, Olivier 29/10/96
//#include "blnktool.h"
#include "cntrtool.h"  // contour tool, DavidM 24/8/99
//#endif
// tools that cannot go in DLLs go here
#include "selector.h"
#include "eliptool.h"
#include "bevtool.h"
//#include "slicetool.h"
//#include "liveeffectstool.h"


static char Name[] 		= "Kernel Module";
static char Purpose[] 	= "Tools that need to be in the kernel";
static char Author[] 	= "The Nasty People";

DECLARE_SOURCE("$Revision: 1464 $");

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

// this macro makes it easier to move tools from the .exe to the .dll
// in AFXDLL builds, the macro returns NULL, otherwise it does a 'new classtype'

//#if _AFXDLL
//#define	IN_DLL(classname)	NULL
//#else
#define	IN_DLL(classname)	new classname
//#endif

#define	NOT_IN_DLL(classname)	new classname

/********************************************************************************************

>	virtual BOOL ViewModule::Init()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/7/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Initialise the view module (which contains the Push and Zoom tools).
				Does nothing at the moment.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL ViewModule::Init()
{
#if !defined(EXCLUDE_FROM_RALPH)
#ifdef STANDALONE
	TextTool* pTextTool = new TextTool();
	if (pTextTool)
		pTextTool->Init();
#endif
#endif

	return TRUE;
}
	
/********************************************************************************************

>	virtual void ViewModule::Describe(void* Info)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/7/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Get info on the Module.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void ViewModule::Describe(void* Info)
{
	// Cast the pointer into one we understand...
	
	ModInfo_v1 *ModInfo = (ModInfo_v1 *) Info;
	
	// ...and fill in the fields
	
	ModInfo->InfoVersion = 1;
	ModInfo->InterfaceVersion = GetInterfaceVersion();
	ModInfo->Version = 1;
	ModInfo->ID = MODULEID_KERNEL;
#ifdef STANDALONE
	ModInfo->NumTools = 2;
#else
#ifdef BUILDSHADOWS
	ModInfo->NumTools = 21; // Shadows + Bevels + Contours + Slicing
#else
	ModInfo->NumTools = 18; // Shadows + Bevels + Contours + Slicing
#endif
#endif
	ModInfo->Name = Name;
	ModInfo->Purpose = Purpose;
	ModInfo->Author = Author;
}
	

/********************************************************************************************

>	virtual void *ViewModule::CreateTool(UINT32 Type)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/7/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Create an instance of a given tool.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void *ViewModule::CreateTool(UINT32 Type)
{
	switch (Type)
	{
		case 1:
			return IN_DLL(ZoomTool);
			
		case 2:
			return IN_DLL(PushTool);

#ifndef STANDALONE
		case 3:
			return IN_DLL(RectangleTool);

#ifndef WEBSTER	//Martin-06/11/96-begin
		case 4:
			return IN_DLL(FreeHandTool);
#endif	//WEBSTER

		case 5:
			return NOT_IN_DLL(SelectorTool);

PORTNOTE("other","Removed grid tool usage")
#ifndef EXCLUDE_FROM_XARALX
#ifndef WEBSTER	//Martin
		case 6:
			return IN_DLL(GridTool);

#endif	//WEBSTER
#endif
		case 7:
			return IN_DLL(BezierTool);

		case 8:
			return NOT_IN_DLL(EllipseTool);

		case 9:
			return IN_DLL(GradFillTool);

#ifndef WEBSTER	//Martin
		case 10:
			return IN_DLL(PenTool);

		case 11:
			return IN_DLL(BlendTool);
#endif	//WEBSTER

		case 12:
			return IN_DLL(TranspTool);

		case 13:
			return IN_DLL(QuickShapeTool);

#ifndef WEBSTER	//Martin
		case 14:
			return IN_DLL(MouldTool);

PORTNOTE("other","Removed blank tool usage")
#ifndef EXCLUDE_FROM_XARALX
		case 15:
			return IN_DLL(BlankTool);
#endif
#endif	//WEBSTER-Martin-06/11/96-end

		case 16:
			return IN_DLL(TextTool);

#ifndef NO_ADVANCED_TOOLS
PORTNOTE("other","Removed effects tool usage")
#ifndef EXCLUDE_FROM_XARALX
		case 17:
			return IN_DLL(LiveEffectsTool);
#endif

		case 18:
			return IN_DLL(SoftShadowTool);

		case 19:
			return IN_DLL(BevelTool);

		case 20:
			return IN_DLL(ContourTool);
#endif

PORTNOTE("other","Removed slice tool usage")
#ifndef EXCLUDE_FROM_XARALX
		case 21:
			return IN_DLL(SliceTool);
#endif

		// Add more view tools here...

#endif
	}
	
	return NULL;
}


