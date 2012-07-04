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


#ifndef INC_PathName
#define INC_PathName
 
/*********************************************************************************************

>	class PathName : public CCObject

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/5/1993          
	Base Class:	CCObject
	Purpose:	Represents a simple path and filename.	
	Errors:		None.

*********************************************************************************************/

class PathName : public CCObject
{
protected:
	BOOL PathNameValid;									// If we like that pathname
	String_256 location;								// Where file resides in file system
	String_256 filename;    	                		// Name of file
	String_256 filetype;        	            		// Type of file - Extension
	String_256 drivename;								// Drive location
	virtual BOOL IsValidAndReturnInfo(const String_256& ConstPath, String_256& tempFilename,
		String_256& tempLocation, String_256& tempFiletype,	String_256& tempDrivename, BOOL SetErrors = TRUE) const;
														// Checks if a pathname is valid or not
														// and if so returns filename, location
														// and file extension found to caller.
	void TruncateName(String_256& FullName, String_256* pShortName, INT32 MaxSize) const;

public:
	PathName();
	PathName(const PathName&);	
	PathName(const String_256&);						// Initialise PathName with string
	
 	const String_256 GetPath(BOOL TrailingSlash=FALSE) const; 	// return full path of file
 	const String_256 GetLocation(BOOL KeepSep=TRUE) const; // return just the location
 	const String_256 GetFileName(BOOL FullName=TRUE) const;// return just the filename.ext
	const String_256 GetType() const;                      // return the file type = .ext

	String_256 GetWebAddress() const;

	const String_256 GetTruncatedPath(UINT32 MaxSize = 0) const; // return truncated form of path
	const String_256 GetTruncatedLocation(UINT32 MaxSize = 0) const; // return truncated form of location
	
	BOOL SetType(const String_256& NewType);			// Allows you to change the file extension
	BOOL SetFileName(const String_256& NewFileName);	// Modifies the filename (if extension present then ignores)
	BOOL SetFileNameAndType(const String_256& NewFileName);// Modifies the filename and type
	BOOL SetPathName(const String_256&, BOOL SetErrors = TRUE);				// Builds a PathName from a string


	virtual BOOL IsValid(const String_256&) const;					// Checks if a pathname is valid or not
	virtual BOOL IsValid() const;										// Checks if the current pathname is valid or not
	
	PathName& operator=(const PathName&);				// Assigns one PathName onto another

};



/*********************************************************************************************

>	class DirPath : public PathName

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/2/1996
	Purpose:	Represents and validates a directory pathname, rather than a file pathname
	Errors:		None.

*********************************************************************************************/

class DirPath : public PathName
{
public:
	DirPath();
	DirPath(const DirPath&);
	DirPath(const String_256&);

	BOOL SetDirPath(const String_256&);				// Builds a DirPath from a string

	virtual BOOL IsValid(const String_256&)const;		// Checks if a pathname is valid or not
	virtual BOOL IsValid()const;							// Checks if the current pathname is valid or not

protected:
	virtual BOOL IsValidAndReturnInfo(const String_256&, String_256&, String_256&, String_256&, 
							  String_256&, BOOL=TRUE)const;
		// Checks if a pathname is valid or not and if so returns filename, location
		// and file extension (which should be empty) found to caller.
		// Note that the filename is the last directory name in the path, so "C:\fred\bob" will
		// return "bob" as its filename, "C:\fred" as its location. (GetPath() will return the
		// lot.
};



/*********************************************************************************************

>	class FilePath : public PathName

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/2/1996
	Purpose:	Represents and validates a file pathname, rather than a directory pathname
	Errors:		None.

*********************************************************************************************/

class FilePath : public PathName
{
public:
	FilePath();
	FilePath(const FilePath&);
	FilePath(const String_256&);

	BOOL SetFilePath(const String_256&);			// Builds a FilePath from a string

	virtual BOOL IsValid(const String_256&)const;		// Checks if a file pathname is valid or not
	virtual BOOL IsValid()const;							// Checks if the current pathname is valid or not

protected:
	virtual BOOL IsValidAndReturnInfo(const String_256&, String_256&, String_256&, String_256&, 
							  String_256&, BOOL=TRUE)const;
		// Checks if a file pathname is valid or not and if so returns filename, location
		// and file extension found to caller.
};


#endif

