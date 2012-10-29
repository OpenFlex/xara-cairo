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

#include "camtypes.h"
#include "swffont.h"

CC_IMPLEMENT_DYNAMIC( FlashFontRecord, CCObject )

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	FlashFontRecord::FlashFontRecord ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Creates a FlashFontRecord list node, and initialises any values.

********************************************************************************************/

FlashFontRecord::FlashFontRecord ( void )
{
	// Initialise the member variables, so as to avoid any unpleasentness later.
	mFontID		= 0;		// Set as 0.
	mTypeface	= 0;		// Default to 0.
	mIsBold		= FALSE;	// Initially the font isn't bold.
	mIsItalic	= FALSE;	// Initially the font isn't italic.

	// Pointers should always be initialised to NULL when created.
	mpLast		= NULL;		// No previous nodes.
	mpNext		= NULL;		// No subsequent nodes.

	// Ensure that the arrays are full of 0s.
	for ( UINT32 i = 0; i < FLASH_TEXT_ARRAY_SIZE; i++ )
	{
		mGlyphs [i] = 0;
		mPaths [i] = NULL;
	}
}

/********************************************************************************************

>	FlashFontRecord::~FlashFontRecord ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Destroys this instance of FlashFontRecord.

********************************************************************************************/

FlashFontRecord::~FlashFontRecord ( void )
{
	// Clean up any stray values.
	for ( UINT32 i = 0; i < FLASH_TEXT_ARRAY_SIZE; i++ )
	{
		Path* pPath = mPaths[i];

		if(pPath)
			delete pPath;
	}
}

/********************************************************************************************

>	FlashFontRecord* FlashFontRecord::AddElement ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	pTail - The pointer to the new node.
	Purpose:	Adds an element to the tail of the list.

********************************************************************************************/

FlashFontRecord* FlashFontRecord::AddElement ( void )
{
	FlashFontRecord *pTail = new FlashFontRecord;
	
	// Set the appropriate pointers.
	pTail->SetLast ( this );		// Ensure that a reference exists to this object...
	pTail->SetNext ( mpNext );		// Avoids any problems if mpLast isn't NULL.
	mpNext = pTail;					// ... and a reference exists to the new one.

	return pTail;
}

/********************************************************************************************

>	void FlashFontRecord::DeleteLastElement ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Deletes the previous item in the list.

********************************************************************************************/

void FlashFontRecord::DeleteLastElement ( void )
{
	FlashFontRecord *pToDelete = mpLast;
	
	// Reset mpLast to be mpLast->GetLast (), so that the list isn't broken.
	mpLast = mpLast->GetLast ();

	delete pToDelete;
}

/********************************************************************************************

>	void FlashFontRecord::DeleteNextElement ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Deletes the next item in the list.

********************************************************************************************/

void FlashFontRecord::DeleteNextElement ( void )
{
	FlashFontRecord *pToDelete = mpNext;
	
	// Reset mpNext to be mpNext->GetNext (), so that the list isn't broken.
	mpNext = mpNext->GetNext ();

	delete pToDelete;
}

/********************************************************************************************

>	WORD FlashFontRecord::GetTypeface ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/10/99
	Inputs:		-
	Returns:	mTypeface - The typeface ID number.
	Purpose:	Gets the value of mFontID.

********************************************************************************************/

WORD FlashFontRecord::GetTypeface ( void )
{
	return mTypeface;
}

/********************************************************************************************

>	WORD FlashFontRecord::GetFontID ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	mFontID - The font ID number.
	Purpose:	Gets the value of mFontID.

********************************************************************************************/

WORD FlashFontRecord::GetFontID ( void )
{
	return mFontID;
}


/********************************************************************************************

>	BOOL FlashFontRecord::GetIsBold ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	IsBold - mIs this font style bold?
	Purpose:	Gets the value of mIsBold.

********************************************************************************************/

BOOL FlashFontRecord::GetIsBold ( void )
{
	return mIsBold;
}

/********************************************************************************************

>	BOOL FlashFontRecord::GetIsItalic ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	IsItalic - mIs this font style Italic?
	Purpose:	Gets the value of mIsItalic.

********************************************************************************************/

BOOL FlashFontRecord::GetIsItalic ( void )
{
	return mIsItalic;
}

/********************************************************************************************

>	WCHAR* FlashFontRecord::GetGlyphs ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	*mGlyphs - A pointer to the array of characters used.
	Purpose:	Gets a pointer to mGlyphs.

********************************************************************************************/

WCHAR* FlashFontRecord::GetGlyphs ( void )
{
	return mGlyphs;
}

