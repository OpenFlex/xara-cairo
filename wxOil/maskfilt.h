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

//

#ifndef INC_MASKEDFILTER
#define INC_MASKEDFILTER

#include "bitfilt.h"
//#include "bmpprefs.h"  	// SelectionType
#include "exphint.h"

class CXaraFileRecord;
class KernelBitmap;
class OutputDIB;

/********************************************************************************************

>	class MaskedFilterExportOptions : public BitmapExportOptions

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/96
	Purpose:   	Base class for storing information about the bitmap we're exporting.

********************************************************************************************/

class MaskedFilterExportOptions : public BitmapExportOptions
{
	CC_DECLARE_DYNAMIC(MaskedFilterExportOptions)

public:

	static BOOL Declare();

	MaskedFilterExportOptions();
    MaskedFilterExportOptions(const CDlgResID& Dialog, 
							  const FilterType FilterID, const StringBase* pFilterName);

	virtual BOOL	RetrieveDefaults();
	virtual BOOL	SetAsDefaults() const;

	// Save and load from named export set properties.
	virtual BOOL Write(CXaraFileRecord* pRec);
	virtual BOOL Read(CXaraFileRecord* pRec);

	virtual DITHER	GetDither() const { return m_Dither; }
	virtual BOOL	SetDither(const DITHER& Dither);

	BOOL	WantTransparent() const;
	BOOL	WantInterlaced() const { return m_bInterlaced; }
	BOOL	SetMakeInterlaced(BOOL bInterlaced);

	void	SetFilterType(FilterType ID)	{	m_FilterID = ID;	}

// WEBSTER - markn 21/1/97
	virtual BOOL UseSpecificNumColsInPalette();

	// for object copying and comparing
	virtual BOOL CopyFrom(BitmapExportOptions *pOther);

	//  Same as above, except it is used to copy information when changing file types
	virtual BOOL FileTypeChangeCopyFrom(BitmapExportOptions *pOther);
//	virtual BOOL Equal(BitmapExportOptions *pOther);

	// needed for the make bitmap copy options preview dialog
	BOOL CopyFromMasked(MaskedFilterExportOptions *pOther);

protected:

	// Parameters that the dialog can set
	DITHER	m_Dither;					// Dither type
	BOOL	m_bInterlaced;

	// Persistant buffer
	static DITHER	g_Dither;
	static PALETTE	g_Palette;
	static BOOL		g_bTransparent;
	static BOOL		g_bInterlaced;

};

/********************************************************************************************

>	class MaskedFilter : public BitmapFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/96
	Purpose:	Encapsulates a masked filter which provides funcitonality for doing masked
				bitmap export and import.

********************************************************************************************/

class MaskedFilter : public BaseBitmapFilter
{
	CC_DECLARE_DYNAMIC(MaskedFilter);
	
public:

	MaskedFilter();
	BOOL Init();

	INT32	SetTransColour(INT32 NewColour);
	INT32	GetTransColour() { return TransColour; }

	// SMFIX - Sets All the appropriate colour to being Transparent!
	BOOL ApplyTransparentColoursToBitmap(KernelBitmap* pExportBitmap = NULL, BitmapExportOptions* pExportOptions = NULL);
	BOOL ApplyTransparentColoursToBitmap(BITMAPINFOHEADER* pInfoHeader = NULL, BYTE* pBMPBits = NULL,
										 BitmapExportOptions* pExportOptions = NULL, UINT32 YOffset = 0,
										 UINT32 StripHeight = 0);

	// Virtual overrides
	virtual UINT32 GetNumReservedColours();
	virtual BOOL ExportSelectionOnly(BOOL MaskedRender = FALSE); 

	virtual BOOL CheckSingleBitmapsOnSpread ( Spread	*pSpread,
											  BOOL		*pSamePalettes,
											  BOOL		*pOurBrowserPalette,
											  BOOL		*pAllHaveBitmaps,
											  BOOL		*pAllWithinCount,
											  UINT32		*pPaletteEntries = NULL );

protected:

	// Export a bitmap.
	virtual BOOL WriteToFile ( BOOL End );

	// Get a pointer to the OutputDIB.
	virtual OutputDIB* GetOutputDIB(void) { return NULL; }

	// Base Class version - See PNG Filter
	virtual void InvertAlpha(LPBITMAPINFO lpBitmapInfo, LPBYTE lpBits) { return; }

	INT32 FindUnusedColour(LPBITMAPINFO pBMInfo, LPBYTE pBMBits);

	UINT32 Compression;			// Compression to use (JPEG = %, others = TRUE, FALSE)

	BOOL SecondPass;			// flag for whether we are rendering second pass on export
	BOOL DoingMask;				// flag for whether we are rendering the mask or not

	// Storage for the 8bpp mask that is made up in the first pass rendering on export
	LPBITMAPINFO pDestBMInfo;	
	LPBYTE pDestBMBytes;
	BYTE* pTempBitmapMask;				// WhiteArea mask generated during 1st pass render
	UINT32 CurrentScanline;				// Current scanline in the WhiteArea mask.

	INT32 TransColour;					// -1 == none, or the transparent colour.

	virtual BOOL SetExportHint(Document* pDoc);
	
	// Override this to provide the correct hint type
	virtual UINT32 GetHintType(void) { return(HINTTYPE_BAD); }

	INT32 m_BandNumber;	//  Tells you which band of the bitmap we are working on.
	//  Tells you if the user made a selection before opening the export dialog.
	BOOL m_bSelection;	
};

#endif // INC_MASKEDFILTER


