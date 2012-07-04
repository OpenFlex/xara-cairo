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

	appstate.h

	Functions to save and restore the program's state between runs.
*/

#ifndef APPSTATE_H
#define APPSTATE_H

// Initialises the app-state system.
BOOL InitAppState();

// These save and restore the open documents and views onto those documents.
BOOL SaveAppWindowState(BOOL fAutoRestart);
BOOL LoadAppWindowState(wxWindow *pSplashBox);

// Publicy declare this pref value so that InitInstance can override it on /Restore.
extern BOOL fRestoreWorkspaceOnStartup;

#endif	// !APPSTATE_H
