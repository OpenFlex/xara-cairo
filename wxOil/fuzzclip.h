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

// This is a Gavin File that contains the code to clip paths before rendering them to allow
// much higher levels of zoom.


/************************************************************************************************

>	INT32 FuzzyClip(	PPOINT IPoints, PBYTE ITypes, UINT32 ILength, BOOL IsClosed,
					RECT *InnerRect, RECT *OuterRect, PPOINT pOPoints,
					PBYTE pOTypes, UINT32 pOMaxLength);

	Inputs:		IPoints,ITypes,ILength	- Source path
				IsClosed				- Source path and output path should be closed.
				InnerRect				- Inner rectangle to which to clip.
				OuterRect				- Outer rectangle to which to clip.
	Outputs:	pOPoints,pOTypes		- Outut path.
				pOMaxLength				- Maximum length of output path.
	Returns:	Returns the length of the path, or -1 if an error occurs.
				(ie output path not large enough).
	Purpose:	Note that InnerRect should be slightly larger than the window for which the
				clipping is being performed. This ensures that any slight errors won't be
				visible at the window edges.
				Note also that OuterRect must be over 3 times the width of InnerRect,
				with InnerRect centred within it.
				No errors should occur as the path is expected to be in a legal state.

************************************************************************************************/

size_t FuzzyClip(
		PPOINT	IPoints,
		PBYTE	ITypes,
		size_t	ILength,
		BOOL	IsClosed,
		RECT	*InnerRect,
		RECT	*OuterRect,
		PPOINT	pOPoints,
		PBYTE	pOTypes,
		size_t	pOMaxLength
	) ;

/////////////////////////////////////////////////////////////////////////////////////////////////
