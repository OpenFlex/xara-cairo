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


/********************************************************************************************
	
	OilFiles.cpp	- Contains the function declarations of the WinOil CCFile derived classes.
	These include: CCResourceFile, CCResourceTextFile, CCClipBoardFile. 

********************************************************************************************/


#include "camtypes.h"
#include "oilfiles.h"
//#include "mario.h"
//#include "reshelp.h"
#include "camelot.h"
#include "oilmods.h"


                        
/********************************************************************************************
										CCResourceFile
********************************************************************************************/

CCResourceFile::CCResourceFile()
{
}

/********************************************************************************************

>	CCResourceFile::CCResourceFile(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>. Fixed by Andy.
	Inputs:		UINT32 - Resource Identifier representing the Windows resource to be read in
				UINT32 - Resource Type - String Id representing the type of Camelot resource
				fProt - defines the files protection - default = read only
				Use IsOpen to see if worked. If it didn't, then SetError will have been called
				(but InformError not).
	Created:	9/9/93
	Purpose:	Constructs an instance of CCResourceFile and Opens it

********************************************************************************************/

CCResourceFile::CCResourceFile(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt)
{
	// Load Resouce Name 
	String_256 ResNameID(ResourceId);

	// Load Resouce Type
	String_256 ResType(ResourceType);

	// then do the work - junks return value as IsOpen var is set in function
	open( ResNameID, ResType, fProt );
}

/********************************************************************************************

>	CCResourceFile::~CCResourceFile()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/93        
	Purpose:	Default destructor.

********************************************************************************************/

CCResourceFile::~CCResourceFile()
{                   
	if (isOpen()) close();
}



#if 0 // def _DEBUG
	void BadResLoad( LPCTSTR ResName, LPCTSTR ResType, HINSTANCE inst )
	{
		char RealResName[20];
		char RealResType[20];

		if (HIWORD(ResName)==0)
		{
			wsprintf( RealResName, "<#%u>", (UINT32)LOWORD(ResName) );
			ResName = RealResName;
		}

		if (HIWORD(ResType)==0)
		{
			wsprintf( RealResType, "<#%u>", (UINT32)LOWORD(ResType) );
			ResType = RealResType;
		}

		#ifdef _MAC
		TRACE( _T("ResError name='%s' type='%s' inst=%x\n"), ResName, ResType, (INT32)inst );
		DebugBreak();
		#else
		ERROR3_PF( ("ResError name='%s' type='%s' inst=%x\n", ResName, ResType, (INT32)inst ) );
		#endif
	}
#else
	#define	BadResLoad( ResName, ResType, inst )
#endif


/********************************************************************************************

>	BOOL CCResourceFile::open(LPCTSTR ResName, LPCTSTR ResType, FileAccess fProt = CCMemRead, HINSTANCE hinst = NULL)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Inputs:		ResName - name of resource
				ResType - type of resource
				fProt - file access type (defaults to read)
				hinst - where to get resource from (defaults to .exe)
	Returns:	TRUE if worked, FALSE if failed (SetError done to indicate error). Also
				sets isOpen flag.
	Created:	15/9/94
	Purpose:	Lowest level code - see Win32 FindResource call for further details of parameters.

********************************************************************************************/

