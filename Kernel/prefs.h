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


#ifndef INC_PREFS
#define INC_PREFS

#include <limits.h>
#include <float.h>

#include "list.h"

// Opaque types
class PreferenceSection;
class OILPreferences;
class StringBase;

// Union for accessing polymorphic preference data
// used to be in oilprefs.h before 25/3/97
typedef union
{
	INT32		*pInt;
	UINT32		*pUInt;
	double		*pDouble;
	StringBase	*pString;
} PrefData;

// This is here because OILPreferences needs it
typedef enum
{
	PREF_INT,
	PREF_UINT,
	PREF_DOUBLE,
	PREF_STRING
} PreferenceType;

/********************************************************************************************

>	class Preferences : public List

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/8/93
	Purpose:	Maintains a list of PreferenceSection objects, and allows clients to declare
				new sections, and add new preferences to the sections.
				
				For details of how to declare/use preferences, see the Application class.
				
				
				When the application wants to save the preferences, the Write() function
				of this class should be used.
				
	SeeAlso:	-

********************************************************************************************/


class CCAPI Preferences : public List
{
	CC_DECLARE_MEMDUMP(Preferences)
	
public:
	Preferences();
	~Preferences();
	
	BOOL Init();
	void Deinit();
	
	void Write();

	void WipePreferenceFile();
	void WipeDangerousPrefs();
	
	BOOL DeclareSection(TCHAR *Section, UINT32 InitialSize);
	
	BOOL DeclarePref(TCHAR *Section, TCHAR *Pref, 
					 INT32 *PrefVar, INT32 Min = INT_MIN, INT32 Max = INT_MAX);
					 
	BOOL DeclarePref(TCHAR *Section, TCHAR *Pref, 
					 UINT32 *PrefVar, UINT32 Min = 0, UINT32 Max = UINT_MAX);
					 
	BOOL DeclarePref(TCHAR *Section, TCHAR *Pref, 
					 double *PrefVar, double Min = DBL_MIN, double Max = DBL_MAX);
	
	BOOL DeclarePref(TCHAR *Section, TCHAR *Pref, StringBase *PrefVar);

	// These next functions allow the preferences to be read/written by other
	// people than the owner e.g. the application options dialog box

	BOOL GetPrefValue(TCHAR *Section, TCHAR *Pref, INT32 *PrefVar);
	BOOL GetPrefValue(TCHAR *Section, TCHAR *Pref, UINT32 *PrefVar);
	BOOL GetPrefValue(TCHAR *Section, TCHAR *Pref, double *PrefVar);

	BOOL SetPrefValue(TCHAR *Section, TCHAR *Pref, INT32 *PrefVar);
	BOOL SetPrefValue(TCHAR *Section, TCHAR *Pref, UINT32 *PrefVar);
	BOOL SetPrefValue(TCHAR *Section, TCHAR *Pref, double *PrefVar);

	BOOL SetPrefDirect(TCHAR *Section, TCHAR *Pref, const TCHAR *pValue, BOOL Force = FALSE);
	BOOL SetPrefDirect(TCHAR *Section, TCHAR *Pref, PreferenceType Type, PrefData Data);
	BOOL SetPrefDirect(TCHAR *Section, TCHAR *Pref, INT32 *pValue);
	BOOL SetPrefDirect(TCHAR *Section, TCHAR *Pref, UINT32 *pValue);
	BOOL SetPrefDirect(TCHAR *Section, TCHAR *Pref, double *pValue);

	BOOL GetPrefDirect(TCHAR *Section, TCHAR *Pref, StringBase *pValue);
	BOOL GetPrefDirect(TCHAR *Section, TCHAR *Pref, PreferenceType Type, PrefData Data);
	BOOL GetPrefDirect(TCHAR *Section, TCHAR *Pref, INT32 *pValue);
	BOOL GetPrefDirect(TCHAR *Section, TCHAR *Pref, UINT32 *pValue);
	BOOL GetPrefDirect(TCHAR *Section, TCHAR *Pref, double *pValue);

private:
	// Used to cache the section object when declaring preferences.
	PreferenceSection *CurrentSection;
	PreferenceSection *GetSection(TCHAR *SectionName);
	
	// Link to the OIL layer
	OILPreferences *OILPrefs;

};

#endif
