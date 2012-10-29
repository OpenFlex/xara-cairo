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


// Implementation of the bitmap record handler class of the v2 file format

#include "camtypes.h"

#include "rechbmp.h"	// BitmapRecordHandler for importing bitmaps from v2 native/web files
#include "bmpcomp.h"	// Document bitmap component, handles import of bitmaps
#include "cxfile.h"		// CXaraFile file handling class for version 2 native filter 
#include "cxftags.h"	// TAG_DEFINEBITMAP_**** 
//#include "sgliboil.h"	// Wav stuff

#include "nodebmp.h"	// NodeBitmap
//#include "impbmp.h"		// ImportedBitmaps

DECLARE_SOURCE("$Revision: 1688 $");

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_DYNAMIC(BitmapRecordHandler,CamelotRecordHandler);

//#if NEW_NATIVE_FILTER	// New native filters, only available to those who need them at present

/********************************************************************************************

>	virtual BOOL BitmapRecordHandler::BeginImport()

 	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		-
	Returns:	TRUE if ok
				FALSE otherwise
	Purpose:	Initialises the bitmap record handler
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL BitmapRecordHandler::BeginImport()
{
	pBmpComponent = GetBitmapDocComponent();

	return (pBmpComponent != NULL);
}

/********************************************************************************************

>	virtual UINT32* BitmapRecordHandler::GetTagList()

 	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		-
	Returns:	Ptr to a list of tag values, terminated by CXFRH_TAG_LIST_END
	Purpose:	Provides the record handler system with a list of records handled by this
				handler
	SeeAlso:	-

********************************************************************************************/

UINT32* BitmapRecordHandler::GetTagList()
{
	static UINT32 TagList[] = {TAG_NODE_BITMAP, TAG_NODE_CONTONEDBITMAP,
							  TAG_DEFINEBITMAP_BMP, TAG_DEFINEBITMAP_GIF, TAG_DEFINEBITMAP_JPEG,
							  TAG_DEFINEBITMAP_PNG, TAG_DEFINEBITMAP_BMPZIP, TAG_DEFINESOUND_WAV,
							  TAG_DEFINEBITMAP_JPEG8BPP,
							  TAG_PREVIEWBITMAP_BMP, TAG_PREVIEWBITMAP_GIF, TAG_PREVIEWBITMAP_JPEG,
							  TAG_PREVIEWBITMAP_PNG, TAG_PREVIEWBITMAP_TIFFLZW,
							  TAG_DEFINEBITMAP_XPE,
							  CXFRH_TAG_LIST_END};

	return (UINT32*)&TagList;
}

/********************************************************************************************

>	virtual BOOL BitmapRecordHandler::IsStreamed(UINT32 Tag)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/6/96
	Inputs:		The tag of the record
	Returns:	TRUE if this is a streamed record
				FALSE otherwise
	Purpose:	Function to find out if the record is streamed or not.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL BitmapRecordHandler::IsStreamed(UINT32 Tag)
{
	// We handle both types so check what we need to do by the tag we have been given
	BOOL Streamed = FALSE;
	switch (Tag)
	{
		case TAG_NODE_BITMAP:
		case TAG_NODE_CONTONEDBITMAP:
		case TAG_DEFINEBITMAP_XPE:
			// These are not streamed records.
			Streamed = FALSE;
			break;
		case TAG_PREVIEWBITMAP_BMP:
		case TAG_PREVIEWBITMAP_GIF:
		case TAG_PREVIEWBITMAP_JPEG:
		case TAG_PREVIEWBITMAP_PNG:
		case TAG_PREVIEWBITMAP_TIFFLZW:
		case TAG_DEFINEBITMAP_BMP:
		case TAG_DEFINEBITMAP_GIF:
		case TAG_DEFINEBITMAP_JPEG:
		case TAG_DEFINEBITMAP_PNG:
		case TAG_DEFINEBITMAP_BMPZIP:
		case TAG_DEFINESOUND_WAV:
		case TAG_DEFINEBITMAP_JPEG8BPP:
			// These are streamed records.
			Streamed = TRUE;
			break;
		default:
			Streamed = FALSE;
			ERROR3_PF(("BitmapRecordHandler::IsStreamed I don't handle records with the tag (%d)\n", Tag));
			break;
	}

	return Streamed;
}

/********************************************************************************************

>	virtual BOOL BitmapRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)

 	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Inputs:		pCXaraFileRecord = ptr to record to handle
	Returns:	TRUE if handled successfuly
				FALSE otherwise
	Purpose:	Handles the given record.
	SeeAlso:	-

********************************************************************************************/

