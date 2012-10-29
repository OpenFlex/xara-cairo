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


// Kernel level parts of bitmap lists

/*
*/

#include "camtypes.h"
#include "bitmpinf.h"
#include "fillattr2.h"

CC_IMPLEMENT_MEMDUMP( CachedFractal, ListItem )
CC_IMPLEMENT_MEMDUMP( GlobalFractalList, List )

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/**********************************************************************************************

>	CachedFractal::CachedFractal()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	CachedFractal constructor

**********************************************************************************************/

CachedFractal::CachedFractal()
{
	Fractal		= NULL;
	UsageCount	= 0;
	m_bIsFake	= FALSE;
}

/**********************************************************************************************

>	CachedFractal::~CachedFractal()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	CachedFractal destructor

**********************************************************************************************/

CachedFractal::~CachedFractal()
{
	if (IsFakeFractal())
	{
		if (Fractal->GetBitmap())
		{
			delete Fractal->GetBitmapRef()->GetBitmap();
			Fractal->GetBitmapRef()->SetBitmap(NULL);
		}

		delete Fractal;
		return;
	}
	
	if (UsageCount > 0)
		TRACEUSER( "Mike", _T("Deleting cached fractal while it's still in use\n"));

	if (Fractal)
	{
		GlobalFractalList* pFracList = GetApplication()->GetGlobalFractalList();
		BOOL StillUsed = FALSE;

		if (pFracList)
		{
			CachedFractal* pCachedFractal = (CachedFractal*)pFracList->GetHead();

			while (pCachedFractal != NULL)
			{
				OILBitmap* pBmp = NULL;
				if (pCachedFractal->GetBitmap())
					pBmp = pCachedFractal->GetBitmap()->ActualBitmap;

				// Are the bitmaps the same ?
				if (Fractal->GetBitmap() && 
					Fractal->GetBitmap()->ActualBitmap == pBmp )
				{
					// This fractal bitmap is still being used
					StillUsed = TRUE;
					break;
				}

				pCachedFractal = (CachedFractal*)pFracList->GetNext(pCachedFractal);
			}	
		}

		if (Fractal->GetBitmap())
		{
			// Only delete the actual bitmap, if it's not used for any other fractals
			if (!StillUsed) 
			{
				delete Fractal->GetBitmapRef()->GetBitmap()->ActualBitmap;
				Fractal->GetBitmapRef()->GetBitmap()->ActualBitmap = NULL;
			}

			delete Fractal->GetBitmapRef()->GetBitmap();
			Fractal->GetBitmapRef()->SetBitmap(NULL);
		}

		delete Fractal;
	}
}

/**********************************************************************************************

>	INT32 CachedFractal::operator==(const FillGeometryAttribute& Attrib)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	-

**********************************************************************************************/

INT32 CachedFractal::operator==(const FillGeometryAttribute& Attrib)
{
	FillGeometryAttribute* CachedFrac = GetCachedFractal();
	FillGeometryAttribute* OtherFrac = (FillGeometryAttribute*)&Attrib;

	if (OtherFrac->GetRuntimeClass() != CachedFrac->GetRuntimeClass())
		return FALSE;

	return ( OtherFrac->IsSameAsCachedFractal(CachedFrac) );
}

/**********************************************************************************************

>	void CachedFractal::SetCachedFractal(FillGeometryAttribute* NewFrac)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	-

**********************************************************************************************/

void CachedFractal::SetCachedFractal(FillGeometryAttribute* NewFrac)
{
	CCRuntimeClass* ObjectType = NewFrac->GetRuntimeClass();
	FillGeometryAttribute* FracClone = (FillGeometryAttribute*)ObjectType->CreateObject();

	NewFrac->CacheFractalData(FracClone);

	KernelBitmap* Bmp = new KernelBitmap(NewFrac->GetBitmap()->ActualBitmap, TRUE);
	FracClone->GetBitmapRef()->SetBitmap(Bmp);
//	Bmp->IncUsageCount();

	Fractal = FracClone;
}

/**********************************************************************************************

>	FillGeometryAttribute* CachedFractal::GetCachedFractal()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	-

**********************************************************************************************/

FillGeometryAttribute* CachedFractal::GetCachedFractal()
{
	return Fractal;
}

/**********************************************************************************************

>	void CachedFractal::IncUsageCount()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Outputs:	Increaments the usage count of this cached fractal.
	Purpose:	-

**********************************************************************************************/

void CachedFractal::IncUsageCount()
{
	UsageCount++;
	TRACEUSER( "Mike", _T("Inc Cached Fractal @ %x, Usage to %d\n"),this, UsageCount);
}

