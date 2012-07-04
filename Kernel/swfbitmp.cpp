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
#include "swfbitmp.h"

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	FlashBitmapRecord::FlashBitmapRecord ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	-
	Purpose:	Creates a FlashBitmapRecord list node, and initialises all member variables.

********************************************************************************************/

FlashBitmapRecord::FlashBitmapRecord ( void )
{
	// Pointers should always be initialised to NULL when created.
	mpNext			= NULL;		// No subsequent nodes.
	mpLast			= NULL;		// No previous nodes.
	mpBitmap		= NULL;		// No bitmap attached.

	mIsContone		= FALSE;
	mBitmapID		= 0;

	mTransparency	= 255;		// The bitmap is (initially) transparent.
}

/********************************************************************************************

>	FlashBitmapRecord::~FlashBitmapRecord ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	-
	Purpose:	Destroys this instance of FlashBitmapRecord.

********************************************************************************************/

FlashBitmapRecord::~FlashBitmapRecord ( void )
{
	// Clean up any stray values.
	mpNext		= NULL;
	mpLast		= NULL;
	mpBitmap	= NULL;
}

/********************************************************************************************

>	FlashBitmapRecord* FlashBitmapRecord::AddElement ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	pTail - The pointer to the new node.
	Purpose:	Adds an element to the tail of the list.

********************************************************************************************/

FlashBitmapRecord* FlashBitmapRecord::AddElement ( void )
{
	FlashBitmapRecord *pTail = new FlashBitmapRecord;
	
	// Set the appropriate pointers.
	pTail->SetLast ( this );		// Ensure that a reference exists to this object...
	pTail->SetNext ( mpNext );		// Avoids any problems if mpLast isn't NULL.
	mpNext = pTail;					// ... and a reference exists to the new one.

	return pTail;
}

/********************************************************************************************

>	void FlashBitmapRecord::DeleteLastElement ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	-
	Purpose:	Deletes the previous item in the list.

********************************************************************************************/

void FlashBitmapRecord::DeleteLastElement ( void )
{
	FlashBitmapRecord *pToDelete = mpLast;
	
	// Reset mpLast to be mpLast->GetLast (), so that the list isn't broken.
	if ( mpLast != NULL )
		mpLast = mpLast->GetLast ();

	delete pToDelete;
}

/********************************************************************************************

>	void FlashBitmapRecord::DeleteNextElement ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	-
	Purpose:	Deletes the next item in the list.

********************************************************************************************/

void FlashBitmapRecord::DeleteNextElement ( void )
{
	FlashBitmapRecord *pToDelete = mpNext;
	
	// Reset mpNext to be mpNext->GetNext (), so that the list isn't broken.
	if ( mpNext != NULL )
		mpNext = mpNext->GetNext ();

	delete pToDelete;
}

/********************************************************************************************

>	OILBitmap* FlashBitmapRecord::GetBitmap ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	mpBitmap - A pointer to a kernel bitmap.
	Purpose:	Gets the value of mpBitmap.

********************************************************************************************/

OILBitmap* FlashBitmapRecord::GetBitmap ( void )
{
	return mpBitmap;
}

/********************************************************************************************

>	WORD FlashBitmapRecord::GetBitmapID ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	mBitmapID - The internal ID number used by the Flash file.
	Purpose:	Gets the value of mBitmapID.

********************************************************************************************/

WORD FlashBitmapRecord::GetBitmapID ( void )
{
	return mBitmapID;
}

/********************************************************************************************

>	DocColour FlashBitmapRecord::GetContoneStart ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/12/99
	Inputs:		-
	Returns:	mStartColour - The start colour for a contone operation.
	Purpose:	Gets the value of mStartColour.

********************************************************************************************/

DocColour FlashBitmapRecord::GetContoneStart ( void )
{
	return mStartColour;
}

/********************************************************************************************

>	DocColour FlashBitmapRecord::GetContoneEnd ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/12/99
	Inputs:		-
	Returns:	mEndColour - The end colour for a contone operation.
	Purpose:	Gets the value of mEndColour.

********************************************************************************************/

DocColour FlashBitmapRecord::GetContoneEnd ( void )
{
	return mEndColour;
}

