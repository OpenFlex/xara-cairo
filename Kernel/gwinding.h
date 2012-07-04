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

// Gavin's path winding code

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// GWinding.h
//
/////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************

BOOL GWinding(
		PPOINT	pPoints,			Path
		PBYTE	Types,
		UINT32	Length,
		UINT32	pFlatness,			Flatness
		UINT32	&BottomLeftOffset,	Offset to bottom left point.
		POINT	&BottomLeft			Bottom left most point.
	) ;

This call returns information about the winding of a path. The boolean result indicates a
clockwise or anticlockwise winding at the bottom left most point. This point is returned and also
the offset to either this point or the offset to the curve that contains this point.

No errors should occur as the path is expected to be in a legal state.

************************************************************************************************/

BOOL GWinding(
	PPOINT	pPoints,
	PBYTE	Types,
	INT32	Length,
	UINT32	pFlatness,
	UINT32	&BottomLeftOffset,
	POINT	&BottomLeft
) ;

/////////////////////////////////////////////////////////////////////////////////////////////////
