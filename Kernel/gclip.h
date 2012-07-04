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

// Gavin's path clipping code

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// GClip.h
//
/////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************

INT32 ClipPathToPath( 
		PPOINT	SPoints,
		PBYTE	STypes,
		UINT32	SLength,
		UINT32	SFlatness,
		PPOINT	CPoints,
		PBYTE	CTypes,
		UINT32	CLength,
		UINT32	CFlatness,
		UINT32	Flags,
		UINT32	Tolerance,
		PPOINT	OPoints,
		PBYTE	OTypes,
		UINT32	OMaxLength
) ;

SPoints,STypes,SLength	- Source path
SFlatness				- Source path flatness
CPoints,CTypes,CLength	- Clip path
CFlatness				- Clip path flatness
Flags					- Flags
	CLIPPING_STYLE		- Clip style
		001					- 	  Source AND NOT Clip
		010					-     Source AND     Clip (Intersection)
		011					-     Source
		100					- NOT Source AND     Clip
		101					-     Source EOR	 Clip
		110					-	  				 Clip
		111					-     Source OR      Clip (Union)
						- If source stroked then
		000					- Source AND     Clip (Intersection)
		???					- Source AND NOT Clip
	CLIPPING_SOURCE_WINDING - Source path winding.
	CLIPPING_CLIP_WINDING	- Clip path winding.
	CLIPPING_IS_STROKED	- Source is stroked, not filled
	CLIPPING_IS_CLOSED	- Source path is to be closed (only applicable is stroked).
Tolerance				- Tolerance - two points closer than this value are considered to be
									  the same point.
OPoints,OTypes			- Output path
OMaxLength				- Maximum length of output path.

Returns the length of the path, or an error code if an error occurs. Possible error codes are
		-1 - Insufficient memory to create the path. Increase buffer sizes and try again.
		-2 - new failed.

************************************************************************************************/

INT32 ClipPathToPath( 
		PPOINT	SPoints,
		PBYTE	STypes,
		UINT32	SLength,
//		UINT32	SFlatness,
		double	SFlatness,
		PPOINT	CPoints,
		PBYTE	CTypes,
		UINT32	CLength,
//		UINT32	CFlatness,
		double	CFlatness,
		UINT32	Flags,
		UINT32	Tolerance,
		PPOINT	OPoints,
		PBYTE	OTypes,
		UINT32	OMaxLength
	) ;

/////////////////////////////////////////////////////////////////////////////////////////////////
