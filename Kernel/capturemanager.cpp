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

// CaptureManager.CPP
//
// Created: 29/06/2004 by Phil
//

#include "camtypes.h"
//#include "capturemanager.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "grndrgn.h"
#include "clipattr.h"	// so we know what a ClipRegionAttribute is.

//CC_IMPLEMENT_DYNAMIC(CaptureManager, CCObject)
CC_IMPLEMENT_DYNAMIC(Capture, CCObject)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/********************************************************************************************

>	Capture::Capture()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/07/2004
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default Constructor for Capture Class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

Capture::Capture()
{
	m_pOwner				= NULL;
	m_pDirectBitmapSupplier	= NULL;
	m_pClipRegionAttrValue	= NULL;

	CaptureRect				= DocRect(0,0,0,0);
	lpBitmapInfo			= NULL;
	lpBits					= NULL;
	CaptureMatrix			= Matrix();
	pColContext				= NULL;
	info					= CAPTUREINFO(ctDISABLED, cfNONE);
	dPixelsPerInch			= 96;

//	m_ClipRegionMap.InitHashTable(17, FALSE);
}




/********************************************************************************************

>	Capture::Capture(CCObject* pOwner,							// New Capture constructor
					CAPTUREINFO cinfo,
					Matrix CaptureMatrix,
					DocRect CaptureRect,
					ColourContext* pCaptureColourContext
					)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/07/2004
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	New Capture Constructor for Capture Class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

Capture::Capture(CCObject* pOwner,							// New Capture constructor
				CAPTUREINFO cinfo,
				Matrix cMatrix,
				DocRect cRect,
				double PixelsPerInch,
				ColourContext* pcColourContext
				)
{
	m_pOwner			= pOwner;
	m_pDirectBitmapSupplier = NULL;
	m_pClipRegionAttrValue	= NULL;

	CaptureRect			= cRect;
	lpBitmapInfo		= NULL;
	lpBits				= NULL;
PORTNOTE("other","Removed GRenderRegion::MakeGavinMatrix usage")
#ifndef EXCLUDE_FROM_XARALX
	CaptureGMatrix		= GRenderRegion::MakeGavinMatrix(cMatrix, cRect, PixelsPerInch);
#endif
	CaptureMatrix		= cMatrix;
	pColContext			= pcColourContext;
	info				= cinfo;
	dPixelsPerInch		= PixelsPerInch;
}




/********************************************************************************************

>	Capture::Capture(Capture* pSourceCapture,				// Copy constructor
					BOOL bCopyBitmap)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/07/2004
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Copy Constructor for Capture Class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

Capture::Capture(Capture* pSourceCapture,					// Copy constructor
				BOOL bCopyBitmap)
{
	m_pOwner				= pSourceCapture->m_pOwner;
	m_pDirectBitmapSupplier	= pSourceCapture->m_pDirectBitmapSupplier;
	m_pClipRegionAttrValue	= pSourceCapture->m_pClipRegionAttrValue;

	CaptureRect				= pSourceCapture->CaptureRect;
	lpBitmapInfo			= pSourceCapture->lpBitmapInfo;
	lpBits					= pSourceCapture->lpBits;
	CaptureMatrix			= pSourceCapture->CaptureMatrix;
	pColContext				= pSourceCapture->pColContext;
	info					= pSourceCapture->info;				// Note that copying a master will create a master!
	dPixelsPerInch			= pSourceCapture->dPixelsPerInch;

	if (bCopyBitmap && pSourceCapture->lpBitmapInfo && pSourceCapture->lpBits)
	{
		DIBUtil::CopyBitmap(pSourceCapture->lpBitmapInfo, pSourceCapture->lpBits,
							&lpBitmapInfo, &lpBits);
	}

	// CopyBitmap doesn't copy compression flag correctly...
	lpBitmapInfo->bmiHeader.biCompression = pSourceCapture->lpBitmapInfo->bmiHeader.biCompression;
}




/********************************************************************************************

>	BOOL Capture::AllocateDIB(BOOL bTransparent = FALSE)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/07/2004
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default Destructor for CaptureManager Class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

/*BOOL Capture::AllocateDIB(BOOL bTransparent)
{
	ERROR2(FALSE, "Unimplemented!");

	// NB Millipoint endpoints don't necessarily fall on exact pixel boundaries.
	// Hence use following function to find out which pixels the millipoints fall on
	RECT Rect = CalculateWinRect(CaptureMatrix, CaptureRect, PixelsPerInch);
	UINT32 PixelWidth = Rect.right-Rect.left;
	UINT32 PixelHeight = Rect.bottom-Rect.top;
	UINT32 bpp = 32;

//	TRACEUSER( "Gerry", _T("Creating offscreen bitmap (%d, %d)\n"), PixelWidth, PixelHeight);
	if (PixelWidth==0 || PixelHeight==0)
		return FALSE;

	lpBitmapInfo = ::AllocDIB( PixelWidth, PixelHeight, bpp, &lpBits, NULL, FALSE); // don't use limited mem manager

	if (lpBitmapInfo==NULL || lpBits==NULL)
	{
		ENSURE(FALSE,"Couldn't create bitmap for offscreen rendering.");
		return FALSE;
	}

	LPBITMAPINFOHEADER bh = &lpBitmapInfo->bmiHeader;
	bh->biCompression	= bTransparent ?	0x80000001:	BI_RGB;					// see GDraw docs on GDraw_SetDIBitmap
	bh->biXPelsPerMeter	= PixelsPerMeterAtCurrentViewScale(ScaleFactor);		// Not used by GDraw - just for completeness sake
	bh->biYPelsPerMeter	= PixelsPerMeterAtCurrentViewScale(ScaleFactor);		// Not used by GDraw

	// Success
	return TRUE;
}
*/



