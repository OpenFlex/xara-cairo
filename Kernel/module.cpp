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

#include "oilmods.h"
#include "module.h"
#include "modlist.h"
//#include "viewrc.h"

#include "zoomtool.h"
//#include "pushtool.h"



ModuleList *Module::Modules = NULL;


CC_IMPLEMENT_MEMDUMP(ModInfo_v1, CCObject)
CC_IMPLEMENT_MEMDUMP(ModInfo, ModInfo_v1)
CC_IMPLEMENT_MEMDUMP(Module_v1, CCObject)
CC_IMPLEMENT_MEMDUMP(Module, Module_v1)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	void Module::InitModules()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if OK, FALSE for catastrophic failure
	Purpose:	Called at the end of initialisation (as it may well need all other 
				initialisations to have been done) to add Tools and Modules to the Kernel's
				knowledgebase.
	Errors:		None
	Scope:		Public

********************************************************************************************/

BOOL Module::InitModules()
{
	// Initialise the list of Modules.
	Modules = new ModuleList;
	if (!Modules)
		return FALSE;
		
	if (!OILModule::Init())						// get OIL's list of modules. This works
		return FALSE;							// by calling back to DescribeModule.
												// NB. OILModule::Init does it own error
	BOOL Finished;								// reporting
	
	do
	{
		// All the modules have been 'new'ed now. We can now ask them to initialise themselves.
		// If they don't want to, they get 'delete'ed.

		ModuleListItem *Item = (ModuleListItem *) Modules->GetHead();
		
		Finished = TRUE;
		
		while (Item != NULL)
		{
			Module *Module = Item->m_pModule;
			
			// If this module exists and has not been initialised yet, then try to
			// initialise it.  If it initialises ok, set the item's flag, and force
			// another scan of the remaining modules in case one of them depends on
			// this module being present.
			if ((Module != NULL) && (!Item->m_Initialised) && (Module->Init()))
			{
				Item->m_Initialised = TRUE;	// Tool initialised ok.
				Finished = FALSE;			// At least one more loop to try
			}

			// Try the next module
			Item = (ModuleListItem *) Modules->GetNext(Item);
		}
		
	} while (!Finished);

	// Delete any un-initialised modules
	ModuleListItem *Item = (ModuleListItem *) Modules->GetHead();

	while (Item != NULL)
	{
		if ((Item->m_pModule != NULL) && (!Item->m_Initialised))
		{
			delete Item->m_pModule;
			Item->m_pModule = NULL;
		}

		// Try the next module
		Item = (ModuleListItem *) Modules->GetNext(Item);
	}

	// Scan all the modules and create (but do not initialise) any tools they provide.
	if (!Tool::InitToolList() || !CreateTools())
		return FALSE;

	return TRUE;
}


/********************************************************************************************

>	ModuleListItem *Module::Declare(Module *NewModule)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/6/93
	Inputs:		NewModule - pointer to a new Tool and its ID
				pOILModule - pointer to the OILModule object to be associated with this
				module.
	Outputs:	None
	Returns:	Pointer to new module list item if module.
	Purpose:	Called by OIL code to declare new modules.
	Errors:		Will return NULL if invalid ID or same module ID used twice, and NewModule
				will have been deleted.

********************************************************************************************/

ModuleListItem *Module::Declare(Module *NewModule, OILModule *pOILModule)
{
	// Try to add the module to the kernel's list.
	ModuleListItem *NewItem = Modules->Add(NewModule, pOILModule);
	
	if (NewItem == NULL)
	{
		// Either out of memory or Module has invalid ID - print error message and 
		// destroy module.
		#ifdef _DEBUG
		ModInfo Info;
		NewModule->Describe(&Info);
		TRACE( _T("Module %u is invalid or has no memory to initialise with.\n"), Info.ID );
		#endif
		
		delete NewModule;
	}
	
	return NewItem;
}


/********************************************************************************************

>	ModuleListItem *Module::Find(UINT32 ModuleID)

	Author: 	Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Inputs:		Module ID
	Outputs:	None
	Returns:	Pointer to list item of the required module, or NULL if not found.
	Purpose:	Anyone can ask about a module's presence by its ID.
	Errors:		None.

********************************************************************************************/

ModuleListItem *Module::Find(UINT32 ModuleID)
{
	// Simple search of list for ID
	
	ModuleListItem *Item = (ModuleListItem *) Modules->GetHead();
	
	while (Item != NULL)
	{
		if (Item->m_ModInfo.ID == ModuleID)
			// Found ID - return pointer to this list item.
			return Item;
		
		Item = (ModuleListItem *) Modules->GetNext(Item);
	}
	
	// Not found
	return NULL;
}

