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


// This code handles the interface between the kernel preference system, and 
// the platform's own particular method of storing preferences.


#include "camtypes.h"

//#include "ensure.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "errors.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#include "oilprefs.h"

#include "product.h"	// PRODUCT_OPTIONS_REGISTRYKEY


/********************************************************************************************

>	static OILPreferences* OILPreferences::Init()

	Author:		Luke_Hart & Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/Jun/2006
	Returns:	OILPreferences objects if initialisation succeeded, NULL otherwise.
	Purpose:	Performs any initialisation of the OIL layer preferences mechanisms that
				may fail.

********************************************************************************************/

OILPreferences* OILPreferences::Init()
{
	wxStandardPaths		Paths;
	wxString	strPath( Paths.GetUserConfigDir() );
	strPath += _T("/.xaralx");

	// Delete any file that exists where the directory should be
	if (wxFile::Exists(strPath))
		::wxRemoveFile(strPath);

	// Create directory iff not exist
	if( !wxDir::Exists( strPath ) )
		::wxMkdir( strPath );

	TRACEUSER( "jlh92", _T("OILPreferences::Init %s\n"), PCTSTR(strPath) );

	// Open config storage
	strPath += _T("/preferences");
	OILPreferences* pPrefs = new OILPreferences(_T("xaralx"), _T("Xara"), strPath);

	TRACEUSER( "jlh92", _T("OILPreferences::Init2 %s\n"), PCTSTR(strPath) );
	
	// Return the object we made or a NULL pointer if we failed
	return pPrefs;
}

/********************************************************************************************

>	void OILPreferences::WipePreferenceFile()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/11/93
	Purpose:	Remove all entries from a preference file.  This is done by deleting the
				file and creating a new one.

********************************************************************************************/

void OILPreferences::WipePreferenceFile()
{
	DeleteAll();
}

/********************************************************************************************

>	void OILPreferences::WipeDangerousPrefs()

	Author:		Chris_Gallimore (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/2001
	Purpose:	Remove potentially dangerous entries from the registry.

********************************************************************************************/

void OILPreferences::WipeDangerousPrefs()
{
	// wipe the potentially dangerous settings from the registry
	DeleteGroup(_T("Gallery"));
	DeleteGroup(_T("Options/Templates"));
	DeleteGroup(_T("Options/NewTemplates"));
	
//	DeleteRegKeyAndSubKeys (hAppStateRegKey, PRODUCT_REGISTRYKEY_GALLERY);
//	HKEY optsKey = OpenRegKey(hAppStateRegKey, PRODUCT_REGISTRYKEY_OPTIONS);
//	DeleteRegKeyAndSubKeys (optsKey, TEXT ("Templates"));
//	DeleteRegKeyAndSubKeys (optsKey, TEXT ("NewTemplates"));
//	CloseRegKey (optsKey);
}

/********************************************************************************************

>	void OILPreferences::Write(LPTCHAR Section, LPTCHAR PrefName, PreferenceType Type,
						       PrefData Data)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/93
	Inputs:		Section  - Name of the section to write the preference into.
				PrefName - Name of the preference itself.
				Type     - Type of the preference (INT32, UINT32, etc.)
				Data     - Union holding the pointer to the data to write out to the 
						   preference file.
	Purpose:	This function writes a given preference out to the application's own
				initialisation (profile/preference) file.
	SeeAlso:	OILPreferences; OILPreferences::Read

********************************************************************************************/

void OILPreferences::Write(LPTCHAR Section, LPTCHAR PrefName, PreferenceType Type,
						   PrefData Data)
{
	wxString strKey = _T("/Options/") + wxString(Section) + _T("/") + wxString(PrefName);

	BOOL Worked=FALSE;

	switch (Type)
	{
		case PREF_INT:
		{
			/*TYPENOTE: Correct*/ long l = (long)(*Data.pInt);
			Worked = wxConfig::Write(strKey, l);
			break;
		}
		
		case PREF_UINT:
		{
			// Note that unsigned cast to signed here will appear to store the wrong value
			// in the Config store but this apparent mistake will be rectified when the
			// value is read in and cast back to UINT32 again.
			// (Could write UINT32 prefs as strings...)
			//
			/*TYPENOTE: Correct*/ long l = (long)(*Data.pUInt);
			Worked = wxConfig::Write(strKey, l);
			break;
		}

		case PREF_DOUBLE:
			Worked = wxConfig::Write(strKey, (double)*(Data.pDouble));
			break;
			
		case PREF_STRING:
			Worked = wxConfig::Write(strKey, wxString((TCHAR*)*(Data.pString)));
//			Worked = wxConfig::Write(strKey, *(Data.pString));	// use this form when StringBase derived classes support direct conversion
			break;
			
		default:
			ENSURE(FALSE, "OILPreferences::Write() called with an illegal preference type");
			break;
	}

	if (!Worked)
	{
		ERROR3	("Error saving preference - See trace message for details");
		TRACE( _T("Error saving preference '%s'\n"), PrefName);
	}
}

