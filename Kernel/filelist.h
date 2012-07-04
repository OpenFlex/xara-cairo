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

// The Opdescriptors for the Recent File Liat

#ifndef INC_FILELIST
#define INC_FILELIST

//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]


#define OPTOKEN_MRU_FILE1	_T("01MRUFile")
#define OPTOKEN_MRU_FILE2	_T("02MRUFile")
#define OPTOKEN_MRU_FILE3	_T("03MRUFile")
#define OPTOKEN_MRU_FILE4	_T("04MRUFile")
#define OPTOKEN_MRU_FILE5	_T("05MRUFile")
#define OPTOKEN_MRU_FILE6	_T("06MRUFile")
#define OPTOKEN_MRU_FILE7	_T("07MRUFile")
#define OPTOKEN_MRU_FILE8	_T("08MRUFile")
#define OPTOKEN_MRU_FILE9	_T("09MRUFile")

/********************************************************************************************

>	class DocOps : public Operation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/1/95
	Purpose:	This operation handles all the Recent file list menu options
	SeeAlso:	Operation

********************************************************************************************/

class FileListOp : public Operation
{                           
	CC_DECLARE_DYNCREATE(FileListOp)

public:
	// Construction / initialisation
	FileListOp();
	static BOOL	Init();

	// Read the state of the operation
	static OpState GetState(String_256*, OpDescriptor*);		

	// function that does the work
	void Do(OpDescriptor*);

public:
	// A var that will be a preference. It holds how many menu items should be displayed
	static INT32 MaxFileListSize;
};

#endif  // INC_FILELIST