BOOL CCResourceFile::open(LPCTSTR ResName, LPCTSTR WXUNUSED(ResType), FileAccess fProt, HINSTANCE WXUNUSED(inst) )
{
	// We assume we'll fail, until we don't
	IsOpen = FALSE;

	// Prevent opening file in write mode for the present time
	if (fProt == CCMemWrite)
	{
		Error::SetError(_R(IDE_OPEN_WRITE), 0);
   		return FALSE;
	}

	// Open file from zip FS
	CamResource			Resource;
	wxFSFile*			pFile = Resource.OpenwxFSFile( ResName );
	if( NULL == pFile )
	{
		Error::SetError(_R(IDE_LOAD_RES_ERROR), 0);
		return FALSE;
	}
	wxInputStream*		pStream = pFile->GetStream();
	if( NULL == pStream )
	{
		Error::SetError(_R(IDE_LOAD_RES_ERROR), 0);
		return FALSE;
	}

	// Setup house keeping, including allocation of buffer
	FileSize		= pStream->GetLength();
	MemHandle		= ClaimBlock( FileSize );
	if( BAD_MHANDLE == MemHandle )
	{
		FileSize = 0;
		return FALSE;
	}
	CurrentPos  	= 0;	
	FileProt		= fProt;
	IsOpen			= TRUE;

	// Read into memory
	size_t cbDescSize;
	DescribeBlock( MemHandle, &MemFile, &cbDescSize );
	pStream->Read( MemFile, FileSize );
	
	// If we haven't read all the file, we must have failed
	return (pStream->LastRead() == FileSize);

#if 0
	HRSRC   	hResource;

	if (!inst)
	{
		if(ExtraDLLs[Resources_DLL] != 0)
			inst = ExtraDLLs[Resources_DLL];	// use the external resource dll if present
		else
			inst = 0; // AfxGetResourceHandle();		// use the exe otherwise
	}

	// load Camelot Resources
	if (hResource = FindResource(inst, ResName, ResType))
		ResMemHandle = LoadResource(inst, hResource);

	// If resource not found or could not be loaded
	if (!ResMemHandle)
	{
		BadResLoad( ResName, ResType, inst );
		// report error that file is not closed before destructor call
		Error::SetError(_R(IDE_LOAD_RES_ERROR), 0);
   		return FALSE;
	}	

	// Lock Resource 
	MemFile = (BYTE*) LockResource(ResMemHandle);

	if (!MemFile)
	{
		BadResLoad( ResName, ResType, inst );
		// report error that file is not closed before destructor call
		Error::SetError(_R(IDE_LOAD_RES_ERROR), 0);
   		return FALSE;
	}	

	CurrentPos  	= 0;	
	FileSize		= (UINT32) SizeofResource(inst, hResource);

	// Check that SizeOfResource has worked
	if (FileSize == 0)
	{
		IsOpen = FALSE;
		Error::SetError(_R(IDE_RES_SIZE_ERROR), 0);
   		return FALSE;
	}

	FileProt		= fProt;

	// Prevent opening file in write mode for the present time
	if (FileProt == CCMemWrite)
	{
		IsOpen = FALSE;
		Error::SetError(_R(IDE_OPEN_WRITE), 0);
   		return FALSE;
	}

	IsOpen			= TRUE;

	return IsOpen; 
#endif
}

/********************************************************************************************

>	BOOL CCResourceFile::open(UINT32 ResourceId)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/12/94
	Inputs:		UINT32 - Resource ID of CUSTOM_RESOURCE that is needed to open (in read
				mode) as a file. The module instance is calculated from the ID.
	Returns: 	TRUE if file is opened successfully or FALSE otherwize
	Purpose:	Opens an instance of a CCResourceFile

********************************************************************************************/

BOOL CCResourceFile::open(ResourceID ResourceId)
{
	const TCHAR*		fn = CamResource::GetTextFail(ResourceId);
	return open( fn ? fn : CamResource::GetObjectName( ResourceId ), NULL, CCMemRead, NULL );
}

/********************************************************************************************

>	BOOL CCResourceFile::open(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/9/93
	Inputs:		UINT32 - Resource Identifier representing the Windows resource to be read in
				UINT32 - Resource Type - String Id representing the type of Camelot resource
				fProt - defines the files protection - default = read only
	Returns: 	TRUE if file is opened successfully or FALSE otherwize
	Purpose:	Opens an instance of a CCResourceFile

********************************************************************************************/


BOOL CCResourceFile::open(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt)
{
	// Load Resouce Name 
	String_256 ResNameID(ResourceId);

	// Load Resouce Type
	String_256 ResType(ResourceType);

	// use main function to do work
	return open( ResNameID, ResType, fProt );
}

/********************************************************************************************
										CCResTextFile
********************************************************************************************/

/********************************************************************************************

>	CCResTextFile::CCResTextFile(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Inputs:		UINT32 - Resource Identifier representing the Windows resource to be read in
				UINT32 - Resource Type - String Id representing the type of Camelot resource
				fProt - defines the files protection - default = read only
	Created:	9/9/93
	Purpose:	Constructs an instance of CCResTextFile and Opens it

********************************************************************************************/

CCResTextFile::CCResTextFile(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt)
 : CCResourceFile(ResourceId, ResourceType, fProt)
{
}

/********************************************************************************************

>	CCResTextFile::~CCResTextFile()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/93        
	Purpose:	Default destructor.

********************************************************************************************/

CCResTextFile::~CCResTextFile()
{                   
}

/********************************************************************************************

>	BOOL CCResTextFile::open(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/9/93
	Inputs:		UINT32 - Resource Identifier representing the Windows resource to be read in
				UINT32 - Resource Type - String Id representing the type of Camelot resource
				fProt - defines the files protection - default = read only
	Returns: 	TRUE if file is opened successfully or FALSE otherwize
	Purpose:	Opens an instance of a CCResTextFile

********************************************************************************************/

