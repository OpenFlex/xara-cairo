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


// The document component for the document's unit list.

#ifndef INC_DOCINFOCOMP
#define INC_DOCINFOCOMP

//#include "doccomp.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class BaseCamelotFilter;
class CXaraFileRecord;

/********************************************************************************************

>	class DocInfoComponentClass : public DocComponentClass

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/07/96
	Purpose:	Provide a class that will add document information components to new documents.
	SeeAlso:	DocComponentClass

********************************************************************************************/

class DocInfoComponentClass : public DocComponentClass
{
	CC_DECLARE_DYNAMIC(DocInfoComponentClass)

public:
	static BOOL Init();

	BOOL AddComponent(BaseDocument *);
};

/********************************************************************************************

>	class DocInfoComponent : public DocComponent

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/07/96
	Purpose:	Provide a component that allows	us to save out the information for this document
				using the serialisation facilities of the DocComponent base class.
	SeeAlso:	DocComponent

********************************************************************************************/

class DocInfoComponent : public DocComponent
{
	CC_DECLARE_DYNAMIC(DocInfoComponent)

public:
	DocInfoComponent();
	virtual ~DocInfoComponent();

public:
	// Usual document component functions...

	// These are the Camelot Version 2 Web and Native file related functions
	virtual BOOL StartImport(BaseCamelotFilter *pFilter);
	virtual BOOL EndImport(BaseCamelotFilter *pFilter, BOOL Success);
	virtual BOOL StartExportBeforeComp(BaseCamelotFilter *pFilter);
	virtual BOOL StartExport(BaseCamelotFilter *pFilter);
	virtual BOOL EndExport(BaseCamelotFilter *pFilter, BOOL Success);

	BOOL ImportDocumentComment(CXaraFileRecord* pCXaraFileRecord, Document * pDoc);
	BOOL ImportDocumentDates(CXaraFileRecord* pCXaraFileRecord, Document * pDoc);
	BOOL ImportUndoBufferSize(CXaraFileRecord* pCXaraFileRecord, Document * pDoc);
	BOOL ImportDocumentFlags(CXaraFileRecord* pCXaraFileRecord, Document * pDoc);

private:
	BOOL ExportDocumentComment(BaseCamelotFilter *pFilter, Document * pDoc);
	BOOL ExportDocumentDates(BaseCamelotFilter *pFilter, Document * pDoc);
	BOOL ExportUndoBufferSize(BaseCamelotFilter *pFilter, Document * pDoc);
	BOOL ExportDocumentFlags(BaseCamelotFilter *pFilter, Document * pDoc);
};

#endif  // INC_DOCINFOCOMP


