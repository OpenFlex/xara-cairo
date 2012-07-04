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


#ifndef INC_OILPREFS
#define INC_OILPREFS

//#include "prefs.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class OILPreferences : public wxConfig

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/93
	Purpose:	This class, like the Preferences class, is only ever instantiated once.
				It is a collection of routines to be used to handle the OIL side of reading
				and writing preferences.
				This class is used internally by the Preferences class - no other class
				should need to use it.
	SeeAlso:	Preferences

********************************************************************************************/


class OILPreferences : public wxConfig
{
public:
	// Class factory/Initialise an OILPreferences object
	static OILPreferences* Init();

	// Constructor (I wish I didn't have to duplicate this here but don't know any way
	// to avoid it)
	OILPreferences( const wxString& appName = wxEmptyString,
					const wxString& vendorName = wxEmptyString,
					const wxString& localFilename = wxEmptyString,
					const wxString& globalFilename = wxEmptyString,
					long /*TYPENOTE: Correct*/ style = 0, wxMBConv& conv = wxConvUTF8)
		: wxConfig(appName, vendorName, localFilename, globalFilename, style, conv) {;}

	// Write a preference
	void Write(LPTCHAR Section, LPTCHAR PrefName, PreferenceType Type, PrefData pData);
		
	// Read a preference
	void Read(LPTCHAR Section, LPTCHAR PrefName, PreferenceType Type, PrefData pData);

	// Perform any platform-dependent initialisation/cleanup needed for reading preferences
	BOOL OpenInput();
	BOOL CloseInput();

	// Perform any platform-dependent initialisation/cleanup needed for saving preferences
	BOOL OpenOutput();
	BOOL CloseOutput();
	
	// Clear all entries in a preference file
	void WipePreferenceFile();
	void WipeDangerousPrefs();

};

#endif
