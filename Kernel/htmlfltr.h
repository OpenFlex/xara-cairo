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



#ifndef INC_HTMLFILTERS
#define INC_HTMLFILTERS


// include
#include "textfltr.h"
#include "htmllist.h"


/********************************************************************************************
>	class HTMLFilter : public BaseTextFilter

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/03/97
	Purpose:	A filter for html file, recognise only tags containing bitmaps
	SeeAlso:	BaseTextFilter
********************************************************************************************/

class HTMLFilter : public BaseTextFilter
{
	CC_DECLARE_DYNAMIC(HTMLFilter)

public:
	HTMLFilter();
	~HTMLFilter();

	INT32 Init();
	// Initialise some member variables
	//BOOL Init1();
	// free memory used by member variables
	//BOOL DeInit1();

	// Function called before HowCompatible so that filters have a chance to do
	// something, if required. Baseclass version is present but does nothing.
	// Therefore, only needs to be overridden by a filter or set of filters which requires it.
	virtual BOOL PreHowCompatible();

	// HowCompatible() returns value in range 0 to 10:
	//   0 => "Definitely Not"
	//  10 => "Yes Sir, that's my file format"
	virtual INT32 HowCompatible(	PathName& Filename, 
								ADDR  HeaderStart, 
								UINT32 HeaderSize,
								UINT32 FileSize );

	virtual BOOL DoImport(SelOperation*, CCLexFile*, Document*, 
						  BOOL AutoChosen = FALSE, ImportPosition *Pos = NULL,
						  KernelBitmap** ppImportedBitmap = NULL,
						  DocCoord* pPosTranslate = NULL, String_256* URL=NULL);

	//BOOL ScanListAndImport(HTMLFileList* HTMLList, CCLexFile* pFile, SelOperation *Op, Document *DestDoc);
	BOOL ScanListAndImport(HTMLFileList* HTMLList, String_256* Address, Document *DestDoc, SelOperation *Op, PathName pthImportFile);
	static BOOL DoImportBitmap(HTMLTAG_TYPE TagId, SelOperation *Op, Document *DestDoc, 
								PathName Path, INT32 FileNum, INT32 FileNumber, 
								DocCoord& PosTranslate, BOOL IsCentre, String_256* NewName);

	static BOOL ImportBitmap(SelOperation *Op, PathName &Path,
							KernelBitmap** ppImportedBitmap,
							DocCoord* pPosTranslate, INT32 FileNum, 
							INT32 FileNumber, String_256* NewName);

	BOOL ParseHTMLFile(CCLexFile* pFile, HTMLFileList* HTMLList);
	BOOL GetTag(TCHAR*, TCHAR*, const TCHAR* TokenBuffer);
	BOOL GetAttribute(const TCHAR* AttrName, const TCHAR*, TCHAR*);
	TCHAR* SearchStr(const char* A, const char* B);

	virtual BOOL IsDefaultDocRequired(const TCHAR* pcszPathName) { return TRUE; }

	// unused
	virtual BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL) { return TRUE; }

public:
	//This variable is set to TRUE when we import a bitmap as part of an HTML document
	static BOOL ImportingHTML;
	
protected:
	//Graham 5/6/97: Calculates the Nth position at which to import a bitmap
	DocCoord GetImportPosition(Document* pdocTarget, INT32 iPosNum);

protected:
	String_256 m_WarningsString;
};


#endif	//INC_HTMLFILTERS