BOOL BitmapRecordHandler::HandleRecord(CXaraFileRecord* pCXaraFileRecord)
{
	ERROR2IF(pCXaraFileRecord == NULL,FALSE,"BitmapRecordHandler::HandleRecord pCXaraFileRecord is NULL");

	BOOL ok = TRUE;

	INT32 Tag = pCXaraFileRecord->GetTag();
	switch (Tag)
	{
		case TAG_NODE_BITMAP:
		{
			// Load in that node bitmap 
			ok = HandleNodeBitmap(pCXaraFileRecord, Tag);
			break;
		}
		case TAG_NODE_CONTONEDBITMAP:
		{
			// Load in that node contone bitmap 
			ok = HandleNodeBitmap(pCXaraFileRecord, Tag);
			break;
		}
		case TAG_DEFINEBITMAP_XPE:
		{
			// Load in the empty place marker for a XPE processed bitmap
			ok = HandleXPEBitmapPlaceHolder(pCXaraFileRecord, Tag);
			break;
		}
		
		default:
			ok = FALSE;
			ERROR3_PF(("BitmapRecordHandler::HandleRecord I don't handle records with the tag (%d)\n", Tag));
			break;
	}

	return ok;
}

/********************************************************************************************

>	virtual BOOL BitmapRecordHandler::HandleStreamedRecord(CXaraFile * pCXFile, UINT32 Tag,UINT32 Size,UINT32 RecordNumber)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/6/96
	Inputs:		pCXFile = access to the CXaraFile class
				Tag	 = the tag value
				Size = size of record
				RecordNumber = the record number in the file
	Returns:	TRUE if handled ok
				FALSE otherwise
	Purpose:	This is the bitmap streamed record handler. It handles the loading of bitmap
				definitions.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL BitmapRecordHandler::HandleStreamedRecord(CXaraFile * pCXFile, UINT32 Tag,UINT32 Size,UINT32 RecordNumber)
{
	ERROR2IF(pCXFile == NULL,FALSE,"BitmapRecordHandler::HandleStreamedRecord pCXFile is NULL");

	BOOL ok = TRUE;

	switch (Tag)
	{
		case TAG_PREVIEWBITMAP_BMP:
		case TAG_PREVIEWBITMAP_GIF:
		case TAG_PREVIEWBITMAP_JPEG:
		case TAG_PREVIEWBITMAP_PNG:
		case TAG_PREVIEWBITMAP_TIFFLZW:
		{
			// We don't require it so just throw it away.
			TRACEUSER( "Neville", _T("BitmapRecordHandler::HandleStreamedRecord PREVIEWBITMAP\n"));
			// Note the current position in the file
			// Get the underlying file stream class, CCFile, that we are using to load the file
			CCLexFile* pFile = pCXFile->GetCCFile();
			if (pFile)
			{
				// Move on by the size of the data in this record
				FilePos pos = pFile->tellIn(); 
				pFile->seekIn(pos + Size);
			}
			break;
		}
		case TAG_DEFINEBITMAP_BMP:
		case TAG_DEFINEBITMAP_GIF:
		case TAG_DEFINEBITMAP_JPEG:
		case TAG_DEFINEBITMAP_PNG:
		case TAG_DEFINEBITMAP_BMPZIP:
		case TAG_DEFINEBITMAP_JPEG8BPP:
			// Ask the bitmap document component class to import that bitmap for us
			if (pBmpComponent)
			{
				TRACEUSER( "Neville", _T("BitmapRecordHandler::HandleStreamedRecord DEFINEBITMAP\n"));
				ok = pBmpComponent->LoadBitmapDefinition(this, pCXFile, Tag, Size, RecordNumber);
			}
			else
				ERROR3("BitmapRecordHandler::HandleStreamedRecord no pBmpComponent");
			break;

		case TAG_DEFINESOUND_WAV:
#if !defined(EXCLUDE_FROM_RALPH) && !defined(EXCLUDE_FROM_XARALX)
			TRACEUSER( "Neville", _T("BitmapRecordHandler::HandleStreamedRecord DEFINESOUND\n"));
			ok = SGLibOil::LoadSoundDefinition(this, pCXFile, Tag, Size, RecordNumber);
#endif
			break;

		default:
			ok = FALSE;
			ERROR3_PF(("BitmapRecordHandler::HandleStreamedRecord I don't handle records with the tag (%d)\n", Tag));
			break;
	}

	return ok;
}

/********************************************************************************************

>	virtual BOOL	BitmapRecordHandler::HandleNodeBitmap(CXaraFileRecord* pCXaraFileRecord, INT32 Tag)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/6/96
	Inputs:		pCXaraFileRecord	= baseclass record handler
				Tag					= record tag
	Returns:	-
	Purpose:	This handles the loading and creation of node bitmaps on receiving the 
				correct records from the main record handler.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL BitmapRecordHandler::HandleNodeBitmap(CXaraFileRecord* pCXaraFileRecord, INT32 Tag)
{
	ERROR2IF(pCXaraFileRecord == NULL,FALSE,"BitmapRecordHandler::HandleNodeBitmap pCXaraFileRecord is NULL");

	BOOL ok = TRUE;

	// Create a NodeBitmap ready for our use
	NodeBitmap * pNodeBmp = NULL;
	pNodeBmp = new NodeBitmap;
	if ((pNodeBmp == NULL) || (!pNodeBmp->SetUpPath(12,12)))
		return FALSE;

	// --------------------------------
	// Get details for that node bitmap 
	// Sort out reading the coordinates for the 4 corners of the rectangle
	// And apply them to the NodeBitmap
	DocCoord Parallel[4];		// 4 coords to represent the parallelogram that the shape fits in
	INT32 i;
	for (i = 0; i < 4; i++)
	{
		if (ok) ok = pCXaraFileRecord->ReadCoord(&Parallel[i]);
		pNodeBmp->Parallel[i] = Parallel[i];
	}

	// Put them into the path.
	pNodeBmp->InkPath.InsertMoveTo(Parallel[0]);

	for (i = 1; i <= 3; i++)
		pNodeBmp->InkPath.InsertLineTo(Parallel[i]);

	pNodeBmp->InkPath.InsertLineTo(Parallel[0]);
	pNodeBmp->InkPath.CloseSubPath();

	// ---------------------------------
	// Read in the details on the bitmap
	INT32 BitmapRecordRef = 0;
	if (ok) ok = pCXaraFileRecord->ReadINT32(&BitmapRecordRef);
	if (BitmapRecordRef == 0)
		return FALSE;

	KernelBitmap * pBitmap = NULL;
	pBitmap = GetReadBitmapReference(BitmapRecordRef);
	if (pBitmap == NULL)
		return FALSE;

	// Attach the bitmap to the NodeBitmap
	pNodeBmp->GetBitmapRef()->Attach(pBitmap, NULL); //GetDocument());

	pNodeBmp->InvalidateBoundingRect();
	if (ok) ok = InsertNode(pNodeBmp);

	// ---------------------------------------------
	// Sort out the contoning to be either on or off
	INT32 StartColourRecordRef = 0;
	INT32 EndColourRecordRef = 0;
	switch (Tag)
	{
		case TAG_NODE_CONTONEDBITMAP:
		{
			// Get the colour details for that contoned node bitmap 
			if (ok) ok = pCXaraFileRecord->ReadINT32(&StartColourRecordRef);
			if (ok) ok = pCXaraFileRecord->ReadINT32(&EndColourRecordRef);
			
			DocColour * pStartColour = new DocColour;
			if (pStartColour && ok)
				ok = GetDocColour(StartColourRecordRef, pStartColour);
			pNodeBmp->SetStartColour(pStartColour);
			delete pStartColour;

			DocColour * pEndColour = new DocColour;
			if (pEndColour && ok)
				ok = GetDocColour(EndColourRecordRef, pEndColour);
			pNodeBmp->SetEndColour(pEndColour);
			delete pEndColour;
			break;
		}

		case TAG_NODE_BITMAP:
		{
			// Plain old node bitmap so just set up the plain colours
			pNodeBmp->SetStartColour(NULL);
			pNodeBmp->SetEndColour(NULL);
			break;
		}

		default:
			ok = FALSE;
			ERROR3_PF(("BitmapRecordHandler::HandleNodeBitmap I don't handle records with the tag (%d)\n", Tag));
			break;
	}

	return ok;
}


/********************************************************************************************

>	virtual BOOL	BitmapRecordHandler::HandleXPEBitmapPlaceHolder(CXaraFileRecord* pCXaraFileRecord, INT32 Tag)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/2004
	Inputs:		pCXaraFileRecord	= baseclass record handler
				Tag					= record tag
	Returns:	-
	Purpose:	This handles the loading and creation of kernel bitmaps to be filled in
				subsequently by XPE bitmap properties.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL BitmapRecordHandler::HandleXPEBitmapPlaceHolder(CXaraFileRecord* pCXaraFileRecord, INT32 Tag)
{
	ERROR2IF(pCXaraFileRecord == NULL, FALSE,
				"BitmapRecordHandler::HandleXPEBitmapPlaceHolder pCXaraFileRecord is NULL");

	BOOL ok = TRUE;

	// First get the name of the bitmap and other details stored in the record
//	String_256 BitmapName;
//	if (ok) ok = pCXaraFileRecord->ReadUnicode(&BitmapName);

	// Check that the Filter existed
	KernelBitmap* pBitmap = NULL;

	// We have no filter present to load it. In the case of RALPH and even in Camelot,
	// the best course of action will be to use a default bitmap instead.
	// In the case of Camelot, warn the user that this has happened.
	pBitmap = KernelBitmap::MakeKernelBitmap(NULL, NULL, TRUE);

	// Set the bitmap name
//	pBitmap->ActualBitmap->SetName(BitmapName);

	// If have a genuine bitmap then add it to the loaded list
	// If the bitmap is null then the reference will use the default instead.
	if (pBitmap != NULL)
	{
		PORTNOTETRACE("other","HandleXPEBitmapPlaceHolder - Removed ImportedBitmaps usage");
#ifndef EXCLUDE_FROM_XARALX
		pBmpComponent->GetImportList()->AddBitmap(pBitmap, pCXaraFileRecord->GetRecordNumber());
#endif
	}

	return ok;
}


/********************************************************************************************

>	virtual void BitmapRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/6/96
	Inputs:		pRecord = ptr to a record
				pStr = ptr to string to update
	Returns:	-
	Purpose:	This provides descriptions for the define bitmap records.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

#ifdef XAR_TREE_DIALOG
void BitmapRecordHandler::GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase* pStr)
{
	if (pStr == NULL || pRecord == NULL)
		return;

	// Call base class first
	// This outputs the tag and size
	CamelotRecordHandler::GetRecordDescriptionText(pRecord,pStr);

	UINT32 Tag = pRecord->GetTag();
	BOOL ok = TRUE;
	TCHAR s[340];
	INT32 RecordNumber = pRecord->GetRecordNumber();

	// If define bitmap records then read in the bitmap name
	String_256 BmpName; 
	String_256 BitmapDetails; 
	if (Tag >= TAG_DEFINEBITMAP_BMP && Tag <= TAG_DEFINEBITMAP_BMPZIP)
	{
		if (ok) ok = pRecord->ReadUnicode(&BmpName);//BmpName, BmpName.MaxLength());
		if (BmpName.Length() == 0)
			BmpName = _T("Unnamed\r\n\r\n");
		else
		{
			BitmapDetails = _T("Bitmap name:- ");
			BitmapDetails += BmpName;
			BitmapDetails += _T("\r\n\r\n");
		}
	}

	INT32 BitmapRecordRef = 0;
	INT32 StartColourRecordRef = 0;
	INT32 EndColourRecordRef = 0;
	DocCoord Parallel[4];		// 4 coords to represent the parallelogram that the shape fits in
	switch (Tag)
	{
	// Node bitmap records
		case TAG_NODE_BITMAP:
		{
			// Show details for that node bitmap
			if (ok) ok = pRecord->ReadCoord(&Parallel[0]);
			if (ok) ok = pRecord->ReadCoord(&Parallel[1]);
			if (ok) ok = pRecord->ReadCoord(&Parallel[2]);
			if (ok) ok = pRecord->ReadCoord(&Parallel[3]);
			if (ok) ok = pRecord->ReadINT32(&BitmapRecordRef);
			(*pStr) += _T("Node bitmap\r\n\r\n");
			camSprintf(s,_T("Bitmap reference : %d\r\n\r\n"),BitmapRecordRef);
			(*pStr) += s;
			(*pStr) += _T("\tNum\tX Coord\tY Coord\r\n");
			for (INT32 i = 0; i < 4; i++)
			{
				camSprintf(s,_T("\t%d\t%d\t%d\r\n"),i,Parallel[i].x,Parallel[i].y);
				(*pStr) += s;
			}
			break;
		}
		case TAG_NODE_CONTONEDBITMAP:
		{
			// Show details for that contoned node bitmap 
			if (ok) ok = pRecord->ReadCoord(&Parallel[0]);
			if (ok) ok = pRecord->ReadCoord(&Parallel[1]);
			if (ok) ok = pRecord->ReadCoord(&Parallel[2]);
			if (ok) ok = pRecord->ReadCoord(&Parallel[3]);
			if (ok) ok = pRecord->ReadINT32(&BitmapRecordRef);
			if (ok) ok = pRecord->ReadINT32(&StartColourRecordRef);
			if (ok) ok = pRecord->ReadINT32(&EndColourRecordRef);
			camSprintf(s,_T("Node contoned bitmap\r\n\r\n"));
			(*pStr) += s;
			camSprintf(s,_T("Bitmap reference :\t %d\r\n\r\n"),BitmapRecordRef);
			(*pStr) += s;
			camSprintf(s,_T("Start colour reference :\t %d\r\n\r\n"),StartColourRecordRef);
			(*pStr) += s;
			camSprintf(s,_T("End colour reference :\t %d\r\n\r\n"),EndColourRecordRef);
			(*pStr) += s;
			camSprintf(s,_T("\tNum\tX Coord\tY Coord\r\n"));
			(*pStr) += s;
			for (INT32 i = 0; i < 4; i++)
			{
				camSprintf(s,_T("\t%d\t%d\t%d\r\n"),i,Parallel[i].x,Parallel[i].y);
				(*pStr) += s;
			}
			break;
		}
	// Preview bitmap records
		case TAG_PREVIEWBITMAP_BMP:
			(*pStr) += _T("Preview bitmap type BMP\r\n\r\n");
			break;
		case TAG_PREVIEWBITMAP_GIF:
			(*pStr) += _T("Preview bitmap type GIF\r\n\r\n");
			break;
		case TAG_PREVIEWBITMAP_JPEG:
			(*pStr) += _T("Preview bitmap type JPEG\r\n\r\n");
			break;
		case TAG_PREVIEWBITMAP_PNG:
			(*pStr) += _T("Preview bitmap type PNG\r\n\r\n");
			break;
		case TAG_PREVIEWBITMAP_TIFFLZW:
			(*pStr) += _T("Preview bitmap type TIFF LZW\r\n\r\n");
			break;
	
	// Define bitmap records
		case TAG_DEFINEBITMAP_BMP:
			camSprintf(s,_T("Define BMP bitmap reference %d\r\n\r\n"),RecordNumber);
			(*pStr) += s;
			(*pStr) += BitmapDetails;
			break;
		case TAG_DEFINEBITMAP_GIF:
			camSprintf(s,_T("Define GIF bitmap reference %d\r\n\r\n"),RecordNumber);
			(*pStr) += s;
			(*pStr) += BitmapDetails;
			break;
		case TAG_DEFINEBITMAP_JPEG:
			camSprintf(s,_T("Define JPEG bitmap reference %d\r\n\r\n"),RecordNumber);
			(*pStr) += s;
			(*pStr) += BitmapDetails;
			break;
		case TAG_DEFINEBITMAP_PNG:
			camSprintf(s,_T("Define PNG bitmap reference %d\r\n\r\n"),RecordNumber);
			(*pStr) += s;
			(*pStr) += BitmapDetails;
			break;
		case TAG_DEFINEBITMAP_BMPZIP:
			camSprintf(s,_T("Define zipped BMP bitmap reference %d\r\n\r\n"),RecordNumber);
			(*pStr) += s;
			(*pStr) += BitmapDetails;
			break;
		case TAG_DEFINEBITMAP_JPEG8BPP:
		{
			camSprintf(s,_T("Define 8bpp JPEG bitmap reference %d\r\n\r\n"),RecordNumber);
			(*pStr) += s;
			(*pStr) += BitmapDetails;
			BYTE Entries = 0;
			if (ok) ok = pRecord->ReadBYTE(&Entries);
			camSprintf(s,_T("Palette entries %d\r\n\r\n"),Entries + 1);
			(*pStr) += s;
			break;
		}
		default:
			(*pStr) += _T("Unknown type of bitmap record\r\n");
			break;
	}

	return;
}
#endif // XAR_TREE_DIALOG

//#endif // NEW_NATIVE_FILTER

