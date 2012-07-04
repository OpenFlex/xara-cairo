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
 *  */

#ifndef INC_OILFILES
#define INC_OILFILES

//#include "ccfile.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/*********************************************************************************************

>	class CCResourceFile : public CCMemFile

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/9/1993          
	Base Class:	CCMemFile
	Purpose:	Will be used to access Windows resource files.
	Errors:		None.

*********************************************************************************************/

class CCAPI CCResourceFile : public CCMemFile
{                                   
public:
	CCResourceFile();
	
	CCResourceFile(ResourceID ResourceId, ResourceID ResourceType, FileAccess fProt = CCMemRead);
	
	~CCResourceFile();
    
	BOOL open(ResourceID ResourceId, ResourceID ResourceType, FileAccess fProt = CCMemRead);
	BOOL open(LPCTSTR, LPCTSTR, FileAccess = CCMemRead, HINSTANCE = NULL);
	BOOL open(UINT32);
};

/*********************************************************************************************

>	class CCResTextFile : public CCResourceFile

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/9/1993          
	Base Class:	CCResourceFile
	Purpose:
		Will be used to access Windows resource text files - such as those used in the 
		for Camelot Menu Scripts.
	Errors:		None.

*********************************************************************************************/

class CCAPI CCResTextFile : public CCResourceFile
{                                   
public:
	CCResTextFile() {}
	
	CCResTextFile(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt = CCMemRead);
	
	~CCResTextFile();
    
	BOOL open(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt = CCMemRead);
	BOOL open(UINT32);

	CCFile& read(TCHAR& 		buf);			// Read from Text Resource File
	CCFile& read(StringBase* 	buf);

	BOOL eof() const;
    
	void close();
};

/*********************************************************************************************

>	class CCClipBoardFile : public CCMemFile

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/9/1993          
	Base Class:	CCMemFile
	Purpose:	Will be used to access Windows text clipboard files.
	Errors:		None.

*********************************************************************************************/

PORTNOTE("clipboard","Removed CCClipBoardFile - MSW clipboard usage")
#ifndef EXCLUDE_FROM_XARALX
class CCAPI CCClipBoardFile : public CCMemFile
{                                   
protected:
	HGLOBAL ClipBoardHandle;
		
	BOOL GrowClipBoardFile();                           

public:
	CCClipBoardFile(FileAccess fProt = CCMemRead);
	
	~CCClipBoardFile();                           
	
	BOOL open(FileAccess fProt = CCMemRead);
                                                   
	CCFile& read(TCHAR& 		buf);  // Read from ClipBoard File
	CCFile& read(StringBase*	buf);
	
	CCFile& write(const TCHAR& 		buf);	// Write to Memory File
	CCFile& write(const StringBase&	buf, UINT32 length);

	BOOL eof() const;
    
	void close();
};
#endif

#endif
