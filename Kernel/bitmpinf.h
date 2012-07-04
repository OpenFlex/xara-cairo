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


// bitmap inofmration structure

#ifndef	INC_BITMPINF
#define	INC_BITMPINF

class BitmapInfo : public SimpleCCObject
{
public:

	UINT32	PixelWidth;
	UINT32	PixelHeight;
	UINT32	PixelDepth;									// e.g. 1,2,4,8,16,24,32

	UINT32	NumPaletteEntries;							// 0 for no palette

	MILLIPOINT	RecommendedWidth;						// original size
	MILLIPOINT	RecommendedHeight;

	UINT32	HDPI;										// Horizontal DPI
	UINT32	VDPI;										// Vertical DPI

	UINT32 	MemoryUsed;									// sizeof bitmap & headers
};

#endif
