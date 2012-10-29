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

#ifndef INC_BMPFILTR
#define INC_BMPFILTR

#include "bitfilt.h"
#include "bmpprefs.h"  // SelectionType
//#include "imglib.h"
//#include "accures.h"
//#include "tim.h"

class CXaraFileRecord;

enum BMP_COMPRESSION
{
	BMP_RGB		= 0,
	BMP_RLE		= 1
};



/********************************************************************************************
>	class BMPExportOptions : public BitmapExportOptions

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/96
	Purpose:   	Base class for storing information about the bitmap we're exporting.
********************************************************************************************/

class BMPExportOptions : public BitmapExportOptions
{
	CC_DECLARE_DYNCREATE(BMPExportOptions)
public:
	BMPExportOptions();
    BMPExportOptions(const FilterType FilterID, const StringBase* pFilterName);

	virtual BOOL	RetrieveDefaults();
	virtual BOOL	SetAsDefaults() const;

	// Save and load from named export set properties.
	virtual BOOL Write(CXaraFileRecord* pRec);
	virtual BOOL Read(CXaraFileRecord* pRec);

	virtual BOOL	GetSupportsImageMap() { return TRUE; }

	virtual DITHER	GetDither() const;
	virtual BOOL	SetDither(const DITHER& Dither);

	PALETTE	GetPalette() const;
	BOOL	SetPalette(const PALETTE& Palette);

	BMP_COMPRESSION	GetCompression() const;
	BOOL			SetCompression(const BMP_COMPRESSION& Compression);

	// for object copying and comparing
	virtual BOOL CopyFrom(BitmapExportOptions *pOther);
	virtual BOOL FileTypeChangeCopyFrom(BitmapExportOptions *pOther);
//	virtual BOOL Equal(BitmapExportOptions *pOther);
	
	virtual UINT32 GetFilterNameStrID() { return _R(IDT_FILTERNAME_BMP) /*_R(IDN_FILTERNAME_ACCUSOFTBMP)*/ /*_R(IDT_BMP_FILTERNAME) */;}


protected:
	// Parameters that the dialog can set
	DITHER				m_Dither;
	PALETTE				m_Palette;
	BMP_COMPRESSION		m_Compression;
};


/********************************************************************************************

>	class BMPFilter : public BitmapFilter

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/6/94
	Purpose:	Encapsulates a Windows BMP export filter. Will probably import one day too.

********************************************************************************************/

class BMPFilter : public BaseBitmapFilter
{
	CC_DECLARE_DYNAMIC(BMPFilter);
	
public:
	BMPFilter();
	BOOL Init();
	virtual INT32 HowCompatible( PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize,
							   UINT32 FileSize );

	// How to get and set details on the default export depth, dpi ...
	static UINT32 GetDefaultExportDepth();
	static double GetDefaultExportDPI();
	static void SetDefaultExportDepth( UINT32 );
	static void SetDefaultExportDPI( double );

	static UINT32 GetDefaultExportDither();
	static void SetDefaultExportDither( UINT32 );

	virtual FilterType GetFilterType() const { return BMP_UNCOMPRESSED; }

	// Import related functions
	virtual BOOL ReadFromFile(OILBitmap* pOilBitmap);

	// This is the function for native/web files to use
    virtual BOOL ReadFromFile(OILBitmap* pOilBitmap, BaseCamelotFilter *pFilter,
							  CCLexFile * pFile, BOOL IsCompressed);

	void AlterPaletteContents( LPLOGPALETTE pPalette );
	virtual void PostGetExportOptions(BitmapExportOptions* pOptions);

protected:
	// Export related functions
	virtual BitmapExportOptions*	CreateExportOptions() const;

	virtual BOOL WriteToFile( BOOL End );
	virtual BOOL EndWriteToFile( );
	virtual BOOL GetExportOptions(BitmapExportOptions* pOptions);
	virtual void CleanUpAfterExport();

	virtual BOOL WriteBitmapToFile(KernelBitmap* pKernelBitmap, double Dpi);

	// this is used for the actual writing of the file
	virtual BOOL WriteDataToFile( BOOL End, UINT32 Bpp, UINT32 Compression);
	static BOOL EndWriteDataToFile( );
	static OutputDIB DestDIB;

	// This is so we can remember what we thought of the BMP file.
	INT32 BMPHowCompatible;

	// Function to see if we should export via Accusoft filters or not
	BOOL ExportViaAccusoftFilters();

	// Find out which way we need to render
	virtual BOOL GetRenderBottomToTop();

public:
	// Function for web/native filters to use to write out the bitmap data to file
	virtual BOOL WriteBitmapToFile(KernelBitmap* pKernelBitmap, BaseCamelotFilter *pFilter,
								   CCLexFile *pFile, INT32 Compression);

	// Check if this Bitmap filter can cope with saving at this Bpp/Colour depth
	virtual BOOL IsThisBppOk(UINT32 Bpp);

	// Public way of finding out how compatable the BMP filter thought the file was
	// We might want to bring in the Accusoft filter to help out.
	INT32 GetBmpCompatibility();
};

#endif
