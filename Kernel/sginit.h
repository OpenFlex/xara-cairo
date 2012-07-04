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

// sginit.h - Centralised initialisation for galleries

#ifndef INC_SGINIT
#define INC_SGINIT


/***********************************************************************************************

>	class SGInit : public CC_CLASS_MEMDUMP

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/2/95

	Purpose:	Provides static functions for initialisation/deinitialisation of the 
				SuperGallery system, plus useful internal SuperGallery work functions.

				Note: SGInit::Init() is called from main.cpp. It initialises ALL Ops
				relating to galleries, to remove the dependency between main.cpp and
				the supergallery subsystem. This also helps to keep all sgallery related
				stuff in the same group of files.

	SeeAlso:	SuperGallery; SGInit::Init

***********************************************************************************************/

class SGInit : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(SGInit)

public:
	static BOOL Init(void);
	static void DeInit(void);

	static void UpdateGalleryButton(ResourceID OpToken, BOOL IsVisible);
};

#endif

