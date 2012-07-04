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

#include "rechcomp.h"	// CompressionRecordHandler for handling compression for v2 native/web files

#if !defined(EXCLUDE_FROM_XARLIB)
#include "colcomp.h"	// Document colour component, handles import of colours
//#include "camfiltr.h"	// BaseCamelotFilter - version 2 native filter - in camtypes.h [AUTOMATICALLY REMOVED]
#endif

#include "cxftags.h"	// TAG_DEFINERGBCOLOUR TAG_DEFINECOMPLEXCOLOUR
//#include "cxfrec.h"		// TAG_STARTCOMPRESSION TAG_STOPCOMPRESSION - in camtypes.h [AUTOMATICALLY REMOVED]

DECLARE_SOURCE("$Revision: 1688 $");

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_DYNAMIC(CompressionRecordHandler,CamelotRecordHandler);

//#if NEW_NATIVE_FILTER	// New native filters, only available to those who need them at present

/********************************************************************************************

>	virtual UINT32* CompressionRecordHandler::GetTagList()

 	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/96
	Inputs:		-
	Returns:	Ptr to a list of tag values, terminated by CXFRH_TAG_LIST_END
	Purpose:	Provides the record handler system with a list of records handled by this
				handler
	SeeAlso:	-

********************************************************************************************/

UINT32* CompressionRecordHandler::GetTagList()
{
	static UINT32 TagList[] = {TAG_STARTCOMPRESSION, TAG_ENDCOMPRESSION, CXFRH_TAG_LIST_END};

	return (UINT32*)&TagList;
}

/********************************************************************************************

>	virtual BOOL CompressionRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)

 	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/96
	Inputs:		pCXaraFileRecord = ptr to record to handle
	Returns:	TRUE if handled successfuly
				FALSE otherwise
	Purpose:	Handles the given record.
	SeeAlso:	-

********************************************************************************************/

BOOL CompressionRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)
{
	ERROR2IF(pCXaraFileRecord == NULL,FALSE,"CompressionRecordHandler::HandleRecord pCXaraFileRecord is NULL");
	
	// This should be unused and we should error if this is called
	ERROR2(FALSE,"CompressionRecordHandler::HandleRecord called! Use Streamed form instead");
	
	BOOL ok = TRUE;

	switch (pCXaraFileRecord->GetTag())
	{
		case TAG_STARTCOMPRESSION:
			// Ask the compression system to be turned on
			TRACEUSER( "Neville", _T("Turn compression on\n"));
			ok = SetCompression(TRUE);
			break;
		case TAG_ENDCOMPRESSION:
			// Ask the compression system to be turned off
			TRACEUSER( "Neville", _T("Turn compression on\n"));
			ok = SetCompression(FALSE);
			break;

		default:
			ok = FALSE;
			ERROR3_PF(("CompressionRecordHandler::HandleRecord I don't handle records with the tag (%d)\n",pCXaraFileRecord->GetTag()));
			break;
	}

	return ok;
}

/********************************************************************************************

>	virtual BOOL CompressionRecordHandler::HandleStreamedRecord(CXaraFile * pCXFile, UINT32 Tag,UINT32 Size,UINT32 RecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/6/96
	Inputs:		pCXFile = access to the CXaraFile class 
				Tag	 = the tag value
				Size = size of record
				RecordNumber = the record number in the file
	Returns:	TRUE if handled ok
				FALSE otherwise
	Purpose:	This is the streamed record handler. It is used when 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL CompressionRecordHandler::HandleStreamedRecord(CXaraFile * pCXFile, UINT32 Tag,UINT32 Size,UINT32 RecordNumber)
{
	ERROR2IF(Tag <= 0,FALSE,"CompressionRecordHandler::HandleStreamedRecord Tag is negative!");
	
	BOOL ok = TRUE;

	switch (Tag)
	{
		case TAG_STARTCOMPRESSION:
			// Ask the compression system to be turned on
			TRACEUSER( "Neville", _T("Turn compression on\n"));
			ok = SetCompression(TRUE);
			break;
		case TAG_ENDCOMPRESSION:
			// Ask the compression system to be turned off
			TRACEUSER( "Neville", _T("Turn compression off\n"));
			ok = SetCompression(FALSE);
			break;

		default:
			ok = FALSE;
			ERROR3_PF(("CompressionRecordHandler::HandleStreamedRecord I don't handle records with the tag (%d)\n",Tag));
			break;
	}

	return ok;
}


/********************************************************************************************

>	virtual BOOL CompressionRecordHandler::IsStreamed(UINT32 Tag)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/6/96
	Inputs:		The tag of the record
	Returns:	TRUE if this is a streamed record
				FALSE otherwise
	Purpose:	Function to find out if the record is streamed or not.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL CompressionRecordHandler::IsStreamed(UINT32 Tag)
{
	// We don't want these records read in or handled by any outsiders as the ZLib code
	// reads things like the CRC and uncompressed size itself when compression is stopped
	return TRUE;
}


/********************************************************************************************

>	virtual void CompressionRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/6/96
	Inputs:		pRecord = ptr to a record
				pStr = ptr to string to update
	Returns:	-
	Purpose:	This provides descriptions for the compression on and off records.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

#ifdef XAR_TREE_DIALOG
void CompressionRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr)
{
	if (pStr == NULL || pRecord == NULL)
		return;

	// Call base class first
	// This outputs the tag and size
	CamelotRecordHandler::GetRecordDescriptionText(pRecord,pStr);

	UINT32 Tag = pRecord->GetTag();
	TCHAR s[256];
	switch (Tag)
	{
		case TAG_STARTCOMPRESSION:
		{
			// Show what a compression on record looks like
			// Read the version number
			UINT32 Version = 0L;
			pRecord->ReadUINT32(&Version);
			
			UINT32 Type = 0L;
			UINT32 MajorVersion = Version / 100;
			UINT32 MinorVersion = Version - MajorVersion * 100;
			camSprintf(s,_T("Compression type\t= %d\r\n"),Type);
			(*pStr) += s;
			camSprintf(s,_T("Compression version\t= %d.%d\r\n"),MajorVersion,MinorVersion);
			(*pStr) += s;
			break;
		}
		case TAG_ENDCOMPRESSION:
		{
			// Show what a compression off record looks like
			// Read the number of bytes read 
			UINT32 Checksum = 0L;
			pRecord->ReadUINT32(&Checksum);
			camSprintf(s,_T("Compression checksum\t= %d\r\n"),Checksum);
			(*pStr) += s;
			UINT32 BytesRead = 0L;
			pRecord->ReadUINT32(&BytesRead);
			camSprintf(s,_T("Compression bytes read\t= %d\r\n"),BytesRead);
			(*pStr) += s;
			break;
		}
	}

	return;
}
#endif

//#endif // NEW_NATIVE_FILTER

