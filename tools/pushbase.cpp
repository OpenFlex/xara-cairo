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


// DLL-end of push tool DLL

#include "camtypes.h"
#include <afxdllx.h>
#include "module.h"
#include "pushtool.h"
//#include "zoomtool.h"
//#include "freehand.h"
#include "pentool.h"
//#include "blndtool.h"
#include "beztool.h"
#include "filltool.h"
#include "gridtool.h"
#include "rectangl.h"
#include "regshape.h"
#include "moldtool.h"
#include "blnktool.h"

#include "ezmodule.h"

#if 0
#ifndef WIN32
#error 32-bit only - why are you compiling me?
#endif
static AFX_EXTENSION_MODULE extensionDLL;

extern "C" INT32 APIENTRY
DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID)
{

	if (dwReason==DLL_PROCESS_ATTACH)
	{
		if (!AfxInitExtensionModule(extensionDLL, hInstance))
			return 0;
	}
	return 1;
}

extern "C" __declspec( dllexport ) UINT32 GetNumberOfModules()
{
	// this is required to link us into a load of MFC stuff
	new CDynLinkLibrary(extensionDLL);

	return 1;
}
#endif

static char Name[] 		= "Push Module";
static char Purpose[] 	= "To do push type stuff";
static char Author[] 	= "Mr DLL Pennell";

class PushModule : public Module_v1
{
public:
	// Initialise the module
	virtual BOOL Init();
	
	// What version of the Module interface does this module understand?
	virtual UINT32 GetInterfaceVersion() { return 1; } ;
	
	// What version of the Module info class does this module understand?
	virtual UINT32 GetInfoVersion() { return 1; };
	
	// Get info on the Module.
	virtual void Describe(void* Info);
	
	// Create an instance of a given tool.
	virtual void *CreateTool(UINT32 ToolID);

};

BOOL PushModule::Init()
{
	return TRUE;
}

void PushModule::Describe(void* Info)
{
	// Cast the pointer into one we understand...
	
	ModInfo_v1 *ModInfo = (ModInfo_v1 *) Info;
	
	// ...and fill in the fields
	
	ModInfo->InfoVersion = 1;
	ModInfo->InterfaceVersion = GetInterfaceVersion();
	ModInfo->Version = 1;
	ModInfo->ID = MODULEID_PUSH;
	ModInfo->NumTools = 13;
	ModInfo->Name = Name;
	ModInfo->Purpose = Purpose;
	ModInfo->Author = Author;
}
	


void *PushModule::CreateTool(UINT32 Type)
{
	if (Type==1)
		return NULL; //new ZoomTool;

	if (Type==2)
		return new PushTool;

	if (Type==3)
		return NULL; //new FreeHandTool;

	if (Type==4)
		return new PenTool;

	if (Type==5)
		return NULL; //new BlendTool;

	if (Type==6)
		return new BezierTool;

	if (Type==7)
		return new GradFillTool;

	if (Type==8)
		return new TranspTool;

	if (Type==9)
		return new GridTool;

	if (Type==10)
		return new RectangleTool;

	if (Type==11)
		return new QuickShapeTool;

	if (Type==12)
		return new MouldTool;

	if (Type==13)
		return new BlankTool;

	return NULL;
}			



#if 0
extern "C" __declspec( dllexport ) Module_v1 *CreateModule(UINT32 which)
{
	return new PushModule();
}

#ifdef _DEBUG
extern "C" __declspec( dllexport ) void IAmADebugTool()
{
}
#endif

#endif

IMPLEMENT_SIMPLE_MODULE_OIL( PushModule )
