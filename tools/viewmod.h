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


#ifndef INC_VIEWMOD
#define INC_VIEWMOD

#include "module.h"

class ViewModule : public Module_v1
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

#endif // INC_VIEWMOD
