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


// MenuPref.cpp - This module is responsible for parsing a menu script and generating
// a set of Camelot Menus.


#include "camtypes.h"
#include "menuitem.h"
#include "menucmds.h"
#include "menupref.h"
#include "menuops.h"
//#include "opdesc.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "errors.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ensure.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "mario.h"
#include "oilfiles.h"

DECLARE_SOURCE("$Revision: 1550 $");  

// We want better memory tracking
#define new CAM_DEBUG_NEW

MenuItem* CreateMenuItem(TCHAR *OpToken, UINT32 ParentId, BOOL Separator);

UINT32 WindowMenuID;       


/********************************************************************************************

>	inline void ClearArray(TCHAR buffer[], INT32 size);

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/8/93
	Inputs:		Char Array
				Integer - Array Size
	Outputs:	-
	Returns:	-
	Purpose:	Initialises a Character Array with Nulls
	Errors:		-

********************************************************************************************/

inline void ClearArray(TCHAR buffer[], INT32 size)
{
	::memset(buffer, 0, size * sizeof(buffer[0]));
}



/********************************************************************************************

>	MenuItem *GetMenuPreferences(UINT32 ResourceID)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/8/93
	Inputs:		ResourceID representing the menu resource to be loaded.
	Outputs:	-
	Returns:	A MenuItem representing the default Menu that was parsed in or NULL if failed
				(SetError will be called)
	Purpose:	Parses a Menu Script representing the Camelot Default Menus. 
	Errors:		-
	SeeAlse:	GetToken();
	SeeAlso:	GetKeyword();
	SeeAlso:	GetSeparator();

********************************************************************************************/

MenuItem *GetMenuPreferences(UINT32 ResourceID)
{                              
	// Keyword Buffer
	const INT32 keywordSize 	= 10;
	TCHAR keyword[keywordSize];

	// Token Buffer
	const INT32 TokenSize 	= 30;
	TCHAR OpToken[TokenSize];

	// Lexical Tokens
	const String_256 menu_sym 		= "MENU";
	const String_256 submenu_sym 	= "SUBMENU";
	const String_256 menuitem_sym 	= "MENUITEM";
	const String_256 end_sym 		= "END";
	const String_256 separator_sym	= "SEPARATOR";
	
	CCResTextFile MenuScript;	// Resource File
                                                
	// Open Resource File                                                
    MenuScript.open(ResourceID, _R(IDT_CAM_MENU_RES));

    // Stack of all the Menus and SubMenus currently in Scope!             
    List MenuStack;
    
    MenuItem* 		pCurMenu = NULL; 	// Menu Currently in Scope

    MenuItem* 		pMenu = NULL; 
    MenuItem* 		pSubMenu; 
    MenuItem* 		pMenuItem; 
    
   	while ((MenuScript.isOpen()) && (!MenuScript.eof()))
    {
		ClearArray(keyword, keywordSize);

		//Get The Keyword
		if (GetKeyword(&MenuScript, keyword, keywordSize))
		{
        // MENU reserved word
			if (menu_sym == keyword)				
			{
				ERRORIF((!GetToken(&MenuScript, OpToken, TokenSize)), 
						_R(IDE_SYNTAX_ERROR), 
						NULL);
				
				pMenu = new MenuItem(OpToken);

				if (pMenu==NULL)
				{
					TRACEALL( _T("GetMenuPrefs: failed to allocate MenuItem"));
					break;											// willeventually return NULL
				}
			    
				pCurMenu = pMenu;
			}
			// SUBMENU reserved word
			else if (submenu_sym == keyword)
			{                                       
				ERRORIF((!GetToken(&MenuScript, OpToken, TokenSize)), 
						_R(IDE_SYNTAX_ERROR), 
						NULL);

				TRACEUSER( "luke", _T("SUBMENU \"%s\" \"%s\"\n"), OpToken, OPTOKEN_DEBUG_MENU );

#if !defined(_DEBUG)
				// Remove DEBUG menu
				if( 0 == camStrcmp( OpToken, OPTOKEN_DEBUG_MENU ) )
				{
					TRACEUSER( "luke", _T(">-SUBMENU %s\n"), OPTOKEN_DEBUG_MENU );
					MenuStack.AddHead(pCurMenu);	//Push Current Menu onto stack
					pCurMenu = NULL;
					continue;
				}
#endif

				pSubMenu = CreateMenuItem(	OpToken, 
											pCurMenu->GetMenuId(),
											GetSeparator(	&MenuScript, 
															separator_sym, 
															keyword,
															keywordSize)
										 );

				// stop now if run out of memory
				if (pSubMenu==NULL)
					break;

				// Get the ID for the Window Menu
				if (String(OpToken) == String(OPTOKEN_WINDOW_MENU))
					//MenuItem ID must be first sub element of menu because in windows 
					//menus do not have IDs
					WindowMenuID = ((pSubMenu->GetMenuId()) + 1);
				
				pCurMenu->AddMenuItem(pSubMenu);
				MenuStack.AddHead(pCurMenu);	//Push Current Menu onto stack
				pCurMenu = pSubMenu;
			}
			// MENUITEM reserved word
			else if (menuitem_sym == keyword)
			{
				ERRORIF((!GetToken(&MenuScript, OpToken, TokenSize)), 
						_R(IDE_SYNTAX_ERROR), 
						NULL);

#if !defined(_DEBUG)
				// Don't add menu itemns if parent not wanted
				if( NULL == pCurMenu )
					continue;
#endif

				pMenuItem = CreateMenuItem(	OpToken,
											pCurMenu->GetMenuId(),
											GetSeparator(	&MenuScript, 
															separator_sym, 
															keyword,
															keywordSize)
										  );
				
           		if (pMenuItem != NULL)
           			pCurMenu->AddMenuItem(pMenuItem);
				else
					break;

			}
			// END reserved word
			else if (end_sym == keyword)
			{                                       // Pop Menu from stack
				pCurMenu = (MenuItem*) MenuStack.RemoveHead();
				// WEBSTER - markn 22/1/97
				// Stops circular menu lists being generated when the last main menu item
				// contains a sub menu (thank you mario)
				if (pCurMenu != NULL)
					pCurMenu->ClearPointers();
			}
		}

	}                                        
		
    MenuScript.close();
    
	return pMenu;	
}

