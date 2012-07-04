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

#ifndef INC_FLASH_BITMAP_RECORD
#define INC_FLASH_BITMAP_RECORD

//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class FlashBitmapRecord : public CObject

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/10/99
	Purpose:	Maintains a record of the bitmaps used for fills.

********************************************************************************************/

class FlashBitmapRecord : public CCObject
{
public:
	// Constructor and destructor.
	FlashBitmapRecord ( void );									// Constructor.
	~FlashBitmapRecord ( void );								// Destructor.

	// Add and remove elements to a linked list.
	FlashBitmapRecord*	AddElement ( void );					// Adds an element.
	void				DeleteNextElement ( void );				// Deletes the next element.
	void				DeleteLastElement ( void );				// Deletes the last element.

	// Data access functions.
	OILBitmap*			GetBitmap ( void );						// Gets mpBitmap.
	WORD				GetBitmapID ( void );					// Gets mBitmapID.
	DocColour			GetContoneStart ( void );				// Gets mStartColour.
	DocColour			GetContoneEnd ( void );					// Gets mEndColour.
	BOOL				GetIsContone ( void );					// Gets mIsContoned.
	UINT32				GetTransparency ( void );				// Gets mTransparency.
	FlashBitmapRecord*	GetNext ( void );						// Gets mpNext.
	FlashBitmapRecord*	GetLast ( void );						// Gets mpLast.

	// Set value functions.
	void				SetBitmap ( OILBitmap *pBitmap );		// Sets mpBitmap.
	void				SetBitmapID ( WORD BitmapID );			// Sets mBitmap.
	void				SetContoneColours ( const DocColour &Start,	// Sets mStart
											const DocColour &End );	// and mEnd.
	void				SetIsContone ( BOOL State );			// Sets mIsContone.
	void				SetTransparency ( UINT32 Transparency );	// Sets mTransparency.
	void				SetNext ( FlashBitmapRecord *pNext );	// Sets the value of mpNext.
	void				SetLast ( FlashBitmapRecord *pLast );	// Sets the value of mpLast.

private:
	OILBitmap			*mpBitmap;								// Pointer to the bitmap.
	WORD				mBitmapID;								// ID value for the bitmap.
	DocColour			mStartColour;							// Start colour for contone.
	DocColour			mEndColour;								// End colour for contone.
	BOOL				mIsContone;								// Is the fill contoned?
	UINT32				mTransparency;							// The bitmap's transparency.
	FlashBitmapRecord	*mpNext;								// Pointer to the next node.
	FlashBitmapRecord	*mpLast;								// Pointer to the next node.
};

#endif