/********************************************************************************************

>	void OILPreferences::Read(LPTCHAR Section, LPTCHAR PrefName, 
							  PreferenceType Type, PrefData pData)

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/93
	Inputs:		Section  - The name of the preferences section to search.
				PrefName - The name of the preference to search for.
				Type     - The data-type of the preference.
				pData    - Pointer to the location in which to put the value read from the
						   preference file.
				MaxSize  - If the preference is a string, the size of the buffer that pData
						   points to.
	Outputs:	pData - the data pointed to by pData is updated from the preference file (if
						the preference was found - otherwise it is unchanged).
	Returns:	-
	Purpose:	This function attempts to read the given preference in the given section
				from the preference file.  No error is raised if the preference cannot be
				found, because this is a perfectly valid occurence - e.g. when a tool is
				being used for the first time, it has no preferences in the preference
				file.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

/********************************************************************************************

TECHNICAL NOTES

This function does not use the MFC GetProfileString() function becuase this returns a CString
and we're trying to avoid these in Camelot.  It uses the standard SDK function instead.

********************************************************************************************/

void OILPreferences::Read(LPTCHAR Section, LPTCHAR PrefName,
						  PreferenceType Type, PrefData pData)
{
	wxString strKey = _T("/Options/") + wxString(Section) + _T("/") + wxString(PrefName);
	
	switch (Type)
	{
		case PREF_INT:
		{
			// Use the value already in pData->Int as the value to return if the 
			// preference is not found.
			/*TYPENOTE: Correct*/ long l;
			if (wxConfig::Read(strKey, &l))
				*pData.pInt = (INT32)l; // Do not write directly as may be longer than 32 bits
			break;
		}

		case PREF_UINT:
		{
			// Note that signed value is read and cast directly into Unsigned memory
			// allocation reversing the effects fo the cast used in Write above...
			/*TYPENOTE: Correct*/ long l;
			if (wxConfig::Read(strKey, &l))
				*pData.pUInt = (UINT32)l; // Do not write directly as may be longer than 32 bits
			break;
		}
		case PREF_DOUBLE:
		{
			// Get the textual version of the double and convert it to a double.
			// default to null string
			wxConfig::Read(strKey, (double*)(pData.pDouble));
			break;
		}	
		case PREF_STRING:
		{
			// Just get the string - need to ask for the address of the String's
			// text buffer so we can pass it to the SDK profile API.
			wxString str;
			if (wxConfig::Read(strKey, &str))
			{
				str.Truncate(256);
				*(pData.pString) = (LPCTSTR)str;
//				*(pData.pString) = String_256(str);	// use this form when StringBase derived classes support direct conversion
			}
			break;
		}

		default:
			ENSURE(FALSE, "OILPreferences::Read() called with an illegal preference type");
			break;
	}
}

/********************************************************************************************

>	BOOL OILPreferences::OpenInput()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/93
	Returns:	TRUE if the INT32 file was successfully opened, FALSE otherwise.
	Purpose:	Prepares the preference system for reading in preferences.

********************************************************************************************/

BOOL OILPreferences::OpenInput()
{
	// Tell wxWidgets this is the default wxConfig object
	wxConfig::Set(this);

	return TRUE;
}

/********************************************************************************************

>	BOOL OILPreferences::CloseInput()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/93
	Returns:	TRUE if the input file was successfully closed, FALSE otherwise.
	Purpose:	Performs clean-up necessary when the preferences file is no longer needed
				for reading.

********************************************************************************************/

BOOL OILPreferences::CloseInput()
{
	wxConfig::Set(NULL);

	return TRUE;
}


/********************************************************************************************

>	BOOL OILPreferences::OpenOutput()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/93
	Returns:	TRUE if the output file was successfully opened, FALSE otherwise.
	Purpose:	Prepares the OIL for writing preferences out to the preferences file.

********************************************************************************************/

BOOL OILPreferences::OpenOutput()
{
	return TRUE;
}

/********************************************************************************************

>	BOOL OILPreferences::CloseOutput()

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/93
	Returns:	TRUE if the output file was successfully closeed, FALSE otherwise.
	Purpose:	Closes the preference file when all the preferences have been written.

********************************************************************************************/

BOOL OILPreferences::CloseOutput()
{
	Flush();
	return TRUE;
}
