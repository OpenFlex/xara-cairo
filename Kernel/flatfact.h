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

//
// Header for the Path Shape typedef

#ifndef INC_FLATTENINGFACTOR
#define INC_FLATTENINGFACTOR

/**************************************************************************************

>	typedef enum FlatteningFactor

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Purpose:	Use in conjunction with Path::Flatten.

				Instead of passing a double to Path::Flatten, you can pass
				a FlatteningFactor. Passing FF_VERYCLOSELY will flatten the paths
				a lot, passing FF_APPROXIMATELY will flatten them less, etc.

				This is used in Imagemaps, in which it's useful to have
				four discrete levels of flattening.

				Feel free to add intermediate levels of flattening (e.g. add
				"FF_XXXXCLOSELY = 32") but don't change the values
				assigned to FF_VERYCLOSELY, FF_CLOSELY, FF_APPROXIMATELY or
				FF_NOTATALL, or you'll change the way imagemaps save.

**************************************************************************************/

typedef enum
{
	FF_VERYCLOSELY =64,
	FF_CLOSELY =256,
	FF_APPROXIMATELY = 1024,
	FF_NOTATALL=100000,
} FlatteningFactor;

#endif // INC_FLATTENINGFACTOR