/**********************************************************************************************

>	void CachedFractal::DecUsageCount()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Outputs:	Decreaments the usage count of this cached fractal.
	Purpose:	-

**********************************************************************************************/

void CachedFractal::DecUsageCount()
{
	UsageCount--;
	TRACEUSER( "Mike", _T("Dec Cached Fractal @ %x, Usage to %d\n"),this, UsageCount);
}

/**********************************************************************************************

>	INT32 CachedFractal::GetSize()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Returns:	The memory used by this fractal.
	Purpose:	-

**********************************************************************************************/

INT32 CachedFractal::GetSize()
{
	ERROR2IF(Fractal->GetBitmap() == NULL ||
			 Fractal->GetBitmap()->ActualBitmap == NULL, 0, "GetSize called when bitmap is NULL");

	BitmapInfo Info;
	Info.MemoryUsed = 0;

	if (Fractal->GetBitmap() &&
		Fractal->GetBitmap()->ActualBitmap)
	{
		Fractal->GetBitmap()->ActualBitmap->GetInfo(&Info);
	}

	return Info.MemoryUsed;
}

/**********************************************************************************************

>	KernelBitmap* CachedFractal::GetBitmap()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/8/96
	Returns:	The fractal bitmap 
	Purpose:	-

**********************************************************************************************/

KernelBitmap* CachedFractal::GetBitmap()
{
	if (Fractal == NULL)
		return NULL;

	return Fractal->GetBitmap();
}

/**********************************************************************************************

>	GlobalBitmapList::GlobalFractalList()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	GlobalFractalList constructor

**********************************************************************************************/

GlobalFractalList::GlobalFractalList()
{
}

/**********************************************************************************************

>	GlobalFractalList::~GlobalFractalList()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	GlobalFractalList destructor

**********************************************************************************************/

GlobalFractalList::~GlobalFractalList()
{
	if (!IsEmpty())
	{
		TRACEALL( _T("Trying to delete global fractal list when it's not empty !!\n") );
		Destroy();
	}
}

/**********************************************************************************************

>	void GlobalFractalList::Destroy()

	Author: 	Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/2/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destroy the contents of the fractal list

**********************************************************************************************/

void GlobalFractalList::Destroy()
{
	ListItem* Fractal;
	while ((Fractal=RemoveHead())!=NULL)
		delete Fractal;
}


/**********************************************************************************************

>	BOOL GlobalFractalList::Init()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/2/95
	Returns:	FALSE if failed.
	Purpose:	Initialise the GlobalFractalList

**********************************************************************************************/

BOOL GlobalFractalList::Init()
{
	return TRUE;
}

/**********************************************************************************************

>	static BOOL GlobalFractalList::DeInit()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/2/95
	Returns:	FALSE if failed.
	Purpose:	DeInitialise the GlobalFractalList. Static function so it finds the global
				fractal list first

**********************************************************************************************/

BOOL GlobalFractalList::DeInit()
{
	GlobalFractalList* FracList = GetApplication()->GetGlobalFractalList();
	if (FracList)
		FracList->Destroy();
	return TRUE;
}

/**********************************************************************************************

>	BOOL GlobalFractalList::AddFractal(FillGeometryAttribute* NewFractal)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Returns:	FALSE if this fractal already exits.
	Purpose:	Adds an item to the tail of the GlobalFractallist if it doesn't already
				exist.

**********************************************************************************************/

BOOL GlobalFractalList::AddFractal(FillGeometryAttribute* NewFractal)
{
	CachedFractal* ExistingFrac = CheckFractalBitmap(NewFractal);

	if (ExistingFrac != NULL)
	{
		ExistingFrac->IncUsageCount();
		return FALSE;
	}

	CachedFractal* Fractal = new CachedFractal();

	if (Fractal == NULL)
		return FALSE;

	TRACEUSER( "Mike", _T("Adding Cached Fractal @ %x\n"),Fractal);

	Fractal->SetCachedFractal(NewFractal);
	Fractal->IncUsageCount();

	AddTail((ListItem*)Fractal);

	if (this != GetApplication()->GetGlobalFractalList())
		Fractal->MakeFakeFractal();

	TRACEUSER( "Mike", _T("Cached Fractal Count = %d\n"),GetFractalCacheCount());
	TRACEUSER( "Mike", _T("Cached Fractal Size  = %d\n"),GetFractalCacheSize());

	return(TRUE);
}

/**********************************************************************************************

>	BOOL GlobalFractalList::RemoveFractal(FillGeometryAttribute* Frac)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Returns:	TRUE if the fractal was really removed (or doesn't exist)
	Purpose:	Called when a fractal is destroyed.

**********************************************************************************************/

