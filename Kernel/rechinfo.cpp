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


// Implementation of the colour record handler class of the v2 file format

#include "camtypes.h"

#include "rechinfo.h"	// DocInfoRecordHandler for importing doc info from v2 native/web files
#include "infocomp.h"	// Document info component, handles import of document information
#include "cxftags.h"	// TAG_DOCUMENTCOMMENT

//#include "localenv.h"	// LocalEnvironment

DECLARE_SOURCE("$Revision: 1688 $");

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_DYNAMIC(DocInfoRecordHandler,CamelotRecordHandler);

// #if NEW_NATIVE_FILTER	// New native filters, only available to those who need them at present

/********************************************************************************************

>	virtual BOOL DocInfoRecordHandler::BeginImport()

 	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96
	Inputs:		-
	Returns:	TRUE if ok
				FALSE otherwise
	Purpose:	Initialises the units record handler
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL DocInfoRecordHandler::BeginImport()
{
	pInfoComponent = GetDocInfoComponent();

	return (pInfoComponent != NULL);
}

/********************************************************************************************

>	virtual UINT32* DocInfoRecordHandler::GetTagList()

 	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96
	Inputs:		-
	Returns:	Ptr to a list of tag values, terminated by CXFRH_TAG_LIST_END
	Purpose:	Provides the record handler system with a list of records handled by this
				handler
	SeeAlso:	-

********************************************************************************************/

UINT32* DocInfoRecordHandler::GetTagList()
{
	static UINT32 TagList[] = {TAG_DOCUMENTCOMMENT, TAG_DOCUMENTDATES,
							  TAG_DOCUMENTUNDOSIZE,
							  TAG_DOCUMENTFLAGS,
							  CXFRH_TAG_LIST_END};

	return (UINT32*)&TagList;
}

/********************************************************************************************

>	virtual BOOL DocInfoRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)

 	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96
	Inputs:		pCXaraFileRecord = ptr to record to handle
	Returns:	TRUE if handled successfuly
				FALSE otherwise
	Purpose:	Handles the given record.
	SeeAlso:	-

********************************************************************************************/

BOOL DocInfoRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)
{
	ERROR2IF(pCXaraFileRecord == NULL,FALSE,"DocInfoRecordHandler::HandleRecord pCXaraFileRecord is NULL");

	BOOL ok = TRUE;
	Document * pDoc = GetDocument();
	INT32 Tag = pCXaraFileRecord->GetTag();
	if (pInfoComponent == NULL)
	{
		ERROR3("DocInfoRecordHandler::HandleRecord no pInfoComponent");
		return FALSE;
	}

	// If we are just importing data from this document into an existing one,
	// then don't import any of this data.
	if (IsImporting())
		return TRUE;

	switch (Tag)
	{
		case TAG_DOCUMENTCOMMENT:
			// Ask the document information component class to import that data for us
			pInfoComponent->ImportDocumentComment(pCXaraFileRecord, pDoc);
			break;

		case TAG_DOCUMENTDATES:
			// Ask the document information component class to import that data for us
			pInfoComponent->ImportDocumentDates(pCXaraFileRecord, pDoc);
			break;

		case TAG_DOCUMENTUNDOSIZE:
			// Ask the document information component class to import that data for us
			pInfoComponent->ImportUndoBufferSize(pCXaraFileRecord, pDoc);
			break;

		case TAG_DOCUMENTFLAGS:
			// Ask the document information component class to import that data for us
			pInfoComponent->ImportDocumentFlags(pCXaraFileRecord, pDoc);
			break;

		default:
			ok = FALSE;
			ERROR3_PF(("DocInfoRecordHandler::HandleRecord I don't handle records with the tag (%d)\n",Tag));
			break;
	}

	return ok;
}

/********************************************************************************************

>	virtual void DocInfoRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96
	Inputs:		pRecord = ptr to a record
				pStr = ptr to string to update
	Returns:	-
	Purpose:	This provides descriptions for the define units records.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

#ifdef XAR_TREE_DIALOG
void DocInfoRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase* pStr)
{
	if (pStr == NULL || pRecord == NULL)
		return;

	// Call base class first
	// This outputs the tag and size
	CamelotRecordHandler::GetRecordDescriptionText(pRecord, pStr);

	UINT32 Tag = pRecord->GetTag();
	BOOL ok = TRUE;
//	INT32 RecordNumber = pRecord->GetRecordNumber();
	switch (Tag)
	{
		case TAG_DOCUMENTCOMMENT:
		{
			String_256 Comment;
			if (ok) ok = pRecord->ReadUnicode(&Comment);//Comment, Comment.MaxLength());
			if (Comment.Length() == 0)
				(*pStr) += _T("None\r\n\r\n");
			else
			{
				(*pStr) += _T("Comment:- \r\n");
				(*pStr) += Comment;
				(*pStr) += _T("\r\n\r\n");
			}

			break;
		}

		case TAG_DOCUMENTDATES:
		{
#if FALSE
			// Read in the times/dates from the record
			time_t Creation;
			time_t LastSaved;

			if (ok) ok = pRecord->ReadINT32((INT32*)&Creation);
			if (ok) ok = pRecord->ReadINT32((INT32*)&LastSaved);
			
#if !defined(EXCLUDE_FROM_RALPH)
			String_256 String;
			(*pStr) += _T("Document created:- \t");
			LocalEnvironment::SystemTimeToString(&String, &Creation);
			(*pStr) += String;
			(*pStr) += _T("\t");
			LocalEnvironment::SystemDateToString(&String, &Creation);
			(*pStr) += String;
			(*pStr) += _T("\r\n\r\n");
			(*pStr) += _T("Document last saved:- \t");
			LocalEnvironment::SystemTimeToString(&String, &LastSaved);
			(*pStr) += String;
			(*pStr) += _T("\t");
			LocalEnvironment::SystemDateToString(&String, &LastSaved);
			(*pStr) += String;
			(*pStr) += _T("\r\n\r\n");
#endif
#endif
			break;
		}

		case TAG_DOCUMENTUNDOSIZE:
		{
			UINT32 UndoBufSize = 0;
			if (ok) ok = pRecord->ReadUINT32(&UndoBufSize);
			if (UndoBufSize == UINT32_MAX)
			{
				(*pStr) += _T("Undo buffer size: \t= unlimited\r\n");
			}
			else
			{
				(*pStr) += _T("Undo buffer size:- ");
				String_256 Value;
				Convert::BytesToString(&Value, UndoBufSize);
				(*pStr) += Value;
				(*pStr) += _T("\r\n\r\n");
			}
			break;
		}

		case TAG_DOCUMENTFLAGS:
		{
			UINT32 DocFlags = 0;
			if (ok) ok = pRecord->ReadUINT32(&DocFlags);
			(*pStr) += _T("Document flags which are currently set are:- \r\n");
			if (DocFlags & 2)
				(*pStr) += _T("Multilayer ");
			if (DocFlags & 1)
				(*pStr) += _T("AllLayersVisible ");
			(*pStr) += _T("\r\n\r\n");
			break;
		}
	} 

	return;
}

#endif // _DEBUG

// #endif // NEW_NATIVE_FILTER

