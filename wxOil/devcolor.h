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

// devcolor.h - Interface between kernel DocColours and ColourContexts and the
// outside world. Currently this is a very thin veneer over functions supplied
// in the RGBT colour context, but this may change in ported versions of Camelot
// and/or as other output devices are supoprted by the rendering subsystem.


#ifndef INC_DEVCOLOR
#define INC_DEVCOLOR


#include "colcontx.h"

/****************************************************************************

>	inline DWORD ConvertColourToScreenWord(ColourContext *cc, DocColour *col)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94

	Inputs:		cc  - An *RGBT* colourContext for screen output
				col - The Colour to be converted
	Outputs:	-
	Returns:	An RGB value suitable for passing to the host OS
				- In this case, an rgb DWORD as used by Windows GDI (0x00BBGGRR)

	Purpose:	Converts the given DocColour into the given screen (RGB) output
				context for whatever host OS we are running under. This function
				does NOT include any transparency information in the result.

	Notes:		Note that to save poking about in the internal DocColour
				representations, a function is supplied by the ColourContextRGBT
				class which just happens (!) to suit our needs. However, I've
				wrapped the call up in this WinOil veneer so that on other OS's
				it will not be necessary to touch that kernel code (just write
				equivalent code to go into here)

****************************************************************************/

inline DWORD ConvertColourToScreenWord(ColourContext *cc, DocColour *col)
{
	return( ((ColourContextRGBT *)cc)->ConvertToScreenWord(col) );
}



/****************************************************************************

>	inline DWORD ConvertColourToTransScreenWord(ColourContext *cc, DocColour *col)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94

	Inputs:		cc  - An *RGBT* colourContext for screen output
				col - The Colour to be converted
	Outputs:	-
	Returns:	An RGB value suitable for passing to the host OS
				- In this case, an rgb DWORD as used by GAVIN (0xTTBBGGRR)
				NOTE that this word must NOT be passed to Windows GDI, as GDI
				uses the MS byte in a different manner to Gavin.

	Purpose:	Converts the given DocColour into the given screen (RGB) output
				context for whatever host OS we are running under, including
				the transparent component as well.

	Notes:		Note that to save poking about in the internal DocColour
				representations, a function is supplied by the ColourContextRGBT
				class which just happens (!) to suit our needs. However, I've
				wrapped the call up in this WinOil veneer so that on other OS's
				it will not be necessary to touch that kernel code (just write
				equivalent code to go into here)

****************************************************************************/

inline DWORD ConvertColourToTransScreenWord(ColourContext *cc, DocColour *col)
{
	return( ((ColourContextRGBT *)cc)->ConvertToTransparentScreenWord(col) );
}

#endif

