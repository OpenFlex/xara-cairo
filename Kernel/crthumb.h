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


// The operation for the "Import from URL..." menu item

#ifndef INC_CREATEFONTTHUMBNAILS
#define INC_CREATEFONTTHUMBNAILS

//#include "ops.h" //class Operation - in camtypes.h [AUTOMATICALLY REMOVED]

class SGDisplayPreviewFonts;

/********************************************************************************************

>	class OpCreateFontThumbnails : public OpMenuImport

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/6/97
	Purpose:	The "Create Font Thumbnails" debug command
	SeeAlso:	-
	Notes:		Karim 08/12/00	modified to use SGDisplayPreviewFonts instead of just TTF.

********************************************************************************************/

#define	OPTOKEN_CREATEFONTTHUMBNAILS _T("CreateFontThumbnails")

class OpCreateFontThumbnails : public Operation
{
	CC_DECLARE_DYNCREATE(OpCreateFontThumbnails)

public:
	OpCreateFontThumbnails();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

	//Toolkit functions
protected:
	void CreateThumbnailFiles(SGDisplayPreviewFonts* pFontItem, INT32 lFontID, PathName pthIndex);
	SGDisplayPreviewFonts* FindFontFromName(String_256& strName);

};

#define	OPTOKEN_CONVERTFILEFORMATS _T("ConvertFileFormats")



/********************************************************************************************

>	class OpConvertFileFormats : public Operation

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/8/2000
	Purpose:	The "Convert File Formats" debug command
	SeeAlso:	-

********************************************************************************************/

class OpConvertFileFormats : public Operation
{
	CC_DECLARE_DYNCREATE(OpConvertFileFormats)

public:
	OpConvertFileFormats();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
	static BOOL IsActive () { return (active); }
protected:
	static BOOL active;
};

#endif // INC_CREATEFONTTHUMBNAILS
