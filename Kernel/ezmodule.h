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


// macros making it easy to declare a Module containing a single Tool
// this is a Kernel file. The OIL equivalent is in ezmodoil.h

#ifndef INC_EZMODULE
#define	INC_EZMODULE

#include "module.h"
//#include "ezmodoil.h"


/*********************************************************************************************

< IMPLEMENT_SIMPLE_MODULE( ModName, ModID, ToolName, name, purpose, author )

	Comment:	This is a macro which expands to a whole load of things in DLL builds,
				or nothing in nonDLL builds. It is an easy way to define a module that
				uses only one tool.

**********************************************************************************************/ 


#if TOOLS_SEPARATE


#define	IMPLEMENT_SIMPLE_MODULE( ModName, ModID, ToolName, name, purpose, author ) \
\
class ModName : public Module_v1							\
{															\
public:														\
	BOOL Init() { return TRUE; };							\
	UINT32 GetInterfaceVersion() { return 1; } ;				\
	UINT32 GetInfoVersion() { return 1; };					\
	void Describe(void* Info);								\
	void *CreateTool(UINT32 Type);							\
};															\
void ModName::Describe(void* Info)							\
{															\
	ModInfo_v1 *ModInfo = (ModInfo_v1 *) Info;				\
	ModInfo->InfoVersion = 1;								\
	ModInfo->InterfaceVersion = GetInterfaceVersion();		\
	ModInfo->Version = 1;									\
	ModInfo->ID = ModID;									\
	ModInfo->NumTools = 1;									\
	ModInfo->Name = name;									\
	ModInfo->Purpose = purpose;								\
	ModInfo->Author = author;								\
}															\
void *ModName::CreateTool(UINT32 Type) { return (Type==1) ? new ToolName : NULL; }	\
IMPLEMENT_SIMPLE_MODULE_OIL( ModName )

#else

#define	IMPLEMENT_SIMPLE_MODULE( ModName, ModID, ToolName, name, purpose, author )

#endif

#endif