BOOL CCResTextFile::open(UINT32 ResourceId, UINT32 ResourceType, FileAccess fProt)
{
	return CCResourceFile::open(ResourceId, ResourceType, fProt);
}

BOOL CCResTextFile::open( UINT32 ResourceID )
{
	return CCResourceFile::open( ResourceID );
}

/********************************************************************************************

>	CCFile& CCResTextFile::read(TCHAR& buf)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/9/93
	Outputs;	character read in
	Return:		A reference to a memory file object
	Purpose:	Reads a single character from the Memory file 

********************************************************************************************/

CCFile& CCResTextFile::read(TCHAR& buf)
{
	// Make sure the file is open before it is read!
	if (!isOpen())
	{
		GotError(_R(IDE_NOTOPEN_ERROR));
		return (CCFile&) *this;
	}

    // if file is write protected then exit
    if (FileProt != CCMemRead)
    {
    	GotError(_R(IDE_WRITE_ONLY));
		return (CCFile&) *this;
	}

	char* tempResFile 	= (char*)MemFile;			// Cast MemFile to a TCHAR pointer

	if (!eof())
	{
#if FALSE != wxUSE_UNICODE
		mbtowc( &buf, tempResFile + CurrentPos, 1 );
#else
		buf = tempResFile[CurrentPos];
#endif
		++CurrentPos;
	}
	else
	{
		GotError(_R(IDE_EOF_ERROR));
	}

	return (CCFile&) *this;
}



/********************************************************************************************

>	CCFile& CCResTextFile::read(StringBase* buf)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com> & Mark Neves
	Created:	6/9/93 (updated 26/4/94 by MarkN)
	Inputs:		buf - the String object to place the characters in.
	Outputs:	buf - the characters read from the file.
	Returns:	Reference to the CCFile object.
	Purpose:	Read in a string from the file.  The read operation stops at the first
				newline, or when the string is full.  The newline is removed from the input
				stream.

********************************************************************************************/

CCFile& CCResTextFile::read(StringBase* buf)
{
	// Make sure the file is open before it is read!
	if (!isOpen())
	{
		GotError(_R(IDE_NOTOPEN_ERROR));
		return (CCFile&) *this;
	}

    // if file is write protected then exit
    if (FileProt != CCMemRead)
    {
    	GotError(_R(IDE_WRITE_ONLY));
		return (CCFile&) *this;
	}

	char* tempResFile 	= (char*) MemFile;			// Cast MemFile to a TCHAR pointer
	TCHAR* pString 		= *buf;						// Cast input string to a TCHAR pointer
	UINT32 i = 0;
	
	UINT32 Len = buf->MaxLength();

	// Added check for '\n' on 26/4/94 by MarkN

	while ((i <= Len) && (!eof()) && (tempResFile[CurrentPos] != '\n') && (tempResFile[CurrentPos] != '\r'))
 	{
#if FALSE != wxUSE_UNICODE
		mbtowc( pString, tempResFile + CurrentPos, 1 );
		++CurrentPos;
#else
		*pString = tempResFile[CurrentPos++];
#endif
		pString++;
		i++;
	}

	if ((tempResFile[CurrentPos] == '\n') || (tempResFile[CurrentPos] == '\r'))
	{
		CurrentPos++;

		// It is possible for the CR to be made up of a \r\n pair , so we have to look for this
		if ((!eof()) && ((tempResFile[CurrentPos] == '\n') || (tempResFile[CurrentPos] == '\r')))
		{
			CurrentPos++;
		}
	}
	
	*pString = 0;							// Added 26/4/94 by MarkN
	
	return (CCFile&) *this;
}


/********************************************************************************************

>	BOOL CCResTextFile::eof()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/93
	Return:		TRUE if end of file and FALSE otherwize
	Purpose:	Determines whether an instance of CCResTextFile is open

********************************************************************************************/

BOOL CCResTextFile::eof() const
{                                          
	char* tempResFile = (char*) MemFile;			// Cast MemFile to a char pointer

	// Changed the '==' to '>=' in the following check on CurrentPos (MarkN 9/5/94)

	if ((CurrentPos >= (FileSize - 1)) || (tempResFile[CurrentPos] == END_OF_FILE))
		return TRUE;
	else
		return FALSE;
}


/********************************************************************************************

>	void CCResTextFile::close()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/93
	Purpose:	Closes an instance of a CCResTextFile

********************************************************************************************/

