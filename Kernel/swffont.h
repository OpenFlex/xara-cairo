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

//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#ifndef INC_FLASH_FONT_RECORD
#define INC_FLASH_FONT_RECORD

#define FLASH_TEXT_ARRAY_SIZE 256

/********************************************************************************************
>	class FlashFontRecord : public CObject

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Purpose:	Maintains a record of all text styles used, and the characters they contain.
				This is then used when exporting path records to create the DefineFont
				entries within a Flash format file when exporting the image. Elements are
				stored in a double-linked list.

********************************************************************************************/

class FlashFontRecord : public CCObject
{
public:
	CC_DECLARE_DYNAMIC( FlashFontRecord )

	// Constructor and destructor.
	FlashFontRecord ( void );								// Constructor.
	~FlashFontRecord ( void );								// Destructor.

	// Add and remove elements to a linked list.
	FlashFontRecord*	AddElement ( void );				// Adds an element to the list.
	void				DeleteLastElement ( void );			// Deletes the element mpLast.
	void				DeleteNextElement ( void );			// Deletes the element mpNext.

	// Data access functions.
	WORD				GetTypeface ( void );				// Gets the value of mTypeface.
	WORD				GetFontID ( void );					// Gets the value of mFontID.
	BOOL				GetIsBold ( void );					// Gets the value of mIsBold.
	BOOL				GetIsItalic ( void );				// Gets the value of mIsItalic.
	WCHAR*				GetGlyphs ( void );					// Gets a pointer to mGlyphs.
	Path**				GetPaths ( void );					// Gets a pointer to mGlyphs.
	FlashFontRecord*	GetLast ( void );					// Gets mpLast.
	FlashFontRecord*	GetNext ( void );					// Gets mpNext.

	// Set value functions.
	void				SetTypeface ( WORD Typeface );		// Sets the value of mTypeface.
	void				SetFontID ( WORD FontID );			// Sets the value of mFontID.
	void				SetIsBold ( BOOL IsBold );			// Sets the value of mIsBold.
	void				SetIsItalic ( BOOL IsItalic );		// Sets the value of mIsItalic.
	BOOL				AddGlyph ( WCHAR Glyph,				// Adds a glyph to mGlyphs.
								   INT32 &Code );
	void				AddPath ( Path* ToAdd, INT32 Index );	// Adds a glyph path to the array.
	void				SetLast ( FlashFontRecord *pLast );	// Sets the value of mpLast.
	void				SetNext ( FlashFontRecord *pNext );	// Sets the value of mpNext.

private:
	// Member variables.
	WORD				mTypeface;							// A Camelot font name handle.
	WORD				mFontID;							// The font's ID number.
	BOOL				mIsBold;							// Is the font bold?
	BOOL				mIsItalic;							// Is the font italic?
	WCHAR				mGlyphs [FLASH_TEXT_ARRAY_SIZE];	// A list of the glyphs used.
	Path				*mPaths [FLASH_TEXT_ARRAY_SIZE];	// An array of the paths.
	FlashFontRecord		*mpLast;							// Pointer to the previous node.
	FlashFontRecord		*mpNext;							// Pointer to the next node.
};

#endif
