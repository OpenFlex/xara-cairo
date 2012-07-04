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

// SGRMfile.h - Gallery Resource Management file routines

#ifndef INC_SGRMFILE
#define INC_SGRMFILE

//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ccfile.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class PathName;
class String_256;

/********************************************************************************************

>	class LibSettingsListItem : public ListItem

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/01/96
	Purpose:	Memory list of section lines to speed GRMFile reading up somewhat
	SeeAlso:	LibSettings::BuildList, which builds the list from a section name
	
********************************************************************************************/

class LibSettingsListItem : public ListItem
{
	CC_DECLARE_DYNCREATE( LibSettingsListItem )

public:
	LibSettingsListItem();
	~LibSettingsListItem();

	LibSettingsListItem(String_256 *Entry);
	String_256 *Line;
};



/********************************************************************************************

>	LibSettings

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/5/95
	Purpose:	The Gallery Resource Management class...

	Notes:		Currently this code uses the GRM file to remember which groups were in which
				libraries and in which order when quitting the program so than on loading next
				time we can reflect the old status in the library...
				
				As this is fairly general read and write ini file code, then this has been
				expanded so that an option other ini file name can be specified. If this is
				specified then this will be used instead of the GRM file name.
				Added by Neville 14/1/97 for saving/loading paths for plug-ins as the main 
				ini file code cannot cope with the concept of sections filled with an arbitrary
				number of items which need cleaning out when resaving to remove old items no
				longer required.

********************************************************************************************/

class LibSettings: public CCObject
{
	CC_DECLARE_DYNCREATE( LibSettings )

public:
  	LibSettings();
	~LibSettings();
	static BOOL Init(void);
	static BOOL GetEntry(String_256 *Section, INT32 Line, String_256 *Entry,
						 FilePos *Pos = NULL, String_256 * pIniFileString = NULL);
	static BOOL AddLine(String_256 *Line, String_256 * pIniFileString = NULL);
	static BOOL AddSection(String_256 *Section, String_256 * pIniFileString = NULL);
	static BOOL IsThisANewSection(String_256 *Line, String_256 *Section);
	static BOOL StartOutput(String_256 *Section, String_256 * pIniFileString = NULL);
	static BOOL NukeSettings(String_256 * pIniFileString = NULL);
	static BOOL GetPathName(PathName *PathName, String_256 * pIniFileString = NULL);

	static BOOL GetEntryStart(CCDiskFile *DiskFile, String_256 * pIniFileString = NULL);
	static BOOL GetEntryFromFile(CCLexFile *TheFile, String_256 *Section, INT32 Line, String_256 *Entry,
						FilePos *Pos = NULL);
	static BOOL GetEntryFinish(CCDiskFile *DiskFile);

	static BOOL BuildList(String_256 *Section, List *OutputList);
	static BOOL GetNextLine(CCDiskFile *TheFile, String_256 *Line);
	static BOOL SeekToSection(CCDiskFile *TheFile, String_256 *Section);

	static CCDiskFile *DiskFile;
};  

#endif
