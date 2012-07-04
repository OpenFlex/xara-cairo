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


// The units record handler for native and web files.

#ifndef INC_DOCINFORECORDHANDLER
#define INC_DOCINFORECORDHANDLER

class DocInfoComponent;

// Header for the attribute record handling classes for the v2 file format
//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CXaraFileRecord;

/********************************************************************************************

>	class DocInfoRecordHandler : public CamelotRecordHandler

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96
	Purpose:	Provide a units record handler for the new native and web file formats.
				This asks the units document component to import the unit definitions
				for us.
	SeeAlso:	UnitListDocComponent;

********************************************************************************************/

class DocInfoRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(DocInfoRecordHandler);

public:
	DocInfoRecordHandler() : CamelotRecordHandler() {}
	~DocInfoRecordHandler() {}

	virtual BOOL BeginImport();

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
#endif

protected:
	// We will be using the document info component class to handle the importing of
	// document information, so we must keep a pointer to it.
	DocInfoComponent * pInfoComponent;	
};

#endif  // INC_DOCINFORECORDHANDLER
