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
#include "swfsprit.h"

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	FlashSprite::FlashSprite ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		-
	Returns:	-
	Purpose:	Default constructor. Ensure that all the variables are set to values
				that won't cause problems.

********************************************************************************************/

FlashSprite::FlashSprite ( void )
{
	// Generate initial settings.
	mpNext = NULL;
	mpPlace = NULL;
	mpPlaceTail = NULL;
	mID = 0;
	mLayer = NO_BUTTON;
	mName.Empty ();
}

/********************************************************************************************

>	FlashSprite::~FlashSprite ()

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		-
	Returns:	-
	Purpose:	Default destructor.

********************************************************************************************/

FlashSprite::~FlashSprite ()
{
	// Delete the list of FlashPlaceObject records.
	while ( mpPlace != NULL )
	{
		FlashPlaceObject *pLast = mpPlace;
		mpPlace = mpPlace->GetNext ();
		delete pLast;
	}

	// Reset the other pointers.
	mpPlaceTail = NULL;
	mpNext = NULL;
}

/********************************************************************************************

>	FlashSprite* FlashSprite::GetNext ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		-
	Returns:	A pointer to the next item in the list.
	Purpose:	Gets a pointer to the next item in the list.

********************************************************************************************/

FlashSprite* FlashSprite::GetNext ( void )
{
	return mpNext;
}

/********************************************************************************************

>	void FlashSprite::SetNext ( FlashSprite *pNext )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		pNext - A pointer to a FlashSprite.
	Returns:	void
	Purpose:	Sets mpNext (the pointer to the next item in the list) to the
				FlashSprite pointed to by pNext.

********************************************************************************************/

void FlashSprite::SetNext ( FlashSprite *pNext )
{
	mpNext = pNext;
}

/********************************************************************************************

>	FlashSprite* FlashSprite::AddNext ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		-
	Returns:	A pointer to the next item in the list.
	Purpose:	Creates a new item, adds it to the list after this node, and returns a
				pointer to this item.

********************************************************************************************/

FlashSprite* FlashSprite::AddNext ( void )
{
	// Do a recursive call: If there is a next object, call the AddNext function within this,
	// and attempt to create the new object there.
	if ( mpNext != NULL )
	{
		return mpNext->AddNext ();
	}
	else
	{
		mpNext = new FlashSprite;
		return mpNext;
	}
}

/********************************************************************************************

>	void FlashSprite::SetID ( WORD ID )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		WORD ID - The ID value shape to be displayed.
	Returns:	-
	Purpose:	Sets mID.

********************************************************************************************/

void FlashSprite::SetID ( WORD ID )
{
	mID = ID;
}

/********************************************************************************************

>	WORD FlashSprite::GetID ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		-
	Returns:	The ID number of the current record.
	Purpose:	Returns the ID of the object to be placed.

********************************************************************************************/

WORD FlashSprite::GetID ( void )
{
	return mID;
}

/********************************************************************************************

>	void FlashSprite::SetName ( const TCHAR* pName )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/1/00
	Inputs:		TCHAR *pName - A pointer to a string containing a button's name.
	Returns:	-
	Purpose:	Sets mName.

********************************************************************************************/

void FlashSprite::SetName ( const TCHAR* pName )
{
	mName = pName;
}

/********************************************************************************************

>	TCHAR* FlashSprite::GetName ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/1/00
	Inputs:		-
	Returns:	A pointer to the contents of the record's name.
	Purpose:	Returns the name of the button.

********************************************************************************************/

TCHAR* FlashSprite::GetName ( void )
{
	return ( TCHAR* ) mName;
}

/********************************************************************************************

>	void FlashSprite::SetLayer ( LayerState Layer )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/1/00
	Inputs:		LayerState Layer - An enumerated type containing the state of the layer.
	Returns:	-
	Purpose:	Sets mLayer.

********************************************************************************************/

void FlashSprite::SetLayer ( LayerState Layer )
{
	mLayer = Layer;
}

/********************************************************************************************

>	LayerState FlashSprite::GetLayer ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/1/00
	Inputs:		-
	Returns:	mLayer - The named layer on which the button is placed.
	Purpose:	Returns the LayerState of the button.

********************************************************************************************/

LayerState FlashSprite::GetLayer ( void )
{
	return mLayer;
}

/********************************************************************************************

>	BOOL FlashSprite::IsAMatch ( const TCHAR *pName,
								 LayerState State )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/1/00
	Inputs:		-
	Returns:	TRUE if a match, FALSE otherwise.
	Purpose:	If the state and name values match, then the object data which these were
				related to forms part of this button record, and thus should be incorporated
				into it.

********************************************************************************************/

BOOL FlashSprite::IsAMatch ( const TCHAR *pName,
							 LayerState State )
{
	if ( mName.IsIdentical ( pName ) && State == mLayer )
		return TRUE;
	else
		return FALSE;
}

/********************************************************************************************

>	FlashPlaceObject* FlashSprite::GetPlace ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		-
	Returns:	mpPlace - A pointer to a FlashPlaceObject.
	Purpose:	Gets a pointer to the head of a FlashPlaceObject list.

********************************************************************************************/

FlashPlaceObject* FlashSprite::GetPlace ( void )
{
	return mpPlace;
}

/********************************************************************************************

>	void FlashSprite::SetPlace ( FlashPlaceObject *pPlace )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/99
	Inputs:		pPlace - A pointer to a FlashPlaceObject.
	Returns:	-
	Purpose:	Sets mpPlace, which is the head of a linked list of FlashPlaceObject
				records.

********************************************************************************************/

void FlashSprite::SetPlace ( FlashPlaceObject *pPlace )
{
	mpPlaceTail = mpPlace = pPlace;
}

/********************************************************************************************

>	void FlashSprite::SetPlaceTail ( FlashPlaceObject *pPlace )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/1/00
	Inputs:		pPlace - A pointer to a FlashPlaceObject.
	Returns:	-
	Purpose:	Sets the value of PlaceTail to be pPlace, so that the list of objects can
				be extended.

********************************************************************************************/

void FlashSprite::SetTail ( FlashPlaceObject *pPlace )
{
	// Check to see whether or not there is a pointer first. If not, create a new record.
	if ( mpPlaceTail != NULL )
	{
		mpPlaceTail->SetNext ( pPlace );
		mpPlaceTail = pPlace;
	}
	else
		SetPlace ( pPlace );
}