/********************************************************************************************

>	BOOL FlashBitmapRecord::GetIsContone ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/12/99
	Inputs:		-
	Returns:	mIsContone - Is the bitmap contoned.
	Purpose:	Gets the value of mIsContone.

********************************************************************************************/

BOOL FlashBitmapRecord::GetIsContone ( void )
{
	return mIsContone;
}

/********************************************************************************************

>	UINT32 FlashBitmapRecord::GetTransparency ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/11/00
	Inputs:		-
	Returns:	mTransparency - The transparency channel of the bitmap.
	Purpose:	Gets the value of mTransparency.

********************************************************************************************/

UINT32 FlashBitmapRecord::GetTransparency ( void )
{
	return mTransparency;
}

/********************************************************************************************

>	FlashBitmapRecord* FlashBitmapRecord::GetLast ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	*mpLast - A pointer to the previous node in the linked list.
	Purpose:	Gets mpLast.

********************************************************************************************/

FlashBitmapRecord* FlashBitmapRecord::GetLast ( void )
{
	return mpLast;
}

/********************************************************************************************

>	FlashBitmapRecord* FlashBitmapRecord::GetNext ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		-
	Returns:	*mpNext - A pointer to the next node in the linked list.
	Purpose:	Gets mpNext.

********************************************************************************************/

FlashBitmapRecord* FlashBitmapRecord::GetNext ( void )
{
	return mpNext;
}

/********************************************************************************************

>	void FlashBitmapRecord::SetBitmap ( OILBitmap *pBitmap )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		pBitmap - A pointer to a kernel bitmap.
	Returns:	-
	Purpose:	Sets the value of mpBitmap.

********************************************************************************************/

void FlashBitmapRecord::SetBitmap ( OILBitmap *pBitmap )
{
	mpBitmap = pBitmap;
}

/********************************************************************************************

>	void FlashBitmapRecord::SetContoneColours ( const DocColour &Start,
												const DocColour &End )
	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/12/99
	Inputs:		Start	- The start colour for a contone fill.
				End		- The end colour for a contone fill.
	Returns:	-
	Purpose:	Sets the values of mStartColour and mEndColour.

********************************************************************************************/

void FlashBitmapRecord::SetContoneColours ( const DocColour &Start,
											const DocColour &End )
{
	// Set the values for the start and end colours.
	mStartColour	= Start;
	mEndColour		= End;
}

/********************************************************************************************

>	void FlashBitmapRecord::SetIsContone ( BOOL IsContone )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/12/99
	Inputs:		IsContone - Is the bitmap to be rendered as a contone bitmap.
	Returns:	-
	Purpose:	Sets the value of mIsContone.

********************************************************************************************/

void FlashBitmapRecord::SetIsContone ( BOOL IsContone )
{
	mIsContone = IsContone;
}

/********************************************************************************************

>	void FlashBitmapRecord::SetTransparency ( UINT32 Transparency )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/11/00
	Inputs:		Transparency - The transparency of the bitmap.
	Returns:	-
	Purpose:	Sets the value of mTransparency.

********************************************************************************************/

void FlashBitmapRecord::SetTransparency ( UINT32 Transparency )
{
	mTransparency = Transparency;
}

/********************************************************************************************

>	void FlashBitmapRecord::SetBitmapID ( WORD BitmapID )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		BitmapID - The ID value for this bitmap.
	Returns:	-
	Purpose:	Sets the value of mBitmapID.

********************************************************************************************/

void FlashBitmapRecord::SetBitmapID ( WORD BitmapID )
{
	mBitmapID = BitmapID;
}

/********************************************************************************************

>	void FlashBitmapRecord::SetLast ( FlashBitmapRecord *pLast )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		pLast - A pointer to the previous FlashBitmapRecord in the linked list.
	Returns:	-
	Purpose:	Sets the value of mpLast.

********************************************************************************************/

void FlashBitmapRecord::SetLast ( FlashBitmapRecord *pLast )
{
	mpLast = pLast;
}

/********************************************************************************************

>	void FlashBitmapRecord::SetNext ( FlashBitmapRecord *pNext )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/99
	Inputs:		pNext - A pointer to the next FlashBitmapRecord in the linked list.
	Returns:	-
	Purpose:	Sets the value of mpNext.

********************************************************************************************/

void FlashBitmapRecord::SetNext ( FlashBitmapRecord *pNext )
{
	mpNext = pNext;
}
