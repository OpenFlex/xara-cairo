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

#ifndef INC_FLASH_SPRITE
#define INC_FLASH_SPRITE

#include "swfplace.h"

/********************************************************************************************

>	class FlashSprite : public CCObject

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Purpose:	Contains the necessary data to generate a sprite object within a Flash file.

********************************************************************************************/

class FlashSprite : public CCObject
{
public:
	FlashSprite ();
	~FlashSprite ();

	// Access functions.
	FlashSprite* GetNext ( void );				// Get mpNext.
	void SetNext ( FlashSprite *pNext );		// Set mpNext.
	FlashSprite* AddNext ( void );				// Create a new element at mpNext.

	void SetID ( WORD ID );						// Set the ID of the shape to be placed.
	WORD GetID ( void );						// Get the ID of the shape.

	void SetName ( const TCHAR* pName );		// Sets mName.
	TCHAR* GetName ( void );					// Gets a pointer to mName.

	void SetLayer ( LayerState Layer );			// Sets mLayer.
	LayerState GetLayer ( void );				// Gets a pointer to mLayer.

	BOOL IsAMatch ( const TCHAR *pName,			// Do the states match?
					LayerState State );

	void SetPlace ( FlashPlaceObject *pPlace );	// Sets mpPlace.
	void SetTail ( FlashPlaceObject *pPlace );	// Sets mpPlaceTail.
	FlashPlaceObject* GetPlace ( void );		// Gets mpPlace.

private:
	WORD				mID;					// ID number.
	String_256			mName;					// Name of button to be used.
	LayerState			mLayer;					// The button layer this corresponds to.
	FlashSprite			*mpNext;				// Pointer to next item.
	FlashPlaceObject	*mpPlace;				// A pointer to a FlashPlaceObject record.
	FlashPlaceObject	*mpPlaceTail;			// A pointer to a FlashPlaceObject record.
};

#endif
