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


// OIL specific Module support routines supplied for the Kernel

/********************************************************************************************

>	class OILModule

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Purpose:	This class hides the mechanism of loading modules via whatever OS calls
				are required.  For example, under Windows it loads DLLs and interrogates
				them, whereas on the Arc something quite different could happen.
				It also provides a link between a kernel 'Module' item and the OIL
				transport mechanism used to load it.

********************************************************************************************/

class OILModule
{
public:
	OILModule();
	HINSTANCE GetInstance();
	
	static BOOL Init();
	static void Deinit();
	static void DeinitExtras();
	static HINSTANCE GetInstance(UINT32 ModuleID);

private:
#ifdef _AFXDLL
	static void EnumerateModulesFromDLL(const char *Filename);
#endif
	HINSTANCE hInstance;
};

// The following is unfortunately required in this header file (see winoil\killdlls.cpp).

const UINT32 MAX_DLLS = 10;

extern HINSTANCE DLLs[MAX_DLLS];

extern UINT32 DLLCount;

// these are indices into the ExtraDLLs array below and are so we can close any
// dynamically bound DLLs at exit time. They are zero if no DLL loaded.
enum ExtraDLLenum
{
	GDI_Util_DLL = 0,
	Ctl3d_DLL,
	Slider_Control_DLL,
	BitmapButton_Control_DLL,
	TabBox_Control_DLL,
	CheckList_Control_DLL,
	DDeck_Control_DLL,
	Grid_Control_DLL,
	Text3d_Control_DLL,
	Redraw_Control_DLL,
	WinG_DLL,
	ATM_Util_DLL,
	Resources_DLL,
	// more here
	Extra_DLL_Count
};

extern HINSTANCE ExtraDLLs[Extra_DLL_Count];

	