void CCResTextFile::close()
{   
	CCResourceFile::close();
}

/********************************************************************************************
										CCClipBoardFile
********************************************************************************************/

/********************************************************************************************

>	CCClipBoardFile::CCClipBoardFile(FileAccess fProt)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Inputs:		fProt - defines the files protection - default = read only
	Created:	9/9/93
	Purpose:	Constructs an instance of CCClipBoardFile and Opens it

********************************************************************************************/

PORTNOTE("clipboard","Removed CCClipBoardFile - MSW clipboard usage")
#ifndef EXCLUDE_FROM_XARALX
CCClipBoardFile::CCClipBoardFile(FileAccess fProt)
{
	// Get Current Applications main window and apply the OpenClipboard() member 
	// function to it!
	((AfxGetApp())->m_pMainWnd)->OpenClipboard();
	
	FileProt	= fProt;

	if (FileProt == CCMemRead)
	{
		// Check to see if there is any text in the clipboard
		if (IsClipboardFormatAvailable(CF_TEXT))
   		{
			IsOpen = FALSE;
			Error::SetError(_R(IDE_EMPTY_CLIPBOARD), 0);
    	   	return;
    	}	

		// Get a handle to the clipboard data
		ClipBoardHandle = GetClipboardData(CF_TEXT);
	
		// Check if clipboard data could be found
		if (ClipBoardHandle == NULL)
	    {
			IsOpen = FALSE;
			Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
   	    	return;
	    }	
	
		// Get a pointer to the clipboard data
		MemFile	= (BYTE*) GlobalLock(ClipBoardHandle);
	       
		// Check if memory to be occupied by data was available
		if (MemFile == NULL)
	    {                  
	    	IsOpen = FALSE;
			Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
	       	return;
	    }	
	
		// Get the size of the data
		FileSize	= (UINT32) GlobalSize(ClipBoardHandle);
    }
    else if (FileProt == CCMemWrite)
    {
		// Empty Clipboard
		EmptyClipboard();

		// Allocate Global Memory 
		ClipBoardHandle = GlobalAlloc(GHND, (DWORD) CCFILE_DEFAULTSIZE);

		// Check if Memory was allocated properly
		if (ClipBoardHandle == NULL)
	    {
			IsOpen = FALSE;
			Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
   	    	return;
	    }	

		// Get a pointer to the clipboard
		MemFile	= (BYTE*) GlobalLock(ClipBoardHandle);
	       
		// Check if memory to be occupied by data was available
		if (MemFile == NULL)
	    {                  
	    	IsOpen = FALSE;
			Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
	       	return;
	    }	
	    
		// Set to default size.
	    FileSize = CCFILE_DEFAULTSIZE;
    } 
     
	CurrentPos  = 0;	
	IsOpen		= TRUE;
}

/********************************************************************************************

>	CCClipBoardFile::~CCClipBoardFile()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/93        
	Purpose:	Default destructor.

********************************************************************************************/

CCClipBoardFile::~CCClipBoardFile()
{                   
	CCMemFile::~CCMemFile();
	
	// if the file has been left open then unlock memory and close clipboard
	if (isOpen())
	{
		// Unlock memory allocated
		GlobalUnlock(ClipBoardHandle);
                   
		// Write to clipboard - ClipBoardHandle must be unlocked before given to clipboard
		SetClipboardData(CF_TEXT, ClipBoardHandle);                   
                   
		// Close the clipboard
		CloseClipboard();
	}
}

/********************************************************************************************

>	BOOL CCClipBoardFile::open(FileAccess fProt)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/9/93
	Inputs:		fProt - defines the files protection - default = read only
	Returns:	TRUE if file is opened ok and FALSE otherwize
	Purpose:	Constructs opens the clipboard for reading or writing.

********************************************************************************************/

