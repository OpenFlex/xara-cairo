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

// Definition of the path nudge classes

#ifndef INC_PATHNDGE
#define INC_PATHNDGE

#include "tranlate.h"

#define OPTOKEN_PATHNUDGE 		_T("PathNudge")

/********************************************************************************************

>	class OpPathNudge : public TransOperation

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/10/94
	Purpose:	The underlying nudge op that does a nudge on the selected points in a path.
	SeeAlso:	class OpNudge

********************************************************************************************/

class OpPathNudge : public TransOperation
{
CC_DECLARE_DYNCREATE(OpPathNudge);

public:
	static BOOL    Init();
	static OpState GetState(String_256*, OpDescriptor*);

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

	virtual void PerformMergeProcessing();

protected:
	// The X and Y nudge factors are set up by a derived class' Do() function
	// E.g. OpNudgeUp1::Do() would set X_NudgeFactor=0, and Y_NudgeFactor = 1
	static double			X_NudgeFactor;	// displacement nudged in x dir = NudgeStep * X_NudgeFactor;
	static double			Y_NudgeFactor;	// displacement nudged in y dir = NudgeStep * Y_NudgeFactor;

	UINT32 NudgeUndoIDS;

private:
	static	MILLIPOINT 	NudgeStep;		// The size of a single nudge (must be a +ve value)
	BOOL	PixelNudgeClass ;			// Flag to test whether to nudge in MM or PIXELS
	double	PixelNudge;					// The size of a single nudge 

};

#define OPTOKEN_PATHNUDGEUP1		_T("PathNudgeUp1")
#define OPTOKEN_PATHNUDGEUP5		_T("PathNudgeUp5")
#define OPTOKEN_PATHNUDGEUP10		_T("PathNudgeUp10")
#define OPTOKEN_PATHNUDGEUPFIFTH	_T("PathNudgeUpFifth")
#define OPTOKEN_PATHNUDGEUPPIXEL1	_T("PathNudgeUpPixel1")
#define OPTOKEN_PATHNUDGEUPPIEL10	_T("PathNudgeUpPixel10")

#define OPTOKEN_PATHNUDGEDOWN1		 _T("PathNudgeDown1")
#define OPTOKEN_PATHNUDGEDOWN5		 _T("PathNudgeDown5")
#define OPTOKEN_PATHNUDGEDOWN10		 _T("PathNudgeDown10")
#define OPTOKEN_PATHNUDGEDOWNFIFTH	 _T("PathNudgeDownFifth")
#define OPTOKEN_PATHNUDGEDOWNPIXEL1	 _T("PathNudgeDownPixel1")
#define OPTOKEN_PATHNUDGEDOWNPIXEL10 _T("PathNudgeDownPixel10")


#define OPTOKEN_PATHNUDGELEFT1		 _T("PathNudgeLeft1")
#define OPTOKEN_PATHNUDGELEFT5		 _T("PathNudgeLeft5")
#define OPTOKEN_PATHNUDGELEFT10		 _T("PathNudgeLeft10")
#define OPTOKEN_PATHNUDGELEFTFIFTH	 _T("PathNudgeLeftFifth")
#define OPTOKEN_PATHNUDGELEFTPIXEL1	 _T("PathNudgeLeftPixel1")
#define OPTOKEN_PATHNUDGELEFTPIXEL10 _T("PathNudgeLeftPixel10")


#define OPTOKEN_PATHNUDGERIGHT1		  _T("PathNudgeRight1")
#define OPTOKEN_PATHNUDGERIGHT5		  _T("PathNudgeRight5")
#define OPTOKEN_PATHNUDGERIGHT10	  _T("PathNudgeRight10")
#define OPTOKEN_PATHNUDGERIGHTFIFTH	  _T("PathNudgeRightFifth")
#define OPTOKEN_PATHNUDGERIGHTPIXEL1  _T("PathNudgeRightPixel1")
#define OPTOKEN_PATHNUDGERIGHTPIXEL10 _T("PathNudgeRightPixel10")



#define DECLARE_OPPATHNUDGE_CLASS(DIR1) \
	class OpPathNudge ## DIR1 : public OpPathNudge \
	{ \
	CC_DECLARE_DYNCREATE(OpPathNudge ## DIR1) \
	public: \
		virtual void Do(OpDescriptor* pOpDesc); \
	}; \

DECLARE_OPPATHNUDGE_CLASS	(Up1)
DECLARE_OPPATHNUDGE_CLASS	(Up5)
DECLARE_OPPATHNUDGE_CLASS	(Up10)
DECLARE_OPPATHNUDGE_CLASS	(UpFifth)
DECLARE_OPPATHNUDGE_CLASS	(UpPixel1)
DECLARE_OPPATHNUDGE_CLASS	(UpPixel10)

DECLARE_OPPATHNUDGE_CLASS	(Down1)
DECLARE_OPPATHNUDGE_CLASS	(Down5)
DECLARE_OPPATHNUDGE_CLASS	(Down10)
DECLARE_OPPATHNUDGE_CLASS	(DownFifth)
DECLARE_OPPATHNUDGE_CLASS	(DownPixel1)
DECLARE_OPPATHNUDGE_CLASS	(DownPixel10)

DECLARE_OPPATHNUDGE_CLASS	(Left1)
DECLARE_OPPATHNUDGE_CLASS	(Left5)
DECLARE_OPPATHNUDGE_CLASS	(Left10)
DECLARE_OPPATHNUDGE_CLASS	(LeftFifth)
DECLARE_OPPATHNUDGE_CLASS	(LeftPixel1)
DECLARE_OPPATHNUDGE_CLASS	(LeftPixel10)

DECLARE_OPPATHNUDGE_CLASS	(Right1)
DECLARE_OPPATHNUDGE_CLASS	(Right5)
DECLARE_OPPATHNUDGE_CLASS	(Right10)
DECLARE_OPPATHNUDGE_CLASS	(RightFifth)
DECLARE_OPPATHNUDGE_CLASS	(RightPixel1)
DECLARE_OPPATHNUDGE_CLASS	(RightPixel10)


#endif  
