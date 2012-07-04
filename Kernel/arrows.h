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

// Defines ArrowRec class (a Line ArrowHead Record)

#ifndef INC_ARROW
#define INC_ARROW

#include "fixed16.h"
#include "doccoord.h"
#include "paths.h"

class Trans2DMatrix;

const INT32 DEFAULT_ARROW_LINEWIDTH = (72000/2);
const INT32 DEFAULT_ARROW_SIZE = 3;

/********************************************************************************************

< StockArrow

Comment:
	MonoOn
	enum StockArrow
	{
		SA_NULLARROW,
		SA_STRAIGHTARROW,
		SA_ANGLEDARROW,
		SA_ROUNDEDARROW,
		SA_SPOT,
		SA_DIAMOND,
		SA_ARROWFEATHER
		SA_ARROWFEATHER2,
		SA_HOLLOWDIAMOND
	};
	MonoOff
	
********************************************************************************************/

enum StockArrow
{
	SA_NULLARROW,
	SA_STRAIGHTARROW,
	SA_ANGLEDARROW,
	SA_ROUNDEDARROW,
	SA_SPOT,
	SA_DIAMOND,
	SA_ARROWFEATHER,
	SA_ARROWFEATHER2,
	SA_HOLLOWDIAMOND,

	NUM_STOCK_ARROWS
};

/********************************************************************************************

>	class ArrowRec : public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/4/95
	Purpose:	A class defining a Line ArrowHead Record.

********************************************************************************************/

class ArrowRec : public CCObject
{
	CC_DECLARE_DYNCREATE(ArrowRec);

public:

// Construction
	ArrowRec();
	ArrowRec(Path* pArrowPath, const DocCoord& Centre, 
			 INT32 LineWidth = DEFAULT_ARROW_LINEWIDTH, 
			 FIXED16 WidthScale  = DEFAULT_ARROW_SIZE, 
			 FIXED16 HeightScale = DEFAULT_ARROW_SIZE,
			 BOOL Start = FALSE);

// Copy constructor
	ArrowRec(const ArrowRec&);

// Destruction
	~ArrowRec();

//Initialisation
	BOOL CreateStockArrow(StockArrow);

	void SetArrowSize(FIXED16 Width, FIXED16 Height = 0);

// Copying and equality
	INT32 operator==(const ArrowRec&);
	ArrowRec& operator=(const ArrowRec&);

	INT32 operator==(StockArrow);
	ArrowRec& operator=(StockArrow);

// Arrow Data access
	Path*	 	GetArrowPath();
	DocCoord 	GetArrowCentre();
	INT32	 	GetArrowLineWidth();
	FIXED16 	GetArrowWidth();
	FIXED16 	GetArrowHeight();

	BOOL 		IsStartArrow();
	BOOL 		ShouldScaleWithLineWidth();

	INT32 		GetArrowID();

// Position and bounds calculations
	DocRect GetArrowBoundingRect(Path* pParent, INT32 LineWidth, BOOL StartArrow);

	BOOL GetArrowMatrix(const DocCoord& Centre, const DocCoord& Direction, 
		 				INT32 LineWidth, Trans2DMatrix* pMatrix);

// Statics for getting arrow positions within paths
	static BOOL DoesPathNeedArrowHeads(DocCoord* Coords, PathVerb* Verbs, INT32 NumCoords);

	static BOOL GetFirstArrowPos(BOOL StartArrow,
								 DocCoord* Coords, PathVerb* Verbs, INT32 NumCoords, 
								 INT32* Index, DocCoord* Centre, DocCoord* Direction);

	static BOOL GetNextArrowPos(BOOL StartArrow,
							 	DocCoord* Coords, PathVerb* Verbs, INT32 NumCoords, 
								INT32* Index, DocCoord* Centre, DocCoord* Direction);

// Check for a dummy ArrowHead
	inline BOOL IsNullArrow() { return (ArrowShape == NULL || IsNull); }

// Number of Stock Arrows available
	static INT32 GetNumStockArrows() { return NUM_STOCK_ARROWS; }
	static String_256 GetStockArrowName(StockArrow);

// Angle calculation
	static ANGLE CalcAngle(const DocCoord& Centre, const DocCoord& Direction);

private:
	DocRect FindBoundsAt(const DocCoord& Centre, const DocCoord& Direction, INT32 LineWidth);

public:
	Path* ArrowShape;
	DocCoord Centre;
	INT32 LineWidth;
	FIXED16 ArrowWidth;
	FIXED16 ArrowHeight;

	BOOL StartArrow;
	BOOL ScaleWithLineWidth;
	INT32 ArrowID;

	// For backwards compatability
	BOOL IsNull;

	// gets the base of the arrow (in arrow coordinates i.e. before it's been transformed
	// by the matrix delivered in GetArrowMatrix)
	void GetArrowBase(DocCoord * pPoint);

	// flag to indicate that the arrow is outside of the path
	BOOL m_bExtendPath;
};

#endif  // INC_ARROW
