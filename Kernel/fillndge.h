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

// Definition of the fill nudge classes

#ifndef INC_FILLNDGE
#define INC_FILLNDGE

#include "tranlate.h"

#define OPTOKEN_FILLNUDGE 		_T("FillNudge")

/********************************************************************************************

>	class OpFillNudge : public Operation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/3/95
	Purpose:	The underlying nudge op that does a nudge on the selected points in a path.
	SeeAlso:	class OpNudge

********************************************************************************************/

class OpFillNudge : public Operation	
{
CC_DECLARE_DYNCREATE(OpFillNudge);

public:
	static BOOL    Init();
	static OpState GetState(String_256*, OpDescriptor*);
	//BOOL IsPixelNudgeClass ;							//flag to determnie whether to nudge in MM otr Pixels rabir

	// The actual nudge displacement is the one that takes into account the nudge factor, which
	// provides the magnitude and direction.
	// Use these functions to get the X and Y nudge displacements to apply
	// chnaged from MIILIPOINT to double to get 0.2MM nudging
	static double	GetXNudgeDisplacement()			{ return NudgeStep * X_NudgeFactor; }
	static double	GetYNudgeDisplacement()			{ return NudgeStep * Y_NudgeFactor; }
	double			GetXPixelDisplacement()			{ return PixelNudge * X_NudgeFactor;}
	double			GetYPixelDisplacement()			{ return PixelNudge * Y_NudgeFactor;}

	// Do() will nudge each selected object by GetXNudgeDisplacement() in the x direction
	// and GetYNudgeDisplacement in the y direction
	virtual void Do(OpDescriptor* pOpDesc);

	// Overide GetOpName() so the correct string appears in the undo/redo menu item strings
	void GetOpName(String_256* OpName);

	static void NudgeColours(BOOL);

protected:
	// The X and Y nudge factors are set up by a derived class' Do() function
	// E.g. OpNudgeUp1::Do() would set X_NudgeFactor=0, and Y_NudgeFactor = 1
	// Changed from INT32 to double for 0.2 MM Nudging
	static double			X_NudgeFactor;	// displacement nudged in x dir = NudgeStep * X_NudgeFactor;
	static double			Y_NudgeFactor;	// displacement nudged in y dir = NudgeStep * Y_NudgeFactor;
	
	UINT32	NudgeUndoIDS;

private:
	static	MILLIPOINT	NudgeStep;		// The size of a single nudge (must be a +ve value)
	static	BOOL NudgeCols;				// Shall we nudge colour or transparency fills ?
	BOOL	IsPixelNudgeClass ;			// Flag to test whether to nudge in MM or PIXELS
	double	PixelNudge;					// The size of a single nudge 
};


#define OPTOKEN_FILLNUDGEUP1			_T("FillNudgeUp1")
#define OPTOKEN_FILLNUDGEUP5			_T("FillNudgeUp5")
#define OPTOKEN_FILLNUDGEUP10			_T("FillNudgeUp10")
#define OPTOKEN_FILLNUDGEUPFIFTH		_T("FillNudgeUpFifth")
#define OPTOKEN_FILLNUDGEUPPIXEL1		_T("FillNudgeUpPixel1")
#define OPTOKEN_FILLNUDGEUPPIXEL10		_T("FillNudgeUpPixel10")

#define OPTOKEN_FILLNUDGEDOWN1			_T("FillNudgeDown1")
#define OPTOKEN_FILLNUDGEDOWN5			_T("FillNudgeDown5")
#define OPTOKEN_FILLNUDGEDOWN10			_T("FillNudgeDown10")
#define OPTOKEN_FILLNUDGEDOWNFIFTH		_T("FillNudgeDownFifth")
#define OPTOKEN_FILLNUDGEDOWNPIXEL1		_T("FillNudgeDownPixel1")
#define OPTOKEN_FILLNUDGEDOWNPIXEL10	_T("FillNudgeDownPixel10")

