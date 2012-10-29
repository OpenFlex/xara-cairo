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
	Platform-dependent implementation of a function to determine the size of a file.
	Uses MFC 2.0


*/


#include "camtypes.h"

DECLARE_SOURCE("$Revision: 1282 $");



size_t CCDiskFile::Size()
{
	ENSURE(isOpen(), "Must open a CCDiskFile before calling Size()!\n");

/*	CFileStatus fs;
	if (!CFile::GetStatus((const TCHAR*)filePath.GetPath(), fs))
	{
		#ifdef	_DEBUG
			if (IsUserName("JustinF"))
				TRACE( _T("Attempt to read size of non-existent file\n"));
		#endif	// _DEBUG
		return -1;
	}
	return fs.m_size;*/

	// [A quick story from richard]
	// Whilst writing the library gallery code I came to much grief using MFC functions
	// to check for a file's existance and its size... In the end I resorted to writing
	// some functions of my own which did the same job, only better, and didn't hinder
	// timings that much. The above code was found to have problems with certain files.
	// Basically if the file has invalid datestamps, MFC goes tits-up... We found quite
	// a few files in this catagory... The below call is known to work, and has been
	// tested beyond belief whilst writing gallery stuff...
	size_t			FileSize = 0;

#if defined(__WXMSW__) || 0 == wxUSE_UNICODE
	FILE *FP = _tfopen((const TCHAR *)filePath.GetPath(), _T("rb"));
#else
	// GNU\Linux seems to have no unicode filesystem name support, so we
	// just get on and do the needed conversion as efficiently as possible
	size_t				cchTmp = camWcstombs( NULL, filePath.GetPath(), 0 ) + 1;
	PSTR				pszTmp = PSTR( alloca( cchTmp ) );
	camWcstombs( pszTmp, filePath.GetPath(), cchTmp );

	FILE *FP = fopen( pszTmp, "rb" );
#endif
	
	if(FP != NULL)
	{
		fseek(FP,0,SEEK_END);
		FileSize = ftell(FP);
		fclose(FP);
	}

	return FileSize;
}
