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

#ifndef INC_FLASH_PLACE_OBJECT
#define INC_FLASH_PLACE_OBJECT


#define FLASH_FIRST_ID	1						// The ID of the first object to render.

// Enumerated type for the object state.
typedef enum
{
	FLASH_TEXT,
	FLASH_SHAPE,
	FLASH_SPRITE,
	FLASH_BUTTON
} FlashType;

// Enumerated type for the layer state.
typedef enum
{
	NO_BUTTON,
	CLICKED,
	DEFAULT,
	MOUSE,
	SELECTED
} LayerState;

/********************************************************************************************

>	class FlashPlaceObject : public CCObject

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Purpose:	Contains the information necessary to do a PlaceObject tag.

********************************************************************************************/

class FlashPlaceObject : public CCObject
{
public:
	FlashPlaceObject ();
	~FlashPlaceObject ();

	// Access functions.
	FlashPlaceObject* GetNext ( void );			// Get mpNext.
	void SetNext ( FlashPlaceObject *pNext );	// Set mpNext.
	FlashPlaceObject* AddNext ( void );			// Create a new element at mpNext.

	FlashPlaceObject* GetLast ( void );			// Get mpLast.
	void SetLast ( FlashPlaceObject *pLast );	// Set mpLast.

	void SetType ( FlashType Type );			// Sets mToRender.
	FlashType GetType ( void );					// Gets mToRender.

	void SetPosition ( DocCoord Point );		// Position to place the object at.
	DocCoord GetPosition ( void );				// Get the position the object is at.

	void SetID ( WORD ID );						// Set the ID of the shape to be placed.
	WORD GetID ( void );						// Get the ID of the shape.
	WORD GetRawID ( void );						// Get the raw ID (i.e. mID ).

	void SetDoTransform ( BOOL State );			// Sets mDoTransform.
	BOOL GetDoTransform ( void );				// Gets mDoTransform.

	// Static member functions.
	static void ResetStatics ( void );			// Reset all the counter variables.

	static void IncBitmapCount ( void );		// Increase mBitmapCount.
	static void IncFontCount ( void );			// Increase mFontCount.
	static void IncTextCount ( void );			// Increase mTextCount.
	static void IncShapeCount ( void );			// Increase mShapeCount.
	static void IncSpriteCount ( void );		// Increase mSpriteCount.
	static void DecSpriteCount ( void );		// Decrease mSpriteCount.
	static void IncButtonCount ( void );		// Increase mButtonCount.

	static WORD GetBitmapCount ( void );		// Get mBitmapCount.
	static WORD GetFontCount ( void );			// Get mFontCount.
	static WORD GetTextCount ( void );			// Get mTextCount.
	static WORD GetShapeCount ( void );			// Get mShapeCount.
	static WORD GetSpriteCount ( void );		// Get mSpriteCount.
	static WORD	GetButtonCount ( void );		// Get mButtonCount.

private:
	WORD				mID;					// ID number.
	DocCoord			mPosition;				// Translation position.
	FlashPlaceObject	*mpNext;				// Pointer to next item.
	FlashPlaceObject	*mpLast;				// Pointer to previous item.
	FlashType			mToRender;				// The type of record to render.
	BOOL				mDoTransform;			// Are the co-ordinates OK for Flash?

	// Static member variables.
	static WORD			mBitmapCount;			// The number of bitmaps.
	static WORD			mFontCount;				// The number of font definitions.
	static WORD			mTextCount;				// The number of text strings.
	static WORD			mShapeCount;			// The number of shape records.
	static WORD			mSpriteCount;			// The number of sprite records.
	static WORD			mButtonCount;			// The number of button records.
};

#endif
