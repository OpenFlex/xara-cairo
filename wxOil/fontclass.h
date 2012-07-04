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

// Declares the known font classes

/*
*/

#ifndef INC_FONTCLASS
#define INC_FONTCLASS

/********************************************************************************************
	The types of fonts the OIL font manager recognises so far
********************************************************************************************/

typedef enum FontClass {
	FC_UNDEFINED = 0,
	FC_RASTER,
	FC_DEVICE,
	FC_TRUETYPE,
	FC_ATM,

	// Add further font classes before this
	FC_ILLEGAL
};

// The kernel likes dealing with LOGFONT and ENUMLOGFONT structures, so we do it this favour

#if !defined(__WXMSW__)
struct LOGFONT
{
	String_64 FaceName;
};
typedef LOGFONT		   *PLOGFONT, *LPLOGFONT;

struct ENUMLOGFONT
{
	LOGFONT elfLogFont;
};
#endif

#endif