#define OPTOKEN_FILLNUDGELEFT1			_T("FillNudgeLeft1")
#define OPTOKEN_FILLNUDGELEFT5			_T("FillNudgeLeft5")
#define OPTOKEN_FILLNUDGELEFT10			_T("FillNudgeLeft10")
#define OPTOKEN_FILLNUDGELEFTFIFTH		_T("FillNudgeLeftFifth")
#define OPTOKEN_FILLNUDGELEFTPIXEL1		_T("FillNudgeLeftPixel1")
#define OPTOKEN_FILLNUDGELEFTPIXEL10	_T("FillNudgeLeftPixel10")

#define OPTOKEN_FILLNUDGERIGHT1			_T("FillNudgeRight1")
#define OPTOKEN_FILLNUDGERIGHT5			_T("FillNudgeRight5")
#define OPTOKEN_FILLNUDGERIGHT10		_T("FillNudgeRight10")
#define OPTOKEN_FILLNUDGERIGHTFIFTH		_T("FillNudgeRightFifth")
#define OPTOKEN_FILLNUDGERIGHTPIXEL1	_T("FillNudgeRightPixel1")
#define OPTOKEN_FILLNUDGERIGHTPIXEL10	_T("FillNudgeRightPixel10")


#define DECLARE_OPFILLNUDGE_CLASS(DIR1) \
	class OpFillNudge ## DIR1 : public OpFillNudge \
	{ \
	CC_DECLARE_DYNCREATE(OpFillNudge ## DIR1) \
	public: \
		virtual void Do(OpDescriptor* pOpDesc); \
	}; \


DECLARE_OPFILLNUDGE_CLASS	(Up1)
DECLARE_OPFILLNUDGE_CLASS	(Up5)
DECLARE_OPFILLNUDGE_CLASS	(Up10)
DECLARE_OPFILLNUDGE_CLASS	(UpFifth)
DECLARE_OPFILLNUDGE_CLASS	(UpPixel1)
DECLARE_OPFILLNUDGE_CLASS	(UpPixel10)

DECLARE_OPFILLNUDGE_CLASS	(Down1)
DECLARE_OPFILLNUDGE_CLASS	(Down5)
DECLARE_OPFILLNUDGE_CLASS	(Down10)
DECLARE_OPFILLNUDGE_CLASS	(DownFifth)
DECLARE_OPFILLNUDGE_CLASS	(DownPixel1)
DECLARE_OPFILLNUDGE_CLASS	(DownPixel10)


DECLARE_OPFILLNUDGE_CLASS	(Left1)
DECLARE_OPFILLNUDGE_CLASS	(Left5)
DECLARE_OPFILLNUDGE_CLASS	(Left10)
DECLARE_OPFILLNUDGE_CLASS	(LeftFifth)
DECLARE_OPFILLNUDGE_CLASS	(LeftPixel1)
DECLARE_OPFILLNUDGE_CLASS	(LeftPixel10)

DECLARE_OPFILLNUDGE_CLASS	(Right1)
DECLARE_OPFILLNUDGE_CLASS	(Right5)
DECLARE_OPFILLNUDGE_CLASS	(Right10)
DECLARE_OPFILLNUDGE_CLASS	(RightFifth)
DECLARE_OPFILLNUDGE_CLASS	(RightPixel1)
DECLARE_OPFILLNUDGE_CLASS	(RightPixel10)


/***********************************************************************************************

>	class FillGeometryNudger : public AttrValueChange

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/3/94
	Purpose:	Nudges a fill geometry.
				This Attribute never exists in the Tree.
	SeeAlso:	AttrValueChange

***********************************************************************************************/

class FillGeometryNudger : public AttrValueChange
{
	CC_DECLARE_DYNCREATE(FillGeometryNudger)
	
public:
	FillGeometryNudger() : AttrValueChange() {}

	virtual UINT32 GetAttrNameID(void);  
	virtual AttributeValue* GetAttributeValue() { return NULL; }
	virtual AttrFillGeometry* MutateFill(AttrFillGeometry* FillToMutate);

	void SetNudgeDistance(INT32 xOffset, INT32 yOffset);

protected:
	INT32 X_NudgeDistance;
	INT32 Y_NudgeDistance;
};
#endif  