/********************************************************************************************

>	BOOL Capture::FreeDIB()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/07/2004
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default Destructor for CaptureManager Class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL Capture::FreeDIB()
{
	::FreeDIB(lpBitmapInfo, lpBits, NULL, FALSE);
	lpBitmapInfo = NULL;							// Owns bitmap will now return FALSE
	lpBits = NULL;

	return FALSE;
}




/********************************************************************************************

>	Capture::~Capture()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/07/2004
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default Destructor for CaptureManager Class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

Capture::~Capture()
{
	RemoveAllCachedClipRegions();

	if (m_pClipRegionAttrValue)
	{
		delete m_pClipRegionAttrValue;
		m_pClipRegionAttrValue = NULL;
	}
}




/********************************************************************************************

>	void Capture::SetTransparent(BOOL bNewState)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/07/2004
	Inputs:		bNewState - TRUE if captured bitmap should be made transparent
							FALSE if captured bitmap should be made opaque
	Outputs:	-
	Returns:	-
	Purpose:	Change the transparency of a captured bitmap
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void Capture::SetTransparent(BOOL bNewState)
{
	if (lpBitmapInfo && lpBits && lpBitmapInfo->bmiHeader.biBitCount==32)
	{
		lpBitmapInfo->bmiHeader.biCompression = bNewState ? 0x80000001 : BI_RGB;
		UINT32 BmpSize = GetDIBBitsSize(&lpBitmapInfo->bmiHeader);
		UINT32 Index = 0;
		LPBYTE pSetBits = lpBits;

		if (bNewState)
		{
			// ReInit bitmap to be fully transparent
			while(Index < BmpSize)
			{
				// initial values for using internal alpha channelled format
				// fully transparent black bacground

				pSetBits[Index++] = 0x00;
				pSetBits[Index++] = 0x00;
				pSetBits[Index++] = 0x00;
				pSetBits[Index++] = 0xFF;
			}
		}
		else
		{
			// ReInit bitmap to be fully opaque
			while(Index < BmpSize)
			{
				// fully opaque white background
				pSetBits[Index++] = 0xFF;
				pSetBits[Index++] = 0xFF;
				pSetBits[Index++] = 0xFF;
				pSetBits[Index++] = 0x00;
			}
		}
	}
	else
	{
		ERROR3("SetTransparency called on empty/non-32BPP bitmap");
	}
}




/********************************************************************************************

>	BOOL Capture::ConsumeDirectBitmap(NodeRenderableInk* pSupplier)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/2005
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Consume the supplied bitmap if the supplier is right
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL Capture::ConsumeDirectBitmap(NodeRenderableInk* pSupplier)
{
	if (m_pDirectBitmapSupplier!=pSupplier || info.caFlags.Direct==FALSE)
		return FALSE;

	// TODO: Could grab some info about the direct bitmap here?

	return TRUE;
}




/********************************************************************************************

>	const REGION* Capture::GetClipRegion(ClipRegionAttribute* pClipAttr)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/10/2005
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	-
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

const REGION* Capture::GetCachedClipRegion(ClipRegionAttribute* pClipAttr)
{
	ClipRegionMap::const_iterator iter = m_ClipRegionMap.find( pClipAttr );
	if( m_ClipRegionMap.end() == iter )
		return NULL;

	return (REGION *)iter->second;
}




/********************************************************************************************

>	void Capture::SetCachedClipRegion(ClipRegionAttribute* pClipAttr, const REGION* pClipRegion)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/10/2005
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	-
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void Capture::SetCachedClipRegion(ClipRegionAttribute* pClipAttr, const REGION* pClipRegion)
{
	m_ClipRegionMap[pClipAttr] = (void *)pClipRegion;
}




/********************************************************************************************

>	void Capture::RemoveCachedClipRegion(ClipRegionAttribute* pClipAttr)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/10/2005
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	-
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void Capture::RemoveCachedClipRegion(ClipRegionAttribute* pClipAttr)
{
	ClipRegionMap::iterator iter = m_ClipRegionMap.find( pClipAttr );
	if( m_ClipRegionMap.end() != iter )
	{
		if (iter->second != NULL)
			delete []( (BYTE *)iter->second );

		m_ClipRegionMap.erase( iter );
	}
}




/********************************************************************************************

>	void Capture::RemoveAllCachedClipRegions()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/10/2005
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	-
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void Capture::RemoveAllCachedClipRegions()
{
	ClipRegionMap::const_iterator iter = m_ClipRegionMap.begin();
	for( ; iter != m_ClipRegionMap.end(); ++iter )
	{
		if( iter->second != NULL )
			delete []( (BYTE *)iter->second );
	}
	m_ClipRegionMap.clear();
}




