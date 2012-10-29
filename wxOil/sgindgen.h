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

// SGindgen.h - Index generation code

#ifndef INC_SGINDGEN
#define INC_SGINDGEN


/********************************************************************************************

>	class IndGenFileBuffer : public CCObject

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/05/95
	Purpose:	Since MSDOS seems happy returning filenames of files in a directory in a
				completely random fashion, we need to have some way of storing all the ones
				it returns us and sorting them alphabetically, so we can generate index files
				in a nice alphabetical order.

				The data structure used below is basically an array of TCHAR *'s pointed to
				by Buffer. These TCHAR *'s are CCMalloced and given variable length C style
				strings by AddItem. The destructor handles the memory tidying up.

********************************************************************************************/

class IndGenFileBuffer : public CCObject
{
	CC_DECLARE_DYNCREATE( IndGenFileBuffer )

public:
	IndGenFileBuffer();
	~IndGenFileBuffer();
	BOOL Init(INT32 Count);
	BOOL AddItem(TCHAR *String);
	BOOL Sort(void);
	TCHAR *GetItem(INT32 Count);
	INT32 ItemCount(void)	{return Items;}

protected:
	static INT32 __cdecl SortComparator(const void *Item1, const void *Item2);

protected:
	TCHAR **Buffer;
	INT32 Items;
	INT32 Position;
};


/********************************************************************************************

>	class GenerateIndexFile : public CCObject

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/04/95
	Purpose:	For generating of index files

********************************************************************************************/

class GenerateIndexFile : public CCObject
{
	CC_DECLARE_DYNCREATE( GenerateIndexFile )

public:

	// Constructor
	GenerateIndexFile();

	// Destructor
	~GenerateIndexFile() {}

	// Actually generate the index
	BOOL Generate(PathName *IndexFile, PathName *LibDirPath, String_64 *Author,
								SGLibType Type, BOOL Thumbnails);

protected:

	// Close the search handle
	BOOL CloseSearchHandle(void);
	
	// Close the file handle
	BOOL CloseIndexFileHandle(void);

	// Create the index file and keywords file then add headers to them													   
	BOOL CreateIndexFile(void);

	// Count the number of files that will be added to the index file in the directory
	INT32 CountValidFiles(void);

	// If the normal place for the index is read only, sir might consider a more remote location, oui ?
	BOOL RemoteIndexSetup(PathName *FilesPath);

	// Check if the given index has a remote pointer, and return the location if it has
	BOOL CheckExistingIndexForRemoteness(PathName *IndexFile, PathName *FilesPath);

public:

	// Returns true if the directory is read only
	static BOOL IsDirectoryReadOnly(PathName *Directory);

	// Check to see if we've already got a remote directory for a FilesDirectory, or at
	// least return the location for the remote directory
	static BOOL CheckForRemote(PathName *FilesDirectory, String_256 *RemoteDirectory);

	// Given a random collection of garbage as an input string, return a valid directory path on output
	static BOOL GiveMeAValidDirectoryName(String_256 *Input, String_256 *Output);

protected:

	// Add all the header data to an index file
	BOOL DoIndexHeader(void);

	// Scan the directory for files and add them to the index file
	BOOL AddToSubLibrary(void);

	// Poke the count field with the correct value
	BOOL FixSubLibraryNumber(void);

protected:

	// Add a file to the index
	BOOL AddFile(PathName *FileName);

	// Return true if a file should be associated with the index
	static BOOL IsFileType(PathName *FileName, const SGLibType Type);

protected:
	// Get a 16bit value from the file
	INT16 GetShort(FILE *fp);

	// Return the integer part of a 16.16 fixed only
	INT16 GetFixed(FILE *fp);

	// Return a full 32 bit number from a file
	INT32 GetLONG(FILE *fp);

	// Rip out the full TTF typeface name from a font file
	BOOL RipTrueTypeNameFromFile(PathName *FileName, String_256 *Name);