BOOL CCClipBoardFile::open(FileAccess fProt)
{
	// Get Current Applications main window and apply the OpenClipboard() member 
	// function to it!
	((AfxGetApp())->m_pMainWnd)->OpenClipboard();
	
	FileProt	= fProt;

	if (FileProt == CCMemRead)
	{
		// Check to see if there is any text in the clipboard
		if (IsClipboardFormatAvailable(CF_TEXT))
   		{
			IsOpen = FALSE;
			Error::SetError(_R(IDE_EMPTY_CLIPBOARD), 0);
    	   	return FALSE;
    	}	

		// Get a handle to the clipboard data
		ClipBoardHandle = GetClipboardData(CF_TEXT);
	
		// Check if clipboard data could be found
		if (ClipBoardHandle == NULL)
	    {
			IsOpen = FALSE;
			Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
   	    	return FALSE;
	    }	
	
		// Get a pointer to the clipboard data
		MemFile	= (BYTE*) GlobalLock(ClipBoardHandle);
	       
		// Check if memory to be occupied by data was available
		if (MemFile == NULL)
	    {                  
	    	IsOpen = FALSE;
			Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
	       	return FALSE;
	    }	
	
		// Get the size of the data
		FileSize	= (UINT32) GlobalSize(ClipBoardHandle);
    }
    else if (FileProt == CCMemWrite)
    {
		// Empty Clipboard
		EmptyClipboard();

		// Allocate Global Memory 
		ClipBoardHandle = GlobalAlloc(GHND, (DWORD) CCFILE_DEFAULTSIZE);

		// Check if Memory was allocated properly
		if (ClipBoardHandle == NULL)
	    {
			IsOpen = FALSE;
			Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
   	    	return FALSE;
	    }	

		// Get a pointer to the clipboard
		MemFile	= (BYTE*) GlobalLock(ClipBoardHandle);
	       
		// Check if memory to be occupied by data was available
		if (MemFile == NULL)
	    {                  
	    	IsOpen = FALSE;
			Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
	       	return FALSE;
	    }	
	    
		// Set to default size.
	    FileSize = CCFILE_DEFAULTSIZE;
    } 
     
	CurrentPos  = 0;	
	IsOpen		= TRUE;
	
	return IsOpen;
}

/********************************************************************************************

>	BOOL CCClipBoardFile::GrowClipBoardFile()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/9/93
	Returns:	TRUE if File was increased ok and FALSE otherwize
	Purpose:	Increases the size of the file by the default size of 1k.

********************************************************************************************/

BOOL CCClipBoardFile::GrowClipBoardFile()
{                                                 
	//Increase File Size
	FileSize += CCFILE_DEFAULTSIZE;	
	
	// Unlock memory allocated
	GlobalUnlock(ClipBoardHandle);
                   
	// Allocate Global Memory 
	ClipBoardHandle = GlobalReAlloc(ClipBoardHandle, 
									(DWORD) FileSize,
									(GMEM_MOVEABLE | GMEM_ZEROINIT)
									);

	// Check if Memory was allocated properly
	if (ClipBoardHandle == NULL)
    {
		IsOpen = FALSE;
		Error::SetError(_R(IDE_REALLOC_ERROR), 0);
    	return FALSE;
    }	                                 
    
	// Get a pointer to the clipboard
	MemFile	= (BYTE*) GlobalLock(ClipBoardHandle);

	// Check if memory to be occupied by data was available
	if (MemFile == NULL)
    {                  
    	IsOpen = FALSE;
		Error::SetError(_R(IDE_LOAD_CLIPBOARD), 0);
       	return FALSE;
    }	

	return TRUE;
}

/********************************************************************************************

>	CCFile& CCClipBoardFile::read(TCHAR& buf)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/9/93
	Outputs;	character read in
	Return:		A reference to a memory file object
	Purpose:	Reads a single character from the Memory file 

********************************************************************************************/

CCFile& CCClipBoardFile::read(TCHAR& buf)
{
	// Make sure the file is open before it is read!
	if (!isOpen())
	{
		GotError(_R(IDE_NOTOPEN_ERROR));
		return (CCFile&) *this;
	}

	TCHAR* tempClipFile = (TCHAR*) MemFile;			// Cast MemFile to a TCHAR pointer

	if (!eof())
		buf = tempClipFile[CurrentPos++];
	else
	{
		GotError(_R(IDE_EOF_ERROR));
	}

	return (CCFile&) *this;
}

/********************************************************************************************

>	CCFile& CCClipBoardFile::read(StringBase* buf)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/93
	Inputs:		Length - is number of Bytes to be read in.
	Output:		The character string read in.
	Return:		A reference to CCClipBoardFile object
	Purpose:	Reads a stream of characters from the Memory file 

********************************************************************************************/

CCFile& CCClipBoardFile::read(StringBase* buf)
{
	// Make sure the file is open before it is read!
	if (!isOpen())
	{
		GotError(_R(IDE_NOTOPEN_ERROR));
		return (CCFile&) *this;
	}

	TCHAR* tempClipFile 	= (TCHAR*) MemFile;			// Cast MemFile to a TCHAR pointer
	TCHAR* pString 		= *buf;						// Cast input string to a TCHAR pointer
	UINT32 i = 0;
	
	UINT32 MaxLen = buf->MaxLength();

	while ((i <= MaxLen) && (!eof())) 	
	{
		*pString = tempClipFile[CurrentPos++];
		pString++;
		i++;
	}
	
	return (CCFile&) *this;
}


