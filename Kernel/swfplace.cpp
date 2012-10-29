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
#include "swfplace.h"

// Global definitions of the static member variables.
WORD FlashPlaceObject::mBitmapCount	= 0;
WORD FlashPlaceObject::mFontCount	= 0;
WORD FlashPlaceObject::mTextCount	= 0;
WORD FlashPlaceObject::mShapeCount	= 0;
WORD FlashPlaceObject::mSpriteCount	= 0;
WORD FlashPlaceObject::mButtonCount	= 0;

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	FlashPlaceObject::FlashPlaceObject ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Default constructor. Ensure that all the variables are set to values
				that won't cause problems.

********************************************************************************************/

FlashPlaceObject::FlashPlaceObject ( void )
{
	// Generate initial settings.
	DocCoord DefaultPosition ( 0, 0 );

	// And set them.
	mToRender = FLASH_SHAPE;
	mID = 0;
	mPosition = DefaultPosition;
	mpNext = NULL;
	mpLast = NULL;
	mDoTransform = FALSE;
}

/********************************************************************************************

>	FlashPlaceObject::~FlashPlaceObject ()

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Default destructor.

********************************************************************************************/

FlashPlaceObject::~FlashPlaceObject ()
{
	// Nothing needed at the present.
}

/********************************************************************************************

>	FlashPlaceObject* FlashPlaceObject::GetNext ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Inputs:		-
	Returns:	A pointer to the next item in the list.
	Purpose:	Gets a pointer to the next item in the list.

********************************************************************************************/

FlashPlaceObject* FlashPlaceObject::GetNext ( void )
{
	return mpNext;
}

/********************************************************************************************

>	void FlashPlaceObject::SetNext ( FlashPlaceObject *pNext )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Inputs:		pNext - A pointer to a FlashPlaceObject.
	Returns:	void
	Purpose:	Sets mpNext (the pointer to the next item in the list) to the
				FlashPlaceObject pointed to by pNext.

********************************************************************************************/

void FlashPlaceObject::SetNext ( FlashPlaceObject *pNext )
{
	mpNext = pNext;
}

/********************************************************************************************

>	FlashPlaceObject* FlashPlaceObject::AddNext ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Inputs:		-
	Returns:	A pointer to the next item in the list.
	Purpose:	Creates a new item, adds it to the list after this node, and returns a
				pointer to this item.

********************************************************************************************/

FlashPlaceObject* FlashPlaceObject::AddNext ( void )
{
	// Do a recursive call: If there is a next object, call the AddNext function within this,
	// and attempt to create the new object there.
	if ( mpNext != NULL )
	{
		return mpNext->AddNext ();
	}
	else
	{
		mpNext = new FlashPlaceObject;
		ASSERT ( mpNext != NULL );
		mpNext->SetLast ( this );
		return mpNext;
	}
}

/********************************************************************************************

>	FlashPlaceObject* FlashPlaceObject::GetLast ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/1/00
	Inputs:		-
	Returns:	A pointer to the previous item in the list.
	Purpose:	Gets a pointer to the previous item in the list.

********************************************************************************************/

FlashPlaceObject* FlashPlaceObject::GetLast ( void )
{
	return mpLast;
}

/********************************************************************************************

>	void FlashPlaceObject::SetLast ( FlashPlaceObject *pLast )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/1/00
	Inputs:		pLast - A pointer to a FlashPlaceObject.
	Returns:	void
	Purpose:	Sets mpLast (the pointer to the previous item in the list) to the
				FlashPlaceObject pointed to by pLast.

********************************************************************************************/

void FlashPlaceObject::SetLast ( FlashPlaceObject *pLast )
{
	mpLast = pLast;
}

/********************************************************************************************

>	void FlashPlaceObject::SetType ( FlashType Type )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/99
	Inputs:		Type - The kind of Flash record to be rendered.
	Returns:	-
	Purpose:	Sets mToRender, a record of what kind of Flash record to write to the file.

********************************************************************************************/

void FlashPlaceObject::SetType ( FlashType Type )
{
	mToRender = Type;
}

