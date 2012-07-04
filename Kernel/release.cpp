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


// ReleaseInfo class - informs program about release information

/*
*/

#include "camtypes.h"
//#include "release.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "brandinf.h"
//#include "justin2.h"
//#include "app.h"		// Camelot object - in camtypes.h [AUTOMATICALLY REMOVED]

// these are packed so that a brander program can easily find & verify them

// lets declare a Unicode version of the name, which will be much harder to find

PORTNOTE("other", "Removed branding stuff")
#ifndef EXCLUDE_FROM_XARALX
// put these in a different segment to the others
#pragma data_seg( "CAMELOT", "DATA" )
struct
{
	UINT32 Magic;
	UINT32 Serial;
	wchar_t Name[BRANDED_NAME_MAX];
	wchar_t Company[BRANDED_NAME_MAX];
} SecretInfo =
{
	BRANDED_MAGIC2,
	BRANDED_SERIALNUMBER ^ BRANDED_XOR,
	BRANDED_NAME_UNICODE,
	BRANDED_COMPANY_UNICODE
};

#endif

#ifndef BRANDED_NAME_MAX
	#define BRANDED_NAME_MAX 255
#endif

#pragma data_seg()
struct p
{
	UINT32	Magic;
	UINT32	Serial;
	TCHAR	Name[BRANDED_NAME_MAX];
	TCHAR	Company[BRANDED_NAME_MAX];
} PublicInfo =
#ifndef EXCLUDE_FROM_XARALX
{
	BRANDED_MAGIC1,
	BRANDED_SERIALNUMBER,
	BRANDED_NAME,
	BRANDED_COMPANY
};
#else
{
	0,
	0,
	_T("Unregistered user"),
	_T("Unregistered company")
};
#endif

// bug - before 28/2/97 only allocated 10 chars so when it puts 101- and then the
// number to 9 places it will overflow into the next string. This string dictates
// the key name it is written under. So it will be written/read from the wrong section.
static TCHAR szCachedSerial[25]	= _T("");

// Pseudo-Preferences
static TCHAR szUISection[]		= _T("UserInfo");

static TCHAR szSerialNumber[]	= _T("SerialNo");
static TCHAR szLicensee[]		= _T("Licensee");
static TCHAR szCompany[]		= _T("Company");

//***************************************************************************
// this returns the obvious user name. Not hidden at all


// Why was this class written to use type TCHAR, not TCHAR?   This is a royal pain in the backside.

const TCHAR *ReleaseInfo::GetInfo()
{
	static TCHAR buf[256];

#ifndef STANDALONE
//	camSprintf(buf, "%s (#101-%09ld)", PublicInfo.Name, PublicInfo.Serial );
//	camSprintf(buf, TEXT("%s (#%s)"), ReleaseInfo::GetLicensee(), ReleaseInfo::GetSerialNumber());

	String_256 jcf;
	jcf.MakeMsg(_R(IDS_RELEASE_INFO_FORMAT), ReleaseInfo::GetLicensee(), ReleaseInfo::GetSerialNumber());
	camStrcpy(buf, jcf);

#else
	camStrcpy(buf, PublicInfo.Name);
#endif

	return buf;
}

//***************************************************************************

const TCHAR* ReleaseInfo::GetLicensee()
{
	static TCHAR buffer[64];
#if !defined(EXCLUDE_FROM_XARALX) && defined(_DEBUG)
	TCHAR* pLogName=_tgetenv(TCHAR);
	if (pLogName!=NULL)
		camSprintf(buffer,_T("%s"),pLogName);
	else
		camSprintf(buffer,_T("%s"),("NoLogName"));
#else
	// read the licensee preference value into a string
	String_256 Str;
	BOOL ok = Camelot.GetPrefDirect(szUISection, szLicensee, &Str);
	if (ok) 
	{
		// copy the string into the return buffer
		TCHAR* StringBuf = (TCHAR*)Str;
		camSprintf(buffer, _T("%s"), StringBuf);
	}
	else
	{
		// something went wrong so use a default, the bound in one
		camSprintf(buffer,_T("%s"),PublicInfo.Name);
	}
#endif

	return buffer;
}

//***************************************************************************