/********************************************************************************************

>	MenuItem *CreateMenuItem(TCHAR *OpToken, UINT32 ParentId, BOOL Separator)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/9/93
	Inputs:		OpToken used to get the appropriate operation
				Parent Identifier
				Separator Boolean 
	Returns:	MenuItem if created ok else NULL
	Purpose:	Creates a MenuItem given an Optoken.

********************************************************************************************/

MenuItem *CreateMenuItem(TCHAR *OpToken, UINT32 ParentId, BOOL Separator)
{
	OpDescriptor *Operation = OpDescriptor::FindOpDescriptor(OpToken);

PORTNOTE( "other", "Use DO_NOTHING op for menuitem, if optoken not found" );
#if defined(EXCLUDE_FROM_XARALX)
	if( NULL == Operation )
		Operation = OpDescriptor::FindOpDescriptor( OPTOKEN_DO_NOTHING );
#endif
	
	if (!Operation)
	{
		String_256 ErrorMsg(_R(IDE_OPNOTFOUND));
		ErrorMsg += OpToken;	

 		Error::SetError(_R(IDE_OPNOTFOUND), ErrorMsg, 0);
		InformError();

    	return NULL;
    }
    else	
	{
	    MenuItem *pMenuItem;
	
		// Create an instance of a MenuItem
		pMenuItem = new MenuItem(	ParentId,
									Operation,
									Separator
								);
    
		ERROR3IF( pMenuItem==NULL, "CreateMenuItem failed" );
		
		return pMenuItem;
    }
}

/********************************************************************************************

>	BOOL GetKeyword(CCResTextFile *pResScript, TCHAR keyword[], INT32 size)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/8/93
	Inputs:		Input Stream - Menu Script
				Integer - Maximum size of keyword
	Outputs:	Char Array - The Keyword
	Returns:	TRUE if Keyword is found
				FALSE otherwize
	Purpose:	Parses a Menu Script Keyword.
	Errors:		-

********************************************************************************************/

