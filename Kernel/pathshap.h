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

#ifndef INC_PATHSHAPE
#define INC_PATHSHAPE


/********************************************************************************************

>	typedef enum PathShape

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	This is a value which describes what shape a path is:
				a circle, a rectangle, and so on.

				Feel free to add to it.

********************************************************************************************/

typedef enum {
	PATHSHAPE_PATH=0,		//The path has no particular shape

	PATHSHAPE_CIRCLE,		//The path is a regular circle
	PATHSHAPE_ELLIPSE,		//The path is an (non-rotated) ellipse

	PATHSHAPE_SQUARE,		//The path is a (non-rotated) square
	PATHSHAPE_RECTANGLE,	//The path is a (non-rotated) rectangle

	PATHSHAPE_ELLIPSE_ROTATED,		//The path is a rotated ellipse

	PATHSHAPE_SQUARE_ROTATED,			//The path is a rotated square
	PATHSHAPE_RECTANGLE_ROTATED,		//The path is a rotated rectangle


} PathShape;

#endif // INC_PATHSHAPE