BOOL GlobalFractalList::RemoveFractal(FillGeometryAttribute* Frac)
{
	CachedFractal* ExistingFrac = CheckFractalBitmap(Frac);

	if (ExistingFrac == NULL)
		return TRUE;		// This will be the case when we delete the cached fractal

	ExistingFrac->DecUsageCount();

	if (ExistingFrac->GetUsageCount() <= 0)
	{
		TRACEUSER( "Mike", _T("Removing Cached Fractal @ %x\n"),ExistingFrac);
		RemoveItem((ListItem*)ExistingFrac);
		delete ExistingFrac;

		return TRUE;
	}

	TRACEUSER( "Mike", _T("Cached Fractal Count = %d\n"),GetFractalCacheCount());
	TRACEUSER( "Mike", _T("Cached Fractal Size  = %d\n"),GetFractalCacheSize());

	return FALSE;	// The fractal is still there
}

/**********************************************************************************************

>	CachedFractal* GlobalFractalList::CheckFractalBitmap(FillGeometryAttribute*)

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Returns:	The existing Fractal if one exists.
	Purpose:	Checks to see if this fractal fill is already in the list.

**********************************************************************************************/

CachedFractal* GlobalFractalList::CheckFractalBitmap(FillGeometryAttribute* FractalFill)
{
	ListItem* Fractal = GetHead();
	while (Fractal!=NULL)
	{
		// Are the fractals the same ?
		if ( *((CachedFractal*)Fractal) == *FractalFill )
			return ((CachedFractal*)Fractal);
		
		Fractal = GetNext(Fractal);
	}	
	return NULL;
}

/**********************************************************************************************

>	INT32 GlobalFractalList::GetFractalCacheCount()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/3/94
	Returns:	The total number of cached fractals.
	Purpose:	Calculates the total number of cached fractals.

**********************************************************************************************/

INT32 GlobalFractalList::GetFractalCacheCount()
{
	return GetCount();
}

/**********************************************************************************************

>	INT32 GlobalFractalList::GetFractalCacheSize()

	Author: 	Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/3/94
	Returns:	The total memory used by the cached fractals.
	Purpose:	Calculates the total memory used by the cached fractals.

**********************************************************************************************/

INT32 GlobalFractalList::GetFractalCacheSize()
{
	INT32 FracSize = 0;
	ListItem* Fractal = GetHead();
	while (Fractal != NULL)
	{
		FracSize += ((CachedFractal*)Fractal)->GetSize();
		Fractal = GetNext(Fractal);
	}	
	return FracSize;
}


/**********************************************************************************************

>	void GlobalFractalList::GetDocumentFractalData(Document* pDoc, EnumFractalData *pData)

	Author: 	Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/3/94
	Inputs:		pDoc  = a pointer to a document
				pData = a pointer to a structure to fill
	Outputs:	pData is updated with information about the fractals used in this document
	Returns:	-
	Purpose:	Updates the fields in the EnumFractalData with information about fractals
				in the specified document

**********************************************************************************************/

void GlobalFractalList::GetDocumentFractalData(Document* pDoc, EnumFractalData *pData)
{
	BitmapInfo Info;
	GlobalFractalList FoundList;

	if (pDoc != NULL)
	{
		// Now Scan this document's tree for any references to a bitmap
		Node* pNode = Node::DocFindFirstDepthFirst(pDoc);
		while (pNode != NULL)
		{
			// First of all is this a NodeHidden ?
			// If so we want to look at the actual hidden node it's pointing at,
			// and scan the subtree, for Hidden bitmap references.
			if (!pNode->IsNodeHidden())
			{
				if (pNode->IsAnAttribute())		// Is this an Attribute ?
				{
					// Is it a Fractal Fill ?
					if (((NodeAttribute*)pNode)->IsAFractalFill())
					{
						AttrFractalFill* pFrac = (AttrFractalFill*)pNode;
						FillGeometryAttribute* pVal = (FillGeometryAttribute*)pFrac->GetAttributeValue();
						BOOL NewFractal = FoundList.AddFractal(pVal);

						if (NewFractal)
						{
							pData->Count++;

							if (pVal->GetBitmap() &&
								pVal->GetBitmap()->ActualBitmap)
							{
								pVal->GetBitmap()->ActualBitmap->GetInfo(&Info);
								pData->Size += Info.MemoryUsed;
							}
						}
					}
				}
			}

			// Move onto the next node in the tree
			pNode = pNode->DocFindNextDepthFirst(); 
		}
	}

	FoundList.Destroy();
}
