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


#ifndef INC_FONTS
#define INC_FONTS



typedef enum
{
	STOCKFONT_STATUSBAR = 0,		// The Status Line description text
	STOCKFONT_STATUSBARBOLD,		// The Status Line description text (Bold text for)
	STOCKFONT_DIALOGBARCLIENT,		// General text in bars
	STOCKFONT_DIALOGBARSMALL,		// Text for bar buttons in 'small' mode
	STOCKFONT_DIALOGBARLARGE,		// Text for bar buttons in 'large' mode
	STOCKFONT_DIALOGBARTITLE,		// Text for bar titlebars
	STOCKFONT_EDITFIELDLARGE,		// Edit field in 'large' mode
	STOCKFONT_EDITFIELDSMALL,		// Edit field in 'small' mode
    STOCKFONT_GALLERYLIST,			// Text in a gallery list (defunct)
	STOCKFONT_BUBBLEHELP,			// Bubble help display font
	STOCKFONT_SPLASHBOXINFO,		// Splash box information
	STOCKFONT_RNDRGNFIXEDTEXT,		// Text in kernel-rendered dialogues (e.g. supergalleries)
	STOCKFONT_RULERS,				// Text in the rulers
	STOCKFONT_DIALOG,				// Text in dialogs (a user selected font)
	// Add new stock font identifiers here...

	STOCKFONT_MAXIMUMINDEX			// This must be the last item, so we allocate enough
} StockFont;						// memory for the full range of stock fonts



// Do not change this - it should automatically update if new stock fonts are added
const INT32 NUMSTOCKFONTS = (const INT32) STOCKFONT_MAXIMUMINDEX;



/********************************************************************************************

>	class FontFactory

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/05/94
	Purpose:	Provide a centralised place for claiming commonly used fonts.
				All fonts allocated here are automatically released when Camelot shuts down.

********************************************************************************************/

class FontFactory
{
public:
	static BOOL Init();
	static void Deinit();

	static HFONT GetFont(StockFont);
	static CFont *GetCFont(StockFont);
	static BOOL ApplyFontToWindow(HWND,StockFont);
	static BOOL GetSystemDialogFont(LOGFONT* pLogFont);

	// UIC 
	static BOOL InvalidateFont(StockFont); 
	static BOOL CheckSystemBarFontsChanged();
	static BOOL CheckSystemStatusLineFontChanged();

private:
	// The array of stock font handles.
	static CFont *Fonts;

	// The screen details
	static SIZE PixelsPerInch;

	static String_32 FontDBSmall;
	static String_32 FontEFSmall;

	static INT32 FontDBSmallSize;
	static INT32 FontEFSmallSize;

	static BOOL bNoBitmapFonts;
};


#endif