/********************************************************************************************

>	FlashType FlashPlaceObject::GetType ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/99
	Inputs:		-
	Returns:	The type of shape to be rendered.
	Purpose:	Reveals whether this place object is being used to display a particular
				kind of Flash file record.

********************************************************************************************/

FlashType FlashPlaceObject::GetType ( void )
{
	return mToRender;
}

/********************************************************************************************

>	void FlashPlaceObject::SetPosition ( DocCoord Point )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Inputs:		Point - The position to place the object on screen. (Typically lox, loy.)
	Returns:	-
	Purpose:	Sets the position at which the image should be rendered.

********************************************************************************************/

void FlashPlaceObject::SetPosition ( DocCoord Point )
{
	mPosition = Point;
}

/********************************************************************************************

>	DocCoord FlashPlaceObject::GetPosition ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Inputs:		-
	Returns:	DocCoord - The position of the object.
	Purpose:	Sets the initial position to render the object at.

********************************************************************************************/

DocCoord FlashPlaceObject::GetPosition ( void )
{
	return mPosition;
}

/********************************************************************************************

>	void FlashPlaceObject::SetID ( WORD ID )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/99
	Inputs:		WORD ID - The ID value shape to be displayed.
	Returns:	-
	Purpose:	Sets mID.

********************************************************************************************/

void FlashPlaceObject::SetID ( WORD ID )
{
	mID = ID;
}

/********************************************************************************************

>	WORD FlashPlaceObject::GetID ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/99
	Inputs:		-
	Returns:	The ID number of the current record.
	Purpose:	Returns the ID of the object to be placed.

********************************************************************************************/

WORD FlashPlaceObject::GetID ( void )
{
	WORD ID = mID;

	// Use a switch to determine what the ID value should be.
	if ( mToRender == FLASH_TEXT )
	{
		ID += FLASH_FIRST_ID + mBitmapCount + mFontCount;
	}
	else if ( mToRender == FLASH_SHAPE )
	{
		ID += FLASH_FIRST_ID + mBitmapCount + mFontCount + mTextCount;
	}
	else if ( mToRender == FLASH_SPRITE )
	{
		ID += FLASH_FIRST_ID + mBitmapCount + mFontCount + mTextCount + mShapeCount;
	}
	else if ( mToRender == FLASH_BUTTON )
	{
		ID += FLASH_FIRST_ID + mBitmapCount + mFontCount + mTextCount + mShapeCount
			  + mSpriteCount;
	}

	return ID;
}

/********************************************************************************************

>	WORD FlashPlaceObject::GetRawID ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/1/00
	Inputs:		-
	Returns:	The ID number of the current record.
	Purpose:	Returns the raw ID of the object to be placed. (i.e. the value contained in
				mID.)

********************************************************************************************/

WORD FlashPlaceObject::GetRawID ( void )
{
	return mID;
}

/********************************************************************************************

>	void FlashPlaceObject::SetDoTransform ( BOOL State )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/1/00
	Inputs:		State - Should a transform be applied to the place object co-ordinates?
	Returns:	-
	Purpose:	The way the Flash render region code for buttons has been set up mean that
				buttons with roll-over states must be placed at (0,0). Unfortunately, if I
				set the co-ordinates to this value, they are transformed when this class is
				processed, so I'm putting this value in to alert the filter that I want to
				use THIS value in the final image.

********************************************************************************************/

void FlashPlaceObject::SetDoTransform ( BOOL State )
{
	mDoTransform = State;
}

/********************************************************************************************

>	BOOL FlashPlaceObject::GetDoTransform ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/1/00
	Inputs:		-
	Returns:	TRUE if the transform should be done, otherwise FALSE.
	Purpose:	Allows the filter to determine whether or not a transform should be applied
				to the position co-ordinates for this PlaceObject tag.

********************************************************************************************/

BOOL FlashPlaceObject::GetDoTransform ( void )
{
	return mDoTransform;
}

/********************************************************************************************

>	static void FlashPlaceObject::ResetStatics ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Sets all the static member variables to zero.

********************************************************************************************/