/********************************************************************************************

>	void Module::DeinitModules()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/6/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Deletes all allocated modules (and hence tools), then asks OIL to tidy up. 
				Safe to call more than once.
				
				Do NOT try to use any tools or modules after calling this.
				
	Errors:		None

********************************************************************************************/

void Module::DeinitModules()
{
	if (Modules != NULL)
	{
		// Delete the list itself.
		delete Modules;
		Modules = NULL;

		// Perform any clean-up required by the OIL layer.
PORTNOTE("other","Removed OILModule usage")
#ifndef EXCLUDE_FROM_XARALX
		OILModule::Deinit();
#endif
	}
}

/********************************************************************************************

>	BOOL Module::CreateTools()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/7/93
	Inputs:		-
	Outputs:	-
	Returns:	TRUE => Tools created OK.
	Purpose:	Scan all modules known to the kernel, and try to create an instance of each
				tool they contain, and add this tool to the kernel's list.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL Module::CreateTools()
{
	// Scan the list of modules
	ModuleListItem *Item = (ModuleListItem *) Modules->GetHead();
	
	while (Item != NULL)
	{
		// Interrogate module
		ModInfo Info;
		Item->m_pModule->Describe(&Info);

		// Try to create an instance of each tool in this module
		for (unsigned tool = 1; tool <= Info.NumTools; tool++)
		{
			Tool *NewTool = (Tool *) Item->m_pModule->CreateTool(tool);
			
			if (NewTool != NULL)
			{
				// Tool was created - add it to the list
				Tool::Declare(NewTool, Info.ID);
				
 			}
		}

		// Try the next module in the list.		
		Item = (ModuleListItem *) Modules->GetNext(Item);
	}
//	Tool* NewTool ;
//	NewTool = (Tool*)new ZoomTool; if ( NewTool ) Tool::Declare(NewTool,1);
//	NewTool = (Tool*)new PushTool; if ( NewTool ) Tool::Declare(NewTool,Info.ID);

	// No error codes yet
	return TRUE;
}



// Empty functions for the default module.

/********************************************************************************************

>	BOOL Module_v1::Init()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/6/93
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if OK, FALSE if module doesn't want to initialise.
	Purpose:	Called after module's constructor to ask it whether it wants to exist or
				not. Each module is asked in two passes, so that its existence can depend
				on another module. If a module does not want to exist, it should return FALSE,
				whereupon it will be deleted.
	Errors:		None

********************************************************************************************/


BOOL Module_v1::Init()
{
	return FALSE; 					// Should never try to instantiate a module base class
}


/********************************************************************************************

>	Module_v1::~Module_v1()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/7/93
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroys the module, performing any cleanup necessary.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

Module_v1::~Module_v1()
{
	// Null destructor
}

/********************************************************************************************

>	BOOL Module_v1::Describe(void *Infoptr)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/6/93
	Inputs:		Pointer to area to recieve info
	Outputs:	Info area is updated
	Returns:	None
	Purpose:	Asks a module for more information. The pointer points to a struct such as
				ModInfo_v1 which the module should fill in. All fields should be filled
				(NULL is OK for char* variables). The type of the pointer is not explicitly
				defined so the structure can evolve while keeping backward compatibility.
	Errors:		None

********************************************************************************************/

void Module_v1::Describe(void *InfoPtr)
{
	// Cast structure into the latest one we understand.
	ModInfo_v1 *Info = (ModInfo_v1 *) InfoPtr;
	
	Info->InterfaceVersion = GetInterfaceVersion();  	// You should always have this line.
	
	// These are all garbage as we should never try to create one of these...
	Info->Version = 1;
	Info->ID = MODULEID_INVALID;						// so we never get instantiated
	Info->NumTools = 0;
	Info->Name = Info->Purpose = Info->Author = NULL;
}

/********************************************************************************************

>	void *Module_v1::CreateTool(UINT32 ToolNumber)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Inputs:		ToolNumber - The number of the tool to create (1 to NumTools)
	Outputs:	-
	Returns:	Pointer to the new instantiation of the desired tool.
	Purpose:	Provide a clean interface from module to kernel code for the creation
				of tools.
	Errors:		-

********************************************************************************************/

void *Module_v1::CreateTool(UINT32)
{
	return NULL; // Should never call this for the base class
}