const TCHAR* ReleaseInfo::GetSerialNumber()
{
	static TCHAR buffer[64];

	// read the serial number preference value into a string
	String_256 Str;
	BOOL ok = Camelot.GetPrefDirect(szUISection, szSerialNumber, &Str);
	if (ok) 
	{
		// copy the string into the return buffer
		TCHAR* StringBuf = (TCHAR*)Str;
		camSprintf(buffer, _T("%s"), StringBuf);
	}
	else
	{
		// something went wrong so use a default, the bound in one
		camSprintf(buffer,_T("101-%09ld"),PublicInfo.Serial);
	}

	return buffer;
}

//***************************************************************************

const TCHAR* ReleaseInfo::GetCompany()
{
	static TCHAR buffer[64];
	// read the company preference value into a string
	String_256 Str;
	BOOL ok = Camelot.GetPrefDirect(szUISection, szCompany, &Str);
	if (ok) 
	{
		// coy the string into the return buffer
		TCHAR* StringBuf = (TCHAR*)Str;
		camSprintf(buffer, _T("%s"), StringBuf);
	}
	else
	{
		// something went wrong so use a default, the bound in one
		camSprintf(buffer,_T("%s"),PublicInfo.Company);
	}

	return buffer;
}



/***********************************************************************************************

> 	void ReleaseInfo::CacheProfileSettings()

    Author: 	Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
    Created:	10/09/96
    Purpose:    Stores the current ReleaseInfo settings from the .ini file to an internal buffer
				This is currently used to prevent user information being lost when the default
				user profile is restored.
	Scope:		static

	See Also:	RestoreProfileSettings()
                   			                                     
***********************************************************************************************/
void ReleaseInfo::CacheProfileSettings()
{
	camStrcpy(PublicInfo.Name, GetLicensee());
#ifndef WEBSTER
	// No serial number in Webster v2.0.
	// This happens too early to get resources.
	camStrcpy(szCachedSerial, GetSerialNumber());
#endif
	camStrcpy(PublicInfo.Company, GetCompany());
}

/***********************************************************************************************

> 	BOOL ReleaseInfo::RestoreProfileSettings()

    Author: 	Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
    Created:	10/09/96
	Returns:	TRUE if successful
				FALSE otherwise
    Purpose:    Restores the current ReleaseInfo settings in the .ini file to the values
				present in the cache
				This is currently used to prevent user information being lost when the default
				user profile is restored.
	Scope:		static

	See Also:	CacheProfileSettings()
                   			                                     
***********************************************************************************************/
BOOL ReleaseInfo::RestoreProfileSettings()
{
	if (!WriteProfile(szSerialNumber, szCachedSerial))
	{
		return FALSE;
	}

	if (!WriteProfile(szLicensee, PublicInfo.Name))
	{
		return FALSE;
	}

	if (!WriteProfile(szCompany, PublicInfo.Company))
	{
		return FALSE;
	}

	return TRUE;
}


/***********************************************************************************************

> 	BOOL ReleaseInfo::WriteProfile(LPCTSTR pKey, LPCTSTR pValue)

    Author: 	Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
    Created:	10/09/96
	Inputs:		pKey:	The key in the .ini file
				pValue:	The value to which to set it
	Returns:	TRUE if successful
				FALSE otherwise
	Scope:		static protected

    Purpose:    Support function for RestoreCurrentSettings()
				Writes an .ini file setting in the UserInfo section of the current apps profile
				file using ::WritePrivateProfileString() and the given key and value.
                   			                                     
***********************************************************************************************/
BOOL ReleaseInfo::WriteProfile(LPCTSTR pKey, LPCTSTR pValue)
{
	ERROR2IF(pKey == NULL || pValue == NULL,FALSE,"ReleaseInfo::WriteProfile Bad params!");

	// This will be done when the ini file is being vaped. Hence it will happen very soon after
	// start up. If this happens to be the first time Camelot is started up then we may be reading
	// from ini files and wanting to write the data into the registry. If we do this now then we 
	// will be writing into the ini file as we only switch over to the registry when we are
	// destructing Camelot. So we must make sure that this info is written out into the registry.
	// If we do it now then the registry section may be vaped before we write the real data out.
	// We will then need to ensure that if we switch from ini file to registry mode that the data
	// is saved out before and restored into the new place afterwards.

	String_256 Key(pKey);
	String_256 Section(szUISection);
	// don't use this as for some reason it seems to be corrupt
	// and says Tips when it comes to calling this
	if (!Camelot.SetPrefDirect(Section, Key, pValue, TRUE))
		return FALSE;

	return TRUE;
}
