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


// StockCol.h - definition of the available stock colours
//
// Created: 21/04/94 by Jason
//

#ifndef INC_STOCKCOL
#define INC_STOCKCOL


/********************************************************************************************

< StockColour

	Comment:	Stock Colours are currently being rebuilt
				See the top of kernel\colour.h for details on the new 
				stock colours.

				Anyway, the old ones are TRANS, BLACK, GREY, etc etc
				and you must not use them any more. In fact, they'll 
				generate ENSURE failures in the near future.

				The new ones are:

					COLOUR_NONE		(100% transparent, i.e. 'no colour')
					COLOUR_TRANS

					COLOUR_BLACK

					COLOUR_DKGREY
					COLOUR_MIDGREY
					COLOUR_LTGREY
					COLOUR_GREY		(Same as LTGREY)

					COLOUR_WHITE

					COLOUR_RED
					COLOUR_GREEN
					COLOUR_BLUE	

					COLOUR_CYAN
					COLOUR_MAGENTA
					COLOUR_YELLOW

				However, you shouldn't need the above ones, as you should
				generally be using one of the following, which will probably
				become user preferences one day.

					COLOUR_UNSELECTEDBLOB 	// Drag blob (handle) things
					COLOUR_SELECTEDBLOB	  	// (when selected & unselected)
	
					COLOUR_BEZIERBLOB		// Bezier control blob
					COLOUR_BEZIERLINE	  	// Bezier tangent line

					COLOUR_XORNEW		  	// XOR outline colours (when...
					COLOUR_XOREDIT		  	// creating new object, editing
					COLOUR_XORDRAG		  	// existing object, moving/rotating,
					COLOUR_XORSELECT	  	// dragging a selection rectangle)

					COLOUR_GRIDMAJOR	  	// Grid crosses & points
					COLOUR_GRIDMINOR  

					COLOUR_TOOLBLOB	  		// Tool blobs (center of rotation etc)

					COLOUR_LINEDEFAULT	  	// Document default line colour
					COLOUR_FILLDEFAULT	  	// Document default fill colour

				If you are the slightest bit unsure which one to use, ask
				Jason immediately. Not that he'll have a clue either, mind...

********************************************************************************************/


enum StockColour
{
	// **** Deprecated colours - DO NOT USE any from this first block
	TRANS,
	BLACK,
	DKGREY,
	MIDGREY,
	LTGREY,
	GREY = LTGREY,
	WHITE,
	RED,
	GREEN,
	BLUE,
	CYAN,
	MAGENTA,
	YELLOW,




	// Predefined SCREEN colours that may one day become user preferences
	COLOUR_UNSELECTEDBLOB,			// Drag blob (handle) things
	COLOUR_SELECTEDBLOB,			// (when selected & unselected)
	
	COLOUR_BEZIERBLOB,				// Bezier control blob
	COLOUR_BEZIERLINE,				// Bezier tangent line

	COLOUR_XORNEW,					// XOR outline colours (when...
	COLOUR_XOREDIT,					// creating new object, editing
	COLOUR_XORDRAG,					// existing object, moving/rotating,
	COLOUR_XORSELECT,				// dragging a selection rectangle)

	COLOUR_GRID,					// Grid crosses & points

	COLOUR_TOOLBLOB,				// Tool blobs (center of rotation etc)

	// Predefined DOCUMENT colours
	COLOUR_LINEDEFAULT,			  	// Document default line colour
	COLOUR_FILLDEFAULT,			  	// Document default fill colour



	// Predefined stock colours
	COLOUR_NONE		= TRANS,					// } No colour (fully transparent)
	COLOUR_TRANS	= TRANS,					// }
	COLOUR_BLACK	= BLACK,
	COLOUR_DKGREY	= DKGREY,
	COLOUR_MIDGREY	= MIDGREY,
	COLOUR_LTGREY	= LTGREY,
	COLOUR_GREY		= LTGREY,
	COLOUR_WHITE	= WHITE,
	COLOUR_RED		= RED,
	COLOUR_GREEN	= GREEN,
	COLOUR_BLUE		= BLUE,
	COLOUR_CYAN		= CYAN,
	COLOUR_MAGENTA	= MAGENTA,
	COLOUR_YELLOW	= YELLOW
};


#endif


