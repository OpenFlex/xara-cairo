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

#ifndef INC_PNGFILTR
#define INC_PNGFILTR

#include "maskfilt.h"
#include "outptpng.h"
#include "bmpprefs.h"  	// SelectionType
//#include "filtrres.h"

class KernelBitmap;

/********************************************************************************************

>	class PNGExportOptions : public MaskedFilterExportOptions

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/96
	Purpose:   	Base class for storing information about the bitmap we're exporting.

********************************************************************************************/

class PNGExportOptions : public MaskedFilterExportOptions
{
CC_DECLARE_DYNCREATE(PNGExportOptions)

public:
	static BOOL Declare();

    PNGExportOptions(const FilterType FilterID, const StringBase* pFilterName);
	PNGExportOptions() {};

	virtual BOOL	GetSupportsImageMap() { return TRUE; }

	virtual BOOL	RetrieveDefaults();
	virtual BOOL	SetAsDefaults() const;
	
	virtual UINT32 GetFilterNameStrID() { return _R(IDS_FILTERNAME_PNG);}



protected:
	static	UINT32 g_CompactedFlagsForDefaults;
};

/********************************************************************************************

>	class PNGFilter : public MaskedFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/96
	Purpose:	Encapsulates a PNG export filter.
				Derives off the masked filter which provides funcitonality for doing masked
				bitmap export and import.

********************************************************************************************/

class PNGFilter : public MaskedFilter
{
	CC_DECLARE_DYNAMIC(PNGFilter);
	
public:

	PNGFilter();
	BOOL Init();

	virtual INT32 HowCompatible( PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize,
		UINT32 FileSize );

	virtual FilterType GetFilterType() const { return PNG; }

	// Import related functions
	virtual BOOL ReadFromFile(OILBitmap* pOilBitmap);
	// This is the function for native/web files to use
    virtual BOOL ReadFromFile(OILBitmap* pOilBitmap, BaseCamelotFilter* pFilter,
							  CCLexFile* pFile, BOOL IsCompressed);

	// Function for web/native filters to use to write out the bitmap data to file
	virtual BOOL WriteBitmapToFile(KernelBitmap* pKernelBitmap, BaseCamelotFilter* pFilter,
								   CCLexFile* pFile, INT32 Compression);

	// Check if this Bitmap filter can cope with saving at this Bpp/Colour depth
	virtual BOOL IsThisBppOk(UINT32 Bpp);

	// Public way of finding out how compatable the PNG filter thought the file was
	// We might want to bring in the Accusoft filter to help out.
	virtual INT32 GetPNGCompatibility() { return PNGHowCompatible; }

	// Virtual overrides
	virtual UINT32 GetExportMsgID();
	virtual void PostGetExportOptions(BitmapExportOptions* pOptions);

protected:

	// Invert the alpha channel.
	virtual void InvertAlpha ( LPBITMAPINFO	lpBitmapInfo,
							   LPBYTE		lpBits );

	// Get the correct output DIB.
	virtual OutputDIB* GetOutputDIB ( void );

	virtual BitmapExportOptions*	CreateExportOptions() const;

	virtual BOOL GetExportOptions( BitmapExportOptions* pOptions );
	virtual void CleanUpAfterExport();
	virtual BOOL EndWriteToFile();

	virtual BOOL WriteFileHeader(void) { return TRUE; }
	virtual BOOL WritePreFrame(void);
	virtual BOOL WritePreSecondPass(void);
	virtual BOOL WritePostOptimisedPalette(void) { return TRUE; }
	virtual BOOL WriteFrame(void);
	virtual BOOL WritePostFrame(void);
	virtual BOOL WriteFileEnd(void);

	virtual BOOL WriteBitmapToFile(KernelBitmap* pKernelBitmap, double Dpi);

	// this is used for the actual writing of the file
	static BOOL WriteDataToFile( BOOL End, UINT32 Bpp, UINT32 Compression);
	static BOOL WriteToFile ( CCLexFile*, LPBITMAPINFO Info, LPBYTE Bits,
						 	  String_64* ProgressString = NULL);

	// This is the form used for direct saving bitmaps into the native/web file format
	static BOOL WriteToFile ( CCLexFile*, LPBITMAPINFO Info, LPBYTE Bits,
							  BOOL Interlace, INT32 TransparentColour,
						 	  BaseCamelotFilter* pFilter = NULL);

	void AlterPaletteContents( LPLOGPALETTE pPalette );//ap

#ifdef DO_EXPORT
	// The class we use for actually outputting the PNG data and converting from 32 to n bpps
	static OutputPNG DestPNG;
#endif
	
	// This is so we can remember what we thought of the GIF file.
	INT32 PNGHowCompatible;

	static FilterType s_FilterType;						// Type of filter in use i.e. PNG

	// The string to display when exporting the second stage.
	UINT32 Export2ndStageMsgID;
};

#endif // INC_PNGFILTR


