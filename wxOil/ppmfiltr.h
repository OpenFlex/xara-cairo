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

#ifndef INC_PPMFILTR
#define INC_PPMFILTR

#include "bitfilt.h"
#include "bmpprefs.h"  	// SelectionType
#include "maskedrr.h"	// MaskedRenderRegion derived off GRenderBitmap

class KernelBitmap;
//class OILFilter;

enum PMFileType
{
	PPM_BAD,
	PPM_BINARY,
	PPM_ASCII,	
	PGM_BINARY,
	PGM_ASCII,	
	PBM_BINARY,
	PBM_ASCII,	
};	

/********************************************************************************************

>	class BasePMFilter : public BitmapFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/95
	Purpose:	Provides most of the the handling for the PPM, PGM and PBM filters.

********************************************************************************************/

class BasePMFilter : public BaseBitmapFilter
{
	CC_DECLARE_DYNAMIC(BasePMFilter);
	
public:
	BasePMFilter();

	BOOL Init();

	virtual INT32 HowCompatible( PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize,
							   UINT32 FileSize );
	// Import related functions
	virtual BOOL ReadFromFile(OILBitmap* pOilBitmap);

protected:
	//
	// Import related functions
	//
	//virtual BOOL PrepareToImport();
	//virtual void CleanUpAfterImport();

	BOOL ReadFromFile( CCLexFile *File, LPBITMAPINFO *Info, LPBYTE *Bits, String_64 *ProgressString = NULL);

	BOOL ReadASCIIFromFile( CCLexFile *pLexFile, LPBYTE pBits,
						    INT32	Width, INT32 Height, INT32 ColoursPerRGB, INT32 BitsPerRGB,
							INT32 WidthOfLine,
						    String_64 *ProgressString = NULL, BOOL Forwards = TRUE);
	BOOL ReadBinaryFromFile( CCLexFile *pFile, LPBYTE pBits,
							 INT32 Width, INT32 Height, INT32 ColoursPerRGB, INT32 BitsPerRGB,
							 INT32 WidthOfLine,
							 String_64 *ProgressString = NULL, BOOL Forwards = TRUE);

	// Useful palette functions
	void PokePaletteEntry(LPRGBQUAD * Palette, BYTE red, BYTE green, BYTE blue);
	void MakeGreyScalePalette(LPRGBQUAD Palette);
	void Make16GreyScalePalette(LPRGBQUAD Palette);
	void MakeBlackAndWhitePalette(LPRGBQUAD Palette);

	// Functions that a filter derived off this must provide
	virtual BOOL CheckString(TCHAR * pHeader);
	virtual BOOL ReadDataIntoBitmap(INT32 Number, INT32 * Count, LPBYTE * pData, BOOL * NextPixel);

	// What the file type we are reading is
	PMFileType TypeOfPPM;

	// This is so we can remember what we thought of the GIF file.
	INT32 PPMHowCompatible;	

	INT32 x;					// current x position across bitmap
	INT32 y;					// current y position down bitmap
	INT32 TotalWidth;			// width in pixels of bitmap
	INT32 TotalHeight;		// height in pixels of bitmap
	INT32 TotalWidthOfLine;	// width of lien rounded to required word boundaries
	INT32 RGBColours;			// number of colours per colour component
	INT32 RGBBits;			// bits per colour component e.g. R, G and B
	INT32 PixelCounter;		// how many pixels we get per read

	INT32 Red;				// red component for 24bit files
	INT32 Green;				// green component for 24bit files
	INT32 Blue;				// blue component for 24bit files

	BYTE Bits;				// accumulator for bits in 1bpp files

public:
	// Check if this Bitmap filter can cope with saving at this Bpp/Colour depth
	virtual BOOL IsThisBppOk(UINT32 Bpp);
};

/********************************************************************************************

>	class PPMFilter : public BitmapFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/95
	Purpose:	Encapsulates a Unix PPM import filter.

********************************************************************************************/

class PPMFilter : public BasePMFilter
{
	CC_DECLARE_DYNAMIC(PPMFilter);
	
public:
	PPMFilter();

	BOOL Init();

protected:
	virtual BOOL CheckString(TCHAR * pHeader);
	virtual BOOL ReadDataIntoBitmap(INT32 Number, INT32 * Count, LPBYTE * pData, BOOL * NextPixel);
};

/********************************************************************************************

>	class PPMFilter : public BitmapFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/95
	Purpose:	Encapsulates a Unix PGM import filter.

********************************************************************************************/

class PGMFilter : public BasePMFilter
{
	CC_DECLARE_DYNAMIC(PGMFilter);
	
public:
	PGMFilter();

	BOOL Init();

protected:
	virtual BOOL CheckString(TCHAR * pHeader);
	virtual BOOL ReadDataIntoBitmap(INT32 Number, INT32 * Count, LPBYTE * pData, BOOL * NextPixel);
};

/********************************************************************************************

>	class PBMFilter : public BitmapFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/95
	Purpose:	Encapsulates a Unix PBM import filter.

********************************************************************************************/

class PBMFilter : public BasePMFilter
{
	CC_DECLARE_DYNAMIC(PBMFilter);
	
public:
	PBMFilter();

	BOOL Init();

protected:
	virtual BOOL CheckString(TCHAR * pHeader);
	virtual BOOL ReadDataIntoBitmap(INT32 Number, INT32 * Count, LPBYTE * pData, BOOL * NextPixel);
};


/********************************************************************************************

>	class PPMOILFilter : public OILFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/95
	Purpose:	Provide the OIL parts of the PPM filter which loads in the file as a BMP.
	SeeAlso:	PPMFilter

********************************************************************************************/

class PPMOILFilter : public OILFilter
{
public:
	PPMOILFilter(Filter *pFilter);
};

/********************************************************************************************

>	class PGMOILFilter : public OILFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/95
	Purpose:	Provide the OIL parts of the PGM filter which loads in the file as a BMP.
	SeeAlso:	PGMFilter

********************************************************************************************/

class PGMOILFilter : public OILFilter
{
public:
	PGMOILFilter(Filter *pFilter);
};

/********************************************************************************************

>	class PBMOILFilter : public OILFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/95
	Purpose:	Provide the OIL parts of the PBM filter which loads in the file as a BMP.
	SeeAlso:	PBMFilter

********************************************************************************************/

class PBMOILFilter : public OILFilter
{
public:
	PBMOILFilter(Filter *pFilter);
};



#endif // INC_PPMFILTR