BOOL GetKeyword(CCResTextFile *pResScript, TCHAR keyword[], INT32 size)
{
	// Get Keyword
	TCHAR ch; 
	INT32 i = 0;			
    
	ClearArray(keyword, size);

    pResScript->read(ch);
    
	// if not a keyword return false!
    if (!String::IsAlpha(ch) && (!pResScript->eof()))
		return FALSE;	
	   
	while (String::IsAlpha(ch) && !pResScript->eof() && i < size)
	{
		keyword[i++] = ch;
	    pResScript->read(ch);
	}           

	if (!pResScript->eof())	
		return TRUE;
	else
	{
//		TRACEUSER( "JustinF", _T("Menu GetKeyword() - read %s\n"), keyword);
		return FALSE;	
	}
}           

/********************************************************************************************

>	BOOL GetToken(CCResTextFile *pMenuScript, TCHAR OpToken[], INT32 TokenSize) 

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/8/93
	Inputs:		Input Stream - Menu Script
				Integer - Maximum size of Token
	Outputs:	Char Array - The Token
	Returns:	TRUE if Token is found
				FALSE otherwize
	Purpose:	Parses a Menu Script Token.
	Errors:		-

********************************************************************************************/

BOOL GetToken(CCResTextFile *pMenuScript, TCHAR OpToken[], INT32 TokenSize) 
{        
	// Get Keyword
	TCHAR ch;
	INT32 i = 0;			

	ClearArray(OpToken, TokenSize);

	//Go back one place and reread last character.
	pMenuScript->seek((pMenuScript->tell() - 1));
    pMenuScript->read(ch);
	 
	while (StringBase::IsSpace(ch) && !pMenuScript->eof())
		pMenuScript->read(ch);
		
	if (ch == TEXT('"'))
	    pMenuScript->read(ch);
	else
	{
//		TRACEUSER( "JustinF", _T("Menu GetToken() - no opening \"\n"));
		pMenuScript->close();
		return FALSE;	
	}

	while ((String::IsAlphaNumeric(ch) || (ch == _T('_'))) &&
		   ch != TEXT('"') &&
		   !pMenuScript->eof() &&
		   i < TokenSize)
	{
		OpToken[i++] = ch;
	    pMenuScript->read(ch);
	}           
	
	if (ch == TEXT('"') && !pMenuScript->eof())
		return TRUE;
	else
	{
//		TRACEUSER( "JustinF", _T("Menu GetToken() - read %s\n"), OpToken);
		pMenuScript->close();
		return FALSE;	
	}
}

/********************************************************************************************

>	BOOL GetSeparator(	CCResTextFile *pMenuScript, 
						const String& separator_sym, 
						TCHAR SepKeyword[], 
						INT32 size) 

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/8/93
	Inputs:		Input Stream - Menu Script
				constant String - Separator Symbol
				Char Array - Keyword Array  
				Integer - size of Symbol
	Outputs:	-
	Returns:	TRUE if Separator is found
				FALSE otherwize
	Purpose:	Parses a Menu Script Menu Separator Token.
	Errors:		-

********************************************************************************************/

BOOL GetSeparator(	CCResTextFile *pMenuScript, 
					const String& separator_sym, 
					TCHAR SepKeyword[], 
					INT32 size) 
{        
	// Get Keyword
	TCHAR ch;
	INT32 i = 0;			

	ClearArray(SepKeyword, size);
	
	//Go back one place and reread last character.
	pMenuScript->seek((pMenuScript->tell() - 1));
    pMenuScript->read(ch);
    
	//Find First Alpha Numeric Character
	while(!String::IsAlpha(ch) && (!pMenuScript->eof()) && (ch != '\n'))
	    pMenuScript->read(ch);

	//Read in the keyword until not Alpha Numeric
	while (String::IsAlpha(ch) && (!pMenuScript->eof()) && (i < size))
	{
		SepKeyword[i++] = ch;
	    pMenuScript->read(ch);
	}           

	if (separator_sym == SepKeyword)
		return TRUE;
	else
	{
//		TRACEUSER( "JustinF", _T("Menu GetSeparator() - read %s\n"), SepKeyword);
		return FALSE;
	}
}
