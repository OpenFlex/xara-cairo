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

// Super Gallery Library File class

#ifndef INC_SGSCANF
#define INC_SGSCANF

//#include "thumb.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class PathName;
class SuperGallery;
class LibraryGallery;
class Library;


/***********************************************************************************************

>	class LibraryFile : public ListItem

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/2/95
	Purpose:	This is the main super gallery library creation class...
				Creating one of these will give your gallery a set of new sub-lib groups
				containing DisplayItems for the entries in the sub-group.
	SeeAlso:	Library; LibraryFileGroup;

***********************************************************************************************/

class LibraryFile : public ListItem
{
	CC_DECLARE_DYNCREATE(LibraryFile)

public:		// Construction/destruction
	LibraryFile();
	~LibraryFile();


public:		// public interface

	// Ask a newly created LibraryFile to scan and create Gallery groups
	// Returns number of groups created, or 0 in case of error
	// If the main or default subindex files don't exits we give the option
	// of generating a default sublib index to the user.
	INT32 Init(SuperGallery *ParentGal, PathName *Path, SGLibType Type, BOOL Updated = FALSE, BOOL DoScroll = TRUE);

	// Add a specific index to a newly created LibraryFile (This can be called instead
	// of the above Init call, which is really designed to hunt out it's own index files) 
	BOOL AddSpecificIndex(SuperGallery *ParentGal, PathName *Path, SGLibType Type, StringBase *Description = NULL, UINT32 bModified = 0, 
		BOOL bIsWebLib = FALSE);

	// Find the list of Libraries found by Init
	inline List *GetLibraryList(void);

	// Kill leading spaces from a string
	static BOOL KillLeadingSpaces(StringBase *Str);

	// Returns the pathname of this library, as passed in to the Init method
	PathName *GetLibraryPathName(void);

	// Returns the type of this library, as passed into the Init method
	SGLibType GetLibraryType(void);

	// Generate a default index for a given directory
	static BOOL GenerateDefaultIndex(PathName *IndexFile, PathName *LibDirPath,
								String_64 *Author, SGLibType Type, BOOL Thumbnails);

	// Check directory for subindex files. If we find any, add them to the gal.
	// If we don't, give the option to generate a subindex if the type can cope with it.
	BOOL CheckForSubIndexes(SuperGallery *ParentGal, PathName *Path, SGLibType Type, BOOL Updated = FALSE);

	// Get pathname of default sublib index and find out whether we can generate indexes, etc
	static BOOL GetSubIndexDetails(LibraryGallery *LG, String_256 *DefaultIndex, String_256 *IndexDesc, BOOL *CanGenerate);

	// Remove XaraInfo's and trailing backslashes from a string
	static BOOL TidyUpSubPath(String_256 *Str);

	// Count number of valid lines in a file
	static INT32 CountLines(PathName *IndexFilePath);

	// Actually do the scroll / redraw...
	void DoScrollRedraw(void);

protected:

	// Init the scroll/redraw system
	void InitScrollRedrawSystem(void);

	// Add a new folder to the scroll/redraw system
	void AddNewFolderToScrollRedrawSystem(Library *NewFolder);
	
protected:
	PathName MyPath;						// The pathname of this library file
	SGLibType MyType;						// The type of library we represent

public:
	List Libraries;							// A list of all contained Libraries
	SuperGallery *ParentGallery;			// A pointer to the gallery who owns us
	LibraryGallery *ParentLibraryGallery;	// A pointer to the library gallery who owns us (if either
											// of these are NULL, we're in deep water...)
	static Library *FirstLibraryAdded;		// Two statics for redraw/scroll purposes...
	static Library *LastLibraryAdded;
};



/***********************************************************************************************

>	inline List *LibraryFile::GetLibraryList(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/2/95
	Purpose:	Returns a pointer to the LibraryFile's list of available libraries.
				You should treat this list as READ ONLY.

***********************************************************************************************/

List *LibraryFile::GetLibraryList(void)
{
	return(&Libraries);
}


#endif
