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

// Bitmap export palette interface class that provides an interface
// between the real palette and the sorted version of the palette

#ifndef INC_BMPALINT
#define INC_BMPALINT

/**************************************************************************************
>	class BitmapExportPaletteInterface : public CC_CLASS_MEMDUMP
	Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/11/2000
	Purpose:	Provides an interface between the real palette and the sorted version
				of the palette
**************************************************************************************/
class BitmapExportPaletteInterface : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(BitmapExportPaletteInterface);

private:	// Private constants
	enum {
		MAX_PALETTE_ENTRYS		= 256
	};

public:		// Public constants
	enum PaletteSortType{SORT_NONE, SORT_USE, SORT_LUMINANCE, SORT_HUE};

private:	// Data
	// Array index == value in real palette, value == value in sorted palette
	INT32 m_PaletteRealToSorted[MAX_PALETTE_ENTRYS];

	// Array index == value in sorted palette, value == value in real palette
	INT32 m_PaletteSortedToReal[MAX_PALETTE_ENTRYS];

	PaletteSortType m_CurrentSortType;

private:	// Statics
	// If this is false, we need to regenerate the arrays before using them again
	static bool m_SortedPaletteValid;

public:		// Constructors
	BitmapExportPaletteInterface();

public:		// Interface
	INT32		GetNumberOfColours();

	void			SetPaletteSortType(PaletteSortType newSortType);
	PaletteSortType	GetPaletteSortType();

	BYTE	GetRed	(INT32 index);
	BYTE	GetGreen(INT32 index);
	BYTE	GetBlue	(INT32 index);
	INT32		GetFlags(INT32 index);

	void	SetRed	(INT32 index, BYTE red);
	void	SetGreen(INT32 index, BYTE green);
	void	SetBlue	(INT32 index, BYTE blue);
	void	SetFlags(INT32 index, INT32 flags);

	// Function to convert from a index in the sorted palette to an index in the real palette
	INT32		SortedValueToRealValue(INT32 index);
	INT32		RealValueToSortedValue(INT32 index);

public:		// Static interface
	static void InvalidateSortedPalette();

private:	// Implementation
	void ValidateSortedPalette();

private:	// Static functions (so that they can be passed to qsort)
	static INT32 LuminanceComparisonFn(const INT32 *arg1, const INT32 *arg2);
	static INT32 HueComparisonFn(const INT32 *arg1, const INT32 *arg2);
};

#endif	// INC_BMPALINT