void FlashPlaceObject::ResetStatics ( void )
{
	// Reset the counter variables.
	mBitmapCount	= 0;
	mFontCount		= 0;
	mTextCount		= 0;
	mShapeCount		= 0;
	mSpriteCount	= 0;
	mButtonCount	= 0;
}

/********************************************************************************************

>	static void FlashPlaceObject::IncBitmapCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Increases mBitmapCount.

********************************************************************************************/

void FlashPlaceObject::IncBitmapCount ( void )
{
	mBitmapCount ++;
}

/********************************************************************************************

>	static void FlashPlaceObject::IncFontCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Increases mFontCount.

********************************************************************************************/

void FlashPlaceObject::IncFontCount ( void )
{
	mFontCount ++;
}

/********************************************************************************************

>	static void FlashPlaceObject::IncTextCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Increases mTextCount.

********************************************************************************************/

void FlashPlaceObject::IncTextCount ( void )
{
	mTextCount ++;
}

/********************************************************************************************

>	static void FlashPlaceObject::IncShapeCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Increases mShapeCount.

********************************************************************************************/

void FlashPlaceObject::IncShapeCount ( void )
{
	mShapeCount ++;
}

/********************************************************************************************

>	static void FlashPlaceObject::IncSpriteCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		-
	Returns:	-
	Purpose:	Increases mSpriteCount.

********************************************************************************************/

void FlashPlaceObject::IncSpriteCount ( void )
{
	mSpriteCount ++;
}

/********************************************************************************************

>	static void FlashPlaceObject::DecSpriteCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/00
	Inputs:		-
	Returns:	-
	Purpose:	Decreases mSpriteCount.

********************************************************************************************/

void FlashPlaceObject::DecSpriteCount ( void )
{
	// Only decrease the sprite count if it is greated than zero, since it is an unsigned
	// value.
	if ( mSpriteCount > 0 )
		mSpriteCount --;
}

/********************************************************************************************

>	static void FlashPlaceObject::IncButtonCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/12/99
	Inputs:		-
	Returns:	-
	Purpose:	Increases mButtonCount.

********************************************************************************************/

void FlashPlaceObject::IncButtonCount ( void )
{
	mButtonCount ++;
}

/********************************************************************************************

>	static WORD FlashPlaceObject::GetBitmapCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	The current value of mBitmapCount.
	Purpose:	Access function to the static member variable mBitmapCount.

********************************************************************************************/

WORD FlashPlaceObject::GetBitmapCount ( void )
{
	return mBitmapCount;
}

/********************************************************************************************

>	static WORD FlashPlaceObject::GetFontCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	The current value of mFontCount.
	Purpose:	Access function to the static member variable mFontCount.

********************************************************************************************/

WORD FlashPlaceObject::GetFontCount ( void )
{
	return mFontCount;
}

/********************************************************************************************

>	static WORD FlashPlaceObject::GetTextCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	The current value of mTextCount.
	Purpose:	Access function to the static member variable mTextCount.

********************************************************************************************/

WORD FlashPlaceObject::GetTextCount ( void )
{
	return mTextCount;
}

/********************************************************************************************

>	static WORD FlashPlaceObject::GetShapeCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	The current value of mShapeCount.
	Purpose:	Access function to the static member variable mShapeCount.

********************************************************************************************/

WORD FlashPlaceObject::GetShapeCount ( void )
{
	return mShapeCount;
}

/********************************************************************************************

>	static WORD FlashPlaceObject::GetSpriteCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	The current value of mSpriteCount.
	Purpose:	Access function to the static member variable mSpriteCount.

********************************************************************************************/

WORD FlashPlaceObject::GetSpriteCount ( void )
{
	return mSpriteCount;
}

/********************************************************************************************

>	static WORD FlashPlaceObject::GetButtonCount ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/10/99
	Inputs:		-
	Returns:	The current value of mButtonCount.
	Purpose:	Access function to the static member variable mButtonCount.

********************************************************************************************/

WORD FlashPlaceObject::GetButtonCount ( void )
{
	return mButtonCount;
}
