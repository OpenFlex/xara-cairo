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


#ifndef	INC_BMPSEQ
#define	INC_BMPSEQ

#include "impbmp.h"

class Document;
class OILBitmap;

/********************************************************************************************

>	class BitmapSequenceInfo : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05-07-96
	Purpose:	Describes a BitmapSequence
	SeeAlso:	BitmapSequence

********************************************************************************************/
class BitmapSequenceInfo : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(BitmapSequenceInfo)

public:
	UINT32 GetCount() const	{	return m_uCount;	}

//	FilterID	m_SourceFilterID;

protected:
	UINT32	m_uCount;

};


/********************************************************************************************

>	class BitmapSequence : public ImportedBitmaps

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05-07-96
	Purpose:	Maintains a sequence of bitmaps
	SeeAlso:	NewImportBitmap; ImportBitmapList

********************************************************************************************/

class BitmapSequence : public ImportedBitmaps
{
	CC_DECLARE_MEMDUMP(BitmapSequence)

public:
	BitmapSequence(BitmapSequenceInfo* pSequenceInfo) :
		m_pSequenceInfo(pSequenceInfo) {}

	void			DeleteAll();

	KernelBitmap*	FindInDocumentList(Document* pDocument);
	BOOL			CopyFromDocumentList(Document* pDocument, const KernelBitmap* pStartBitmap, 
										const UINT32 uNumberToCopy);

	BitmapSequenceInfo*	GetSequenceInfo() const;
	BOOL				SetSequenceInfo(BitmapSequenceInfo* pNewInfo);

	UINT32 GetCount() const;
protected:
	BitmapSequenceInfo*	m_pSequenceInfo;
};


#endif // INC_BMPSEQ
