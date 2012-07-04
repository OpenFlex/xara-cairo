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


// kernel class to encompass bitmaps

#ifndef	INC_FILTERTYPES
#define	INC_FILTERTYPES

/*********************************************************************************************

>	enum 		FILTERID

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/3/2006
	Purpose:	Enumerate different types of filter

**********************************************************************************************/ 

typedef enum FILTERID
{
	INVALID = -1,

	TIFF_UNCOMPRESSED =	0,
	BMP_UNCOMPRESSED,
	PCX,
	TARGA,
	GIF,
	WPG,
	WMF,
	TIFF_HUFFMAN,
	TIFF_G3_FAX,
	TIFF_LZW,
	TIFF_G4_FAX,
	DCX,
	BMP_COMPRESSED,
	JPEG,
	EPS,
	PICT,
	TIFF_PACK,
	TIFF_2D,
	CALS,
	LASER_DATA,
	XBM,
	MACPAINT,
	GX2,
	KOFAX,
	IOCA,
	ICON,
	IFF_ILBM,
	CLIP,
	IMG,
	BROOK_TROUT,
	MSP,
	CUT,
	TARGA16,
	CCITT_G3,
	CCITT_G4,
	XPM,
	XWD,
	RAST,
	ASCII,
	PHOTOCD,
	TIFF_JPEG,
	PHOTOSHOP,
	IMNET,
	PNG,
	GIF_INTERLACED,
	XEROX_EPS,
	TIFF_ABIC,
	TIFF_ABIC_BW,
	DIB,
	MODCA_IOCA,
						UNDEFINED50,
	TIFF_G4_FAX_FO,
	CCITT_G4_FO,
	CCITT_G3_FO,
	FLASH_PIX,
	IFF_5,
	DICOM,
	PCL_1,
	WINFAX,

	PDF,
	SCITEX,
	MAG,
	DCS,
	EPS_BITMAP,
	EPS_BITMAP_G4,
	NCR,
	TI_GIF,
	TI_GIF_INTERLACED,
	TI_GIF_TRANSPARENT,
	TI_GIF_TRANSINTER,
	TI_GIF_ANIM,
	MAKE_BITMAP_FILTER,
	PNG_INTERLACED,
	PNG_TRANSPARENT,
	PNG_TRANSINTER,

	IMAGEMAGICK,

	// --- Insert new Filter Types just above here ---

	MAXFILTERS
} FilterType;



#endif
