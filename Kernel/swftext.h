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

#include "nodetext.h"
#include "swfshape.h"	// For FlashColour.

#ifndef INC_FLASH_TEXT_RECORD
#define INC_FLASH_TEXT_RECORD

#define FTR_STRING_SIZE 256

/********************************************************************************************

>	class FlashTextRecord : public CObject

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/10/99
	Purpose:	Maintains a record of the string being used.

********************************************************************************************/

class FlashTextRecord : public CCObject
{
public:
	// Constructor and destructor.
	FlashTextRecord ( void );								// Constructor.
	~FlashTextRecord ( void );								// Destructor.

	// Add and remove elements to a linked list.
	FlashTextRecord*	AddElement ( void );				// Adds an element to the list.
	void				DeleteLastElement ( void );			// Deletes the element mpLast.
	void				DeleteNextElement ( void );			// Deletes the element mpNext.

	// Data access functions.
	INT32*				GetString ( void );					// Gets a pointer to mText.
	BOOL				IsFull ( void );					// Is the string full?
	DocCoord			GetPosition ( void );				// Gets the value of mPosition.
	DocRect				GetBounds ( void );					// Gets the value of mBounds.
	INT32*				GetAdvances ( void );				// Gets a pointer to mAdvances.
	WORD*				GetSizes ( void );					// Gets mCharacterSize [].
	FlashColour*		GetColours ( void );				// Gets mCharacterColour [].
	WORD*				GetFontStyles ( void );				// Gets mCharacterStyle [].
	INT8*				GetOffsets ( void );				// Gets mOffsets [].
	FIXED16				GetAspect ( void );					// Gets mAspectRatio.
	INT32				GetAscent ( void );					// Gets mAscent.
	INT32					GetCount ( void );					// Gets the number of characters.
	WORD				GetTextID ( void );					// Gets the ID value for the text.
	FlashTextRecord*	GetLast ( void );					// Gets mpLast.
	FlashTextRecord*	GetNext ( void );					// Gets mpNext.

	// Set value functions.
	INT32					AddChar ( TextChar *pTheLetter,		// Appends TheLetter to mText.
								  INT32 FlashCode );
	void				SetPosition ( DocCoord Point );		// Sets the value of mPosition.
	void				SetBounds ( DocRect Bounds );		// Sets the value of mTextBounds.
	void				SetAdvance ( INT32 Advance,			// Sets the value of mAdvances at
									  INT32 i );				// position i. ( mAdvances [i] ).
	void				SetSize ( MILLIPOINT Size,			// Sets mCharacterSize [i].
								  INT32 i );
	void				SetColour ( DocColour *Colour,		// Sets mCharacterColour [i].
									UINT32 *Alpha,
									INT32 i );
	void				SetStyle ( WORD Style,				// Sets mCharacterStyle [i].
								   INT32 i );
	void				SetOffset ( INT32 Offset,			// Sets mOffsets [i].
									INT32 i );
	void				SetAspect ( FIXED16 AspectRatio );	// Sets mAspectRatio.
	void				SetTextID ( WORD ID );				// Sets mTextID.
	void				SetAscent ( INT32 Ascent );			// Sets mAscent.
	void				SetLast ( FlashTextRecord *pLast );	// Sets the value of mpLast.
	void				SetNext ( FlashTextRecord *pNext );	// Sets the value of mpNext.

	// Matrix storage functions.
	INT32				GetSkewX ( void );					// Get mSkewX.
	INT32				GetSkewY ( void );					// Get mSkewY.
	INT32				GetScaleX ( void );					// Get mScaleX.
	INT32				GetScaleY ( void );					// Get mScaleY.

	void				SetSkewX ( INT32 Skew );				// Set mSkewX.
	void				SetSkewY ( INT32 Skew );				// Set mSkewY.
	void				SetScaleX ( INT32 Scale );			// Set mScaleX.
	void				SetScaleY ( INT32 Scale );			// Set mScaleY.

private:
	// Member variables.
	DocCoord			mPosition;							// The position of the text.
	DocRect				mTextBounds;						// The text's bounding box.
	INT32					mText [FTR_STRING_SIZE];			// A string containing the text.
	INT32				mAdvances [FTR_STRING_SIZE];		// The advances for the text.
	WORD				mCharacterSize [FTR_STRING_SIZE];	// The sizes of the characters.
	FlashColour			mCharacterColour [FTR_STRING_SIZE];	// The colours of the characters.
	WORD				mCharacterStyle [FTR_STRING_SIZE];	// The letter's font handles.
	INT8				mOffsets [FTR_STRING_SIZE];			// A record of the Y offsets.
	INT32					mCurrent;							// The current element being used.
	FIXED16				mAspectRatio;						// The aspect ratio of the font.
	INT32				mAscent;							// The ascent value for the font.
	WORD				mTextID;							// The ID for PlaceObject.
	FlashTextRecord		*mpLast;							// Pointer to the previous node.
	FlashTextRecord		*mpNext;							// Pointer to the next node.
	INT32				mScaleX;							// The sine of the rotation.
	INT32				mScaleY;							// The cosine of the rotation.
	INT32				mSkewX;								// First skew value.
	INT32				mSkewY;								// Second skew value.
};

#endif
