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

#include "camtypes.h"

//#include "cxfrec.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "cxftags.h"
//#include "prnmkcom.h"
//#include "princomp.h"
#include "rechprnt.h"

DECLARE_SOURCE("$Revision: 1688 $");


CC_IMPLEMENT_DYNAMIC(PrintingRecordHandler, CamelotRecordHandler);

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/********************************************************************************************

>	virtual BOOL PrintingRecordHandler::BeginImport()

 	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/8/96

	Returns:	TRUE if ok
				FALSE otherwise

	Purpose:	Initialises the record handler ready for importing

********************************************************************************************/

BOOL PrintingRecordHandler::BeginImport()
{
#if !defined(EXCLUDE_FROM_RALPH) && !defined(EXCLUDE_FROM_XARALX)
	pPrintComponent = GetPrintComponent();

	// Let's not faff around for the print marks component - just find it for ourselves
	Document *ScopeDoc = GetDocument();
	if (ScopeDoc != NULL)
	{
		pPrintMarksComponent = (PrintMarksComponent *)
							ScopeDoc->GetDocComponent(CC_RUNTIME_CLASS(PrintMarksComponent));
	}

	return (pPrintComponent != NULL && pPrintMarksComponent != NULL);
#else
	return TRUE;
#endif
}


/********************************************************************************************

>	virtual UINT32* PrintingRecordHandler::GetTagList()

 	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/5/96

	Returns:	Ptr to a list of tag values, terminated by CXFRH_TAG_LIST_END

	Purpose:	Provides the record handler system with a list of records handled by this
				handler

********************************************************************************************/

UINT32* PrintingRecordHandler::GetTagList()
{
	static UINT32 TagList[] =
	{
		TAG_PRINTERSETTINGS,
		TAG_IMAGESETTING,
		TAG_COLOURPLATE,
		TAG_PRINTMARKDEFAULT,
		TAG_PRINTMARKCUSTOM,
		CXFRH_TAG_LIST_END
	};

	return(TagList);
}



/********************************************************************************************

>	virtual BOOL PrintingRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)

 	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/5/96

	Inputs:		pCXaraFileRecord = ptr to record to handle

	Returns:	TRUE if handled successfuly
				FALSE otherwise

	Purpose:	Handles the given record.

********************************************************************************************/

BOOL PrintingRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)
{
	ERROR2IF(pCXaraFileRecord == NULL, FALSE, "PrintingRecordHandler::HandleRecord pCXaraFileRecord is NULL");

#if !defined(EXCLUDE_FROM_RALPH) && !defined(EXCLUDE_FROM_XARALX)
	// When we're "opening" a file, we load, but if we're "importing" then we ignore all
	// printing options from the imported file (we don't want to override the existing
	// settings when you import into a different document)
	if (IsImporting())
		return(TRUE);

	switch (pCXaraFileRecord->GetTag())
	{
		case TAG_PRINTERSETTINGS:
			if (pPrintComponent)
				pPrintComponent->ImportPrintSettings(pCXaraFileRecord);
			break;

		case TAG_IMAGESETTING:
			if (pPrintComponent)
				pPrintComponent->ImportImagesetting(pCXaraFileRecord);
			break;

		case TAG_COLOURPLATE:
			if (pPrintComponent)
				pPrintComponent->ImportColourPlate(pCXaraFileRecord, this);
			break;

		case TAG_PRINTMARKDEFAULT:
			if (pPrintMarksComponent)
				pPrintMarksComponent->ImportDefaultPrintMark(pCXaraFileRecord);
			break;

		case TAG_PRINTMARKCUSTOM:
			if (pPrintMarksComponent)
				pPrintMarksComponent->StartImportCustomPrintMark(this, pCXaraFileRecord);
			break;

		default:
			ERROR3_PF(("PrintingRecordHandler::HandleRecord doesn't handle records with the tag (%d)\n",pCXaraFileRecord->GetTag()));
			return(FALSE);
	}
#endif
	return(TRUE);
}



/********************************************************************************************

>	virtual BOOL PrintingRecordHandler::BeginSubtree(UINT32 Tag)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/9/96

	Inputs:		Tag = tag value of the tag this handler last handled
	Returns:	TRUE if this func wants exclusive handling of the tag
				FALSE otherwise
	Purpose:	Informs the record handler that a subtree is following a tag of type 'Tag'

				If you override this func and you do not wish other parts of the system to be informed of the
				subtree start, you should return TRUE

********************************************************************************************/

BOOL PrintingRecordHandler::BeginSubtree(UINT32 Tag)
{
	// We only want to know about following subtrees when doing custom print mark records.
	// If we are doing one, then we grab the subtree so nobody else can faff about with it
	if (Tag != TAG_PRINTMARKCUSTOM)
		return(FALSE);

	return(TRUE);
}



/********************************************************************************************

>	virtual BOOL PrintingRecordHandler::EndSubtree(UINT32 Tag)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/9/96

	Inputs:		Tag = tag value of the tag this handler last handled
	Returns:	TRUE if this func wants exclusive handling of the tag
				FALSE otherwise

	Purpose:	Informs the record handler that a subtree that followed a tag of type 'Tag' has ended

				If you override this func and you do not wish other parts of the system to be informed of the
				subtree end, you should return TRUE

********************************************************************************************/

BOOL PrintingRecordHandler::EndSubtree(UINT32 Tag)
{
	// We only want to know about following subtrees when doing custom print mark records.
	// If we are doing one, then we grab the subtree so nobody else can faff about with it
	if (Tag != TAG_PRINTMARKCUSTOM)
		return(FALSE);

#if !defined(EXCLUDE_FROM_RALPH) && !defined(EXCLUDE_FROM_XARALX)
	// OK, it is the end of a custom print mark record, so complete the import
	if (pPrintMarksComponent && !IsImporting())
		pPrintMarksComponent->EndImportCustomPrintMark(this);
#endif
	
	return(TRUE);
}



/********************************************************************************************

>	virtual void PrintingRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/6/96

	Inputs:		pRecord = ptr to a record
				pStr = ptr to string to update
	Returns:	-
	Purpose:	This provides descriptions for the define colour records.

	Notes:		This funciton is only present in _DEBUG builds

********************************************************************************************/

#ifdef XAR_TREE_DIALOG
void PrintingRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase* pStr)
{
	if (pStr == NULL || pRecord == NULL)
		return;

	// Call base class first to output the tag and size
	CamelotRecordHandler::GetRecordDescriptionText(pRecord, pStr);

	UINT32 Tag = pRecord->GetTag();
//	INT32 RecordNumber = pRecord->GetRecordNumber();

	switch (Tag)
	{
		case TAG_PRINTERSETTINGS:
			break;

		case TAG_IMAGESETTING:
			break;

		case TAG_COLOURPLATE:
			break;

		case TAG_PRINTMARKDEFAULT:
			{
				BYTE ID;
				pRecord->ReadBYTE(&ID);
				String_16 Temp;
				Temp._MakeMsg(_T("Printers mark, ID = #1%ld"), (INT32)ID);
				*pStr += Temp;
			}
			break;

		case TAG_PRINTMARKCUSTOM:
			*pStr += _T("Custom printers mark subtree follows...");
			break;

		default:
			ERROR3("Unknown tag passed to PrintingRecordHandler");
			break;
	}
}

#endif		// _DEBUG

