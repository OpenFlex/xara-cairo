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

/********************************************************************************************

>	cxfnbmp.cpp

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/06/96
	Purpose:	Implementation of an abstract class, holding code for exporting NodeBitmaps.

********************************************************************************************/

#include "camtypes.h"

#include "nodebmp.h"

#include "cxftags.h"
#include "cxfile.h"
#include "cxfnbmp.h"

/********************************************************************************************

>	BOOL CXaraFileNodeBitmap::WritePreChildrenWeb(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap);
	BOOL CXaraFileNodeBitmap::WritePreChildrenNative(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap);

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/06/96
	Inputs:		pFilter - filter to save to
				pNodeBitmap - NodeBitmap to save
	Returns:	TRUE if successful, FALSE otherwise
	Purpose:	Saves a NodeBitmap record to the filter

********************************************************************************************/

BOOL CXaraFileNodeBitmap::WritePreChildrenWeb(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap)
{
	ERROR2IF(pFilter==NULL, FALSE, "parameter pFilter==NULL");
	ERROR2IF(pNodeBitmap==NULL, FALSE, "parameter pNodeBitmap==NULL");

	return WriteNodeBitmap(pFilter, pNodeBitmap);
}

BOOL CXaraFileNodeBitmap::WritePreChildrenNative(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap)
{
	ERROR2IF(pFilter==NULL, FALSE, "parameter pFilter==NULL");
	ERROR2IF(pNodeBitmap==NULL, FALSE, "parameter pNodeBitmap==NULL");

	return WriteNodeBitmap(pFilter, pNodeBitmap);
}

/********************************************************************************************

>	BOOL CXaraFileNodeBitmap::WriteNodeBitmap(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap)

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/06/96
	Inputs:		pFilter - filter to save to
				pNodeBitmap - NodeBitmap to save out
	Returns:	TRUE if successful, FALSE otherwise
	Purpose:	saves a NodeBitmap record to the filter

********************************************************************************************/

BOOL CXaraFileNodeBitmap::WriteNodeBitmap(BaseCamelotFilter *pFilter, NodeBitmap *pNodeBitmap)
{
	ERROR2IF(pFilter==NULL, FALSE, "parameter pFilter==NULL");
	ERROR2IF(pNodeBitmap==NULL, FALSE, "parameter pNodeBitmap==NULL");

	BOOL ok = TRUE;

	// save out the actual bitmap, and remember its record number
	INT32 BitmapRecordRef = 0;
	INT32 StartColourRecordRef = 0;
	INT32 EndColourRecordRef = 0;

	// Get the bitmap that the node references and hence we need to save.
	// Then get a reference to it. In the process this may save out the
	// bitmap definition, if it has not already been saved
	KernelBitmap *pBmp = pNodeBitmap->GetBitmap();
	// Complain if no bitmap was found	
	ERROR2IF(pBmp == NULL,FALSE,"CXaraFileNodeBitmap::WriteNodeBitmap pBmp is NULL");
	BitmapRecordRef = pFilter->WriteRecord(pBmp);
	ERROR2IF(BitmapRecordRef == 0,FALSE,"CXaraFileNodeBitmap::WriteNodeBitmap BitmapRecordRef is 0");

	// Do the same for the start and end colours (Contoning)
	// Only get a colour reference if they are present
	DocColour *pStartCol = pNodeBitmap->GetStartColour();
	if (pStartCol)
		StartColourRecordRef = pFilter->WriteRecord(pStartCol);
	DocColour *pEndCol = pNodeBitmap->GetEndColour();
	if (pEndCol)
		EndColourRecordRef = pFilter->WriteRecord(pEndCol);

	// BOOL Contoned = pNodeBitmap->GetApplyContoneColour();
	// The above flag may lie. If you have a 24bpp bitmap and have tried to apply a contone colour
	// and cancelled the operation, then this flag is set but there are no colours.
	// Check for the prescence of the colours and that they have been converted to colour references
	// ok. Only then, do we save a contoned bitmap.
	if (pStartCol != NULL && pEndCol != NULL &&
		StartColourRecordRef != 0 && EndColourRecordRef != 0 )
	{
		// Write out a contoned node bitmap record
		CamelotFileRecord Rec(pFilter,TAG_NODE_CONTONEDBITMAP, TAG_NODE_CONTONEDBITMAP_SIZE);
TRACEUSER( "Neville", _T("Write contoned node bitmap, bitmap reference %d, Start colour %d, EndColour %d\n"),BitmapRecordRef,StartColourRecordRef,EndColourRecordRef);
		if (ok) ok = Rec.Init();
		// Write out the encompassing rectangle
		if (ok) ok = Rec.WriteCoord(pNodeBitmap->Parallel[0]);
		if (ok) ok = Rec.WriteCoord(pNodeBitmap->Parallel[1]);
		if (ok) ok = Rec.WriteCoord(pNodeBitmap->Parallel[2]);
		if (ok) ok = Rec.WriteCoord(pNodeBitmap->Parallel[3]);
		// Write out the bitmap reference
		if (ok) ok = Rec.WriteReference(BitmapRecordRef);
		if (ok) ok = Rec.WriteReference(StartColourRecordRef);
		if (ok) ok = Rec.WriteReference(EndColourRecordRef);
		if (ok) ok = pFilter->Write(&Rec);
	}
	else
	{
		// Write out a normal node bitmap record
		CamelotFileRecord Rec(pFilter,TAG_NODE_BITMAP, TAG_NODE_BITMAP_SIZE);
TRACEUSER( "Neville", _T("Write node bitmap, bitmap reference %d\n"),BitmapRecordRef);
		if (ok) ok = Rec.Init();
		// Write out the encompassing rectangle
		if (ok) ok = Rec.WriteCoord(pNodeBitmap->Parallel[0]);
		if (ok) ok = Rec.WriteCoord(pNodeBitmap->Parallel[1]);
		if (ok) ok = Rec.WriteCoord(pNodeBitmap->Parallel[2]);
		if (ok) ok = Rec.WriteCoord(pNodeBitmap->Parallel[3]);
		// Write out the bitmap reference
		if (ok) ok = Rec.WriteReference(BitmapRecordRef);
		if (ok) ok = pFilter->Write(&Rec);
	}

	return ok;
}

