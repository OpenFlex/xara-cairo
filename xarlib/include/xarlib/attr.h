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


// Attribute type definitions

#ifndef INC_ATTR
#define INC_ATTR

#include "xarlib/doccoord.h"

class Path;

/********************************************************************************************
	These are the Attribute type definitions
********************************************************************************************/

/********************************************************************************************

< LineCapType

Comment:
	enum LineCapType
	{
		LineCapButt,
		LineCapRound,
		LineCapSquare
	};
	
********************************************************************************************/

enum LineCapType
{
	LineCapButt,
	LineCapRound,
	LineCapSquare
};

/********************************************************************************************

< JointType

Comment:
	enum JointType
	{
		MitreJoin,
		RoundJoin,
		BevelledJoin	
	};
	
********************************************************************************************/

enum JointType
{
	MitreJoin,
	RoundJoin,
	BevelledJoin	
};

/********************************************************************************************

< WindingType

Comment:
	enum WindingType
	{
		NonZeroWinding,
		NegativeWinding,
		EvenOddWinding,
		PositiveWinding
	};
	
********************************************************************************************/

enum WindingType
{
	NonZeroWinding,
	NegativeWinding,
	EvenOddWinding,
	PositiveWinding
};
   
/********************************************************************************************

< DrawModeType

Comment:
	enum DrawModeType
	{
		DM_COPYPEN = 13,	// These are set to the same numbers as Windows uses, so they can
		DM_EORPEN = 7       // be passed straight to the CDC::SetROP2 function.
	};
	
********************************************************************************************/

enum DrawModeType
{
	DM_COPYPEN = 13,	// These are set to the same numbers as Windows uses, so they can
	DM_EORPEN = 7,      // be passed straight to the CDC::SetROP2 function.

	DM_EORDITHER = 1	// Used for drawing grad fills with EOR - we just want the brush
						// to be set as if we were using DM_COPYPEN, i.e. dithered and
						// not messed about with like it is when we do DM_EORPEN.
};

/********************************************************************************************

< BlobType

Comment:
	MonoOn
	enum BlobType
	{
		BT_UNSELECTED,
		BT_SELECTED,
		BT_SELECTEDLARGEST,							the larger of the two above
		BT_CLICKME,									invisible blob used for click detection
		BT_MSTAGEFILLUNSELECTED,
		BT_MSTAGEFILLSELECTED,
		BT_MSTAGESELECTEDLARGEST,
		BT_CLIPVIEW									refers to ClipView's ToolObject blobs
	};
	MonoOff
	
********************************************************************************************/

enum BlobType
{
	BT_UNSELECTED,
	BT_SELECTED,
	BT_SELECTEDLARGEST,
	BT_CLICKME,
	BT_MSTAGEFILLUNSELECTED,
	BT_MSTAGEFILLSELECTED,
	BT_MSTAGESELECTEDLARGEST,
	BT_CLIPVIEW
};

/********************************************************************************************
	Dash Records.  These define Dash patterns for dotted lines.
********************************************************************************************/

/********************************************************************************************

>	class DashRec : public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/10/94
	Purpose:	A class defining a Dash pattern.
	SeeAlso:	-

********************************************************************************************/

enum StockDash
{
// These are old dashes,
// don't use these any more
	SD_DASH = 1,
	SD_DOT,
	SD_DASHDOT,
	SD_DASHDOTDOT,
	SD_FILLMESH,

// New Dashes
	SD_SOLID = 0,
	SD_DASH1,
	SD_DASH2,
	SD_DASH3,
	SD_DASH4,
	SD_DASH5,
	SD_DASH6,
	SD_DASH7,
	SD_DASH8,
	SD_DASH9,
	SD_DASH10,
	SD_DASH11,
	SD_DASH12,
	SD_DASH13,
	SD_DASH14,
	SD_DASH15,
	SD_DASH16,
	SD_DASH17,
	SD_DASH18,
	SD_DASH19,
	SD_DASH20,
	SD_DASH_GUIDELAYER,

	NUM_STOCK_DASHES
};

typedef INT32 DashElement;

class DashRec : public CCObject
{
	CC_DECLARE_DYNCREATE(DashRec)
public:
	DashRec();
	
	INT32 operator==(DashRec&);
	INT32 operator==(StockDash);
	DashRec& operator=(DashRec&);
	DashRec& operator=(StockDash);

// Number of Stock Dashes available
	static INT32 GetNumStockDashes() { return NUM_STOCK_DASHES; }
	static String_256 GetStockDashName(StockDash);

	INT32 GetDashID() { return DashID; }
	BOOL ShouldScaleWithLineWidth() { return ScaleWithLineWidth; }

	void CheckAndFix();
	void CheckIfDefaultPattern();

public:
	INT32 Elements;
	INT32 DashStart;
	DashElement* ElementData;

	INT32 LineWidth;
	BOOL ScaleWithLineWidth;
	INT32 DashID;
};

#endif // INC_ATTR
