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



#ifndef INC_MODULE
#define INC_MODULE


class OILModule; 		// #include "oilmods.h"
class ModuleList; 		// #include "modlist.h"
class ModuleListItem;	// #include "modlist.h"


/********************************************************************************************

>	class ModInfo_v1 : public SimpleCCObject

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Purpose:	Holds details of a Module.  See ModInfo for details.
	SeeAlso:	ModInfo

********************************************************************************************/


class CCAPI ModInfo_v1 : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(ModInfo_v1);

public:
	UINT32	InfoVersion; // Determines how many of the fields are filled in
	UINT32	InterfaceVersion;
	UINT32	Version;
	UINT32	ID;
	UINT32	NumTools;
	char*	Name;
	char*	Purpose;
	char*	Author;
};

/********************************************************************************************

>	class ModInfo : public ModInfo_v1

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Purpose:	Holds details about a module.  This class will always be derived from the
				latest version of the ModInfo_vnn class.  Having this class means that the
				source only needs to be changed in one place when the ModInfo spec changes.
				
				The members are as follows:
				
				InterfaceVersion: The version of Module_vnn that the module is derived from,
				and hence which parts of the module interface are understood by the mdoule.
				
				Version: Version number of this particular module.
				
				ID: The unique ID of this module - these are allocated centrally by
				Computer Concepts.
				
				NumTools: The number of tools provided by this module.
				
				Name: Text string containing the name of the module (e.g. "View")
				
				Purpose: Text string describing the purpose of the module.
				
				Author: Text string containing the author(s) of the module.
				
	SeeAlso:	ModInfo_v1; Module

********************************************************************************************/


class CCAPI ModInfo : public ModInfo_v1
{
	CC_DECLARE_MEMDUMP(ModInfo);
	// No extra members needed.
};

/********************************************************************************************

>	class Module_v1 : public SimpleCCObject

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/93
	Purpose:	Module interface definition. See Module for details.
	SeeAlso:	Module

********************************************************************************************/


class CCAPI Module_v1 : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(Module_v1);

public:
	virtual ~Module_v1();
	
	// Initialise the module
	virtual BOOL Init();
	
	// What version of the Module interface does this module understand?
	virtual UINT32 GetInterfaceVersion() { return 1; } ;
	
	// Get info on the Module.
	virtual void Describe(void* Info);
	
	// Create an instance of a given tool.
	virtual void *CreateTool(UINT32 ToolID);
};

// Each module needs a valid Module ID. They get allocated here. Funnily enough
// they look remarkably similar to Tool IDs, but thats just for convenience, they
// dont have to be

const UINT32	MODULEID_INVALID	=	0;
const UINT32	MODULEID_KERNEL		=	1;

const UINT32	MODULEID_PUSH		=	3;
const UINT32	MODULEID_ZOOM		=	4;

const UINT32	MODULEID_FREEHAND	=	6;

const UINT32	MODULEID_GRID		=	10;
const UINT32	MODULEID_BEZTOOL	=	11;

const UINT32	MODULEID_GRADFILL	=	13;
const UINT32	MODULEID_PEN		=	14;

const UINT32	MODULEID_BLEND		=	16;
const UINT32	MODULEID_TRANSP		=	17;
const UINT32	MODULEID_REGSHAPE	=	18;
const UINT32	MODULEID_MOULD		=	19;
const UINT32	MODULEID_ACCUSOFT	=	20;

const UINT32	MODULEID_TEST		=	42;




/********************************************************************************************

>	class Module : public Module_v1

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Purpose:	The Module type reflects the latest Module specification. Do NOT subclass
				from Module, but use the latest Module revision (e.g. Module_v42).
				The Module type should only be used by the Kernel and OIL layers, never by
				Modules themselves.
				
				The modules known to the kernel are contained in the Modules object, which
				is pointer to an instance of the class ModuleList.  This class should be
				used to declare/search for modules, etc.

	SeeAlso:	Module_v1; ModuleList; ModuleListItem; Tool

********************************************************************************************/

// This should always inherit from the most modern definition of the Module_vnn class

class CCAPI Module : public Module_v1
{
	CC_DECLARE_MEMDUMP(Module);
	
public:

	static BOOL InitModules();
	static void DeinitModules();
	static ModuleListItem *Find(UINT32 ModuleID);
	static ModuleListItem *Declare(Module *, OILModule *);

private:
	static ModuleList *Modules;
	
	static BOOL CreateTools();
};

#endif		// INC_MODULE
