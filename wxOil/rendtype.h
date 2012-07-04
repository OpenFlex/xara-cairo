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


// file containing the definition of an enum called RenderType. This is not in ccdc.h
// to avoid serious dependency problems

#ifndef INC_RENDTYPE
#define	INC_RENDTYPE

/********************************************************************************************

>	Comment:	RenderType

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/11/93
	Purpose:	A enumerated type to help in rendering to different devices. Some types
				are Kernel-safe (i.e. will exist on all platforms), others are specific
				to a particular OIL implementation. Examples are RENDERTYPE_SCREEN, _PRINTER,
				_METAFILE etc.
			
********************************************************************************************/

enum RenderType
{
	RENDERTYPE_NONE,							// these are Kernel-types
	RENDERTYPE_SCREEN,
	RENDERTYPE_PRINTER,
	RENDERTYPE_PRINTER_PS,
	RENDERTYPE_MONOBITMAP,						// Deprecated - HITDETECT used instead now
	RENDERTYPE_COLOURBITMAP,
	RENDERTYPE_SCREENXOR,						// used to XOR to the screen
	RENDERTYPE_SCREENPAPER,						// (not currently used)
	RENDERTYPE_FILE,
	RENDERTYPE_HITDETECT,						// 32BPP hit detection based on transparency

	RENDERTYPE_METAFILE16 = 0x80,				// these are OIL-specific types
	RENDERTYPE_METAFILE32

};

#endif
