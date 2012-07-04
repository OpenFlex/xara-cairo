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

// The printer/imagesetting settings record handler for native and web files.

#ifndef INC_RECHPRNT
#define INC_RECHPRNT

// Header for the attribute record handling classes for the v2 file format
//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CXaraFileRecord;
class PrintComponent;
class PrintMarksComponent;
class StringBase;


/********************************************************************************************

>	class PrintingRecordHandler : public CamelotRecordHandler

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/8/96

	Purpose:	Handles importing of the print options records:
					TAG_PRINTERSETTINGS
					TAG_IMAGESETTING
					TAG_COLOURPLATE

	SeeAlso:	PrintComponent

********************************************************************************************/

class PrintingRecordHandler : public CamelotRecordHandler
{
	CC_DECLARE_DYNAMIC(PrintingRecordHandler);

public:
	PrintingRecordHandler() : CamelotRecordHandler() { pPrintComponent = NULL; pPrintMarksComponent = NULL; }
	~PrintingRecordHandler() {}

public:
	virtual BOOL BeginImport();

	virtual UINT32 *GetTagList();
	virtual BOOL HandleRecord(CXaraFileRecord* pCXaraFileRecord);

	virtual BOOL BeginSubtree(UINT32 Tag);
	virtual BOOL EndSubtree(UINT32 Tag);


#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord *pCXaraFileRecord, StringBase *Str);
#endif

private:
	PrintComponent		*pPrintComponent;
	PrintMarksComponent	*pPrintMarksComponent;
};

#endif  // INC_RECHPRNT
