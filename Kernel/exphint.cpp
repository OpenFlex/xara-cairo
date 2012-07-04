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


/*
*/

#include "camtypes.h"
#include "exphint.h"

//#include "cxfrec.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "cxftags.h"
//#include "filtrres.h"

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_MEMDUMP(ExportHint, CC_CLASS_MEMDUMP);
CC_IMPLEMENT_DYNAMIC(ExportHintRecordHandler, CamelotRecordHandler);

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	ExportHint::ExportHint()

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Purpose:	Default constructor
	SeeAlso:	-

********************************************************************************************/

ExportHint::ExportHint()
{
	m_Type = HINTTYPE_BAD;
	m_Width = 0;
	m_Height = 0;
	m_BPP = 0;

	// The contructor of the string should ensure this but...
	m_sOptions.Empty();
}


/********************************************************************************************

>	ExportHint::ExportHint(const ExportHint& other)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Purpose:	Copy constructor
	SeeAlso:	-

********************************************************************************************/

ExportHint::ExportHint(const ExportHint& other)
{
	// Use the assignment operator
	*(this) = other;
}


/********************************************************************************************

>	const ExportHint& ExportHint::operator=(const ExportHint& other)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Purpose:	Assignment operator
	SeeAlso:	-

********************************************************************************************/

const ExportHint& ExportHint::operator=(const ExportHint& other)
{
	m_Type = other.m_Type;
	m_Width = other.m_Width;
	m_Height = other.m_Height;
	m_BPP = other.m_BPP;
	m_sOptions = other.m_sOptions;

	return(*this);
}



/********************************************************************************************

>	BOOL ExportHint::InitFromRecord(CXaraFileRecord* pRecord)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Purpose:	Initialises the hint from a Flare record
	SeeAlso:	-

********************************************************************************************/

BOOL ExportHint::InitFromRecord(CXaraFileRecord* pRecord)
{
	String_256 sOptions;

	BOOL ok = pRecord->ReadUINT32(&m_Type);
	if (ok) ok = pRecord->ReadUINT32(&m_Width);
	if (ok) ok = pRecord->ReadUINT32(&m_Height);
	if (ok) ok = pRecord->ReadUINT32(&m_BPP);
	if (ok) ok = pRecord->ReadASCII(sOptions, 256);

	m_sOptions = sOptions;

	return(ok);
}



/********************************************************************************************

>	BOOL ExportHint::WriteExportHintRecord(BaseCamelotFilter* pFilter)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Purpose:	Writes the hint to a Flare record
	SeeAlso:	-

********************************************************************************************/

BOOL ExportHint::WriteExportHintRecord(BaseCamelotFilter* pFilter)
{
	// If the hint hasn't been set then don't save it
	if (m_Type == HINTTYPE_BAD)
		return(TRUE);
	
	// Add a description of the TAG_EXPORT_HINT record
	pFilter->AddTagDescription(TAG_EXPORT_HINT, _R(IDS_TAG_EXPORT_HINT));

	BOOL ok = TRUE;
	// Create a record (variable length)
	CXaraFileRecord Rec(TAG_EXPORT_HINT);
	ok = Rec.Init();

	if (ok) ok = Rec.WriteUINT32(m_Type);
	if (ok) ok = Rec.WriteUINT32(m_Width);
	if (ok) ok = Rec.WriteUINT32(m_Height);
	if (ok) ok = Rec.WriteUINT32(m_BPP);
	if (ok) ok = Rec.WriteASCII(m_sOptions);

	INT32 RecNum = 0;
	if (ok) RecNum = pFilter->Write(&Rec);	// Write the record
	if (RecNum == 0)
		ok = FALSE;

	return(ok);
}


/********************************************************************************************

>	virtual UINT32* ExportHintRecordHandler::GetTagList()

 	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Returns:	Ptr to a list of tag values, terminated by CXFRH_TAG_LIST_END
	Purpose:	Provides the record handler system with a list of records handled by this
				handler

********************************************************************************************/

UINT32* ExportHintRecordHandler::GetTagList()
{
	static const UINT32 TagList[] = {TAG_EXPORT_HINT, CXFRH_TAG_LIST_END};

	return (UINT32*)&TagList;
}