	// Rip out the full ATM typeface and styles from a font file
	BOOL RipATMNameFromFile(PathName *FileName, String_256 *RetName, BOOL *Bold, BOOL *Italic);

protected:
	// This will check that creating the thumbnail won't cause us to go BANG !
	static BOOL PreCreateThumbnail(PathName *InFile);

	// Given an input filename and output filename, generate a thumbnail of specified dimensions
	BOOL CreateThumbnail(PathName *InFile, PathName *OutFile, UINT16 XSize, UINT16 YSize);

	/* Create the thumbnails for the specified file */
	BOOL CreateThumbnails(PathName *FileName, BOOL NewSystem = TRUE);

protected:

	// Scan the given file and try and work out a description and keywords for it
	BOOL RipDescriptionFromFile(PathName *FileName,
					String_256 *Text, String_256 *Keywords = NULL, String_256 *Title = NULL);

	// Try and work out a description and keywords given an EPS/ART filename (uses comments in file)
	BOOL RipDescriptionFromEPSFile(PathName *FileName,
					String_256 *Text, String_256 *Keywords = NULL, String_256 *Title = NULL);

	// Try and work out a description and keywords given a CDR filename
	BOOL RipDescriptionFromCDRFile(PathName *FileName,
					String_256 *Text, String_256 *Keywords = NULL, String_256 *Title = NULL);

	// Try and work out a description and keywords given a version 2 native/web filename
	BOOL RipDescriptionFromNativeV2File(PathName *FileName,
					String_256 *Text, String_256 *Keywords = NULL, String_256 *Title = NULL,
					BOOL *FileIsNewNative = NULL);


	// Scan an old index file looking for the description of the given filename
	BOOL RipDescriptionFromIndex(PathName *IndexFile, PathName *FileName,
					FilePos Start, INT32 DescriptionField, INT32 KeywordField, INT32 TitleField,
					String_256 *Text, String_256 *Keywords = NULL, String_256 *Title = NULL);

	BOOL PrePassIndex(PathName *IndexFile, FilePos *Start,
		INT32 *DescriptionField, INT32 *KeywordField, INT32 *TitleField, String_256 *Description);

public:
	// General utilities for the ripping functions
	static BOOL ReplaceCharacters(StringBase *Source, TCHAR Search, TCHAR Replace);
	static INT32 CountCommas(StringBase *Source, StringBase &SearchFor);
	static BOOL GetToken(StringBase *Source, INT32 Count, String_256 *Result);

protected:
	// Adds the given text to the index file
	BOOL AddLineToIndex(String_256 *Text);

protected:
	PathName Index;
	PathName LibPath;
	SGLibType LibType;
	BOOL DoThumbnails;
	String_64 Author;

	// Disk file for index file
	CCDiskFile *IndexFile;

	// Offset into index for the 'Number of files' data
	FilePos IndexCountOff;

	// Search handle for directory scan		
	HANDLE hSearch;

	// ID of current item and number of items in file
	UINT32 ID;

	// Pre-counted number of files to add to index
	INT32 TotalFiles;

	// Location of old index file (if there was one)
	PathName *TmpIndexFile;

	// Sorted buffer containing all the filenames in the directory
	// ( Initialised by CountValidFiles() )
	IndGenFileBuffer FileNameBuffer;

	// Vars to speed up ripping old data from existing indexes
	FilePos OldIndexStart;
	INT32 OldIndexDescriptionField;
	INT32 OldIndexKeywordField;
	INT32 OldIndexTitleField;
	BOOL OldIndexOK;
	String_256 OldIndexDescription;

	// Remote indexes
	BOOL IndexIsRemote;
	String_256 RemoteLocationOfIndex;
	String_256 RemoteLocationOfFiles;


	// Automatic index update functions
public:
	static UINT32 GetDirectoryChecksum(String_256 *Directory, SGLibType Type = SGLib_Blank);
	static BOOL UseAutomaticUpdate;

public:
	// Preference setting saying whether thumbnail generation is required	
	static BOOL CreateFontIndexes;

	// Preferences to use old index files / rip doc comments out
	static BOOL UseOldIndexes;
	static BOOL UseDocComments;

};

#endif
