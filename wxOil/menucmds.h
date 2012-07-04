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

/********************************************************************************************

< Menu Commands
< OIL Menus

COMMENT:

\b MENUCMDS Module \b0

The MenuCmds (Menu Commands) module encapsulates all of the global functions used to 
implement the menu actions and menu updates of the Camelot dynamic menu system.

SeeAlso: 	OilMenus
 
********************************************************************************************/


#ifndef INC_MENUCMDS
#define INC_MENUCMDS 
                    
#include "menuitem.h"
                    
void ExitAction(); 

void FileNewAction(); 
void FileNewAnimationAction(); 
void FileNewTemplateAction(INT32 iNumberOfTemplate); 
void FileOpenAction(); 
void FileCloseAction(); 
void FileSaveAction(); 
void FileSaveAsAction();
void FileSaveAllAction();
//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER
void PrintAction(); 
void PrintSetupAction(); 
#endif //webster
void PrintPreviewAction();

void ViewToolBarAction();
void ViewStatusBarAction();
void ViewColourBarAction();
void ViewFullScreenAction();
void ViewScrollBarsAction();
void ViewRulersAction();

OpState ViewToolBarState();
OpState ViewStatusBarState();
OpState ViewColourBarState();
OpState ViewFullScreenState();
OpState ViewScrollBarsState();
OpState ViewRulersState();

void HelpIndexAction(); 
void HelpUsingAction(); 
void HelpToolsAction();
void HelpGalleriesAction();
void HelpDemosAction();
void HelpPlayerAction();
void HelpDemosNativeAction();
void HelpTechSupportAction();
void HelpXaraPurchasePage();

BOOL IsCDROMOn();
void WebsterDemos();
void WebsterHelpPages();
void HelpXaraForumAction();
void HelpWebsterHomePage();
void HelpXaraHomePage(); 
void SetWebsterReg(BOOL pcData);
BOOL InvokeWeblink(const String_256& command);

#ifdef STANDALONE
void HelpSpecAction(); 
#endif


void WindowNewAction(); 
void WindowArrangeAction(); 
void WindowCascadeAction(); 
void WindowTileHorzAction(); 
void WindowTileVertAction();
void WindowNextDcocument( bool fForward );
OpState WindowCmdState(); 


#endif
