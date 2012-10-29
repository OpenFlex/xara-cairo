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


// Header for PNGUtil which suprisingly enough contains lots of
// useful routines for:-
//		reading in a PNG file as a bitmap
//

// Code based on the PNGLib code which has the following

#ifndef INC_PNGUTIL
#define	INC_PNGUTIL

#include "png.h"						// png_colorp

/********************************************************************************************

>	class PNGUtil : public CC_CLASS_MEMDUMP

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/05/96
	Purpose:	Contains functions to read in a PNG file as a DIB.
	SeeAlso:	OutputPNG;

********************************************************************************************/

class PNGUtil : public CC_CLASS_MEMDUMP
{
public:
	// Give my name in memory dumps
	// If you need a different sort of decare, replace this one. 
	// See CCObject in the help file for info about DECLARE types
	CC_DECLARE_MEMDUMP(PNGUtil);

	PNGUtil();
	~PNGUtil();

	static BOOL ReadFromFile( CCLexFile *File, LPBITMAPINFO *Info, LPBYTE *Bits,
							  INT32 *TransColour, 
							  String_64 *ProgressString = NULL,
							  BaseCamelotFilter *pFilter = NULL);
//	static BOOL WriteToFile ( CCLexFile *, LPBITMAPINFO Info, LPBYTE Bits,
//							  String_64 *ProgressString = NULL);

//	static void DefaultErrorHandler(UINT32 MessageID, TCHAR * pMessage = NULL);
	static void DefaultErrorHandler();

	// Public access to the pFile exception handling pointer
	static BOOL SetCCFilePointer(CCLexFile* pNewFile);
	static CCLexFile* GetCCFilePointer();

protected:
	static BOOL ReadColourMap(INT32 Png_Entries, png_colorp pPNGPalette, INT32 number, LPRGBQUAD lpPalette);
	static BOOL GenerateGreyPalette(INT32 PaletteSize, LPRGBQUAD lpPalette);

private:
	// Some useful variables
	// I do not think this variable is used anywhere but I left
	// it as I do not know what else it effects -- Jonathan 8/2000
	static INT32 Transparent;			// colour or -1 = no transparency

	// exception handling pointer
	static CCLexFile* pFile;			// The CCLexFile class that we are using
};

#endif // INC_PNGUTIL