/********************************************************************************************

>	virtual BOOL ExportHintRecordHandler::HandleRecord(CXaraFileRecord* pRecord)

 	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Inputs:		pCXaraFileRecord = ptr to record to handle
	Returns:	TRUE if handled successfuly
				FALSE otherwise

********************************************************************************************/

BOOL ExportHintRecordHandler::HandleRecord(CXaraFileRecord* pRecord)
{
	ERROR2IF(pRecord == NULL, FALSE, "pCXaraFileRecord is NULL");
	ERROR2IF(pRecord->GetTag() != TAG_EXPORT_HINT, FALSE, "I don't handle this tag type");

	BaseCamelotFilter* const pFilter = GetBaseCamelotFilter();
	ERROR2IF(pFilter == NULL, FALSE, "No filter in ExportHint::HandleRecord");

	Document* pDocument = pFilter->GetDocument();
	ERROR2IF(pDocument == NULL, FALSE, "No Document in ExportHint::HandleRecord");

	ExportHint* pHint = pDocument->GetExportHint();	
	ERROR2IF(pHint == NULL, FALSE, "No ExportHint in ExportHint::HandleRecord");

	return(pHint->InitFromRecord(pRecord));
}


#ifdef XAR_TREE_DIALOG
/********************************************************************************************

>	virtual void ExportHintRecordHandler::GetRecordDescriptionText(
											CXaraFileRecord* pRecord, StringBase* pStr)
	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Inputs:		pRecord - ptr to a record
				pStr - ptr to string to update
	Purpose:	Provides descriptve text for debug dialog

********************************************************************************************/

void ExportHintRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr)
{
	if (pStr == NULL || pRecord == NULL)
	{
		TRACE( _T("ExportHintRecordHandler::GetRecordDescriptionText - NULL Args\n"));
		return;
	}
	if (pRecord->GetTag() != TAG_EXPORT_HINT)
	{
		TRACE( _T("ExportHintRecordHandler::GetRecordDescriptionText - Incorrect record\n"));
		return;
	}

	//	 Call base class first
	CamelotRecordHandler::GetRecordDescriptionText(pRecord, pStr);

	UINT32 Type;
	UINT32 Width;
	UINT32 Height;
	UINT32 BPP;
	String_256 sOptions;
	String_16 sNumber;

	BOOL ok = pRecord->ReadUINT32(&Type);
	if (ok) ok = pRecord->ReadUINT32(&Width);
	if (ok) ok = pRecord->ReadUINT32(&Height);
	if (ok) ok = pRecord->ReadUINT32(&BPP);
	if (ok) ok = pRecord->ReadASCII(sOptions, 256);

	if (ok)
	{
		*pStr += TEXT("Type = ");
		ok = Convert::LongToString(Type, &sNumber);
		if (ok) *pStr += sNumber;
		if (ok) *pStr += _T("\r\n");
	}
	if (ok)
	{
		*pStr += TEXT("Width = ");
		ok = Convert::LongToString(Width, &sNumber);
		if (ok) *pStr += sNumber;
		if (ok) *pStr += _T("\r\n");
	}
	if (ok)
	{
		*pStr += TEXT("Height = ");
		ok = Convert::LongToString(Height, &sNumber);
		if (ok) *pStr += sNumber;
		if (ok) *pStr += _T("\r\n");
	}
	if (ok)
	{
		*pStr += TEXT("BPP = ");
		ok = Convert::LongToString(BPP, &sNumber);
		if (ok) *pStr += sNumber;
		if (ok) *pStr += _T("\r\n");
	}
	if (ok)
	{
		*pStr += TEXT("Options = ");
		if (ok) *pStr += sOptions;
		if (ok) *pStr += _T("\r\n");
	}
}


/********************************************************************************************

>	virtual void ExportHintRecordHandler::GetTagText(UINT32 Tag,String_256& Str)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Inputs:		Tag	- the tag value
	Outputs:	Str - place to put textual description of the tag
	Purpose:	Returns the tag description in the string

********************************************************************************************/

void ExportHintRecordHandler::GetTagText(UINT32 Tag, String_256& Str)
{
	Str = TEXT("TAG_EXPORT_HINT");
}
#endif	// _DEBUG
