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


// file used to determine whether a release version or not

#ifndef	INC_RELEASE
#define	INC_RELEASE

//#include "cversion.h"

// Previous tortuous logic removed 21/6/96 by Phil & Jim
// RELEASE is defined in the OLE mfc bits so try and use something different. Neville 9/6/97
#ifndef _RELEASE
	#ifdef _DEBUG
		#define	_RELEASE 0
	#else
		#define _RELEASE 1
	#endif
#endif

class ReleaseInfo
{
public:
	static const TCHAR* GetInfo();
	static const TCHAR* GetLicensee();
	static const TCHAR* GetSerialNumber();
	static const TCHAR* GetCompany();

	static void CacheProfileSettings();
	static BOOL RestoreProfileSettings();

protected:
	static BOOL WriteProfile(LPCTSTR pKey, LPCTSTR pValue);

private:
	UINT32 SerialNumber;
	const TCHAR *Name;
};

#endif
