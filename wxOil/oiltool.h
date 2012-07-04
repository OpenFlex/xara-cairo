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


#ifndef INC_OILTOOL
#define INC_OILTOOL

// The range of 'public' resource IDs of the kernel.
// i.e. the resources in the Camelot kernel that any tool can access if they ask nicely.
#define KID_FIRST (0x6000)
#define KID_LAST  (0x6FFF)


class CCAPI OILTool
{
public:
	OILTool(UINT32 ModuleID);
	
	// Access to a tool's resources.
	// (Or kernel's if the ID is in the kernel ID range).
	HCURSOR LoadCursor(UINT32 ID);
	HBITMAP LoadBitmap(UINT32 ID);
	HICON	LoadIcon(UINT32 ID);
	BOOL	LoadString(UINT32 ID, char*);
	
	// Instance handle of the DLL for the Tool associated with this OilTool.
	HINSTANCE hInstance;
};

#endif // INC_OILTOOL
