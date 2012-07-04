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


/*
 *  */

/*********************************************************************************************

>	class DocCoord

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/5/1993          
	Base Class: Coord
	Purpose:	Structure holding a 32-bit cartesian coordinate.
				Its main use is to hold the physical coordinates of objects in document space.
	Errors:		None.

*********************************************************************************************/

#ifndef INC_DOCCOORD
#define INC_DOCCOORD

#include "xarlib/coord.h"

#if !defined(EXCLUDE_FROM_XARLIB)
#include "xarlib/wrkcoord.h"
#endif

#include "xarlib/matrix.h"

// Declare various classes to prevent bogus stuff...
class Chapter;
class CCAPI WorkCoord;
class CCAPI OSCoord;
class Matrix;
class XMatrix;
class Spread;
class Document;
class View;
class UserCoord;

class CCAPI DocCoord : public Coord
{
public:

	DocCoord( INT32 x, INT32 y ) : Coord(x,y) {};
	DocCoord() : Coord() {};

#if !defined(EXCLUDE_FROM_XARLIB)
	// Build the matrix which transforms DocCoords into OilCoords...
	friend Matrix ComposeDocToOilMat( const DocCoord& ChapterPos,	// Top left coord of chapter
                          const XLONG& ChapterDepth,			// Accumulated height of previous chaps
                          const FIXED16& ViewScale,			// User viewing scale
                          const WorkCoord& ScrollOffset );	// Scroll offsets

	// Build the matrix which transforms DocCoords into WorkCoords...
	friend XMatrix ComposeDocToWorkXMat( const DocCoord ChapterPos,	// Top left coord of chapter
                          const XLONG ChapterDepth,		// Accumulated height of previous chaps
                          const FIXED16 ViewScale);		// User viewing scale

	// Convert between coords
	WorkCoord ToWork( Document *pDocument, View *pView);
	WorkCoord ToWork( Spread *pSpread, View *pView);
	DocCoord  ToDoc(Spread* pSpread, View* pView);		// ie from SpreadCoords to    DocCoords
	DocCoord  ToSpread(Spread* pSpread, View* pView);	// ie from    DocCoords to SpreadCoords
	UserCoord ToUser(Spread* pSpread);					// ie from SpreadCoords to   UserCoords
	OilCoord  ToOil(Spread* pSpread, View* pView);		// ie from SpreadCoords to   OilCoords

	// Convert a DocCoord into a Logical coord (ie in millipoints, but 64 bits high)
	// The result will be returned in a WorkCoord (normally used for coords measured
	// in pixels)
	WorkCoord ToLogical(Spread* pSpread, View *pView);

	// Given a DocCoords, find the chapter its in and return other details...
	Chapter* FindEnclosingChapter(Document *pDocument, 
								  DocCoord* ChapterPos, 
								  XLONG* ChapterDepth,
								  View *pView);  

	// Functions dealing with pixel size taking scaling into account...
	// (See View class for actual scaled pixel size values/access functions)
	BOOL Pixelise();
	BOOL Pixelise(View* pView);
	BOOL IsPixelised(View* pView);
#endif

	// Some operator functions
	friend DocCoord operator + (const DocCoord& , const DocCoord& );
	friend DocCoord operator - (const DocCoord& , const DocCoord& );

	// Graeme (29-3-00) - Added the += and -= operators.
	const DocCoord& operator += ( const DocCoord &Other );
	const DocCoord& operator -= ( const DocCoord &Other );

	//A scaling function
	void Scale(const DocCoord dcOrigin, const double dDPI=96.0);

	// Karim 13/06/2000
	// Imagining a vector from the origin, return our angle clockwise from the vertical.
	// The angle returned is in radians, for ease-of-use with trig fns,
	// and is zero at the origin.
	// To convert to degrees, use (result * 180.0 / PI) :o)
	double AngleFromVertical() const { return atan2( (double)x, (double)y ); }

	// Jolly useful functions for working out coordinate positions
	static BOOL IsJoinAcute(const DocCoord* pJoin, const DocCoord* pOtherEndOfJoin, const DocCoord* pOtherPoint);
	static DocCoord PositionPointFromRatio(const DocCoord& StartPoint, const DocCoord& EndPoint, const double Ratio);
	static double DistanceFromLine(const DocCoord& Line1, const DocCoord& Line2, const DocCoord& Point);
	static DocCoord OneThird(const DocCoord& Start, const DocCoord& End);
	static DocCoord OneHalf(const DocCoord& Start, const DocCoord& End);
	static DocCoord TwoThirds(const DocCoord& Start, const DocCoord& End);
};

#endif

