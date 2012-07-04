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

// FileUtil - WinOil level file manipulation library


#ifndef INC_FILEUTIL
#define INC_FILEUTIL

class PathName;


/****************************************************************************

>	class FileUtil

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/07/96
	Purpose:	This class contains a library of static functions for use
				on Windows platforms. The functions perform general file
				manipulation operations, rather than single file data IO.
				If you want the size of a file, to locate a particular file
				on disc etc, then here's where you'll find all those useful
				routines to do it.
	SeeAlso:

****************************************************************************/

class FileUtil
{
public:		// Scanning for specific files
	static BOOL FindResourceFile(TCHAR* SearchFile, TCHAR* FoundFile);


public:		// Scanning through a set of particular files in a directory
	static BOOL StartFindingFiles(String_256 *FileSpecifier);
	static BOOL FindNextFile(String_256 *FoundFile);
	static void StopFindingFiles(void);

public:		// Misc
	static BOOL GetLongFileName(LPTSTR lpszPath, LPTSTR lpszOutput, size_t cchMaxOutLen);
	static UINT32 GetTemporaryFileName(const TCHAR *PathName, const TCHAR *Prefix, UINT32 Unique, TCHAR *FileName);
	static DWORD GetTemporaryPath(UINT32 BufferLength,	TCHAR *Buffer);

	static PathName GetTemporaryPathName();
	static BOOL GetTemporaryPathName(const TCHAR *pExt, PathName *pTempPath);
	static BOOL DeleteFile(PathName *FileToRemove);

	static BOOL GetCurrentDirectory(String_256 * pCurrentPath);
	static BOOL SetCurrentDirectory(const PathName& NewCurrentPath);
	static BOOL SetCurrentDirectory(const String_256& NewCurrentPath);

	static BOOL RecursiveCreateDirectory( const String_256& strDirPath );

	//A straightforward wrapper for the MFC function GetFileAttributes
	static DWORD FindFileAttributes(LPCTSTR lpFileName)
	{
		TRACE( wxT("Warning - FileUtil::FindFileAttributes called\n") );
#if defined(__WXMSW__)
		return GetFileAttributes( lpFileName );
#else
		return 0;
#endif
		}

private:	// Private data
	static BOOL				SearchActive;
	static bool				s_fStarted;
	static String_256		SearchPath;
	static wxDir			s_dirSearch;
};

/****************************************************************************

>	class FindFiles : public CC_CLASS_MEMDUMP

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/01/97
	Purpose:	This class can be used for searching directories for files.
				It is basically equivalent to the 
	SeeAlso:

****************************************************************************/

class FindFiles : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(FindFiles);
public:
	FindFiles() {};

public:		// Scanning through a set of particular files in a directory
	BOOL StartFindingFiles(String_256 *FileSpecifier);
	BOOL FindNextFile(String_256 *FoundFile, BOOL *IsDirectory);
	BOOL StopFindingFiles();

private:	// Private data
	String_256		m_SearchPath;
#if defined(__WXMSW__)
	HANDLE			m_SearchHandle;
	WIN32_FIND_DATA	m_SearchData;
#endif
};

#endif