/********************************************************************************************

>	CCFile& CCClipBoardFile::write(const TCHAR& buf)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/9/93
	Inputs:		A pointer to a single char
	Return:		A reference to a clipboard file object
	Purpose:	Writes a single character to the Clipboard file 

********************************************************************************************/

CCFile& CCClipBoardFile::write(const TCHAR& buf)
{
	// Make sure the file is open before it is written!
	if (!isOpen())
	{
		GotError(_R(IDE_NOTOPEN_ERROR));
		return (CCFile&) *this;
	}

    // if file is read only then exit
    if (FileProt != CCMemWrite)
    {
    	GotError(_R(IDE_READ_ONLY));
		return (CCFile&) *this;
	}
    
    TCHAR* tempClipFile;
    
	// Cast pointer to memory file to TCHAR
    tempClipFile = (TCHAR*) MemFile;
    
	// if the file size limit is reached then increase memory file by default amount
	if (CurrentPos != (FileSize - 1)) 
		tempClipFile[CurrentPos++] = buf;
	else 
		if (GrowClipBoardFile())
			// write input byte
			tempClipFile[CurrentPos++] = buf;
				
	return (CCFile&) *this;
}

/********************************************************************************************

>	CCFile& CCClipBoardFile::write(const StringBase& buf, UINT32 length = 0)

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/9/93
	Inputs:		constant unicode string
				Length denotes number of bytes to written 
	Return:		A reference to a clipboard file object
	Purpose:	Writes a stream of characters to the ClipBoard file 

********************************************************************************************/

CCFile& CCClipBoardFile::write(const StringBase& buf, UINT32 length)
{                                      
	// Make sure the file is open before it is written!
	if (!isOpen())
	{
		GotError(_R(IDE_NOTOPEN_ERROR));
		return (CCFile&) *this;
	}

    // if file is read only then exit
    if (FileProt != CCMemWrite)
    {
    	GotError(_R(IDE_READ_ONLY));
		return (CCFile&) *this;
	}
    
	// Ensure that the length of the string to be written is not longer
	// than the string's maximum size
	if (length == 0)
		length = buf.Length();
	else if ((INT32) length > buf.MaxLength())
	{
		GotError(_R(IDE_STRING_SIZE_ERROR));
		return (CCFile&) *this;
	}

	const TCHAR* tempBuf = buf;
    TCHAR* tempClipFile;
    
	// Cast pointer to memory file to TCHAR
    tempClipFile = (TCHAR*) MemFile;

	for (UINT32 i = 0; (i <= length); i++)
	{
		// if the file size limit is reached then increase memory file by default amount
		if (CurrentPos != (FileSize - 1))
			tempClipFile[CurrentPos++] = *tempBuf++;
		else
			if (GrowClipBoardFile())
				// write input byte
				tempClipFile[CurrentPos++] = *tempBuf++;
			else
				break;
	}
	
	return (CCFile&) *this;
}


/********************************************************************************************

>	BOOL CCClipBoardFile::eof() const

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/93
	Return:		TRUE if end of file and FALSE otherwize
	Purpose:	Determines whether an instance of CCClipBoardFile is open

********************************************************************************************/

BOOL CCClipBoardFile::eof() const
{                                          
	TCHAR* tempClipFile = (TCHAR*) MemFile;				// Cast MemFile to a TCHAR pointer

	// Changed the '==' to '>=' in the following check on CurrentPos (MarkN 9/5/94)

	if ((CurrentPos >= (FileSize - 1)) || (tempClipFile[CurrentPos] == END_OF_FILE))
		return TRUE;
	else
		return FALSE;
}


/********************************************************************************************

>	void CCClipBoardFile::close()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/93
	Purpose:	Closes an instance of a CCClipBoardFile

********************************************************************************************/

void CCClipBoardFile::close()
{   
	IsOpen = FALSE;
		                         
	// Unlock memory allocated
	GlobalUnlock(ClipBoardHandle);
                   
	// Write to clipboard - ClipBoardHandle must be unlocked before given to clipboard
	SetClipboardData(CF_TEXT, ClipBoardHandle);                   
                   
	// Close the clipboard
	CloseClipboard();
}

#endif
