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

	helpuser.h

	Routines for running the user help system.
*/

#ifndef HELPUSER_H
#define HELPUSER_H

// Forward references.
class DialogOp;
class CDialog;
class OpDescriptor;

// These overloaded functions are passed various Camelot objects to provide user help on.
// Each version knows how to associate a help topic index with the given object.
BOOL HelpUser(const DialogOp& dlgop);
BOOL HelpUser(const wxDialog& dlg);
BOOL HelpUser(const OpDescriptor& opdesc);
BOOL HelpUser(UINT32 nMessageID);
BOOL HelpUserPropertyPage(UINT32 PageID);
BOOL HelpUserTopic(DWORD dwHelpIndex);

// Unfortunately, there are a few cases where it isn't possible to associate an object type
// with a help topic, such as the Print Setup dialog.  We use this bodgy "direct-access"
// function for those tricky cases.
BOOL _HelpUser(LPCTSTR lpcszClassName, UINT32 nSubTopic = 0);

// These functions run the help system and display the appropriate topic.
BOOL HelpContents();
BOOL HelpUsingHelp();
BOOL HelpUsingTools();
BOOL HelpUsingGalleries();
BOOL HelpOnlineDemos();
BOOL HelpTechnicalSupport();

// This displays the special Xara Studio info helpfile in the viewer build.
#ifdef STANDALONE
BOOL ShowHelpSpec();
#endif

// This function determines if help is available to the user for the given message.
BOOL CanHelpUser(UINT32 nMessageID);

// This is a "bodgy" function called by the String class MakeMsg function.  Many error
// and warning boxes require parameter substitution in their message strings.  This
// function records the help context of the last string resource passed to MakeMsg,
// usually this will be the key for context-sensitive help.
void SetNextMsgHelpContext(UINT32 nMessageID);
// Andy Hills, 22-11-00
// We also need a 'get' function for a 'bodge-on-top-of-a-bodge'
UINT32 GetNextMsgHelpContext();

// These are called on program startup and shutdown.  You can leave 'em alone, otherwise.
BOOL InitUserHelp();
BOOL DeInitUserHelp();

#endif	// !HELPUSER_H
