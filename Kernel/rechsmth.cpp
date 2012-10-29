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


// Handles the reading of bitmap properties records

#include "camtypes.h"

#include "rechsmth.h"	// BitmapSmoothingRecordHandler for importing bitmaps from v2 native/web files
#include "bmpcomp.h"	// Document bitmap component, handles import of bitmaps
#include "cxfile.h"		// CXaraFile file handling class for version 2 native filter 
#include "cxftags.h"	// TAG_DEFINEBITMAP_**** 
//#include "sgliboil.h"	// Wav stuff



// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_DYNAMIC(BitmapSmoothingRecordHandler,CamelotRecordHandler);


/********************************************************************************************

>	virtual UINT32* BitmapSmoothingRecordHandler::GetTagList()

 	Author:		Andy_Hills (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/00
	Inputs:		-
	Returns:	Ptr to a list of tag values, terminated by CXFRH_TAG_LIST_END
	Purpose:	Provides the record handler system with a list of records handled by this
				handler
	SeeAlso:	-

********************************************************************************************/

UINT32* BitmapSmoothingRecordHandler::GetTagList()
{
	static UINT32 TagList[] = {TAG_DOCUMENTBITMAPSMOOTHING, CXFRH_TAG_LIST_END};

	return (UINT32*)&TagList;
}


/********************************************************************************************

>	virtual BOOL BitmapSmoothingRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)

 	Author:		Andy_Hills (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/00
	Inputs:		pCXaraFileRecord = ptr to record to handle
	Returns:	TRUE if handled successfuly
				FALSE otherwise
	Purpose:	Handles the given record.
	SeeAlso:	-

********************************************************************************************/

BOOL BitmapSmoothingRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)
{
	ERROR2IF(pCXaraFileRecord == NULL,FALSE,"BitmapSmoothingRecordHandler::HandleRecord pCXaraFileRecord is NULL");

	BOOL ok = TRUE;

	// read in the record ---------------------------------------------------------

	BYTE Flags;
	if (ok) ok = pCXaraFileRecord->ReadBYTE(&Flags);	// flags byte

	// read other stuff
	BYTE Temp;
	for( INT32 i=0; i<4; i++ )
	{
		if (ok) ok = pCXaraFileRecord->ReadBYTE(&Temp);	// 4 reserved bytes
	}

	// process the record ---------------------------------------------------------

	BOOL bSmoothWhenScaledUp = Flags & 0x01;

	// get the document
	Document *pDoc = GetDocument();
	ERROR3IF( (!pDoc), "BitmapSmoothingRecordHandler::HandleRecord - Document is NULL" );

	// set the document's bitmap smoothing flag accordingly
	pDoc->SetBitmapSmoothing (bSmoothWhenScaledUp);

	return ok;
}


/********************************************************************************************

>	virtual void BitmapSmoothingRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr)

	Author:		Andy_Hills (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/00
	Inputs:		pRecord = ptr to a record
				pStr = ptr to string to update
	Returns:	-
	Purpose:	This provides descriptions for the define bitmap properties records.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

#ifdef XAR_TREE_DIALOG
void BitmapSmoothingRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase* pStr)
{
	if (pStr == NULL || pRecord == NULL)
		return;

	// Call base class first
	// This outputs the tag and size
	CamelotRecordHandler::GetRecordDescriptionText(pRecord,pStr);
	return;
}
#endif // XAR_TREE_DIALOG

//#endif // NEW_NATIVE_FILTER

