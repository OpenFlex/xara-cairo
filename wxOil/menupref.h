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
 * */         
         
#ifndef INC_MENUPREF
#define INC_MENUPREF      

#include "oilfiles.h"
#include "menuitem.h"

// Get Menu Preferences;

MenuItem *GetMenuPreferences(UINT32 ResourceID);

MenuItem *CreateMenuItem(TCHAR *OpToken, UINT32 ParentId, BOOL Separator);

// Parser Routines

void ClearArray(TCHAR buffer[], INT32 size);

BOOL GetKeyword(CCResTextFile* pResScript, TCHAR keyword[], INT32 size);
                                                 
BOOL GetToken(CCResTextFile* pResScript, TCHAR OpToken[], INT32 TokenSize); 

BOOL GetSeparator(	CCResTextFile* pMenuScript, 
					const String& separator_sym, 
					TCHAR SepKeyword[], 
					INT32 size
				 );

// Identifier of the Window Menu

extern UINT32 WindowMenuID;       

#endif