/********************************************************************************************

>	Path** FlashFontRecord::GetPaths ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/10/99
	Inputs:		-
	Returns:	*mpPaths - A pointer to the array of paths of the characters used.
	Purpose:	Gets a pointer to mpPaths.

********************************************************************************************/

Path** FlashFontRecord::GetPaths ( void )
{
	return mPaths;
}

/********************************************************************************************

>	FlashFontRecord* FlashFontRecord::GetLast ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	*mpLast - A pointer to the previous node in the linked list.
	Purpose:	Gets mpLast.

********************************************************************************************/

FlashFontRecord* FlashFontRecord::GetLast ( void )
{
	return mpLast;
}

/********************************************************************************************

>	FlashFontRecord* FlashFontRecord::GetNext ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		-
	Returns:	*mpNext - A pointer to the next node in the linked list.
	Purpose:	Gets mpNext.

********************************************************************************************/

FlashFontRecord* FlashFontRecord::GetNext ( void )
{
	return mpNext;
}

/********************************************************************************************

>	void FlashFontRecord::SetTypeface ( WORD Typeface )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/10/99
	Inputs:		Typeface - The ID number of a font in the Camelot image.
	Returns:	-
	Purpose:	Sets the value of mTypeface. This is a handle to a font name that is stored
				within the Camelot font manager.

********************************************************************************************/

void FlashFontRecord::SetTypeface ( WORD Typeface )
{
	mTypeface = Typeface;
}

/********************************************************************************************

>	void FlashFontRecord::SetFontID ( WORD FontID )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		FontID - The ID number of a font within a Flash file.
	Returns:	-
	Purpose:	Sets the value of mFontID, which is the number used to relate a DefineFont
				entry to a DefineText entry.

********************************************************************************************/

void FlashFontRecord::SetFontID ( WORD FontID )
{
	mFontID = FontID;
}

/********************************************************************************************

>	void FlashFontRecord::SetIsBold ( BOOL IsBold )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		IsBold - Is the current font in a bold typeface?
	Returns:	-
	Purpose:	Sets the value of mIsBold.

********************************************************************************************/

void FlashFontRecord::SetIsBold ( BOOL IsBold )
{
	mIsBold = IsBold;
}

/********************************************************************************************

>	void FlashFontRecord::SetIsItalic ( BOOL IsItalic )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		IsItalic - Is the current font in an Italic typeface?
	Returns:	-
	Purpose:	Sets the value of mIsItalic.

********************************************************************************************/

void FlashFontRecord::SetIsItalic ( BOOL IsItalic )
{
	mIsItalic = IsItalic;
}

/********************************************************************************************

>	BOOL FlashFontRecord::AddGlyph ( WCHAR Glyph,
									 INT32 &Code )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		Glyph - A single unicode character.
				&Code - A reference which contains the position of the glyph in the array.
	Returns:	TRUE if a character is added, otherwise false.
	Purpose:	Adds a glyph to mGlyphs.

********************************************************************************************/

BOOL FlashFontRecord::AddGlyph ( WCHAR Glyph,
								 INT32 &Code )
{
	// Set up the return values.
	BOOL bResult = TRUE;
	Code = 0;

	// Compare the value of the new character to the entries in the array.
	while ( mGlyphs [Code] != 0 )
	{
		if ( mGlyphs [Code] == Glyph )
		{
			// The character is already present within the listing, so quit out.
			bResult = FALSE;
			break;
		}

		// Increment the value of Code so that it points to the next element in the array.
		Code++;
	}

	mGlyphs[Code] = Glyph;			// Write the new value into the array.

	return bResult;
}

/********************************************************************************************

>	void FlashFontRecord::AddPath ( Path* ToAdd, INT32 Index )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		ToAdd - A pointer to a path.
				Index - The matrix element to which you want to add it to.
	Returns:	-
	Purpose:	Adds a path reference to mpPaths.

********************************************************************************************/

void FlashFontRecord::AddPath ( Path* ToAdd, INT32 Index )
{
	mPaths [ Index ] = ToAdd;
}

/********************************************************************************************

>	void FlashFontRecord::SetLast ( FlashFontRecord *pLast )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		pLast - A pointer to the previous FlashFontRecord in the linked list.
	Returns:	-
	Purpose:	Sets the value of mpLast.

********************************************************************************************/

void FlashFontRecord::SetLast ( FlashFontRecord *pLast )
{
	mpLast = pLast;
}

/********************************************************************************************

>	void FlashFontRecord::SetNext ( FlashFontRecord *pNext )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/99
	Inputs:		pNext - A pointer to the next FlashFontRecord in the linked list.
	Returns:	-
	Purpose:	Sets the value of mpNext.

********************************************************************************************/

void FlashFontRecord::SetNext ( FlashFontRecord *pNext )
{
	mpNext = pNext;
}
