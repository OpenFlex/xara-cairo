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

// Short Description of what this file is for

#ifndef INC_ARCHIVE
#define INC_ARCHIVE

class CCLexFile;


/********************************************************************************************

>	class CCArchive : public CC_CLASS_MEMDUMP

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/12/94
	Purpose:	Archive class used to save and load the Camelot tree

********************************************************************************************/

class CCArchive : public CC_CLASS_MEMDUMP
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(CCArchive);


	enum { Load=1, Save=2 };

	// Construction etc.
	CCArchive(CCLexFile* pNewFile, UINT32 Mode);
	~CCArchive();

	void Close();

	// Saving operators
	CCArchive& operator>>(INT32&);
	CCArchive& operator>>(BYTE&);
	CCArchive& operator>>(WORD&);
	CCArchive& operator>>(INT32&);
	CCArchive& operator>>(DWORD&);
	CCArchive& operator>>(float&);
	CCArchive& operator>>(double&);

	// Loading operators
	CCArchive& operator<<(INT32);
	CCArchive& operator<<(BYTE);
	CCArchive& operator<<(WORD);
	CCArchive& operator<<(INT32);
	CCArchive& operator<<(DWORD);
	CCArchive& operator<<(float);
	CCArchive& operator<<(double);

	// Query functions
	BOOL IsReady();
	BOOL IsLoading() const;
	BOOL IsSaving() const;

protected:
	// archive objects cannot be copied or assigned
	CCArchive(const CCArchive& Src);
	void operator=(const CCArchive& Src);

	// Members
	CCLexFile* pFile;				// The file that the Archive will be using to Save/Load

	// Flags
	BOOL IsLoadArchive;			// TRUE if the Archive is loading, FALSE if it is Saving
	BOOL IsArchiveOK;			// TRUE if the Archive is all OK

};

#endif  // INC_ARCHIVE
